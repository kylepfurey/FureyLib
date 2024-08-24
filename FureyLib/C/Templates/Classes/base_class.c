
// Base C Class Structure Script
// by Kyle Furey

// REQUIREMENT: base_class.h

// Include this heading to use the class
#include "base_class.h"


// BASE CLASS CONSTRUCTORS

void destruct_base(base_class* self);

// Default constructor:
// Returns a newly constructed instance of the given class.
base_class construct_base()
{
	base_class self =
	{
		// New constructor code here

		// Set destructor
		self.destruct = &destruct_base
	};

	return self;
}

// New constructors here


// BASE CLASS DESTRUCTOR

// Destructor:
// Properly destroys this class.
void destruct_base(base_class* self)
{
	// New destructor code here
}


// BASE CLASS FUNCTIONS

// New function definitions here
