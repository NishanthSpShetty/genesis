/* isr ahdlers
 * */

#include "kernel/interrupt.h"
#include "kernel/timer.h"
#include "kernel/tty.h"

/* Interrupt dispatcher
 * param register content and interrupt info @register_t
 * */
void com_isr_handler(register_t reg){
//	terminal_writestring("\n\n Interrupt occured...dispatching handler \n");
	switch(reg.int_no){
		case 0:
			terminal_writestring("\nDevide by zero exception\n");
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 30:
		case 31:
			terminal_writestring("\nInterrupt handler for this interrupt hasn't been registered yet.");
			write_dec(reg.int_no);	
			break;
			
		case 14:
			page_fault_handler(reg);
			break;
		case 32:
			//timer interrupt
			timer_handler();
			break;
		case 34:
		case 35:
		case 36:
			break;
		case 33:
			keyboard_handler();
			return;
		default:
			terminal_writestring("\nInterrupt handler for this interrupt hasn't been registered yet.");
			write_dec(reg.int_no);	
	}
	

	return;
}
