
// Base C Class Structure Script
// by Kyle Furey

// REQUIREMENT: base_class.c

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Include this heading to use the class
#include "base_class.h"

// A structure that owns its own data, methods, and can be inherited from to share different properties.
#define class(name) typedef struct name name; struct name

// Represents a function pointer with a return type, variable name, and potential parameters.
#define FUNCTION(return, variable, ...) return (*variable) (__VA_ARGS__)


// BASE CLASS

// Template for a base class structure in C.
class(base_class)
{
	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New function pointers here


	// DESTRUCTOR

	// Properly destroys this class (call at the end of this object's scope)
	FUNCTION(void, destruct, base_class*);
};
