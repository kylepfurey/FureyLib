
// Name
// Creator

// REQUIREMENT: MyClass.cpp

#pragma once
#include "CoreMinimal.h"

// Include this heading to use the class
// #include "MyClass.h"

/** Template Unreal class script. */
class GAME_API MyClass
{
protected:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New functions here

public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor. */
	MyClass();

	/** Copy constructor. */
	MyClass(const MyClass& Copied);

	/** Move constructor. */
	MyClass(MyClass&& Moved) noexcept;

	// New constructors here

	/** Destructor. */
	virtual ~MyClass();


	// FUNCTIONS

	// New functions here


	// OPERATORS

	/** Copy assignment operator. */
	MyClass& operator=(const MyClass& Copied);

	/** Move assignment operator. */
	MyClass& operator=(MyClass&& Moved) noexcept;

	// New overloaded operators here
};
