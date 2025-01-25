// .cpp
// Networked Component Script
// by Kyle Furey

// REQUIREMENT: NetComponent.h

// Include this heading to use the class
#include "Networking/Component/NetComponent.h"


// CONSTRUCTORS

// Default constructor.
UNetComponent::UNetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = TG_PostPhysics;

	UActorComponent::SetIsReplicated(true);

	TransformReplicateDelay = 0;

	LastTransform = FTransform();
}

// Object initializer constructor.
UNetComponent::UNetComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = TG_PostPhysics;

	UActorComponent::SetIsReplicated(true);

	TransformReplicateDelay = 0;

	LastTransform = FTransform();
}


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void UNetComponent::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();

	if (ActorHasAuthority())
	{
		ReplicateTransform();
	}
}

// Called each game tick.
void UNetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Calls the base class's function.
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ActorHasAuthority())
	{
		TransformReplicateDelay -= DeltaTime;

		if (TransformReplicateDelay <= 0)
		{
			ReplicateTransform();
		}
	}
}


// REPLICATION

// Sends transform data to the server.
void UNetComponent::ReplicateTransformToServer_Implementation(FTransform NewWorldTransform)
{
	if (NewWorldTransform.IsValid())
	{
		ReplicateTransformToClients(NewWorldTransform);
	}
}

// Sends transform data to each client.
void UNetComponent::ReplicateTransformToClients_Implementation(FTransform NewWorldTransform)
{
	if (NewWorldTransform.IsValid())
	{
		SetWorldTransform(NewWorldTransform);

		OnTransformReplicated(LastTransform, NewWorldTransform);

		LastTransform = NewWorldTransform;
	}
}

// Returns whether this scene component's actor has authority over this scene component.
bool UNetComponent::ActorHasAuthority()
{
	AActor* Owner = GetAttachParentActor();

	if (IsValid(Owner))
	{
#if OWNING_CLIENT_HAS_AUTHORITY
		return Owner->GetLocalRole() == ROLE_AutonomousProxy;
#else
		return Owner->GetLocalRole() == ROLE_Authority;
#endif
	}

	return false;
}

// Replicates this scene component's transform.
void UNetComponent::ReplicateTransform()
{
	FTransform NewTransform = GetComponentTransform();

	if (ActorHasAuthority())
	{
		float Delay = 1.0f / GetAttachParentActor()->GetNetUpdateFrequency();

		TransformReplicateDelay = FMath::Min(TransformReplicateDelay + Delay, Delay);

		if (!LastTransform.Equals(NewTransform, KINDA_SMALL_NUMBER))
		{
			ReplicateTransformToServer(NewTransform);
		}
	}
}

// Automatically called when this scene component's transform is replicated.
void UNetComponent::OnTransformReplicated_Implementation(FTransform OldWorldTransform, FTransform NewWorldTransform) {}
