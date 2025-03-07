#ifndef __OPERAND_H__
#define __OPERAND_H__

#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"

// operand type for immediate number, register, and memory
enum
{
	OPR_IMM,
	OPR_REG,
	OPR_MEM,
	OPR_CREG,
	OPR_SREG
};
/*OPR_MEM	opr->addr中保存的是一个内存地址（位于数据段或栈段）
OPR_IMM	opr->addr中保存的是一个立即数的内存地址（位于代码段）
OPR_REG	opr->addr中保存的是一个通用寄存器的编号，随着opr->data_size的不同，其对应关系略有不同。参照nemu/include/cpu/reg.h中定义的enum数据结构。
OPR_SREG	opr->addr中保存的是一个段寄存器的编号，参照nemu/include/cpu/reg.h中定义的enum数据结构。（PA 3-2用到）
OPR_CREG	opr->addr中保存的是一个控制寄存器的编号CRx, x=0,1,2,3。（PA 3-2开始用到）*/
#define MEM_ADDR_NA 0xffffffff

//enum {MEM_ADDR_OFF, MEM_ADDR_SIB};

typedef struct
{
	//	uint32_t type;
	uint32_t disp;  // hex
	uint32_t base;  // register
	uint32_t index; // register
	uint32_t scale; // 1, 2, 4, 8
} MEM_ADDR;			// memory address details

typedef struct
{
	int type;//寻址方式
	uint32_t addr;//address
	uint8_t sreg;
	uint32_t val;//value
	size_t data_size;//length of the opcode
	MEM_ADDR mem_addr;//memory address
} OPERAND;

extern OPERAND opr_src, opr_dest;

// read the operand's value from its addr
void operand_read(OPERAND *opr);

// write the operand's value to its addr
void operand_write(OPERAND *opr);
void operand_write_cr0(OPERAND *opr);

void parse_operand_address(OPERAND *opr, char *str);
void clear_operand_mem_addr(OPERAND *opr);

#endif
