#include "cpu/instr.h"

make_instr_func(jmp_near)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, data_size);//?
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("jmp_near", "", 1 + data_size / 8, &rel);

        cpu.eip += offset;

        return 1 + data_size / 8;
}
make_instr_func(jmp_short){
    OPERAND rel;
    rel.type=OPR_IMM;
    //rel.sreg=SREG_CS;
    rel.data_size=8;
    rel.addr=eip+1;
    operand_read(&rel);
    int offset=sign_ext(rel.val,8);
    print_asm_1("jmp_short", "",2, &rel);
    cpu.eip+=offset;
    return 2;
}
make_instr_func(jmp_near_indirect){
    OPERAND rm;
    rm.data_size=data_size;
    modrm_rm(eip+1,&rm);
    operand_read(&rm);
    int offset=sign_ext(rm.val,data_size);
    print_asm_1("jmp_near_indirect", "", rm.val, &rm);
    cpu.eip=offset;
    return 0;
    
}
make_instr_func(jmp_far_imm){//这是ljmp
    #ifdef IA32_SEG
    OPERAND ptr;
    ptr.type=OPR_IMM;
    ptr.sreg=SREG_CS;
    ptr.data_size=data_size;
    ptr.addr=eip+1;
    operand_read(&ptr);
    print_asm_1("jmp_far_imm", "", 1 + data_size / 8, &ptr);
    cpu.eip=ptr.val;
    ptr.data_size=16;//Load CS Register with new segment descripter,48bits ptr/m16:32,m16:visiable m32:invisiable
    ptr.addr+=data_size/8;//read 16bits,the second is $GDT_ENTRY(1),which addr is $va_to_pa(start_cond)+data_size/8;
    operand_read(&ptr);
    cpu.segReg[1].val=sign_ext(ptr.val,ptr.data_size);
    load_sreg(1);
    return 0;
    #else
    return 0;
    #endif
}