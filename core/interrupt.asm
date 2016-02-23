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
global isr32
global isr33
global isr34
global isr35
global isr36
global isr37
global isr38
global isr39
global isr40
global isr41
global isr42
global isr43
global isr44
global isr45
global isr46
global isr47

extern com_isr_handler


isr0:
	
		cli
		push byte 0
		push byte 0
		jmp com_isr_stub_handler
isr1:
	
		cli
		push byte 1
		push byte 1
		jmp com_isr_stub_handler

isr2:
	
		cli
		push byte 2
		push byte 2
		jmp com_isr_stub_handler

isr3:
		cli
		push byte 3
		push byte 3
		jmp com_isr_stub_handler

isr4:
		cli
		push byte  4
		push byte  4
		jmp com_isr_stub_handler

isr5:
		cli
		push byte  5
		push byte  5
		jmp com_isr_stub_handler

isr6:
		cli
		push byte  6
		push byte  6
		jmp com_isr_stub_handler

isr7:
		cli
		push byte  7
		push byte  7
		jmp com_isr_stub_handler

isr8:
	      
		cli
		push byte  8
		push byte  8
		jmp com_isr_stub_handler

isr9:
	      
		cli
		push byte  9
		push byte  9
		jmp com_isr_stub_handler

isr10:
	      
		cli
		push byte  10
		push byte  10
		jmp com_isr_stub_handler

isr11:   
	      
		cli
		push byte  11
		push byte  11
		jmp com_isr_stub_handler

isr12: 
	      
		cli
		push byte  12
		push byte  12
		jmp com_isr_stub_handler

isr13:
	      
		cli
		push byte  13
		push byte  13
		jmp com_isr_stub_handler

isr14:
	      
		cli
		push byte  14
		push byte  14
		jmp com_isr_stub_handler

isr15:
	      
		cli
		push byte  15
		push byte  15
		jmp com_isr_stub_handler

isr16:
	      
		cli
		push byte  16
		push byte  16
		jmp com_isr_stub_handler

isr17:
	      
		cli
		push byte  17
		push byte  17
		jmp com_isr_stub_handler

isr18:
	      
		cli
		push byte  18
		push byte  18
		jmp com_isr_stub_handler

isr19:
	      
		cli
		push byte  19
		push byte  19
		jmp com_isr_stub_handler

isr20:
	      
		cli
		push byte  20
		push byte  20
		jmp com_isr_stub_handler

isr21:   
	      
		cli
		push byte  21
		push byte  21
		jmp com_isr_stub_handler

isr22:
	      
		cli
		push byte  22
		push byte  22
		jmp com_isr_stub_handler

isr23:
		cli
		push byte 23
		push byte 23
		jmp com_isr_stub_handler

isr24:
		cli
		push byte 24
		push byte 24
		jmp com_isr_stub_handler

isr25:
		cli
		push byte 25
		push byte 25
		jmp com_isr_stub_handler

isr26:
		cli
		push byte 26
		push byte 26
		jmp com_isr_stub_handler

isr27:
		cli
		push byte 27
		push byte 27
		jmp com_isr_stub_handler

isr28:
	       
		cli
		push byte   28
		push byte   28
		jmp com_isr_stub_handler

isr29:
	       
		cli
		push byte   29
		push byte   29
		jmp com_isr_stub_handler

isr30:
		cli
		push byte 30
		push byte 30
		jmp com_isr_stub_handler

isr31:    
		cli
		push byte   31
		push byte   31
		jmp com_isr_stub_handler

isr32:   
		cli
		push byte   32
		push byte   32
		jmp com_isr_stub_handler

isr33:   
		cli
		push byte   33
		push byte   33
		jmp com_isr_stub_handler
isr34:   
		cli
		push byte   34
		push byte   34
		jmp com_isr_stub_handler
isr35:   
		cli
		push byte   35
		push byte   35
		jmp com_isr_stub_handler
isr36:   
		cli
		push byte   36
		push byte   36
		jmp com_isr_stub_handler
isr37:   
		cli
		push byte   37
		push byte   37
		jmp com_isr_stub_handler
isr38:   
		cli
		push byte   38
		push byte   38
		jmp com_isr_stub_handler
isr39:   
		cli
		push byte   39
		push byte   39
		jmp com_isr_stub_handler
isr40:   
		cli
		push byte   40
		push byte   40
		jmp com_isr_stub_handler
isr41:   
		cli
		push byte   41
		push byte   41
		jmp com_isr_stub_handler
isr42:   
		cli
		push byte   42
		push byte   42
		jmp com_isr_stub_handler
isr43:   
		cli
		push byte   43
		push byte   43
		jmp com_isr_stub_handler
isr44:   
		cli
		push byte   44
		push byte   44
		jmp com_isr_stub_handler
isr45:   
		cli
		push byte   45
		push byte   45
		jmp com_isr_stub_handler
isr46:   
		cli
		push byte   46
		push byte   46
		jmp com_isr_stub_handler

isr47:   
		cli
		push byte   47
		push byte   47
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
	iretd ; pop cs eip eflags ss esp
