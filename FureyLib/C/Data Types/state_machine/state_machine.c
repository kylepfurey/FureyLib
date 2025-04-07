// .c
// C State Machine Script
// by Kyle Furey

#include "state_machine.h"

// CONSTRUCTORS AND DESTRUCTOR

// Initializes a new state machine with a pointer to the state machine's data and a starting state.
state_machine state_machine_new(void *data, const state starting_state) {
    const state_machine self = {
        starting_state,
        data
    };
    return self;
}

// FUNCTIONS

// Forcefully switches the state machine's current state to the given state.<br/>
// NOTE: This does not execute the new state.
void state_machine_switch(state_machine *self, const state new_state) {
    if (self == NULL) {
        return;
    }
    self->state = new_state;
}

// Executes the state machine's current state.
// The current state's returned state will be the state machine's new state.
// Returns the state machine's new state.
state state_machine_execute(state_machine *self) {
    if (self == NULL) {
        return NULL_STATE;
    }
    if (self->state != NULL_STATE) {
        self->state = (state) self->state(self);
    }
    return self->state;
}

// Executes the state machine's current state until it is NULL.
void state_machine_unwrap(state_machine *self) {
    if (self == NULL) {
        return;
    }
    while (self->state != NULL_STATE) {
        self->state = (state) self->state(self);
    }
}
