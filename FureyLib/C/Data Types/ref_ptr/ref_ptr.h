// .h
// Reference Counting Pointer Script
// by Kyle Furey

#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// STRUCTURE

/** Represents a pointer to dynamically allocated memory that tracks its number of references. */
typedef struct {
    // VARIABLES

    /** The raw pointer to the data that is being reference counted. */
    void *data;

    /** The total number of remaining references to the data. */
    size_t count;
} ref_ptr;

/** Represents a pointer to a reference counting pointer without increasing the reference count. */
typedef struct {
    // VARIABLES

    /**
     * A pointer to the reference pointer.<br/>
     * You may only dereference this pointer if weak_ptr_valid() returns true.<br/>
     * You can convert this weak pointer into a reference pointer using weak_ptr_upgrade().
     */
    ref_ptr *owner;

    /**
     * A copy of the pointer to the reference pointer's data.<br/>
     * This is compared with the address pointer to check if the reference pointer is still valid.<br/>
     * Do not dereference this pointer! Use weak_ptr_upgrade() instead.
     */
    const void *data;

    /**
     * A pointer to the reference pointer's data.<br/>
     * This is compared with the data pointer to check if the reference pointer is still valid.<br/>
     * Do not dereference this pointer! Use weak_ptr_upgrade() instead.
     */
    const void **address;
} weak_ptr;

// CONSTRUCTORS AND DESTRUCTOR

/**
 * Allocates memory for a new reference pointer with a copy of the given data.<br/>
 * Passing data as NULL will zero-initialize the data.
 */
ref_ptr *ref_ptr_new(size_t size_of_data, const void *data);

/**
 * Creates a new weak pointer from a given reference pointer.<br/>
 * This allows a reference pointer to be accessed without increasing the reference count.<br/>
 * Use weak_ptr_upgrade() to convert a weak pointer into a reference pointer.
 */
weak_ptr weak_ptr_new(ref_ptr *self);

/**
 * Properly decrements the reference count of the given reference pointer, and frees the memory if no references remain.<br/>
 * This takes in a pointer to a pointer to ensure memory safety.<br/>
 * Returns the number of remaining references.
 */
size_t ref_ptr_free(ref_ptr **self);

// FUNCTIONS

/**
 * Properly increments the reference count of the given reference pointer and returns a copy of it.<br/>
 * This should be used instead of standard copying to ensure proper reference counting.
 */
ref_ptr *ref_ptr_ref(ref_ptr *self);

/**
 * Converts a weak pointer into a reference pointer if it is still valid.<br/>
 * Returns a new reference pointer or NULL if the pointer is expired.<br/>
 * NOTE: This new reference pointer needs to be freed with ref_ptr_free()!
 */
ref_ptr *weak_ptr_upgrade(const weak_ptr *self);

/** Returns whether the given weak pointer is still valid or not. */
bool weak_ptr_valid(const weak_ptr *self);
