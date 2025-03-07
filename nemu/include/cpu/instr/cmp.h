#ifndef __INSTR_CMP_H__
#define __INSTR_CMP_H__
/*
Put the declarations of `cmp' instructions here.
*/
make_instr_func(cmp_i2a_b);//3C
make_instr_func(cmp_i2a_v);//3D
make_instr_func(cmp_i2rm_b);//80
make_instr_func(cmp_i2rm_v);//81
make_instr_func(cmp_i2rm_bv);//83
make_instr_func(cmp_r2rm_b);//38
make_instr_func(cmp_r2rm_v);//39
make_instr_func(cmp_rm2r_b);//3A
make_instr_func(cmp_rm2r_v);//3B
#endif
