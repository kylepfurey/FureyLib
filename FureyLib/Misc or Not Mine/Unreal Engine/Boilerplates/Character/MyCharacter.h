
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
	AMyCharacter();

	// New constructors here


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;

	/** Called to bind functionality to input. */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// FUNCTIONS

	// New functions here
};
