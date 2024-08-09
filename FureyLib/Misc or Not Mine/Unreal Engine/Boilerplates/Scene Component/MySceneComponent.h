
// Name
// Creator

// REQUIREMENT: MySceneComponent.cpp

#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MySceneComponent.generated.h"

// Include this heading to use the class
#include "MySceneComponent.h"

/** Template Unreal scene component script. */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAME_API UMySceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:

	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor */
	UMySceneComponent();

	/** Copy constructor */
	UMySceneComponent(const UMySceneComponent& Copied);

	/** Move constructor */
	UMySceneComponent(UMySceneComponent&& Moved) noexcept;

	// New constructors here

	/** Destructor */
	virtual ~UMySceneComponent();

protected:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	/** Called when the game starts */
	virtual void BeginPlay() override;

	// New functions here

public:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	/** Called every frame */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// New functions here


	// OPERATORS

	/** Copy assignment operator */
	UMySceneComponent& operator=(const UMySceneComponent& Copied);

	/** Move assignment operator */
	UMySceneComponent& operator=(UMySceneComponent&& Moved) noexcept;

	// New overloaded operators here
};
