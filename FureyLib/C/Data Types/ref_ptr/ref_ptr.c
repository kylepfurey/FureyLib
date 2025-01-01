// .c
// Reference Counting Pointer Script
// by Kyle Furey

#include "ref_ptr.h"

// CONSTRUCTORS AND DESTRUCTOR

// Allocates memory for a new reference pointer.
ref_ptr *ref_ptr_new(const size_t size_of_data) {
     ref_ptr *self = malloc(sizeof(ref_ptr));
     if (self == NULL) {
          return NULL;
     }

     self->data = malloc(size_of_data);
     if (self->data == NULL) {
          free(self);

          return NULL;
     }

     self->count = 1;

     return self;
}

// Properly increments the reference count of the given reference pointer and returns a copy of it.
// This should be used instead of standard copying to ensure proper reference counting.
ref_ptr *ref_ptr_ref(ref_ptr *self) {
     if (self == NULL) {
          return NULL;
     }

     ++self->count;

     return self;
}

// Properly decrements the reference count of the given reference pointer, and frees the memory if no references remain.
// This takes in a pointer to a pointer to ensure memory safety.
// Returns the number of remaining references.
size_t ref_ptr_free(ref_ptr **self) {
     if (self != NULL && *self != NULL) {
          ref_ptr *ptr = *self;

         --ptr->count;

          if (ptr->count == 0) {
               free(ptr->data);

               ptr->data = NULL;

               free(ptr);

               ptr = NULL;

               *self = NULL;

               return 0;
         }

          *self = NULL;

          return ptr->count;
     }

     return 0;
}

// FUNCTIONS

// Returns a weak pointer to the given reference pointer’s data.
// This pointer does not increase the reference count and therefore should not be freed.
// NOTE: This pointer may be NULL if the original reference pointer runs out of references.
void **ref_ptr_weak(ref_ptr *self) {
     if (self == NULL) {
          return NULL;
     }

     return &self->data;
}
