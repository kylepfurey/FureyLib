
// Name
// Creator

// REQUIREMENT: MyHUD.h

// Include this heading to use the class
#include "MyHUD.h"


// CONSTRUCTORS

// Default constructor.
AMyHUD::AMyHUD()
{
	// Set this HUD to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Object initializer constructor.
AMyHUD::AMyHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this HUD to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
