// .c
// C Binary Tree Structure Script
// by Kyle Furey

#include "tree.h"

// CONSTRUCTORS AND DESTRUCTOR

// Initializes a new tree node attached to the given leaf node.
// Returns a pointer to the new node or NULL if allocation failed.
tree_node *tree_node_new(const size_t size_of_type, const void *tree,
                         tree_node *leaf_node, const bool insert_right,
                         tree_node **root) {
    if (tree == NULL || root == NULL) {
        return NULL;
    }

    if (leaf_node != NULL) {
        if (*root == NULL || leaf_node->tree != (*root)->tree) {
            return NULL;
        }
    }

    tree_node *node = malloc(sizeof(tree_node));
    if (node == NULL) {
        return NULL;
    }

    node->data = malloc(size_of_type);
    if (node->data == NULL) {
        free(node);

        node = NULL;

        return NULL;
    }

    node->tree = tree;
    node->left = NULL;
    node->right = NULL;
    node->parent = leaf_node;

    if (leaf_node != NULL) {
        if (insert_right) {
            if (leaf_node->right == NULL) {
                leaf_node->right = node;
            } else {
                free(node->data);

                node->data = NULL;

                free(node);

                node = NULL;

                return NULL;
            }
        } else {
            if (leaf_node->left == NULL) {
                leaf_node->left = node;
            } else {
                free(node->data);

                node->data = NULL;

                free(node);

                node = NULL;

                return NULL;
            }
        }
    } else {
        *root = node;
    }

    return node;
}

// Properly destroys the given tree node and removes it from its binary tree.
// This takes in a pointer to a pointer to a node to ensure memory safety.
void tree_node_free(tree_node **self, tree_node **root) {
    if (self != NULL) {
        tree_node *removed_node = *self;
        if (removed_node != NULL) {
            if (root != NULL && *root != NULL && removed_node->tree == (*root)->tree) {
                if (removed_node == *root) {
                    if (removed_node->left == NULL) {
                        if (removed_node->right == NULL) {
                            // No children
                            *root = NULL;
                        } else {
                            // One child
                            removed_node->right->parent = NULL;

                            *root = removed_node->right;
                        }
                    } else {
                        if (removed_node->right == NULL) {
                            // One child
                            removed_node->left->parent = NULL;

                            *root = removed_node->left;
                        } else {
                            // Two children
                            tree_node *successor = removed_node->left;
                            while (successor->right != NULL) {
                                successor = successor->right;
                            }

                            successor->right = removed_node->right;
                            if (successor->right != NULL) {
                                successor->right->parent = successor;
                            }

                            if (successor->parent != removed_node) {
                                successor->parent->right = successor->left;
                                if (successor->left != NULL) {
                                    successor->left->parent = successor->parent;
                                }

                                successor->left = removed_node->left;
                                if (successor->left != NULL) {
                                    successor->left->parent = successor;
                                }
                            }

                            successor->parent = NULL;

                            *root = successor;
                        }
                    }
                } else {
                    if (removed_node->left == NULL) {
                        if (removed_node->right == NULL) {
                            // No children
                            if (removed_node->parent->left == removed_node) {
                                removed_node->parent->left = NULL;
                            } else {
                                removed_node->parent->right = NULL;
                            }
                        } else {
                            // One child
                            removed_node->right->parent = removed_node->parent;

                            if (removed_node->parent->left == removed_node) {
                                removed_node->parent->left = removed_node->right;
                            } else {
                                removed_node->parent->right = removed_node->right;
                            }
                        }
                    } else {
                        if (removed_node->right == NULL) {
                            // One child
                            removed_node->left->parent = removed_node->parent;

                            if (removed_node->parent->left == removed_node) {
                                removed_node->parent->left = removed_node->left;
                            } else {
                                removed_node->parent->right = removed_node->left;
                            }
                        } else {
                            // Two children
                            tree_node *successor = removed_node->left;
                            while (successor->right != NULL) {
                                successor = successor->right;
                            }

                            if (removed_node->parent->left == removed_node) {
                                removed_node->parent->left = successor;
                            } else {
                                removed_node->parent->right = successor;
                            }

                            successor->right = removed_node->right;
                            if (successor->right != NULL) {
                                successor->right->parent = successor;
                            }

                            if (successor->parent != removed_node) {
                                successor->parent->right = successor->left;
                                if (successor->left != NULL) {
                                    successor->left->parent = successor->parent;
                                }

                                successor->left = removed_node->left;
                                if (successor->left != NULL) {
                                    successor->left->parent = successor;
                                }
                            }

                            successor->parent = removed_node->parent;
                        }
                    }
                }
            }

            free(removed_node->data);

            removed_node->data = NULL;

            free(removed_node);

            removed_node = NULL;

            *self = NULL;
        }
    }
}

// FUNCTIONS

// The default comparison function.
// This simply compares the memory addresses of A and B.
comparison default_compare(const void *A, const void *B) {
    if (A == B) {
        return EQUAL_TO;
    }

    return A > B ? GREATER_THAN : LESS_THAN;
}
