#include <stddef.h>  // for size_t
#include <stdint.h>  // For uint8_t etc.

// Memory block structure to manage allocation metadata
struct Block {
    size_t size;         // Size of the allocated block
    int free;            // 1 if block is free, 0 if allocated
    struct Block* next;  // Pointer to the next block in the free list
};

#define BLOCK_SIZE sizeof(struct Block)  // Size of the block metadata
#define HEAP_SIZE 1024 * 1024            // 1 MB heap size (can be adjusted as needed)

static struct Block* free_list = NULL;  // Free block list head
static void* heap_start = NULL;         // Starting point of the heap
static void* heap_end = NULL;           // End of the heap memory

// Simulated heap memory (statically allocated)
static uint8_t heap_memory[HEAP_SIZE];

// Simulate sbrk function to provide heap space
void* sbrk(int increment) {
    static void* heap = heap_memory;   // Heap starts at the beginning of the heap_memory array
    static size_t allocated_size = 0;  // Track the size allocated so far

    // If increment leads to exceeding the total heap size, return failure
    if (allocated_size + increment > HEAP_SIZE) {
        return (void*)-1;  // Out of memory
    }

    void* prev_heap = heap;
    heap = (uint8_t *)heap + increment;  // Move heap forward by 'increment'
    allocated_size += increment;  // Increase allocated size by 'increment'

    return prev_heap;  // Return previous heap location (like real sbrk)
}

// Initializes the heap for the first time
void* initialize_heap() {
    heap_start = sbrk(HEAP_SIZE);  // Call our sbrk to allocate full heap memory
    if (heap_start == (void*)-1) {
        return NULL;  // Failed to allocate heap
    }

    heap_end = (uint8_t *)heap_start + HEAP_SIZE;  // Set the heap end

    // Create the initial free block, which spans the entire heap
    free_list = (struct Block*)heap_start;
    free_list->size = HEAP_SIZE - BLOCK_SIZE;  // Free block size excludes the block metadata
    free_list->free = 1;
    free_list->next = NULL;

    return heap_start;
}

// Find a free block of sufficient size
struct Block* find_free_block(size_t size) {
    struct Block* current = free_list;

    // Traverse the free list to find a block that is free and large enough
    while (current && !(current->free && current->size >= size)) {
        current = current->next;
    }

    return current;  // Returns NULL if no suitable block is found
}

// Expands the heap when no suitable block is found (in this case, a placeholder)
struct Block* expand_heap(size_t size) {
    (void)size;
    // In a real OS, you'd use sbrk or another system call to request more memory.
    // Here we simulate failure, as heap expansion is limited by HEAP_SIZE.
    return NULL;
}

// Splits a block into two if it's larger than needed
void split_block(struct Block* block, size_t size) {
    // Create a new block in the space after the allocated block
    struct Block* new_block = (struct Block*)((char*)block + size + BLOCK_SIZE);
    new_block->size = block->size - size - BLOCK_SIZE;  // Remaining size after the split
    new_block->free = 1;  // The new block is marked as free
    new_block->next = block->next;  // Link the new block to the next block

    block->size = size;  // Shrink the original block to the requested size
    block->next = new_block;  // Link the original block to the new block
}

void* malloc(size_t size) {
    if (size <= 0) {
        return NULL;  // Invalid size
    }

    struct Block* block;

    // Initialize the heap on the first malloc call
    if (!heap_start) {
        if (initialize_heap() == NULL) {
            return NULL;  // Heap initialization failed
        }
    }

    // Find a suitable free block
    block = find_free_block(size);

    if (!block) {
        // No suitable block found, try to expand the heap (not implemented for simplicity)
        block = expand_heap(size);
        if (!block) {
            return NULL;  // Out of memory
        }
    }

    // If the found block is larger than required, split it
    if (block->size > size + BLOCK_SIZE) {
        split_block(block, size);
    }

    block->free = 0;  // Mark the block as allocated
    return (void*)(block + 1);  // Return the memory address after the block metadata
}

void free(void* ptr) {
    if (!ptr) {
        return;  // No need to free a NULL pointer
    }

    // Retrieve the block metadata by moving back from the pointer
    struct Block* block = (struct Block*)ptr - 1;
    block->free = 1;  // Mark the block as free

    // Optionally, coalesce adjacent free blocks here to reduce fragmentation
}

// Allocate and zero-initialize memory
void* calloc(size_t num, size_t size) {
    size_t total_size = num * size;
    void* ptr = malloc(total_size);  // Allocate memory using malloc

    if (ptr) {
        // Initialize allocated memory to zero
        for (size_t i = 0; i < total_size; i++) {
            ((char*)ptr)[i] = 0;
        }
    }

    return ptr;  // Return the zero-initialized memory
}

void* realloc(void* ptr, size_t size) {
    if (!ptr) {
        return malloc(size);  // If ptr is NULL, realloc behaves like malloc
    }

    struct Block* block = (struct Block*)ptr - 1;

    // If the current block is large enough, return the same pointer
    if (block->size >= size) {
        return ptr;
    }

    // Otherwise, allocate a new block of the required size
    void* new_ptr = malloc(size);
    if (new_ptr) {
        // Copy the data from the old block to the new one
        size_t old_size = block->size;
        for (size_t i = 0; i < old_size && i < size; i++) {
            ((char*)new_ptr)[i] = ((char*)ptr)[i];
        }

        free(ptr);  // Free the old block
    }

    return new_ptr;  // Return the pointer to the new block
}
