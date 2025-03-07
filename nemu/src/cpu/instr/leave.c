#include "cpu/instr.h"
/*
Put the implementations of `leave' instructions here.
*/
make_instr_func(leave){

    cpu.esp=cpu.ebp;
     print_asm_0("leave"," " ,1);
    OPERAND esp;
    esp.data_size=data_size;
    esp.type=OPR_MEM;
    esp.sreg=SREG_SS;
    esp.addr=cpu.esp;
    cpu.esp+=data_size/8;
    operand_read(&esp);
    cpu.ebp=sign_ext(esp.val,data_size);
    return 1;
}
