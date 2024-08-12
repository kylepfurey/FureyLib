
// Template State Machine State Script
// by Kyle Furey

#pragma once
#include "state_machine.h"

// Base class macro
#define base state_base::

// A template for a new state machine state.
class state : public state_base
{
public:

	// Constructor (sets state machine)
	state(state_machine* state_machine)
	{
		this->my_state_machine = state_machine;

		// Change the state type enum here!
		this->my_state_machine->current_state_type = state_type::state;
	}

	// Destructor
	virtual ~state()
	{

	}

	// Called when this state is set as the state machine's current state
	void on_state_enter() override
	{
		// Calls the base class's function
		base on_state_enter();
	}

	// Called every frame while this state is the state machine's current state
	void on_state_update() override
	{
		// Calls the base class's function
		base on_state_update();
	}

	// Called when this state machine's current state is no longer this state
	void on_state_exit() override
	{
		// Calls the base class's function
		base on_state_exit();
	}
};
