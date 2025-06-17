// .h
// State Machine Interface and Class
// by Kyle Furey

#pragma once
#include <chrono>
#include <utility>
#include <typeinfo>


// STATE

/** Forward declaration of StateMachine. */
template<typename Type>
class StateMachine;

/** An interface defining a class that can be used as a state within a state machine. */
template <typename Type>
class IState {

	// FRIENDS

	friend class StateMachine<Type>;


	// INTERFACE

	/** The state machine that owns this state instance. */
	StateMachine<Type>* stateMachine = nullptr;

public:

	// DESTRUCTOR

	/** Destructor. */
	virtual ~IState() = default;


	// INTERFACE

	/** Called when a state machine instantiates this state. */
	virtual void OnStateEnter(IState<Type>* previousState) = 0;

	/** Called when a state machine updates this state. */
	virtual void OnStateUpdate(double deltaTime) = 0;

	/** Called when a state machine switches off this state. */
	virtual void OnStateExit(IState<Type>* nextState) = 0;


	// GETTERS

	/** Returns the state machine that owns this state instance. */
	StateMachine<Type>& GetStateMachine() {
		return *stateMachine;
	}

	/** Returns the state machine that owns this state instance. */
	const StateMachine<Type>& GetStateMachine() const {
		return *stateMachine;
	}
};


// STATE MACHINE

/** A class that manages its data within different states of code. */
template <typename Type>
class StateMachine {

	// VARIABLES

	/** The data this state machine is managing. */
	Type data;

	/** The current state of this state machine. */
	IState<Type>* state;

	/** The time of this state machine's last update. */
	std::chrono::system_clock::time_point lastUpdate;

	/** The time in seconds since the state machine's last update. */
	double deltaTime;

public:

	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor. */
	StateMachine(Type data = Type(), IState<Type>* state = nullptr) : data(data), state(state), lastUpdate(std::chrono::system_clock::now()), deltaTime(0.0) {
		if (state != nullptr) {
			state->stateMachine = this;
			state->OnStateEnter(nullptr);
		}
	}

	/** State constructor. */
	StateMachine(IState<Type>* state, Type data = Type()) : data(data), state(state), lastUpdate(std::chrono::system_clock::now()), deltaTime(0.0) {
		if (state != nullptr) {
			state->stateMachine = this;
			state->OnStateEnter(nullptr);
		}
	}

	/** Delete copy constructor. */
	StateMachine(const StateMachine<Type>&) = delete;

	/** Move constructor. */
	StateMachine(StateMachine<Type>&& moved) noexcept : data(moved.data), state(moved.state), lastUpdate(moved.lastUpdate), deltaTime(moved.deltaTime) {
		if (state != nullptr) {
			state->stateMachine = this;
		}
		moved.data = Type();
		moved.state = nullptr;
		moved.lastUpdate = std::chrono::system_clock::now();
		moved.deltaTime = 0.0;
	}

	/** Destructor. */
	~StateMachine() {
		delete state;
		state = nullptr;
	}


	// OPERATORS

	/** Delete copy assignment operator. */
	StateMachine<Type>& operator=(const StateMachine<Type>&) = delete;

	/** Move assignment operator. */
	StateMachine<Type>& operator=(StateMachine<Type>&& moved) noexcept {
		if (this == &moved) {
			return *this;
		}
		data = moved.data;
		state = moved.state;
		lastUpdate = moved.lastUpdate;
		deltaTime = moved.deltaTime;
		if (state != nullptr) {
			state->stateMachine = this;
		}
		moved.data = Type();
		moved.state = nullptr;
		moved.lastUpdate = std::chrono::system_clock::now();
		moved.deltaTime = 0.0;
		return *this;
	}


	// GETTERS

	/** Returns the data this state machine is managing. */
	Type& GetData() {
		return data;
	}

	/** Returns the data this state machine is managing. */
	const Type& GetData() const {
		return data;
	}

	/** Returns the current state of this state machine. */
	IState<Type>* GetState() {
		return state;
	}

	/** Returns the current state of this state machine. */
	const IState<Type>* GetState() const {
		return state;
	}

	/** Returns whether the state machine's current state is not null. */
	bool IsStateValid() const {
		return state != nullptr;
	}

	/** Returns whether the state machine's current state is the given type. */
	template<typename StateType>
	bool StateIs() const {
		return state != nullptr && typeid(*state) == typeid(StateType);
	}

	/** Returns the state machine's current state as the given type. */
	template<typename StateType>
	StateType* StateAs() {
		return dynamic_cast<StateType*>(state);
	}

	/** Returns the state machine's current state as the given type. */
	template<typename StateType>
	const StateType* StateAs() const {
		return dynamic_cast<const StateType*>(state);
	}

	/** Returns the time of this state machine's last update. */
	std::chrono::system_clock::time_point GetLastUpdate() const {
		return lastUpdate;
	}

	/** Returns the time in seconds since the state machine's last update. */
	double GetDeltaTime() const {
		return deltaTime;
	}


	// SETTERS

	/** Sets the data this state machine is managing. */
	void SetData(const Type& data) {
		this->data = data;
	}

	/** Switches the state machine's current state to a new state. */
	IState<Type>* SwitchState(IState<Type>* newState) {
		IState<Type>* currentState = state;
		if (state != nullptr) {
			state->OnStateExit(newState);
		}
		state = newState;
		if (state != nullptr) {
			state->stateMachine = this;
			state->OnStateEnter(currentState);
		}
		delete currentState;
		currentState = nullptr;
		return state;
	}

	/** Updates the state machine's current state and returns the state machine's current or new state. */
	IState<Type>* Update() {
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		deltaTime = std::max((std::chrono::duration<double>(now - lastUpdate)).count(), 0.000001);
		lastUpdate = now;
		if (state != nullptr) {
			state->OnStateUpdate(deltaTime);
		}
		return state;
	}

	/** Updates the state machine until its current state is null. */
	void Unwrap() {
		while (Update() != nullptr);
	}
};
