// .h
// C Set Collection Script
// by Kyle Furey

#pragma once
#include <string.h>
#include "../tree/tree.h"

// STRUCTURE

/** Represents an ordered collection of unique data in C. */
typedef struct set set;

/** Represents an ordered collection of unique data in C. */
struct set {
    // VARIABLES

    /** The size in bytes of each element stored in the set. */
    const size_t element_size;

    /** The current number of elements stored in the set. */
    size_t size;

    /** A pointer to the root node of this set. */
    tree_node *root;

    /** A pointer to a function used to compare each node's data. */
    const comparison (*comparer_func)(const void *, const void *);
};

// CONSTRUCTORS AND DESTRUCTOR

/**
 * Initializes a new set with the given comparer function.<br/>
 * A NULL comparer function uses the default_compare() function.
 */
set set_new(size_t size_of_type, const comparison (*comparer_func)(const void *, const void *));

/** Properly destroys the given set. */
void set_free(set *self);

// FUNCTIONS

/** Clears the set's binary tree of all of its nodes. */
void set_clear(set *self);

/**
 * Traverses the set's binary tree in-order until it reaches the node at the given index.<br/>
 * Returns a pointer to the node at the given index or NULL if the index is out of the binary tree's bounds.
 */
tree_node *set_at(const set *self, size_t index);

/**
 * Inserts a new node into the set's binary tree with a copy of the given data.<br/>
 * Returns a pointer to the new node or NULL if the insertion failed.
 */
tree_node *set_insert(set *self, const void *data);

/**
 * Erases the node from the set's binary tree that matches the given data.<br/>
 * Returns whether a node was successfully erased.
 */
bool set_erase(set *self, const void *data);

/**
 * Locates a node in the set's binary tree that matches the given data.<br/>
 * Returns the matching node or NULL if no node was found.
 */
tree_node *set_find(const set *self, const void *data);

/**
 * Copies all the set's values into a new array.<br/>
 * NOTE: This array must be freed!
 */
void *set_values(const set *self);
