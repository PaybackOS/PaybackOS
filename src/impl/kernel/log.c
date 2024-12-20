#include <stdarg.h>
#include <stdio.h>

// Log level names
static const char* LOG_LEVELS[] = {
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR"
};

#define NUM_LOG_LEVELS (sizeof(LOG_LEVELS) / sizeof(LOG_LEVELS[0]))

void log(int level, const char* format, ...) {
    if (level < 0 || level >= NUM_LOG_LEVELS) {
        // Invalid log level, treat as ERROR
        level = NUM_LOG_LEVELS - 1;
    }

    // Print log level
    printf("[%s] ", LOG_LEVELS[level]);

    va_list args;
    va_start(args, format);

    // Process format string
    for (const char* ptr = format; *ptr != '\0'; ++ptr) {
        if (*ptr == '%' && *(ptr + 1) != '\0') {
            ++ptr;
            switch (*ptr) {
                case 'd': { // Integer
                    int value = va_arg(args, int);
                    printf("%d", value);
                    break;
                }
                case 'c': { // Character
                    char value = (char)va_arg(args, int);
                    printf("%c", value);
                    break;
                }
                case 's': { // String
                    const char* value = va_arg(args, const char*);
                    printf("%s", value);
                    break;
                }
                case 'x': { // Hexadecimal
                    int value = va_arg(args, int);
                    printf("%x", value);
                    break;
                }
                default: // Unknown format specifier, print as-is
                    printf("%%%c", *ptr);
                    break;
            }
        } else {
            // Print regular character
            putchar(*ptr);
        }
    }

    va_end(args);

    // Newline at the end of the log
    putchar('\n');
}