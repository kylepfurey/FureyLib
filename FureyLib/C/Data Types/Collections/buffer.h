// .h
// Generic Stack Buffer Structure
// by Kyle Furey

#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/** An ID used to locate data within a buffer. */
typedef size_t buffer_id;

/** The value of a buffer ID that indicates the buffer is full. */
#define BUFFER_ERROR ((buffer_id)-1)

/** Declares a fixed-sized buffer of the given type and size with the given name. */
#define DECLARE_BUFFER_NAMED(type, size, name)\
\
/** A fixed-sized buffer of a certain type and size. */\
typedef struct {\
    /** The underlying array containing the data of this buffer. */\
    type buffer[size];\
\
    /** A bitset used to check whether data is being stored in this buffer. */\
    uint8_t available[(size + 7) / 8];\
\
    /** The current number of spaces occupied in this buffer. */\
    size_t count;\
\
    /** The next available ID in this buffer. */\
    buffer_id next_id;\
} name;\
\
/** The maximum size of this type of buffer. */\
enum {\
    name##_SIZE = size\
};\
\
/** Allocates a new zeroed-out buffer. */\
static inline name name##_new() {\
    return (name){0};\
}\
\
/** Inserts new data into the given buffer and returns its ID, or BUFFER_ERROR if the buffer is full. */\
static inline buffer_id name##_insert(name *const self, const type data) {\
    if (self == NULL || self->count >= size) {\
        return BUFFER_ERROR;\
    }\
    const buffer_id id = self->next_id++;\
    self->buffer[id] = data;\
    self->available[id / 8] |= 1u << (id % 8);\
    ++self->count;\
    while (self->next_id < size && (self->available[self->next_id / 8] & 1u << (self->next_id % 8)) != 0) {\
        ++self->next_id;\
    }\
    return id;\
}\
\
/** Erases the data in the given buffer with the given ID and returns whether it was successful. */\
static inline bool name##_erase(name *const self, const buffer_id id) {\
    if (self == NULL || id >= size || (self->available[id / 8] & 1u << (id % 8)) == 0) {\
        return false;\
    }\
    self->buffer[id] = (type){0};\
    self->available[id / 8] &= ~(1u << (id % 8));\
    --self->count;\
    self->next_id = id < self->next_id ? id : self->next_id;\
    return true;\
}\
\
/** Returns a pointer to the data in the given buffer with the given ID, or NULL if no data exists. */\
static inline type *name##_find(name *const self, const buffer_id id) {\
    if (self == NULL || id >= size || (self->available[id / 8] & 1u << (id % 8)) == 0) {\
        return NULL;\
    }\
    return &self->buffer[id];\
}\
\
/** Returns a const pointer to the data in the given buffer with the given ID, or NULL if no data exists. */\
static inline const type *name##_find_const(const name *const self, const buffer_id id) {\
    if (self == NULL || id >= size || (self->available[id / 8] & 1u << (id % 8)) == 0) {\
        return NULL;\
    }\
    return &self->buffer[id];\
}\
\
/** Returns whether the given buffer has data associated with the given ID. */\
static inline bool name##_contains(const name *const self, const buffer_id id) {\
    if (self == NULL || id >= size) {\
        return false;\
    }\
    return (self->available[id / 8] & 1u << (id % 8)) != 0;\
}\
\
/** Clears the given buffer. */\
static inline size_t name##_clear(name *const self) {\
    if (self == NULL) {\
        return 0;\
    }\
    const size_t count = self->count;\
    *self = (name){0};\
    return count;\
}\
\
/** Iterates through the given buffer with the given function and returns whether the iteration successfully completed. */\
static inline bool name##_foreach(name *const self, bool(*const action)(type*)) {\
    if (self == NULL) {\
        return false;\
    }\
    size_t count = self->count;\
    for (buffer_id id = 0; id < size && count > 0; ++id) {\
        if ((self->available[id / 8] & 1u << (id % 8)) != 0) {\
            --count;\
            if (!action(&self->buffer[id])) {\
                return false;\
            }\
        }\
    }\
    return true;\
}\
\
/** Iterates through the given buffer with the given const function and returns whether the iteration successfully completed. */\
static inline bool name##_foreach_const(const name *const self, bool(*const action)(const type*)) {\
    if (self == NULL) {\
        return false;\
    }\
    size_t count = self->count;\
    for (buffer_id id = 0; id < size && count > 0; ++id) {\
        if ((self->available[id / 8] & 1u << (id % 8)) != 0) {\
            --count;\
            if (!action(&self->buffer[id])) {\
                return false;\
            }\
        }\
    }\
    return true;\
}

/** Declares a fixed-sized buffer of the given type and size. */
#define DECLARE_BUFFER(type, size) DECLARE_BUFFER_NAMED(type, size, type##_buffer_##size)

#endif // BUFFER_H
