char* strcpy(char* dest, const char* src) {
    char* original_dest = dest; // Store the original destination pointer

    // Copy characters from source to destination
    while (*src != '\0') {       // Continue until we reach the null terminator
        *dest = *src;           // Copy character
        dest++;                  // Move to the next position in dest
        src++;                   // Move to the next character in src
    }

    *dest = '\0';                // Add null terminator to the end of dest

    return original_dest;        // Return the original destination pointer
}
