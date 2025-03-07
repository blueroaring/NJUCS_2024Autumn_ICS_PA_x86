#ifndef __INSTR_SHIFT_H__
#define __INSTR_SHIFT_H__

make_instr_func(shl_i2rm_bv);//C1
make_instr_func(shl_i2rm_b);//C0
make_instr_func(shl_rm_v);//D1
make_instr_func(shl_rm_b);//D0
make_instr_func(shl_c2rm_bv);//D3
make_instr_func(shl_c2rm_b);//D2

make_instr_func(shr_i2rm_bv);//C1
make_instr_func(shr_i2rm_b);//C0
make_instr_func(shr_rm_v);//D1
make_instr_func(shr_rm_b);//D0
make_instr_func(shr_c2rm_bv);//D3
make_instr_func(shr_c2rm_b);//D2

make_instr_func(sar_i2rm_bv);//C1
make_instr_func(sar_i2rm_b);//C0
make_instr_func(sar_rm_v);//D1
make_instr_func(sar_rm_b);//D0
make_instr_func(sar_c2rm_bv);//D3
make_instr_func(sar_c2rm_b);//D2

#endif
