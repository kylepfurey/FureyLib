// .c
// Reference Counting Pointer Script
// by Kyle Furey

#include "ref_ptr.h"

// CONSTRUCTORS AND DESTRUCTOR

// Allocates memory for a new reference pointer with a copy of the given data.
// Passing data as NULL will zero-initialize the data.
ref_ptr *ref_ptr_new(const size_t size_of_data, const void *data) {
    ref_ptr *self = malloc(sizeof(ref_ptr));
    if (self == NULL) {
        return NULL;
    }

    if (data != NULL) {
        self->data = malloc(size_of_data);
        if (self->data == NULL) {
            free(self);

            return NULL;
        }

        memcpy(self->data, data, size_of_data);
    } else {
        self->data = calloc(1, size_of_data);
        if (self->data == NULL) {
            free(self);

            return NULL;
        }
    }

    self->count = 1;

    return self;
}

// Creates a new weak pointer from a reference pointer.
// This allows a reference pointer to be accessed without increasing the reference count.
// Use weak_ptr_upgrade() to convert a weak pointer into a reference pointer.
weak_ptr weak_ptr_new(ref_ptr *self) {
    if (self == NULL || self->count == 0 || self->data == NULL) {
        const weak_ptr weak = {
            NULL,
            NULL,
            NULL
        };

        return weak;
    }

    const weak_ptr weak = {
        self,
        self->data,
        &self->data
    };

    return weak;
}

// Properly decrements the reference count of the given reference pointer, and frees the memory if no references remain.
// This takes in a pointer to a pointer to ensure memory safety.
// Returns the number of remaining references.
size_t ref_ptr_free(ref_ptr **self) {
    if (self != NULL && *self != NULL) {
        ref_ptr *ptr = *self;

        --ptr->count;

        if (ptr->count == 0) {
            free(ptr->data);

            ptr->data = NULL;

            free(ptr);

            ptr = NULL;

            *self = NULL;

            return 0;
        }

        *self = NULL;

        return ptr->count;
    }

    return 0;
}

// FUNCTIONS

// Properly increments the reference count of the given reference pointer and returns a copy of it.
// This should be used instead of standard copying to ensure proper reference counting.
ref_ptr *ref_ptr_ref(ref_ptr *self) {
    if (self == NULL) {
        return NULL;
    }

    ++self->count;

    return self;
}

// Converts a weak pointer into a reference pointer if it is still valid.
// Returns a new reference pointer or NULL if the reference counting pointer is expired.
// NOTE: This new reference pointer needs to be freed with ref_ptr_free()!
ref_ptr *weak_ptr_upgrade(const weak_ptr *self) {
    if (!weak_ptr_valid(self)) {
        return NULL;
    }

    ++self->owner->count;

    return self->owner;
}

// Returns whether the given weak pointer is still valid or not. 
bool weak_ptr_valid(const weak_ptr *self) {
    if (self == NULL || self->owner == NULL || self->data == NULL || self->address == NULL) {
        return false;
    }

    return self->data == *self->address && self->owner->count > 0;
}
