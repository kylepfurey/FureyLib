
// Base C Class Structure Script
// by Kyle Furey

// REQUIREMENT: base_class.c

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// Include this heading to use the class
#include "base_class.h"

// A structure that owns its own data, methods, and can be inherited from to share different properties.
#define class(name) typedef struct name name; struct name

// Represents a function pointer with a return type, variable name, and potential parameters.
// Use this in class declarations to allow functions to be directly called by the class.
#define METHOD(return_type, name, ...) return_type (*name) (__VA_ARGS__)


// BASE CLASS

// Template for a base class structure in C.
class(base_class)
{
	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New functions here


	// DESTRUCTOR

	// Properly destroys this class (call at the end of this object's scope).
	const METHOD(void, destroy, base_class*);
};


// CONSTRUCTORS AND DESTRUCTOR

// Initializes a new base class.
base_class base_class_new();

// New constructors here

// Properly destroys this base class.
void base_class_free(base_class* self);


// FUNCTIONS

// New functions here
