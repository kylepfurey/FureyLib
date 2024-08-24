
// Name
// Creator

// REQUIREMENT: MyHUD.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

// Include this heading to use the class
// #include "Boilerplate/MyHUD.h"

/** Template Unreal HUD script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API AMyHUD : public AHUD
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
	AMyHUD();

	/** Object initializer constructor. */
	AMyHUD(const FObjectInitializer& ObjectInitializer);

	// New constructors here


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;


	// FUNCTIONS

	// New functions here
};
