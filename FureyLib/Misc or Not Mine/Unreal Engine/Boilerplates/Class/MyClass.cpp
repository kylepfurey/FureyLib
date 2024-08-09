
// Name
// Creator

// REQUIREMENT: MyClass.h

// Include this heading to use the class
#include "MyClass.h"


// CONSTRUCTORS AND DESTRUCTOR

// Default constructor
MyClass::MyClass()
{

}

// Copy constructor
MyClass::MyClass(const MyClass& Copied)
{

}

// Move constructor
MyClass::MyClass(MyClass&& Moved) noexcept
{

}

// New constructors here

// Destructor
virtual MyClass::~MyClass()
{

}


// FUNCTIONS

// New functions here


// OPERATORS

// Copy assignment operator
MyClass& MyClass::operator=(const MyClass& Copied)
{
	return *this;
}

// Move assignment operator
MyClass& MyClass::operator=(MyClass&& Moved) noexcept
{
	return *this;
}
