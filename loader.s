#stuff for grub, kind of like a password
.set MAGIC, 0x1badb002 
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM


.section .text
.extern kernelMain
.extern callConstructors
.global loader


loader:
    mov $kernel_stack, %esp
    call callConstructors
    push %eax #pushing pointer to multiboot structure, taht store info about RAM, kernel, etc
    push %ebx #oushing register that stores magic number
    call kernelMain

#infinite loop
_stop:
    cli
    hlt
    jmp _stop

#you defining stack yourself. not sure what happens if we start overriding kernel
.section .bss
.space 2*1024*1024; # 2 MiB
kernel_stack:

