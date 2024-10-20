#include <stddef.h>
#include <string.h>

typedef struct File {
    char name[256];
    char data[1024];
    size_t size;
} File;

File files[63]; // Array at 63 since array starts at 0

void createfile(int filenumber, char filename[256], char data[1024]) {
    strcpy(files[filenumber].name, filename);
    strcpy(files[filenumber].data, data);
    return;
}