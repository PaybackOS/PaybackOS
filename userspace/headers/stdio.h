#ifndef STDIO_H
#define STDIO_H

#include <stdbool.h>
#include <stdint.h>

// Print a string to the user space
void user_print(const char* str);

// Write a character to the user space
void user_putchar(char c);

// Log a message with a specific log level
void log(int level, const char* log);

// Halt the system
void halt(void);

// Check if debug mode is active
bool checkdebug(void);

// Formatted printing
void printf(const char* format, ...);

uint8_t get_scancode();

#endif
