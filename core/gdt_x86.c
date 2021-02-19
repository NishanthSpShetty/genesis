/* Module implementing decriptor init func
 * and other static function
 * */

#include "../include/string.h"
#include "../kernel/descriptors.h"
#include "../kernel/interrupt.h"
#include "../kernel/irq.h"
#include "../kernel/tty.h"
// GDT loader a extrern func
// defined in asm
extern void load_gdt(uint32_t);
extern void load_idt(uint32_t);
// gdt table and pointer initializer

// static void init_gdt_table(gdt_entry_t* desc,uint32_t base,uint32_t
// limit,uint8_t access,uint8_t flags);
static void __init_gdt();
static void __init_idt();

gdt_entry_t gdt_entries[GDT_SIZE];
gdt_ptr_t gdt_ptr;

idt_entry_t idt_entries[IDT_SIZE];
idt_ptr_t idt_ptr;

void init_gdt() { __init_gdt(); }

void init_idt() { __init_idt(); }
// keyboard buffer

void kb_init()
{
    outb(PIC1_DATA, 0xfd);
    //	outb(PIC2_DATA,0xfd);
}

static void init_gdt_table(gdt_entry_t *desc, uint32_t base, uint32_t limit,
                           uint8_t access, int8_t flags)
{
    // initialize base and limits
    desc->limit_low = (limit & 0xffff);
    desc->base_low = (base & 0xffff);
    desc->base_middle = (base & 0xff0000) >> 16;
    desc->base_high = (base >> 24) & 0xff;
    desc->limit_up = (limit & 0xf0000) >> 16;
    // access bits
    desc->access = access;
    desc->flags = (flags & 0xf);
}

static void __init_gdt()
{
    // load gdt base table address
    gdt_ptr.base = (uint32_t)gdt_entries;
    // setup the limit [65536-1]
    gdt_ptr.limit = (uint16_t)(sizeof(gdt_entry_t) * GDT_SIZE - 1);

    // initialize the tables
    // setup null gdt table
    init_gdt_table(&gdt_entries[0], 0x0, 0x0, 0x0, 0x0);
    // kernel code and data
    init_gdt_table(&gdt_entries[1], 0x0, 0xffffffff, 0x9a, 0xc);
    init_gdt_table(&gdt_entries[2], 0x0, 0xffffffff, 0x92, 0xc);
    // user code and data
    init_gdt_table(&gdt_entries[3], 0x0, 0xffffffff, 0xfa, 0xc);
    init_gdt_table(&gdt_entries[4], 0x0, 0xffffffff, 0xf2, 0xc);
    load_gdt((uint32_t)&gdt_ptr);
}

