#include <stdint.h>
#include <stdio.hpp>

extern "C" void userspace_c(void) {
    // asm("cli"); // This code should cause a GPF since we are in ring 3.
    asm("int $80");
    while(1) {
    }
}
