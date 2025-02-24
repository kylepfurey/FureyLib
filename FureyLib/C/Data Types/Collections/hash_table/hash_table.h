// .h
// C Hash Table Collection Script
// by Kyle Furey

#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

// TYPEDEF

/** A unique value that can be consistently generated from a key. */
typedef size_t hash;

// STRUCTURE

/** Represents a value paired with its unique hash key used to identify it in C. */
typedef struct hash_pair hash_pair;

/** Represents an open addressed hash table in C. */
typedef struct hash_table hash_table;

/** Represents a value paired with its unique hash key used to identify it in C. */
struct hash_pair {
    // VARIABLES

    /** The hashed key that represents this pair's placement in the hash table. */
    hash hash;

    /** A pointer to this pair's element in the hash table. */
    void *value;
};

/** Represents an open addressed hash table in C. */
struct hash_table {
    // VARIABLES

    /** The size in bytes of each value stored in the hash table. */
    const size_t element_size;

    /** The current number of values stored in the hash table. */
    size_t size;

    /** The total number of buckets currently in the hash table. */
    size_t bucket_count;

    /** A pointer to an array of buckets holding each value and its hashed key. */
    hash_pair *buckets;

    /** A pointer to a function used to convert a key into a unique hash value. */
    const hash (*hash_func)(const void *);
};

// CONSTRUCTORS AND DESTRUCTOR

/**
 * Initializes a new hash table with the given hash function.<br/>
 * A NULL hash function uses the default_hash() function.
 */
hash_table hash_table_new(size_t size_of_type, size_t bucket_count, const hash (*hash_func)(const void *));

/** Properly destroys the given hash table. */
void hash_table_free(hash_table *self);

// FUNCTIONS

/**
 * Expands the hash table to have at least the given number of buckets.<br/>
 * The new bucket count must successfully hold all values.<br/>
 * All values are rehashed back into the expanded table to ensure all values are retained with unique keys.<br/>
 * Returns true if the hash table was successfully expanded.
 */
bool hash_table_rehash(hash_table *self, size_t new_bucket_count);

/** Clears the hash table of all its values. */
void hash_table_clear(hash_table *self);

/**
 * Inserts a new value into the hash table using the given hashed key.<br/>
 * Returns a pointer to the new value or an existing value if a matching key was found.<br/>
 * Returns NULL if the insertion failed.
 */
void *hash_table_insert(hash_table *self, const void *key);

/**
 * Erases the value within the hash table that matches the given hashed key.<br/>
 * Returns whether a value was successfully erased.
 */
bool hash_table_erase(hash_table *self, const void *key);

/**
 * Locates the value within the hash table that matches the given hashed key.<br/>
 * Returns a pointer to the matching value or NULL if no match was found.
 */
void *hash_table_find(const hash_table *self, const void *key);

/**
 * Copies all the hash table's values into a new array.<br/>
 * NOTE: This array must be freed!
 */
void *hash_table_values(const hash_table *self);

/**
 * The default hash function.<br/>
 * This simply reads the first byte of the given data.
 */
hash default_hash(const void *key);
