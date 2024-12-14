
// Base C Class Structure Script
// by Kyle Furey

// REQUIREMENT: base_class.h

// Include this heading to use the class
#include "base_class.h"


// CONSTRUCTORS AND DESTRUCTOR

// Initializes a new base class.
base_class base_class_new()
{
	const base_class self =
	{
		// New code here

		// Set destructor
		&base_class_free
	};

	return self;
}

// New constructors here

// Properly destroys this base class.
void base_class_free(base_class* self)
{
	// New code here
}


// FUNCTIONS

// New functions here
