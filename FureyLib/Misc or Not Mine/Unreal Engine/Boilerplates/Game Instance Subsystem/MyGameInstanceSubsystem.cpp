
// Name
// Creator

// REQUIREMENT: MyGameInstanceSubsystem.h

// Include this heading to use the class
#include "Boilerplate/MyGameInstanceSubsystem.h"


// CONSTRUCTORS

// Default constructor.
UMyGameInstanceSubsystem::UMyGameInstanceSubsystem()
{

}

// New constructors here


// UNREAL FUNCTIONS

// Returns whether the subsystem should be instantiated.
bool UMyGameInstanceSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}

// Called when the subsystem is initialized.
void UMyGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	// Calls the base class's function.
	Super::Initialize(Collection);
}

// Called when the subsystem is deinitialized.
void UMyGameInstanceSubsystem::Deinitialize()
{
	// Calls the base class's function.
	Super::Deinitialize();
}


// FUNCTIONS

// New functions here
