
// Actor Partition Manager Script
// by Kyle Furey

// REQUIREMENT: PartitionManager.h

// Include this heading to use the class
#include "Partition/PartitionManager.h"


// IPARTITIONABLE FUNCTIONS

// Loads the actor when in range.
// By default: this actor stops calling the Tick() function and shows itself.
void IPartitionable::OnLoad_Implementation()
{
	AActor* Actor = Cast<AActor>(_getUObject());

	if (Actor != nullptr && Actor->PrimaryActorTick.bCanEverTick)
	{
		Actor->SetActorTickEnabled(true);

		Actor->SetActorHiddenInGame(false);
	}
}

// Unloads the actor when out of range.
// By default: this actor stops calling the Tick() function and hides itself.
void IPartitionable::OnUnload_Implementation()
{
	AActor* Actor = Cast<AActor>(_getUObject());

	if (Actor != nullptr)
	{
		Actor->SetActorTickEnabled(false);

		Actor->SetActorHiddenInGame(true);
	}
}


// CONSTRUCTORS

// Default constructor.
APartitionManager::APartitionManager()
{
	PrimaryActorTick.bCanEverTick = true;

	bActive = true;

	bUseZ = false;

	MaxDistance = 10000;

	PlayerActor = nullptr;

	PartitionedActors = TSet<AActor*>();

	NeverUnloadedActors = TSet<AActor*>();

	NeverLoadedActors = TSet<AActor*>();

	CurrentLoadedActors = TSet<AActor*>();

	CurrentUnloadedActors = TSet<AActor*>();

	bLoadOnStart = true;

	bUnloadOnStart = true;

	PrimaryActorTick.TickInterval = 0;

	bUseGridDistance = false;

	GridOrigin = FVector(0, 0, 0);

	GridSize = 1000;
}

// Object initializer constructor.
APartitionManager::APartitionManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	bActive = true;

	bUseZ = false;

	MaxDistance = 10000;

	PlayerActor = nullptr;

	PartitionedActors = TSet<AActor*>();

	NeverUnloadedActors = TSet<AActor*>();

	NeverLoadedActors = TSet<AActor*>();

	CurrentLoadedActors = TSet<AActor*>();

	CurrentUnloadedActors = TSet<AActor*>();

	bLoadOnStart = true;

	bUnloadOnStart = true;

	PrimaryActorTick.TickInterval = 0;

	bUseGridDistance = false;

	GridOrigin = FVector(0, 0, 0);

	GridSize = 1000;
}

// Partition manager constructor.
APartitionManager::APartitionManager(bool bActive, bool bUseZ, float MaxDistance, AActor* PlayerActor, TSet<AActor*> PartitionedActors, TSet<AActor*> NeverUnloadedActors, TSet<AActor*> NeverLoadedActors, bool bLoadOnStart, bool bUnloadOnStart, float _TickInterval, bool bUseGridDistance, bool bIsGridOrigin, FVector GridOrigin, float GridSize)
{
	PrimaryActorTick.bCanEverTick = true;

	this->bActive = bActive;

	this->bUseZ = bUseZ;

	this->MaxDistance = MaxDistance;

	this->PlayerActor = PlayerActor;

	this->PartitionedActors = PartitionedActors;

	this->NeverUnloadedActors = NeverUnloadedActors;

	this->NeverLoadedActors = NeverLoadedActors;

	CurrentLoadedActors = TSet<AActor*>();

	CurrentUnloadedActors = TSet<AActor*>();

	this->bLoadOnStart = bLoadOnStart;

	this->bUnloadOnStart = bUnloadOnStart;

	PrimaryActorTick.TickInterval = _TickInterval;

	this->bUseGridDistance = bUseGridDistance;

	this->bIsGridOrigin = bIsGridOrigin;

	this->GridOrigin = bIsGridOrigin ? GetActorLocation() : GridOrigin;

	this->GridSize = GridSize;
}


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void APartitionManager::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();

	// Check for an existing partition manager.
	if (Instance == nullptr)
	{
		// Store the current instance of the partition manager.
		Instance = this;

		// Tick only after physics update.
		PrimaryActorTick.TickGroup = ETickingGroup::TG_DuringPhysics;

		// Loads actors on start.
		if (bLoadOnStart)
		{
			for (AActor* Actor : PartitionedActors)
			{
				if ((IsWithinDistanceOfPlayer(Actor) && !NeverLoadedActors.Contains(Actor)) || NeverUnloadedActors.Contains(Actor))
				{
					LoadPartitionActor(Actor);
				}
			}
		}

		// Unloads actors on start.
		if (bUnloadOnStart)
		{
			for (AActor* Actor : PartitionedActors)
			{
				if ((!IsWithinDistanceOfPlayer(Actor) && !NeverUnloadedActors.Contains(Actor)) || NeverLoadedActors.Contains(Actor))
				{
					UnloadPartitionActor(Actor);
				}
			}
		}
	}
	else
	{
		// Remove this actor as it is not needed.
		Destroy();
	}
}

