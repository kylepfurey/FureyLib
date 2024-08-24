
// Name
// Creator

// REQUIREMENT: MyObject.cpp

#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

// Include this heading to use the class
// #include "Boilerplate/MyObject.h"

/** Template Unreal object script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UMyObject : public UObject
{
	GENERATED_BODY()

protected:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New functions here

public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS

	/** Default constructor. */
	UMyObject();

	/** Object initializer constructor. */
	UMyObject(const FObjectInitializer& ObjectInitializer);

	// New constructors here


	// FUNCTIONS

	// New functions here
};
