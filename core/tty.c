/*terminal functionality defined here
 * Can be used to build higher lever output functions
 * */


#include "kernel/tty.h"
#include "kernel/vga.h"
#include "include/string.h"
//terminal attribute
size_t terminal_row;
size_t terminal_col;
uint8_t terminal_color;
uint16_t* terminal_buffer;
//function to intialize the screen
//black background (display color)
//grey foreground (character color)
void terminal_initialize(){
	size_t y=0,x=0,index=0;
	terminal_row=0;
	terminal_col=0;
	terminal_color = make_color(COLOR_LIGHT_GREY,COLOR_BLACK);
	terminal_buffer = vga_mem_ptr;
	
	for(;y<VGA_HEIGHT;y++)
		for(;x<VGA_WIDTH;x++){
			index = y*VGA_WIDTH +x;
			terminal_buffer[index] = make_vgaentry(' ',terminal_color);
		}
}


//Set the terminal color
void terminal_setcolor(uint8_t color){
	terminal_color = color;
}


//function to write the char on the screen at (x,y) location [RANDOM]
void terminal_putentryat(char _char,uint8_t color,size_t y,size_t x){
	size_t index;
	index = y*VGA_WIDTH +x;
	terminal_buffer[index] = make_vgaentry(_char,color);
}

//function to write the char., continuos location [LINEAR]
void terminal_putchar(char ch){
	terminal_putentryat(ch,terminal_color,terminal_row,terminal_col);
	//update the rows and columns
	//check whether you reached the end of the screen
	if( ++terminal_col == VGA_WIDTH){
		terminal_col = 0;
		if(++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

//function to write the string onto the screen


void terminal_write(const char *str,size_t len){
	size_t i=0;
	for(;i<len;i++)
		terminal_putchar(str[i]);
}

void terminal_writestring(const char *str){
	terminal_write(str,str_len(str));
}
