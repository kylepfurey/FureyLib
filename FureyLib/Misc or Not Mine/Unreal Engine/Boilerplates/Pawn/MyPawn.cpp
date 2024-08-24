
// Name
// Creator

// REQUIREMENT: MyPawn.h

// Include this heading to use the class
#include "Boilerplate/MyPawn.h"


// CONSTRUCTORS

// Default constructor.
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Object initializer constructor.
AMyPawn::AMyPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// New constructors here


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void AMyPawn::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();
}

// Called every frame.
void AMyPawn::Tick(float DeltaTime)
{
	// Calls the base class's function.
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input.
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Calls the base class's function.
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


// FUNCTIONS

// New functions here
