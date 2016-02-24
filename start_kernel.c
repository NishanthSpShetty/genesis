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
	init_pic();
	terminal_writestring(":[done]");
	
	clear_screen();
	terminal_setcolor(make_color(COLOR_BLUE,COLOR_LIGHT_CYAN));
	terminal_writestring("-------------------------------------Ni-OS--------------------------------------\n");
	terminal_writeat("Nishanth Shetty",65,24);
	terminal_setcolor(make_color(COLOR_GREEN,COLOR_BLACK));
//	terminal_writestring("Implementation of a kernel");

	terminal_writestring("\nStart typing...\n>>");
	while(1){
	}
}
