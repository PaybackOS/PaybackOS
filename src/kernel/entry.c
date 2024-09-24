#include <tty.h>
#include <stdlib.h>
#include <string.h>

// The main function of our kernel
void main();

// Define our init function for our kernel
void _init() {
    terminal_initialize();
    main();
    while(1) {
        
    }
}
