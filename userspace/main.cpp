#include <stdio.hpp>
#include <vfs.h>

extern "C" void userspace_c(void) {
    print("This is being printed from the userspace!\n");
    klog(1, "test log from userspace");
    readfile("Test.txt");
    while(1) {
    }
}
