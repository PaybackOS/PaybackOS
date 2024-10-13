#include <stdio.hpp>
#include <stdarg.h>

void print_integer(int num) {
    if (num < 0) {
        putchar('-'); // Print the negative sign for negative numbers
        num = -num;   // Convert to positive for further processing
    }
    if (num / 10) {
        print_integer(num / 10); // Recursive call for higher digits
    }
    putchar(num % 10 + '0'); // Print the last digit
}

void printf(const char* format, ...) {
    va_list args; // Variable argument list
    va_start(args, format); // Initialize args to retrieve additional arguments

    while (*format) { // Iterate through the format string
        if (*format == '%') { // Check for format specifier
            format++; // Move to the next character

            switch (*format) {
                case 'c': { // Handle character
                    char c = (char)va_arg(args, int); // Retrieve argument as char
                    putchar(c); // Print character
                    break;
                }
                case 's': { // Handle string
                    const char* str = va_arg(args, const char*); // Retrieve string argument
                    while (*str) {
                        putchar(*str++); // Print each character in the string
                    }
                    break;
                }
                case 'd': { // Handle integer
                    int num = va_arg(args, int); // Retrieve integer argument
                    print_integer(num); // Call function to print integer
                    break;
                }
                case '%': { // Handle literal '%' character
                    putchar('%');
                    break;
                }
                default:
                    break; // Ignore unrecognized format specifiers
            }
        } else {
            putchar(*format); // Print regular characters
        }
        format++; // Move to the next character in the format string
    }

    va_end(args); // Clean up the variable argument list
}
