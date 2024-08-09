
// Name
// Creator

// REQUIREMENT: MyStruct.cpp

#pragma once
#include "CoreMinimal.h"

// Include this heading to use the class
// #include "MyStruct.h"

/** Template Unreal structure script. */
USTRUCT(BlueprintType)
struct GAME_API FMyStruct
{
	GENERATED_BODY()

public:

	// VARIABLES

	/** Example setting */
	UPROPERTY(BlueprintReadWrite)
	bool setting = false;

	// New variables here


	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor */
	FMyStruct();

	/** Copy constructor */
	FMyStruct(const FMyStruct& Copied);

	/** Move constructor */
	FMyStruct(FMyStruct&& Moved) noexcept;

	// New constructors here

	/** Destructor */
	virtual ~FMyStruct();


	// FUNCTIONS

	// New functions here


	// OPERATORS

	/** Copy assignment operator */
	FMyStruct& operator=(const FMyStruct& Copied);

	/** Move assignment operator */
	FMyStruct& operator=(FMyStruct&& Moved) noexcept;

	// New overloaded operators here
};
