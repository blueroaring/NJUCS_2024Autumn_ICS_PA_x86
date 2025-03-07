#include "cpu/instr.h"
/*
Put the implementations of `ret' instructions here.
*/
make_instr_func(ret_near){
   OPERAND ip;
   print_asm_0("ret_near"," " ,1);
    ip.type=OPR_MEM;
    ip.data_size=data_size;
    ip.addr=cpu.esp;
    ip.sreg=SREG_SS;
    cpu.esp+=data_size/8;
    operand_read(&ip);
    cpu.eip=sign_ext(ip.val,data_size);
    if(data_size==16)
    cpu.eip&=0x0000FFFF;
   // print_asm_0("ret_near"," " ,1);
    return 0;
}
make_instr_func(ret_near_imm16){
    OPERAND ip,imm;
  // print_asm_0("ret_nearimm1"," " ,1);
    ip.type=OPR_MEM;
    imm.type=OPR_IMM;
    imm.data_size=data_size;
    imm.addr=eip+1;
    operand_read(&imm);
    ip.data_size=data_size;
    ip.sreg=SREG_SS;
    ip.addr=cpu.esp;
    cpu.esp+=data_size/8;
    operand_read(&ip);
    cpu.eip=sign_ext(ip.val,data_size);
    cpu.esp+=sign_ext(imm.val,data_size);
    print_asm_0("ret_nearimm"," " ,1);
    return 0;
}
make_instr_func(ret_far){
      OPERAND ip;
  // print_asm_0("ret_far1"," " ,1);
    ip.type=OPR_MEM;
    ip.data_size=data_size;
    ip.addr=cpu.esp;
    ip.sreg=SREG_SS;
    cpu.esp+=data_size/8;
    operand_read(&ip);
    cpu.eip=ip.val;
    print_asm_0("ret_far"," " ,1);
    return 0;
}
make_instr_func(ret_far_imm16){
    OPERAND ip,imm;
  // print_asm_0("ret_farimm1"," " ,1);
    ip.type=OPR_MEM;
    imm.type=OPR_IMM;
    imm.data_size=data_size;
    imm.addr=eip+1;
    operand_read(&imm);
    ip.data_size=data_size;
    ip.sreg=SREG_SS;
    ip.addr=cpu.esp;
    cpu.esp+=data_size/8;
    operand_read(&ip);
    cpu.eip=ip.val;
    cpu.esp+=imm.val;
    print_asm_0("ret_farimm"," " ,1);
    return 0;
}