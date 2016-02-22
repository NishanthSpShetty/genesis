global load_gdt
global load_idt
load_gdt:
	;pop gdt_ptr to eax
	mov eax,[esp+4]
	lgdt [eax] ;

	;load the segments
	mov ax,0x10 ; GDT offset (base)_ptr
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
	;to change code segment
	jmp 0x08:.done
.done:
	ret

load_idt:
	mov eax,[esp+4]
	lidt [eax]
	ret
