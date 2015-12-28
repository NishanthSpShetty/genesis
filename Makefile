all:kernel_asm.o kernel_c.o
	ld -m elf_i386 -T link.ld -o kernel-2001 kernel_asm.o kernel_c.o

kernel_asm.o :kernel.asm
	nasm -f elf32 kernel.asm -o kernel_asm.o

kernel_c.o:kernel.c
	gcc -m32 -c kernel.c -o kernel_c.o

clean:
	rm *.o
