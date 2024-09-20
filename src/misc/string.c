#include <stddef.h>  // For size_t and NULL
#include <stdint.h>

void* memcpy(void* dest, const void* src, size_t n) {
    uint8_t* d = dest;
    const uint8_t* s = src;

    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }

    return dest;
}

int memcmp(const void* lhs, const void* rhs, size_t n) {
    const uint8_t* l = lhs;
    const uint8_t* r = rhs;

    for (size_t i = 0; i < n; ++i) {
        if (l[i] != r[i]) {
            return (int)(l[i] - r[i]);
        }
    }

    return 0;
}

char *strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return (char *)haystack;  // If needle is empty, return the haystack
    }

    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;

        // Check if the substring starting at haystack matches needle
        while (*h && *n && *h == *n) {
            ++h;
            ++n;
        }

        // If we reached the end of needle, we found a match
        if (*n == '\0') {
            return (char *)haystack;
        }

        ++haystack;  // Move to the next position in haystack
    }

    return NULL;  // No match found
}
