;;kernel.asm

;nasm directive - 32 bit
bits 32


MBALIGN   equ 1 << 0
MEMINFO   equ 1 << 1
FLAGS     equ MBALIGN | MEMINFO
MAGIC     equ 0x1BADB002
CHECKSUM  equ -(MAGIC + FLAGS)

section .multiboot
        ;multiboot spec
        align 4
        
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .text
global _start
extern start_kernel     ;kmain is defined in the c file

_start:
  cli 			;block interrupts
  mov esp, stack_space	;set stack pointer
  call start_kernel 
  hlt		 	;halt the CPU

section .bss
resb 8192		;8KB for stack
stack_space:
