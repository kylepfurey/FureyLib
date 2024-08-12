
// Name
// Creator

// REQUIREMENT: struct.cpp

#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <map>

// Include this heading to use the struct
#include "struct.h"

// Template structure script.
struct my_struct
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
	my_struct();

	// Copy constructor.
	my_struct(const my_struct& copied);

	// Move constructor.
	my_struct(my_struct&& moved) noexcept;

	// New constructors here

	// Destructor.
	virtual ~my_struct();


	// FUNCTIONS

	// New functions here


	// OPERATORS

	// Copy assignment operator.
	my_struct& operator=(const my_struct& copied)
	{
		return *this;
	}

	// Move assignment operator.
	my_struct& operator=(my_struct&& moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
