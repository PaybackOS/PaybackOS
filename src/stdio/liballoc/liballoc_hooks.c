/*
This code is not from liballoc; it is for liballoc to use
*/
#include <stddef.h>
#include <stdint.h>

#define PAGE_SIZE 4096  // Define the size of a memory page
#define HEAP_SIZE (PAGE_SIZE * 10)  // Total heap size (10 pages)
#define ALIGNMENT 8  // Align to 8 bytes

typedef struct Block {
    size_t size;  // Size of the block
    struct Block* next;  // Pointer to the next free block
} Block;

// Memory pool
static uint8_t heap[HEAP_SIZE];  
// Head of the free list, initialized statically
static Block* free_list = (Block*)heap; 

// Automatically set up the free list at the start
static void setup_free_list() {
    free_list->size = HEAP_SIZE - sizeof(Block);
    free_list->next = NULL;
}

static int spinlock = 0;

int liballoc_lock() {
    if (spinlock == 1) {
        return 1;  // Lock already acquired
    } 
    spinlock = 1;  // Acquire lock
    return 0;  // Lock acquired successfully
}

int liballoc_unlock() {
    if (spinlock == 1) {
        spinlock = 0;  // Release lock
        return 0;  // Lock released successfully
    }
    return 1;  // Lock was not held
}

// First call to liballoc_alloc will trigger the setup
void* liballoc_alloc(int size) {
    // Ensure the free list is set up only once
    static int initialized = 0;
    if (!initialized) {
        setup_free_list();
        initialized = 1;
    }

    // Align the size
    size = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
    
    Block* current = free_list;
    Block* previous = NULL;

    // Traverse the free list to find a suitable block
    while (current) {
        if (current->size >= (size_t)size) {  // Cast size to size_t for comparison
            // Found a suitable block
            if (current->size >= size + sizeof(Block) + ALIGNMENT) {
                // Split the block if it's larger than needed
                Block* next_block = (Block*)((uint8_t*)current + sizeof(Block) + size);
                next_block->size = current->size - size - sizeof(Block);
                next_block->next = current->next;
                
                current->size = size;
                current->next = next_block;
            } else {
                // Use the whole block
                if (previous) {
                    previous->next = current->next;  // Remove from free list
                } else {
                    free_list = current->next;  // Move head of free list
                }
            }
            return (uint8_t*)current + sizeof(Block);  // Return pointer to the allocated memory
        }
        previous = current;
        current = current->next;
    }
    return NULL;  // No suitable block found
}

void liballoc_free(void* ptr) {
    if (!ptr) return;  // NULL pointer check
    
    Block* block_to_free = (Block*)((uint8_t*)ptr - sizeof(Block));
    
    // Add block back to the free list
    block_to_free->next = free_list;
    free_list = block_to_free;
}
