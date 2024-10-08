
// Name
// Creator

// REQUIREMENT: MyPawn.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

// Include this heading to use the class
// #include "Boilerplate/MyPawn.h"

/** Template Unreal pawn script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API AMyPawn : public APawn
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
	AMyPawn();

	/** Object initializer constructor. */
	AMyPawn(const FObjectInitializer& ObjectInitializer);

	// New constructors here


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;

	/** Called to bind functionality to input. */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// FUNCTIONS

	// New functions here
};
