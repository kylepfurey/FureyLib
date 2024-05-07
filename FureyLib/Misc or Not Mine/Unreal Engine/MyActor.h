
// Name
// Creator

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Update the name of the actor here!
#include "MyActor.generated.h"

// Include this heading to use the class
#include "MyActor.h"

// Example Unreal Actor script.
UCLASS()
class GAME_API AMyActor : public AActor
{
	GENERATED_BODY()

public:	// Constructors and deconstructors

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	AMyActor()
	{

	}

	// New constructors here

	// Deconstructor
	~AMyActor()
	{

	}

protected:	// Protected variables and functions

	// VARIABLES

	// New variables here


	// FUNCTIONS

	// Called when the game starts or when spawned
	virtual void BeginPlay() override
	{

	}

	// New functions here

public:		// Public variables and functions

	// VARIABLES

	// New variables here


	// FUNCTIONS

	// Called every frame
	virtual void Tick(float DeltaTime) override
	{

	}

	// New functions here

private:	// Private variables and functions

	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New functions here
};
