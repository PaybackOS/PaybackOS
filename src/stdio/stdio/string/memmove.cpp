#include <stddef.h>

void* memmove(void* dest, const void* src, size_t n) {
    // Convert pointers to char pointers for byte-wise copying
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    // Check for overlap and copy accordingly
    if (d < s) {
        // Non-overlapping or destination is before source
        while (n--) {
            *d++ = *s++;
        }
    } else if (d > s) {
        // Overlapping case: copy from the end to avoid corruption
        d += n;
        s += n;
        while (n--) {
            *(--d) = *(--s);
        }
    }

    // Return the destination pointer
    return dest;
}