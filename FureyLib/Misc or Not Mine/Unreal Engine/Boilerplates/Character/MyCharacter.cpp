
// Name
// Creator

// REQUIREMENT: MyCharacter.h

// Include this heading to use the class
#include "MyCharacter.h"


// CONSTRUCTOR

// Default constructor.
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
virtual void AMyCharacter::BeginPlay() override
{
	Super::BeginPlay();
}

// Called every frame.
virtual void AMyCharacter::Tick(float DeltaTime) override
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input.
virtual void AMyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


// FUNCTIONS

// New functions here
