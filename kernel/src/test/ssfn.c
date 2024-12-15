#define SSFN_CONSOLEBITMAP_TRUECOLOR  /* use the special renderer for 32-bit truecolor packed pixels */

#include <ssfn.h>
#include <limine.h>

/* Declare the font binary object; it must be linked into the binary */
extern unsigned char _binary_src_console_sfn_start;

/* Set up the SSFN context, using a pointer to the framebuffer */
void ssfn_setup(struct limine_framebuffer *framebuffer) {
    /* Initialize the SSFN font rendering context using the linked-in bitmap font */
    ssfn_src = (ssfn_font_t *)&_binary_src_console_sfn_start;  /* Correctly cast to ssfn_font_t * */

    /* Configure the destination frame buffer for rendering */
    ssfn_dst.ptr = (void *)framebuffer->address;  /* Address of the linear framebuffer */
    ssfn_dst.w = framebuffer->width;               /* Screen width in pixels (from framebuffer) */
    ssfn_dst.h = framebuffer->height;              /* Screen height in pixels (from framebuffer) */
    ssfn_dst.p = framebuffer->pitch;               /* Bytes per line (pitch) (from framebuffer) */
    ssfn_dst.x = 0;                                /* Initial X-coordinate of the pen */
    ssfn_dst.y = 0;                                /* Initial Y-coordinate of the pen */
    ssfn_dst.fg = 0xFFFFFF;                        /* Set default foreground color to white */
}

/* Function to render a test string on the screen */
void ssfn_test(struct limine_framebuffer *framebuffer) {
    ssfn_setup(framebuffer); // Call ssfn_setup to initialize framebuffer settings

    /* Render each character directly using SSFN's simple rendering function */
    const char *test_string = "Hello, SSFN!";
    const char *ptr = test_string;

    /* Render characters and adjust pen position automatically */
    while (*ptr) {
        ssfn_putc(*ptr++);  // Render character and advance pen position
    }
    while(1) {
        
    }
}