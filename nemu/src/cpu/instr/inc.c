#include "cpu/instr.h"
/*
Put the implementations of `inc' instructions here.
*/
static void instr_execute_1op(){
    int cf=cpu.eflags.CF;
    operand_read(&opr_src);
    opr_src.val=alu_add(1,sign_ext(opr_src.val,opr_src.data_size),opr_src.data_size);
    cpu.eflags.CF=cf;
    operand_write(&opr_src);
}
make_instr_impl_1op(inc,rm,b)
make_instr_impl_1op(inc,rm,v)
make_instr_impl_1op(inc,r,v)
