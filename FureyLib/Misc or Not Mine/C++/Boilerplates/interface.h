
// Name
// Creator

#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>

// Include this heading to use the interface
#include "interface.h"

// Inherit from this interface to implement it

// Template interface script.
class my_interface
{
public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	my_interface()
	{

	}

	// Copy constructor
	my_interface(const my_interface& copied)
	{

	}

	// Move constructor
	my_interface(my_interface&& moved) noexcept
	{

	}

	// New constructors here

	// Deconstructor
	virtual ~my_interface()
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
	my_interface& operator=(const my_interface& copied)
	{
		return *this;
	}

	// Move assignment operator
	my_interface& operator=(my_interface&& moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
