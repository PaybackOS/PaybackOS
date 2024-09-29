#include <string.h>
#include <stddef.h>
#include <port.h>
#include <stdint.h>

/* Hardware text mode color constants. */
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | (uint16_t)color << 8;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void update_cursor(int x, int y) {
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*)0xB8000;
    update_cursor(terminal_column, terminal_row);
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

namespace vga {
    void terminal_setcolor(uint8_t color) {
        terminal_color = color;
    }

    void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
        const size_t index = y * VGA_WIDTH + x;
        terminal_buffer[index] = vga_entry(c, color);
    }

    // Function to handle scrolling
    void terminal_scroll() {
        // Move all lines one row up
        memmove(terminal_buffer, terminal_buffer + VGA_WIDTH, (VGA_HEIGHT - 1) * VGA_WIDTH * sizeof(uint16_t));

        // Clear the last line
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }

        // Move cursor to the last row
        terminal_row = VGA_HEIGHT - 1;
        terminal_column = 0;
        update_cursor(terminal_column, terminal_row);
    }

    void putchar(char c) {
        if (c == '\n') {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT) {
                terminal_scroll();
            }
        } else if (c == '\b') {
            if (terminal_column > 0) {
                --terminal_column; // Move cursor back
            } else if (terminal_row > 0) {
                --terminal_row; // Move to the end of the previous line
                terminal_column = VGA_WIDTH - 1;
            }
            terminal_putentryat(' ', terminal_color, terminal_column, terminal_row); // Erase character
            update_cursor(terminal_column, terminal_row); // Update cursor position
        } else {
            terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
            if (++terminal_column == VGA_WIDTH) {
                terminal_column = 0;
                if (++terminal_row == VGA_HEIGHT) {
                    terminal_scroll();
                }
            }
        }
        update_cursor(terminal_column, terminal_row);
    }

    void terminal_write(const char* data, size_t size) {
        for (size_t i = 0; i < size; i++) {
            putchar(data[i]);
        }
    }

    void print(const char* data) {
        while (*data != '\0') {
            putchar(*data);
            data++;
        }
    }
    void move_cursor_up() {
        if (terminal_row > 0) {
            terminal_row--;
            update_cursor(terminal_column, terminal_row);
        }
    }

    void move_cursor_down() {
        if (terminal_row < VGA_HEIGHT - 1) {
            terminal_row++;
            update_cursor(terminal_column, terminal_row);
        }
    }

    void move_cursor_left() {
        if (terminal_column > 0) {
            terminal_column--;
        } else if (terminal_row > 0) {
            terminal_row--;
            terminal_column = VGA_WIDTH - 1;
        }
        update_cursor(terminal_column, terminal_row);
    }

    void move_cursor_right() {
        if (terminal_column < VGA_WIDTH - 1) {
            terminal_column++;
        } else if (terminal_row < VGA_HEIGHT - 1) {
            terminal_column = 0;
            terminal_row++;
        }
        update_cursor(terminal_column, terminal_row);
    }
}
