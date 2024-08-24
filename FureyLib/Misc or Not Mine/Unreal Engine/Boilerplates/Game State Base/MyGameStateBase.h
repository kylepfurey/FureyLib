
// Name
// Creator

// REQUIREMENT: MyGameStateBase.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

// Include this heading to use the class
// #include "Boilerplate/MyGameStateBase.h"

/** Template Unreal game state base script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API AMyGameStateBase : public AGameStateBase
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
	AMyGameStateBase();

	/** Object initializer constructor. */
	AMyGameStateBase(const FObjectInitializer& ObjectInitializer);

	// New constructors here


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;


	// FUNCTIONS

	// New functions here
};
