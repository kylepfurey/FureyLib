
// Name
// Creator

// REQUIREMENT: MyGameModeBase.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

// Include this heading to use the class
// #include "Boilerplate/MyGameModeBase.h"

/** Template Unreal game mode base script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API AMyGameModeBase : public AGameModeBase
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
	AMyGameModeBase();

	/** Object initializer constructor. */
	AMyGameModeBase(const FObjectInitializer& ObjectInitializer);

	// New constructors here


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;


	// FUNCTIONS

	// New functions here
};
