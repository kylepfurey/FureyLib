
// Name
// Creator

// REQUIREMENT: MyActor.h

// Include this heading to use the class
#include "MyActor.h"


// CONSTRUCTORS AND DESTRUCTOR

// Default constructor
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Copy constructor
AMyActor::AMyActor(const AMyActor& Copied)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Move constructor
AMyActor::AMyActor(AMyActor&& Moved) noexcept
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Destructor
virtual AMyActor::~AMyActor()
{

}


// FUNCTIONS

// Called when the game starts or when spawned
virtual void AMyActor::BeginPlay() override
{
	Super::BeginPlay();
}

// Called every frame
virtual void AMyActor::Tick(float DeltaTime) override
{
	Super::Tick(DeltaTime);
}


// OPERATORS

// Copy assignment operator
AMyActor& AMyActor::operator=(const AMyActor& Copied)
{
	return *this;
}

// Move assignment operator
AMyActor& AMyActor::operator=(AMyActor&& Moved) noexcept
{
	return *this;
}