static void init_idt_table(idt_entry_t *this, uint32_t base, uint8_t sel,
                           uint8_t type_attr)
{
    this->base_offset_l = base & 0xffff;
    this->base_offset_h = (base & 0xff0000) >> 16;
    this->selector = sel;
    this->zero = 0;
    this->type_attr = type_attr;
}
void __init_idt()
{
    idt_ptr.base = (uint32_t)idt_entries;
    idt_ptr.limit = (uint16_t)(sizeof(idt_entry_t) * IDT_SIZE - 1);

    // init idt tables
    memset(idt_entries, 0,
           (uint16_t)IDT_SIZE * ((uint16_t)sizeof(idt_entries)));
    //	init_pic();
    // register all service routines, kernel privillaege
    init_idt_table(&idt_entries[0], (uint32_t)isr0, 0x08, 0x8E);
    init_idt_table(&idt_entries[1], (uint32_t)isr1, 0x08, 0x8E);
    init_idt_table(&idt_entries[2], (uint32_t)isr2, 0x08, 0x8E);
    init_idt_table(&idt_entries[3], (uint32_t)isr3, 0x08, 0x8E);
    init_idt_table(&idt_entries[4], (uint32_t)isr4, 0x08, 0x8E);
    init_idt_table(&idt_entries[5], (uint32_t)isr5, 0x08, 0x8E);
    init_idt_table(&idt_entries[6], (uint32_t)isr6, 0x08, 0x8E);
    init_idt_table(&idt_entries[7], (uint32_t)isr7, 0x08, 0x8E);
    init_idt_table(&idt_entries[8], (uint32_t)isr8, 0x08, 0x8E);
    init_idt_table(&idt_entries[9], (uint32_t)isr9, 0x08, 0x8E);
    init_idt_table(&idt_entries[10], (uint32_t)isr10, 0x08, 0x8E);
    init_idt_table(&idt_entries[11], (uint32_t)isr11, 0x08, 0x8E);
    init_idt_table(&idt_entries[12], (uint32_t)isr12, 0x08, 0x8E);
    init_idt_table(&idt_entries[13], (uint32_t)isr13, 0x08, 0x8E);
    init_idt_table(&idt_entries[14], (uint32_t)isr14, 0x08, 0x8E);
    init_idt_table(&idt_entries[15], (uint32_t)isr15, 0x08, 0x8E);
    init_idt_table(&idt_entries[16], (uint32_t)isr16, 0x08, 0x8E);
    init_idt_table(&idt_entries[17], (uint32_t)isr17, 0x08, 0x8E);
    init_idt_table(&idt_entries[18], (uint32_t)isr18, 0x08, 0x8E);
    init_idt_table(&idt_entries[19], (uint32_t)isr19, 0x08, 0x8E);
    init_idt_table(&idt_entries[20], (uint32_t)isr20, 0x08, 0x8E);
    init_idt_table(&idt_entries[21], (uint32_t)isr21, 0x08, 0x8E);
    init_idt_table(&idt_entries[22], (uint32_t)isr22, 0x08, 0x8E);
    init_idt_table(&idt_entries[23], (uint32_t)isr23, 0x08, 0x8E);
    init_idt_table(&idt_entries[24], (uint32_t)isr24, 0x08, 0x8E);
    init_idt_table(&idt_entries[25], (uint32_t)isr25, 0x08, 0x8E);
    init_idt_table(&idt_entries[26], (uint32_t)isr26, 0x08, 0x8E);
    init_idt_table(&idt_entries[27], (uint32_t)isr27, 0x08, 0x8E);
    init_idt_table(&idt_entries[28], (uint32_t)isr28, 0x08, 0x8E);
    init_idt_table(&idt_entries[29], (uint32_t)isr29, 0x08, 0x8E);
    init_idt_table(&idt_entries[30], (uint32_t)isr30, 0x08, 0x8E);
    init_idt_table(&idt_entries[31], (uint32_t)isr31, 0x08, 0x8E);
    init_idt_table(&idt_entries[32], (uint32_t)isr32, 0x08, 0x8E);
    init_idt_table(&idt_entries[33], (uint32_t)isr33, 0x08, 0x8E);
    init_idt_table(&idt_entries[34], (uint32_t)isr34, 0x08, 0x8E);
    init_idt_table(&idt_entries[35], (uint32_t)isr35, 0x08, 0x8E);
    init_idt_table(&idt_entries[36], (uint32_t)isr36, 0x08, 0x8E);
    init_idt_table(&idt_entries[37], (uint32_t)isr37, 0x08, 0x8E);
    init_idt_table(&idt_entries[38], (uint32_t)isr38, 0x08, 0x8E);
    init_idt_table(&idt_entries[39], (uint32_t)isr39, 0x08, 0x8E);
    init_idt_table(&idt_entries[40], (uint32_t)isr40, 0x08, 0x8E);
    init_idt_table(&idt_entries[41], (uint32_t)isr41, 0x08, 0x8E);
    init_idt_table(&idt_entries[42], (uint32_t)isr43, 0x08, 0x8E);
    init_idt_table(&idt_entries[43], (uint32_t)isr43, 0x08, 0x8E);
    init_idt_table(&idt_entries[44], (uint32_t)isr44, 0x08, 0x8E);
    init_idt_table(&idt_entries[45], (uint32_t)isr45, 0x08, 0x8E);
    init_idt_table(&idt_entries[46], (uint32_t)isr46, 0x08, 0x8E);
    init_idt_table(&idt_entries[47], (uint32_t)isr47, 0x08, 0x8E);

    load_idt((uint32_t)&idt_ptr);
}

void init_pic()
{
    uint8_t mask1, mask2;

    // get the default mask
    mask1 = inb(PIC1_DATA);
    mask2 = inb(PIC2_DATA);

    // initilize PIC ICW1

    outb(PIC1_CNTRL, 0x11);  // init bit and IC4 mode
    outb(PIC2_CNTRL, 0x11);
    // remap IVT to 32-47 ICW2
    outb(PIC1_DATA, 0x20);  // 32 master 0-7
    outb(PIC2_DATA, 0x28);  // 8-15

    // ICW3  :master ->int connections
    //	:slave  -> IRQ num of master to connect to
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);

    // ICW4 : Control how everything is to operate
    // set up PIC to x86 mode (0x01)
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);
    // mask the interrupt

    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);

    // initialize IRQ1 for keyboard
    kb_init();
}
