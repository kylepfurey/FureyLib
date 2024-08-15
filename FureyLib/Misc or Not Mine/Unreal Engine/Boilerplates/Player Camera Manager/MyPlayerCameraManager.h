
// Name
// Creator

// REQUIREMENT: MyPlayerCameraManager.cpp

#pragma once
#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "MyPlayerCameraManager.generated.h"

// Include this heading to use the class
// #include "MyPlayerCameraManager.h"

/** Template Unreal player camera manager script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API AMyPlayerCameraManager : public APlayerCameraManager
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


	// CONSTRUCTORS

	/** Default constructor. */
	AMyPlayerCameraManager();

	/** Object initializer constructor. */
	AMyPlayerCameraManager(const FObjectInitializer& ObjectInitializer);

	// New constructors here


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;


	// FUNCTIONS

	// New functions here
};
