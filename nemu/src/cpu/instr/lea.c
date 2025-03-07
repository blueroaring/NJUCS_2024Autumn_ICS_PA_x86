#include "cpu/instr.h"
/*
Put the implementations of `lea' instructions here.
*/
make_instr_func(lea){
    OPERAND r,m;
     print_asm_0("lea","",1);
    //r.type=OPR_REG;
   // r.sreg=SREG_CS;
    //m.sreg=SREG_CS;
    r.data_size=m.data_size=data_size;
    int len=1;
    len+=modrm_r_rm(eip+1,&r,&m);
    //operand_read(&r);
    r.val=sign_ext(m.addr,data_size);
    operand_write(&r);
    return len;
}
