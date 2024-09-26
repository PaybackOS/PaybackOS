.global switch_to_user_mode
.extern userspace_c

switch_to_user_mode:
    mov $0x1B, %ax              // Load the data selector (for ring 3) into %ax
    mov %ax, %ds                // Move %ax to %ds
    mov %ax, %es                // Move %ax to %es 
    mov %ax, %fs                // Move %ax to %fs 
    mov %ax, %gs                // Move %ax to %gs // SS is handled by iret

    // Set up the stack frame iret expects
    mov %eax, %esp              // Move the value of %eax to %esp
    push $0x1B                  // Push the data selector
    push %eax                   // Push current esp
    pushf                       // Push flags
    push $0x23                  // Push the code selector (for ring 3)
    push userspace_c           // Push instruction address to return to
    iret
