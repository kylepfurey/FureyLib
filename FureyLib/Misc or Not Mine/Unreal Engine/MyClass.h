
// Name
// Creator

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"

// Include this heading to use the class
#include "MyClass.h"

// Template Unreal class script.
class GAME_API MyClass
{
public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	MyClass()
	{

	}

	// Copy constructor
	MyClass(const MyClass& Copied)
	{

	}

	// Move constructor
	MyClass(MyClass&& Moved) noexcept
	{

	}

	// New constructors here

	// Deconstructor
	virtual ~MyClass()
	{

	}


	// FUNCTIONS

	// New functions here


	// OPERATORS

	// Copy assignment operator
	MyClass& operator=(const MyClass& Copied)
	{
		return *this;
	}

	// Move assignment operator
	MyClass& operator=(MyClass&& Moved) noexcept
	{
		return *this;
	}

	// New overloaded operators here
};
