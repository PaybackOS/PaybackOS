#include <stdio.h>

void userspace_init(void) {
    if (user_checkdebug() == true) {
        user_klog(1, "This is a message from the userspace");
    }
    while (1);
}
