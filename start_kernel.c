/*
   kernel.c
 */

#include "kernel/tty.h"
#include "kernel/vga.h"
#include "kernel/descriptors.h"
#include "kernel/timer.h"
#include "kernel/kmalloc.h"
#include "kernel/paging.h"
#include "include/stdtypes.h"
#include "include/string.h"
//temp key value storage
void start_kernel(void){
	//initialize the terminal
	terminal_initialize();
	terminal_writestring("Loading gdt into memory");
	init_gdt();
	init_idt();
	init_pic();
	initialize_paging();
	clear_screen();
	terminal_setcolor(make_color(COLOR_BLUE,COLOR_LIGHT_CYAN));
	terminal_writestring("-------------------------------------Ni-OS--------------------------------------");
//	terminal_writeat("Nishanth Shetty [",57,24);
	terminal_setcolor(make_color(COLOR_GREEN,COLOR_BLACK));
//	terminal_writestring("Implementation of a kernel");

	//initialize and start timer to interrupt at every 10ms >100Hz
	
	init_timer(1000);
	terminal_writeat("Time:[",62,24);
	terminal_writestring("Start typing...\n>>");
	terminal_writestring("Testing paging...");
	uint32_t *ptr = (uint32_t*)0xa0000fff0f0;
//	asm volatile("int $14");
	uint32_t fault = *ptr;

	while(1){
	}
}
