#include <stddef.h> // for size_t

char* strcpy(char* dest, const char* src) {
    char* original_dest = dest; // Save the original destination pointer

    while (*src != '\0') { // Copy characters from src to dest
        *dest = *src; 
        dest++;
        src++;
    }

    *dest = '\0'; // Null-terminate the destination string
    return original_dest; // Return the original destination pointer
}