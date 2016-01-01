all:kernel_asm.o kernel_c.o
	@echo "Linking to flat bin file kernel-2001"
	ld -m elf_i386 -T link.ld -o kernel-2001 kernel_asm.o kernel_c.o

kernel_asm.o :kernel.asm
	@echo "Compiling down to object files..."
	nasm -f elf32 kernel.asm -o kernel_asm.o

kernel_c.o:kernel.c
	gcc -m32 -c kernel.c -o kernel_c.o
qemu: all
	@echo "Creating iso file..."
	mkdir -p isodir/boot/grub
	cp kernel-2001 isodir/boot/
	cp grub.cfg isodir/boot/grub
	@echo "Creating bootable iso..."
	grub-mkrescue -o myos.iso isodir
	@echo "Runnibg the kernel..[kernel-2001]"
	qemu-system-i386 -cdrom myos.iso
clean:
	rm *.o
	rm -R isodir
	rm myos.iso

