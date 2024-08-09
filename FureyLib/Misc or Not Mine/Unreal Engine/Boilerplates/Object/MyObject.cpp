
// Name
// Creator

// REQUIREMENT: MyObject.h

// Include this heading to use the class
#include "MyObject.h"


// CONSTRUCTORS AND DESTRUCTOR

// Default constructor
UMyObject::UMyObject()
{

}

// Copy constructor
UMyObject::UMyObject(const UMyObject& Copied)
{

}

// Move constructor
UMyObject::UMyObject(UMyObject&& Moved) noexcept
{

}

// New constructors here

// Destructor
virtual UMyObject::~UMyObject()
{

}


// FUNCTIONS

// New functions here


// OPERATORS

// Copy assignment operator
UMyObject& UMyObject::operator=(const UMyObject& Copied)
{
	return *this;
}

// Move assignment operator
UMyObject& UMyObject::operator=(UMyObject&& Moved) noexcept
{
	return *this;
}
