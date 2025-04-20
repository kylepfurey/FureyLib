// .h
// Functional State Machine Type
// by Kyle Furey

#pragma once

// Declares a new state machine state with the given type and name.
// The state's reference to the state machine is stored as "SM".
#define DECLARE_STATE(Type, Name) static void* Name(Toolbox::StateMachine<Type>& SM)

// Represents an empty state.
#define NULL_STATE nullptr

/** A collection of useful template types in C++. */
namespace Toolbox {

	// STATE MACHINE

	/** A system that manages data via states that can transition into a finite number of other states. */
	template<typename Type>
	class StateMachine final {
	public:

		// STATE

		/**
		 * Represents single function that acts as the state machine's current state.<br/>
		 * This function takes a reference to the state machine as its only parameter.<br/>
		 * This function returns the next state for the state machine to execute.
		 */
		using STATE = void* (*)(StateMachine&);

	private:

		// DATA

		/** The current state of this state machine. */
		STATE state;

		/** The managed data by this state machine. */
		Type data;

	public:

		// CONSTRUCTORS

		/** Default constructor. */
		StateMachine(const Type& Data = Type(), const STATE StartingState = NULL_STATE) : state(StartingState), data(Data) {
		}

		/** Default constructor. */
		StateMachine(const STATE StartingState, const Type& Data = Type()) : state(StartingState), data(Data) {
		}


		// GETTERS

		/** Returns the state machine's current state. */
		STATE State() const {
			return state;
		}

		/** Returns a reference to the state machine's managed data. */
		Type& Get() {
			return data;
		}

		/** Returns a constant reference to the state machine's managed data. */
		const Type& Get() const {
			return data;
		}

		/** Returns whether the state machine's current state is valid. */
		bool IsValidState() const {
			return state != NULL_STATE;
		}


		// SETTERS

		/**
		 * Forcefully switches the state machine's current state to the given state.<br/>
		 * NOTE: This does not execute the new state.
		 */
		void Switch(const STATE NewState) {
			state = NewState;
		}

		/** Sets the state machine's managed data to a copy of the given data. */
		void Set(const Type& NewData) {
			data = NewData;
		}


		// EXECUTION

		/**
		 * Executes the state machine's current state.<br/>
		 * The current state's returned state will be the state machine's new state.<br/>
		 * Returns the state machine's new state.
		 */
		STATE Execute() {
			if (state != NULL_STATE) {
				state = static_cast<STATE>(state(*this));
			}
			return state;
		}

		/** Executes the state machine's current state until it is NULL. */
		void Unwrap() {
			while (state != NULL_STATE) {
				state = static_cast<STATE>(state(*this));
			}
		}
	};
}
