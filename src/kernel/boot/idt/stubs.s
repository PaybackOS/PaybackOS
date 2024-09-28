.extern C_handler
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

common_isr_stub:
//  Uncomment to create a BOCHS magic breakpoint
//  xchg %bx, %bx

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
    push %esp        // Arg 1 is a pointer to the interrupt stack_frame
    call C_handler   // Call the common exception handler for errors
    pop %eax         // Remove argument from stack

    // Restore segment registers
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popal

    add $8, %esp     // Remove interrupt numnber and error code
    iret             // Return from interrupt

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

// isr_labelX is a macro that generates a 32-bit long
// pointing to an isr_stub_NNN stub function.
.altmacro
.macro isr_labelX number
    .long isr_stub_\number
.endm

.global isr_stub_table
.section .data

// Create a stub table of 256 entries
isr_stub_table:
// Create entries for the first 32 exceptions
.set i,0
.rept 32
    isr_labelX %i
    .set i, i+1
.endr
// Create entries in isr_stub_table for the remaining 224 interrupts
// including IRQs (from 32 to 48). Generate the stub code for each
// entry at the same time. All these stubs have no error code
// pushed by the CPU on the stack.
.rept 256-32
    // Generate stub code for this isr
    .section .text
    isr_no_err_stub %i

    // Switch bakc and generate an entry i isr_stub_table
    .section .data
    isr_labelX %i
    .set i, i+1
.endr
