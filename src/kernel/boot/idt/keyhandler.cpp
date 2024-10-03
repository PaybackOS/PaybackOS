#include <stdint.h>
#include "keyhandler.h"
#include <tty.hpp>
#include <stddef.h> // For NULL

// Global variable to store the last pressed key
volatile char last_key = '\0';
volatile bool shift_pressed = false; // Track shift key state
volatile bool movekey = false; // Track move key state
volatile bool key_available = false; // Indicates if a key has been pressed

// Scancode translation table (lowercase letters, numbers, and basic keys)
static char scancode_table[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8',   // 0x00 - 0x09: ESC, 1-9
    '9', '0', '-', '=', '\b',                        // 0x0A - 0x0E: 0, -, =, Backspace
    '\t',                                            // 0x0F: Tab
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', // 0x10 - 0x19: q-p
    '[', ']', '\n',                                  // 0x1A - 0x1C: [, ], Enter
    0,                                               // 0x1D: Left Ctrl (ignored)
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', // 0x1E - 0x27: a-l
    '\'', '`',                                        // 0x28 - 0x29: ', `
    0,                                               // 0x2A: Left Shift
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', // 0x2B - 0x35: z-m, , . /
    0,                                               // 0x36: Right Shift
    '*',                                             // 0x37: Keypad *
    0,                                               // 0x38: Left Alt (ignored)
    ' ',                                             // 0x39: Space
    0,                                               // 0x3A: Caps Lock (ignored)
    0, 0, 0, 0, 0, 0, 0, 0,                          // 0x3B - 0x42: (function keys ignored)
    0, 0,                                            // 0x43 - 0x44: (function keys ignored)
    0, 0, 0, 0, 0, 0, 0, 0                           // Unused keys
};

// Scancode translation table for shift (uppercase letters, symbols)
static char scancode_table_shift[128] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*',   // 0x00 - 0x09: ESC, !-*
    '(', ')', '_', '+', '\b',                        // 0x0A - 0x0E: (, ), _, +, Backspace
    '\t',                                            // 0x0F: Tab
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', // 0x10 - 0x19: Q-P
    '{', '}', '\n',                                  // 0x1A - 0x1C: {, }, Enter
    0,                                               // 0x1D: Left Ctrl (ignored)
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', // 0x1E - 0x27: A-L
    '"', '~',                                        // 0x28 - 0x29: ", ~
    0,                                               // 0x2A: Left Shift
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', // 0x2B - 0x35: Z-M, <, >, ?
    0,                                               // 0x36: Right Shift
    '*',                                             // 0x37: Keypad *
    0,                                               // 0x38: Left Alt (ignored)
    ' ',                                             // 0x39: Space
    0,                                               // 0x3A: Caps Lock (ignored)
    0, 0, 0, 0, 0, 0, 0, 0,                          // 0x3B - 0x42: (function keys ignored)
    0, 0,                                            // 0x43 - 0x44: (function keys ignored)
    0, 0, 0, 0, 0, 0, 0, 0                           // Unused keys
};

// Function to translate scancode and handle key actions
void key_translate(uint8_t scancode) {
    // Check for key release (scancode & 0x80 means key release)
    if (scancode & 0x80) {
        // Handle shift key release
        if (scancode == 0xAA || scancode == 0xB6) {
            shift_pressed = false;
        }
        return;
    }

    // Handle shift key press
    if (scancode == 0x2A || scancode == 0x36) {
        shift_pressed = true;
        return;
    }

    // Handle Backspace (scancode 0x0E)
    if (scancode == 0x0E) {
        vga::putchar('\b'); // Move cursor back
        vga::putchar(' ');  // Erase the character
        vga::putchar('\b'); // Move cursor back again
        return;
    }

    if (movekey == true) {
        if (scancode == 0x4B) {
            vga::move_cursor_left();
            movekey = false;
        }
        if (scancode == 0x4D) {
            vga::move_cursor_right();
            movekey = false;
        }
        if (scancode == 0x48) {
            vga::move_cursor_up();
            movekey = false;
        }
        if (scancode == 0x50) {
            vga::move_cursor_down();
            movekey = false;
        }
        return;
    } else {
        // Do nothing if not a movement key
    }

    // Get the correct character based on the shift state
    char key;
    if (shift_pressed) {
        key = scancode_table_shift[scancode];
    } else {
        key = scancode_table[scancode];
    }

    last_key = key;
    key_available = true; // Indicate a key has been pressed
    vga::putchar(key);
}

// Function to get a character from the keyboard
char getch() {
    while (!key_available); // Wait for a key press

    key_available = false; // Reset key availability
    return last_key; // Return the last pressed key
}
