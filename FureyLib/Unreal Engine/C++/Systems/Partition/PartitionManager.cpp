
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

	if (Actor != nullptr)
	{
		if (Actor->PrimaryActorTick.bCanEverTick)
		{
			Actor->SetActorTickEnabled(true);
		}

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

	PartitionedActors = TArray<AActor*>();

	NeverUnloadedActors = TSet<AActor*>();

	NeverLoadedActors = TSet<AActor*>();

	CurrentLoadedActors = TSet<AActor*>();

	CurrentUnloadedActors = TSet<AActor*>();

	bLoadOnStart = true;

	bUnloadOnStart = true;

	TickInterval = 0;

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

	PartitionedActors = TArray<AActor*>();

	NeverUnloadedActors = TSet<AActor*>();

	NeverLoadedActors = TSet<AActor*>();

	CurrentLoadedActors = TSet<AActor*>();

	CurrentUnloadedActors = TSet<AActor*>();

	bLoadOnStart = true;

	bUnloadOnStart = true;

	TickInterval = 0;

	PrimaryActorTick.TickInterval = 0;

	bUseGridDistance = false;

	GridOrigin = FVector(0, 0, 0);

	GridSize = 1000;
}

// Partition manager constructor.
APartitionManager::APartitionManager(AActor* _PlayerActor, TArray<AActor*> _PartitionedActors, TSet<AActor*> _NeverUnloadedActors, TSet<AActor*> _NeverLoadedActors, bool Active, bool UseZ, float _MaxDistance, bool LoadOnStart, bool UnloadOnStart, float _TickInterval, bool UseGridDistance, bool IsGridOrigin, FVector _GridOrigin, float _GridSize)
{
	this->PrimaryActorTick.bCanEverTick = true;

	this->bActive = Active;

	this->bUseZ = UseZ;

	this->MaxDistance = _MaxDistance;

	this->PlayerActor = _PlayerActor;

	this->PartitionedActors = _PartitionedActors;

	this->NeverUnloadedActors = _NeverUnloadedActors;

	this->NeverLoadedActors = _NeverLoadedActors;

	this->CurrentLoadedActors = TSet<AActor*>();

	this->CurrentUnloadedActors = TSet<AActor*>();

	this->bLoadOnStart = LoadOnStart;

	this->bUnloadOnStart = UnloadOnStart;

	this->TickInterval = _TickInterval;

	this->PrimaryActorTick.TickInterval = _TickInterval;

	this->bUseGridDistance = UseGridDistance;

	this->bIsGridOrigin = IsGridOrigin;

	this->GridOrigin = IsGridOrigin ? GetActorLocation() : _GridOrigin;

	this->GridSize = _GridSize;
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
					LoadActor(Actor);
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
					UnloadActor(Actor);
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
		UpdatePartition();
	}
}


// GETTERS

// Returns whether this world has a partition manager.
bool APartitionManager::PartitionManagerExists()
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
TArray<AActor*> APartitionManager::GetPartitionedActors()
{
	if (Instance == nullptr)
	{
		return TArray<AActor*>();
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
void APartitionManager::SetPartitionActive(bool Active)
{
	if (Instance == nullptr)
	{
		return;
	}

	Instance->bActive = Active;
}

// Sets whether the Z axis (up) is used in partitioning.
void APartitionManager::SetPartitionUsesZ(bool UseZ)
{
	if (Instance == nullptr)
	{
		return;
	}

	Instance->bUseZ = UseZ;
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

	Instance->TickInterval = _TickInterval;
}


// LOADING AND UNLOADING FUNCTIONS

// Updates the partition's actors' load states.
// Automatically called each tick while the partition manager is present and active.
// Returns whether the update was successful.
bool APartitionManager::UpdatePartition()
{
	if (Instance == nullptr || Instance->PlayerActor == nullptr)
	{
		return false;
	}

	// Check for deleted actors.
	for (AActor* Actor : Instance->PartitionedActors)
	{
		if (!IsValid(Actor))
		{
			Instance->PartitionedActors.Remove(Actor);

			Instance->CurrentLoadedActors.Remove(Actor);

			Instance->CurrentUnloadedActors.Remove(Actor);

			Instance->NeverUnloadedActors.Remove(Actor);

			Instance->NeverLoadedActors.Remove(Actor);
		}
	}

	// Updates loaded actors.
	for (AActor* Actor : Instance->CurrentUnloadedActors)
	{
		if (IsWithinDistanceOfPlayer(Actor) && !Instance->NeverLoadedActors.Contains(Actor))
		{
			LoadActor(Actor);
		}
	}

	// Updates unloaded actors.
	for (AActor* Actor : Instance->CurrentLoadedActors)
	{
		if (!IsWithinDistanceOfPlayer(Actor) && !Instance->NeverUnloadedActors.Contains(Actor))
		{
			UnloadActor(Actor);
		}
	}

	// Final partition check.
	for (AActor* Actor : Instance->PartitionedActors)
	{
		if (!Instance->CurrentLoadedActors.Contains(Actor) && !Instance->NeverLoadedActors.Contains(Actor) && (IsWithinDistanceOfPlayer(Actor) || Instance->NeverUnloadedActors.Contains(Actor)))
		{
			LoadActor(Actor);
		}
		else if (!Instance->CurrentUnloadedActors.Contains(Actor) && !Instance->NeverUnloadedActors.Contains(Actor) && (!IsWithinDistanceOfPlayer(Actor) || Instance->NeverLoadedActors.Contains(Actor)))
		{
			UnloadActor(Actor);
		}
	}

	return true;
}

// Returns if the given actor is loaded.
bool APartitionManager::IsActorLoaded(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	return Instance->CurrentLoadedActors.Contains(Actor);
}

// Loads an actor using the IPartitionable interface.
// Returns whether the actor was loaded using the interface (true) or by default (false).
bool APartitionManager::LoadActor(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	Instance->CurrentUnloadedActors.Remove(Actor);

	Instance->CurrentLoadedActors.Add(Actor);

	if (Actor->Implements<UPartitionable>())
	{
		IPartitionable::Execute_OnLoad(Actor);

		return true;
	}
	else
	{
		if (Actor->PrimaryActorTick.bCanEverTick)
		{
			Actor->SetActorTickEnabled(true);
		}

		Actor->SetActorHiddenInGame(false);

		return false;
	}
}

// Returns if the given actor is unloaded.
bool APartitionManager::IsActorUnloaded(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	return Instance->CurrentUnloadedActors.Contains(Actor);
}

// Unloads an actor using the IPartitionable interface.
// Returns whether the actor was unloaded using the interface (true) or by default (false).
bool APartitionManager::UnloadActor(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	Instance->CurrentLoadedActors.Remove(Actor);

	Instance->CurrentUnloadedActors.Add(Actor);

	if (Actor->Implements<UPartitionable>())
	{
		IPartitionable::Execute_OnUnload(Actor);

		return true;
	}
	else
	{
		Actor->SetActorTickEnabled(false);

		Actor->SetActorHiddenInGame(true);

		return false;
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
bool APartitionManager::IsActorNeverUnloaded(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	return Instance->NeverUnloadedActors.Contains(Actor);
}

// Never unloads the given actor and returns if it was successful.
bool APartitionManager::NeverUnloadActor(AActor* Actor)
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
		LoadActorNormally(Actor);

		Instance->NeverUnloadedActors.Add(Actor);

		return true;
	}
}

// Returns if the given actor is never loaded.
bool APartitionManager::IsActorNeverLoaded(AActor* Actor)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return false;
	}

	return Instance->NeverLoadedActors.Contains(Actor);
}

