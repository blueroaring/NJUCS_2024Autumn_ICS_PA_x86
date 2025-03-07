#ifndef __INSTR_PUSH_H__
#define __INSTR_PUSH_H__
/*
Put the declarations of `push' instructions here.
*/
make_instr_func(push_rm_v);//FF /6?
make_instr_func(push_r_v); //50+rw,rd
make_instr_func(push_i_b);//6A
make_instr_func(push_i_v);//68
make_instr_func(pusha);
//CS等寄存器暂时不知道怎么做,不实现了？
#endif
