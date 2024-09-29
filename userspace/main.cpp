#include <cstdio.hpp>

extern "C" void userspace_c(void) {
    print("This is being printed from the userspace!\n");
    while(1) {
    }
}
