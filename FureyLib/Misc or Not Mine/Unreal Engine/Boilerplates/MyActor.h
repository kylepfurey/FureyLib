
// Name
// Creator

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

// Template Unreal actor script.
UCLASS()
class GAME_API AMyActor : public AActor
{
	GENERATED_BODY()

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	AMyActor()
	{
		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

	}

	// Copy constructor
	AMyActor(const AMyActor& Copied)
	{
		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

	}

	// Move constructor
	AMyActor(AMyActor&& Moved) noexcept
	{
		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

	}

	// New constructors here

	// Deconstructor
	virtual ~AMyActor()
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

	// New functions here


	// OPERATORS

	// Copy assignment operator
	AMyActor& operator=(const AMyActor& Copied)
	{
		return *this;
	}

	// Move assignment operator
	AMyActor& operator=(AMyActor&& Moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
