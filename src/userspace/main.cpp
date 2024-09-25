extern "C" void userspace_c(void) {
    // Enable interrupts again
    asm("sti");
    
    // Example: Trigger a divide by zero exception
    volatile int a = 1;
    volatile int b = 0;
    volatile int c = a / b; // This will trigger a divide by zero exception
}
