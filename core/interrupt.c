/* isr ahdlers
 * */

#include "kernel/interrupt.h"
#include "kernel/tty.h"

void com_isr_handler(register_t reg){
	terminal_writestring("\n\n Unhandleled Interrupt occured : ");
	write_dec(reg.int_no,0);
	terminal_putchar('|');
	write_dec(reg.int_no,1);

	return;
}
