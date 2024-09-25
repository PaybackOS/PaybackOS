#include <stdio.hpp>

extern "C" void C_handler(void) {
    klog(3, "Exception handler called, shutting down kernel\n");
}