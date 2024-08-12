
// Stack Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/stack/stack/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.stack?view=net-8.0

#pragma once
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the class
#include "stack.h"

// Wrapper class of a linked list allowing first in last out access of its elements.
template<typename data_type> class stack
{
private:

	// VARIABLES

	// The linked list holding the data of the stack
	std::list<data_type> my_stack = std::list<data_type>();

public:

	// TO ARRAY AND VECTOR

	// Returns an array of the current stack (MUST BE DEALLOCATED)
	data_type* to_new_array()
	{
		data_type* array = new data_type[my_stack.size()];

		int i = 0;

		for (data_type node : my_stack)
		{
			array[i] = node;

			i++;
		}

		return array;
	}

	// Returns a vector of the current stack
	std::vector<data_type> to_vector()
	{
		std::vector<data_type> vector = std::vector<data_type>();

		int i = 0;

		for (data_type node : my_stack)
		{
			vector.push_back(node);

			i++;
		}

		return vector;
	}


	// CONSTRUCTORS

	// Default constructor
	stack()
	{
		my_stack = std::list<data_type>();
	}

	// Copy constructor
	stack(const stack<data_type>& copied_stack)
	{
		my_stack = std::list<data_type>(copied_stack.my_stack);
	}

	// Move constructor
	stack(stack<data_type>&& moved_stack) noexcept
	{
		my_stack = moved_stack.my_stack;

		moved_stack.my_stack = std::list<data_type>();
	}

	// Data constructor
	stack(data_type data)
	{
		my_stack = std::list<data_type>();

		my_stack.push_back(data);
	}

	// Array constructor
	stack(int array_size, data_type* array)
	{
		my_stack = std::list<data_type>();

		for (int i = 0; i < array_size; i++)
		{
			my_stack.push_front(array[i]);
		}
	}

	// Array constructor
	stack(int argc, data_type array ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		data_type* argv = new data_type[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, data_type);
		}

		va_end(_va_list);

		my_stack = std::list<data_type>();

		for (int i = 0; i < argc; i++)
		{
			my_stack.push_front(argv[i]);
		}

		delete[] argv;

		argv = nullptr;
	}

	// Vector constructor
	stack(std::vector<data_type> vector)
	{
		my_stack = std::list<data_type>();

		for (int i = 0; i < vector.size(); i++)
		{
			my_stack.push_front(vector[i]);
		}
	}

	// Linked list constructor
	stack(std::list<data_type> list)
	{
		my_stack = std::list<data_type>();

		for (data_type node : list)
		{
			my_stack.push_front(node);
		}
	}

	// List constructor
	stack(std::initializer_list<data_type> list)
	{
		my_stack = std::list<data_type>();

		for (int i = 0; i < list.size(); i++)
		{
			my_stack.push_front(*(list.begin() + i));
		}
	}


	// OPERATORS

	// Copy assignment operator
	stack<data_type>& operator=(const stack<data_type>& copied_stack)
	{
		my_stack = std::list<data_type>(copied_stack.my_stack);

		return *this;
	}

	// Move assignment operator
	stack<data_type>& operator=(stack<data_type>&& moved_stack) noexcept
	{
		my_stack = moved_stack.my_stack;

		moved_stack.my_stack = std::list<data_type>();

		return *this;
	}


	// EQUALITY

	// Check if another stack is equal to the stack
	bool equals(stack<data_type>& compared_stack)
	{
		return my_stack == compared_stack.my_stack;
	}

	// Check if another stack is equal to the stack
	bool operator ==(stack<data_type>& compared_stack)
	{
		return equals(compared_stack);
	}

	// Check if another stack is not equal to the stack
	bool operator !=(stack<data_type>& compared_stack)
	{
		return !equals(compared_stack);
	}


	// CAPACITY

	// Returns whether the stack is empty
	bool empty()
	{
		return my_stack.size() == 0;
	}

	// Returns the current number of elements of the stack
	int size()
	{
		return my_stack.size();
	}


	// ELEMENT ACCESS

	// Returns the most recent element without popping it
	data_type front()
	{
		return my_stack.front();
	}

	// Returns the oldest element
	data_type back()
	{
		return my_stack.back();
	}


	// LOCATING ELEMENTS

	// Returns whether the stack contains at least one of the elements 
	bool contains(data_type contained_data)
	{
		return std::find(my_stack.begin(), my_stack.end(), contained_data) != my_stack.end();
	}


	// MODIFIERS

	// Assigns the stack's elements from another stack's elements
	stack<data_type>& assign(stack<data_type>& new_data)
	{
		my_stack = std::list<data_type>(new_data.my_stack);

		return *this;
	}

	// Inserts a new element of the given data at the top of the stack
	stack<data_type>& push(data_type data)
	{
		my_stack.push_front(data);

		return *this;
	}

	// Creates and inserts a new element of the given data at the top of the stack
	template<typename ... argument_types> stack<data_type>& emplace(argument_types ... arguments)
	{
		my_stack.emplace_front(arguments...);

		return *this;
	}

	// Remove and return the top element from the stack
	data_type pop()
	{
		data_type element = my_stack.front();

		my_stack.pop_front();

		return element;
	}

	// Clears the stack
	int clear()
	{
		int total = my_stack.size();

		my_stack.clear();

		return total;
	}


	// OPERATIONS

	// Swaps the stack with another stack
	stack<data_type>& swap(stack<data_type>& swapped_data)
	{
		std::list<data_type> data = my_stack;

		my_stack = swapped_data.my_stack;

		swapped_data.my_stack = data;

		return *this;
	}

	// Reverse the stack
	stack<data_type>& reverse()
	{
		std::list<data_type> new_stack = std::list<data_type>(my_stack);

		for (int i = 0; i < my_stack.size(); i++)
		{
			my_stack.push_back(new_stack.back());

			my_stack.pop_front();

			new_stack.pop_back();
		}

		return *this;
	}

	// Returns a copy of the stack's data
	stack<data_type> copy()
	{
		return stack<data_type>(*this);
	}


	// TO STRING

	// Converts the elements of the stack into a string
	std::string to_string()
	{
		if (my_stack.size() == 0)
		{
			return "{ }";
		}

		data_type* data = to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < my_stack.size(); i++)
		{
			log += (data[i] + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		delete[] data;

		data = nullptr;

		return log;
	}

	// Converts the elements of the stack into a string
	std::string to_string(std::string(*to_string_function) (data_type))
	{
		if (my_stack.size() == 0)
		{
			return "{ }";
		}

		data_type* data = to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < my_stack.size(); i++)
		{
			log += (to_string_function(data[i]) + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		delete[] data;

		data = nullptr;

		return log;
	}
};
