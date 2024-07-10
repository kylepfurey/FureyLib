
// Name
// Creator

#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>

// Include this heading to use the class
#include "class.h"

// Template class script.
class my_class
{
public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	my_class()
	{

	}

	// Copy constructor
	my_class(const my_class& copied)
	{

	}

	// Move constructor
	my_class(my_class&& moved) noexcept
	{

	}

	// New constructors here

	// Deconstructor
	virtual ~my_class()
	{

	}


	// FUNCTIONS

	// New functions here


	// OPERATORS

	// Copy assignment operator
	my_class& operator=(const my_class& copied)
	{
		return *this;
	}

	// Move assignment operator
	my_class& operator=(my_class&& moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
