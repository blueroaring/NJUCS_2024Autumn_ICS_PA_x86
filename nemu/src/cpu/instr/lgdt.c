#include "cpu/instr.h"
/*
Put the implementations of `lgdt' instructions here.
*/
make_instr_func(lgdt){
    #ifdef IA32_SEG
    assert(data_size==32||data_size==16);
    if(data_size==32){
    OPERAND op;
    op.data_size=16;
    int len=1;
    len+=modrm_rm(eip+1,&op);
    operand_read(&op);
    cpu.gdtr.limit = op.val;
    op.data_size = 32;
    op.addr += 2;//高位加地址
    operand_read(&op);
    cpu.gdtr.base = op.val;
    //printf("cpu.gdtr.base=%x,limit=%x",cpu.gdtr.base,cpu.gdtr.limit);
    return len;
    }
    else{
         OPERAND op;
    op.data_size=16;
    int len=1;
    len+=modrm_rm(eip+1,&op);
    operand_read(&op);
    cpu.gdtr.limit = op.val;
    op.data_size = 24;
    op.addr += 1;
    operand_read(&op);
    cpu.gdtr.base = op.val;
    return len;
    }
    #else
    return 0;
    #endif
}