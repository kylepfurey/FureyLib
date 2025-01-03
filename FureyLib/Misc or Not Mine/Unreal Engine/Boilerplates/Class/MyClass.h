
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

public:

	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor. */
	FMyClass();

	// New constructors here

	/** Delete copy constructor. */
	FMyClass(const FMyClass& Copied) = delete;

	/** Delete move constructor. */
	FMyClass(FMyClass&& Moved) = delete;

	/** Delete copy assignment operator. */
	FMyClass& operator=(const FMyClass& Copied) = delete;

	/** Delete move assignment operator. */
	FMyClass& operator=(FMyClass&& Moved) = delete;

	/** Destructor. */
	virtual ~FMyClass();


	// FUNCTIONS

	// New functions here
};
