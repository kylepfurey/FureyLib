
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

// Retrieves the base class of the given class.
#define super(class) class.base


// DERIVED CLASS

// Forward declaration of derived class
typedef class derived_class derived_class;

// Template for a derived class structure in C.
class derived_class
{
	// BASE CLASS

	// The base class this class derives from
	base_class base;


	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New functions here


	// DESTRUCTOR

	// Properly destroys this class
	FUNCTION(void, destruct, derived_class*);
};


// DERIVED CLASS FUNCTIONS

// New functions here


// DERIVED CLASS CONSTRUCTORS

void destruct_derived(derived_class* target);

// Default constructor:
// Returns a newly constructed instance of the given class
derived_class construct_derived()
{
	derived_class target;

	// Call base constructor
	target.base = construct_base();

	// Set destructor
	target.destruct = &destruct_derived;

	// New constructor code here

	return target;
}

// New constructors here


// DERIVED CLASS DESTRUCTOR

// Destructor:
// Properly destroys this class
void destruct_derived(derived_class* target)
{
	// New destructor code here

	// Call base destructor
	destruct_base(&target->base);
}
