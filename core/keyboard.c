/*Keyboard handler module*/
#include "kernel/keyboard.h"
#include "kernel/tty.h"
#include "kernel/irq.h"
void keyboard_handler(){
	uint8_t status;
	uint8_t keycode;

	//Signal EOI to PIC [ACK]
//	outb(PIC1_CNTRL,EOI);
	outb(0x20,0x20);
	status = inb(KEYBOARD_STATUS_PORT);
	if(status & 0x01){
		//buffer is full->read
		keycode = inb(KEYBOARD_DATA_PORT);
		if(keycode<0)
			return;
		write_dec(keycode,0);
		terminal_putchar(' ');
		return;
	}
	outb(0x20,0x20);
	return;
}
