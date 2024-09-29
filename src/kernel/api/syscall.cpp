#include <stdio.hpp>
#include <tty.hpp>

typedef struct
{
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, useless_esp, ebx, edx, ecx, eax;
	uint32_t int_num, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed)) stack_frame_t;

extern volatile char last_key;

/*
EAX is the syscall number
all other registers should be considered free game other than the pointer
*/
void syscall_handler(stack_frame_t *frame) {
    if (frame->eax == 1) {
        printf("%s", frame->ebx);
        return;
    } else if (frame->eax == 2) {
        vga::putchar(frame->ebx);
        return;
    }
    return;
}
