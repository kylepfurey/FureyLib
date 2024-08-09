
// Name
// Creator

// REQUIREMENT: MyActor.h

// Include this heading to use the class
#include "MyActor.h"


// CONSTRUCTORS

// Default constructor.
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// New constructors here


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame.
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// FUNCTIONS

// New functions here
