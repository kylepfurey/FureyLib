
// Name
// Creator

// REQUIREMENT: MyStruct.cpp

#pragma once
#include "CoreMinimal.h"
#include "MyStruct.generated.h"

// Include this heading to use the struct
// #include "Boilerplate/MyStruct.h"

/** Template Unreal structure script. */
USTRUCT(BlueprintType)
struct MYGAME_API FMyStruct final
{
	GENERATED_BODY()

public:

	// VARIABLES

	/** Example setting. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Category")
	bool bSetting = false;

	// New variables here


	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor. */
	FMyStruct();

	// New constructors here

	/** Destructor. */
	~FMyStruct();


	// FUNCTIONS

	// New functions here
};
