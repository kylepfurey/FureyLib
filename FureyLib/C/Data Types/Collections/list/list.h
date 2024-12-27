// .h
// C Linked List Collection Script
// by Kyle Furey

#pragma once
#include <stdlib.h>
#include <stdbool.h>

// STRUCTURE

/** Represents a single doubly linked list node in C. */
typedef struct list_node list_node;

/** Represents a doubly circular linked list in C. */
typedef struct list list;

/** Represents a single doubly linked list node in C. */
struct list_node {
    // VARIABLES

    /** A pointer to the linked list structure that owns this node. */
    const void *list;

    /** A pointer to the node sequentially before this node in the linked list. */
    list_node *previous;

    /** A pointer to the node sequentially after this node in the linked list. */
    list_node *next;

    /** A pointer to the element stored in this node. */
    void *data;
};

/** Represents a doubly circular linked list in C. */
struct list {
    // VARIABLES

    /** The size in bytes of each element stored in the linked list. */
    const size_t element_size;

    /** The current number of nodes stored in the linked list. */
    size_t size;

    /** A pointer to the first (and last) node of the linked list. */
    list_node *head;
};

// CONSTRUCTORS AND DESTRUCTOR

/** Initializes a new linked list. */
list list_new(size_t size_of_type);

/** Properly destroys the given linked list. */
void list_free(list *self);

// FUNCTIONS

/** Clears the linked list of all of its nodes. */
void list_clear(list *self);

/**
 * Traverses the linked list until it reaches the node at given index.<br/>
 * Returns a pointer to the node at the given index or NULL if the index is out of the linked list's bounds.
 */
list_node *list_at(const list *self, size_t index);

/**
 * Inserts a new node after the given node in the linked list.<br/>
 * Returns a pointer to the new node or NULL if the insertion failed.
 */
list_node *list_insert(list *self, list_node *previous_node);

/**
 * Inserts a new node at the end of the linked list.<br/>
 * Returns a pointer to the new node or NULL if the insertion failed.
 */
list_node *list_push(list *self);

/**
 * Erases the given node from the linked list.<br/>
 * This takes in a pointer to a pointer to a node to ensure memory safety.<br/>
 * Returns true if the removal was successful.
 */
bool list_erase(list *self, list_node **node);

/**
 * Erases the node at the end of the linked list.<br/>
 * Returns true if the removal was successful.
 */
bool list_pop(list *self);

/** Returns whether the given node is within the linked list. */
bool list_contains(const list *self, const list_node *node);
