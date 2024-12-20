#include <stdarg.h>
#include <stdio.h>

void log(int level, const char* format, ...) {
    va_list args;
    va_start(args, format);

    // Determine the log level and print appropriately
    switch (level) {
        case DEBUG:
            printf("[DEBUG] ");
            break;
        case INFO:
            printf("[INFO] ");
            break;
        case WARNING:
            printf("[WARNING] ");
            break;
        case ERROR:
            printf("[ERROR] ");
            // Optionally handle critical error, if you want to halt the system
            // asm("cli; hlt");
            break;
        default:
            printf("[UNKNOWN] ");
            break;
    }

    // Custom string formatting
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
                    char value = (char) va_arg(args, int);  // `char` promoted to `int` in va_arg
                    printf("%c", value);
                    break;
                }
                case 's': { // String
                    const char* value = va_arg(args, const char*);
                    printf("%s", value);
                    break;
                }
                default: // If unknown format specifier, just print as-is
                    printf("%%%c", *ptr);
                    break;
            }
        } else {
            // Print regular characters
            putchar(*ptr);
        }
    }

    va_end(args);

    // New line after log
    printf("\n");
}
