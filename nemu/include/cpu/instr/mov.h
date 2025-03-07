#ifndef __INSTR_MOV_H__
#define __INSTR_MOV_H__

make_instr_func(mov_r2rm_b);//88
make_instr_func(mov_r2rm_v);//89
make_instr_func(mov_rm2r_b);//8A
make_instr_func(mov_rm2r_v);//8B
make_instr_func(mov_i2rm_b);//B0+rb ib
make_instr_func(mov_i2rm_v);//B8+rw,iw or +rd,id
make_instr_func(mov_i2r_b);//C6
make_instr_func(mov_i2r_v);//C7
make_instr_func(mov_o2a_b);//A0
make_instr_func(mov_o2a_v);//A1
make_instr_func(mov_a2o_b);//A2
make_instr_func(mov_a2o_v);//A3
make_instr_func(mov_zrm82r_v);
make_instr_func(mov_zrm162r_l);
make_instr_func(mov_srm82r_v);
make_instr_func(mov_srm162r_l);
make_instr_func(mov_rm2s_w);//8E
make_instr_func(mov_c2r_l);//
make_instr_func(mov_r2c_l);//

make_instr_func(movs_v);
make_instr_func(movs_b);

make_instr_func(cmova_rm2r_v);
make_instr_func(cmovae_rm2r_v);
make_instr_func(cmovb_rm2r_v);
make_instr_func(cmovbe_rm2r_v);
make_instr_func(cmovg_rm2r_v);
make_instr_func(cmovge_rm2r_v);
make_instr_func(cmovl_rm2r_v);
make_instr_func(cmovle_rm2r_v);
make_instr_func(cmovne_rm2r_v);
make_instr_func(cmovno_rm2r_v);
make_instr_func(cmovnp_rm2r_v);
make_instr_func(cmovns_rm2r_v);
make_instr_func(cmovo_rm2r_v);
make_instr_func(cmovp_rm2r_v);
make_instr_func(cmovs_rm2r_v);
make_instr_func(cmove_rm2r_v);

#endif
