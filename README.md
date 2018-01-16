#Genesis

Hobby OS,an attempt to develop a simple 32 bit kernel using Assembly and C. 


## Prerequisite
1. gcc
2. nasm
3. QEMU
4. Grub Bootloader with grub-mkrescue

## Following features are implemented
1. Timer
2. GDT
3. IDT
4. Memory Management functions like memcopy, memset
5. Interrupt handlers
6. Keyboard driver
7. Display Scrolling
8. System time
9. Pagination 
... (FIX:Cant use, Triple faults CPU)
10. Basic shell
...TODO: Add more feautures to shell, to replicate \*nix shell




# Compilation 

Make will build and create bootable iso using grub tools. To build the OS use following command and run the emulator

```
    make all
    qemu-system-i386 -cdrom myos.iso
	```

You can compile and bring up the system with following command

    ```
    make qemu
    ```

To clean the project, issue following command
    ```
    make clean
    ```
