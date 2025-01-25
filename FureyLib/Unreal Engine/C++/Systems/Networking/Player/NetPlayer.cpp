// .cpp
// Networked Player Character Script
// by Kyle Furey

// REQUIREMENT: NetPlayer.h

// Include this heading to use the class
#include "Networking/Player/NetPlayer.h"


// CONSTRUCTORS

// Default constructor.
ANetPlayer::ANetPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	AActor::SetReplicates(true);

	AActor::SetReplicateMovement(true);

	bAlwaysRelevant = true;

	bOnlyRelevantToOwner = false;
}

// Object initializer constructor.
ANetPlayer::ANetPlayer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	AActor::SetReplicates(true);

	AActor::SetReplicateMovement(true);

	bAlwaysRelevant = true;

	bOnlyRelevantToOwner = false;
}
