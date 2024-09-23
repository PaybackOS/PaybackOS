#include <string.h>
#include <stddef.h> // For size_t

void* memmove(void* dest, const void* src, size_t size) {
    unsigned char* d = dest;
    const unsigned char* s = src;
    
    if (d != s && ((unsigned long)d < (unsigned long)s || (unsigned long)d > (unsigned long)s + size)) {
        // Copying between overlapping regions
        for (size_t i = 0; i < size; i++) {
            d[i] = s[i];
        }
    } else {
        // No overlap or copying within same memory region
        memcpy(d, s, size);
    }
}
