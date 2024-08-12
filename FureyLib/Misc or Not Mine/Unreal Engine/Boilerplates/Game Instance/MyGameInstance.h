
// Name
// Creator

// REQUIREMENT: MyGameInstance.cpp

#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

// Include this heading to use the class
// #include "MyGameInstance.h"

/** Template Unreal game instance script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UMyGameInstance : public UGameInstance
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
	UMyGameInstance(const FObjectInitializer& ObjectInitializer);

	// New constructors here


	// FUNCTIONS

	// New functions here
};
