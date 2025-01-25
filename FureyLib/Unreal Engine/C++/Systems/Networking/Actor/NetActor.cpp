// .cpp
// Networked Actor Script
// by Kyle Furey

// REQUIREMENT: NetActor.h

// Include this heading to use the class
#include "Networking/Actor/NetActor.h"


// CONSTRUCTORS

// Default constructor.
ANetActor::ANetActor()
{
	PrimaryActorTick.bCanEverTick = true;

	AActor::SetReplicates(true);

	AActor::SetReplicateMovement(true);

	bAlwaysRelevant = true;

	bOnlyRelevantToOwner = false;
}

// Object initializer constructor.
ANetActor::ANetActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	AActor::SetReplicates(true);

	AActor::SetReplicateMovement(true);

	bAlwaysRelevant = true;

	bOnlyRelevantToOwner = false;
}
