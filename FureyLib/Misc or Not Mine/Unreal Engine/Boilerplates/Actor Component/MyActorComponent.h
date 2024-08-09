
// Name
// Creator

// REQUIREMENT: MyActorComponent.cpp

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"

// Include this heading to use the class
// #include "MyActorComponent.h"

/** Template Unreal actor component script. */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAME_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor */
	UMyActorComponent();

	/** Copy constructor */
	UMyActorComponent(const UMyActorComponent& Copied);

	/** Move constructor */
	UMyActorComponent(UMyActorComponent&& Moved) noexcept;

	// New constructors here

	/** Destructor */
	virtual ~UMyActorComponent();

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
	UMyActorComponent& operator=(const UMyActorComponent& Copied);

	/** Move assignment operator */
	UMyActorComponent& operator=(UMyActorComponent&& Moved) noexcept;

	// New overloaded operators here
};
