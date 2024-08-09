
// Name
// Creator

// REQUIREMENT: MyActorComponent.h

// Include this heading to use the class
#include "MyActorComponent.h"


// CONSTRUCTOR

// Default constructor.
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// UNREAL FUNCTIONS

// Called when the game starts.
virtual void UMyActorComponent::BeginPlay() override
{
	Super::BeginPlay();
}

// Called every frame.
virtual void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// FUNCTIONS

// New functions here
