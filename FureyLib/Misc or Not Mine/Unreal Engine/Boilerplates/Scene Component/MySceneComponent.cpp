
// Name
// Creator

// REQUIREMENT: MySceneComponent.h

// Include this heading to use the class
#include "MySceneComponent.h"


// CONSTRUCTORS AND DESTRUCTOR

// Default constructor
UMySceneComponent::UMySceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Copy constructor
UMySceneComponent::UMySceneComponent(const UMySceneComponent& Copied)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Move constructor
UMySceneComponent::UMySceneComponent(UMySceneComponent&& Moved) noexcept
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// New constructors here

// Destructor
virtual UMySceneComponent::~UMySceneComponent()
{

}


// FUNCTIONS

// Called when the game starts
virtual void UMySceneComponent::BeginPlay() override
{
	Super::BeginPlay();
}

// Called every frame
virtual void UMySceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// OPERATORS

// Copy assignment operator
UMySceneComponent& UMySceneComponent::operator=(const UMySceneComponent& Copied)
{
	return *this;
}

// Move assignment operator
UMySceneComponent& UMySceneComponent::operator=(UMySceneComponent&& Moved) noexcept
{
	return *this;
}
