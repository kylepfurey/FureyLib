
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
struct MYGAME_API FMyStruct
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


	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor. */
	FMyStruct();

	// New constructors here

	/** Destructor. */
	virtual ~FMyStruct();


	// FUNCTIONS

	// New functions here
};
