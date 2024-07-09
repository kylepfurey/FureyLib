
// Delegate and Event Data Types Script
// by Kyle Furey

#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include <initializer_list>

// Include this heading to use the class
#include "delegate.h"

// Represents a void function pointer either with or without parameters.
#define METHOD(variable) void (*variable) (parameter_types...)

// Represents a function pointer with a return type either with or without parameters.
#define FUNCTION(variable) return_type (*variable) (parameter_types...)

// Forward declaration of event
template <typename ... parameter_types> class event;

// •  Wrapper class for a collection of functions.
// •  All stored functions must return void.
// •  All stored functions must share the same parameters.
template <typename ... parameter_types> class event
{
private:

	// STATIC DELEGATE DATA

	// Global list of all delegates
	static std::vector<event<parameter_types...>*> all_delegates;

	// Global cancellation token
	static bool cancelled_all;

	// Index of current invoked delegate
	static int invoke_index;


	// DELEGATE DATA

	// List of functions included in the delegate
	std::vector<METHOD()> functions = std::vector<METHOD()>();

	// Whether the delegate is currently invoking functions
	bool invoking = false;

	// Delegate cancellation token
	bool cancel_invoke = false;

	// Index of current delegate
	int index = 0;

public:

	// DELEGATE CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	event()
	{
		functions = std::vector<METHOD()>();

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Copy constructor
	event(const event<parameter_types...>& delegate)
	{
		functions = delegate.functions;

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Move constructor
	event(event<parameter_types...>&& delegate) noexcept
	{
		functions = delegate.functions;

		delegate.functions.clear();

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Function constructor
	event(METHOD(function))
	{
		this->functions = std::vector<METHOD()>();

		this->functions.push_back(function);

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Array constructor
	event(METHOD(functions[]), int number_of_functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Parameter constructor
	event(int number_of_functions,
		METHOD(function1) = nullptr, METHOD(function2) = nullptr, METHOD(function3) = nullptr, METHOD(function4) = nullptr,
		METHOD(function5) = nullptr, METHOD(function6) = nullptr, METHOD(function7) = nullptr, METHOD(function8) = nullptr,
		METHOD(function9) = nullptr, METHOD(function10) = nullptr, METHOD(function11) = nullptr, METHOD(function12) = nullptr,
		METHOD(function13) = nullptr, METHOD(function14) = nullptr, METHOD(function15) = nullptr, METHOD(function16) = nullptr)
	{
		this->functions = std::vector<METHOD()>();

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;

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

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// List constructor
	event(const std::initializer_list<METHOD()> functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(*(functions.begin() + i));
		}

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Delegate constructor
	event(event<parameter_types...>& functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Destructor
	~event()
	{
		for (int i = index + 1; i < all_delegates.size(); i++)
		{
			all_delegates[i]->index--;
		}

		all_delegates.erase(std::find(all_delegates.begin(), all_delegates.end(), this));
	}


	// DELEGATE FUNCTIONS

	// Call each function in the delegate and return if the invoke was successful
	bool invoke(parameter_types... parameters)
	{
		cancel_invoke = false;

		cancelled_all = false;

		invoke_index = index;

		invoking = true;

		for (int i = 0; i < functions.size(); i++)
		{
			functions[i](parameters...);

			if (cancel_invoke || cancelled_all)
			{
				invoking = false;

				return false;
			}
		}

		invoking = false;

		return true;
	}

	// Invokes every delegate
	static bool invoke_all(parameter_types... parameters)
	{
		for (int i = 0; i < all_delegates.size(); i++)
		{
			if (!all_delegates[i]->invoke(parameters...))
			{
				return false;
			}
		}

		return true;
	}

	// Reinvokes the current delegate
	static bool invoke_current(parameter_types... parameters)
	{
		return all_delegates[invoke_index]->invoke(parameters...);
	}

	// Cancel an invoke
	void cancel()
	{
		cancel_invoke = true;
	}

	// Cancel all invokes
	static void cancel_all()
	{
		cancelled_all = true;
	}

	// Cancel the current invoke
	static void cancel_current()
	{
		all_delegates[invoke_index]->cancel_invoke = true;
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
	event<parameter_types...>& set(int index, METHOD(function))
	{
		functions[index] = function;

		return *this;
	}

	// Add a new function to the delegate
	event<parameter_types...>& add(METHOD(function))
	{
		functions.push_back(function);

		return *this;
	}

	// Adds new functions to the delegate
	event<parameter_types...>& add(int number_of_functions, METHOD(functions[]))
	{
		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Adds new functions to the delegate
	event<parameter_types...>& add(std::vector<METHOD()> functions)
	{
		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Add a delegate to the delegate
	event<parameter_types...>& add(event<parameter_types...>& functions)
	{
		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Remove a function from the delegate
	event<parameter_types...>& remove(METHOD(function))
	{
		functions.erase(std::find(functions.begin(), functions.end(), function));

		return *this;
	}

	// Remove a delegate from the delegate
	event<parameter_types...>& remove(event<parameter_types...>& functions)
	{
		for (int i = 0; i < functions.count(); i++)
		{
			functions.erase(std::find(this->functions.begin(), this->functions.end(), functions[i]));
		}

		return *this;
	}

	// Remove a function from the delegate
	event<parameter_types...>& remove_at(int index)
	{
		functions.erase(functions.begin() + index);

		return *this;
	}

	// Clear all functions from the delegate
	event<parameter_types...>& clear()
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
		auto functions = new void[this->functions.size()](parameter_types...);

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
	event<parameter_types...>& operator=(const event<parameter_types...>& delegate)
	{
		functions = delegate.functions;

		return *this;
	}

	// Move assignment operator
	event<parameter_types...>& operator=(event<parameter_types...>&& delegate) noexcept
	{
		functions = delegate.functions;

		delegate.functions.clear();

		return *this;
	}


	// COLLECTION OPERATORS

	// Adding a function
	event<parameter_types...>& operator+(METHOD(function))
	{
		return add(function);
	}

	// Adding a function
	event<parameter_types...>& operator+=(METHOD(function))
	{
		return add(function);
	}

	// Removing a function
	event<parameter_types...>& operator-(METHOD(function))
	{
		return remove(function);
	}

	// Removing a function
	event<parameter_types...>& operator-=(METHOD(function))
	{
		return remove(function);
	}
};

// Forward declaration of delegate
template <typename return_type, typename ... parameter_types> class delegate;

// •  Wrapper class for a collection of functions.
// •  All stored functions must share the same return type.
// •  All stored functions must share the same parameters.
template <typename return_type, typename ... parameter_types> class delegate
{
private:

	// STATIC DELEGATE DATA

	// Global list of all delegates
	static std::vector<delegate<return_type, parameter_types...>*> all_delegates;

	// Global cancellation token
	static bool cancelled_all;

	// Index of current invoked delegate
	static int invoke_index;


	// DELEGATE DATA

	// List of functions included in the delegate
	std::vector<FUNCTION()> functions = std::vector<FUNCTION()>();

	// Whether the delegate is currently invoking functions
	bool invoking = false;

	// Delegate cancellation token
	bool cancel_invoke = false;

	// Index of current delegate
	int index = 0;

public:

	// DELEGATE CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	delegate()
	{
		functions = std::vector<FUNCTION()>();

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Copy constructor
	delegate(const delegate<return_type, parameter_types...>& delegate)
	{
		functions = delegate.functions;

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Move constructor
	delegate(event<return_type, parameter_types...>&& delegate) noexcept
	{
		functions = delegate.functions;

		delegate.functions.clear();

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Function constructor
	delegate(FUNCTION(function))
	{
		this->functions = std::vector<FUNCTION()>();

		this->functions.push_back(function);

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Array constructor
	delegate(FUNCTION(functions[]), int number_of_functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Parameter constructor
	delegate(int number_of_functions,
		FUNCTION(function1) = nullptr, FUNCTION(function2) = nullptr, FUNCTION(function3) = nullptr, FUNCTION(function4) = nullptr,
		FUNCTION(function5) = nullptr, FUNCTION(function6) = nullptr, FUNCTION(function7) = nullptr, FUNCTION(function8) = nullptr,
		FUNCTION(function9) = nullptr, FUNCTION(function10) = nullptr, FUNCTION(function11) = nullptr, FUNCTION(function12) = nullptr,
		FUNCTION(function13) = nullptr, FUNCTION(function14) = nullptr, FUNCTION(function15) = nullptr, FUNCTION(function16) = nullptr)
	{
		this->functions = std::vector<FUNCTION()>();

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;

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

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// List constructor
	delegate(const std::initializer_list<FUNCTION()> functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(*(functions.begin() + i));
		}

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Delegate constructor
	delegate(delegate<return_type, parameter_types...>& functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Destructor
	~delegate()
	{
		for (int i = index + 1; i < all_delegates.size(); i++)
		{
			all_delegates[i]->index--;
		}

		all_delegates.erase(std::find(all_delegates.begin(), all_delegates.end(), this));
	}


	// DELEGATE FUNCTIONS

	// Returns a map with each key representing the function and the value being the returned data
	std::map<FUNCTION(), return_type> invoke(parameter_types... parameters)
	{
		cancel_invoke = false;

		cancelled_all = false;

		invoke_index = index;

		invoking = true;

		std::map<FUNCTION(), return_type> returns = std::map<FUNCTION(), return_type>();

		for (int i = 0; i < functions.size(); i++)
		{
			returns[functions[i]] = functions[i](parameters...);

			if (cancel_invoke || cancelled_all)
			{
				for (int j = i + 1; j < functions.size(); j++)
				{
					returns[functions[i]] = return_type();
				}

				break;
			}
		}

		invoking = false;

		return returns;
	}

	// Invokes every delegate
	static std::map<delegate<return_type, parameter_types...>*, std::map<FUNCTION(), return_type>> invoke_all(parameter_types... parameters)
	{
		std::map<delegate<return_type, parameter_types...>*, std::map<FUNCTION(), return_type>> returns = std::map<delegate<return_type, parameter_types...>*, std::map<FUNCTION(), return_type>>();

		for (int i = 0; i < all_delegates.size(); i++)
		{
			returns[all_delegates[i]] = all_delegates[i]->invoke(parameters...);;

			if (all_delegates[i]->cancel_invoke || cancelled_all)
			{
				break;
			}
		}

		return returns;
	}

	// Reinvokes the current delegate
	static std::map<FUNCTION(), return_type> invoke_current(parameter_types... parameters)
	{
		return all_delegates[invoke_index]->invoke(parameters...);
	}

	// Cancel an invoke
	void cancel()
	{
		cancel_invoke = true;
	}

	// Cancel all invokes
	static void cancel_all()
	{
		cancelled_all = true;
	}

	// Cancel the current invoke
	static void cancel_current()
	{
		all_delegates[invoke_index]->cancel_invoke = true;
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
	delegate<return_type, parameter_types...>& set(int index, FUNCTION(function))
	{
		functions[index] = function;

		return *this;
	}

	// Add a new function to the delegate
	delegate<return_type, parameter_types...>& add(FUNCTION(function))
	{
		functions.push_back(function);

		return *this;
	}

	// Adds new functions to the delegate
	delegate<return_type, parameter_types...>& add(int number_of_functions, FUNCTION(functions[]))
	{
		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Adds new functions to the delegate
	delegate<return_type, parameter_types...>& add(std::vector<FUNCTION()> functions)
	{
		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Add a delegate to the delegate
	delegate<return_type, parameter_types...>& add(delegate<return_type, parameter_types...>& functions)
	{
		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Remove a function from the delegate
	delegate<return_type, parameter_types...>& remove(FUNCTION(function))
	{
		functions.erase(std::find(functions.begin(), functions.end(), function));

		return *this;
	}

	// Remove a delegate from the delegate
	delegate<return_type, parameter_types...>& remove(delegate<return_type, parameter_types...>& functions)
	{
		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.erase(std::find(this->functions.begin(), this->functions.end(), functions[i]));
		}

		return *this;
	}

	// Remove a function from the delegate
	delegate<return_type, parameter_types...>& remove_at(int index)
	{
		functions.erase(functions.begin() + index);

		return *this;
	}

	// Clear all functions from the delegate
	delegate<return_type, parameter_types...>& clear()
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
		auto functions = new return_type[this->functions.size()](parameter_types...);

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
	delegate<return_type, parameter_types...>& operator=(const delegate<return_type, parameter_types...>& delegate)
	{
		functions = delegate.functions;

		return *this;
	}

	// Move assignment operator
	delegate<return_type, parameter_types...>& operator=(delegate<return_type, parameter_types...>&& delegate) noexcept
	{
		functions = delegate.functions;

		delegate.functions.clear();

		return *this;
	}


	// COLLECTION OPERATORS

	// Adding a function
	delegate<return_type, parameter_types...>& operator+(FUNCTION(function))
	{
		return add(function);
	}

	// Adding a function
	delegate<return_type, parameter_types...>& operator+=(FUNCTION(function))
	{
		return add(function);
	}

	// Removing a function
	delegate<return_type, parameter_types...>& operator-(FUNCTION(function))
	{
		return remove(function);
	}

	// Removing a function
	delegate<return_type, parameter_types...>& operator-=(FUNCTION(function))
	{
		return remove(function);
	}
};

// Static variable initialization
template <typename ... parameter_types> std::vector<event<parameter_types...>*> event<parameter_types...>::all_delegates = std::vector<event<parameter_types...>*>();
template <typename ... parameter_types> bool event<parameter_types...>::cancelled_all = false;
template <typename ... parameter_types> int event<parameter_types...>::invoke_index = 0;
template <typename return_type, typename ... parameter_types> std::vector<delegate<return_type, parameter_types...>*> delegate<return_type, parameter_types...>::all_delegates = std::vector<delegate<return_type, parameter_types...>*>();
template <typename return_type, typename ... parameter_types> bool delegate<return_type, parameter_types...>::cancelled_all = false;
template <typename return_type, typename ... parameter_types> int delegate<return_type, parameter_types...>::invoke_index = 0;
