// .h
// Networked Component Script
// by Kyle Furey

// REQUIREMENT: OnlineSubsystem, NetActor.h, NetComponent.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Networking/Actor/NetActor.h"
#include "NetComponent.generated.h"

// Include this heading to use the class
// #include "Networking/Actor/NetActor.h"

/**
 * Represents a replicated scene component.
 * This acts as an opaque base class for all networked components.
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class MYGAME_API UNetComponent : public USceneComponent
{
	GENERATED_BODY()

protected:

	// REPLICATION

	/** The time in seconds before the next transform replication. */
	float TransformReplicateDelay = 0;

	/** The last known transform of this scene component. */
	FTransform LastTransform = FTransform();

	/** Sends transform data to the server. */
	UFUNCTION(Server, Unreliable)
	void ReplicateTransformToServer(FTransform NewWorldTransform);
	virtual void ReplicateTransformToServer_Implementation(FTransform NewWorldTransform);

	/** Sends transform data to each client. */
	UFUNCTION(NetMulticast, Unreliable)
	void ReplicateTransformToClients(FTransform NewWorldTransform);
	virtual void ReplicateTransformToClients_Implementation(FTransform NewWorldTransform);

public:

	// CONSTRUCTORS

	/** Default constructor. */
	UNetComponent();

	/** Object initializer constructor. */
	UNetComponent(const FObjectInitializer& ObjectInitializer);


	// UNREAL FUNCTIONS

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

	/** Called each game tick. */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// REPLICATION

	/** Returns whether this scene component's actor has authority over this scene component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Replication")
	virtual bool ActorHasAuthority();

	/** Replicates this scene component's current transform. */
	UFUNCTION(BlueprintCallable, Category = "Replication")
	virtual void ReplicateTransform();

	/** Automatically called when this scene component's transform is replicated. */
	UFUNCTION(BlueprintNativeEvent, Category = "Replication")
	void OnTransformReplicated(FTransform OldWorldTransform, FTransform NewWorldTransform);
	virtual void OnTransformReplicated_Implementation(FTransform OldWorldTransform, FTransform NewWorldTransform);
};
