/* Implementation of kernel heap allocator
 * */

#include "kernel/kmalloc.h"
#include "include/stdtypes.h"


uint32_t kernel_heap = (uint32_t)&kernel_heap_addr;

uint32_t kmalloc(uint32_t size,uint8_t align){
	uint32_t temp;;
	// If the address is not already page-aligned
	// Align it.
	if (align == 1 && (kernel_heap & 0xFFFFF000))  {
	   kernel_heap &= 0xFFFFF000;
	   kernel_heap += 0x1000; //4KB
	}

	//reset kernel heap
	kernel_heap+=size;
	//return the pointer to heap
	return temp;
}
