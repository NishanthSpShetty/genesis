/* Module implementing decriptor init func
 * and other static function
 * */

#include "kernel/descriptors.h"
#include "kernel/interrupt.h"
#include "include/string.h"
//GDT loader a extrern func
//defined in asm
extern void load_gdt(uint32_t);
extern void load_idt(uint32_t);
//gdt table and pointer initializer

//static void init_gdt_table(gdt_entry_t* desc,uint32_t base,uint32_t limit,uint8_t access,uint8_t flags);
static void __init_gdt();
static void __init_idt();

gdt_entry_t gdt_entries[GDT_SIZE];
gdt_ptr_t gdt_ptr;

idt_entry_t idt_entries[IDT_SIZE];
idt_ptr_t idt_ptr;


void init_gdt(){
	__init_gdt();
}

void init_idt(){
	__init_idt();
}

static void init_gdt_table(gdt_entry_t *desc,uint32_t base,uint32_t limit,uint8_t access,int8_t flags){
	
	//initialize base and limits
	desc->limit_low   = (limit & 0xffff);
	desc->base_low    =  (base  & 0xffff);
	desc->base_middle = (base & 0xff0000) >> 16;
	desc->base_high   = (base>>24) & 0xff;
	desc->limit_up	  = (limit & 0xf0000) >> 16;
	//access bits
	desc->access	  = access;
	desc->flags	  = (flags & 0xf);

}


static void __init_gdt(){
	//load gdt base table address
	gdt_ptr.base = (uint32_t)gdt_entries;
	//setup the limit [65536-1]
	gdt_ptr.limit = (sizeof(gdt_entry_t)*GDT_SIZE -1);

	//initialize the tables 
	//setup null gdt table
	init_gdt_table(&gdt_entries[0],0x0,0x0,0x0,0x0);
	//kernel code and data
	init_gdt_table(&gdt_entries[1],0x0,0xffffffff, 0x9a ,0xcf);
	init_gdt_table(&gdt_entries[2],0x0,0xffffffff, 0x92,0xcf);
	//user code and data
	init_gdt_table(&gdt_entries[3],0x0,0xffffffff, 0xfa,0xcf);
	init_gdt_table(&gdt_entries[4],0x0,0xffffffff, 0xf2,0xcf);
	load_gdt((uint32_t)&gdt_ptr);
}


void __init_idt(){
	idt_ptr.base = (uint32_t)idt_entries;
	idt_ptr.limit = (uint16_t)(sizeof(idt_entries)*IDT_SIZE -1);
	
	//init idt tables
	memset(idt_entries,0,IDT_SIZE);

	load_idt((uint32_t)&gdt_ptr);
}
