#ifndef __INSTR_RET_H__
#define __INSTR_RET_H__
/*
Put the declarations of `ret' instructions here.
*/
make_instr_func(ret_near);//C3
make_instr_func(ret_near_imm16);//C2
make_instr_func(ret_far);//CB
make_instr_func(ret_far_imm16);//CA
//CA，CBref中未实现
#endif
