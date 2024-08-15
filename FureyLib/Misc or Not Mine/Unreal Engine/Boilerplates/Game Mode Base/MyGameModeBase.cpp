
// Name
// Creator

// REQUIREMENT: MyGameModeBase.h

// Include this heading to use the class
#include "MyGameModeBase.h"


// CONSTRUCTORS

// Default constructor.
AMyGameModeBase::AMyGameModeBase()
{
	// Set this game mode base to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Object initializer constructor.
AMyGameModeBase::AMyGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this game mode base to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// New constructors here


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void AMyGameModeBase::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();
}

// Called every frame.
void AMyGameModeBase::Tick(float DeltaTime)
{
	// Calls the base class's function.
	Super::Tick(DeltaTime);
}


// FUNCTIONS

// New functions here
