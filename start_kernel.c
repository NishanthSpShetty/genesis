/*
   kernel.c
 */

#include "kernel/tty.h"
#include "kernel/vga.h"
#include "kernel/descriptors.h"
#include "kernel/timer.h"
//temp key value storage
void start_kernel(void){
	//initialize the terminal
	terminal_initialize();
	terminal_writestring("Loading gdt into memory");
	init_gdt();
	init_idt();
	init_pic();
	init_timer(10000); //1ms
	clear_screen();
	terminal_setcolor(make_color(COLOR_BLUE,COLOR_LIGHT_CYAN));
	terminal_writestring("-------------------------------------Ni-OS--------------------------------------");
//	terminal_writeat("Nishanth Shetty [",57,24);
	terminal_setcolor(make_color(COLOR_GREEN,COLOR_BLACK));
//	terminal_writestring("Implementation of a kernel");

	//initialize and start timer to interrupt at every 10ms >100Hz
	
	terminal_writeat("Time: [",65,24);
	terminal_writestring("Start typing...\n>>");
	
	while(1){
	}
}
