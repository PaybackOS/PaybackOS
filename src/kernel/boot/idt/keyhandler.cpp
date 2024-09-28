#include "keyhandler.h"
#include <tty.hpp>
#include <stddef.h> // For NULL

// Global variable to store the last pressed key
volatile char last_key = 0;

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
    0,                                               // 0x2A: Left Shift (ignored)
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', // 0x2B - 0x35: z-m, , . /
    0,                                               // 0x36: Right Shift (ignored)
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
    // Ignore key releases (scancode & 0x80 means key release)
    if (scancode & 0x80) {
        return;
    }

    // Get the character from the scancode table
    char key = scancode_table[scancode];

    // Only process the key if it's valid (non-zero)
    if (key) {
        if (key == '\b') {
            // Handle backspace: You can implement your backspace logic here
            vga::print("\b");
        } else {
            // Store the key in the global variable
            last_key = key;
            vga::print(&key);  // Print the valid character to the terminal
        }
    }
}

// Function to retrieve the last keypress (blocking)
char getch() {
    // Wait until a key is pressed (last_key is set by the keyboard handler)
    while (last_key == 0) {
        // Busy wait (in a real system, you might want to yield CPU time)
    }

    // Capture the key and reset last_key to 0 for the next keypress
    char key = last_key;
    last_key = 0;

    return key;
}
