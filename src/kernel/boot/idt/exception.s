.globl exception_handler
.extern C_handler

exception_handler:
    pusha                       // Push all general-purpose registers onto the stack
    cli                         // Disable interrupts

    // Retrieve the interrupt number from the stack
    // Adjust the offset based on your stack frame layout
    movl 0(%esp), %eax         // Move the interrupt number into eax

    call C_handler              // Otherwise, call the C handler

    // After returning from C_handler, halt execution
    hlt

.loop:
    hlt                        // Halt the CPU
    jmp .loop                  // Stay in this loop indefinitely
