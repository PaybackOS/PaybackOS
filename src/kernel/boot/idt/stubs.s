.extern C_handler
.global syscall_stub
.extern syscall_handler
.section .text

// Define ISR stubs for exceptions with error
.macro isr_err_stub num
isr_stub_\num:
    pushl $\num
    jmp common_isr_stub
.endm

// Define ISR stubs for exceptions without error
// This applies to external IRQs too.
.macro isr_no_err_stub num
isr_stub_\num:
    pushl $0        // Push Dummy error code
    pushl $\num
    jmp common_isr_stub
.endm

syscall_stub:
    pushl $0        // Push Dummy error code
    pushl $80       // Push interrupt number

    pusha           // Push all general purpose registers
    push %ds
    push %es
    push %fs
    push %gs

    // Switch to kernel data segments
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    call syscall_handler

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa

    add $8, %esp    // Clean up error code and interrupt number
    iret            // Return from interrupt

common_isr_stub:
    xchg %bx, %bx
    pushal
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    // Switch to kernel data segments
    mov $0x10, %eax
    mov %eax, %ds
    mov %eax, %es
    mov %eax, %fs
    mov %eax, %gs

    cld
    push %esp
    call C_handler  // Call the common exception handler for errors
    pop %eax

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popal

    add $8, %esp
    iret                    // Return from interrupt

// Define stubs for exceptions (interrupts 0-31)
isr_no_err_stub 0    // Divide by Zero
isr_no_err_stub 1    // Debug Exception
isr_no_err_stub 2    // NMI Interrupt
isr_no_err_stub 3    // Breakpoint
isr_no_err_stub 4    // Overflow
isr_no_err_stub 5    // Out of Bounds
isr_no_err_stub 6    // Invalid Opcode
isr_no_err_stub 7    // Device Not Available
isr_err_stub    8    // Double Fault
isr_no_err_stub 9    // Coprocessor Segment Overrun
isr_err_stub    10   // Invalid TSS
isr_err_stub    11   // Segment Not Present
isr_err_stub    12   // Stack Fault
isr_err_stub    13   // General Protection Fault
isr_err_stub    14   // Page Fault
isr_no_err_stub 15   // Reserved
isr_no_err_stub 16   // x87 Floating Point Exception
isr_no_err_stub 17   // Alignment Check
isr_no_err_stub 18   // Machine Check
isr_no_err_stub 19   // SIMD Floating Point Exception
isr_no_err_stub 20   // Reserved
isr_no_err_stub 21   // Reserved
isr_no_err_stub 22   // Reserved
isr_no_err_stub 23   // Reserved
isr_no_err_stub 24   // Reserved
isr_no_err_stub 25   // Reserved
isr_no_err_stub 26   // Reserved
isr_no_err_stub 27   // Reserved
isr_no_err_stub 28   // Reserved
isr_no_err_stub 29   // Reserved
isr_no_err_stub 30   // Security Exception
isr_no_err_stub 31   // Reserved

// External IRQs
isr_no_err_stub 32   // IRQ0
isr_no_err_stub 33   // IRQ1
isr_no_err_stub 34   // IRQ2
isr_no_err_stub 35   // IRQ3
isr_no_err_stub 36   // IRQ4
isr_no_err_stub 37   // IRQ5
isr_no_err_stub 38   // IRQ6
isr_no_err_stub 39   // IRQ7

isr_no_err_stub 40   // IRQ8
isr_no_err_stub 41   // IRQ9
isr_no_err_stub 42   // IRQ10
isr_no_err_stub 43   // IRQ11
isr_no_err_stub 44   // IRQ12
isr_no_err_stub 45   // IRQ13
isr_no_err_stub 46   // IRQ14
isr_no_err_stub 47   // IRQ15

isr_no_err_stub 80

.global isr_stub_table

.section .data
.altmacro
.macro isr_labelX number
    .long isr_stub_\number
.endm

isr_stub_table:
.set i,0
.rept 48
    isr_labelX %i
    .set i, i+1
.endr