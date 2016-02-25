/*Keyboard handler module*/
#include "kernel/keyboard.h"
#include "kernel/tty.h"
#include "kernel/irq.h"
#include "include/stdtypes.h"

extern keystat_t key_buffer;
void keyboard_handler(){
	uint8_t status=0,shift=0;

	//Signal EOI to PIC [ACK]
	outb(PIC1_CNTRL,EOI);
	status = inb(KEYBOARD_STATUS_PORT);
	if(status & 0x01){
		//buffer is full->read
	key_buffer.cur_keycode = inb(KEYBOARD_DATA_PORT);
		if(key_buffer.cur_keycode<0)
			return;
		//get the keyboard character :scancode
			
		key_buffer.cur_keychar = keyboard_map[key_buffer.cur_keycode];
		
		if( key_buffer.cur_keycode == CAPS_LOCK){
			if( key_buffer.prev_keycode == CAPS_LOCK)
				key_buffer.prev_keycode=0;
			else
				key_buffer.prev_keycode=CAPS_LOCK;
			return;
		}

		if((key_buffer.prev_keycode == LEFT_SHIFT 	 \
			||key_buffer.prev_keycode == RIGHT_SHIFT \
			|| key_buffer.prev_keycode == CAPS_LOCK) \
			&& ( key_buffer.cur_keychar<='z'&& key_buffer.cur_keychar>='a')){

			key_buffer.cur_keychar -= 32;
		}
		//display the char :[#debug]
		terminal_putchar(key_buffer.cur_keychar);
		
		if(key_buffer.cur_keychar == '\n')
			terminal_writestring(">>"); 
		if(key_buffer.prev_keycode!=CAPS_LOCK)
			key_buffer.prev_keycode = key_buffer.cur_keycode;
	}
	return;
}
