#include <stdio.hpp>
#include <string.hpp>
#include <stdlib.hpp>
#include <vfs.h>

#define debug 1

extern "C" void userspace_c(void) {
    print("This is being printed from the userspace!\n");
    klog(1, "test log from userspace");
    // Test our userspace VFS
    readfile("Test.txt");
    if (debug) {
        // Test our userspace heap
        print("Testing our userspace heap...\n");
        void* heap_str = malloc(19);
        strcpy((char*)heap_str, "hi from the heap!\n");
        print((char*)heap_str);
        free(heap_str);
    }
    while(1) {
    }
}
