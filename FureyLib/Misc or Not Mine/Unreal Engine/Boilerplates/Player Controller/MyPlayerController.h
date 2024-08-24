
// Name
// Creator

// REQUIREMENT: MyPlayerController.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

// Include this heading to use the class
// #include "Boilerplate/MyPlayerController.h"

/** Template Unreal player controller script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API AMyPlayerController : public APlayerController
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
	AMyPlayerController();

	/** Object initializer constructor. */
	AMyPlayerController(const FObjectInitializer& ObjectInitializer);

	// New constructors here


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;


	// FUNCTIONS

	// New functions here
};
