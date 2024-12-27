// .h
// C Binary Tree Structure Script
// by Kyle Furey

#pragma once
#include <stdlib.h>
#include <stdbool.h>

// ENUM

/**
 * An enumeration of different types of comparisons.<br/>
 * 0 = Less Than<br/>
 * 1 = Greater Than<br/>
 * 2 = Equal To
 */
typedef enum {
    LESS_THAN = 0,
    GREATER_THAN = 1,
    EQUAL_TO = 2
} comparison;

// STRUCTURE

/**
 * Represents a single binary tree node in C.<br/>
 * This structure is useful for creating collections with fast lookups, like sets or maps.
 */
typedef struct tree_node tree_node;

/**
 * Represents a single binary tree node in C.<br/>
 * This structure is useful for creating collections with fast lookups, like sets or maps.
 */
struct tree_node {
    // VARIABLES

    /** A pointer to the binary tree structure that owns this node. */
    const void *tree;

    /** A pointer to the lesser node of this binary tree node. */
    tree_node *left;

    /** A pointer to the greater node of this binary tree node. */
    tree_node *right;

    /** A pointer to the parent node of this binary tree node. */
    tree_node *parent;

    /** A pointer to the element stored in this node. */
    void *data;
};

// CONSTRUCTORS AND DESTRUCTOR

/**
 * Initializes a new tree node attached to the given leaf node.<br/>
 * Returns a pointer to the new node or NULL if allocation failed.
 */
tree_node *tree_node_new(size_t size_of_type, const void *tree,
                         tree_node *leaf_node, bool insert_right,
                         tree_node **root);

/**
 * Properly destroys the given tree node and removes it from its binary tree.<br/>
 * This takes in a pointer to a pointer to a node to ensure memory safety.
 */
void tree_node_free(tree_node **self, tree_node **root);

// FUNCTIONS

/**
 * The default comparison function.<br/>
 * This simply compares the memory addresses of A and B.
 */
comparison default_compare(const void *A, const void *B);
