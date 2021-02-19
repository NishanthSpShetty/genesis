#ifndef KMALLOC_H
#define KMALLOC_H

#include "../include/stdtypes.h"
// kernel heap defined in linker using linker location counter
extern uint32_t kernel_heap_addr;

uint32_t kmalloc(uint32_t size, uint8_t align, uint32_t *phy_addr);

#endif /*kamlloc.h */
