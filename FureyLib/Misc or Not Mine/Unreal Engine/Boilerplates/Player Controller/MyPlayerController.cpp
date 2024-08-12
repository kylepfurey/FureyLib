
// Name
// Creator

// REQUIREMENT: MyPlayerController.h

// Include this heading to use the class
#include "MyPlayerController.h"


// CONSTRUCTORS

// Default constructor.
AMyPlayerController::AMyPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

// New constructors here


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void AMyPlayerController::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();
}

// Called every frame.
void AMyPlayerController::Tick(float DeltaTime)
{
	// Calls the base class's function.
	Super::Tick(DeltaTime);
}


// FUNCTIONS

// New functions here
