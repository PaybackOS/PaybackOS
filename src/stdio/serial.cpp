#include <port.h>
#include <stdarg.h>

#define PORT 0x3f8          // COM1

namespace serial {
    int init_serial() {
       outb(PORT + 1, 0x00);    // Disable all interrupts
       outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
       outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
       outb(PORT + 1, 0x00);    //                  (hi byte)
       outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
       outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
       outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
       outb(PORT + 4, 0x1E);    // Set in loopback mode, test the serial chip
       outb(PORT + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

       // Check if serial is faulty (i.e: not same byte as sent)
       if(inb(PORT + 0) != 0xAE) {
          return 1;
       }

       // If serial is not faulty set it in normal operation mode
       // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
       outb(PORT + 4, 0x0F);
       return 0;
    }

    int is_transmit_empty() {
       return inb(PORT + 5) & 0x20;
    }

    void putchar(char a) {
       while (is_transmit_empty() == 0);

       outb(PORT,a);
    }
    
    void print(const char* str) {
        while (*str != '\0') {
            putchar(*str);
            str++;
        }
    }
    // Helper function to print an integer in base 10
    void print_int(int num) {
        if (num < 0) {
            putchar('-');
            num = -num;
        }

        if (num == 0) {
            putchar('0');
            return;
        }

        char buffer[10]; // Enough for 32-bit integer
        int i = 0;

        // Convert the number to string
        while (num > 0) {
            buffer[i++] = '0' + (num % 10);
            num /= 10;
        }

        // Print the number in reverse
        while (i > 0) {
            putchar(buffer[--i]);
        }
    }

    // The actual printf function for serial output
    void printf(const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);

        for (const char *p = fmt; *p != '\0'; p++) {
            if (*p == '%') {
                p++;  // Move past '%'
                switch (*p) {
                    case 'c': {
                        char c = (char) va_arg(args, int);
                        putchar(c);
                        break;
                    }
                    case 's': {
                        const char *str = va_arg(args, const char *);
                        print(str);
                        break;
                    }
                    case 'd': {
                        int num = va_arg(args, int);
                        print_int(num);
                        break;
                    }
                    case 'x': {
                        unsigned int num = va_arg(args, unsigned int);
                        print("0x");
                        print_int(num); // Using print_int to display hex as decimal for now
                        break;
                    }
                    default: {
                        // If unknown format specifier, just print it as-is
                        putchar('%');
                        putchar(*p);
                        break;
                    }
                }
            } else {
                putchar(*p);  // Just print regular characters
            }
        }

        va_end(args);
    }
}