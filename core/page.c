#include "kernel/paging.h"
#include "include/stdtypes.h"
#include "kernel/tty.h"
#include "kernel/interrupt.h"
#include "include/string.h"
extern uint32_t kernel_heap_addr;



void initialize_paging(){
uint32_t *kernel_page_dir =(uint32_t *) kmalloc(4*1024,1,0);

uint32_t *page_table = (uint32_t*) kmalloc(4*1024,1,0);
	uint32_t address=0;
	uint32_t i=0;
	for(;i<1024;i++){
		page_table[i] = address|3;
		address +=4096; //4k align
	}

	kernel_page_dir[0] = (uint32_t)page_table;
		
	kernel_page_dir[0] = kernel_page_dir[0]|3;

	for(i=1;i<1024;i++){
		kernel_page_dir[i]= 0|2;
	}

	switch_page_dir(kernel_page_dir);
}
