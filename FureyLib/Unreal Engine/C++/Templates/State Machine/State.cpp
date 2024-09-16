
// Template State Machine State Script
// by Kyle Furey

// REQUIREMENT: State.h

// Include this heading to use the class
#include "State Machine/State.h"


// STATE CONSTRUCTORS

// Default constructor.
UState::UState()
{
	StateMachine = nullptr;

	// Change the state type enum here!
	StateType = EStateType::STATE;

	// Initialize new variables here
}

// Object initializer constructor.
UState::UState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	StateMachine = nullptr;

	// Change the state type enum here!
	StateType = EStateType::STATE;

	// Initialize new variables here
}

// State machine constructor.
UState::UState(UStateMachine* _StateMachine)
{
	StateMachine = _StateMachine;

	// Change the state type enum here!
	StateType = EStateType::STATE;

	// Initialize new variables here
}


// STATE EVENTS

// Called when this state is set as the state machine's current state.
void UState::OnStateBegin_Implementation()
{
	// Calls the base class's implementation.
	Super::OnStateBegin_Implementation();

	// New code here
}

// Called every frame while this state is the state machine's current state.
void UState::OnStateTick_Implementation(float DeltaTime)
{
	// Calls the base class's implementation.
	Super::OnStateTick_Implementation(DeltaTime);

	// New code here
}

// Called when this state machine's current state is no longer this state.
void UState::OnStateEnd_Implementation()
{
	// Calls the base class's implementation.
	Super::OnStateEnd_Implementation();

	// New code here
}
