.global exception_handler
.extern C_handler

exception_handler:
    pusha                // Push all general-purpose registers onto the stack
    cli                  // Disable interrupts

    call C_handler

    // Infinite loop to halt execution
.loop:
    hlt                  // Halt the CPU
    jmp .loop            // Stay in this loop indefinitely