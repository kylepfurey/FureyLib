
// Actor Partition Manager Script
// by Kyle Furey

// REQUIREMENT: PartitionManager.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/Interface.h"
#include "Math/Vector.h"
#include "Math/Vector2D.h"
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
	* By default: this actor stops calling the Tick() function.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Partitionable")
	void OnLoad();
	virtual void OnLoad_Implementation();

	/**
	* Unloads the actor when out of range.
	* By default: this actor stops calling the Tick() function.
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

	/** Whether or not to use the Z axis (up) when partitioning actors. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Partition Manager")
	bool bUseZ = false;

	/** The maximum distance actors can be from the player before unloading. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Partition Manager")
	float MaxDistance = 10000;

	/** The player actor used to compare distances for partitioning other actors. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Partition Manager")
	AActor* PlayerActor = nullptr;

	/** The current set of partitioned actors. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "Partition Manager")
	TSet<AActor*> PartitionedActors = TSet<AActor*>();

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

	/** The current instance of the partition manager in this world. */
	static APartitionManager* Instance;


	// GRID VARIABLES

	/** The origin used to calculate grid space. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Partition Manager")
	FVector GridOrigin = FVector(0, 0, 0);

	/** The size used to calculate grid space. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Partition Manager")
	float GridSize = 1000;


	// UNREAL FUNCTIONS

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

	/** Called when the actor is destroyed. */
	virtual void BeginDestroy() override;


	// LOADING AND UNLOADING FUNCTIONS

	/**
	* Loads an actor using the IPartitionable interface.
	* Returns whether the actor was loaded using the interface (true) or by enabling tick (false).
	*/
	virtual bool LoadActor(AActor* Actor);

	/**
	* Unloads an actor using the IPartitionable interface.
	* Returns whether the actor was unloaded using the interface (true) or by disabling tick (false).
	*/
	virtual bool UnloadActor(AActor* Actor);

public:

	// CONSTRUCTORS

	/** Default constructor. */
	APartitionManager();

	/** Object initializer constructor. */
	APartitionManager(const FObjectInitializer& ObjectInitializer);

	/** Partition manager constructor. */
	APartitionManager(bool bUseZ, float MaxDistance = 10000, AActor* PlayerActor = nullptr, TSet<AActor*> PartitionedActors = TSet<AActor*>(), TSet<AActor*> NeverUnloadedActors = TSet<AActor*>(), TSet<AActor*> NeverLoadedActors = TSet<AActor*>(), FVector GridOrigin = FVector(0, 0, 0), float GridSize = 1000);


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

	/** Returns whether the Z axis (up) is used in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool GetPartitionUseZ();

	/** Returns the distance before actors are partitioned. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static float GetPartitionMaxDistance();

	/** Returns the player actor used for distance calculations in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static AActor* GetPartitionPlayer();

	/** Returns the actors in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TSet<AActor*> GetPartitionedActors();

	/** Returns actors never to be unloaded in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TSet<AActor*> GetNeverUnloadedPartitionActors();

	/** Returns actors never to be loaded in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TSet<AActor*> GetNeverLoadedPartitionActors();

	/** Returns actors currently unloaded in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TSet<AActor*> GetUnloadedPartitionActors();

	/** Returns actors currently loaded in partitioning. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TSet<AActor*> GetLoadedPartitionActors();

	/** Returns the origin point used in grid space. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static FVector GetPartitionGridOrigin();

	/** Returns the grid size used in grid space. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static float GetPartitionGridSize();


	// SETTERS

	/** Sets whether the Z axis (up) is used in partitioning. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static void SetPartitionUseZ(bool _bUseZ);

	/** Sets the distance before actors are partitioned. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static void SetPartitionMaxDistance(float _MaxDistance);

	/** Sets the player actor used for distance calculations in partitioning. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static void SetPartitionPlayer(AActor* _PlayerActor);

	/** Sets the origin point used in grid space. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static void SetPartitionGridOrigin(FVector _GridOrigin);

	/** Sets the grid size used in grid space. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static void SetPartitionGridSize(float _GridSize);


	// PARTITION FUNCTIONS

	/** Returns if the given actor is partitioned. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool IsPartitioned(AActor* Actor);

	/** Marks the actor for partitioning and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static bool MarkPartitioned(AActor* Actor);

	/** Marks the actor for partitioning and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static bool UnmarkPartitioned(AActor* Actor);

	/** Returns if the given actor is never unloaded. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool IsPartitionNeverUnloaded(AActor* Actor);

	/** Never unloads the given actor and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static bool NeverUnloadPartition(AActor* Actor);

	/** Returns if the given actor is never loaded. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool IsPartitionNeverLoaded(AActor* Actor);

	/** Never loads the given actor and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static bool NeverLoadPartition(AActor* Actor);

	/** Partitions the given actor normally and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "Partition Manager")
	static bool PartitionRegularly(AActor* Actor);


	// GRID FUNCTIONS

	/** Calculates a grid space based on the given world position. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static void CalculatePartitionGridSpace(FVector WorldPosition, FVector& GridSpace, FVector2D& GridSpace2D);

	/** Calculates a world position based on the given grid space. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static FVector CalculatePartitionWorldPosition(FVector GridSpace);

	/** Returns the current grid space of the given actor. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static void GetPartitionGridSpace(AActor* Actor, FVector& GridSpace, FVector2D& GridSpace2D);

	/** Returns the current grid space of the player. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static void GetPlayerPartitionGridSpace(FVector& GridSpace, FVector2D& GridSpace2D);

	/** Returns whether the given actor is in the given grid space. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static bool IsInPartitionGridSpace(AActor* Actor, FVector GridSpace);

	/** Returns the given actors that are in a given grid space. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TSet<AActor*> GetActorsInPartitionGridSpace(TArray<AActor*> Actors, FVector GridSpace);

	/** Returns all of the world's current actors. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Partition Manager")
	static TArray<AActor*> GetAllActors();
};
