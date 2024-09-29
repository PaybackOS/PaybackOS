.global print
.global putchar
.global klog
.global malloc
.global free
.type print, @function

print:
    movl $1, %eax        # Set the system call number to 1 (write string)
    movl 4(%esp), %ebx  # Load the first argument (address of the string)
    int $80             # Trigger the interrupt
    ret                 # Return to the calling function

putchar:
    movl $2, %eax        # Set the system call number to 2 (write character)
    movl 4(%esp), %ebx  # Load the first argument (character to write)
    int $80             # Trigger the interrupt
    ret                 # Return to the calling function

klog:
    movl $3, %eax # Set the system call number to 3 (log)
    movl 4(%esp), %ebx # Move the int for the log level to the first argument
    movl 8(%esp), %ecx # Move the const char* for the log to the 2nd argument
    int $80
    ret

malloc:
    movl $4, %eax # Set the system call number to 4 (malloc)
    movl 4(%esp), %ebx # Set the size
    int $80
    ret

free:
    movl $5, %eax
    movl 4(%esp), %ebx # The pointer to free
    int $80
    ret