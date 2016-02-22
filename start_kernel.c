/*
   kernel.c
 */

#include "kernel/tty.h"
#include "kernel/vga.h"
#include "kernel/descriptors.h"
void start_kernel(void){
	int i;
	//initialize the terminal
	terminal_initialize();
	terminal_writestring("Loading gdt into memory");
	init_gdt();
	init_idt();
	terminal_writestring(":[done]");
	clear_screen();
	terminal_setcolor(make_color(COLOR_BLUE,COLOR_LIGHT_CYAN));
	terminal_writestring("-------------------------------------Ni-OS--------------------------------------\n");
	terminal_setcolor(make_color(COLOR_BLACK,COLOR_LIGHT_CYAN));
	terminal_writestring("\n");
	terminal_writestring("Implementation of a kernel");

//	asm volatile("int $2");
//	asm volatile("int $0x00");
//	asm volatile("int $0x00");
//	asm volatile("int $0x00");
//	asm volatile("int $0x00");
	terminal_writeat("Nishanth Shetty",65,24);

}
