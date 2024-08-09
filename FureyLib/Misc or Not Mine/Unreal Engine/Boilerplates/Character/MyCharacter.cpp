
// Name
// Creator

// REQUIREMENT: MyCharacter.h

// Include this heading to use the class
#include "MyCharacter.h"


// CONSTRUCTORS

// Default constructor.
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// New constructors here


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame.
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input.
void AMyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


// FUNCTIONS

// New functions here
