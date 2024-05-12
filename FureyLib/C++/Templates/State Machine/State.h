
// Template State Machine State Script
// by Kyle Furey

#pragma once
#include "StateMachine.h"

// Include this header at the bottom of StateMachine.h!
#include "State.h"

// Base class macro
#define base __super::

// A template for a new state machine state.
class State : public StateBase
{
public:

	// Constructor (sets state machine)
	State(StateMachine* stateMachine)
	{
		this->stateMachine = stateMachine;

		// Change the state type enum here!
		this->stateMachine->currentStateType = StateType::State;
	}

	// Called when this state is set as the state machine's current state
	void OnStateEnter() override
	{
		// Calls the base class's function
		base OnStateEnter();
	}

	// Called every frame while this state is the state machine's current state
	void OnStateUpdate() override
	{
		// Calls the base class's function
		base OnStateUpdate();
	}

	// Called when this state machine's current state is no longer this state
	void OnStateExit() override
	{
		// Calls the base class's function
		base OnStateExit();
	}
};
