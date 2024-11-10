#ifndef STDIO_H
#define STDIO_H

#include <stddef.h>
#include <stdbool.h>

// Print a string to the user space
void user_print(const char* str);

// Write a character to the user space
void user_putchar(char c);

// Log a message with a specific log level
void user_klog(int level, const char* log);

// Halt the system
void user_halt(void);

// Check if debug mode is active
bool user_checkdebug(void);

#endif
