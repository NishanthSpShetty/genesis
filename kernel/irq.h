#ifndef IRQ_H
#define IRQ_H

//PIC definitions
#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_CNTRL PIC1
#define PIC2_CNTRL PIC2
#define PIC1_DATA 0x21
#define PIC2_DATA 0xA1
#define EOI 0x20
void init_pic();

#endif /* irq.h */
