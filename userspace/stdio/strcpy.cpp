char* strcpy(char* dest, const char* src) {
    char* original_dest = dest;  // Keep the original pointer to return later

    while (*src) {
        *dest = *src;  // Copy each character from src to dest
        dest++;
        src++;
    }

    *dest = '\0';  // Add the null terminator at the end

    return original_dest;  // Return the destination pointer
}
