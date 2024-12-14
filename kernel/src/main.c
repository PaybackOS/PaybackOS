#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limine.h>

// Function prototypes for serial
#define PORT 0x3f8          // COM1

int init_serial();
char read_serial();
void write_serial(char a);
void print_serial(char* str);
void ssfn_test(struct limine_framebuffer *framebuffer);

// Set the base revision to 3, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.
__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

// Limine framebuffer request and symbols for linking
__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// Halt function to halt execution (trap)
static void hcf(void) {
    for (;;) {
        asm ("cli; hlt");
    }
}

void kmain(void) {
    // Init the serial port for logging
    init_serial();
    print_serial("test");

    // Ensure framebuffer is valid
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        print_serial("No framebuffer available!");
        hcf();
    }

    // Fetch the first framebuffer
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
    ssfn_test(framebuffer);

    // Start SSFN test (draw the text)
    ssfn_test(framebuffer);

    // End of the test, just hang.
    hcf();
}
