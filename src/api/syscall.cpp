#include <liballoc.h> // Include your memory allocation functions

// Define syscalls
#define SYSCALL_PRINT 1
#define SYSCALL_PUTCHAR 2
#define SYSCALL_LOG 3
#define SYSCALL_MALLOC 4
#define SYSCALL_FREE 5

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
    } else if (frame->eax == SYSCALL_MALLOC) {
        int size = frame->ebx; // Size to allocate (assuming ebx contains the size)
        void* ptr = malloc(size); // Call your custom malloc function
        frame->eax = (uint32_t)ptr; // Return the allocated pointer in eax
        return;
    } else if (frame->eax == SYSCALL_FREE) {
        void* ptr = (void*)frame->ebx; // Pointer to free (assuming ebx contains the pointer)
        int result = free(ptr); // Call your custom free function (ecx for size)
        frame->eax = result; // Return result (0 for success, -1 for failure) in eax
        return;
    }
    return; // If no valid syscall number, do nothing
}
