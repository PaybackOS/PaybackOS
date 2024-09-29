#include <stdio.hpp>

extern "C" void userspace_c(void) {
    print("This is being printed from the userspace!\n");
    klog(1, "test log from userspace");
    while(1) {
    }
}
