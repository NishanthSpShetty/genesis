/* isr ahdlers
 * */

#include "kernel/interrupt.h"
#include "kernel/tty.h"

void com_isr_handler(register_t reg){
	terminal_writestring("\n\n Unhandleled Interrupt occured \n");
	return;
}
