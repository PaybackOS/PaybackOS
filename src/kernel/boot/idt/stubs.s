.extern exception_handler

// Define ISR stubs that call exception_handler
.macro isr_err_stub num
isr_stub_\num:
    call exception_handler  // Call the common exception handler
    iret                    // Return from interrupt
.endm

.macro isr_no_err_stub num
isr_stub_\num:
    call exception_handler  // Call the common exception handler
    iret                    // Return from interrupt
.endm

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

.global isr_stub_table
isr_stub_table:
    .rept 32              // Repeat the following 32 times
        .long isr_stub_0   // Start with ISR stub 0
    .endr