// Never loads the given actor and returns if it was successful.
bool APartitionManager::NeverLoadActor(AActor* Actor)
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
		LoadActorNormally(Actor);

		Instance->NeverLoadedActors.Add(Actor);

		return true;
	}
}

// Partitions the given actor normally and returns if it was successful.
bool APartitionManager::LoadActorNormally(AActor* Actor)
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

// Spawns a new APartitionManager actor into the world.
APartitionManager* APartitionManager::SpawnPartitionManager(FTransform SpawnTransform, AActor* _PlayerActor, TArray<AActor*> _PartitionedActors, TSet<AActor*> _NeverUnloadedActors, TSet<AActor*> _NeverLoadedActors, bool Active, bool UseZ, float _MaxDistance, bool LoadOnStart, bool UnloadOnStart, float _TickInterval, bool UseGridDistance, bool IsGridOrigin, FVector _GridOrigin, float _GridSize)
{
	if (Instance != nullptr || GWorld == nullptr)
	{
		return nullptr;
	}

	APartitionManager* PartitionManager = GWorld->SpawnActor<APartitionManager>(APartitionManager::StaticClass(), SpawnTransform);

	PartitionManager->PrimaryActorTick.bCanEverTick = true;

	PartitionManager->bActive = Active;

	PartitionManager->bUseZ = UseZ;

	PartitionManager->MaxDistance = _MaxDistance;

	PartitionManager->PlayerActor = _PlayerActor;

	PartitionManager->PartitionedActors = _PartitionedActors;

	PartitionManager->NeverUnloadedActors = _NeverUnloadedActors;

	PartitionManager->NeverLoadedActors = _NeverLoadedActors;

	PartitionManager->CurrentLoadedActors = TSet<AActor*>();

	PartitionManager->CurrentUnloadedActors = TSet<AActor*>();

	PartitionManager->bLoadOnStart = LoadOnStart;

	PartitionManager->bUnloadOnStart = UnloadOnStart;

	PartitionManager->TickInterval = _TickInterval;

	PartitionManager->PrimaryActorTick.TickInterval = _TickInterval;

	PartitionManager->bUseGridDistance = UseGridDistance;

	PartitionManager->bIsGridOrigin = IsGridOrigin;

	PartitionManager->GridOrigin = IsGridOrigin ? SpawnTransform.GetLocation() : _GridOrigin;

	PartitionManager->GridSize = _GridSize;

	return PartitionManager;
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
void APartitionManager::SetPartitionUsesGridDistance(bool UseGridDistance)
{
	if (Instance == nullptr)
	{
		return;
	}

	Instance->bUseGridDistance = UseGridDistance;
}

// Calculates a grid space based on the given world position.
void APartitionManager::CalculateGridSpace(FVector WorldPosition, FVector& GridSpace, FVector2D& GridSpace2D)
{
	if (Instance == nullptr)
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
	if (Instance == nullptr)
	{
		return FVector();
	}

	return FVector();
}

// Returns the current grid space of the given actor.
void APartitionManager::GetGridSpace(AActor* Actor, FVector& GridSpace, FVector2D& GridSpace2D)
{
	if (Instance == nullptr || Actor == nullptr)
	{
		return;
	}

	CalculateGridSpace(Actor->GetActorLocation(), GridSpace, GridSpace2D);
}

// Returns the current grid space of the player.
void APartitionManager::GetPlayerGridSpace(FVector& GridSpace, FVector2D& GridSpace2D)
{
	if (Instance == nullptr)
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
