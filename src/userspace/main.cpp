extern "C" void userspace_c(void) {
//    __asm__("int $0"); // Int 0 software interrupt. DPL needs to be 3
                       // in the gate descriptor for this exception
                       // to not cause a GPF
    __asm__("div %b0" :: "a"(0));
                       // This generates a real division by 0. DPL in
                       // the divbyzero exception can remain 0 for this
                       // to work
    while(1) {
    }
}
