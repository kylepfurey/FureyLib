
// Name
// Creator

// REQUIREMENT: MyActor.h

// Include this heading to use the class
#include "MyActor.h"


// CONSTRUCTOR

// Default constructor.
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
virtual void AMyActor::BeginPlay() override
{
	Super::BeginPlay();
}

// Called every frame.
virtual void AMyActor::Tick(float DeltaTime) override
{
	Super::Tick(DeltaTime);
}


// FUNCTIONS

// New functions here
