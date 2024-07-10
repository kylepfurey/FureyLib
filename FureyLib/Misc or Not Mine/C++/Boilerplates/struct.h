
// Name
// Creator

#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <map>

// Include this heading to use the structure
#include "struct.h"

// Template structure script.
struct my_structure
{
public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	my_structure()
	{

	}

	// Copy constructor
	my_structure(const my_structure& copied)
	{

	}

	// Move constructor
	my_structure(my_structure&& moved) noexcept
	{

	}

	// New constructors here

	// Deconstructor
	virtual ~my_structure()
	{

	}


	// FUNCTIONS

	// New functions here


	// OPERATORS

	// Copy assignment operator
	my_structure& operator=(const my_structure& copied)
	{
		return *this;
	}

	// Move assignment operator
	my_structure& operator=(my_structure&& moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
