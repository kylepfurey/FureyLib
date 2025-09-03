
// Name
// Creator

// REQUIREMENT: MyGameInstanceSubsystem.cpp

#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MyGameInstanceSubsystem.generated.h"

// Include this heading to use the class
// #include "Boilerplate/MyGameInstanceSubsystem.h"

/** Template Unreal game instance subsystem script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UMyGameInstanceSubsystem : public UGameInstanceSubsystem
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
	UMyGameInstanceSubsystem();

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
