
// Template State Machine Script
// by Kyle Furey

// REQUIREMENT: StateMachine.h

// Include this heading to use the class
#include "State Machine/StateMachine.h"


// STATE BASE CONSTRUCTORS

// Default constructor.
UStateBase::UStateBase()
{
	StateMachine = nullptr;
}

// Object initializer constructor.
UStateBase::UStateBase(const FObjectInitializer& ObjectInitializer)
{
	StateMachine = nullptr;
}

// State machine constructor.
UStateBase::UStateBase(UStateMachine* _StateMachine)
{
	StateMachine = _StateMachine;
}


// STATE BASE GETTERS

// Returns this state's state machine.
UStateMachine* UStateBase::GetStateMachine()
{
	return StateMachine;
}

// Returns this state's class.
UClass* UStateBase::GetStateClass()
{
	return StaticClass();
}

// Returns this state's owning actor.
AActor* UStateBase::GetActor()
{
	if (IsValid(StateMachine))
	{
		return StateMachine->GetOwner();
	}
	else
	{
		return nullptr;
	}
}

// Returns a new state of the given state class and state machine.
UStateBase* UStateBase::ConstructState(UClass* NewStateClass, UStateMachine* _StateMachine)
{
	if (IsValid(NewStateClass) && NewStateClass->IsChildOf(UStateBase::StaticClass()) && IsValid(_StateMachine))
	{
		UStateBase* NewState = NewObject<UStateBase>(_StateMachine, NewStateClass);

		NewState->StateMachine = _StateMachine;

		return NewState;
	}
	else
	{
		return nullptr;
	}
}


// STATE BASE EVENTS

// Called when this state is set as the state machine's current state.
void UStateBase::OnStateBegin_Implementation(UClass* PreviousStateClass)
{
	// Note: Logic applies to all derived states.

	// New code here
}

// Called every frame while this state is the state machine's current state.
void UStateBase::OnStateTick_Implementation(float DeltaTime)
{
	// Note: Logic applies to all derived states.

	// New code here
}

// Called when this state machine's current state is no longer this state.
void UStateBase::OnStateEnd_Implementation(UClass* PreviousStateClass)
{
	// Note: Logic applies to all derived states.

	// New code here
}


// STATE MACHINE CONSTRUCTORS

// Default constructor.
UStateMachine::UStateMachine()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentState = nullptr;

	StartingStateClass = nullptr;
}

// Object initializer constructor.
UStateMachine::UStateMachine(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentState = nullptr;

	StartingStateClass = nullptr;
}

// Starting state constructor.
UStateMachine::UStateMachine(UClass* _StartingStateClass)
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentState = nullptr;

	if (IsValid(_StartingStateClass) && _StartingStateClass->IsChildOf(UStateBase::StaticClass()))
	{
		StartingStateClass = _StartingStateClass;
	}
	else
	{
		StartingStateClass = nullptr;
	}
}


// UNREAL FUNCTIONS

// Called when the game starts.
void UStateMachine::BeginPlay()
{
	Super::BeginPlay();

	SwitchState(StartingStateClass);
}

// Called when the component is destroyed.
void UStateMachine::BeginDestroy()
{
	Super::BeginDestroy();

	SwitchState(nullptr);
}

// Called every frame.
void UStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(CurrentState))
	{
		CurrentState->OnStateTick(DeltaTime);
	}
}


// STATE MACHINE GETTERS

// Returns the current state of this state machine.
UStateBase* UStateMachine::GetCurrentState()
{
	return CurrentState;
}

// Returns the class of the current state of this state machine.
UClass* UStateMachine::GetCurrentStateClass()
{
	return CurrentState->StaticClass();
}

// Returns the starting state class of this state machine.
UClass* UStateMachine::GetStartingStateClass()
{
	return StartingStateClass;
}

// Returns whether the current state is null.
bool UStateMachine::IsStateNull()
{
	return !IsValid(CurrentState);
}

// Returns a new state machine component starting with the given state class.
UStateMachine* UStateMachine::ConstructStateMachine(AActor* Parent, UClass* _StartingStateClass)
{
	if (!IsValid(GWorld) || !IsValid(Parent) || !IsValid(_StartingStateClass) || !_StartingStateClass->IsChildOf<UStateBase>())
	{
		return nullptr;
	}

	UStateMachine* NewStateMachine = Cast<UStateMachine>(Parent->AddComponentByClass(UStateMachine::StaticClass(), true, FTransform(), true));

	NewStateMachine->RegisterComponent();

	Parent->AddInstanceComponent(NewStateMachine);

	NewStateMachine->StartingStateClass = _StartingStateClass;

	return NewStateMachine;
}


// STATE MACHINE FUNCTIONS

// Properly switches the state machine's current state to the given state type.
// Returns whether the switch was successful.
bool UStateMachine::SwitchState(UClass* NewStateClass)
{
	UClass* PreviousStateClass;

	if (IsValid(CurrentState))
	{
		PreviousStateClass = CurrentState->StaticClass();

		CurrentState->OnStateEnd(NewStateClass);
	}
	else
	{
		PreviousStateClass = nullptr;
	}

	if (IsValid(NewStateClass))
	{
		CurrentState = UStateBase::ConstructState(NewStateClass, this);

		if (IsValid(CurrentState))
		{
			CurrentState->OnStateBegin(PreviousStateClass);
		}
		else
		{
			return false;
		}
	}
	else
	{
		CurrentState = nullptr;
	}

	return true;
}
