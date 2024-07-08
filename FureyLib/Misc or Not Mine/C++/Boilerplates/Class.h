
// Name
// Creator

#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <map>

// Include this heading to use the class
#include "Class.h"

// Template class script.
class Class
{
public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	Class()
	{

	}

	// Copy constructor
	Class(const Class& copied)
	{

	}

	// Move constructor
	Class(Class&& moved) noexcept
	{

	}

	// New constructors here

	// Deconstructor
	virtual ~Class()
	{

	}


	// FUNCTIONS

	// New functions here


	// OPERATORS

	// Copy assignment operator
	Class& operator=(const Class& copied)
	{
		return *this;
	}

	// Move assignment operator
	Class& operator=(Class&& moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
