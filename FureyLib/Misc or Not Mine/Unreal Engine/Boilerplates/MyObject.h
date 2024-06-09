
// Name
// Creator

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

// Template Unreal object script.
UCLASS()
class GAME_API UMyObject : public UObject
{
	GENERATED_BODY()

public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	UMyObject()
	{

	}

	// Copy constructor
	UMyObject(const UMyObject& Copied)
	{

	}

	// Move constructor
	UMyObject(UMyObject&& Moved) noexcept
	{

	}

	// New constructors here

	// Deconstructor
	virtual ~UMyObject()
	{

	}


	// FUNCTIONS

	// New functions here


	// OPERATORS

	// Copy assignment operator
	UMyObject& operator=(const UMyObject& Copied)
	{
		return *this;
	}

	// Move assignment operator
	UMyObject& operator=(UMyObject&& Moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
