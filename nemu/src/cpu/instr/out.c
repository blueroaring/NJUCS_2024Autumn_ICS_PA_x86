#include "cpu/instr.h"
#include "device/port_io.h"
/*
Put the implementations of `out' instructions here.
*/
make_instr_func(out_b){
    OPERAND ra,rd;
    //参考reg.h的enum
    ra.data_size = 8;
    ra.type = OPR_REG;
    ra.addr = 0x0; //AL

    rd.data_size = 16;
    rd.type = OPR_REG;
    rd.addr = 0x2;    //DX

    operand_read(&ra);
    operand_read(&rd);

    pio_write(rd.val, 1, ra.val);//it has done operand_write  AL to DX
    
    return 1;
}
make_instr_func(out_v){
OPERAND ra,rd;
    //参考reg.h的enum
    ra.data_size = data_size;
    ra.type = OPR_REG;
    ra.addr = 0x0; //AL

    rd.data_size = 16;
    rd.type = OPR_REG;
    rd.addr = 0x2;    //DX

    operand_read(&ra);
    operand_read(&rd);

    pio_write(rd.val, data_size/8, ra.val);//it has done operand_write  AL to DX
    
    return 1;
}
