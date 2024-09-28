#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include <stdint.h>

// Function to translate scancode into characters
void key_translate(uint8_t scancode);
char getch();
#endif
