
// Derived C Class Structure Script
// by Kyle Furey

// REQUIREMENTS: derived_class.h

// Include this heading to use the class
#include "derived_class.h"


// DERIVED CLASS CONSTRUCTORS

void destruct_derived(derived_class* self);

// Default constructor:
// Returns a newly constructed instance of the given class.
derived_class construct_derived()
{
	derived_class self =
	{
		// Call base constructor
		self.super = construct_base(),

		// New constructor code here

		// Set destructor
		self.destruct = &destruct_derived
	};

	return self;
}

// New constructors here


// DERIVED CLASS DESTRUCTOR

// Destructor:
// Properly destroys this class.
void destruct_derived(derived_class* self)
{
	// New destructor code here

	// Call base destructor
	destruct_base(&self->super);
}


// DERIVED CLASS FUNCTIONS

// New function definitions here
