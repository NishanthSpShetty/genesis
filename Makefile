FLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
all: tty.o string.o desc.o start_sys.o start_kernel.o 
	@echo "Linking to flat bin file kernel-2001"
	ld -m elf_i386 -T link.ld -o kernel-2001 start_sys.o tty.o start_kernel.o string.o gdt.o gdt_l.o


tty.o:core/tty.c
	gcc $(FLAGS) -c core/tty.c -o tty.o -I .
string.o: core/string.c
	gcc $(FLAGS) -c core/string.c -o string.o -I .
desc.o:core/gdt_x86.c core/gdt_x86.asm
	gcc $(FLAGS) -c core/gdt_x86.c -o gdt.o -I .
	nasm -f elf32 core/gdt_x86.asm -o gdt_l.o


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
	grub-mkrescue -o myos.iso isodir
	@echo "Running the kernel..[kernel-2001]"
	qemu-system-i386 -cdrom myos.iso
clean:
	rm *.o
	rm -R isodir
	rm myos.iso

