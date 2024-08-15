
// Name
// Creator

// REQUIREMENT: MyWorldSettings.h

// Include this heading to use the class
#include "MyWorldSettings.h"


// CONSTRUCTORS

// Default constructor.
AMyWorldSettings::AMyWorldSettings()
{
	// Set these world settings to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Object initializer constructor.
AMyWorldSettings::AMyWorldSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set these world settings to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// New constructors here


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void AMyWorldSettings::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();
}

// Called every frame.
void AMyWorldSettings::Tick(float DeltaTime)
{
	// Calls the base class's function.
	Super::Tick(DeltaTime);
}


// FUNCTIONS

// New functions here
