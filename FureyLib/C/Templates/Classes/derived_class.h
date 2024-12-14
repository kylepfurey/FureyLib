
// Derived C Class Structure Script
// by Kyle Furey

// REQUIREMENTS: base_class.c, derived_class.c

#pragma once
#include "base_class.h"

// Include this heading to use the class
#include "derived_class.h"


// DERIVED CLASS

// Template for a derived class structure in C.
class(derived_class)
{
	// BASE CLASS

	// The base class this class derives from.
	base_class super;


	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New functions here


	// DESTRUCTOR

	// Properly destroys this class (call at the end of this object's scope).
	const METHOD(void, destroy, derived_class*);
};


// CONSTRUCTORS AND DESTRUCTOR

// Initializes a new derived class.
derived_class derived_class_new();

// New constructors here

// Properly destroys this derived class.
void derived_class_free(derived_class* self);


// FUNCTIONS

// New functions here
