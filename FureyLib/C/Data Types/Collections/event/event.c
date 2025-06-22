// .c
// C Multicast Event Script
// by Kyle Furey

#include "event.h"

// CONSTRUCTORS AND DESTRUCTOR

// Initializes a new event with the given capacity.
event event_new(const size_t capacity) {
    event self = {
        0,
        0,
        NULL
    };

    if (capacity > 0) {
        event_resize(&self, capacity);
    }

    return self;
}

// Properly destroys the given event.
void event_free(event *self) {
    event_resize(self, 0);
}

// FUNCTIONS

// Resizes the event's underlying array to the given capacity.
bool event_resize(event *self, const size_t new_capacity) {
    if (self != NULL && self->capacity != new_capacity && new_capacity <= SIZE_MAX / sizeof(func)) {
        if (self->bindings == NULL) {
            if (new_capacity > 0) {
                self->bindings = malloc(sizeof(func) * new_capacity);
                if (self->bindings == NULL) {
                    return false;
                }
                self->capacity = new_capacity;
            }
            return true;
        }

        if (new_capacity == 0) {
            free(self->bindings);

            self->count = 0;
            self->capacity = 0;
            self->bindings = NULL;

            return true;
        }

        void *new_data = realloc(self->bindings, sizeof(func) * new_capacity);
        if (new_data == NULL) {
            return false;
        }

        self->count = new_capacity < self->count ? new_capacity : self->count;
        self->capacity = new_capacity;
        self->bindings = new_data;

        return true;
    }

    return false;
}

// Binds a new function to this event.
void event_bind(event *self, const func callback) {
    if (self == NULL || callback == NULL) {
        return;
    }

    if (self->count + 1 > self->capacity) {
        const size_t new_capacity = self->capacity * 2;
        if (!event_resize(self, new_capacity > 0 ? new_capacity : 2)) {
            return;
        }
    }

    self->bindings[self->count] = callback;

    ++self->count;
}

// Unbinds the first bound function that matches the given function from this event.
bool event_unbind(event *self, const func callback) {
    if (self == NULL || callback == NULL) {
        return false;
    }

    for (size_t i = 0; i < self->count; ++i) {
        if (self->bindings[i] == callback) {
            const size_t shift = self->count - i - 1;
            if (shift > 0) {
                memmove(&self->bindings[i], &self->bindings[i + 1], shift * sizeof(func));
            }
            self->count--;
            return true;
        }
    }

    return false;
}

// Returns whether at least one bound function matches the given function.
bool event_is_bound(const event *self, const func callback) {
    if (self == NULL || callback == NULL) {
        return false;
    }

    for (size_t i = 0; i < self->count; ++i) {
        if (self->bindings[i] == callback) {
            return true;
        }
    }

    return false;
}

// Unbinds all functions from this event.
void event_clear(event *self) {
    if (self == NULL) {
        return;
    }

    self->count = 0;
}
