/*********************************************
 * linker script to link all the object files
 * link.ld
 *
 ********************************************/

OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)
SECTIONS{
	. = 0x100000;
	.text : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
	.data : {*(.text)}
	.bss :  {*(.bss)}
	kernel_heap_addr = .;
}
