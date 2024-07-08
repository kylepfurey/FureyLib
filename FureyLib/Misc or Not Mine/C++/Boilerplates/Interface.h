
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

// Include this heading to use the interface
#include "Interface.h"

// Inherit from this interface to implement it

// Template interface script.
class IInterface
{
public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	IInterface()
	{

	}

	// Copy constructor
	IInterface(const IInterface& copied)
	{

	}

	// Move constructor
	IInterface(IInterface&& moved) noexcept
	{

	}

	// New constructors here

	// Deconstructor
	virtual ~IInterface()
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
	IInterface& operator=(const IInterface& copied)
	{
		return *this;
	}

	// Move assignment operator
	IInterface& operator=(IInterface&& moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
