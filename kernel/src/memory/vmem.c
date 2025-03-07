#include "common.h"
#include "memory.h"
#include <string.h>

#define VMEM_ADDR 0xa0000
#define SCR_SIZE (320 * 200)
#define NR_PT ((SCR_SIZE + PT_SIZE - 1) / PT_SIZE) // number of page tables to cover the vmem

PDE *get_updir();
PTE table[NR_PTE] align_to_page;
void create_video_mapping()
{
   PDE *pageDir=(PDE *)va_to_pa(get_updir());
   PTE *pageTable=(PTE *)va_to_pa(table);
   uint32_t index_pageDir=0x0;
   uint32_t index_pageTable=0x0;
   uint32_t index_pageFrame=0x0;
   pageDir[index_pageDir].val=make_pde(pageTable);//fill
   for(index_pageTable=0x0;index_pageTable<1024;index_pageTable++){
   pageTable->val=make_pte(index_pageFrame<<12);
   index_pageFrame++;
   pageTable++;
   }
   
	/* TODO: create an identical mapping from virtual memory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) to physical memeory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) for user program. You may define
	 * some page tables to create this mapping.
	 */

	//panic("please implement me");
}

void video_mapping_write_test()
{
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for (i = 0; i < SCR_SIZE / 4; i++)
	{
		buf[i] = i;
	}
}

void video_mapping_read_test()
{
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for (i = 0; i < SCR_SIZE / 4; i++)
	{
		assert(buf[i] == i);
	}
}

void video_mapping_clear()
{
	memset((void *)VMEM_ADDR, 0, SCR_SIZE);
}
