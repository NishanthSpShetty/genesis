/*Header file defining terminal actions
 * */

#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H
#include "include/stdtypes.h" 
 
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* string);
void terminal_writeat(const char *,size_t,size_t); 
void write_dec(uint32_t);
void write_dec_at(uint32_t,size_t, size_t);
void clear_screen();
void move_cursor(void);
void outb(uint16_t,uint8_t);
uint8_t inb(uint16_t);
uint16_t inw(uint16_t);

#endif
