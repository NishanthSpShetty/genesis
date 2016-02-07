/*
   kernel.c
 */

#include "kernel/tty.h"
#include "kernel/vga.h"
void start_kernel(void){

	//initialize the terminal
	terminal_initialize();
	
	terminal_setcolor(make_color(COLOR_BLUE,COLOR_LIGHT_CYAN));
	terminal_writestring("-------------------------------------Ni-OS--------------------------------------\n");
	terminal_setcolor(make_color(COLOR_BLACK,COLOR_LIGHT_CYAN));
	terminal_writestring("\n");
	terminal_writestring("Implementation of a kernel\b");

	terminal_writeat("Nishanth Shetty",65,24);

}
