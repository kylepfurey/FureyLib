
// Name
// Creator

#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <map>

// Only one of the union's variables may be stored at a time

// Include this heading to use the union
#include "union.h"

// Template union script.
union my_union
{
private:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New functions here

public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor.
	my_union()
	{

	}

	// Copy constructor.
	my_union(const my_union& copied)
	{

	}

	// Move constructor.
	my_union(my_union&& moved) noexcept
	{

	}

	// New constructors here

	// Destructor.
	virtual ~my_union()
	{

	}


	// FUNCTIONS

	// New functions here


	// OPERATORS

	// Copy assignment operator.
	my_union& operator=(const my_union& copied)
	{
		return *this;
	}

	// Move assignment operator.
	my_union& operator=(my_union&& moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
