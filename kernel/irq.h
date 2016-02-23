#ifndef IRQ_H
#define IRQ_H

//PIC definitions
#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_CNTRL PIC1
#define PIC2_CNTRL PIC2
#define PIC1_DATA PIC1+1
#define PIC2_DATA PIC2+1
#define EOI 20
void init_pic();

#endif /* irq.h */
