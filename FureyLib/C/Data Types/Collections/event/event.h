// .h
// C Multicast Event Script
// by Kyle Furey

#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

// TYPEDEF

/** An alias for a generic function pointer. */
typedef void (*func)(...);

// STRUCTURE

/** A collection of functions that can be bound, unbound, and invoked all at once. */
typedef struct {
    // VARIABLES

    /** The current number of bound functions to this event. */
    size_t count;

    /** The maximum number of bound functions to this event. */
    size_t capacity;

    /** The underlying array of bound functions in this event. */
    func *bindings;
} event;

// CONSTRUCTORS AND DESTRUCTOR

/** Initializes a new event with the given capacity. */
event event_new(size_t capacity);

/** Properly destroys the given event. */
void event_free(event *self);

// FUNCTIONS

/** Resizes the event's underlying array to the given capacity. */
bool event_resize(event *self, size_t new_capacity);

/** Binds a new function to this event. */
void event_bind(event *self, func callback);

/** Unbinds the first bound function that matches the given function from this event. */
bool event_unbind(event *self, func callback);

/** Returns whether at least one bound function matches the given function. */
bool event_is_bound(const event *self, func callback);

/** Unbinds all functions from this event. */
void event_clear(event *self);

/** Invokes each bound function with the given arguments. */
#define event_invoke(self, ...) {\
    if ((self) != NULL) {\
        for (size_t i = 0; i < (self)->count; ++i) {\
            if ((self)->bindings[i] != NULL) {\
                (self)->bindings[i](__VA_ARGS__);\
            }\
        }\
    }\
}

/** Invokes each bound function with the given arguments and stores the last function's result in return. */
#define event_invoke_return(self, return_type, return_value, ...)\
    return_type return_value = (return_type)0; {\
    if ((self) != NULL) {\
        for (size_t i = 0; i < (self)->count; ++i) {\
            if ((self)->bindings[i] != NULL) {\
                return_value = ((return_type(*)(...))(self)->bindings[i])(__VA_ARGS__);\
            }\
        }\
    }\
}
