
// Name
// Creator

// REQUIREMENT: MyActorComponent.cpp

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"

// Include this heading to use the class
// #include "Boilerplate/MyActorComponent.h"

/** Template Unreal actor component script. */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYGAME_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	// VARIABLES

	// New variables here


	// UNREAL FUNCTIONS

	/** Called when the game starts. */
	virtual void BeginPlay() override;


	// FUNCTIONS

	// New functions here

public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS

	/** Default constructor. */
	UMyActorComponent();

	/** Object initializer constructor. */
	UMyActorComponent(const FObjectInitializer& ObjectInitializer);

	// New constructors here


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// FUNCTIONS

	// New functions here
};
