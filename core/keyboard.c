/*Keyboard handler module*/
#include "kernel/keyboard.h"
#include "kernel/tty.h"
#include "kernel/irq.h"
void keyboard_handler(){
	uint8_t status;
	uint8_t keycode;
	uint8_t shift=0;

	//Signal EOI to PIC [ACK]
	outb(PIC1_CNTRL,EOI);
	status = inb(KEYBOARD_STATUS_PORT);
	if(status & 0x01){
		//buffer is full->read
	keycode = inb(KEYBOARD_DATA_PORT);
		if(keycode<0)
			return;
		//get the keyboard character :scancode
			
		status = keyboard_map[keycode];
		if(keycode == 0x2A){
			shift=1;
			return;
		}
		//if(shift)
		//	status -= 32;
		terminal_putchar(status);
		if(status == '\n')
			terminal_writestring(">>");
	}
	return;
}
