
// Base C Class Structure Script
// by Kyle Furey

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Include this heading to use the class
#include "base_class.h"

// A structure that owns its own data, methods, and can be inherited from to share different properties.
#define class struct

// Represents a function pointer with a return type, variable name, and potential parameters.
#define FUNCTION(return, variable, ...) return (*variable) (__VA_ARGS__)


// BASE CLASS

// Forward declaration of base class
typedef class base_class base_class;

// Template for a base class structure in C.
class base_class
{
	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New functions here


	// DESTRUCTOR

	// Properly destroys this class
	FUNCTION(void, destruct, base_class*);
};


// BASE CLASS FUNCTIONS

// New functions here


// BASE CLASS CONSTRUCTORS

void destruct_base(base_class* target);

// Default constructor:
// Returns a newly constructed instance of the given class
base_class construct_base()
{
	base_class target;

	// Set destructor
	target.destruct = &destruct_base;

	// New constructor code here

	return target;
}

// New constructors here


// BASE CLASS DESTRUCTOR

// Destructor:
// Properly destroys this class
void destruct_base(base_class* target)
{
	// New destructor code here
}
