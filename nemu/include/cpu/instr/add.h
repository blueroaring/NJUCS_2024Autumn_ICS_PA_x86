#ifndef __INSTR_ADD_H__
#define __INSTR_ADD_H__
/*
Put the declarations of `add' instructions here.
*/
make_instr_func(add_r2rm_b);//00
make_instr_func(add_r2rm_v);//01
make_instr_func(add_rm2r_b);//02
make_instr_func(add_rm2r_v);//03
make_instr_func(add_i2a_b);//04
make_instr_func(add_i2a_v);//05
make_instr_func(add_i2rm_b);//80 /0 ib
make_instr_func(add_i2rm_v);//81 /0 iw,id
make_instr_func(add_i2rm_bv);//83 /0 ib,符号扩展单独写吗？为什么呢？是因为默认符号扩展吗？

#endif
