.global print      # Make the function globally accessible
.type print, @function

print:
    movl $1, %eax        # Set the system call number to 1 (write)
    movl 4(%esp), %ebx  # Load the first argument (address of the string)
    int $80             # Trigger the interrupt
    ret                 # Return to the calling function
