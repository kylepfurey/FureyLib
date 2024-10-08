
// Name
// Creator

// REQUIREMENT: MyActorComponent.h

// Include this heading to use the class
#include "Boilerplate/MyActorComponent.h"


// CONSTRUCTORS

// Default constructor.
UMyActorComponent::UMyActorComponent()
{
	// Set this actor component to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}

// Object initializer constructor.
UMyActorComponent::UMyActorComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor component to be initialized when the game starts, and to be ticked every frame.
	// You can turn these features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// New constructors here


// UNREAL FUNCTIONS

// Called when the game starts.
void UMyActorComponent::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();
}

// Called every frame.
void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Calls the base class's function.
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// FUNCTIONS

// New functions here
