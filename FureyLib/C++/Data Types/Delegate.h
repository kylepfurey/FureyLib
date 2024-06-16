
// Delegate and Event Data Types Script
// by Kyle Furey

#pragma once
#include <vector>
#include <map>
#include <functional>
#include <initializer_list>

// Include this heading to use the class
#include "Delegate.h"

// Represents a void function either with or without parameters.
#define METHOD(variable) std::function<void(ParameterTypes...)> variable

// Represents a function with a return type either with or without parameters.
#define FUNCTION(variable) std::function<ReturnType(ParameterTypes...)> variable

// Event interface forward declaration
class event_interface;

// Delegate interface forward declaration
class delegate_interface;

// Event interface class
class event_interface
{
public:

	// STATIC DELEGATE DATA

	// Global list of all delegates
	static std::vector<event_interface*> all_delegates;


	// DELEGATE DATA

	// Index of current delegate
	int index = 0;

protected:

	// STATIC DELEGATE DATA

	// Global cancellation token
	static bool cancelled_all;

	// Index of current invoked delegate
	static int invoke_index;


	// DELEGATE DATA

	// Delegate cancellation token
	bool cancel_invoke = false;

	// Whether the delegate is currently invoking functions
	bool invoking = false;


	// CONTRACTED FUNCTIONS

	// Cancel function
	virtual void cancel() { }
};

// Delegate interface class
class delegate_interface
{
public:

	// STATIC DELEGATE DATA

	// Global list of all delegates
	static std::vector<delegate_interface*> all_delegates;


	// DELEGATE DATA

	// Index of current delegate
	int index = 0;

protected:

	// STATIC DELEGATE DATA

	// Global cancellation token
	static bool cancelled_all;

	// Index of current invoked delegate
	static int invoke_index;


	// DELEGATE DATA

	// Delegate cancellation token
	bool cancel_invoke = false;

	// Whether the delegate is currently invoking functions
	bool invoking = false;


	// CONTRACTED FUNCTIONS

	// Cancel function
	virtual void cancel() { }
};

