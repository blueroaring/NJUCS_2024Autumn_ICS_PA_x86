#ifndef __INSTR_CALL_H__
#define __INSTR_CALL_H__
/*
Put the declarations of `call' instructions here.
*/
make_instr_func(call_near);//E8
make_instr_func(call_near_indirect);//FF
//9A似乎ref没有实现
make_instr_func(call_far_imm);//9A
#endif
