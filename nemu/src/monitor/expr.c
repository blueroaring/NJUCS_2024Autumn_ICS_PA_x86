#include "nemu.h"
#include "cpu/reg.h"
#include "memory/memory.h"

#include <stdlib.h>
extern uint32_t look_up_symtab(char *sym, bool *success);
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum
{
	NOTYPE = 256,
	EQ,
	HEX,
	NUM,
	REG,
	SYMB,
	ADD,
	SUB,
	MUL,
	DIV,
	LEFT,
	RIGHT,
	MINUS,//负号
	POINTER,
	EQUAL,
	NEQUAL,
	AND,
	OR,
	NOT
    
	/* TODO: Add more token types */

};

static struct rule
{
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */
	{"0[xX][0-9a-fA-F]{1,8}", HEX},
	{"[0-9]+", NUM},
	{"\\$[a-z]+", REG},
	{"[a-zA-Z0-9_]+", SYMB},
	{" +", NOTYPE}, // white space(不是＋号！)
	{"\\+", ADD},
	{"-", SUB},
	{"\\*", MUL},
	{"/", DIV},
	{"\\(", LEFT},
	{"\\)", RIGHT},
	{"==", EQUAL},
	{"!=", NEQUAL},
	{"&&", AND},
	{"[\\|]{2}", OR},
	{"!", NOT},
	
	
	
	
	
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]))

static regex_t re[NR_REGEX];

/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex()
{
	int i;
	char error_msg[128];
	int ret;

	for (i = 0; i < NR_REGEX; i++)
	{
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if (ret != 0)
		{
			regerror(ret, &re[i], error_msg, 128);
			assert(ret != 0);
		}
	}
}

