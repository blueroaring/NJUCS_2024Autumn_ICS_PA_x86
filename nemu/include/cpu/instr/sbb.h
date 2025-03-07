#ifndef __INSTR_SBB_H__
#define __INSTR_SBB_H__
/*
Put the declarations of `sbb' instructions here.
*/
make_instr_func(sbb_i2a_b);//1C
make_instr_func(sbb_i2a_v);//1D
make_instr_func(sbb_i2rm_b);//80
make_instr_func(sbb_i2rm_v);//81
make_instr_func(sbb_i2rm_bv);//83
make_instr_func(sbb_r2rm_b);//18
make_instr_func(sbb_r2rm_v);//19
make_instr_func(sbb_rm2r_b);//1A
make_instr_func(sbb_rm2r_v);//1B
#endif
