// .h
// Reference Counting Pointer Script
// by Kyle Furey

#pragma once
#include <stdlib.h>

// STRUCTURE

/** Represents a pointer to dynamically allocated memory that tracks its number of references. */
typedef struct {
    // VARIABLES

    /** The raw pointer to the data that is being reference counted. */
    void *data;

    /** The total number of remaining references to the data. */
    size_t count;
} ref_ptr;

// CONSTRUCTORS AND DESTRUCTOR

/** Allocates memory for a new reference pointer. */
ref_ptr *ref_ptr_new(size_t size_of_data);

/**
  * Properly increments the reference count of the given reference pointer and returns a copy of it.<br/>
  * This should be used instead of standard copying to ensure proper reference counting.
  */
ref_ptr *ref_ptr_ref(ref_ptr *self);

/**
  * Properly decrements the reference count of the given reference pointer, and frees the memory if no references remain.<br/>
  * This takes in a pointer to a pointer to ensure memory safety.<br/>
  * Returns the number of remaining references.
  */
size_t ref_ptr_free(ref_ptr **self);

// FUNCTIONS

/** 
  * Returns a weak pointer to the given reference pointer’s data.<br/>
  * This pointer does not increase the reference count and therefore should not be freed.<br/>
  * NOTE: This pointer may be NULL if the original reference pointer runs out of references.
  */
void **ref_ptr_weak(ref_ptr *self);
