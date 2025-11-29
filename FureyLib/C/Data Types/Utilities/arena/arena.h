// .h
// Memory Arena Structure
// by Kyle Furey

#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/** The size of a memory block's header. */
#define MEMBLOCK_SIZE \
offsetof(memblock, data)

/** Returns the memory block header of the given address. */
#define MEMBLOCK_GET(address) \
((memblock *)((address) - MEMBLOCK_SIZE))

/** Calculates the location of the next memblock. */
#define MEMBLOCK_NEXT(block) \
((memblock *)(&(block)->data + (block)->size))

/** Calculates how many bytes are free between memblocks. */
#define MEMBLOCK_AVAILABLE(arena, block) \
(((block)->next != NULL) ? \
((uint8_t*)(block)->next - (&(block)->data + (block)->size)) : \
((arena)->memory + ARENA_SIZE - (uint8_t*)MEMBLOCK_NEXT(block)))

/** The maximum size in bytes of a memory arena. */
#define ARENA_SIZE \
4096

/** The size of a byte segment in a memory arena. */
#define ARENA_ALIGN \
4

/** Rounds a number of bytes up to the nearest byte segment in a memory arena. */
#define ARENA_ROUND(size)\
((((size) + (ARENA_ALIGN - 1)) / (ARENA_ALIGN)) * (ARENA_ALIGN))

/** A doubly-linked list node for dynamic memory blocks. */
typedef struct memblock {
	/** The address of the memory block after this one. */
	struct memblock *next;

	/** The address of the memory block before this one. */
	struct memblock *previous;

	/** The size of the allocated data of this memory block. */
	size_t size;

	/** The first byte of allocated data of this memory block. */
	uint8_t data;
} memblock;

/** A large chunk of bytes that can be dynamically allocated from. */
typedef struct {
	/** The address of the first memory block. */
	memblock *head;

	/** The address of the last memory block. */
	memblock *tail;

	/** The bytes containing each memory block that can be allocated from. */
	uint8_t memory[ARENA_SIZE];
} arena;

/** Returns whether the given memblock is valid. */
bool memblock_valid(arena *self, memblock *block);

/** Allocates memory from the given memory arena. NULL on failure. */
void *arena_malloc(arena *self, size_t size);

/** Allocates an array of zeroed memory from the given memory arena. NULL on failure. */
void *arena_calloc(arena *self, size_t size, size_t count);

/** Reallocates memory in the given memory arena to the given size. NULL on failure. */
void *arena_realloc(arena *self, void *address, size_t size);

/** Frees memory from the given memory arena. False on failure. */
bool arena_free(arena *self, void *address);

#endif // ARENA_H
