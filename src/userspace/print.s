.global syscall      # Make the function globally accessible
.type syscall, @function

syscall:
    movl 4(%esp), %eax  # Move the first argument (number) into eax
    movl 8(%esp), %ebx  # Move the second argument (string) into ebx
    int $80             # Trigger the interrupt
    ret                 # Return to the calling function
