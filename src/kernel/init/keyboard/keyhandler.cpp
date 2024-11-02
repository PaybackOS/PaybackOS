// Code taken and modified from Frank Rosner on dev.to (https://dev.to/frosnerd/writing-my-own-shell-1a7p)
#include <stdbool.h>
#include <stdint.h>
#include <stdio.hpp>
#include <tty.hpp>
#include <string.h>

void execute_command(char *input);

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];
bool welcome = false;

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

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len + 1] = '\0';
}

void key_translate(uint8_t scancode) {
    if (!welcome) {
        kprintf("Welcome to the debug shell type 'help' for help\n> ");
        welcome = true;
    }
    if (scancode > SC_MAX) return;

    if (scancode == BACKSPACE) {
        // Remove the last character from the buffer
        size_t len = strlen(key_buffer);
        if (len > 0) {
            key_buffer[len - 1] = '\0'; // Remove last character
            vga::putchar('\b'); // Move cursor back
            vga::putchar(' ');   // Overwrite with space
            vga::putchar('\b');  // Move cursor back again
        }
    } else if (scancode == ENTER) {
        vga::putchar('\n');
        execute_command(key_buffer);
        key_buffer[0] = '\0'; // Clear the buffer
    } else {
        char letter = sc_ascii[(int) scancode];
        append(key_buffer, letter); // Add character to the buffer
        char str[2] = {letter, '\0'};
        vga::print(str); // Print the character to the screen
    }
}