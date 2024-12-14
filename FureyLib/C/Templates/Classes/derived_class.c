
// Derived C Class Structure Script
// by Kyle Furey

// REQUIREMENTS: derived_class.h

// Include this heading to use the class
#include "derived_class.h"


// CONSTRUCTORS AND DESTRUCTOR

// Initializes a new derived class.
derived_class derived_class_new()
{
	const derived_class self =
	{
		// Call base constructor
		base_class_new(),

		// New code here

		// Set destructor
		&derived_class_free
	};

	return self;
}

// New constructors here

// Properly destroys this derived class.
void derived_class_free(derived_class* self)
{
	// New code here

	// Call base destructor
	base_class_free(&self->super);
}


// FUNCTIONS

// New functions here
