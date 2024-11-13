.global user_print
.global user_putchar
.global log
.global halt
.global checkdebug
.global user_malloc
.global user_free
.global user_realloc
.global user_calloc
.global get_scancode

user_print:
    movl $1, %eax # Write string
    movl 4(%esp), %ebx  # String we are writing
    int $80
    ret

user_putchar:
    movl $2, %eax # Write Character
    movl 4(%esp), %ebx # Character
    int $80
    ret

log:
    movl $3, %eax # Log with levels
    movl 4(%esp), %ebx # Log level
    movl 8(%esp), %ecx # Log
    int $80
    ret

halt:
    movl $0, %eax # Halt
    int $80
    ret

checkdebug:
    movl $5, %eax # Check if debug
    int $80
    ret

user_malloc:
    movl $6, %eax # Malloc function
    movl 4(%esp), %ebx # Amount to malloc
    int $80
    ret

user_free:
    movl $7, %eax # Free function
    movl 4(%esp), %ebx # The pointer to free
    int $80
    ret

user_calloc:
    movl $8, %eax # Calloc function
    movl 4(%esp), %eax
    movl 8(%esp), %eax
    int $80
    ret

user_realloc:
    movl $9, %eax # The realloc (resize) function
    movl 4(%esp), %eax # The pointer
    movl 8(%esp), %eax # The size
    int $80
    ret

get_scancode:
    movl $10, %eax
    int $80
    ret