#include <stdarg.h>
#include "headers/print.h"

void printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    for (size_t i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            i++;

            switch (format[i]) {
                case 'c': { // Character
                    char c = (char)va_arg(args, int);
                    putchar(c);
                    break;
                }
                case 's': { // String
                    char* s = va_arg(args, char*);
                    print_str(s);
                    break;
                }
                case 'd': { // Integer
                    int num = va_arg(args, int);
                    char buffer[32];
                    int is_negative = num < 0;

                    if (is_negative) {
                        num = -num;
                        putchar('-');
                    }

                    size_t pos = 0;
                    do {
                        buffer[pos++] = (char)('0' + (num % 10));
                        num /= 10;
                    } while (num > 0);

                    for (size_t j = 0; j < pos; j++) {
                        putchar(buffer[pos - j - 1]);
                    }

                    break;
                }
                case 'x': { // Hexadecimal
                    unsigned int num = va_arg(args, unsigned int);
                    char buffer[32];
                    const char* hex_chars = "0123456789abcdef";

                    size_t pos = 0;
                    do {
                        buffer[pos++] = hex_chars[num % 16];
                        num /= 16;
                    } while (num > 0);

                    for (size_t j = 0; j < pos; j++) {
                        putchar(buffer[pos - j - 1]);
                    }

                    break;
                }
                case '%': {
                    putchar('%');
                    break;
                }
                default: {
                    putchar('%');
                    putchar(format[i]);
                    break;
                }
            }
        } else {
            putchar(format[i]);
        }
    }

    va_end(args);
}
