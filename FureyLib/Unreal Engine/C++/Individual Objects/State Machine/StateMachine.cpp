// .cpp
// State Machine Actor Component Script
// by Kyle Furey

#include "State Machine/StateMachine.h"


// INTERFACE

// Returns the UStateMachine component that owns this state.
UStateMachine* IState::GetStateMachine_Implementation() const { return nullptr; }

// Sets the UStateMachine component that owns this state.
void IState::SetStateMachine_Implementation(UStateMachine* StateMachine) {}


// CONSTRUCTORS

// Default constructor.
UStateMachine::UStateMachine()
{
	State = nullptr;
	StartingStateClass = nullptr;
	DestroyBehaviour = EStateDestroyBehaviour::ALWAYS;
	PrimaryComponentTick.bCanEverTick = false;
}

// Object initializer constructor.
UStateMachine::UStateMachine(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	State = nullptr;
	StartingStateClass = nullptr;
	DestroyBehaviour = EStateDestroyBehaviour::ALWAYS;
	PrimaryComponentTick.bCanEverTick = false;
}


// EVENTS

// Initializes the starting state component.
void UStateMachine::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(StartingStateClass))
		SwitchState(StartingStateClass);
}

// Cleans up the state machine's current state component.
void UStateMachine::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (IsValid(State))
		DestroyState();
}


// GETTERS

// Returns the state machine's current state component.
UActorComponent* UStateMachine::GetState() const
{
	return State;
}

// Returns the class of the state machine's current state component.
TSubclassOf<UActorComponent> UStateMachine::GetStateClass() const
{
	return IsValid(State) ? State->GetClass() : nullptr;
}

// Returns the class of the state machine's starting state component.
TSubclassOf<UActorComponent> UStateMachine::GetStartingStateClass() const
{
	return StartingStateClass;
}

// Returns the behaviour set for when components are destroyed by this state machine.
EStateDestroyBehaviour UStateMachine::GetDestroyBehaviour() const
{
	return DestroyBehaviour;
}

// Returns whether the state machine's current state component is valid.
bool UStateMachine::IsStateValid() const
{
	return IsValid(State);
}

// Returns whether the state machine's current state component is the given component class.
bool UStateMachine::StateIs(TSubclassOf<UActorComponent> StateClass) const
{
	return IsValid(State) && State->IsA(StateClass);
}


// SETTERS

// Sets the behaviour set for when components are destroyed by this state machine.
void UStateMachine::SetDestroyBehaviour(const EStateDestroyBehaviour _DestroyBehaviour)
{
	DestroyBehaviour = _DestroyBehaviour;
}

// Switches the state machine's state component to the given state component.
UActorComponent* UStateMachine::SwitchStateTo(UActorComponent* NewState)
{
	if (NewState == State)
		return State;
	if (IsValid(State))
		DestroyState();
	State = NewState;
	if (IsValid(State) && State->GetClass()->ImplementsInterface(UState::StaticClass()))
		IState::Execute_SetStateMachine(State, this);
	OnSwitchState.Broadcast(State);
	return State;
}

// Switches the state machine's state component to a new state component of the given class.
UActorComponent* UStateMachine::SwitchState(TSubclassOf<UActorComponent> StateClass)
{
	if (!IsValid(StateClass))
		return SwitchStateTo(nullptr);
	AActor* Actor = IsValid(State) ? State->GetOwner() : GetOwner();
	UActorComponent* NewState = NewObject<UActorComponent>(Actor, StateClass);
	if (IsValid(NewState))
	{
		NewState->RegisterComponent();
		USceneComponent* SceneComponent = Cast<USceneComponent>(NewState);
		if (IsValid(SceneComponent))
		{
			SceneComponent->AttachToComponent(Actor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			SceneComponent->SetRelativeLocation(FVector::ZeroVector);
		}
		return SwitchStateTo(NewState);
	}
	return nullptr;
}

// Destroys this state machine's current state component based on its destroy behaviour.
// Returns whether the component was successfully destroyed.
bool UStateMachine::DestroyState()
{
	if (!IsValid(State))
		return false;
	switch (DestroyBehaviour)
	{
	default:
		return false;
	case EStateDestroyBehaviour::NEVER:
		return false;
	case EStateDestroyBehaviour::MY_COMPONENTS:
		if (State->GetOwner() == GetOwner())
		{
			State->DestroyComponent();
			State = nullptr;
			return true;
		}
		else return false;
	case EStateDestroyBehaviour::OTHER_COMPONENTS:
		if (State->GetOwner() != GetOwner())
		{
			State->DestroyComponent();
			State = nullptr;
			return true;
		}
		else return false;
	case EStateDestroyBehaviour::ALWAYS:
		State->DestroyComponent();
		State = nullptr;
		return true;
	}
}
