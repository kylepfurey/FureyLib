// .h
// C Vector Collection Script
// by Kyle Furey

#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// STRUCTURE

/** Represents a dynamic array in C. */
typedef struct {
    // VARIABLES

    /** The size in bytes of each element stored in the vector. */
    const size_t element_size;

    /** The current number of elements stored in the vector. */
    size_t size;

    /** The maximum number of elements in the vector before needing to expand. */
    size_t capacity;

    /** A pointer to the first element of the vector. */
    void *data;
} vector;

// CONSTRUCTORS AND DESTRUCTOR

/** Initializes a new vector with the given capacity. */
vector vector_new(size_t size_of_type, size_t capacity);

/** Properly destroys the given vector. */
void vector_free(vector *self);

// FUNCTIONS

/**
 * Resizes the vector to given capacity.<br/>
 * Any elements outside the new capacity are deleted.<br/>
 * Returns true if the vector was successfully resized.
 */
bool vector_resize(vector *self, size_t new_capacity);

/** Clears the vector of all of its elements. */
void vector_clear(vector *self);

/**
 * Returns the element at the given index in the vector<br/>
 * or NULL if the given index is out of the vector's bounds.
 */
void *vector_at(const vector *self, size_t index);

/**
 * Places a new element at the given index and pushes the rest of the vector's elements forward.<br/>
 * This will double the vector's capacity if new space is needed.<br/>
 * Returns the new element at the given index or NULL if the insertion failed.
 */
void *vector_insert(vector *self, size_t index);

/**
 * Places a new element at the end of the vector.<br/>
 * This will double the vector's capacity if new space is needed.<br/>
 * Returns the new element or NULL if the insertion failed.
 */
void *vector_push_back(vector *self);

/**
 * Places a new element at the front of the vector.<br/>
 * This will double the vector's capacity if new space is needed.<br/>
 * Returns the new element or NULL if the insertion failed.
 */
void *vector_push_front(vector *self);

/**
 * Erases the vector's element at the given index and shifts subsequent elements backward.<br/>
 * Returns true if the removal was successful.
 */
bool vector_erase(vector *self, size_t index);

/**
 * Erases the element at the end of the vector.<br/>
 * Returns true if the removal was successful.
 */
bool vector_pop_back(vector *self);

/**
 * Erases the element at the front of the vector.<br/>
 * Returns true if the removal was successful.
 */
bool vector_pop_front(vector *self);
