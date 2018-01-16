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


// Handler for memio controller
void outb(uint16_t port,uint8_t value){
	asm volatile("outb %1, %0": :"dN"(port),"a"(value));
}

uint8_t inb(uint16_t port){
	uint8_t ret;
	asm volatile("inb %1,%0":"=a"(ret):"dN"(port));
	return ret;
}

uint16_t inw(uint16_t port){
	uint16_t ret;
	asm volatile("inw %1,%0":"=a"(ret):"dN"(port));
	return ret;
}

//function to intialize the screen
//black background (display color)
//grey foreground (character color)

void terminal_initialize(){
	size_t y=0,x=0,index=0;
	terminal_row=0;
	terminal_col=0;
	terminal_color = make_color(COLOR_LIGHT_GREY,COLOR_BLACK);
	terminal_buffer = vga_mem_ptr;
	
	for(x=0;x<VGA_WIDTH;x++)
		for(y=0;y<VGA_HEIGHT;y++){
			index = y*VGA_WIDTH +x;
			terminal_buffer[index] = make_vgaentry(' ',terminal_color);
		}
}

void clear_screen(){
	terminal_initialize();
}

void clear_window(){
	size_t x,y,index=0;
	terminal_row = 2;
	for(x=0;x<VGA_WIDTH;x++)
		for(y=2;y<VGA_HEIGHT;y++){
			index = y*VGA_WIDTH +x;
			terminal_buffer[index] = make_vgaentry(' ',terminal_color);
		}
}
//Set the terminal color
void terminal_setcolor(uint8_t color){
	terminal_color = color;
	
}

//error msg print

void error(const char *msg){
	uint8_t prev_color = terminal_color;
	terminal_color = make_color(COLOR_RED,COLOR_BLACK);
	terminal_writestring("[ERROR] : ");
	terminal_writestring(msg);
	terminal_color = prev_color;
}

//function to write the char on the screen at (x,y) location [RANDOM]
void terminal_putentryat(char _char,uint8_t color,size_t y,size_t x){
	size_t index;
	index = y*VGA_WIDTH +x;
	move_cursor();
	terminal_buffer[index] = make_vgaentry(_char,color);
}

//function to write the char., continuos location [LINEAR]
void terminal_putchar(char ch){

	if(terminal_row == VGA_HEIGHT){
			terminal_row = 2;
			clear_window();
		}

	//handle backspace
	if(ch == 0x08 && terminal_col){
		terminal_col--;
		ch=' ';
		terminal_putentryat(ch,terminal_color,terminal_row,terminal_col);
		ch=0;		
	}
	else if(ch=='\r'){
		terminal_col=0;
		ch=0;
	}
	else if(ch=='\t'){
		ch=0;
		terminal_col = (terminal_col+8)& ~(7);
	}
	else if(ch=='\n'){
		ch=0;
		terminal_row++;
		terminal_col=0;
	
	}

	if(ch)
		terminal_putentryat(ch,terminal_color,terminal_row,terminal_col);
	//update the rows and columns
	//check whether you reached the end of the screen
	if(ch!=0 &&  ++terminal_col == VGA_WIDTH ){
		terminal_col = 0;
		terminal_row++;
	}

	move_cursor();
}

//function to write the string onto the screen

// It will change the next write position
void terminal_writeat(const char *str,size_t x,size_t y){
	int tempx,tempy;	
	tempy = terminal_row;
	tempx = terminal_col;
	terminal_row = y;
	terminal_col= x;
	terminal_writestring(str);
	terminal_row = tempy;
	terminal_col=tempx;
	move_cursor();
}

void terminal_write(const char *str,size_t len){
	size_t i=0;
	for(;i<len;i++)
		terminal_putchar(str[i]);
}

void terminal_writestring(const char *str){
	terminal_write(str,str_len(str));
}

void move_cursor(void){
	uint16_t pos = terminal_row*VGA_WIDTH + terminal_col;
	outb(0x3D4,14);
	outb(0x3D5,pos>>8);
	outb(0x3D4,15);
	outb(0x3D5,pos);
}
//wrapper to preserve the cusror position	
void write_dec_at(uint32_t num,size_t x,size_t y){
	
	int tempx,tempy;	
	tempy = terminal_row;
	tempx = terminal_col;
	terminal_row = y;
	terminal_col= x;
	write_dec(num);
	terminal_row = tempy;
	terminal_col=tempx;
	move_cursor();
}
	
void write_dec(uint32_t num){
	uint8_t rem;
	uint32_t n=num;
	uint8_t ch[15],ch2[15];
	uint8_t i=0,j=0;
	if(num == 0){
		terminal_putchar('0');
		terminal_putchar('0');
		return;
	}
	if(num<10)
		terminal_putchar('0');

	while(n>0){
		rem = n%10;
		n   = n/10;
		ch[i++]='0'+rem;
		
	}
	ch[i]=0;
	j=i-1;
	i=0;
//	if(leading)
//		while(ch[i++]=='0');
	while(ch[i]){
		ch2[j]=ch[i];
		j--;
		i++;
	}
	ch2[i]=0;
	terminal_writestring(ch2);
	move_cursor();	
	return;
}
