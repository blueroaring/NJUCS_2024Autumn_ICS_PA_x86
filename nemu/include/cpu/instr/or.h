#ifndef __INSTR_OR_H__
#define __INSTR_OR_H__
/*
Put the declarations of `or' instructions here.
*/
make_instr_func(or_i2a_b);//0C
make_instr_func(or_i2a_v);//0D
make_instr_func(or_i2rm_b);//80
make_instr_func(or_i2rm_v);//81
make_instr_func(or_i2rm_bv);//83
make_instr_func(or_r2rm_b);//08
make_instr_func(or_r2rm_v);//09
make_instr_func(or_rm2r_b);//0A
make_instr_func(or_rm2r_v);//0B
#endif
