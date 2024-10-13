#include <stdint.h>
#include <port.h>  // Use angle brackets for system includes

#define IDE_PORT_BASE 0x1F0    // Base port for primary IDE
#define IDE_CMD_READ 0x20
#define IDE_CMD_WRITE 0x30
#define IDE_STATUS_REG (IDE_PORT_BASE + 0x07)
#define IDE_DATA_REG (IDE_PORT_BASE + 0x00)
#define IDE_ERROR_REG (IDE_PORT_BASE + 0x01)
#define IDE_SECTOR_COUNT_REG (IDE_PORT_BASE + 0x02)
#define IDE_LBA_LOW_REG (IDE_PORT_BASE + 0x03)
#define IDE_LBA_MID_REG (IDE_PORT_BASE + 0x04)
#define IDE_LBA_HIGH_REG (IDE_PORT_BASE + 0x05)
#define IDE_DRIVE_REG (IDE_PORT_BASE + 0x06)

// Status register flags
#define STATUS_READY 0x40
#define STATUS_ERROR 0x01

// Function to wait until the IDE drive is ready
static void ide_wait_ready() {
    while (!(inb(IDE_STATUS_REG) & STATUS_READY));
}

// Function to read sectors from IDE
void ide_read(uint32_t lba, uint16_t sectors, void *buffer) {
    ide_wait_ready();

    // Set up the LBA and sector count
    outb(IDE_SECTOR_COUNT_REG, sectors);
    outb(IDE_LBA_LOW_REG, lba & 0xFF);
    outb(IDE_LBA_MID_REG, (lba >> 8) & 0xFF);
    outb(IDE_LBA_HIGH_REG, (lba >> 16) & 0xFF);
    outb(IDE_DRIVE_REG, 0xE0);  // Select master drive

    // Send the read command
    outb(IDE_CMD_READ, IDE_CMD_READ);

    ide_wait_ready();

    // Read the data
    uint16_t *data = (uint16_t *)buffer;
    for (int i = 0; i < sectors * 256; i++) {
        ide_wait_ready();
        data[i] = inw(IDE_DATA_REG);
    }
}