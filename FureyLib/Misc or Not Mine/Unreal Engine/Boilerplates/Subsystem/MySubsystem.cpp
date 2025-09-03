
// Name
// Creator

// REQUIREMENT: MySubsystem.h

// Include this heading to use the class
#include "Boilerplate/MySubsystem.h"


// CONSTRUCTORS

// Default constructor.
UMySubsystem::UMySubsystem()
{

}

// New constructors here


// UNREAL FUNCTIONS

// Returns whether the subsystem should be instantiated.
bool UMySubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}

// Called when the subsystem is initialized.
void UMySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	// Calls the base class's function.
	Super::Initialize(Collection);
}

// Called when the subsystem is deinitialized.
void UMySubsystem::Deinitialize()
{
	// Calls the base class's function.
	Super::Deinitialize();
}


// FUNCTIONS

// New functions here
