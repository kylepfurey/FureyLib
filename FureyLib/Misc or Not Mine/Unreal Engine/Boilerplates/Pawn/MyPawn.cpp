
// Name
// Creator

// REQUIREMENT: MyPawn.h

// Include this heading to use the class
#include "MyPawn.h"


// CONSTRUCTORS AND DESTRUCTOR

// Default constructor
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Copy constructor
AMyPawn::AMyPawn(const AMyPawn& Copied)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Move constructor
AMyPawn::AMyPawn(AMyPawn&& Moved) noexcept
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// New constructors here

// Destructor
virtual AMyPawn::~AMyPawn()
{

}


// FUNCTIONS

// Called when the game starts or when spawned
virtual void AMyPawn::BeginPlay() override
{
	Super::BeginPlay();
}


// FUNCTIONS

// Called every frame
virtual void AMyPawn::Tick(float DeltaTime) override
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
virtual void AMyPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


// OPERATORS

// Copy assignment operator
AMyPawn& AMyPawn::operator=(const AMyPawn& Copied)
{
	return *this;
}

// Move assignment operator
AMyPawn& AMyPawn::operator=(AMyPawn&& Moved) noexcept
{
	return *this;
}
