#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/
make_instr_func(call_near){
        OPERAND esp;
         print_asm_0("call_near", "", 1 + data_size / 8);
        esp.type = OPR_MEM;
        esp.sreg=SREG_CS;
        esp.data_size = data_size;
        cpu.esp -= data_size / 8;//push(EIP)
        esp.addr = cpu.esp;
        esp.val = eip + 1 + data_size / 8; //这里是当前指令的下一个指令地址，所以需要额外加上 data_size/8
      // printf("%#x\n",esp.val);
        operand_write(&esp);
        OPERAND rel;
        rel.type = OPR_IMM;
     // rel.sreg = SREG_CS;
      rel.data_size = data_size;
      rel.addr = eip + 1;                                                     
      operand_read(&rel);
      int offset = sign_ext(rel.val, data_size);
      cpu.eip += offset; 
     
 		return 1 + data_size / 8;
      
    
}
make_instr_func(call_near_indirect){
    OPERAND rm, esp, ip;
    rm.data_size = data_size;
    int len = 1;
    len += modrm_rm(eip + 1, &rm);
    operand_read(&rm);
    esp.data_size = 32;
    esp.type = OPR_REG;
    esp.addr = 0x4;
    operand_read(&esp);
    ip.data_size = 32;
    ip.type = OPR_MEM;
    ip.val = cpu.eip + len;//下一条指令的地址
    esp.val -= 4;//下一条指令
    ip.addr = esp.val;
    operand_write(&esp);
    operand_write(&ip);
    if(data_size == 16){
        rm.val = sign_ext(rm.val, data_size);
    }
    cpu.eip = rm.val;
    return 0;
}
make_instr_func(call_far_imm){
   OPERAND ptr;
    ptr.type=OPR_IMM;
    ptr.sreg=SREG_CS;
    ptr.data_size=data_size;
    ptr.addr=eip+1;
    operand_read(&ptr);
    int offset = sign_ext(ptr.val, data_size);
    print_asm_1("call_far_imm", "", 1 + data_size / 8, &ptr);
    cpu.eip=offset;
    return 1 + data_size / 8;
}