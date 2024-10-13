.global print
.global putchar
.global klog
.global readisk
.type print, @function

print:
    movl $1, %eax # Write string
    movl 4(%esp), %ebx  # String we are writing
    int $80
    ret

putchar:
    movl $2, %eax # Write Character
    movl 4(%esp), %ebx # Character
    int $80
    ret

klog:
    movl $3, %eax # Log with levels
    movl 4(%esp), %ebx # Log level
    movl 8(%esp), %ecx # Log
    int $80
    ret

readisk:
    movl $4, %eax # Syscall to read from IDE disk
    movl 4(%esp), %ebx # Starting point of where we start to read
    movl 8(%esp), %ecx # The amount of sectors we read.
    int $80
    ret