// .h
// C State Machine Script
// by Kyle Furey

#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

// MACRO

// Declares a new state machine state with the given name.
// The state's pointer to the state machine is stored as "self".
#define DECLARE_STATE(name) void *name(state_machine *self)

// Represents an empty state.
#define NULL_STATE NULL

// TYPEDEF

/** A system that manages data via states that can transition into a finite number of other states. */
typedef struct state_machine state_machine;

/**
 * Represents single function that acts as the state machine's current state.<br/>
 * This function takes a pointer to the state machine as its only parameter.<br/>
 * This function returns the next state for the state machine to execute.
 */
typedef void *(*state)(state_machine *);

// STRUCTURE

/** A system that manages data via states that can transition into a finite number of other states. */
struct state_machine {
    // VARIABLES

    /** The current state of this state machine. */
    state state;

    /** A pointer to the managed data of this state machine. */
    void *data;
};

// CONSTRUCTORS AND DESTRUCTOR

/** Initializes a new state machine with a pointer to the state machine's data and a starting state. */
state_machine state_machine_new(void *data, state starting_state);

// FUNCTIONS

/**
 * Executes the state machine's current state.<br/>
 * The current state's returned state will be the state machine's new state.<br/>
 * Returns the state machine's new state.
 */
state state_machine_execute(state_machine *self);
