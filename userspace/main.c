#include <stdio.h>
#include <stdbool.h>

void userspace_init(void) {
    if (checkdebug() == true) {
        log(1, "This is a message from the userspace");
    }
    while (1);
}
