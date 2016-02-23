/* isr ahdlers
 * */

#include "kernel/interrupt.h"
#include "kernel/tty.h"

/* Interrupt dispatcher
 * param register content and interrupt info @register_t
 * */
void com_isr_handler(register_t reg){
	terminal_writestring("\n\n Interrupt occured...dispatching handler \n");
	switch(reg.int_no){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4: terminal_writestring("dispatching isr =>");
			write_dec(reg.err_no,0);
			terminal_putchar('\n');
			break;
		default:
			terminal_writestring("Interrupt handler for this interrupt hasn't been registered yet.");
	
	}
	

	return;
}
