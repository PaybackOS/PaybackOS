#include <stdint.h>
#include <tty.hpp>
#include <stdio.hpp>
// Define our registers that we can use in our syscall handler
typedef struct
{
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, useless_esp, ebx, edx, ecx, eax;
	uint32_t int_num, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed)) stack_frame_t;

// Define syscalls
#define SYSCALL_PRINT 1
#define SYSCALL_PUTCHAR 2
#define SYSCALL_LOG 3

void syscall_handler(stack_frame_t *frame) {
    if (frame->eax == SYSCALL_PRINT) {
        kprintf("%s", (char*)frame->ebx); // Assuming ebx points to a string
        return;
    } else if (frame->eax == SYSCALL_PUTCHAR) {
        vga::putchar(frame->ebx); // Assuming ebx is a character
        return;
    } else if (frame->eax == SYSCALL_LOG) {
        klog(frame->ebx, (const char*)frame->ecx); // Logging
        return;
    }
    return; // If no valid syscall number, do nothing
}
