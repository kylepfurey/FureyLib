
// Name
// Creator

// REQUIREMENT: MyCharacter.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

// Include this heading to use the class
// #include "MyCharacter.h"

/** Template Unreal character script. */
UCLASS(Blueprintable, BlueprintType)
class GAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor */
	AMyCharacter();

	/** Copy constructor */
	AMyCharacter(const AMyCharacter& Copied);

	/** Move constructor */
	AMyCharacter(AMyCharacter&& Moved) noexcept;

	// New constructors here

	/** Destructor */
	virtual ~AMyCharacter();

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
	AMyCharacter& operator=(const AMyCharacter& Copied);

	/** Move assignment operator */
	AMyCharacter& operator=(AMyCharacter&& Moved) noexcept;

	// New overloaded operators here
};
