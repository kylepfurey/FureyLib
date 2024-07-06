
// Base C Class Structure Script
// by Kyle Furey

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Include this heading to use the class
#include "BaseClass.h"

// A structure that owns its own data, methods, and can be inherited from to share different properties.
#define class struct

// Represents a function pointer with a return type, variable name, and potential parameters.
#define FUNCTION(return, variable, ...) return (*variable) (__VA_ARGS__)


// BASE CLASS

// Forward declaration of Base Class
typedef class BaseClass BaseClass;

// Template for a base class structure in C.
class BaseClass
{
	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New functions here


	// DESTRUCTOR

	// Properly destroys this class
	FUNCTION(void, Destruct, BaseClass*);
};


// BASE CLASS FUNCTIONS

// New functions here


// BASE CLASS CONSTRUCTORS

void DestructBase(BaseClass* target);

// Default constructor:
// Returns a newly constructed instance of the given class
BaseClass ConstructBase()
{
	BaseClass target;

	// Set destructor
	target.Destruct = &DestructBase;

	// New constructor code here

	return target;
}

// New constructors here


// BASE CLASS DESTRUCTOR

// Destructor:
// Properly destroys this class
void DestructBase(BaseClass* target)
{
	// New destructor code here
}