typedef struct token
{
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e)
{
	int position = 0;
	int i;
	regmatch_t pmatch;

	nr_token = 0;

	while (e[position] != '\0')
	{
		/* Try all rules one by one. */
		for (i = 0; i < NR_REGEX; i++)
		{
			if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0)
			{
			//	char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

			//	printf("\nmatch regex[%d] at position %d with len %d: %.*s\n", i, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */

				switch (rules[i].token_type)
				{
				    case NOTYPE:
				    break;
				    case HEX:
				    tokens[nr_token].type=rules[i].token_type;
				    for(int i=0;i<substr_len;i++){
				        tokens[nr_token].str[i]=e[position-substr_len+i];
				    }
				   for(int i=substr_len;i<32;i++){
				       tokens[nr_token].str[i]='\0';
				   }
				    nr_token++;
				    break;
				    case NUM:
				    tokens[nr_token].type=rules[i].token_type;
				    int num=0;
				    for(int i=0;i<substr_len;i++){
				        num=num*10+(int)(e[position-substr_len+i]-'0');
				    }
				     uint32_t *to_str=(uint32_t*) tokens[nr_token].str;
				        *to_str=(uint32_t) num;
				        nr_token++;
				        break;
				    case REG:
				    tokens[nr_token].type=rules[i].token_type;
				    for(int i=0;i<substr_len;i++){
				        tokens[nr_token].str[i]=e[position-substr_len+i];
				    }
				     for(int i=substr_len;i<32;i++){
				       tokens[nr_token].str[i]='\0';
				   }
				    nr_token++;
				    break;
				    case SYMB:
				     tokens[nr_token].type = rules[i].token_type;
				        for(int j = 0; j < substr_len; j++){
				            tokens[nr_token].str[j] = e[position - substr_len + j];
				        }
				        for(int j = substr_len; j < 32; ++j){
				            tokens[nr_token].str[j] = '\0';
				        }
					    nr_token++;
					    break;
				default:
					tokens[nr_token].type = rules[i].token_type;
					nr_token++;
				}

				break;
			}
		}

		if (i == NR_REGEX)
		{
		//	printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true;
}
bool check_parentheses(int start,int end,bool *success){
    int left=0,right=0;
    if(tokens[start].type!=LEFT||tokens[end].type!=RIGHT) return false;
    else{
        for(int i=start+1;i<=end-1;i++){
            if(tokens[i].type==LEFT) left++;
            else if(tokens[i].type==RIGHT) right++;
            if(left<right) return false;
        }
        return true;
    }
    return true;
}
uint32_t eval(int start,int end,bool *success){
   // printf("start=%d,end=%d\n",start,end);
    if(start>end||*success==false){
        *success=false;
        return 0;
    }
   if(tokens[start].type==POINTER||tokens[start].type==NOT||tokens[start].type==MINUS){
     if(tokens[start].type==POINTER){//has problem
         int read=eval(start+1,end,success);
     //     printf("read_memory is%d\n",read);
       //      printf("read_data is%u\n",vaddr_read(read,0x0,4));
            return vaddr_read(read,0x0,4);
         
       }
            else if(tokens[start].type==NOT)
            return !eval(start+1,end,success);
            else if(tokens[start].type==MINUS) return -1*(eval(start+1,end,success));
        
    }
    else if(start==end){
        if(tokens[start].type==NUM){
            uint32_t *to_str=(uint32_t*) tokens[start].str;
            uint32_t res=*to_str;
            return res;
        }
        else if(tokens[start].type==HEX){
            unsigned int res=0;
            for(int i=2;i<10;i++){
                int offset=0;
                if(tokens[start].str[i]>='0'&&tokens[start].str[i]<='9'){
                    offset=(int) (tokens[start].str[i]-'0');
                }
                else if(tokens[start].str[i]>='a'&&tokens[start].str[i]<='f'){
                    offset=(int) (tokens[start].str[i]-'a')+10;
                }
                else if(tokens[start].str[i]>='A'&&tokens[start].str[i]<='F'){
                    offset=(int) (tokens[start].str[i]-'A')+10;
                }
                res=16*res+offset;
            }
            return res;
        }
        else if(tokens[start].type==REG){
            return get_reg_val(tokens[start].str+1,success);
        }
        else if(tokens[start].type==SYMB){
            return look_up_symtab(tokens[start].str,success);
        }
    }
    else if(start==end-1){
        if(tokens[start].type==NOT){
            return !eval(end,end,success);
        }
        else if(tokens[start].type==MINUS){//has problem
            return -1*eval(start+1,end,success);
        }
        else if(tokens[start].type==POINTER){//has problem
            uint32_t read=eval(end,end,success);
           // printf("read_memory is%d\n",read);
            return vaddr_read(read,0x0,4);//sreg先不管写成0x0
        }
    }
    else if(check_parentheses(start,end,success)){
        return eval(start+1,end-1,success);
    }
    else{
        int op=0;
        int min_priority=5;
        int curpriority=0;
        int has_brackets=0;
        for(int i=start;i<=end;i++){
           // printf("tokens.type is %d\n",tokens[i].type);
            if(tokens[i].type==ADD||tokens[i].type==SUB){
                if(!has_brackets) curpriority=3;
                else curpriority=5;
            }
            else if(tokens[i].type==MUL||tokens[i].type==DIV){
                if(!has_brackets) curpriority=4;
                else curpriority=5;
            }
            else if(tokens[i].type==AND||tokens[i].type==OR){
                if(!has_brackets) curpriority=1;
                else curpriority=5;
            }
            else if(tokens[i].type==EQUAL||tokens[i].type==NEQUAL){
                if(!has_brackets) curpriority=2;
                else curpriority=5;
            }
            else if(tokens[i].type==LEFT){
                has_brackets++;
                continue;
            }
            else if(tokens[i].type==RIGHT){
                has_brackets--;
                continue;
            }
            else {continue;}
            if(curpriority<=min_priority){
                min_priority=curpriority;
                op=i;
            }
        }
       // printf("op=%d\n",op);
        uint32_t val1;
        uint32_t val2;
         val1=eval(start,op-1,success);
         val2=eval(op+1,end,success);
        switch(tokens[op].type){
            case ADD: return val1+val2;
            case SUB: return val1-val2;
            case MUL: return val1*val2;
            case DIV: return val1/val2;
            case EQUAL: return(val1==val2);
            case NEQUAL: return(val1!=val2);
            case AND:return (val1&&val2);
            case OR: return (val1||val2);
            default: 
            printf("\nOh,the token has something wrong,thetype is %d\n",tokens[op].type);
	        fflush(stdout);
            assert(0);
        }
        
      
            
    
            
        
    }
    printf("something is zero\n");
    return 0;
    
}
uint32_t expr(char *e, bool *success)
{
	if (!make_token(e))
	{
		*success = false;
		return 0;
	}
    for(int i=0;i<nr_token;i++){
        if(tokens[i].type==SUB){
            if(i==0) tokens[i].type=MINUS;
            else if(tokens[i-1].type==ADD||tokens[i-1].type==SUB||tokens[i-1].type==MUL||tokens[i-1].type==DIV||tokens[i-1].type==LEFT||tokens[i-1].type==POINTER)  tokens[i].type=MINUS;
        }
        else if(tokens[i].type==MUL){
            if(i==0) {tokens[i].type=POINTER;
            }
            else if(i==nr_token-1){
                *success=false;
                return 0;
            }
            else if(tokens[i-1].type==ADD||tokens[i-1].type==SUB||tokens[i-1].type==MUL||tokens[i-1].type==DIV||tokens[i-1].type==LEFT||tokens[i-1].type==MINUS||tokens[i-1].type==POINTER) tokens[i].type=POINTER;
        }
    }
    *success=true;
//	printf("\nPlease implement expr at expr.c\n");
//	fflush(stdout);
//	assert(0);

	return eval(0,nr_token-1,success);
}
