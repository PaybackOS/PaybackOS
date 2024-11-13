.extern init_gdt
.extern _init
.extern kernel_main

/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

/* 
Declare a multiboot header that marks the program as a kernel. These are magic
values that are documented in the multiboot standard. The bootloader will
search for this signature in the first 8 KiB of the kernel file, aligned at a
32-bit boundary. The signature is in its own section so the header can be
forced to be within the first 8 KiB of the kernel file.
*/
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/*
This is a simple stack for our OS to use since C requires a stack to function
*/
.section .bss
.align 16
stack_bottom:
.skip 32768 # 32 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	// Set up our stack before pushing data
	mov $stack_top, %esp

    // These are placed on the stack and will be used as first
    // 2 parameters to _init.
	push %eax  // Push multiboot magic number
	push %ebx  // Push multiboot info pointer

	// Init the GDT
	call init_gdt

	// Init VGATM (VGA Text Mode), GDT, PIC, IDT and such
	call _init

	// Call our kernel
	xor %ebp, %ebp    // Set %ebp to NULL for stack trace
	call kernel_main

	// If our kernel returns, shutdown everything
	cli
	hlt
/*
Set the size of the _start symbol to the current location '.' minus its start.
*/
.size _start, . - _start
