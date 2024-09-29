#include <stdio.hpp>

extern "C" void userspace_c(void) {
    print("This message is from the userspace\n");
    while(1) {
    }
}
