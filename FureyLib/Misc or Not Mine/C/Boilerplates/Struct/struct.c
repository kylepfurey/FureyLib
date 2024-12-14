
// Name
// Creator

// REQUIREMENT: struct.h

// Include this heading to use the structure
#include "struct.h"


// CONSTRUCTORS AND DESTRUCTOR

// Initializes a new structure.
my_struct my_struct_new(const float x, const float y) {
	const my_struct self = {
		x,
		y
	};
	return self;
}

// New constructors here

// Properly destroys the given structure.
void my_struct_free(my_struct* self) {
	self->x = 0;
	self->y = 0;
}


// FUNCTIONS

// Returns the magnitude of the given structure.
float my_struct_magnitude(const my_struct* self) {
	if (self->x == 0 && self->y == 0) {
		return 0;
	}
	return sqrtf(self->x * self->x + self->y * self->y);
}

// Normalizes the given structure.
my_struct* my_struct_normalize(my_struct* self) {
	const float magnitude = my_struct_magnitude(self);
	if (magnitude == 0) {
		return self;
	}
	self->x /= magnitude;
	self->y /= magnitude;
	return self;
}

// New functions here