// •  Wrapper class for a collection of functions.
// •  All stored functions must return void.
// •  All stored functions must share the same parameters.
template <typename ... ParameterTypes> class event : public event_interface
{
private:

	// DELEGATE DATA

	// List of functions included in the delegate
	std::vector<METHOD()> functions = std::vector<METHOD()>();

public:

	// DELEGATE CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	event()
	{
		functions = std::vector<METHOD()>();

		event_interface::all_delegates.push_back(this);

		index = event_interface::all_delegates.size() - 1;
	}

	// Copy constructor
	event(const event<ParameterTypes...>& delegate)
	{
		functions = delegate.functions;

		event_interface::all_delegates.push_back(this);

		index = event_interface::all_delegates.size() - 1;
	}

	// Move constructor
	event(event<ParameterTypes...>&& delegate) noexcept
	{
		functions = delegate.functions;

		delegate.functions.clear();

		event_interface::all_delegates.push_back(this);

		index = event_interface::all_delegates.size() - 1;
	}

	// Function constructor
	event(METHOD(function))
	{
		this->functions = std::vector<METHOD()>();

		this->functions.push_back(function);

		event_interface::all_delegates.push_back(this);

		index = event_interface::all_delegates.size() - 1;
	}

	// Array constructor
	event(METHOD(functions[]), int number_of_functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		event_interface::all_delegates.push_back(this);

		index = event_interface::all_delegates.size() - 1;
	}

	// Parameter constructor
	event(int number_of_functions,
		METHOD(function1) = nullptr, METHOD(function2) = nullptr, METHOD(function3) = nullptr, METHOD(function4) = nullptr,
		METHOD(function5) = nullptr, METHOD(function6) = nullptr, METHOD(function7) = nullptr, METHOD(function8) = nullptr,
		METHOD(function9) = nullptr, METHOD(function10) = nullptr, METHOD(function11) = nullptr, METHOD(function12) = nullptr,
		METHOD(function13) = nullptr, METHOD(function14) = nullptr, METHOD(function15) = nullptr, METHOD(function16) = nullptr)
	{
		this->functions = std::vector<METHOD()>();

		event_interface::all_delegates.push_back(this);

		index = event_interface::all_delegates.size() - 1;

		if (number_of_functions >= 1) {
			this->functions.push_back(function1);
		}
		else {
			return;
		}

		if (number_of_functions >= 2) {
			this->functions.push_back(function2);
		}
		else {
			return;
		}

		if (number_of_functions >= 3) {
			this->functions.push_back(function3);
		}
		else {
			return;
		}

		if (number_of_functions >= 4) {
			this->functions.push_back(function4);
		}
		else {
			return;
		}

		if (number_of_functions >= 5) {
			this->functions.push_back(function5);
		}
		else {
			return;
		}

		if (number_of_functions >= 6) {
			this->functions.push_back(function6);
		}
		else {
			return;
		}

		if (number_of_functions >= 7) {
			this->functions.push_back(function7);
		}
		else {
			return;
		}

		if (number_of_functions >= 8) {
			this->functions.push_back(function8);
		}
		else {
			return;
		}

		if (number_of_functions >= 9) {
			this->functions.push_back(function9);
		}
		else {
			return;
		}

		if (number_of_functions >= 10) {
			this->functions.push_back(function10);
		}
		else {
			return;
		}

		if (number_of_functions >= 11) {
			this->functions.push_back(function11);
		}
		else {
			return;
		}

		if (number_of_functions >= 12) {
			this->functions.push_back(function12);
		}
		else {
			return;
		}

		if (number_of_functions >= 13) {
			this->functions.push_back(function13);
		}
		else {
			return;
		}

		if (number_of_functions >= 14) {
			this->functions.push_back(function14);
		}
		else {
			return;
		}

		if (number_of_functions >= 15) {
			this->functions.push_back(function15);
		}
		else {
			return;
		}

		if (number_of_functions >= 16) {
			this->functions.push_back(function16);
		}
		else {
			return;
		}
	}

	// Vector constructor
	event(std::vector<METHOD()> functions)
	{
		functions = functions;

		event_interface::all_delegates.push_back(this);

		index = event_interface::all_delegates.size() - 1;
	}

	// List constructor
	event(const std::initializer_list<METHOD()> functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(*(functions.begin() + i));
		}

		event_interface::all_delegates.push_back(this);

		index = event_interface::all_delegates.size() - 1;
	}

	// Delegate constructor
	event(event<ParameterTypes...>& functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		event_interface::all_delegates.push_back(this);

		index = event_interface::all_delegates.size() - 1;
	}

	// Deconstructor
	~event()
	{
		for (int i = index + 1; i < event_interface::all_delegates.size(); i++)
		{
			event_interface::all_delegates[i]->index--;
		}

		event_interface::all_delegates.erase(std::find(event_interface::all_delegates.begin(), event_interface::all_delegates.end(), this));
	}


	// DELEGATE FUNCTIONS

	// Call each function in the delegate and return if the invoke was successful
	bool invoke(ParameterTypes... parameters)
	{
		cancel_invoke = false;

		event_interface::cancelled_all = false;

		event_interface::invoke_index = index;

		invoking = true;

		for (int i = 0; i < functions.size(); i++)
		{
			functions[i](parameters...);

			if (cancel_invoke || event_interface::cancelled_all)
			{
				invoking = false;

				return false;
			}
		}

		invoking = false;

		return true;
	}

	// Cancel an invoke
	void cancel() override
	{
		cancel_invoke = true;
	}

	// Cancel all invokes
	static void cancel_all()
	{
		event_interface::cancelled_all = true;
	}

	// Cancel the current invoke
	static void cancel_current()
	{
		event_interface::all_delegates[event_interface::invoke_index]->cancel_invoke = true;
	}

	// Returns whether the delegate is currently being invoked
	bool is_invoking()
	{
		return invoking;
	}


	// COLLECTION FUNCTIONS

	// Gets a function in the delegate
	auto get(int index)
	{
		return functions[index];
	}

	// Sets a function in the delegate
	event<ParameterTypes...>& set(int index, METHOD(function))
	{
		functions[index] = function;

		return *this;
	}

	// Add a new function to the delegate
	event<ParameterTypes...>& add(METHOD(function))
	{
		functions.push_back(function);

		return *this;
	}

	// Adds new functions to the delegate
	event<ParameterTypes...>& add(int number_of_functions, METHOD(functions[]))
	{
		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Adds new functions to the delegate
	event<ParameterTypes...>& add(std::vector<METHOD()> functions)
	{
		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Add a delegate to the delegate
	event<ParameterTypes...>& add(event<ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Remove a function from the delegate
	event<ParameterTypes...>& remove(METHOD(function))
	{
		functions.erase(std::find(functions.begin(), functions.end(), function));

		return *this;
	}

	// Remove a delegate from the delegate
	event<ParameterTypes...>& remove(event<ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.count(); i++)
		{
			functions.erase(std::find(this->functions.begin(), this->functions.end(), functions[i]));
		}

		return *this;
	}

	// Remove a function from the delegate
	event<ParameterTypes...>& remove_at(int index)
	{
		functions.erase(functions.begin() + index);

		return *this;
	}

	// Clear all functions from the delegate
	event<ParameterTypes...>& clear()
	{
		functions.clear();

		return *this;
	}

	// Return the number of functions in the delegate
	int count()
	{
		return functions.size();
	}

	// Returns if the delegate contains a function
	bool contains(METHOD(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return true;
			}
		}

		return false;
	}

	// Returns the index of the function in the delegate, or -1 if it was not found
	int find(METHOD(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns a new pointer to a new array of the current functions (must be deallocated)
	auto to_new_array()
	{
		auto functions = new void[this->functions.size()](ParameterTypes...);

		for (int i = 0; i < this->functions.size(); i++)
		{
			functions[i] = this->functions[i];
		}

		return functions;
	}

	// Returns a vector of the functions
	auto to_vector()
	{
		return functions;
	}


	// ASSIGNMENT OPERATORS

	// Copy assignment operator
	event<ParameterTypes...>& operator=(const event<ParameterTypes...>& delegate)
	{
		functions = delegate.functions;

		return *this;
	}

	// Move assignment operator
	event<ParameterTypes...>& operator=(event<ParameterTypes...>&& delegate) noexcept
	{
		functions = delegate.functions;

		delegate.functions.clear();

		return *this;
	}


	// COLLECTION OPERATORS

	// Adding a function
	event<ParameterTypes...>& operator+(METHOD(function))
	{
		return add(function);
	}

	// Adding a function
	event<ParameterTypes...>& operator+=(METHOD(function))
	{
		return add(function);
	}

	// Removing a function
	event<ParameterTypes...>& operator-(METHOD(function))
	{
		return remove(function);
	}

	// Removing a function
	event<ParameterTypes...>& operator-=(METHOD(function))
	{
		return remove(function);
	}
};

// •  Wrapper class for a collection of functions.
// •  All stored functions must share the same return type.
// •  All stored functions must share the same parameters.
template <typename ReturnType, typename ... ParameterTypes> class delegate : public delegate_interface
{
private:

	// DELEGATE DATA

	// List of functions included in the delegate
	std::vector<FUNCTION()> functions = std::vector<FUNCTION()>();

public:

	// DELEGATE CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	delegate()
	{
		functions = std::vector<FUNCTION()>();

		delegate_interface::all_delegates.push_back(this);

		index = delegate_interface::all_delegates.size() - 1;
	}

	// Copy constructor
	delegate(const delegate<ReturnType, ParameterTypes...>& delegate)
	{
		functions = delegate.functions;

		delegate_interface::all_delegates.push_back(this);

		index = delegate_interface::all_delegates.size() - 1;
	}

	// Move constructor
	delegate(event<ReturnType, ParameterTypes...>&& delegate) noexcept
	{
		functions = delegate.functions;

		delegate.functions.clear();

		delegate_interface::all_delegates.push_back(this);

		index = delegate_interface::all_delegates.size() - 1;
	}

	// Function constructor
	delegate(FUNCTION(function))
	{
		this->functions = std::vector<FUNCTION()>();

		this->functions.push_back(function);

		delegate_interface::all_delegates.push_back(this);

		index = delegate_interface::all_delegates.size() - 1;
	}

	// Array constructor
	delegate(FUNCTION(functions[]), int number_of_functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		delegate_interface::all_delegates.push_back(this);

		index = delegate_interface::all_delegates.size() - 1;
	}

	// Parameter constructor
	delegate(int number_of_functions,
		FUNCTION(function1) = nullptr, FUNCTION(function2) = nullptr, FUNCTION(function3) = nullptr, FUNCTION(function4) = nullptr,
		FUNCTION(function5) = nullptr, FUNCTION(function6) = nullptr, FUNCTION(function7) = nullptr, FUNCTION(function8) = nullptr,
		FUNCTION(function9) = nullptr, FUNCTION(function10) = nullptr, FUNCTION(function11) = nullptr, FUNCTION(function12) = nullptr,
		FUNCTION(function13) = nullptr, FUNCTION(function14) = nullptr, FUNCTION(function15) = nullptr, FUNCTION(function16) = nullptr)
	{
		this->functions = std::vector<FUNCTION()>();

		delegate_interface::all_delegates.push_back(this);

		index = delegate_interface::all_delegates.size() - 1;

		if (number_of_functions >= 1) {
			this->functions.push_back(function1);
		}
		else {
			return;
		}

		if (number_of_functions >= 2) {
			this->functions.push_back(function2);
		}
		else {
			return;
		}

		if (number_of_functions >= 3) {
			this->functions.push_back(function3);
		}
		else {
			return;
		}

		if (number_of_functions >= 4) {
			this->functions.push_back(function4);
		}
		else {
			return;
		}

		if (number_of_functions >= 5) {
			this->functions.push_back(function5);
		}
		else {
			return;
		}

		if (number_of_functions >= 6) {
			this->functions.push_back(function6);
		}
		else {
			return;
		}

		if (number_of_functions >= 7) {
			this->functions.push_back(function7);
		}
		else {
			return;
		}

		if (number_of_functions >= 8) {
			this->functions.push_back(function8);
		}
		else {
			return;
		}

		if (number_of_functions >= 9) {
			this->functions.push_back(function9);
		}
		else {
			return;
		}

		if (number_of_functions >= 10) {
			this->functions.push_back(function10);
		}
		else {
			return;
		}

		if (number_of_functions >= 11) {
			this->functions.push_back(function11);
		}
		else {
			return;
		}

		if (number_of_functions >= 12) {
			this->functions.push_back(function12);
		}
		else {
			return;
		}

		if (number_of_functions >= 13) {
			this->functions.push_back(function13);
		}
		else {
			return;
		}

		if (number_of_functions >= 14) {
			this->functions.push_back(function14);
		}
		else {
			return;
		}

		if (number_of_functions >= 15) {
			this->functions.push_back(function15);
		}
		else {
			return;
		}

		if (number_of_functions >= 16) {
			this->functions.push_back(function16);
		}
		else {
			return;
		}
	}

	// Vector constructor
	delegate(std::vector<FUNCTION()> functions)
	{
		functions = functions;

		delegate_interface::all_delegates.push_back(this);

		index = delegate_interface::all_delegates.size() - 1;
	}

	// List constructor
	delegate(const std::initializer_list<FUNCTION()> functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(*(functions.begin() + i));
		}

		delegate_interface::all_delegates.push_back(this);

		index = delegate_interface::all_delegates.size() - 1;
	}

	// Delegate constructor
	delegate(delegate<ReturnType, ParameterTypes...>& functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		delegate_interface::all_delegates.push_back(this);

		index = delegate_interface::all_delegates.size() - 1;
	}

	// Deconstructor
	~delegate()
	{
		for (int i = index + 1; i < delegate_interface::all_delegates.size(); i++)
		{
			delegate_interface::all_delegates[i]->index--;
		}

		delegate_interface::all_delegates.erase(std::find(delegate_interface::all_delegates.begin(), delegate_interface::all_delegates.end(), this));
	}


	// DELEGATE FUNCTIONS

	// Returns a dictionary with each key representing the function and the value being the returned data
	auto invoke(ParameterTypes... parameters)
	{
		cancel_invoke = false;

		delegate_interface::cancelled_all = false;

		delegate_interface::invoke_index = index;

		invoking = true;

		std::map<FUNCTION(), ReturnType> returns = std::map<FUNCTION(), ReturnType>();

		for (int i = 0; i < functions.size(); i++)
		{
			returns[functions[i]] = functions[i](parameters...);

			if (cancel_invoke || delegate_interface::cancelled_all)
			{
				for (int j = i + 1; j < functions.size(); j++)
				{
					returns[functions[i]] = ReturnType();
				}

				break;
			}
		}

		invoking = false;

		return returns;
	}

	// Cancel an invoke
	void cancel() override
	{
		cancel_invoke = true;
	}

	// Cancel all invokes
	static void cancel_all()
	{
		delegate_interface::cancelled_all = true;
	}

	// Cancel the current invoke
	static void cancel_current()
	{
		delegate_interface::all_delegates[delegate_interface::invoke_index]->cancel_invoke = true;
	}

	// Returns whether the delegate is currently being invoked
	bool is_invoking()
	{
		return invoking;
	}


	// COLLECTION FUNCTIONS

	// Gets a function in the delegate
	auto get(int index)
	{
		return functions[index];
	}

	// Sets a function in the delegate
	delegate<ReturnType, ParameterTypes...>& set(int index, FUNCTION(function))
	{
		functions[index] = function;

		return *this;
	}

	// Add a new function to the delegate
	delegate<ReturnType, ParameterTypes...>& add(FUNCTION(function))
	{
		functions.push_back(function);

		return *this;
	}

	// Adds new functions to the delegate
	delegate<ReturnType, ParameterTypes...>& add(int number_of_functions, FUNCTION(functions[]))
	{
		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Adds new functions to the delegate
	delegate<ReturnType, ParameterTypes...>& add(std::vector<FUNCTION()> functions)
	{
		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Add a delegate to the delegate
	delegate<ReturnType, ParameterTypes...>& add(delegate<ReturnType, ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Remove a function from the delegate
	delegate<ReturnType, ParameterTypes...>& remove(FUNCTION(function))
	{
		functions.erase(std::find(functions.begin(), functions.end(), function));

		return *this;
	}

	// Remove a delegate from the delegate
	delegate<ReturnType, ParameterTypes...>& remove(delegate<ReturnType, ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.erase(std::find(this->functions.begin(), this->functions.end(), functions[i]));
		}

		return *this;
	}

	// Remove a function from the delegate
	delegate<ReturnType, ParameterTypes...>& remove_at(int index)
	{
		functions.erase(functions.begin() + index);

		return *this;
	}

	// Clear all functions from the delegate
	delegate<ReturnType, ParameterTypes...>& clear()
	{
		functions.clear();

		return *this;
	}

	// Return the number of functions in the delegate
	int count()
	{
		return functions.size();
	}

	// Returns if the delegate contains a function
	bool contains(FUNCTION(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return true;
			}
		}

		return false;
	}

	// Returns the index of the function in the delegate, or -1 if it was not found
	int find(FUNCTION(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns a new pointer to a new array of the current functions (must be deallocated)
	auto to_new_array()
	{
		auto functions = new ReturnType[this->functions.size()](ParameterTypes...);

		for (int i = 0; i < this->functions.size(); i++)
		{
			functions[i] = this->functions[i];
		}

		return functions;
	}

	// Returns a vector of the functions
	auto to_vector()
	{
		return functions;
	}


	// ASSIGNMENT OPERATORS

	// Copy assignment operator
	delegate<ReturnType, ParameterTypes...>& operator=(const delegate<ReturnType, ParameterTypes...>& delegate)
	{
		functions = delegate.functions;

		return *this;
	}

	// Move assignment operator
	delegate<ReturnType, ParameterTypes...>& operator=(delegate<ReturnType, ParameterTypes...>&& delegate) noexcept
	{
		functions = delegate.functions;

		delegate.functions.clear();

		return *this;
	}


	// COLLECTION OPERATORS

	// Adding a function
	delegate<ReturnType, ParameterTypes...>& operator+(FUNCTION(function))
	{
		return add(function);
	}

	// Adding a function
	delegate<ReturnType, ParameterTypes...>& operator+=(FUNCTION(function))
	{
		return add(function);
	}

	// Removing a function
	delegate<ReturnType, ParameterTypes...>& operator-(FUNCTION(function))
	{
		return remove(function);
	}

	// Removing a function
	delegate<ReturnType, ParameterTypes...>& operator-=(FUNCTION(function))
	{
		return remove(function);
	}
};

// Static variable initialization
std::vector<event_interface*> event_interface::all_delegates = std::vector<event_interface*>();
bool event_interface::cancelled_all = false;
int event_interface::invoke_index = 0;
std::vector<delegate_interface*> delegate_interface::all_delegates = std::vector<delegate_interface*>();
bool delegate_interface::cancelled_all = false;
int delegate_interface::invoke_index = 0;

// Event interface forward declaration
class IEvent;

// Delegate interface forward declaration
class IDelegate;

// Event interface class
class IEvent
{
public:

	// STATIC DELEGATE DATA

	// Global list of all delegates
	static std::vector<IEvent*> allDelegates;


	// DELEGATE DATA

	// Index of current delegate
	int index = 0;

protected:

	// STATIC DELEGATE DATA

	// Global cancellation token
	static bool cancelledAll;

	// Index of current invoked delegate
	static int invokeIndex;


	// DELEGATE DATA

	// Delegate cancellation token
	bool cancelInvoke = false;

	// Whether the delegate is currently invoking functions
	bool invoking = false;


	// CONTRACTED FUNCTIONS

	// Cancel function
	virtual void Cancel() { }
};

// Delegate interface class
class IDelegate
{
public:

	// STATIC DELEGATE DATA

	// Global list of all delegates
	static std::vector<IDelegate*> allDelegates;


	// DELEGATE DATA

	// Index of current delegate
	int index = 0;

protected:

	// STATIC DELEGATE DATA

	// Global cancellation token
	static bool cancelledAll;

	// Index of current invoked delegate
	static int invokeIndex;


	// DELEGATE DATA

	// Delegate cancellation token
	bool cancelInvoke = false;

	// Whether the delegate is currently invoking functions
	bool invoking = false;


	// CONTRACTED FUNCTIONS

	// Cancel function
	virtual void Cancel() { }
};

// •  Wrapper class for a collection of functions.
// •  All stored functions must return void.
// •  All stored functions must share the same parameters.
template <typename ... ParameterTypes> class Event : public IEvent
{
private:

	// DELEGATE DATA

	// List of functions included in the delegate
	std::vector<METHOD()> functions = std::vector<METHOD()>();

public:

	// DELEGATE CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	Event()
	{
		functions = std::vector<METHOD()>();

		IEvent::allDelegates.push_back(this);

		index = IEvent::allDelegates.size() - 1;
	}

	// Copy constructor
	Event(const Event<ParameterTypes...>& delegate)
	{
		functions = delegate.functions;

		IEvent::allDelegates.push_back(this);

		index = IEvent::allDelegates.size() - 1;
	}

	// Move constructor
	Event(Event<ParameterTypes...>&& delegate) noexcept
	{
		functions = delegate.functions;

		delegate.functions.clear();

		IEvent::allDelegates.push_back(this);

		index = IEvent::allDelegates.size() - 1;
	}

	// Function constructor
	Event(METHOD(function))
	{
		this->functions = std::vector<METHOD()>();

		this->functions.push_back(function);

		IEvent::allDelegates.push_back(this);

		index = IEvent::allDelegates.size() - 1;
	}

	// Array constructor
	Event(METHOD(functions[]), int number_of_functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		IEvent::allDelegates.push_back(this);

		index = IEvent::allDelegates.size() - 1;
	}

	// Parameter constructor
	Event(int number_of_functions,
		METHOD(function1) = nullptr, METHOD(function2) = nullptr, METHOD(function3) = nullptr, METHOD(function4) = nullptr,
		METHOD(function5) = nullptr, METHOD(function6) = nullptr, METHOD(function7) = nullptr, METHOD(function8) = nullptr,
		METHOD(function9) = nullptr, METHOD(function10) = nullptr, METHOD(function11) = nullptr, METHOD(function12) = nullptr,
		METHOD(function13) = nullptr, METHOD(function14) = nullptr, METHOD(function15) = nullptr, METHOD(function16) = nullptr)
	{
		this->functions = std::vector<METHOD()>();

		IEvent::allDelegates.push_back(this);

		index = IEvent::allDelegates.size() - 1;

		if (number_of_functions >= 1) {
			this->functions.push_back(function1);
		}
		else {
			return;
		}

		if (number_of_functions >= 2) {
			this->functions.push_back(function2);
		}
		else {
			return;
		}

		if (number_of_functions >= 3) {
			this->functions.push_back(function3);
		}
		else {
			return;
		}

		if (number_of_functions >= 4) {
			this->functions.push_back(function4);
		}
		else {
			return;
		}

		if (number_of_functions >= 5) {
			this->functions.push_back(function5);
		}
		else {
			return;
		}

		if (number_of_functions >= 6) {
			this->functions.push_back(function6);
		}
		else {
			return;
		}

		if (number_of_functions >= 7) {
			this->functions.push_back(function7);
		}
		else {
			return;
		}

		if (number_of_functions >= 8) {
			this->functions.push_back(function8);
		}
		else {
			return;
		}

		if (number_of_functions >= 9) {
			this->functions.push_back(function9);
		}
		else {
			return;
		}

		if (number_of_functions >= 10) {
			this->functions.push_back(function10);
		}
		else {
			return;
		}

		if (number_of_functions >= 11) {
			this->functions.push_back(function11);
		}
		else {
			return;
		}

		if (number_of_functions >= 12) {
			this->functions.push_back(function12);
		}
		else {
			return;
		}

		if (number_of_functions >= 13) {
			this->functions.push_back(function13);
		}
		else {
			return;
		}

		if (number_of_functions >= 14) {
			this->functions.push_back(function14);
		}
		else {
			return;
		}

		if (number_of_functions >= 15) {
			this->functions.push_back(function15);
		}
		else {
			return;
		}

		if (number_of_functions >= 16) {
			this->functions.push_back(function16);
		}
		else {
			return;
		}
	}

	// Vector constructor
	Event(std::vector<METHOD()> functions)
	{
		functions = functions;

		IEvent::allDelegates.push_back(this);

		index = IEvent::allDelegates.size() - 1;
	}

	// List constructor
	Event(const std::initializer_list<METHOD()> functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(*(functions.begin() + i));
		}

		IEvent::allDelegates.push_back(this);

		index = IEvent::allDelegates.size() - 1;
	}

	// Delegate constructor
	Event(Event<ParameterTypes...>& functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < functions.Count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		IEvent::allDelegates.push_back(this);

		index = IEvent::allDelegates.size() - 1;
	}

	// Deconstructor
	~Event()
	{
		for (int i = index + 1; i < IEvent::allDelegates.size(); i++)
		{
			IEvent::allDelegates[i]->index--;
		}

		IEvent::allDelegates.erase(std::find(IEvent::allDelegates.begin(), IEvent::allDelegates.end(), this));
	}


	// DELEGATE FUNCTIONS

	// Call each function in the delegate and return if the invoke was successful
	bool Invoke(ParameterTypes... parameters)
	{
		cancelInvoke = false;

		IEvent::cancelledAll = false;

		IEvent::invokeIndex = index;

		invoking = true;

		for (int i = 0; i < functions.size(); i++)
		{
			functions[i](parameters...);

			if (cancelInvoke || IEvent::cancelledAll)
			{
				invoking = false;

				return false;
			}
		}

		invoking = false;

		return true;
	}

	// Cancel an invoke
	void Cancel() override
	{
		cancelInvoke = true;
	}

	// Cancel all invokes
	static void CancelAll()
	{
		IEvent::cancelledAll = true;
	}

	// Cancel the current invoke
	static void CancelCurrent()
	{
		IEvent::allDelegates[IEvent::invokeIndex]->cancelInvoke = true;
	}

	// Returns whether the delegate is currently being invoked
	bool IsInvoking()
	{
		return invoking;
	}


	// COLLECTION FUNCTIONS

	// Gets a function in the delegate
	auto Get(int index)
	{
		return functions[index];
	}

	// Sets a function in the delegate
	Event<ParameterTypes...>& Set(int index, METHOD(function))
	{
		functions[index] = function;

		return *this;
	}

	// Add a new function to the delegate
	Event<ParameterTypes...>& Add(METHOD(function))
	{
		functions.push_back(function);

		return *this;
	}

	// Adds new functions to the delegate
	Event<ParameterTypes...>& Add(int number_of_functions, METHOD(functions[]))
	{
		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Adds new functions to the delegate
	Event<ParameterTypes...>& Add(std::vector<METHOD()> functions)
	{
		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Add a delegate to the delegate
	Event<ParameterTypes...>& Add(Event<ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.Count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Remove a function from the delegate
	Event<ParameterTypes...>& Remove(METHOD(function))
	{
		functions.erase(std::find(functions.begin(), functions.end(), function));

		return *this;
	}

	// Remove a delegate from the delegate
	Event<ParameterTypes...>& Remove(Event<ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.Count(); i++)
		{
			functions.erase(std::find(this->functions.begin(), this->functions.end(), functions[i]));
		}

		return *this;
	}

	// Remove a function from the delegate
	Event<ParameterTypes...>& RemoveAt(int index)
	{
		functions.erase(functions.begin() + index);

		return *this;
	}

	// Clear all functions from the delegate
	Event<ParameterTypes...>& Clear()
	{
		functions.clear();

		return *this;
	}

	// Return the number of functions in the delegate
	int Count()
	{
		return functions.size();
	}

	// Returns if the delegate contains a function
	bool Contains(METHOD(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return true;
			}
		}

		return false;
	}

	// Returns the index of the function in the delegate, or -1 if it was not found
	int Find(METHOD(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns a new pointer to a new array of the current functions (must be deallocated)
	auto ToNewArray()
	{
		auto functions = new void[this->functions.size()](ParameterTypes...);

		for (int i = 0; i < this->functions.size(); i++)
		{
			functions[i] = this->functions[i];
		}

		return functions;
	}

	// Returns a vector of the functions
	auto ToVector()
	{
		return functions;
	}


	// ASSIGNMENT OPERATORS

	// Copy assignment operator
	Event<ParameterTypes...>& operator=(const Event<ParameterTypes...>& delegate)
	{
		functions = delegate.functions;

		return *this;
	}

	// Move assignment operator
	Event<ParameterTypes...>& operator=(Event<ParameterTypes...>&& delegate) noexcept
	{
		functions = delegate.functions;

		delegate.functions.clear();

		return *this;
	}


	// COLLECTION OPERATORS

	// Adding a function
	Event<ParameterTypes...>& operator+(METHOD(function))
	{
		return add(function);
	}

	// Adding a function
	Event<ParameterTypes...>& operator+=(METHOD(function))
	{
		return add(function);
	}

	// Removing a function
	Event<ParameterTypes...>& operator-(METHOD(function))
	{
		return remove(function);
	}

	// Removing a function
	Event<ParameterTypes...>& operator-=(METHOD(function))
	{
		return remove(function);
	}
};

// •  Wrapper class for a collection of functions.
// •  All stored functions must share the same return type.
// •  All stored functions must share the same parameters.
template <typename ReturnType, typename ... ParameterTypes> class Delegate : public IDelegate
{
private:

	// DELEGATE DATA

	// List of functions included in the delegate
	std::vector<FUNCTION()> functions = std::vector<FUNCTION()>();

	// Whether the delegate is currently invoking functions
	bool invoking = false;

	// Delegate cancellation token
	bool cancelInvoke = false;

	// Index of current delegate
	int index = 0;

public:

	// DELEGATE CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	Delegate()
	{
		functions = std::vector<FUNCTION()>();

		IDelegate::allDelegates.push_back(this);

		index = IDelegate::allDelegates.size() - 1;
	}

	// Copy constructor
	Delegate(const Delegate<ReturnType, ParameterTypes...>& delegate)
	{
		functions = delegate.functions;

		IDelegate::allDelegates.push_back(this);

		index = IDelegate::allDelegates.size() - 1;
	}

	// Move constructor
	Delegate(Delegate<ReturnType, ParameterTypes...>&& delegate) noexcept
	{
		functions = delegate.functions;

		delegate.functions.clear();

		IDelegate::allDelegates.push_back(this);

		index = IDelegate::allDelegates.size() - 1;
	}

	// Function constructor
	Delegate(FUNCTION(function))
	{
		this->functions = std::vector<FUNCTION()>();

		this->functions.push_back(function);

		IDelegate::allDelegates.push_back(this);

		index = IDelegate::allDelegates.size() - 1;
	}

	// Array constructor
	Delegate(FUNCTION(functions[]), int number_of_functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		IDelegate::allDelegates.push_back(this);

		index = IDelegate::allDelegates.size() - 1;
	}

	// Parameter constructor
	Delegate(int number_of_functions,
		FUNCTION(function1) = nullptr, FUNCTION(function2) = nullptr, FUNCTION(function3) = nullptr, FUNCTION(function4) = nullptr,
		FUNCTION(function5) = nullptr, FUNCTION(function6) = nullptr, FUNCTION(function7) = nullptr, FUNCTION(function8) = nullptr,
		FUNCTION(function9) = nullptr, FUNCTION(function10) = nullptr, FUNCTION(function11) = nullptr, FUNCTION(function12) = nullptr,
		FUNCTION(function13) = nullptr, FUNCTION(function14) = nullptr, FUNCTION(function15) = nullptr, FUNCTION(function16) = nullptr)
	{
		this->functions = std::vector<FUNCTION()>();

		IDelegate::allDelegates.push_back(this);

		index = IDelegate::allDelegates.size() - 1;

		if (number_of_functions >= 1) {
			this->functions.push_back(function1);
		}
		else {
			return;
		}

		if (number_of_functions >= 2) {
			this->functions.push_back(function2);
		}
		else {
			return;
		}

		if (number_of_functions >= 3) {
			this->functions.push_back(function3);
		}
		else {
			return;
		}

		if (number_of_functions >= 4) {
			this->functions.push_back(function4);
		}
		else {
			return;
		}

		if (number_of_functions >= 5) {
			this->functions.push_back(function5);
		}
		else {
			return;
		}

		if (number_of_functions >= 6) {
			this->functions.push_back(function6);
		}
		else {
			return;
		}

		if (number_of_functions >= 7) {
			this->functions.push_back(function7);
		}
		else {
			return;
		}

		if (number_of_functions >= 8) {
			this->functions.push_back(function8);
		}
		else {
			return;
		}

		if (number_of_functions >= 9) {
			this->functions.push_back(function9);
		}
		else {
			return;
		}

		if (number_of_functions >= 10) {
			this->functions.push_back(function10);
		}
		else {
			return;
		}

		if (number_of_functions >= 11) {
			this->functions.push_back(function11);
		}
		else {
			return;
		}

		if (number_of_functions >= 12) {
			this->functions.push_back(function12);
		}
		else {
			return;
		}

		if (number_of_functions >= 13) {
			this->functions.push_back(function13);
		}
		else {
			return;
		}

		if (number_of_functions >= 14) {
			this->functions.push_back(function14);
		}
		else {
			return;
		}

		if (number_of_functions >= 15) {
			this->functions.push_back(function15);
		}
		else {
			return;
		}

		if (number_of_functions >= 16) {
			this->functions.push_back(function16);
		}
		else {
			return;
		}
	}

	// Vector constructor
	Delegate(std::vector<FUNCTION()> functions)
	{
		functions = functions;

		IDelegate::allDelegates.push_back(this);

		index = IDelegate::allDelegates.size() - 1;
	}

	// List constructor
	Delegate(const std::initializer_list<FUNCTION()> functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(*(functions.begin() + i));
		}

		IDelegate::allDelegates.push_back(this);

		index = IDelegate::allDelegates.size() - 1;
	}

	// Delegate constructor
	Delegate(Delegate<ReturnType, ParameterTypes...>& functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < functions.Count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		IDelegate::allDelegates.push_back(this);

		index = IDelegate::allDelegates.size() - 1;
	}

	// Deconstructor
	~Delegate()
	{
		for (int i = index + 1; i < IDelegate::allDelegates.size(); i++)
		{
			IDelegate::allDelegates[i]->index--;
		}

		IDelegate::allDelegates.erase(std::find(IDelegate::allDelegates.begin(), IDelegate::allDelegates.end(), this));
	}


	// DELEGATE FUNCTIONS

	// Returns a dictionary with each key representing the function and the value being the returned data
	auto Invoke(ParameterTypes... parameters)
	{
		cancelInvoke = false;

		IDelegate::cancelledAll = false;

		IDelegate::invokeIndex = index;

		invoking = true;

		std::map<FUNCTION(), ReturnType> returns = std::map<FUNCTION(), ReturnType>();

		for (int i = 0; i < functions.size(); i++)
		{
			returns[functions[i]] = functions[i](parameters...);

			if (cancelInvoke || IDelegate::cancelledAll)
			{
				for (int j = i + 1; j < functions.size(); j++)
				{
					returns[functions[i]] = ReturnType();
				}

				break;
			}
		}

		invoking = false;

		return returns;
	}

	// Cancel an invoke
	void Cancel() override
	{
		cancelInvoke = true;
	}

	// Cancel all invokes
	static void CancelAll()
	{
		IDelegate::cancelledAll = true;
	}

	// Cancel the current invoke
	static void CancelCurrent()
	{
		IDelegate::allDelegates[IDelegate::invokeIndex]->cancelInvoke = true;
	}

	// Returns whether the delegate is currently being invoked
	bool IsInvoking()
	{
		return invoking;
	}


	// COLLECTION FUNCTIONS

	// Gets a function in the delegate
	auto Get(int index)
	{
		return functions[index];
	}

	// Sets a function in the delegate
	Delegate<ReturnType, ParameterTypes...>& Set(int index, FUNCTION(function))
	{
		functions[index] = function;

		return *this;
	}

	// Add a new function to the delegate
	Delegate<ReturnType, ParameterTypes...>& Add(FUNCTION(function))
	{
		functions.push_back(function);

		return *this;
	}

	// Adds new functions to the delegate
	Delegate<ReturnType, ParameterTypes...>& Add(int number_of_functions, FUNCTION(functions[]))
	{
		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Adds new functions to the delegate
	Delegate<ReturnType, ParameterTypes...>& Add(std::vector<FUNCTION()> functions)
	{
		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Add a delegate to the delegate
	Delegate<ReturnType, ParameterTypes...>& Add(Delegate<ReturnType, ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.Count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Remove a function from the delegate
	Delegate<ReturnType, ParameterTypes...>& Remove(FUNCTION(function))
	{
		functions.erase(std::find(functions.begin(), functions.end(), function));

		return *this;
	}

	// Remove a delegate from the delegate
	Delegate<ReturnType, ParameterTypes...>& Remove(Delegate<ReturnType, ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.Count(); i++)
		{
			this->functions.erase(std::find(this->functions.begin(), this->functions.end(), functions[i]));
		}

		return *this;
	}

	// Remove a function from the delegate
	Delegate<ReturnType, ParameterTypes...>& RemoveAt(int index)
	{
		functions.erase(functions.begin() + index);

		return *this;
	}

	// Clear all functions from the delegate
	Delegate<ReturnType, ParameterTypes...>& Clear()
	{
		functions.clear();

		return *this;
	}

	// Return the number of functions in the delegate
	int Count()
	{
		return functions.size();
	}

	// Returns if the delegate contains a function
	bool Contains(FUNCTION(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return true;
			}
		}

		return false;
	}

	// Returns the index of the function in the delegate, or -1 if it was not found
	int Find(FUNCTION(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns a new pointer to a new array of the current functions (must be deallocated)
	auto ToNewArray()
	{
		auto functions = new ReturnType[this->functions.size()](ParameterTypes...);

		for (int i = 0; i < this->functions.size(); i++)
		{
			functions[i] = this->functions[i];
		}

		return functions;
	}

	// Returns a vector of the functions
	auto ToVector()
	{
		return functions;
	}


	// ASSIGNMENT OPERATORS

	// Copy assignment operator
	Delegate<ReturnType, ParameterTypes...>& operator=(const Delegate<ReturnType, ParameterTypes...>& delegate)
	{
		functions = delegate.functions;

		return *this;
	}

	// Move assignment operator
	Delegate<ReturnType, ParameterTypes...>& operator=(Delegate<ReturnType, ParameterTypes...>&& delegate) noexcept
	{
		functions = delegate.functions;

		delegate.functions.clear();

		return *this;
	}


	// COLLECTION OPERATORS

	// Adding a function
	Delegate<ReturnType, ParameterTypes...>& operator+(FUNCTION(function))
	{
		return add(function);
	}

	// Adding a function
	Delegate<ReturnType, ParameterTypes...>& operator+=(FUNCTION(function))
	{
		return add(function);
	}

	// Removing a function
	Delegate<ReturnType, ParameterTypes...>& operator-(FUNCTION(function))
	{
		return remove(function);
	}

	// Removing a function
	Delegate<ReturnType, ParameterTypes...>& operator-=(FUNCTION(function))
	{
		return remove(function);
	}
};

// Static variable initialization
std::vector<IEvent*> IEvent::allDelegates = std::vector<IEvent*>();
bool IEvent::cancelledAll = false;
int IEvent::invokeIndex = 0;
std::vector<IDelegate*> IDelegate::allDelegates = std::vector<IDelegate*>();
bool IDelegate::cancelledAll = false;
int IDelegate::invokeIndex = 0;
