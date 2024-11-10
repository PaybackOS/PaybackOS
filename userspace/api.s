.global user_print
.global user_putchar
.global user_klog
.global user_halt
.global user_checkdebug
.global user_fulldebug
.global user_malloc
.global user_free
.global user_realloc
.global user_calloc

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

user_klog:
    movl $3, %eax # Log with levels
    movl 4(%esp), %ebx # Log level
    movl 8(%esp), %ecx # Log
    int $80
    ret

user_halt:
    movl $0, %eax # Halt
    int $80
    ret

user_checkdebug:
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