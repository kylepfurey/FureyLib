
// Name
// Creator

// REQUIREMENT: MyGameInstance.h

// Include this heading to use the class
#include "Boilerplate/MyGameInstance.h"


// CONSTRUCTORS

// Default constructor.
UMyGameInstance::UMyGameInstance()
{

}

// Object initializer constructor.
UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

// New constructors here


// UNREAL FUNCTIONS

// Called when the game is first initialized.
void UMyGameInstance::Init()
{
	// Calls the base class's function.
	Super::Init();
}

// Called when the game's current world changes.
void UMyGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	// Calls the base class's function.
	Super::OnWorldChanged(OldWorld, NewWorld);
}

// Called when the game is closed.
void UMyGameInstance::Shutdown()
{
	// Calls the base class's function.
	Super::Shutdown();
}


// FUNCTIONS

// New functions here
