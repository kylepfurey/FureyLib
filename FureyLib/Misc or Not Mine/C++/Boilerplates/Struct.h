
// Name
// Creator

#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <map>

// Include this heading to use the structure
#include "Struct.h"

// Template structure script.
struct Struct
{
public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	Struct()
	{

	}

	// Copy constructor
	Struct(const Struct& copied)
	{

	}

	// Move constructor
	Struct(Struct&& moved) noexcept
	{

	}

	// New constructors here

	// Deconstructor
	virtual ~Struct()
	{

	}


	// FUNCTIONS

	// New functions here


	// OPERATORS

	// Copy assignment operator
	Struct& operator=(const Struct& copied)
	{
		return *this;
	}

	// Move assignment operator
	Struct& operator=(Struct&& moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
