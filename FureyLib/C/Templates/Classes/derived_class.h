
// Derived C Class Structure Script
// by Kyle Furey

// REQUIREMENTS: base_class.c, derived_class.c

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

	// The base class this class derives from.
	base_class super;


	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New function pointers here


	// DESTRUCTOR

	// Properly destroys this class (call at the end of this object's scope)
	FUNCTION(void, destruct, derived_class*);
};
