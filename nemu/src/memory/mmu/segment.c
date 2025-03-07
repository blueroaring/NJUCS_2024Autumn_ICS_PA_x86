#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
    
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	#ifdef IA32_SEG 
	return cpu.segReg[sreg].base+offset;
	#else
	return 0;
	#endif
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)//laddr gdtrÖĞµØÖ·
{
    #ifdef IA32_SEG
   /* printf("base=0x%x",cpu.gdtr.base);
    uint32_t segDesAddr=(uint32_t)hw_mem+cpu.gdtr.base+cpu.segReg[sreg].index*8;//the index is byte,which needs to multiply 8
	SegDesc*seg_desc=(SegDesc*)segDesAddr;//a pointer
	//assert(segDesc->granularity == 1);
	assert(seg_desc->present==1);
	uint32_t base=(seg_desc->base_31_24<<24)+(seg_desc->base_23_16<<16)+seg_desc->base_15_0;
	uint32_t limit=(seg_desc->limit_19_16<<16)+seg_desc->limit_15_0;
	assert(base<=0);
//	assert(limit>=0xFFFFF);
	cpu.segReg[sreg].base=base;
	cpu.segReg[sreg].limit=limit;
	cpu.segReg[sreg].privilege_level=seg_desc->privilege_level;
	cpu.segReg[sreg].type=seg_desc->segment_type;
	cpu.segReg[sreg].soft_use=seg_desc->soft_use;*/
  SegDesc segdesc;
 // printf("base=0x%x",cpu.gdtr.base);
  segdesc.val[0]=laddr_read(cpu.gdtr.base+cpu.segReg[sreg].index*sizeof(SegDesc),4);
	segdesc.val[1]=laddr_read(cpu.gdtr.base+cpu.segReg[sreg].index*sizeof(SegDesc)+4,4);
	assert(segdesc.present==1);
 assert(segdesc.granularity==1);
	cpu.segReg[sreg].base=segdesc.base_15_0+(segdesc.base_23_16<<16)+(segdesc.base_31_24<<24);
	cpu.segReg[sreg].limit=segdesc.limit_15_0+(segdesc.limit_19_16<<16);
  cpu.segReg[sreg].privilege_level=segdesc.privilege_level;
  cpu.segReg[sreg].type=segdesc.segment_type;
  cpu.segReg[sreg].soft_use=segdesc.soft_use;
	#endif
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	 
}
