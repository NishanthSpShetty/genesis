/*timer function and interrupt hanlers
 * */

#include "../kernel/timer.h"

#include "../include/stdtypes.h"
#include "../kernel/irq.h"
#include "../kernel/tty.h"

// define initializer
void init_timer(uint16_t frequency)
{
    uint16_t divisor = PIT_IN_F / frequency;

    outb(PIC1_DATA, 0xf0);  // init
    outb(PIT_PORT_CNTRL, 0x36);
    // send the frequency divisor
    // lower 2byte
    outb(PIT_PORT_DATA, (divisor & 0xff));
    outb(PIT_PORT_DATA, (divisor >> 8 & 0xff));
}

// define timer interrupt handler
uint32_t count = 0, seconds = 0, min = 0, hour = 0;

void timer_handler()
{
    // send End Of Interrupt to master
    outb(PIC1, EOI);
    if (count % 1000 == 0) {
        write_dec_at(hour, 68, 24);
        terminal_writeat("h:", 70, 24);
        write_dec_at(min, 72, 24);
        terminal_writeat("m:", 74, 24);
        write_dec_at(seconds++, 76, 24);
        terminal_writeat("s]", 78, 24);
        if (seconds == 60) {
            min++;
            seconds = 0;
        }
        if (min == 60) {
            min = 0;
            hour++;
            if (hour == 12) hour = 0;
        }
    }
    count++;
    return;
}
