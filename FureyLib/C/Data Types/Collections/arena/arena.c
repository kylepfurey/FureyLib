// .c
// Memory Arena Struct
// by Kyle Furey

#include "arena.h"
#include <string.h>

/** Returns whether the given address is a valid memblock. */
bool memblock_valid(arena *self, memblock *block) {
	if (self == NULL || block == NULL) {
		return false;
	}
	if (block->size == 0 || block->size % ARENA_ALIGN != 0) {
		return false;
	}
	if (block->previous != NULL) {
		memblock *previous = block->previous;
		if (previous >= block || previous < (memblock *)self->memory) {
			return false;
		}
		if (previous->next != block) {
			return false;
		}
	}
	if (block->next != NULL) {
		memblock *next = block->next;
		if (next <= block || next >= (memblock *)(self->memory + ARENA_SIZE)) {
			return false;
		}
		if (next->previous != block) {
			return false;
		}
	}
	return true;
}

/** Allocates memory from the given memory arena. NULL on failure. */
void *arena_malloc(arena *self, size_t size) {
	if (self == NULL) {
		return NULL;
	}
	if (size == 0) {
		size = ARENA_ALIGN;
	} else {
		size = ARENA_ROUND(size);
	}
	if (size > ARENA_SIZE - MEMBLOCK_SIZE) {
		return NULL;
	}
	memblock *block = self->head;
	while (block != NULL) {
		size_t available = MEMBLOCK_AVAILABLE(self, block);
		if (available >= MEMBLOCK_SIZE + size) {
			memblock *new_block = MEMBLOCK_NEXT(block);
			new_block->size = size;
			new_block->previous = block;
			new_block->next = block->next;
			if (block->next != NULL) {
				block->next->previous = new_block;
			}
			block->next = new_block;
			if (self->tail == block) {
				self->tail = new_block;
			}
			memset(&new_block->data, 0, new_block->size);
			return &new_block->data;
		}
		block = block->next;
	}
	if (self->head == NULL) {
		memblock *new_block = (memblock *)self->memory;
		if (&new_block->data + size > self->memory + ARENA_SIZE) {
			return NULL;
		}
		new_block->size = size;
		new_block->previous = NULL;
		new_block->next = NULL;
		self->head = new_block;
		self->tail = new_block;
		memset(&new_block->data, 0, new_block->size);
		return &new_block->data;
	}
	return NULL;
}

/** Allocates an array of zeroed memory from the given memory arena. NULL on failure. */
void *arena_calloc(arena *self, size_t size, size_t count) {
	if (count != 0 && size > SIZE_MAX / count) {
		return NULL;
	}
	size *= count;
	void *data = arena_malloc(self, size);
	if (data == NULL) {
		return NULL;
	}
	return data;
}

/** Reallocates memory in the given memory arena to the given size. NULL on failure. */
void *arena_realloc(arena *self, void *address, size_t size) {
	if (self == NULL || address == NULL) {
		return NULL;
	}
	if (size == 0) {
		size = ARENA_ALIGN;
	} else {
		size = ARENA_ROUND(size);
	}
	memblock *block = MEMBLOCK_GET(address);
	if (!memblock_valid(self, block)) {
		return NULL;
	}
	if (MEMBLOCK_AVAILABLE(self, block) + block->size >= size) {
		block->size = size;
		return &block->data;
	}
	void *data = arena_malloc(self, size);
	if (data == NULL) {
		return NULL;
	}
	memcpy(data, address, block->size);
	arena_free(self, address);
	return data;
}

/** Frees memory from the given memory arena. False on failure. */
bool arena_free(arena *self, void *address) {
	if (self == NULL || address == NULL) {
		return false;
	}
	memblock *block = MEMBLOCK_GET(address);
	if (!memblock_valid(self, block)) {
		return false;
	}
	if (block->previous != NULL) {
		block->previous->next = block->next;
	}
	if (block->next != NULL) {
		block->next->previous = block->previous;
	}
	if (self->head == block) {
		self->head = block->next;
	}
	if (self->tail == block) {
		self->tail = block->previous;
	}
	memset(block, 0, MEMBLOCK_SIZE + block->size);
	return true;
}