// Called when the actor is destroyed.
void APartitionManager::BeginDestroy()
{
	// Calls the base class's function.
	Super::BeginDestroy();

	// Check for an existing partition manager.
	if (Instance == this)
	{
		// Remove the current instance of the partition manager.
		Instance = nullptr;
	}
}

// Called every frame.
void APartitionManager::Tick(float DeltaTime)
{
	// Calls the base class's function.
	Super::Tick(DeltaTime);

	// Check if the partition is enabled.
	if (bActive)
	{
		// Check for deleted actors.
		for (AActor* Actor : PartitionedActors)
		{
			if (!IsValid(Actor))
			{
				PartitionedActors.Remove(Actor);

				CurrentLoadedActors.Remove(Actor);

				CurrentUnloadedActors.Remove(Actor);

				NeverUnloadedActors.Remove(Actor);

				NeverLoadedActors.Remove(Actor);
			}
		}

		// Updates loaded actors.
		for (AActor* Actor : CurrentUnloadedActors)
		{
			if (IsWithinDistanceOfPlayer(Actor) && !NeverLoadedActors.Contains(Actor))
			{
				LoadPartitionActor(Actor);
			}
		}

		// Updates unloaded actors.
		for (AActor* Actor : CurrentLoadedActors)
		{
			if (!IsWithinDistanceOfPlayer(Actor) && !NeverUnloadedActors.Contains(Actor))
			{
				UnloadPartitionActor(Actor);
			}
		}

		// Final partition check.
		for (AActor* Actor : PartitionedActors)
		{
			if (!CurrentLoadedActors.Contains(Actor) && !NeverLoadedActors.Contains(Actor) && (IsWithinDistanceOfPlayer(Actor) || NeverUnloadedActors.Contains(Actor)))
			{
				LoadPartitionActor(Actor);
			}
			else if (!CurrentUnloadedActors.Contains(Actor) && !NeverUnloadedActors.Contains(Actor) && (!IsWithinDistanceOfPlayer(Actor) || NeverLoadedActors.Contains(Actor)))
			{
				UnloadPartitionActor(Actor);
			}
		}
	}
}


// GETTERS

// Returns whether this world has a partition manager.
bool APartitionManager::PartitionExists()
{
	return Instance != nullptr;
}

// Returns the current instance of the partition manager.
APartitionManager* APartitionManager::GetPartitionManager()
{
	return Instance;
}

// Returns whether the partition manager is active.
bool APartitionManager::IsPartitionActive()
{
	if (Instance == nullptr)
	{
		return false;
	}

	return Instance->bActive;
}

// Returns whether the Z axis (up) is used in partitioning.
bool APartitionManager::DoesPartitionUseZ()
{
	if (Instance == nullptr)
	{
		return false;
	}

	return Instance->bUseZ;
}

// Returns the distance before actors are partitioned.
float APartitionManager::GetPartitionMaxDistance()
{
	if (Instance == nullptr)
	{
		return 0;
	}

	return Instance->MaxDistance;
}

// Returns the player actor used for distance calculations in partitioning.
AActor* APartitionManager::GetPlayer()
{
	if (Instance == nullptr)
	{
		return nullptr;
	}

	return Instance->PlayerActor;
}

// Returns the current actors in partitioning.
TSet<AActor*> APartitionManager::GetPartitionedActors()
{
	if (Instance == nullptr)
	{
		return TSet<AActor*>();
	}

	return Instance->PartitionedActors;
}

// Returns actors never to be unloaded in partitioning.
TSet<AActor*> APartitionManager::GetNeverUnloadedActors()
{
	if (Instance == nullptr)
	{
		return TSet<AActor*>();
	}

	return Instance->NeverUnloadedActors;
}

