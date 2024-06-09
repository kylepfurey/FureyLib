
// Name
// Creator

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

// Template Unreal pawn script.
UCLASS()
class GAME_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	AMyPawn()
	{
		// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

	}

	// Copy constructor
	AMyPawn(const AMyPawn& Copied)
	{
		// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

	}

	// Move constructor
	AMyPawn(AMyPawn&& Moved) noexcept
	{
		// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

	}

	// New constructors here

	// Deconstructor
	virtual ~AMyPawn()
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
	AMyPawn& operator=(const AMyPawn& Copied)
	{
		return *this;
	}

	// Move assignment operator
	AMyPawn& operator=(AMyPawn&& Moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
