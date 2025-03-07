#include "memory/mmu/cache.h"
#include <stdlib.h>

#ifdef CACHE_ENABLED 

extern uint8_t hw_mem[];
extern void hw_mem_write(paddr_t paddr, size_t len, uint32_t data);


// init the cache
void init_cache()
{
     for(int i=0;i<1024;i++){
         CacheLine[i].valid=false;
         CacheLine[i].tag=0;
         memset(CacheLine[i].val_block,0,64);
     }	
}
// write data to cache

// write data to cache
/*void cache_write(paddr_t paddr, size_t len, uint32_t data)//len:读入长度,data:待写入数据
{
	uint32_t inner_addr=paddr&0x0000003f;//lower 6 bits,块内地址
	uint32_t line_id=(paddr>>6)&0x0000007f;//7bits,组号
	uint32_t tag=paddr>>13;//tag
	int get_block=line_id*8;//要hit的块号
  if(inner_addr+len<=64){
  for(int i=get_block;i<get_block+8;i++){
        if(CacheLine[i].valid==true&&CacheLine[i].tag==tag){
              memcpy(&(CacheLine[i].val_block[inner_addr]), &data, len);
              memcpy(hw_mem + paddr, &data, len);
	            return;
        }
  }
   memcpy(hw_mem + paddr, &data, len);
   return;
  }
  else{
       for(int i=8*(line_id);i<8*(line_id+1);i++){
       if(CacheLine[i].valid==true&&CacheLine[i].tag==tag){
           memcpy(&(CacheLine[i].val_block[inner_addr]), &data, 64 - inner_addr);
           memcpy(hw_mem + paddr, &data, len);
           break;
       }
       }
       if(line_id+1==128) {
       line_id=-1;
       tag++;
       }
       for(int j=8*(line_id+1);j<8*(line_id+2);j++){
       if(CacheLine[j].valid==true&&CacheLine[j].tag==tag){
       memcpy(&(CacheLine[j].val_block[0]), ((uint8_t*) (&data)) + 64 - inner_addr, len - (64 - inner_addr));
       memcpy(hw_mem + paddr, &data, len);
       break;
       }
       } 
       memcpy(hw_mem + paddr, &data, len);  
       return;
  }

}*/
void cache_write(paddr_t paddr, size_t len, uint32_t data)//len:读入长度,data:待写入数据
{
	uint32_t inner_addr=paddr&0x0000003f;//lower 6 bits,块内地址
	uint32_t line_id=(paddr>>6)&0x0000007f;//7bits,组号
	uint32_t tag=paddr>>13;//tag
	int get_block=line_id*8;//要hit的块号
  if(inner_addr+len<=64){
  for(int i=get_block;i<get_block+8;i++){
        if(CacheLine[i].valid==true&&CacheLine[i].tag==tag){
              memcpy(&(CacheLine[i].val_block[inner_addr]), &data, len);
              memcpy(hw_mem + paddr, &data, len);
	            return;
        }
  }
   memcpy(hw_mem + paddr, &data, len);
   return;
  }
  else{
        int this_line_write=64-inner_addr;//这行要写多少
	            int next_line_write=len-this_line_write;//后面行要写多少
				cache_write(paddr, this_line_write, data);//写这行
				cache_write(paddr + this_line_write, next_line_write, data>>(this_line_write * 8));//paddr清偏移量（顺便行号+1），data移动对应的字节（2^b）
	        memcpy(hw_mem + paddr, &data, len);
	        return;

  }
	//write through,not write allocate
}

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len)
{
	uint32_t line_id = (paddr >> 6) & 0x0000007F;
	uint32_t tag = paddr >> 13;
	uint32_t inner_addr = paddr & 0x0000003F;
	if(inner_addr + len <= 64){
	    for(int i = 8 * line_id; i < 8 * (line_id + 1); i++){
	        if(CacheLine[i].valid==true && tag == CacheLine[i].tag){
	            uint32_t ret = 0;
	            memcpy(&ret, &(CacheLine[i].val_block[inner_addr]), len);
	            return ret;
	        }
	    }
	    for(int i = 8 * line_id; i < 8 * (line_id + 1); i++){
	        if(CacheLine[i].valid==false){
              
	            memcpy(CacheLine[i].val_block, hw_mem + (paddr&0xFFFFFFC0), 64);
	            CacheLine[i].valid = true;
	            CacheLine[i].tag = tag;
	            uint32_t ret = 0;
	            memcpy(&ret, &(CacheLine[i].val_block[inner_addr]), len);
	            return ret;
	        }
	    }
         srand(tag+inner_addr*8);
	    int random = 8 * line_id + rand() % 8;
      //printf("rand=%d\n",random);
	    memcpy(CacheLine[random].val_block, hw_mem + (paddr&0xFFFFFFC0), 64);
	    CacheLine[random].valid = true;
	    CacheLine[random].tag = tag;
	    uint32_t ret = 0;
	    memcpy(&ret, &(CacheLine[random].val_block[inner_addr]), len);
	    return ret;
	}
	else{
	    uint32_t ret = 0;
	    for(int k = 0; k < 2; ++k){
	        if(line_id + k == 128){
	            line_id = -1;
	            tag++;
	        }
	        bool flag = false;
	        for(int i = 8 * (line_id + k); i < 8 * (line_id + k + 1); i++){
	            if(CacheLine[i].valid==true && tag == CacheLine[i].tag){
	                uint32_t temp = 0;
	                if(k == 0){
	                    memcpy(&temp, &(CacheLine[i].val_block[inner_addr]), 64 - inner_addr);
	                    ret = temp;
	                }
	                else{
	                    memcpy(&temp, &(CacheLine[i].val_block[0]), len - (64 - inner_addr));
	                    ret = ret + (temp << (8 * (64 - inner_addr)));
	                }
	                flag = true;
	                break;
	            }
	        }
	        if(flag){
	            continue;
	        }
	        for(int i = 8 * (line_id + k); i < 8 * (line_id + k + 1); i++){
	            if(CacheLine[i].valid==false){
	                memcpy(CacheLine[i].val_block, hw_mem + (((tag << 7) + (line_id + k)) << 6), 64);
	                CacheLine[i].valid = true;
	                CacheLine[i].tag = tag;
	                uint32_t temp = 0;
	                if(k == 0){
	                    memcpy(&temp, &(CacheLine[i].val_block[inner_addr]), 64 - inner_addr);
	                    ret = temp;
	                }
	                else{
	                    memcpy(&temp, &(CacheLine[i].val_block[0]), len - (64 - inner_addr));
	                    ret = ret + (temp << (8 * (64 - inner_addr)));
	                }
	                flag = true;
	                break;
	            }
	        }
	        if(flag){
	            continue;
	        }
                 srand(tag+inner_addr*8);
	        int random = 8 * (line_id + k) + rand() % 8;
	        memcpy(CacheLine[random].val_block, hw_mem + (((tag << 7) + (line_id + k)) << 6), 64);
	        CacheLine[random].valid = true;
	        CacheLine[random].tag = tag;
	        uint32_t temp = 0;
	        if(k == 0){
	            memcpy(&temp, &(CacheLine[random].val_block[line_id]), 64 - inner_addr);
	            ret = temp;
	        }
	        else{
	            memcpy(&temp, &(CacheLine[random].val_block[0]), len - (64 - inner_addr));
	            ret = ret + (temp << (8 * (64 - inner_addr)));
	        }
	    }
	    return ret;
	}
}

#endif


