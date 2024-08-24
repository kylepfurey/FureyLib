
// Name
// Creator

// REQUIREMENT: MyGameStateBase.h

// Include this heading to use the class
#include "Boilerplate/MyGameStateBase.h"


// CONSTRUCTORS

// Default constructor.
AMyGameStateBase::AMyGameStateBase()
{
	// Set this game state base to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Object initializer constructor.
AMyGameStateBase::AMyGameStateBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this game state base to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// New constructors here


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void AMyGameStateBase::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();
}

// Called every frame.
void AMyGameStateBase::Tick(float DeltaTime)
{
	// Calls the base class's function.
	Super::Tick(DeltaTime);
}


// FUNCTIONS

// New functions here
