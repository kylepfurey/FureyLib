// .h
// Networked Actor Script
// by Kyle Furey

// REQUIREMENT: OnlineSubsystem, ClientState.h, NetActor.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Networking/Client/ClientState.h"
#include "NetActor.generated.h"

// Include this heading to use the class
// #include "Networking/Actor/NetActor.h"

/**
 * Represents a replicated pawn.
 * This acts as an opaque base class for all networked actors.
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class MYGAME_API ANetActor : public APawn
{
	GENERATED_BODY()

public:

	// CONSTRUCTORS

	/** Default constructor. */
	ANetActor();

	/** Object initializer constructor. */
	ANetActor(const FObjectInitializer& ObjectInitializer);
};
