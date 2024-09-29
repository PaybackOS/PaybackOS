#include <stdint.h>

extern "C" void print(const char* msg);

extern "C" void userspace_c(void) {
    print("This message is from the userspace\n");
    while(1) {
    }
}
