#include <stdio.hpp>
#include <string.hpp>

struct File {
    char filename[257]; // Correct array syntax
    int size; // The size of the file
    const char* content; // Use const char* for the content
};

// Define an array of File structs
struct File filesystem[] = {
    {"Test.txt", 5, "hi!\n"},               // Directly use const char*
};

// Function to find and read a file from the filesystem array
void readfile(const char* name) {
    for (const auto& file : filesystem) {
        if (strcmp(file.filename, name)) { // Use custom string comparison
            print("Reading file: ");           // Print a message
            print(file.filename);               // Print the filename
            print("\nContent: ");                 // Print content label
            print(file.content);                // Print the content
            return; // Exit the function after reading
        }
    }
    print("File not found: ");                // Print file not found message
    print(name);                              // Print the name of the missing file
}
