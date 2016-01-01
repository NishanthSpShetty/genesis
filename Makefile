all:kernel_asm.o kernel_c.o
	ld -m elf_i386 -T link.ld -o kernel-2001 kernel_asm.o kernel_c.o

kernel_asm.o :kernel.asm
	nasm -f elf32 kernel.asm -o kernel_asm.o

kernel_c.o:kernel.c
	gcc -m32 -c kernel.c -o kernel_c.o
qemu: all
	mkdir -p isodir/boot/grub
	cp kernel-2001 isodir/boot/
	cp grub.cfg isodir/boot/grub
	grub-mkrescue -o myos.iso isodir
	qemu-system-i386 -cdrom myos.iso
clean:
	rm *.o
