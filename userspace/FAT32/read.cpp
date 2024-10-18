#include <stdint.h>
#include <string.hpp>
#include <stdio.hpp>
#include <stddef.h>

#define SECTOR_SIZE 512
#define FAT32_MAX_FILENAME 12

// BIOS Parameter Block structure
typedef struct {
    uint8_t jump[3];
    char filesystem_name[8];
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t num_fats;
    uint16_t max_root_dir_entries;
    uint16_t total_sectors_16;
    uint8_t media_descriptor;
    uint16_t fat_size_16;
    uint16_t sectors_per_track;
    uint16_t number_of_heads;
    uint32_t hidden_sectors;
    uint32_t total_sectors_32;
    uint32_t fat_size_32;
    uint16_t extended_flags;
    uint16_t version;
    uint32_t root_cluster;
    uint16_t fsinfo_sector;
    uint16_t backup_boot_sector;
    uint8_t reserved[12];
    uint8_t drive_number;
    uint8_t reserved1;
    uint8_t boot_signature;
    uint32_t volume_id;
    char volume_label[11];
    char filesystem_type[8];
} __attribute__((packed)) FAT32_BPB;

FAT32_BPB bpb;
uint32_t first_data_sector;
uint32_t fat_start_sector;
uint32_t root_dir_start_sector;

// Function to read sectors using readisk
void read_sectors(uint32_t lba, uint16_t count, void* buffer) {
    readisk(lba, count);
}

// Function to read the BPB
void read_bpb() {
    read_sectors(0, 1, &bpb);
    first_data_sector = bpb.reserved_sectors + (bpb.num_fats * bpb.fat_size_32);
    fat_start_sector = bpb.reserved_sectors;
    root_dir_start_sector = first_data_sector + ((bpb.root_cluster - 2) * bpb.sectors_per_cluster);
}

// FAT32 directory entry structure
typedef struct {
    char filename[FAT32_MAX_FILENAME];
    uint8_t attributes;
    uint8_t reserved[10];
    uint16_t time;
    uint16_t date;
    uint16_t first_cluster_high;
    uint32_t file_size;
    uint16_t first_cluster_low;
} __attribute__((packed)) FAT32_DirectoryEntry;

// Function to read a file by name
int read_file(const char* filename, uint8_t* buffer, size_t buffer_size) {
    FAT32_DirectoryEntry dir_entry;
    uint32_t sector = root_dir_start_sector;

    for (uint32_t i = 0; i < bpb.max_root_dir_entries; i++) {
        read_sectors(sector, 1, &dir_entry);
        
        if (strcmp(dir_entry.filename, filename) == 0) {
            // Here you would typically handle reading clusters
            // For simplicity, just return success
            return 0;  // Success
        }
        sector++;
    }

    return -1;  // File not found
}
