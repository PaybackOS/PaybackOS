#include <stdarg.h>
#include <stdbool.h>
#include <tty.h>

void hex_print(unsigned int num) {
    const char hex_chars[] = "0123456789ABCDEF";
    char buffer[9];  // Enough to hold "0x" + 8 hex digits + null terminator
    int i = 0;

    // Start with "0x"
    buffer[i++] = '0';
    buffer[i++] = 'x';

    // Convert the number to hex and store in buffer
    for (int shift = 28; shift >= 0; shift -= 4) {
        char hex_digit = hex_chars[(num >> shift) & 0xF];
        if (i > 2 || hex_digit != '0') {  // Skip leading zeros
            buffer[i++] = hex_digit;
        }
    }

    // Null-terminate the buffer
    buffer[i] = '\0';

    // Use print from tty.h to output the string
    print(buffer);
}

void printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'c': {
                    char c = (char)va_arg(args, int);
                    putchar(c);
                    break;
                }
                case 's': {
                    char *str = va_arg(args, char*);
                    print(str);
                    break;
                }
                case 'd': {
                    int num = va_arg(args, int);
                    char buffer[10];
                    int i = 0;
                    bool negative = false;

                    if (num < 0) {
                        negative = true;
                        num = -num;
                    }

                    do {
                        buffer[i++] = (num % 10) + '0';
                        num /= 10;
                    } while (num > 0);

                    if (negative) {
                        putchar('-');
                    }

                    while (i-- > 0) {
                        putchar(buffer[i]);
                    }
                    break;
                }
                case 'x': {
                    unsigned int num = va_arg(args, unsigned int);
                    hex_print(num);
                    break;
                }
                default:
                    // Handle unknown format specifiers
                    putchar('%');
                    putchar(*format);
                    break;
            }
        } else {
            putchar(*format);
        }
        format++;
    }

    va_end(args);
}