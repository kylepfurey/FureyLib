
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

public:

	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor */
	AMyPawn();

	/** Copy constructor */
	AMyPawn(const AMyPawn& Copied);

	/** Move constructor */
	AMyPawn(AMyPawn&& Moved) noexcept;

	// New constructors here

	/** Destructor */
	virtual ~AMyPawn();

protected:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	// New functions here

public:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// New functions here


	// OPERATORS

	/** Copy assignment operator */
	AMyPawn& operator=(const AMyPawn& Copied);

	/** Move assignment operator */
	AMyPawn& operator=(AMyPawn&& Moved) noexcept;

	// New overloaded operators here
};
