
// Game Manager Template Script
// by Kyle Furey

// REQUIREMENT: GameManager.h

// Include this heading to use the class
#include "Game Manager/GameManager.h"


// CONSTRUCTORS

// Default constructor.
UGameManager::UGameManager()
{
	// New code here
}

// Object initializer constructor.
UGameManager::UGameManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// New code here
}

// New constructors here


// UNREAL FUNCTIONS

// Called when the game is first initialized.
void UGameManager::Init()
{
	// Calls the base class's function.
	Super::Init();

	// New code here
}

// Called when the game's current world changes.
void UGameManager::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	// Calls the base class's function.
	Super::OnWorldChanged(OldWorld, NewWorld);

	// Call OnCurrentWorldChanged().
	OnCurrentWorldChanged(OldWorld, NewWorld);
}

// Called when the game is closed.
void UGameManager::Shutdown()
{
	// Calls the base class's function.
	Super::Shutdown();

	// New code here
}


// GAME MANAGER EVENTS

// Automatically called when the game's current world changes.
void UGameManager::OnCurrentWorldChanged_Implementation(UWorld* OldWorld, UWorld* NewWorld)
{
	// New code here
}

// New events here


// GAME MANAGER FUNCTIONS

// Retrieves the global instance of the game manager.
UGameManager* UGameManager::GetGameManager()
{
	return Cast<UGameManager>(UGameplayStatics::GetGameInstance(GWorld));
}

// Retrieves the current world.
UWorld* UGameManager::GetCurrentWorld()
{
	return GWorld;
}

// Retrieves the time in seconds since the last game tick.
float UGameManager::GetDeltaTime()
{
	return UGameplayStatics::GetWorldDeltaSeconds(GWorld);
}

// New functions here