// Returns actors never to be loaded in partitioning.
TSet<AActor*> APartitionManager::GetNeverLoadedActors()
{
	if (Instance == nullptr)
	{
		return TSet<AActor*>();
	}

	return Instance->NeverLoadedActors;
}

// Returns actors currently unloaded in partitioning.
TSet<AActor*> APartitionManager::GetUnloadedActors()
{
	if (Instance == nullptr)
	{
		return TSet<AActor*>();
	}

	return TSet<AActor*>(Instance->CurrentUnloadedActors);
}

// Returns actors currently loaded in partitioning.
TSet<AActor*> APartitionManager::GetLoadedActors()
{
	if (Instance == nullptr)
	{
		return TSet<AActor*>();
	}

	return TSet<AActor*>(Instance->CurrentLoadedActors);
}

// Returns the origin point used in grid space.
FVector APartitionManager::GetGridOrigin()
{
	if (Instance == nullptr)
	{
		return FVector(0, 0, 0);
	}

	return Instance->GridOrigin;
}

// Returns whether objects were loaded on start.
float APartitionManager::GetGridSize()
{
	if (Instance == nullptr)
	{
		return 0;
	}

	return Instance->GridSize;
}

// Returns whether objects were loaded on start.
bool APartitionManager::WereActorsLoadedOnStart()
{
	if (Instance == nullptr)
	{
		return false;
	}

	return Instance->bLoadOnStart;
}

// Returns whether objects were unloaded on start.
bool APartitionManager::WereActorsUnloadedOnStart()
{
	if (Instance == nullptr)
	{
		return false;
	}

	return Instance->bUnloadOnStart;
}

// Returns whether the partition manager is the origin of the grid.
bool APartitionManager::IsPartitionManagerGridOrigin()
{
	if (Instance == nullptr)
	{
		return false;
	}

	return Instance->GetActorLocation() == Instance->GridOrigin;
}

// Returns the tick interval of the partition manager.
float APartitionManager::GetPartitionTickInterval()
{
	if (Instance == nullptr)
	{
		return 0;
	}

	return Instance->PrimaryActorTick.TickInterval;
}


// SETTERS

// Sets whether the partition manager is active.
void APartitionManager::SetPartitionActive(bool _bActive)
{
	if (Instance == nullptr)
	{
		return;
	}

	Instance->bActive = _bActive;
}

// Sets whether the Z axis (up) is used in partitioning.
void APartitionManager::SetPartitionUsesZ(bool _bUseZ)
{
	if (Instance == nullptr)
	{
		return;
	}

	Instance->bUseZ = _bUseZ;
}

// Sets the distance before actors are partitioned.
void APartitionManager::SetPartitionMaxDistance(float _MaxDistance)
{
	if (Instance == nullptr)
	{
		return;
	}

	Instance->MaxDistance = _MaxDistance;
}

// Sets the player actor used for distance calculations in partitioning.
void APartitionManager::SetPartitionPlayer(AActor* _PlayerActor)
{
	if (Instance == nullptr)
	{
		return;
	}

	Instance->PlayerActor = _PlayerActor;
}

// Sets the origin point used in grid space.
void APartitionManager::SetGridOrigin(FVector _GridOrigin)
{
	if (Instance == nullptr)
	{
		return;
	}

	Instance->GridOrigin = _GridOrigin;

	Instance->bIsGridOrigin = Instance->GetActorLocation() == _GridOrigin;
}

// Sets the grid size used in grid space.
void APartitionManager::SetGridSize(float _GridSize)
{
	if (Instance == nullptr)
	{
		return;
	}

	Instance->GridSize = _GridSize;
}

// Sets the partition manager's location as the grid origin.
void APartitionManager::SetPartitionManagerAsGridOrigin()
{
	if (Instance == nullptr)
	{
		return;
	}

	Instance->GridOrigin = Instance->GetActorLocation();

	Instance->bIsGridOrigin = true;
}

// Sets the tick interval of the partition manager.
void APartitionManager::SetPartitionTickInterval(float _TickInterval)
{
	if (Instance == nullptr)
	{
		return;
	}

	Instance->PrimaryActorTick.TickInterval = _TickInterval;
}


// LOADING AND UNLOADING FUNCTIONS

