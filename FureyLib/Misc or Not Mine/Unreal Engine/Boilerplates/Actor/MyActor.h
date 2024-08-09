
// Name
// Creator

// REQUIREMENT: MyActor.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

// Include this heading to use the class
// #include "MyActor.h"

/** Template Unreal actor script. */
UCLASS(Blueprintable, BlueprintType)
class GAME_API AMyActor : public AActor
{
	GENERATED_BODY()

public:

	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor */
	AMyActor();

	/** Copy constructor */
	AMyActor(const AMyActor& Copied);

	/** Move constructor */
	AMyActor(AMyActor&& Moved) noexcept;

	// New constructors here

	/** Destructor */
	virtual ~AMyActor();

protected:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	// New functions here

public:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	// New functions here


	// OPERATORS

	/** Copy assignment operator */
	AMyActor& operator=(const AMyActor& Copied);

	/** Move assignment operator */
	AMyActor& operator=(AMyActor&& Moved) noexcept;

	// New overloaded operators here
};
