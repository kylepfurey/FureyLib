
// Name
// Creator

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

// Include this heading to use the class
#include "MyCharacter.h"

// Template Unreal character script.
UCLASS()
class GAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	AMyCharacter()
	{
		// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

	}

	// Copy constructor
	AMyCharacter(const AMyCharacter& Copied)
	{
		// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

	}

	// Move constructor
	AMyCharacter(AMyCharacter&& Moved) noexcept
	{
		// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

	}

	// New constructors here

	// Deconstructor
	~AMyCharacter()
	{

	}

protected:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	// Called when the game starts or when spawned
	virtual void BeginPlay() override
	{
		Super::BeginPlay();

	}

	// New functions here

public:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	// Called every frame
	virtual void Tick(float DeltaTime) override
	{
		Super::Tick(DeltaTime);

	}

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override
	{
		Super::SetupPlayerInputComponent(PlayerInputComponent);

	}

	// New functions here


	// OPERATORS

	// Copy assignment operator
	AMyCharacter& operator=(const AMyCharacter& Copied)
	{
		return *this;
	}

	// Move assignment operator
	AMyCharacter& operator=(AMyCharacter&& Moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
