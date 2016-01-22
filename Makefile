all: tty.o string.o start_sys.o start_kernel.o 
	@echo "Linking to flat bin file kernel-2001"
	ld -m elf_i386 -T link.ld -o kernel-2001 start_sys.o start_kernel.o tty.o string.o


tty.o:core/tty.c
	gcc -m32 -c core/tty.c -o tty.o -I .
string.o: core/string.c
	gcc -m32 -c core/string.c -o string.o -I .


start_sys.o :start_sys.asm
	@echo "Compiling down to object files..."
	nasm -f elf32 start_sys.asm -o start_sys.o

start_kernel.o:  start_kernel.c
	gcc -m32 -c start_kernel.c -o start_kernel.o -I .
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

