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

// Properly destroys the given linked list.
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

            current->data = NULL;

            free(current);

            current = next;
        }

        self->size = 0;
        self->head = NULL;
    }
}

// Traverses the linked list until it reaches the node at given index.
// Returns a pointer to the node at the given index or NULL if the index is out of the linked list's bounds.
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
// Returns a pointer to the new node or NULL if the insertion failed.
list_node *list_insert(list *self, list_node *previous_node) {
    if (!list_contains(self, previous_node)) {
        return NULL;
    }

    list_node *new_node = malloc(sizeof(list_node));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = malloc(sizeof(self->element_size));
    if (new_node->data == NULL) {
        free(new_node);

        new_node = NULL;

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

// Inserts a new node at the end of the linked list.
// Returns a pointer to the new node or NULL if the insertion failed.
list_node *list_push_back(list *self) {
    if (self != NULL && self->head != NULL) {
        return list_insert(self, self->head->previous);
    }

    return false;
}

// Inserts a new node at the front of the linked list.
// Returns a pointer to the new node or NULL if the insertion failed.
list_node *list_push_front(list *self) {
    if (self != NULL && self->head != NULL) {
        if (list_insert(self, self->head->previous)) {
            self->head = self->head->previous;
            return self->head;
        }
    }

    return false;
}

// Erases the given node from the linked list.
// This takes in a pointer to a pointer to a node to ensure memory safety.
// Returns true if the removal was successful.
bool list_erase(list *self, list_node **node) {
    if (node == NULL || !list_contains(self, *node)) {
        return false;
    }

    list_node *removed_node = *node;

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

    removed_node->data = NULL;

    free(removed_node);

    removed_node = NULL;

    *node = NULL;

    return true;
}

// Erases the node at the end of the linked list.
// Returns true if the removal was successful.
bool list_pop_back(list *self) {
    if (self != NULL && self->head != NULL) {
        list_node *end = self->head->previous;
        return list_erase(self, &end);
    }

    return false;
}

// Erases the node at the front of the linked list.
// Returns true if the removal was successful.
bool list_pop_front(list *self) {
    if (self != NULL && self->head != NULL) {
        list_node *head = self->head;
        return list_erase(self, &head);
    }

    return false;
}

// Returns whether the given node is within the linked list.
bool list_contains(const list *self, const list_node *node) {
    if (self == NULL || node == NULL) {
        return false;
    }

    return node->list == self;
}
