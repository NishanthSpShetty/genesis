/*
   kernel.c
 */

#include "kernel/tty.h"
void start_kernel(void){

	//initialize the terminal
	terminal_initialize();
	terminal_writestring("Second version of Ni-OS");

}
