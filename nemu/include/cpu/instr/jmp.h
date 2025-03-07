#ifndef __INSTR_JMP_H__
#define __INSTR_JMP_H__

make_instr_func(jmp_near);//E9
make_instr_func(jmp_short);//EB
make_instr_func(jmp_near_indirect);//FF
make_instr_func(jmp_far_imm);//EA
#endif
