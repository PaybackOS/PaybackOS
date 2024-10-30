.global print
.global putchar
.global klog
.global getch
.global halt
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

getch:
    movl $4, %eax # Getch
    int $80
    ret

halt:
    movl $0, %eax # Halt
    int $80
    ret