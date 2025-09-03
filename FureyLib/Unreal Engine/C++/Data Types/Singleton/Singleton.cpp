// .cpp
// Singleton Subsystem Base Class
// by Kyle Furey

#include "Singleton.h"


// EVENTS

// Returns whether the subsystem should be instantiated.
bool USingleton::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && ShouldCreateSingleton();
}

// Returns whether the singleton should be instantiated.
bool USingleton::ShouldCreateSingleton_Implementation() const
{
	return !GetClass()->HasAnyClassFlags(CLASS_Abstract);
}

// Initializes the subsystem.
void USingleton::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	OnInitialize();
}

// Initializes the singleton.
void USingleton::OnInitialize_Implementation() {}

// Cleans up the subsystem.
void USingleton::Deinitialize()
{
	OnDeinitialize();
	Super::Deinitialize();
}

// Cleans up the singleton.
void USingleton::OnDeinitialize_Implementation() {}
