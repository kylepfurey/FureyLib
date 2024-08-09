
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

protected:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New functions here

public:

	// VARIABLES

	/** Example setting. */
	UPROPERTY(BlueprintReadWrite)
	bool setting = false;

	// New variables here


	// CONSTRUCTOR

	/** Default constructor. */
	FMyStruct();


	// FUNCTIONS

	// New functions here
};
