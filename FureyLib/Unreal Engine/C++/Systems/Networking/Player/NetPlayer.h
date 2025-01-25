// .h
// Networked Player Character Script
// by Kyle Furey

// REQUIREMENT: OnlineSubsystem, NetComponent.h, NetPlayer.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Networking/Component/NetComponent.h"
#include "NetPlayer.generated.h"

// Include this heading to use the class
// #include "Networking/Player/NetPlayer.h"

/**
 * Represents a replicated character.
 * This acts as an opaque base class for an online game's player class.
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class MYGAME_API ANetPlayer : public ACharacter
{
	GENERATED_BODY()

public:

	// CONSTRUCTORS

	/** Default constructor. */
	ANetPlayer();

	/** Object initializer constructor. */
	ANetPlayer(const FObjectInitializer& ObjectInitializer);
};
