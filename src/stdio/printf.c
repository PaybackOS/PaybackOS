#include <stdarg.h>
#include <stdbool.h>
#include <tty.h>

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
