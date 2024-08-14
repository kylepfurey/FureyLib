
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


	// UNREAL FUNCTIONS

	/** Called when the game is first initialized. */
	virtual void Init() override;

	/** Called when the game's current world changes. */
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;

	/** Called when the game is closed. */
	virtual void Shutdown() override;


	// FUNCTIONS

	// New functions here
};
