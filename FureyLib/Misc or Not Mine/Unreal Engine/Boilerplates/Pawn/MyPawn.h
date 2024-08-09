
// Name
// Creator

// REQUIREMENT: MyPawn.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

// Include this heading to use the class
// #include "MyPawn.h"

/** Template Unreal pawn script. */
UCLASS(Blueprintable, BlueprintType)
class GAME_API AMyPawn : public APawn
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


	// CONSTRUCTOR

	/** Default constructor. */
	AMyPawn();


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;

	/** Called to bind functionality to input. */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// FUNCTIONS

	// New functions here
};
