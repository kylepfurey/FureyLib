
// Derived C Class Structure Script
// by Kyle Furey

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "base_class.h"

// Include this heading to use the class
#include "derived_class.h"


// DERIVED CLASS

// Template for a derived class structure in C.
class(derived_class)
{
	// BASE CLASS

	// The base class this class derives from
	base_class super;


	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New function pointers here


	// DESTRUCTOR

	// Properly destroys this class (call at the end of this object's scope)
	FUNCTION(void, destruct, derived_class*);
};


// DERIVED CLASS FUNCTIONS

// New function definitions here


// DERIVED CLASS CONSTRUCTORS

void destruct_derived(derived_class* self);

// Default constructor:
// Returns a newly constructed instance of the given class
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
// Properly destroys this class
void destruct_derived(derived_class* self)
{
	// New destructor code here

	// Call base destructor
	destruct_base(&self->super);
}
