#ifndef __INSTR_MUL_H__
#define __INSTR_MUL_H__

make_instr_func(mul_rm2a_b);//F6
make_instr_func(mul_rm2a_v);//F7

make_instr_func(imul_rm2r_v);//0F AF
make_instr_func(imul_rm2a_b);//F6
make_instr_func(imul_rm2a_v);//F7
make_instr_func(imul_irm2r_v);//69
make_instr_func(imul_i8rm2r_v);//6B

#endif
