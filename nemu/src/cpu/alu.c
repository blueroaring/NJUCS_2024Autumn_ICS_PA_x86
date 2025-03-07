#include "cpu/cpu.h"
//#define NEMU_REF_ALU
#define NEMU_ALU
uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
#ifdef NEMU_ALU
uint32_t alu_add_res=src+dest;//final result
uint64_t and_data=1;//put zero to higher bits
for(int i=0;i<data_size;i++){
    and_data*=2;
}
if(and_data!=0)
and_data-=1;
uint64_t src2=src,dest2=dest;
uint64_t data=1;
for(int i=0;i<32;i++){
    data*=2;
}
data-=1;
alu_add_res&=and_data;
src2&=and_data;
dest2&=and_data;
if(src2+dest2>and_data){
    cpu.eflags.CF=1;
}
else
cpu.eflags.CF=0;
uint32_t check_OF=alu_add_res;
for(int i=0;i<data_size-1;i++){
    src2/=2;
    dest2/=2;
    check_OF/=2;
    
}
if(src2==dest2&&src2!=check_OF){
    cpu.eflags.OF=1;
}
else
cpu.eflags.OF=0;
if(alu_add_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_add_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf=alu_add_res;
for(int i=0;i<data_size-1;i++){
    check_sf/=2;
}
if(check_sf==1)  cpu.eflags.SF=1;//为什么符号位是截断的最高位？
else cpu.eflags.SF=0;
return alu_add_res;

#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
#ifdef NEMU_ALU
uint32_t alu_add_res=dest+src+cpu.eflags.CF;
uint64_t and_data=1;
for(int i=0;i<data_size;i++){
    and_data*=2;
}
and_data-=1;
uint64_t src2=src,dest2=dest;
uint64_t data=1;
for(int i=0;i<32;i++){
    data*=2;
}
data-=1;
alu_add_res&=and_data;
src2&=and_data;
dest2&=and_data;
if(src2+dest2+cpu.eflags.CF>and_data){
    cpu.eflags.CF=1;
}
else
cpu.eflags.CF=0;
uint32_t check_OF=alu_add_res;
for(int i=0;i<data_size-1;i++){
    src2/=2;
    dest2/=2;
    check_OF/=2;
    
}
if(src2==dest2&&src2!=check_OF){
    cpu.eflags.OF=1;
}
else cpu.eflags.OF=0;
if(alu_add_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_add_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf=alu_add_res;
for(int i=0;i<data_size-1;i++){
    check_sf/=2;
}
if(check_sf==1)  cpu.eflags.SF=1;
else cpu.eflags.SF=0;
return alu_add_res;
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else

#ifdef NEMU_ALU
uint32_t alu_res=dest-src;
uint64_t and_data=1;
for(int i=0;i<data_size;i++){
    and_data*=2;
}
and_data-=1;
uint64_t data=1;
uint32_t src2=src,dest2=dest;
for(int i=0;i<32;i++){
    data*=2;
}
data-=1;
alu_res&=and_data;
src2&=and_data;
dest2&=and_data;
if(dest2<src2){
    cpu.eflags.CF=1;
}
else
cpu.eflags.CF=0;
uint32_t check_OF=alu_res;
uint32_t src3=src2;
for(int i=0;i<data_size-1;i++){
    src3/=2;
    dest2/=2;
    check_OF/=2;
    
}
if(dest2!=src3&&src3==check_OF){
    cpu.eflags.OF=1;
}
else cpu.eflags.OF=0;
if(alu_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf=alu_res;
for(int i=0;i<data_size-1;i++){
    check_sf/=2;
}
if(check_sf==1)  cpu.eflags.SF=1;
else cpu.eflags.SF=0;
return alu_res;

#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif

#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
#ifdef NEMU_ALU
uint32_t alu_res=dest-src-cpu.eflags.CF;
uint64_t and_data=1;
for(int i=0;i<data_size;i++){
    and_data*=2;
}
and_data-=1;
uint64_t data=1;
uint32_t dest2=dest;
uint64_t src2=src;
for(int i=0;i<32;i++){
    data*=2;
}
data-=1;
alu_res&=and_data;
src2&=and_data;
uint64_t src3=src2;//???为什么不加CF？
src2+=cpu.eflags.CF;

dest2&=and_data;
if(dest2<src2){
    cpu.eflags.CF=1;
}
else
cpu.eflags.CF=0;
uint32_t check_OF=alu_res;
uint32_t dest3=dest2;
for(int i=0;i<data_size-1;i++){
    src3/=2;
    dest3/=2;
    check_OF/=2;
    
}
if(dest3!=src3&&src3==check_OF){
    cpu.eflags.OF=1;
}
else cpu.eflags.OF=0;
if(alu_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf=alu_res;
for(int i=0;i<data_size-1;i++){
    check_sf/=2;
}
if(check_sf==1)  cpu.eflags.SF=1;
else cpu.eflags.SF=0;
return alu_res;
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
#ifdef NEMU_ALU
uint64_t alu_res;
uint64_t and_data=1;
for(int i=0;i<data_size;i++){
    and_data*=2;
}
and_data--;
uint64_t src_and=src&and_data;
uint64_t dest_and=dest&and_data;//32位乘不会扩展到64位！
alu_res=src_and*dest_and;
uint64_t data=alu_res;
for(int i=0;i<data_size;i++){
    data/=2;
}
if(data!=0){
    cpu.eflags.CF=1;
    cpu.eflags.OF=1;
}
else{
    cpu.eflags.CF=0;
    cpu.eflags.OF=0;
}
if(alu_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf=alu_res;
for(int i=0;i<2*data_size-1;i++){
    check_sf/=2;
}
if(check_sf==1)  cpu.eflags.SF=1;
else cpu.eflags.SF=0;
return alu_res;

#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
#ifdef NEMU_ALU
int64_t alu_res;
int64_t and_data=1;
for(int i=0;i<data_size;i++){
    and_data*=2;
}
and_data--;
uint64_t dest1=dest,src1=src;//防止64位被自动符号扩展
alu_res=src1*dest1;//左移，这里其实不考虑算术的事，也没有“认为”符号位的问题,但是务必注意，高位要全变成符号位！（为了让机器真的知道这是负数）
if(data_size!=32){
int SignData=-1;//改符号位
uint64_t signres=alu_res;//int÷2不对！
for(int i=0;i<2*data_size;i++){
    SignData=signres%2;
    signres/=2;
    
}
uint64_t sign_and_data=1;
//排除极端情况
if(SignData==0){
    for(int i=0;i<2*data_size;i++)
    {sign_and_data*=2;}
    sign_and_data-=1;
    alu_res&=sign_and_data;
}
else{
    sign_and_data=0xffffffff;
    uint64_t sub_data=1;
    for(int i=0;i<2*data_size;i++){
        sub_data*=2;
    }
    sub_data-=1;
    sign_and_data-=sub_data;
    alu_res|=sign_and_data;
}
    
}
int64_t data=alu_res;
for(int i=0;i<data_size;i++){
    data/=2;
}
if(data!=0){
    cpu.eflags.CF=1;
    cpu.eflags.OF=1;
}
else{
    cpu.eflags.CF=0;
    cpu.eflags.OF=0;
}
if(alu_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;//不测试eflags会不会以后有问题？
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf=alu_res;
for(int i=0;i<2*data_size-1;i++){
    check_sf/=2;
}
if(check_sf==1)  cpu.eflags.SF=1;
else cpu.eflags.SF=0;
return alu_res;
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
#ifdef NEMU_ALU
uint64_t and_data_dest=1,and_data_src=1;
for(int i=0;i<2*data_size;i++){
    if(i<data_size)
    and_data_src*=2;
    and_data_dest*=2;
}
and_data_src--;
and_data_dest--;
uint64_t dest_and=dest&and_data_dest;
uint64_t src_and=src&and_data_src;
if(src_and==0){
    printf("Floating Point Exception\n");
    fflush(stdout);
    return 0;
}
uint32_t alu_res=dest_and/src_and;
if(alu_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf=alu_res;
for(int i=0;i<data_size-1;i++){
    check_sf/=2;
}
if(check_sf==1)  cpu.eflags.SF=1;
else cpu.eflags.SF=0;
//除法绝对不会溢出
return alu_res;
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
#ifdef NEMU_ALU
if(src==0){
    printf("Floating Point Exception\n");
    fflush(stdout);
    return 0;
}
int32_t alu_res=dest/src;
if(data_size!=64){
int SignData=-1;//改符号位
uint64_t signres=alu_res;//int÷2不对！
for(int i=0;i<data_size;i++){
    SignData=signres%2;
    signres/=2;
    
}
uint64_t sign_and_data=1;
//排除极端情况
if(SignData==0){
    for(int i=0;i<data_size;i++)
    {sign_and_data*=2;}
    sign_and_data-=1;
    alu_res&=sign_and_data;
}
else{
    sign_and_data=0xffffffff;
    uint64_t sub_data=1;
    for(int i=0;i<data_size;i++){
        sub_data*=2;
    }
    sub_data-=1;
    sign_and_data-=sub_data;
    alu_res|=sign_and_data;
}
}
if(alu_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf=alu_res;
for(int i=0;i<data_size-1;i++){
    check_sf/=2;
}
if(check_sf==1)  cpu.eflags.SF=1;
else cpu.eflags.SF=0;
//除法绝对不会溢出

return alu_res;
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
#ifdef NEMU_ALU
if(src==0){
    printf("Floating Point Exception\n");
    fflush(stdout);
    return 0;
}
uint32_t alu_res=dest%src;
return alu_res;
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
#ifdef NEMU_ALU
if(src==0){
    printf("Floating Point Exception\n");
    fflush(stdout);
    return 0;
}
int32_t alu_res=dest%src;
return alu_res;
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
#ifdef NEMU_ALU
uint32_t alu_res=dest&src;
uint64_t and_data=1;
for(int i=0;i<data_size;i++){
    and_data*=2;
}
and_data-=1;
alu_res&=and_data;
if(alu_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf=alu_res;
for(int i=0;i<data_size-1;i++){
    check_sf/=2;
}
if(check_sf==1)  cpu.eflags.SF=1;
else cpu.eflags.SF=0;
return alu_res;
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
#ifdef NEMU_ALU
uint32_t alu_res=dest^src;
uint64_t and_data=1;
for(int i=0;i<data_size;i++){
    and_data*=2;
}
and_data-=1;
alu_res&=and_data;
if(alu_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf=alu_res;
for(int i=0;i<data_size-1;i++){
    check_sf/=2;
}
if(check_sf==1)  cpu.eflags.SF=1;
else cpu.eflags.SF=0;
return alu_res;
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
#ifdef NEMU_ALU
uint32_t alu_res=dest|src;
uint64_t and_data=1;
for(int i=0;i<data_size;i++){
    and_data*=2;
}
and_data-=1;
alu_res&=and_data;
if(alu_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf=alu_res;
for(int i=0;i<data_size-1;i++){
    check_sf/=2;
}
if(check_sf==1)  cpu.eflags.SF=1;
else cpu.eflags.SF=0;
return alu_res;
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)//算术左移src位，将被移出的位放入CF
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
#ifdef NEMU_ALU
uint32_t alu_res=dest<<src;
uint32_t data=dest<<(src-1);
data=data>>(data_size-1);
data&=0x1;
cpu.eflags.CF=data;
uint64_t and_data=1;
for(int i=0;i<data_size;i++){//对datasize位置0即可
    and_data*=2;
}
and_data-=1;
alu_res&=and_data;
if(src==1){
    uint32_t a=dest>>(data_size-2);
    a&=0x1;
    if(a==cpu.eflags.CF) cpu.eflags.OF=0;
    else cpu.eflags.OF=1;
    
}
if(alu_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf;
check_sf=alu_res>>(data_size-1);
if(check_sf==1)  cpu.eflags.SF=1;
else cpu.eflags.SF=0;
return alu_res;
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}
uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
#ifdef NEMU_ALU
uint32_t alu_res=dest>>src;
uint32_t data=dest,checkOF=-1;
for(uint32_t i=0;i<src;i++){
    checkOF=data%2;
    data/=2;
}
cpu.eflags.CF=checkOF;
uint64_t and_data=1;
for(int i=0;i<data_size-src;i++){//操作数长度是指长度，不是指之后的，当只有这几位做，前面的多余位都当不存在（为0），因此要置0
    and_data*=2;
}
and_data-=1;
alu_res&=and_data;
if(alu_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf=alu_res;
for(int i=0;i<data_size-1;i++){
    check_sf/=2;
}
if(check_sf==1)  cpu.eflags.SF=1;
else cpu.eflags.SF=0;
return alu_res;
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}
uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
#ifdef NEMU_ALU
int dest_int=dest,src_int=src;
int alu_res_1=dest_int;
int SignData=-1;//改符号位
uint32_t signdest=dest_int;
for(int i=0;i<data_size;i++){
    SignData=signdest%2;
    signdest/=2;
   
}
uint64_t sign_and_data=1;
if(SignData==0){
    for(int i=0;i<data_size;i++)
    {sign_and_data*=2;}
    sign_and_data-=1;
    alu_res_1&=sign_and_data;
}
else{
    sign_and_data=0xffffffff;
    uint64_t sub_data=1;
    for(int i=0;i<data_size;i++){
        sub_data*=2;
    }
    sub_data-=1;
    sign_and_data-=sub_data;
    alu_res_1|=sign_and_data;
}
alu_res_1=alu_res_1>>src_int;
uint64_t and_data=1;
for(int i=0;i<data_size;i++){
    and_data*=2;
}
and_data-=1;
alu_res_1&=and_data;
uint32_t alu_res=alu_res_1;
uint32_t data=dest,checkOF=-1;
for(int i=0;i<src;i++){
    checkOF=data%2;
    data/=2;
}
cpu.eflags.CF=checkOF;

if(alu_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf=alu_res;
for(int i=0;i<data_size-1;i++){
    check_sf/=2;
}
if(check_sf==1)  cpu.eflags.SF=1;
else cpu.eflags.SF=0;
return alu_res;
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
#ifdef NEMU_ALU
uint32_t alu_res=dest<<src;
uint32_t data=dest<<(src-1);
data=data>>(data_size-1);
data&=0x1;
cpu.eflags.CF=data;
uint64_t and_data=1;
for(int i=0;i<data_size;i++){//对datasize位置0即可
    and_data*=2;
}
and_data-=1;
alu_res&=and_data;
if(src==1){
    uint32_t a=dest>>(data_size-2);
    a&=0x1;
    if(a==cpu.eflags.CF) cpu.eflags.OF=0;
    else cpu.eflags.OF=1;
    
}
if(alu_res==0)
cpu.eflags.ZF=1;
else
cpu.eflags.ZF=0;
uint32_t get_pf=alu_res;
uint32_t check_pf=0;
uint32_t search_pf=0;
for(int i=0;i<8;i++){
    search_pf=get_pf%2;
    get_pf/=2;
    if(search_pf==1){
        check_pf++;
    }
}
if(check_pf%2!=0){
    cpu.eflags.PF=0;
}
else
cpu.eflags.PF=1;
uint32_t check_sf;
check_sf=alu_res>>(data_size-1);
if(check_sf==1)  cpu.eflags.SF=1;
else cpu.eflags.SF=0;
return alu_res;
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
#endif
}