// Returns if the given actor is loaded.
bool APartitionManager::IsPartitionLoaded(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	return Instance->CurrentLoadedActors.Contains(Actor);
}

// Loads an actor using the IPartitionable interface.
// Returns whether the actor was loaded using the interface (true) or by default (false).
bool APartitionManager::LoadPartitionActor(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	Instance->CurrentUnloadedActors.Remove(Actor);

	Instance->CurrentLoadedActors.Add(Actor);

	IPartitionable* Partition = Cast<IPartitionable>(Actor);

	if (Partition == nullptr)
	{
		if (Actor->PrimaryActorTick.bCanEverTick)
		{
			Actor->SetActorTickEnabled(true);

			Actor->SetActorHiddenInGame(false);
		}

		return false;
	}
	else
	{
		Partition->Execute_OnLoad(Partition->_getUObject());

		return true;
	}
}

// Returns if the given actor is unloaded.
bool APartitionManager::IsPartitionUnloaded(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	return Instance->CurrentUnloadedActors.Contains(Actor);
}

// Unloads an actor using the IPartitionable interface.
// Returns whether the actor was unloaded using the interface (true) or by default (false).
bool APartitionManager::UnloadPartitionActor(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	Instance->CurrentLoadedActors.Remove(Actor);

	Instance->CurrentUnloadedActors.Add(Actor);

	IPartitionable* Partition = Cast<IPartitionable>(Actor);

	if (Partition == nullptr)
	{
		Actor->SetActorTickEnabled(false);

		Actor->SetActorHiddenInGame(true);

		return false;
	}
	else
	{
		Partition->Execute_OnUnload(Partition->_getUObject());

		return true;
	}
}


// PARTITION FUNCTIONS

// Returns whether the given actor is within the maximum distance of the player actor.
bool APartitionManager::IsWithinDistanceOfPlayer(AActor* Actor)
{
	if (Instance == nullptr || Instance->PlayerActor == nullptr || Actor == nullptr)
	{
		return false;
	}

	if (Instance->bUseGridDistance)
	{
		FVector Left;

		FVector2D Left2D;

		GetGridSpace(Instance->PlayerActor, Left, Left2D);

		FVector Right;

		FVector2D Right2D;

		GetGridSpace(Actor, Right, Right2D);

		return (Instance->bUseZ ? FVector::DistSquared(Left, Right) : FVector2D::DistSquared(Left2D, Right2D)) <= ((int32)(Instance->MaxDistance * Instance->MaxDistance));

	}
	else
	{
		FVector Left = Instance->PlayerActor->GetActorLocation();

		FVector Right = Actor->GetActorLocation();

		return (Instance->bUseZ ? FVector::DistSquared(Left, Right) : FVector2D::DistSquared(FVector2D(Left.X, Left.Y), FVector2D(Right.X, Right.Y))) <= (Instance->MaxDistance * Instance->MaxDistance);
	}
}

// Returns if the given actor is partitioned.
bool APartitionManager::IsPartitioned(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	return Instance->PartitionedActors.Contains(Actor);
}

// Marks the actor for partitioning and returns if it was successful.
bool APartitionManager::MarkPartitioned(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	if (Instance->PartitionedActors.Contains(Actor))
	{
		return false;
	}
	else
	{
		Instance->PartitionedActors.Add(Actor);

		return true;
	}
}

// Unmarks the actor for partitioning and returns if it was successful.
bool APartitionManager::UnmarkPartitioned(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	if (Instance->PartitionedActors.Contains(Actor))
	{
		Instance->CurrentLoadedActors.Remove(Actor);

		Instance->CurrentUnloadedActors.Remove(Actor);

		Instance->PartitionedActors.Remove(Actor);

		return true;
	}
	else
	{
		return false;
	}
}

// Returns if the given actor is never unloaded.
bool APartitionManager::IsPartitionNeverUnloaded(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	return Instance->NeverUnloadedActors.Contains(Actor);
}

// Never unloads the given actor and returns if it was successful.
bool APartitionManager::NeverUnloadPartition(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	if (Instance->NeverUnloadedActors.Contains(Actor))
	{
		return false;
	}
	else
	{
		LoadNormally(Actor);

		Instance->NeverUnloadedActors.Add(Actor);

		return true;
	}
}

// Returns if the given actor is never loaded.
bool APartitionManager::IsPartitionNeverLoaded(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	return Instance->NeverLoadedActors.Contains(Actor);
}

