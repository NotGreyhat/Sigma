#ifndef PMM_H
#define PMM_H

#include <stddef.h>
#include <stdint.h>


void* kmalloc(size_t size, uint8_t align);
void pmm_init();
uint32_t fetch_free_memory();
uint64_t getmem();

#endif
