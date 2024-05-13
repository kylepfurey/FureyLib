
// Name
// Creator

#pragma once
#include <iostream>
#include <string>
#include <vector>

// Inherit from this interface to implement it

// Include this heading to use the interface
#include "Interface.h"

// Template interface script.
class Interface
{
public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	Interface()
	{

	}

	// Copy constructor
	Interface(const Interface& copied)
	{

	}

	// Move constructor
	Interface(Interface&& moved) noexcept
	{

	}

	// New constructors here

	// Deconstructor
	virtual ~Interface()
	{

	}


	// FUNCTIONS

	// Contracted function
	virtual void Function()
	{

	}

	// New functions here


	// OPERATORS

	// Copy assignment operator
	Interface& operator=(const Interface& copied)
	{
		return *this;
	}

	// Move assignment operator
	Interface& operator=(Interface&& moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
