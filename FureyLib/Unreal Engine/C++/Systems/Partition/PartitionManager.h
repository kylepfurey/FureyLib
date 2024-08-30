
// Actor Partition Manager Script
// by Kyle Furey

// REQUIREMENT: PartitionManager.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/Interface.h"
#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Math/Transform.h"
#include "Kismet/GameplayStatics.h"
#include "PartitionManager.generated.h"

// Include this heading to use the class
// #include "Partition/PartitionManager.h"

// This class does not need to be modified. Do not inherit from this class.
UINTERFACE(Blueprintable, BlueprintType, MinimalAPI)
class UPartitionable : public UInterface
{
	GENERATED_BODY()
};

// Inherit from the following interface to implement it.

/** Indicates loading and unloading for an actor. */
class MYGAME_API IPartitionable
{
	GENERATED_BODY()

public:

	// IPARTITIONABLE FUNCTIONS

	/**
	* Loads the actor when in range.
	* By default: this actor stops calling the Tick() function and shows itself.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Partitionable")
	void OnLoad();
	virtual void OnLoad_Implementation();

	/**
	* Unloads the actor when out of range.
	* By default: this actor stops calling the Tick() function and hides itself.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Partitionable")
	void OnUnload();
	virtual void OnUnload_Implementation();
};

/** Manages loading and unloading actors relative to the player. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API APartitionManager : public AActor
{
	GENERATED_BODY()

protected:

	// PARTITION VARIABLES

	/** The player actor used to compare distances for partitioning other actors. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Partition Manager")
	AActor* PlayerActor = nullptr;

	/** The current set of partitioned actors. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "Partition Manager")
	TArray<AActor*> PartitionedActors = TArray<AActor*>();

	/** The current set of partitioned actors never to be unloaded. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "Partition Manager")
	TSet<AActor*> NeverUnloadedActors = TSet<AActor*>();

	/** The current set of partitioned actors never to be loaded. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "Partition Manager")
	TSet<AActor*> NeverLoadedActors = TSet<AActor*>();

	/** The current set of loaded actors. */
	TSet<AActor*> CurrentLoadedActors = TSet<AActor*>();

	/** The current set of unloaded actors. */
	TSet<AActor*> CurrentUnloadedActors = TSet<AActor*>();

	/** Whether or not partition updates each tick. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Partition Manager")
	bool bActive = true;

	/** Whether or not to use the Z axis (up) when partitioning actors. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Partition Manager")
	bool bUseZ = false;

	/** The maximum distance (either in units or grid spaces) that actors can be from the player before unloading. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Partition Manager")
	float MaxDistance = 10000;

	/** Whether to load on start. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "Partition Manager")
	bool bLoadOnStart = true;

	/** Whether to unload on start. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "Partition Manager")
	bool bUnloadOnStart = true;

	/** The delay in seconds for each updated partition tick. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "Partition Manager")
	float TickInterval = 0;


	// GRID VARIABLES

	/** Whether or not to use the grid distance when partitioning actors. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Partition Manager")
	bool bUseGridDistance = false;

	/** Whether the partition manager is the grid origin. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Partition Manager")
	bool bIsGridOrigin = false;

	/** The origin used to calculate grid space. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Partition Manager")
	FVector GridOrigin = FVector(0, 0, 0);

	/** The size used to calculate grid space. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Partition Manager")
	float GridSize = 1000;


	// STATIC INSTANCE

	/** The current instance of the partition manager in this world. */
	static APartitionManager* Instance;


	// UNREAL FUNCTIONS

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

	/** Called when the actor is destroyed. */
	virtual void BeginDestroy() override;

public:

	// CONSTRUCTORS

	/** Default constructor. */
	APartitionManager();

	/** Object initializer constructor. */
	APartitionManager(const FObjectInitializer& ObjectInitializer);

	/** Partition manager constructor. */
	APartitionManager(AActor* _PlayerActor, TArray<AActor*> _PartitionedActors, TSet<AActor*> _NeverUnloadedActors, TSet<AActor*> _NeverLoadedActors, bool Active = true, bool UseZ = false, float _MaxDistance = 10000, bool LoadOnStart = true, bool UnloadOnStart = true, float _TickInterval = 0, bool UseGridDistance = false, bool IsGridOrigin = false, FVector _GridOrigin = FVector(0, 0, 0), float _GridSize = 1000);


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;


	// GETTERS

