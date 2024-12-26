// .c
// C Linked List Collection Script
// by Kyle Furey

#include "list.h"

// CONSTRUCTORS AND DESTRUCTOR

// Initializes a new linked list.
list list_new(const size_t size_of_type) {
    const list self = {
        size_of_type,
        0,
        NULL
    };

    return self;
}

// Properly destroys the given linked list and its nodes.
void list_free(list *self) {
    list_clear(self);
}

// FUNCTIONS

// Clears the linked list of all of its nodes.
void list_clear(list *self) {
    if (self != NULL && self->head != NULL) {
        list_node *current = self->head;

        for (size_t i = 0; i < self->size; ++i) {
            list_node *next = current->next;

            free(current->data);

            free(current);

            current = next;
        }

        self->size = 0;
        self->head = NULL;
    }
}

// Traverses the linked list until it reaches the node at given index.
// This returns a pointer to the node at the given index or NULL if the index is out of the linked list's bounds.
list_node *list_at(const list *self, const size_t index) {
    if (self == NULL || self->head == NULL || index >= self->size) {
        return NULL;
    }

    if (index > self->size / 2) {
        list_node *current = self->head->previous;

        for (size_t i = self->size - 1; i > index; --i) {
            current = current->previous;
        }

        return current;
    }

    list_node *current = self->head;

    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }

    return current;
}

// Inserts a new node after the given node in the linked list.
// Passing NULL will push the node at the end of the linked list.
// Returns a pointer to the new node or NULL if the insertion failed.
list_node *list_insert(list *self, list_node *previous_node) {
    if (self == NULL) {
        return NULL;
    }

    if (previous_node == NULL) {
        if (self->head != NULL) {
            previous_node = self->head->previous;
        }
    } else {
        if (self->head == NULL || previous_node->list != self) {
            return NULL;
        }
    }

    list_node *new_node = malloc(sizeof(list_node));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = malloc(sizeof(self->element_size));
    if (new_node->data == NULL) {
        free(new_node);

        return NULL;
    }

    new_node->list = self;

    if (self->head == NULL) {
        self->head = new_node;
        new_node->previous = new_node;
        new_node->next = new_node;
    } else {
        new_node->previous = previous_node;
        new_node->next = previous_node->next;
        previous_node->next->previous = new_node;
        previous_node->next = new_node;
    }

    ++self->size;

    return new_node;
}

// Erases the given node from the linked list.
// This takes in a pointer to a pointer to a node to ensure memory safety.
// This returns true if the removal was successful.
bool list_erase(list *self, list_node **node) {
    if (self == NULL || self->head == NULL || node == NULL) {
        return false;
    }

    list_node *removed_node = *node;
    if (removed_node == NULL || removed_node->list != self) {
        return false;
    }

    --self->size;

    if (self->size == 0) {
        self->head = NULL;
    } else if (self->head == removed_node) {
        self->head = self->head->next;
    }

    if (removed_node->previous != NULL) {
        removed_node->previous->next = removed_node->next;
    }

    if (removed_node->next != NULL) {
        removed_node->next->previous = removed_node->previous;
    }

    free(removed_node->data);

    free(removed_node);

    *node = NULL;

    return true;
}

// Returns whether the linked list contains the given node. 
bool list_contains(const list *self, const list_node *node) {
    if (self == NULL || node == NULL) {
        return false;
    }

    return node->list == self;
}
