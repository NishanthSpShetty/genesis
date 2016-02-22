global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
extern com_isr_handler


isr0:
	
		cli
		push byte 2
		push byte 3
		jmp com_isr_stub_handler
isr1:
	
		cli
		push byte 2
		push byte 3
		jmp com_isr_stub_handler

isr2:
	
		cli
		push byte 2
		push byte 3
		jmp com_isr_stub_handler

isr3:
		cli
		push byte 2
		push byte 3
		jmp com_isr_stub_handler

isr4:
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr5:
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr6:
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr7:
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr8:
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr9:
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr10:
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr11:   
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr12: 
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr13:
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr14:
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr15:
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr16:
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr17:
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr18:
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr19:
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr20:
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr21:   
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr22:
	      
		cli
		push byte  2
		push byte  3
		jmp com_isr_stub_handler

isr23:
		cli
		push byte 2
		push byte 3
		jmp com_isr_stub_handler

isr24:
		cli
		push byte 2
		push byte 3
		jmp com_isr_stub_handler

isr25:
		cli
		push byte 2
		push byte 3
		jmp com_isr_stub_handler

isr26:
		cli
		push byte 2
		push byte 3
		jmp com_isr_stub_handler

isr27:
		cli
		push byte 2
		push byte 3
		jmp com_isr_stub_handler

isr28:
	       
		cli
		push byte   2
		push byte   3
		jmp com_isr_stub_handler

isr29:
	       
		cli
		push byte   2
		push byte   3
		jmp com_isr_stub_handler

isr30:
		cli
		push byte 2
		push byte 3
		jmp com_isr_stub_handler

isr31    
		cli
		push byte   2
		push byte   3
		jmp com_isr_stub_handler



com_isr_stub_handler:
	pusha
	mov ax,ds
	push eax
	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	call com_isr_handler

	pop eax
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	popa
	add esp,8
	sti
	iret ; pop cs eip eflags ss esp
