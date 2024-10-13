#include <stdint.h>
#include "keyhandler.h"
#include <tty.hpp>
#include <port.h>
#include <stddef.h> // For NULL

volatile char last_key = '\0';
volatile bool shift_pressed = false; // Track shift key state
volatile bool movekey = false; // Track move key state
volatile bool key_available = false; // Indicates if a key has been pressed
volatile bool ctrl_pressed = false;  // Track Ctrl key state
volatile bool alt_pressed = false;   // Track Alt key state
/* keyboard interface IO port: data and control
   READ:   status port
   WRITE:  control register */
#define KBRD_INTRFC 0x64

/* keyboard interface bits */
#define KBRD_BIT_KDATA 0 /* keyboard data is in buffer (output buffer is empty) (bit 0) */
#define KBRD_BIT_UDATA 1 /* user data is in buffer (command buffer is empty) (bit 1) */

#define KBRD_IO 0x60 /* keyboard IO port */
#define KBRD_RESET 0xFE /* reset CPU command */

#define bit(n) (1<<(n)) /* Set bit n to 1 */

/* Check if bit n in flags is set */
#define check_flag(flags, n) ((flags) & bit(n))

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

void reboot() {
    uint8_t temp;

    asm volatile ("cli"); /* disable all interrupts */

    /* Clear all keyboard buffers (output and command buffers) */
    do
    {
        temp = inb(KBRD_INTRFC); /* empty user data */
        if (check_flag(temp, KBRD_BIT_KDATA) != 0)
            inb(KBRD_IO); /* empty keyboard data */
    } while (check_flag(temp, KBRD_BIT_UDATA) != 0);

    outb(KBRD_INTRFC, KBRD_RESET); /* pulse CPU reset line */
loop:
    asm volatile ("hlt"); /* if that didn't work, halt the CPU */
    goto loop; /* if a NMI is received, halt again */
}

// Function to translate scancode and handle key actions
void key_translate(uint8_t scancode) {
    // Check for key release (scancode & 0x80 means key release)
    if (scancode & 0x80) {
        uint8_t key_released = scancode & ~0x80;
        if (key_released == 0x1D) ctrl_pressed = false;   // Ctrl key release
        if (key_released == 0x38) alt_pressed = false;    // Alt key release
        if (key_released == 0xAA || key_released == 0xB6) shift_pressed = false; // Shift release
        return;
    }

    // Handle Ctrl and Alt press
    if (scancode == 0x1D) { // Left Ctrl
        ctrl_pressed = true;
        return;
    }
    if (scancode == 0x38) { // Left Alt
        alt_pressed = true;
        return;
    }

    // Handle shift key press
    if (scancode == 0x2A || scancode == 0x36) { // Left/Right Shift
        shift_pressed = true;
        return;
    }

    // Detect Ctrl + Alt + Delete combination
    if (ctrl_pressed && alt_pressed && scancode == 0x53) {
        reboot();
        return;
    }

    // Handle other keys as normal
    if (movekey == true) {
        // Handle cursor movement keys
        if (scancode == 0x4B) {
            vga::move_cursor_left();
            movekey = false;
        } else if (scancode == 0x4D) {
            vga::move_cursor_right();
            movekey = false;
        } else if (scancode == 0x48) {
            vga::move_cursor_up();
            movekey = false;
        } else if (scancode == 0x50) {
            vga::move_cursor_down();
            movekey = false;
        }
        return;
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
    vga::putchar(key);    // Display the character
}

// Function to get a character from the keyboard
char getch() {
    while (!key_available); // Wait for a key press
    key_available = false; // Reset key availability
    return last_key; // Return the last pressed key
}