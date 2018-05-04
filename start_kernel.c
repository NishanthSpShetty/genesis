/**
 * kernel.c
 * c entrypoint
 *
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
	clear_screen();
	terminal_setcolor(make_color(COLOR_BLUE,COLOR_LIGHT_CYAN));
	terminal_writestring("-------------------------------------Ni-OS--------------------------------------");
	terminal_writeat("Nishanth Shetty ",0,24);
	terminal_setcolor(make_color(COLOR_GREEN,COLOR_BLACK));
//	terminal_writestring("Implementation of a kernel");

	//initialize and start timer to interrupt at every 10ms >100Hz
	
//	initialize_paging();
	init_timer(1000);
	terminal_writeat("Time:[",62,24);
	terminal_writestring("Shell is ready for you... ;-)\n>>");
	terminal_writestring("Testing paging...");
//	uint32_t *ptr = (uint32_t*)0xafff0;
//	asm volatile("int $14");
//	uint32_t fault = *ptr;
//	*ptr='A';
//	terminal_putchar(*ptr);

	while(1){
	}
}
