
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

protected:

	// VARIABLES

	// New variables here


	// UNREAL FUNCTIONS

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;


	// FUNCTIONS

	// New functions here

public:

	// VARIABLES

	// New variables here


	// CONSTRUCTOR

	/** Default constructor. */
	AMyActor();


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;


	// FUNCTIONS

	// New functions here
};