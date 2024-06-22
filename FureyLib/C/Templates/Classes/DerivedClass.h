
// Derived C Class Structure Script
// by Kyle Furey

#pragma once
#include "BaseClass.h"

// Include this heading to use the class
#include "DerivedClass.h"

// Retrieves the base class of the given class.
#define super(class) class.base


// DERIVED CLASS

// Forward declaration of Derived Class
typedef class DerivedClass DerivedClass;

// Template for a derived class structure in C.
class DerivedClass
{
	// BASE CLASS

	// The base class this class derives from
	BaseClass base;


	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New functions here


	// DESTRUCTOR

	// Properly destroys this class
	FUNCTION(void, Destruct, DerivedClass*);
};


// DERIVED CLASS FUNCTIONS

// New functions here


// DERIVED CLASS CONSTRUCTORS

void DestructDerived(DerivedClass* target);

// Default constructor:
// Returns a newly constructed instance of the given class
DerivedClass ConstructDerived()
{
	DerivedClass target;

	// Call base constructor
	target.base = ConstructBase();

	// Set destructor
	target.Destruct = &DestructDerived;

	// New constructor code here

	return target;
}

// New constructors here


// DERIVED CLASS DESTRUCTOR

// Destructor:
// Properly destroys this class
void DestructDerived(DerivedClass* target)
{
	// New destructor code here

	// Call base destructor
	DestructBase(&target->base);
}
