
// Name
// Creator

// REQUIREMENT: MySubsystem.cpp

#pragma once
#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include "MySubsystem.generated.h"

// Include this heading to use the class
// #include "Boilerplate/MySubsystem.h"

/** Template Unreal subsystem script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UMySubsystem : public USubsystem
{
	GENERATED_BODY()

protected:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New functions here

public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS

	/** Default constructor. */
	UMySubsystem();

	// New constructors here


	// UNREAL FUNCTIONS

	/** Returns whether the subsystem should be instantiated. */
	bool ShouldCreateSubsystem(UObject* Outer) const override;

	/** Called when the subsystem is initialized. */
	void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Called when the subsystem is deinitialized. */
	void Deinitialize() override;


	// FUNCTIONS

	// New functions here
};
