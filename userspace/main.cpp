#include <stdio.hpp>
#include <string.h>
#include <pid.hpp>
#include <stdbool.h>
#include <string.h> // For strcmp

struct debug {
    bool debug; // General debugging, testing memory managment and so on
    bool fulldebug; // Extension of debug, used to test stuff like a GPF.
};

void kshell() {
    char command[256];  // Buffer for user input
    int index;          // Index for the command buffer

    print("Welcome to KSHELL! Type 'exit' to quit.\n");

    while (1) {
        print("> ");  // Prompt for input
        index = 0;    // Reset index for each command

        // Read characters until Enter is pressed
        while (1) {
            char c = getch();  // Get a single character from the keyboard

            // Check for Enter key (assuming '\n' indicates end of input)
            if (c == '\n') {
                command[index] = '\0';  // Null-terminate the string
                break;  // Exit the input loop
            }

            // Check for backspace (assuming 8 is backspace)
            if (c == 8) {
                if (index > 0) {
                    index--;  // Remove the last character from command
                    // Optionally, you can print a space and the prompt again
                    putchar('\b'); // Print backspace
                    putchar(' ');   // Print space to clear the last character
                    putchar('\b');   // Move back again
                }
            } else {
                // Add character to command buffer if there's space
                if (index < sizeof(command) - 1) {
                    command[index++] = c; // Store character
                    putchar(c);         // Echo the character back
                }
            }
        }

        // Check for the "exit" command
        if (strcmp(command, "exit") == 0) {
            print("Exiting KSHELL...\n");
            break;  // Exit the shell
        }

        // Print the entered command (for demonstration purposes)
        print("You entered: ");
        print(command);
        print("\n");
    }
}

extern "C" void userspace_c(void) {
    init_pid_manager(); // Start the PID managment system
    create_pid(0); // Create the userspace PID
    debug debuginfo;
    // Set the debugging flags
    debuginfo.debug = true; // General debugging
    debuginfo.fulldebug = false; // Enable for testing new features for crash prevention and such
    if (debuginfo.debug) {
        char* debugstuff = new char[25];
        strcpy(debugstuff, "Userspace mem alloc test");
        print(debugstuff);
        delete[] debugstuff;
    }
    if (debuginfo.fulldebug) {
        // Test our stack trace
        klog(1, "Testing stack tracing, this GPF is designed to happen.\n");
        asm("cli"); // Trigger stack trace from calling a command that is priviledged.
    }
    kshell(); // Start our debugging shell
    delete_pid(0); // Shut down the userspace since it is no longer active
    while(true) {
        
    }
}
