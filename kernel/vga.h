#ifndef _KERNEL_VGA_H
#define _KERNEL_VAG_H

/*Header defining vga properties and function
 * definitions
 * */

#include "include/stdtypes.h"

//Screen width and height
#define VGA_WIDTH 80
#define VGA_HEIGHT 25


//A pointer to the vga memory @0xb8000
static uint16_t* const vga_mem_ptr = (uint16_t*)0xB8000;

//Basic colors provided by vga
enum vga_color{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

/* function which returns the attribute defining foreground
 * and background color
 * @parm foreground_color :fg
 * 	 background_color :bg
 * */

static uint8_t make_color(enum vga_color fg,enum vga_color bg);
static uint16_t make_vgaentry(uint8_t _char,uint8_t color);
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);



static uint8_t make_color(enum vga_color fg,enum vga_color bg){
	//8 bytes attribute 
	//First(Upper) nibble defines background
	//Second nibble defines foregraound color
	return fg | (bg<<4);
}

/* function which makes the entry in the vga memory(screen)
 * 16 bits >> unsigned int
 * first byte char to print 
 * second byte attribute value returned by the make_color
 * */
static uint16_t make_vgaentry(uint8_t _char,uint8_t color){
	uint16_t _screen_val=color;
	_screen_val<<=8;
	return _screen_val | _char;
}
 
#endif  /* vga.h */
