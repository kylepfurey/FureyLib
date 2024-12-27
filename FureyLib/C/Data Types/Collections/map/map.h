// .h
// C Map Collection Script
// by Kyle Furey

#pragma once
#include <string.h>
#include "../tree/tree.h"

// STRUCTURE

/** Represents a single key-value pair in C. */
typedef struct pair pair;

/** Represents a key-value map in C. */
typedef struct map map;

/** Represents a single key-value pair in C. */
struct pair {
    // VARIABLES

    /** A pointer to the element representing the key of this pair. */
    void *key;

    /** A pointer to the element representing the value of this pair. */
    void *value;
};

/** Represents a key-value map in C. */
struct map {
    // VARIABLES

    /** The size in bytes of each key stored in the map. */
    const size_t key_size;

    /** The size in bytes of each value stored in the map. */
    const size_t value_size;

    /** The current number of pairs stored in the map. */
    size_t size;

    /** A pointer to the root pair of this map. */
    tree_node *root;

    /** A pointer to a function used to compare each pair's key. */
    const comparison (*comparer)(const void *, const void *);
};

// CONSTRUCTORS AND DESTRUCTOR

/**
 * Initializes a new map with the given key comparer function.<br/>
 * A NULL comparer function uses the default_compare() function.
 */
map map_new(size_t size_of_key, size_t size_of_value,
            const comparison (*comparer)(const void *, const void *));

/** Properly destroys the given map. */
void map_free(map *self);

// FUNCTIONS

/** Clears the map of all its key-value pairs. */
void map_clear(map *self);

/**
 * Inserts a new pair into the map with a copy of the given key.<br/>
 * Returns a pointer to the new pair's value or an existing pair's value if an existing key was found.<br/>
 * Returns NULL if the insertion failed.
 */
void *map_insert(map *self, const void *key);

/**
 * Erases the pair within the map that matches the given key.<br/>
 * Returns whether a pair was successfully erased.
 */
bool map_erase(map *self, const void *key);

/**
 * Locates the value within the map's pairs that matches the given key.<br/>
 * Returns a pointer to the matching pair's value or NULL if no match was found.
 */
void *map_find(const map *self, const void *key);

/**
 * Copies all the map's keys into a new array.<br/>
 * NOTE: This array must be freed!
 */
void *map_keys(const map *self);

/**
 * Copies all the map's values into a new array.<br/>
 * NOTE: This array must be freed!
 */
void *map_values(const map *self);
