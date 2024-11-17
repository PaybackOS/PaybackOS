#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <tty.h>
#include <string.h>

void execute_command(char *input);

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LSHIFT 0x2A
#define RSHIFT 0x36
#define MAX_KEYS 256

static char key_buffer[256];
bool shell_enabled = false;
bool shift_pressed = false;  // To track if Shift key is held down

#define SC_MAX 57

const char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};

const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

// Shifted character mapping (same index as sc_ascii)
const char sc_ascii_shift[] = {'?', '?', '!', '@', '#', '$', '%', '^',
                               '&', '*', '(', ')', '_', '+', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                               'U', 'I', 'O', 'P', '{', '}', '?', '?', 'A', 'S', 'D', 'F', 'G',
                               'H', 'J', 'K', 'L', ':', '"', '~', '?', '|', 'Z', 'X', 'C', 'V',
                               'B', 'N', 'M', '<', '>', '?', '?', '?', ' '};

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len + 1] = '\0';
}

void key_translate(uint8_t scancode) {
    if (scancode > SC_MAX) return;

    // Detect Shift key press/release
    if (scancode == LSHIFT || scancode == RSHIFT) {
        shift_pressed = true;  // Shift key is pressed
    } else if (scancode == BACKSPACE) {
        kprintf("\b");
    } else if (scancode == ENTER) {
        putchar('\n');
    } else {
        char letter;

        // Determine if Shift is pressed and use the correct mapping
        if (shift_pressed) {
            letter = sc_ascii_shift[scancode];  // Use shifted character
            shift_pressed = false;  // Reset shift state (Shift is a toggle, so reset after each key press)
        } else {
            letter = sc_ascii[scancode];  // Use normal character
        }

        append(key_buffer, letter);
        char str[2] = {letter, '\0'};
        print(str);
    }
}
