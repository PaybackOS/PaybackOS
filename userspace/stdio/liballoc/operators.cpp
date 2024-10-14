#include "liballoc.h"  // Ensure this header has your malloc, free, and size_t defined
#include <stdio.hpp>

// Global new operator for single object allocation
void* operator new(size_t size) {
    void* p = malloc(size); // Allocate memory
    if (!p) {
        // Handle allocation failure
        klog(3, "New returned NULL, please reboot device.\n");
        // Optionally exit if desired
    }
    return p; // Return allocated memory (could be NULL)
}

// Global new operator for array allocation
void* operator new[](size_t size) {
    void* p = malloc(size); // Allocate memory for array
    if (!p) {
        // Handle allocation failure
        klog(3, "New[] returned NULL, please reboot device.\n");
        // Optionally exit if desired
    }
    return p; // Return allocated memory (could be NULL)
}

// Global delete operator for single object
void operator delete(void* ptr) noexcept {
    free(ptr); // Free the allocated memory
}

// Global delete operator for array
void operator delete[](void* ptr) noexcept {
    free(ptr); // Free the allocated memory for array
}