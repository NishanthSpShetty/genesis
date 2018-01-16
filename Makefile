FLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
all: tty.o string.o desc.o int.o start_sys.o start_kernel.o keyboard.o timer.o kmalloc.o paging.o page.o shell.o
	@echo "Linking to flat bin file kernel-2001"
	ld -m elf_i386 -T link.ld -o kernel-2001 start_sys.o tty.o start_kernel.o string.o gdt.o gdt_l.o int.o int_.o keyboard.o timer.o kmalloc.o paging.o page.o shell.o

shell.o: core/shell.c
	gcc $(FLAGS) -c core/shell.c -o shell.o -I .

kmalloc.o: core/kmalloc.c
	gcc $(FLAGS) -c core/kmalloc.c -o kmalloc.o -I .

paging.o:core/paging.c
	gcc $(FLAGS) -c core/paging.c -o paging.o -I .
	

page.o:core/page.c
	gcc $(FLAGS) -c core/page.c -o page.o -I .

timer.o: core/timer.c
	gcc $(FLAGS) -c core/timer.c -o timer.o -I .


keyboard.o: core/keyboard.c
	gcc $(FLAGS) -c core/keyboard.c -o keyboard.o -I .


tty.o:core/tty.c
	gcc $(FLAGS) -c core/tty.c -o tty.o -I .
string.o: core/string.c
	gcc $(FLAGS) -c core/string.c -o string.o -I .
desc.o:core/gdt_x86.c core/gdt_x86.asm 
	gcc $(FLAGS) -c core/gdt_x86.c -o gdt.o -I .
	nasm -f elf32 core/gdt_x86.asm -o gdt_l.o
int.o: core/interrupt.asm core/interrupt.c
	gcc $(FLAGS) -c core/interrupt.c -o int.o -I .
	nasm -f elf32 core/interrupt.asm -o int_.o
start_sys.o :start_sys.asm
	@echo "Compiling down to object files..."
	nasm -f elf32 start_sys.asm -o start_sys.o

start_kernel.o:  start_kernel.c
	gcc $(FLAGS) -c start_kernel.c -o start_kernel.o -I .

qemu: all
	@echo "Creating iso file..."
	mkdir -p isodir/boot/grub
	cp kernel-2001 isodir/boot/
	cp grub.cfg isodir/boot/grub
	@echo "Creating bootable iso..."
	grub-mkrescue -o myos.iso isodir > /dev/null 2>&1
	@echo "Running the kernel..[kernel-2001]"
	qemu-system-i386 -cdrom myos.iso
clean:
	rm *.o
	rm -R isodir
	rm myos.iso

