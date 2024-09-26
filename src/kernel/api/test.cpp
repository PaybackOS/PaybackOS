#include <stdio.hpp>

extern "C" void isr_0x80(void) {
    // This function will be called when int 0x80 is triggered
    printf("Userspace just called this thing BABY!\n");
}
