
// Name
// Creator

// REQUIREMENT: MyPawn.h

// Include this heading to use the class
#include "MyPawn.h"


// CONSTRUCTOR

// Default constructor.
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
virtual void AMyPawn::BeginPlay() override
{
	Super::BeginPlay();
}

// Called every frame.
virtual void AMyPawn::Tick(float DeltaTime) override
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input.
virtual void AMyPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


// FUNCTIONS

// New functions here
