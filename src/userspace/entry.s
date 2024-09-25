.global switch_to_user_mode
.extern userspace_c

switch_to_user_mode:
    mov $0x3, %ax               # Set up for ring 3 (use 0x3 instead of (4 * 8) | 3)
    shl $3, %ax                 # Shift left by 3 bits to get the segment selector
    mov %ax, %ds                # Move the data segment selector to DS
    mov %ax, %es                # Move the data segment selector to ES
    mov %ax, %fs                # Move the data segment selector to FS
    mov %ax, %gs                # Move the data segment selector to GS
    # SS is handled by iret, so no need to modify it here

    # Set up the stack frame iret expects
    mov %esp, %eax              # Store current stack pointer in EAX
    push $0x3                    # Push data selector (ring 3)
    push %eax                   # Push current ESP
    pushf                       # Push EFLAGS
    push $0x1B                  # Push code selector (0x1B for ring 3 code)
    push $userspace_c    # Push the instruction address to return to
    iret                        # Return to user mode
