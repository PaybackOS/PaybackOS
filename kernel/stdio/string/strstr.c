#include <stddef.h> // For size_t definition

char* strstr(const char* haystack, const char* needle) {
    // Check for empty needle
    if (!*needle) {
        return (char*)haystack; // Return the original string if needle is empty
    }

    for (; *haystack; haystack++) {
        const char* h = haystack;
        const char* n = needle;

        // Check for the substring match
        while (*h && *n && (*h == *n)) {
            h++;
            n++;
        }

        // If we reached the end of needle, a match was found
        if (!*n) {
            return (char*)haystack; // Found the needle
        }
    }

    return NULL; // Needle not found
}
