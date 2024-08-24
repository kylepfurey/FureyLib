
// Name
// Creator

// REQUIREMENT: MyWorldSettings.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "MyWorldSettings.generated.h"

// Include this heading to use the class
// #include "Boilerplate/MyWorldSettings.h"

/** Template Unreal world settings script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API AMyWorldSettings : public AWorldSettings
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
	AMyWorldSettings();

	/** Object initializer constructor. */
	AMyWorldSettings(const FObjectInitializer& ObjectInitializer);

	// New constructors here


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;


	// FUNCTIONS

	// New functions here
};