	/** Returns whether this world has a partition manager. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool PartitionManagerExists();

	/** Returns the current instance of the partition manager. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static APartitionManager* GetPartitionManager();

	/** Returns whether the partition manager is active. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool IsPartitionActive();

	/** Returns whether the Z axis (up) is used in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool DoesPartitionUseZ();

	/** Returns the distance before actors are partitioned. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static float GetPartitionMaxDistance();

	/** Returns the player actor used for distance calculations in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static AActor* GetPlayer();

	/** Returns the actors in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TArray<AActor*> GetPartitionedActors();

	/** Returns actors never to be unloaded in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TSet<AActor*> GetNeverUnloadedActors();

	/** Returns actors never to be loaded in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TSet<AActor*> GetNeverLoadedActors();

	/** Returns actors currently unloaded in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TSet<AActor*> GetUnloadedActors();

	/** Returns actors currently loaded in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TSet<AActor*> GetLoadedActors();

	/** Returns the origin point used in grid space. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static FVector GetGridOrigin();

	/** Returns the grid size used in grid space. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static float GetGridSize();

	/** Returns whether objects were loaded on start. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool WereActorsLoadedOnStart();

	/** Returns whether objects were unloaded on start. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool WereActorsUnloadedOnStart();

	/** Returns whether the partition manager is the origin of the grid. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool IsPartitionManagerGridOrigin();

	/** Returns the tick interval of the partition manager. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static float GetPartitionTickInterval();


	// SETTERS

	/** Sets whether the partition manager is active. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static void SetPartitionActive(bool Active);

	/** Sets whether the Z axis (up) is used in partitioning. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static void SetPartitionUsesZ(bool UseZ);

	/** Sets the distance before actors are partitioned. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static void SetPartitionMaxDistance(float _MaxDistance);

	/** Sets the player actor used for distance calculations in partitioning. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static void SetPartitionPlayer(AActor* _PlayerActor);

	/** Sets the origin point used in grid space. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static void SetGridOrigin(FVector _GridOrigin);

	/** Sets the grid size used in grid space. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static void SetGridSize(float _GridSize);

	/** Sets the partition manager's location as the grid origin. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static void SetPartitionManagerAsGridOrigin();

	/** Sets the tick interval of the partition manager. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static void SetPartitionTickInterval(float _TickInterval);


	// LOADING AND UNLOADING FUNCTIONS

	/**
	* Updates the partition's actors' load states.
	* Automatically called each tick while the partition manager is present and active.
	* Returns whether the update was successful.
	*/
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static bool UpdatePartition();

	/** Returns if the given actor is loaded. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool IsActorLoaded(AActor* Actor);

	/**
	* Loads an actor using the IPartitionable interface.
	* Returns whether the actor was loaded using the interface (true) or by default (false).
	*/
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static bool LoadActor(AActor* Actor);

	/** Returns if the given actor is unloaded. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool IsActorUnloaded(AActor* Actor);

	/**
	* Unloads an actor using the IPartitionable interface.
	* Returns whether the actor was unloaded using the interface (true) or by default (false).
	*/
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static bool UnloadActor(AActor* Actor);


	// PARTITION FUNCTIONS

	/** Returns whether the given actor is within the maximum distance of the player actor. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool IsWithinDistanceOfPlayer(AActor* Actor);

	/** Returns if the given actor is partitioned. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool IsPartitioned(AActor* Actor);

	/** Marks the actor for partitioning and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static bool MarkPartitioned(AActor* Actor);

	/** Unmarks the actor for partitioning and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static bool UnmarkPartitioned(AActor* Actor);

	/** Returns if the given actor is never unloaded. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool IsActorNeverUnloaded(AActor* Actor);

	/** Never unloads the given actor and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static bool NeverUnloadActor(AActor* Actor);

	/** Returns if the given actor is never loaded. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool IsActorNeverLoaded(AActor* Actor);

	/** Never loads the given actor and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static bool NeverLoadActor(AActor* Actor);

	/** Partitions the given actor normally and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static bool LoadActorNormally(AActor* Actor);

	/** Spawns a new APartitionManager actor into the world. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static APartitionManager* SpawnPartitionManager(FTransform SpawnTransform, AActor* _PlayerActor, TArray<AActor*> _PartitionedActors, TSet<AActor*> _NeverUnloadedActors, TSet<AActor*> _NeverLoadedActors, bool Active = true, bool UseZ = false, float _MaxDistance = 10000, bool LoadOnStart = true, bool UnloadOnStart = true, float _TickInterval = 0, bool UseGridDistance = false, bool IsGridOrigin = false, FVector _GridOrigin = FVector(0, 0, 0), float _GridSize = 1000);


	// GRID FUNCTIONS

	/** Returns whether grid space is used as distance in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool DoesPartitionUseGridDistance();

	/** Sets whether grid space is used as distance in partitioning. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static void SetPartitionUsesGridDistance(bool UseGridDistance);

	/** Calculates a grid space based on the given world position. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static void CalculateGridSpace(FVector WorldPosition, FVector& GridSpace, FVector2D& GridSpace2D);

	/** Calculates a world position based on the given grid space. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static FVector CalculateWorldPosition(FVector GridSpace);

	/** Returns the current grid space of the given actor. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static void GetGridSpace(AActor* Actor, FVector& GridSpace, FVector2D& GridSpace2D);

	/** Returns the current grid space of the player. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static void GetPlayerGridSpace(FVector& GridSpace, FVector2D& GridSpace2D);

	/** Returns whether the given actor is in the given grid space. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool IsInGridSpace(AActor* Actor, FVector GridSpace);

	/** Returns the given actors that are in a given grid space. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TSet<AActor*> GetActorsInGridSpace(TArray<AActor*> Actors, FVector GridSpace);

	/** Returns all of the actors that are in a given grid space. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TSet<AActor*> GetAllActorsInGridSpace(FVector GridSpace);

	/** Returns all of the world's current actors. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TArray<AActor*> GetAllActors();
};
