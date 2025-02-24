// .c
// C Set Collection Script
// by Kyle Furey

#include "set.h"

// CONSTRUCTORS AND DESTRUCTOR

// Initializes a new set with the given comparer function.
// A NULL comparer function uses the default_compare() function.
set set_new(const size_t size_of_type, const comparison (*comparer_func)(const void *, const void *)) {
    const set self = {
        size_of_type,
        0,
        NULL,
        comparer_func != NULL ? comparer_func : default_compare,
    };

    return self;
}

// Using recursion, frees all the nodes and their data within a set.
void _set_free(tree_node *root) {
    if (root == NULL) {
        return;
    }

    _set_free(root->left);

    tree_node *right = root->right;

    free(root->data);

    root->data = NULL;

    free(root);

    root = NULL;

    _set_free(right);
}

// Properly destroys the given set.
void set_free(set *self) {
    set_clear(self);
}

// FUNCTIONS

// Clears the set's binary tree of all of its nodes.
void set_clear(set *self) {
    if (self != NULL) {
        _set_free(self->root);

        self->size = 0;
        self->root = NULL;
    }
}

// Traverses the set in-order until the given count reaches 0.
// Returns the node the set leaves off of.
tree_node *_set_iterate(tree_node *root, size_t *count) {
    if (root == NULL) {
        return NULL;
    }

    tree_node *node = _set_iterate(root->left, count);
    if (node != NULL) {
        return node;
    }

    if (*count == 0) {
        return root;
    }

    --*count;

    return _set_iterate(root->right, count);
}

// Traverses the set's binary tree in-order until it reaches the node at the given index.
// Returns a pointer to the node at the given index or NULL if the index is out of the binary tree's bounds.
tree_node *set_at(const set *self, size_t index) {
    if (self == NULL || index >= self->size) {
        return NULL;
    }

    return _set_iterate(self->root, &index);
}

// Inserts a new node into the set's binary tree with a copy of the given data.
// Returns a pointer to the new node or NULL if the insertion failed.
tree_node *set_insert(set *self, const void *data) {
    if (self == NULL || data == NULL) {
        return NULL;
    }

    tree_node *inserted_node = self->root;
    tree_node *parent_node = NULL;
    bool insert_right = false;
    while (inserted_node != NULL) {
        switch (self->comparer_func(data, inserted_node->data)) {
            case LESS_THAN:
                parent_node = inserted_node;
                inserted_node = inserted_node->left;
                insert_right = false;
                break;

            case GREATER_THAN:
                parent_node = inserted_node;
                inserted_node = inserted_node->right;
                insert_right = true;
                break;

            default:
                memcpy(inserted_node->data, data, self->element_size);
                return inserted_node;
        }
    }

    inserted_node = tree_node_new(self->element_size, self, parent_node, insert_right, &self->root);
    if (inserted_node == NULL) {
        return NULL;
    }

    memcpy(inserted_node->data, data, self->element_size);

    ++self->size;

    return inserted_node;
}

// Erases the node from the set's binary tree that matches the given data.
// Returns whether a node was successfully erased.
bool set_erase(set *self, const void *data) {
    tree_node *removed_node = set_find(self, data);
    if (removed_node == NULL) {
        return false;
    }

    --self->size;

    tree_node_free(&removed_node, &self->root);

    return true;
}

// Locates a node in the set's binary tree that matches the given data.
// Returns the matching node or NULL if no node was found.
tree_node *set_find(const set *self, const void *data) {
    if (self == NULL || data == NULL) {
        return NULL;
    }

    tree_node *current = self->root;
    while (current != NULL) {
        switch (self->comparer_func(data, current->data)) {
            case LESS_THAN:
                current = current->left;
                break;

            case GREATER_THAN:
                current = current->right;
                break;

            default:
                return current;
        }
    }

    return NULL;
}

// Using recursion, traverses the set in-order, copying each value into an array.
void _set_store_values(const tree_node *root, void *array, size_t *index) {
    if (root == NULL || root->data == NULL || array == NULL) {
        return;
    }

    _set_store_values(root->left, array, index);

    const set *set = root->tree;
    if (set == NULL) {
        return;
    }

    memcpy(array + set->element_size * *index, root->data, set->element_size);

    ++*index;

    _set_store_values(root->right, array, index);
}

// Copies all the set's values into a new array.
// NOTE: This array must be freed!
void *set_values(const set *self) {
    if (self == NULL) {
        return NULL;
    }

    void *array = malloc(self->element_size * self->size);
    if (array == NULL) {
        return NULL;
    }

    size_t index = 0;

    _set_store_values(self->root, array, &index);

    return array;
}
