
// Name
// Creator

// REQUIREMENT: MyPlayerCameraManager.h

// Include this heading to use the class
#include "MyPlayerCameraManager.h"


// CONSTRUCTORS

// Default constructor.
AMyPlayerCameraManager::AMyPlayerCameraManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

// New constructors here


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void AMyPlayerCameraManager::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();
}

// Called every frame.
void AMyPlayerCameraManager::Tick(float DeltaTime)
{
	// Calls the base class's function.
	Super::Tick(DeltaTime);
}


// FUNCTIONS

// New functions here
