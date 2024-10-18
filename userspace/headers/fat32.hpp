#ifndef FAT32_HPP
#define FAT32_HPP
#pragma once

#include <stdint.h>
#include <stddef.h>

#define SECTOR_SIZE 512

// Function to read a file by name
int read_file(const char* filename, uint8_t* buffer, size_t buffer_size);
// Function to read the BPB
void read_bpb();

#endif