// Never loads the given actor and returns if it was successful.
bool APartitionManager::NeverLoadPartition(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	if (Instance->NeverLoadedActors.Contains(Actor))
	{
		return false;
	}
	else
	{
		LoadNormally(Actor);

		Instance->NeverLoadedActors.Add(Actor);

		return true;
	}
}

// Partitions the given actor normally and returns if it was successful.
bool APartitionManager::LoadNormally(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	bool Success = false;

	if (Instance->NeverLoadedActors.Contains(Actor))
	{
		Instance->NeverLoadedActors.Remove(Actor);

		Success = true;
	}

	if (Instance->NeverUnloadedActors.Contains(Actor))
	{
		Instance->NeverUnloadedActors.Remove(Actor);

		Success = true;
	}

	return Success;
}


// GRID FUNCTIONS

// Returns whether grid space is used as distance in partitioning.
bool APartitionManager::DoesPartitionUseGridDistance()
{
	if (Instance == nullptr)
	{
		return false;
	}

	return Instance->bUseGridDistance;
}

// Sets whether grid space is used as distance in partitioning.
void APartitionManager::SetPartitionUsesGridDistance(bool _bUseGridDistance)
{
	if (Instance == nullptr)
	{
		return;
	}

	Instance->bUseGridDistance = _bUseGridDistance;
}

// Calculates a grid space based on the given world position.
void APartitionManager::CalculateGridSpace(FVector WorldPosition, FVector& GridSpace, FVector2D& GridSpace2D)
{
	if (Instance != nullptr)
	{
		GridSpace = FVector(0, 0, 0);

		GridSpace2D = FVector2D(0, 0);

		return;
	}

	WorldPosition -= Instance->GridOrigin;

	WorldPosition /= Instance->GridSize > 0 ? Instance->GridSize : 1;

	GridSpace = FVector((int32)WorldPosition.X, (int32)WorldPosition.Y, (int32)WorldPosition.Z);

	GridSpace2D = FVector2D(GridSpace.X, GridSpace.Y);
}

// Calculates a world position based on the given grid space.
FVector APartitionManager::CalculateWorldPosition(FVector GridSpace)
{
	if (Instance != nullptr)
	{
		return FVector();
	}

	return FVector();
}

// Returns the current grid space of the given actor.
void APartitionManager::GetGridSpace(AActor* Actor, FVector& GridSpace, FVector2D& GridSpace2D)
{
	if (Instance != nullptr || Actor == nullptr)
	{
		return;
	}

	CalculateGridSpace(Actor->GetActorLocation(), GridSpace, GridSpace2D);
}

// Returns the current grid space of the player.
void APartitionManager::GetPlayerGridSpace(FVector& GridSpace, FVector2D& GridSpace2D)
{
	if (Instance != nullptr)
	{
		return;
	}

	GetGridSpace(Instance->PlayerActor, GridSpace, GridSpace2D);
}

// Returns whether the given actor is in the given grid space.
bool APartitionManager::IsInGridSpace(AActor* Actor, FVector GridSpace)
{
	FVector NewGridSpace;

	FVector2D GridSpace2D;

	GetGridSpace(Actor, NewGridSpace, GridSpace2D);

	return GridSpace == NewGridSpace;
}

// Returns the given actors that are in a given grid space.
TSet<AActor*> APartitionManager::GetActorsInGridSpace(TArray<AActor*> Actors, FVector GridSpace)
{
	TSet<AActor*> NewActors = TSet<AActor*>();

	for (AActor* Actor : Actors)
	{
		if (IsInGridSpace(Actor, GridSpace))
		{
			NewActors.Add(Actor);
		}
	}

	return NewActors;
}

// Returns all of the actors that are in a given grid space.
TSet<AActor*> APartitionManager::GetAllActorsInGridSpace(FVector GridSpace)
{
	return GetActorsInGridSpace(GetAllActors(), GridSpace);
}

// Returns all of the world's current actors.
TArray<AActor*> APartitionManager::GetAllActors()
{
	TArray<AActor*> Actors;

	UGameplayStatics::GetAllActorsOfClass(GWorld, AActor::StaticClass(), Actors);

	return Actors;
}


// STATIC VARIABLE INITIALIZATION

// The current instance of the partition manager in this world.
APartitionManager* APartitionManager::Instance = nullptr;
