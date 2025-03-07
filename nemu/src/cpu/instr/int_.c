#include "cpu/intr.h"
#include "cpu/instr.h"

/*
Put the implementations of `int' instructions here.

Special note for `int': please use the instruction name `int_' instead of `int'.
*/
make_instr_func(int_){
print_asm_0("int_","",1);
    OPERAND imm;
    imm.type=OPR_IMM;
    imm.data_size=8;
    imm.sreg=SREG_CS;
    imm.addr=eip+1;
    operand_read(&imm);
    raise_sw_intr(imm.val);
    return 0;
}
