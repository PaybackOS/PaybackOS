#include <stdint.h>
#include <stdio.hpp>

extern "C" void syscall(int syscall_number, const char* msg);

extern "C" void userspace_c(void) {
    syscall(1, "This message is from the userspace\n");
    while(1) {
    }
}
