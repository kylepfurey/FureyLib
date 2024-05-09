
// Name
// Creator

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"

// Include this heading to use the class
#include "MyActorComponent.h"

// Template Unreal actor component script.
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAME_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	UMyActorComponent()
	{
		// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
		// off to improve performance if you don't need them.
		PrimaryComponentTick.bCanEverTick = true;

	}

	// Copy constructor
	UMyActorComponent(const UMyActorComponent& Copied)
	{
		// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
		// off to improve performance if you don't need them.
		PrimaryComponentTick.bCanEverTick = true;

	}

	// Move constructor
	UMyActorComponent(UMyActorComponent&& Moved) noexcept
	{
		// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
		// off to improve performance if you don't need them.
		PrimaryComponentTick.bCanEverTick = true;

	}

	// New constructors here

	// Deconstructor
	virtual ~UMyActorComponent()
	{

	}

protected:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	// Called when the game starts
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override
	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	}

	// New functions here


	// OPERATORS

	// Copy assignment operator
	UMyActorComponent& operator=(const UMyActorComponent& Copied)
	{
		return *this;
	}

	// Move assignment operator
	UMyActorComponent& operator=(UMyActorComponent&& Moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
