#include "cpu/instr.h"
/*
Put the implementations of `add' instructions here.
*/
static void instr_execute_2op() 
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_dest.val=alu_add(sign_ext(opr_src.val,opr_src.data_size),sign_ext(opr_dest.val,opr_dest.data_size),data_size);
	operand_write(&opr_dest);
}
make_instr_impl_2op(add,r,rm,b)
make_instr_impl_2op(add,r,rm,v)
make_instr_impl_2op(add,rm,r,b)
make_instr_impl_2op(add,rm,r,v)
make_instr_impl_2op(add,i,a,b)
make_instr_impl_2op(add,i,a,v)
make_instr_impl_2op(add,i,rm,b)
make_instr_impl_2op(add,i,rm,v)
make_instr_impl_2op(add,i,rm,bv)
/*make_instr_func(add_si82rm_v){//暂时废弃
    int len=1;
    OPERAND rm,imm;
    imm.data_size=8;
    rm.data_size=data_size;
    len+=modrm_rm(eip+1,&rm);
    imm.type=OPR_IMM;
    imm.sreg = SREG_CS;
    imm.addr = eip + len;
    operand_read(&imm);
    operand_read(&rm);
    uint32_t a=sign_ext(imm.val,8);
    alu_add(a,rm.val,data_size);
    operand_write(&rm);
     return len + data_size / 8;   
    
}*/
