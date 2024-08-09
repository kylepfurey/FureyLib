
// Name
// Creator

// REQUIREMENT: MyActorComponent.h

// Include this heading to use the class
#include "MyActorComponent.h"


// CONSTRUCTORS AND DESTRUCTOR

// Default constructor
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Copy constructor
UMyActorComponent::UMyActorComponent(const UMyActorComponent& Copied)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Move constructor
UMyActorComponent::UMyActorComponent(UMyActorComponent&& Moved) noexcept
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// New constructors here

// Destructor
virtual UMyActorComponent::~UMyActorComponent()
{

}


// FUNCTIONS

// Called when the game starts
virtual void UMyActorComponent::BeginPlay() override
{
	Super::BeginPlay();
}

// Called every frame
virtual void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// OPERATORS

// Copy assignment operator
UMyActorComponent& UMyActorComponent::operator=(const UMyActorComponent& Copied)
{
	return *this;
}

// Move assignment operator
UMyActorComponent& UMyActorComponent::operator=(UMyActorComponent&& Moved) noexcept
{
	return *this;
}
