#include <stdint.h>
#include <port.h>

#define PIC_COMMAND_PORT_MASTER   0x0020
#define PIC_DATA_PORT_MASTER     0x0021
#define PIC_COMMAND_PORT_SLAVE   0x00A0
#define PIC_DATA_PORT_SLAVE     0x00A1

#define ICW1_INIT         0x11      // Start initialization
#define ICW4_8086          0x01      // ICW4: Only support 8086/IA32 mode

// Define constants for IRQ offsets
#define IRQ_OFFSET_MASTER     0x08
#define IRQ_OFFSET_SLAVE      0x70

// Define ICW4 constant
#define ICW4_8086             0x01

void PIC_init(void) {
    // Initialize master PIC
    outb(PIC_COMMAND_PORT_MASTER, ICW1_INIT);
    io_wait();
    
    outb(PIC_DATA_PORT_MASTER, IRQ_OFFSET_MASTER);
    io_wait();
    
    outb(PIC_DATA_PORT_MASTER, 0x04); // Cascade slave PIC
    io_wait();
    
    outb(PIC_DATA_PORT_MASTER, ICW4_8086);
    io_wait();

    // Initialize slave PIC
    outb(PIC_COMMAND_PORT_SLAVE, ICW1_INIT);
    io_wait();
    
    outb(PIC_DATA_PORT_SLAVE, IRQ_OFFSET_SLAVE);
    io_wait();
    
    outb(PIC_DATA_PORT_SLAVE, 0x02); // Cascade to master PIC
    io_wait();
    
    outb(PIC_DATA_PORT_SLAVE, ICW4_8086);
    io_wait();

    // Mask off all interrupts
    outb(PIC_DATA_PORT_MASTER, 0xFF);
    outb(PIC_DATA_PORT_SLAVE, 0xFF);

    // Small delay to ensure proper timing
    for (volatile int i = 0; i < 100000; i++) {}
}
