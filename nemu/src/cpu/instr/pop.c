#include "cpu/instr.h"
/*
Put the implementations of `pop' instructions here.
*/
static void instr_execute_1op(){
    operand_read(&opr_src);
    OPERAND esp;
    esp.type = OPR_MEM;
    esp.data_size = data_size;
    esp.addr = cpu.esp;
    esp.sreg = SREG_SS;
    operand_read(&esp);
    opr_src.val=sign_ext(esp.val,data_size);
    operand_write(&opr_src);
    cpu.esp+=data_size/8;
   
   
   
}
make_instr_impl_1op(pop,r,v)
make_instr_func(popa){
print_asm_0("popa","",1);
    OPERAND reg;
    reg.data_size = 32;
    reg.sreg = SREG_SS;
    reg.type = OPR_MEM;
    
    reg.addr = cpu.esp;
    operand_read(&reg);
    cpu.edi = reg.val;
    cpu.esp += 4;

    reg.addr = cpu.esp;
    operand_read(&reg);
    cpu.esi = reg.val;
    cpu.esp += 4;

    reg.addr = cpu.esp;
    operand_read(&reg);
    cpu.ebp = reg.val;
    cpu.esp += 4;

    cpu.esp += 4;

    reg.addr = cpu.esp;
    operand_read(&reg);
    cpu.ebx = reg.val;
    cpu.esp += 4;

    reg.addr = cpu.esp;
    operand_read(&reg);
    cpu.edx = reg.val;
    cpu.esp += 4;

    reg.addr = cpu.esp;
    operand_read(&reg);
    cpu.ecx = reg.val;
    cpu.esp += 4;

    reg.addr = cpu.esp;
    operand_read(&reg);
    cpu.eax = reg.val;
    cpu.esp += 4;

    return 1;
}
