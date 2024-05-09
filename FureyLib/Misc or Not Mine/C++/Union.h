
// Name
// Creator

#pragma once
#include <iostream>
#include <string>
#include <vector>

// Only one of the union's variables may be stored at a time

// Include this heading to use the class
#include "Union.h"

// Template union script.
union Union
{
public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	Union()
	{

	}

	// Copy constructor
	Union(const Union& copied)
	{

	}

	// Move constructor
	Union(Union&& moved) noexcept
	{

	}

	// New constructors here

	// Deconstructor
	~Union()
	{

	}


	// FUNCTIONS

	// New functions here


	// OPERATORS

	// Copy assignment operator
	Union& operator=(const Union& copied)
	{
		return *this;
	}

	// Move assignment operator
	Union& operator=(Union&& moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
