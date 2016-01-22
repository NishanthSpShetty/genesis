/*
   kernel.c
 */

#include "kernel/tty.h"
#include "kernel/vga.h"
void start_kernel(void){

	//initialize the terminal
	terminal_initialize();
	terminal_writestring("Second version of Ni-OS");
	terminal_setcolor(make_color(COLOR_RED,COLOR_BROWN));
	terminal_setcolor(make_color(COLOR_BLACK,COLOR_LIGHT_CYAN));
	terminal_writeat(" By Nishanth Shetty",2,8);

}
