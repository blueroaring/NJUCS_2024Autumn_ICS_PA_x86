#include "cpu/instr.h"
/*
Put the implementations of `lidt' instructions here.
*/
make_instr_func(lidt){
#ifdef IA32_INTR
        OPERAND r;
        int len=1;
        r.data_size=16;
        len+=modrm_rm(eip+1,&r);
        operand_read(&r);
        cpu.idtr.limit=r.val;
        r.addr+=2;
        r.data_size=32;
        operand_read(&r);
        cpu.idtr.base=r.val;
        return len;
#else
return 1;
#endif
}
