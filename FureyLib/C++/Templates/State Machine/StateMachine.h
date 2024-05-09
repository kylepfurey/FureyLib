
// Template State Machine Script
// by Kyle Furey

#pragma once

// Include this heading to use the class
#include "StateMachine.h"

// INCLUDE YOUR STATE HEADERS AT THE BOTTOM OF THIS SCRIPT!

// State machine states enum
enum StateType
{
	Null = 0,
	State = 1
};

// Forward declaration of state machine
class StateMachine;

// The base class for each state. All states should inherit from this class.
class StateBase
{
protected:

	// The inherited state machine from the owner
	StateMachine* stateMachine = nullptr;

public:

	// Called when this state is set as the state machine's current state
	virtual void OnStateEnter()
	{
		// Note: Logic applies to all inherited states
	}

	// Called when this state machine's current state is no longer this state
	virtual void OnStateExit()
	{
		// Note: Logic applies to all inherited states
	}

	// Called every frame while this state is the state machine's current state
	virtual void StateUpdate()
	{
		// Note: Logic applies to all inherited states
	}
};

// Base for building a state machine.
class StateMachine
{
public:

	// The current state of this state machine
	StateBase* currentState = nullptr;

	// The current state of this state machine
	StateType currentStateType = StateType::Null;

	// Starting state constructor
	StateMachine(state_base* new_state)
	{
		SwitchState(new_state);
	}

	// Deconstructor
	~StateMachine()
	{
		delete currentState;

		currentState = nullptr;
	}

	// Properly switches the state machine's current state
	void SwitchState(StateBase* newState)
	{
		// Exit the current state
		if (currentState != nullptr)
		{
			currentState->OnStateExit();
		}

		// Deallocate state memory
		delete currentState;

		// Switch the current state to the new state
		currentState = newState;

		// Enter the new state
		if (currentState != nullptr)
		{
			currentState->OnStateEnter();
		}
	}

	// Updates the current state (should be called each tick)
	void Tick()
	{
		// Call the current state's update function
		if (currentState != nullptr)
		{
			currentState->StateUpdate();
		}
	}
};

// Include your state headers here!
#include "State.h"
