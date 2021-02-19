#ifndef TIMER_H
#define TIMER_H
/* Defines all timer
 * headers and macros
 */
#include "../include/stdtypes.h"

#define PIT_PORT_DATA 0x40   // channel 0
#define PIT_PORT_DATA2 0x42  // channel 1
#define PIT_PORT_CNTRL 0x43  // common to channel 0 and channel 2
#define PIT_IN_F 1193180     // Hz
void init_timer(uint16_t frequency);
void timer_handler();

#endif /* timer.h */
