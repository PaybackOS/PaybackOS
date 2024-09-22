#include <stddef.h>  // For size_t and NULL
#include <stdint.h>

void* memcpy(void* dest, const void* src, size_t size) {
    uint8_t* d = dest;
    const uint8_t* s = src;

    for (size_t i = 0; i < size; ++i) {
        d[i] = s[i];
    }

    return dest;
}

int memcmp(const void* dest, const void* src, size_t size) {
    const uint8_t* l = dest;
    const uint8_t* r = src;

    for (size_t i = 0; i < size; ++i) {
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
size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
void strcpy(char* dest, const char* src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}