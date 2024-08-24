
// Name
// Creator

// REQUIREMENT: MyClass.cpp

#pragma once
#include "CoreMinimal.h"

// Include this heading to use the class
// #include "Boilerplate/MyClass.h"

/** Template Unreal class script. */
class MYGAME_API FMyClass
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
	FMyClass();

	/** Copy constructor. */
	FMyClass(const FMyClass& Copied);

	/** Move constructor. */
	FMyClass(FMyClass&& Moved) noexcept;

	// New constructors here

	/** Destructor. */
	virtual ~FMyClass();


	// FUNCTIONS

	// New functions here


	// OPERATORS

	/** Copy assignment operator. */
	FMyClass& operator=(const FMyClass& Copied)
	{
		return *this;
	}

	/** Move assignment operator. */
	FMyClass& operator=(FMyClass&& Moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
