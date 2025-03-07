#ifndef __CACHE_H__
#define __CACHE_H__

#include "nemu.h"

//#ifdef CACHE_ENABLED
// init the cache
struct cacheline{
    bool valid;//有效位
    uint32_t tag;//26bits   32 19 7 6 
    uint8_t val_block[64];//6bits数据 64B
    
}CacheLine[1024];//2^10行

void init_cache();

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data);

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len);

//#endif

#endif
