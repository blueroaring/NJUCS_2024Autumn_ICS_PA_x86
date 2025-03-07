#include "cpu/instr.h"
/*
Put the implementations of `push' instructions here.
*/
static void instr_execute_1op(){
    operand_read(&opr_src);
    cpu.esp-=data_size/8;
    OPERAND esp;
    esp.type = OPR_MEM;
    esp.data_size = data_size;
    esp.addr = cpu.esp;
    esp.sreg = SREG_SS;
    esp.val = sign_ext(opr_src.val, opr_src.data_size);
    operand_write(&esp);
}
make_instr_impl_1op(push,rm,v)
make_instr_impl_1op(push,r,v)
make_instr_impl_1op(push,i,b)
make_instr_impl_1op(push,i,v)
make_instr_func(pusha){
print_asm_0("pusha","",1);
uint32_t temp = cpu.esp;
OPERAND reg;
reg.data_size=32;
reg.sreg=SREG_SS;
reg.type=OPR_MEM;

cpu.esp-=4;
reg.val=cpu.eax;
reg.addr=cpu.esp;
operand_write(&reg);

cpu.esp-=4;
reg.val=cpu.ecx;
reg.addr=cpu.esp;
operand_write(&reg);

cpu.esp-=4;
reg.val=cpu.edx;
reg.addr=cpu.esp;
operand_write(&reg);

cpu.esp-=4;
reg.val=cpu.ebx;
reg.addr=cpu.esp;
operand_write(&reg);

cpu.esp-=4;
reg.val=temp;
reg.addr=cpu.esp;
operand_write(&reg);

cpu.esp-=4;
reg.val=cpu.ebp;
reg.addr=cpu.esp;
operand_write(&reg);

cpu.esp-=4;
reg.val=cpu.esi;
reg.addr=cpu.esp;
operand_write(&reg);

cpu.esp-=4;
reg.val=cpu.edi;
reg.addr=cpu.esp;
operand_write(&reg);

return 1;
}
