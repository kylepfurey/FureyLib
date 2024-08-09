
// Name
// Creator

// REQUIREMENT: MyStruct.h

// Include this heading to use the class
#include "MyStruct.h"


// CONSTRUCTORS AND DESTRUCTOR

// Default constructor
FMyStruct::FMyStruct()
{

}

// Copy constructor
FMyStruct::FMyStruct(const FMyStruct& Copied)
{

}

// Move constructor
FMyStruct::FMyStruct(FMyStruct&& Moved) noexcept
{

}

// New constructors here

// Destructor
virtual FMyStruct::~FMyStruct()
{

}


// FUNCTIONS

// New functions here


// OPERATORS

// Copy assignment operator
FMyStruct& FMyStruct::operator=(const FMyStruct& Copied)
{
	return *this;
}

// Move assignment operator
FMyStruct& FMyStruct::operator=(FMyStruct&& Moved) noexcept
{
	return *this;
}
