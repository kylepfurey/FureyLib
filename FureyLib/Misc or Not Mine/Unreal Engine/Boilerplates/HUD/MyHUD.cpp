
// Name
// Creator

// REQUIREMENT: MyHUD.h

// Include this heading to use the class
#include "MyHUD.h"


// CONSTRUCTORS

// Default constructor.
AMyHUD::AMyHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

// New constructors here


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void AMyHUD::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();
}

// Called every frame.
void AMyHUD::Tick(float DeltaTime)
{
	// Calls the base class's function.
	Super::Tick(DeltaTime);
}


// FUNCTIONS

// New functions here