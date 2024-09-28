#include <stdint.h>
#include <stdio.hpp>

extern "C" void userspace_c(void) {
    // asm("int $0x80"); // This code causes the kernel to have an invalid opcode.
    while(1) {
    }
}
