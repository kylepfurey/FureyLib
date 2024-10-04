
// Template State Machine State Script
// by Kyle Furey

// REQUIREMENTS: StateMachine.h, State.cpp

#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "State Machine/StateMachine.h"
#include "State.generated.h"

// Include this heading to use the class
// #include "State Machine/State.h"

/** A template for a new state machine state. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UState : public UStateBase
{
	GENERATED_BODY()

protected:

	// STATE VARIABLES

	// New variables here

public:

	// STATE CONSTRUCTORS

	/** Default constructor. */
	UState();

	/** Object initializer constructor. */
	UState(const FObjectInitializer& ObjectInitializer);

	/** State machine constructor. */
	UState(UStateMachine* _StateMachine);


	// STATE EVENTS

	/** Called when this state is set as the state machine's current state. */
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	virtual void OnStateBegin_Implementation(UClass* PreviousStateClass) override;

	/** Called every frame while this state is the state machine's current state. */
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	virtual void OnStateTick_Implementation(float DeltaTime) override;

	/** Called when this state machine's current state is no longer this state. */
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	virtual void OnStateEnd_Implementation(UClass* NewStateClass) override;
};
