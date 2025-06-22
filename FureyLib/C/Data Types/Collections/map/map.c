// .c
// C Map Collection Script
// by Kyle Furey

#include "map.h"

// CONSTRUCTORS AND DESTRUCTOR

// Initializes a new map with the given key comparer function.
// A NULL comparer function uses the default_compare() function.
map map_new(const size_t size_of_key, const size_t size_of_value,
            const comparison (*comparer_func)(const void *, const void *)) {
    const map self = {
        size_of_key,
        size_of_value,
        0,
        NULL,
        comparer_func != NULL ? comparer_func : default_compare,
    };

    return self;
}

// Using recursion, frees all the pairs and their data within a map.
void _map_free(tree_node *root) {
    if (root == NULL) {
        return;
    }

    _map_free(root->left);

    tree_node *right = root->right;

    pair *pair = root->data;
    if (pair != NULL) {
        free(pair->value);

        pair->value = NULL;

        free(pair->key);

        pair->key = NULL;

        free(pair);

        pair = NULL;
    }

    free(root);

    root = NULL;

    _map_free(right);
}

// Properly destroys the given map.
void map_free(map *self) {
    map_clear(self);
}

// FUNCTIONS

// Clears the map of all its key-value pairs.
void map_clear(map *self) {
    if (self != NULL) {
        _map_free(self->root);

        self->size = 0;
        self->root = NULL;
    }
}

// Inserts a new pair into the map with a copy of the given key.
// Returns a pointer to the new pair's value or an existing pair's value if an existing key was found.
// Returns NULL if the insertion failed.
void *map_insert(map *self, const void *key) {
    if (self == NULL || key == NULL) {
        return NULL;
    }

    tree_node *inserted_node = self->root;
    tree_node *parent_node = NULL;
    bool insert_right = false;
    pair *pair = NULL;
    while (inserted_node != NULL) {
        pair = inserted_node->data;
        if (pair == NULL) {
            return NULL;
        }

        switch (self->comparer_func(key, pair->key)) {
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
                return pair->value;
        }
    }

    inserted_node = tree_node_new(sizeof(struct pair), self, parent_node, insert_right, &self->root);
    if (inserted_node == NULL) {
        return NULL;
    }

    pair = inserted_node->data;

    pair->key = malloc(self->key_size);
    if (pair->key == NULL) {
        tree_node_free(&inserted_node, &self->root);

        return NULL;
    }

    pair->value = malloc(self->value_size);
    if (pair->value == NULL) {
        free(pair->key);

        pair->key = NULL;

        tree_node_free(&inserted_node, &self->root);

        return NULL;
    }

    memcpy(pair->key, key, self->key_size);

    ++self->size;

    return pair->value;
}

// Erases the pair within the map that matches the given key.
// Returns whether a pair was successfully erased.
bool map_erase(map *self, const void *key) {
    if (self == NULL || key == NULL) {
        return false;
    }

    tree_node *removed_node = self->root;
    pair *pair = NULL;
    while (removed_node != NULL) {
        pair = removed_node->data;
        if (pair == NULL) {
            return false;
        }

        switch (self->comparer_func(key, pair->key)) {
            case LESS_THAN:
                removed_node = removed_node->left;
                break;

            case GREATER_THAN:
                removed_node = removed_node->right;
                break;

            default:
                --self->size;

                free(pair->value);

                pair->value = NULL;

                free(pair->key);

                pair->key = NULL;

                tree_node_free(&removed_node, &self->root);

                return true;
        }
    }

    return false;
}

// Locates the value within the map's pairs that matches the given key.
// Returns a pointer to the matching pair's value or NULL if no match was found.
void *map_find(const map *self, const void *key) {
    if (self == NULL || key == NULL) {
        return NULL;
    }

    const tree_node *current = self->root;
    while (current != NULL && current->data != NULL) {
        switch (self->comparer_func(key, ((pair *) current->data)->key)) {
            case LESS_THAN:
                current = current->left;
                break;

            case GREATER_THAN:
                current = current->right;
                break;

            default:
                return ((pair *) current->data)->value;
        }
    }

    return NULL;
}

// Using recursion, traverses the map in-order, copying each key into an array.
void _map_store_keys(const tree_node *root, void *array, size_t *index) {
    if (root == NULL || root->data == NULL || array == NULL) {
        return;
    }

    _map_store_keys(root->left, array, index);

    const map *map = root->tree;
    if (map == NULL) {
        return;
    }

    memcpy((uint8_t *) array + map->key_size * *index, ((pair *) root->data)->key, map->key_size);

    ++*index;

    _map_store_keys(root->right, array, index);
}

// Copies all the map's keys into a new array.
// NOTE: This array must be freed!
void *map_keys(const map *self) {
    if (self == NULL) {
        return NULL;
    }

    void *array = malloc(self->key_size * self->size);
    if (array == NULL) {
        return NULL;
    }

    size_t index = 0;

    _map_store_keys(self->root, array, &index);

    return array;
}

// Using recursion, traverses the map in-order, copying each value into an array.
void _map_store_values(const tree_node *root, void *array, size_t *index) {
    if (root == NULL || root->data == NULL || array == NULL) {
        return;
    }

    _map_store_values(root->left, array, index);

    const map *map = root->tree;
    if (map == NULL) {
        return;
    }

    memcpy((uint8_t *) array + map->value_size * *index, ((pair *) root->data)->value, map->value_size);

    ++*index;

    _map_store_values(root->right, array, index);
}

// Copies all the map's values into a new array.
// NOTE: This array must be freed!
void *map_values(const map *self) {
    if (self == NULL) {
        return NULL;
    }

    void *array = malloc(self->value_size * self->size);
    if (array == NULL) {
        return NULL;
    }

    size_t index = 0;

    _map_store_values(self->root, array, &index);

    return array;
}
