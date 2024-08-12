
// Name
// Creator

// REQUIREMENT: MyPlayerState.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

// Include this heading to use the class
// #include "MyPlayerState.h"

/** Template Unreal player state script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	// VARIABLES

	// New variables here


	// UNREAL FUNCTIONS

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;


	// FUNCTIONS

	// New functions here

public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS

	/** Default constructor. */
	AMyPlayerState(const FObjectInitializer& ObjectInitializer);

	// New constructors here


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;


	// FUNCTIONS

	// New functions here
};
