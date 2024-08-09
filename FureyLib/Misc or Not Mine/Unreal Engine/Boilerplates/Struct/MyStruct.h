
// Name
// Creator

// REQUIREMENT: MyStruct.cpp

#pragma once
#include "CoreMinimal.h"
#include "MyStruct.generated.h"

// Include this heading to use the struct
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Category")
	bool bSetting = false;

	// New variables here


	// CONSTRUCTORS

	/** Default constructor. */
	FMyStruct();

	// New constructors here


	// FUNCTIONS

	// New functions here
};
