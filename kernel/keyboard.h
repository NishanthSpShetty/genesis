#ifndef KEYBOARD_H
#define KEYBOARD_H
/*Keyboard handlers and definitioan */
#define KEYBOARD_STATUS_PORT 0x60
#define KEYBOARD_DATA_PORT   0x64

char key[] ={
		'A','B','C'
	};
//uint8_t getch();
void keyboard_handler();


#endif /*keyboard.h*/
