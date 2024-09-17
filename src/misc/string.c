#include <stddef.h>  // For size_t and NULL

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
