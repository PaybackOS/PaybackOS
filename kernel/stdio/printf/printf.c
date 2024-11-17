#include <tty.h>
#include <stdarg.h>

// Helper function to print an integer in base 10
void kprint_int(int num) {
    char buffer[10];  // Enough for a 32-bit int
    int i = 0;

    // Handle negative numbers
    if (num < 0) {
        kputchar('-');
        num = -num;
    }

    // Convert the number to string
    if (num == 0) {
        kputchar('0');
        return;
    }

    while (num > 0) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }

    // Print the number in reverse
    while (i > 0) {
        kputchar(buffer[--i]);
    }
}

// Helper function to print an integer in hexadecimal
void kprint_hex(unsigned int num) {
    char hex_digits[] = "0123456789ABCDEF";
    char buffer[8];  // Enough for a 32-bit int in hexadecimal
    int i = 0;

    if (num == 0) {
        kputchar('0');
        return;
    }

    // Convert the number to hexadecimal string
    while (num > 0) {
        buffer[i++] = hex_digits[num % 16];
        num /= 16;
    }

    // Print the hex number in reverse
    while (i > 0) {
        kputchar(buffer[--i]);
    }
}

// The actual kprintf function
void kprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    for (const char *p = fmt; *p != '\0'; p++) {
        if (*p == '%') {
            p++;  // Move past '%'
            switch (*p) {
                case 'c': {
                    char c = (char) va_arg(args, int);
                    kputchar(c);
                    break;
                }
                case 's': {
                    const char *str = va_arg(args, const char *);
                    print(str);
                    break;
                }
                case 'd': {
                    int num = va_arg(args, int);
                    kprint_int(num);
                    break;
                }
                case 'x': {
                    unsigned int num = va_arg(args, unsigned int);
                    print("0x");
                    kprint_hex(num);
                    break;
                }
                default: {
                    // If unknown format specifier, just print it as-is
                    kputchar('%');
                    kputchar(*p);
                    break;
                }
            }
        } else {
            kputchar(*p);  // Just print regular characters
        }
    }

    va_end(args);
}
