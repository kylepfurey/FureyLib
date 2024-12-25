// .c
// C Vector Collection Script
// by Kyle Furey

#include "vector.h"

// CONSTRUCTORS AND DESTRUCTOR

// Initializes a new vector with the given capacity.
vector vector_new(const size_t size_of_type, const size_t capacity) {
    vector self = {
        size_of_type,
        0,
        0,
        NULL
    };

    if (capacity > 0) {
        vector_resize(&self, capacity);
    }

    return self;
}

// Properly destroys the given vector.
void vector_free(vector *self) {
    if (self != NULL) {
        free(self->data);

        self->data = NULL;
    }
}

// FUNCTIONS

// Resizes the vector to given capacity.
// Any elements outside the new capacity are deleted.
// This returns true if the vector was successfully resized.
bool vector_resize(vector *self, const size_t new_capacity) {
    if (self != NULL && self->capacity != new_capacity && new_capacity <= SIZE_MAX / self->element_size) {
        if (self->data == NULL) {
            if (new_capacity > 0) {
                self->data = malloc(self->element_size * new_capacity);
                if (self->data == NULL) {
                    return false;
                }

                self->capacity = new_capacity;
            }

            return true;
        }

        if (new_capacity == 0) {
            free(self->data);

            self->size = 0;
            self->capacity = 0;
            self->data = NULL;

            return true;
        }

        void *new_data = realloc(self->data, self->element_size * new_capacity);
        if (new_data == NULL) {
            return false;
        }

        self->size = new_capacity < self->size ? new_capacity : self->size;
        self->capacity = new_capacity;
        self->data = new_data;

        return true;
    }

    return false;
}

// Clears the vector of all of its elements.
void vector_clear(vector *self) {
    if (self != NULL) {
        free(self->data);

        self->size = 0;
        self->capacity = 0;
        self->data = NULL;
    }
}

// Returns the element at the given index in the vector.
// This returns NULL if the given index is out of the vector's bounds.
void *vector_at(const vector *self, const size_t index) {
    if (self == NULL || self->data == NULL || index >= self->size) {
        return NULL;
    }

    return self->data + self->element_size * index;
}

// Places a new element at the given index and pushes the rest of the vector forward.
// This will double the vector's capacity if new space is needed.
// Returns the element at the given index or NULL if the insertion failed.
void *vector_insert(vector *self, const size_t index) {
    if (self == NULL || index > self->size) {
        return NULL;
    }

    if (self->size + 1 > self->capacity) {
        const size_t new_capacity = self->capacity * 2;
        if (!vector_resize(self, new_capacity > 0 ? new_capacity : 2)) {
            return NULL;
        }
    }

    for (size_t i = self->size; i > index; --i) {
        memcpy(self->data + self->element_size * i, self->data + self->element_size * (i - 1), self->element_size);
    }

    ++self->size;

    return self->data + self->element_size * index;
}

// Erases the vector's element at the given index and shifts subsequent elements backward.
// This returns true if the removal was successful.
bool vector_erase(vector *self, const size_t index) {
    if (self == NULL || index >= self->size) {
        return false;
    }

    --self->size;

    for (size_t i = index; i < self->size; ++i) {
        memcpy(self->data + self->element_size * i, self->data + self->element_size * (i + 1), self->element_size);
    }

    return true;
}
