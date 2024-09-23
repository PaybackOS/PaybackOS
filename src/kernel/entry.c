#include <tty.h>
#include <stdlib.h>
#include <string.h>

/*
Define the main() function for our kernel main
*/
void main();

void _init() {
    terminal_initialize();
    main();
    while(1) {
        
    }
}
