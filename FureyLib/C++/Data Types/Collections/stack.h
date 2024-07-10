
// Stack and Priority Stack Containers Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/stack/stack/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.stack?view=net-8.0, https://en.cppreference.com/w/cpp/container/priority_queue, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.priorityqueue-2?view=net-8.0

#pragma once
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the class
#include "stack.h"

// The priority type used for sorting
#define PRIORITY_TYPE float

// Wrapper class of a linked list allowing first in last out access of its elements.
template<typename data_type> class stack
{
private:

	// VARIABLES

	// The linked list holding the data of the stack
	std::list<data_type> my_stack = std::list<data_type>();

public:

	// TO ARRAY AND LIST

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

	// Returns a linked list of the current stack
	std::list<data_type> to_list()
	{
		return std::list<data_type>(my_stack);
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
			my_stack.push_back(array[i]);
		}
	}

	// Array constructor
	stack(int argc, data_type* array ...)
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
			my_stack.push_back(argv[i]);
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
			my_stack.push_back(vector[i]);
		}
	}

	// Linked list constructor
	stack(std::list<data_type> list)
	{
		my_stack = std::list<data_type>(list);
	}

	// List constructor
	stack(std::initializer_list<data_type> list)
	{
		my_stack = std::list<data_type>();

		for (int i = 0; i < list.size(); i++)
		{
			my_stack.push_back(*(list.begin() + i));
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
		return my_stack.back();
	}

	// Returns the most recent element without popping it safely
	data_type peek()
	{
		if (my_stack.size() == 0)
		{
			return data_type();
		}

		return my_stack.back();
	}

	// Returns the oldest element
	data_type back()
	{
		return my_stack.front();
	}

	// Returns the oldest element safely
	data_type peek_back()
	{
		if (my_stack.size() == 0)
		{
			return data_type();
		}

		return my_stack.front();
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
		my_stack.push_back(data);

		return *this;
	}

	// Creates a new element of the given data at the top of the stack
	template<typename  ... argument_types> stack<data_type>& emplace(argument_types ... arguments)
	{
		my_stack.emplace_back(arguments...);

		return *this;
	}

	// Remove and return the top element from the stack
	data_type pop()
	{
		data_type element = my_stack.front();

		my_stack.pop_back();

		return element;
	}

	// Remove and return the top element from the stack safely
	data_type safe_pop()
	{
		if (my_stack.size() == 0)
		{
			return data_type();
		}

		data_type element = my_stack.front();

		my_stack.pop_back();

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

// •  Wrapper class of a linked list allowing first in last out access of its elements.
// •  Each element has its own associated priority value used for automatic sorting on insertion.
// •  Elements with higher priority are destackd first.
template<typename data_type> class priority_stack
{
private:

	// VARIABLES

	// The linked list holding the data of the stack
	std::list<data_type> my_stack = std::list<data_type>();

	// The linked list holding the priority values of the stack
	std::list<PRIORITY_TYPE> priority = std::list<PRIORITY_TYPE>();

public:

	// TO ARRAY AND LIST

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

	// Returns a linked list of the current stack
	std::list<data_type> to_list()
	{
		return std::list<data_type>(my_stack);
	}

	// Returns an array of the current stack's priority (MUST BE DEALLOCATED)
	PRIORITY_TYPE* priority_to_new_array()
	{
		PRIORITY_TYPE* array = new PRIORITY_TYPE[my_stack.size()];

		int i = 0;

		for (PRIORITY_TYPE node : priority)
		{
			array[i] = node;

			i++;
		}

		return array;
	}

	// Returns a vector of the current stack's priority
	std::vector<PRIORITY_TYPE> priority_to_vector()
	{
		std::vector<PRIORITY_TYPE> vector = std::vector<PRIORITY_TYPE>();

		int i = 0;

		for (PRIORITY_TYPE node : priority)
		{
			vector.push_back(node);

			i++;
		}

		return vector;
	}

	// Returns a linked list of the current stack's priority
	std::list<PRIORITY_TYPE> priority_to_list()
	{
		return std::list<PRIORITY_TYPE>(priority);
	}


	// CONSTRUCTORS

	// Default constructor
	priority_stack()
	{
		my_stack = std::list<data_type>();

		priority = std::list<PRIORITY_TYPE>();
	}

	// Copy constructor
	priority_stack(priority_stack<data_type>& copied_stack)
	{
		my_stack = std::list<data_type>(copied_stack.my_stack);

		priority = std::list<PRIORITY_TYPE>(copied_stack.priority);
	}

	// Move constructor
	priority_stack(priority_stack<data_type>&& moved_stack) noexcept
	{
		my_stack = moved_stack.my_stack;

		priority = moved_stack.priority;

		moved_stack.my_stack = std::list<data_type>();

		moved_stack.priority = std::list<PRIORITY_TYPE>();
	}

	// Data constructor
	priority_stack(data_type data, float priority)
	{
		my_stack = std::list<data_type>();

		my_stack.push_back(data);

		this->priority = std::list<PRIORITY_TYPE>();

		this->priority.push_back(priority);
	}

	// List constructor
	priority_stack(std::initializer_list<std::tuple<data_type, PRIORITY_TYPE>> list)
	{
		my_stack = std::list<data_type>();

		for (int i = 0; i < list.size(); i++)
		{
			push(std::get<0>(*(list.begin() + i)), std::get<1>(*(list.begin() + i)));
		}
	}


	// OPERATORS

	// Copy assignment operator
	priority_stack<data_type>& operator=(const priority_stack<data_type>& copied_stack)
	{
		my_stack = std::list<data_type>(copied_stack.my_stack);

		priority = std::list<PRIORITY_TYPE>(copied_stack.priority);

		return *this;
	}

	// Move assignment operator
	priority_stack<data_type>& operator=(priority_stack<data_type>&& moved_stack) noexcept
	{
		my_stack = moved_stack.my_stack;

		priority = moved_stack.priority;

		moved_stack.my_stack = std::list<data_type>();

		moved_stack.priority = std::list<PRIORITY_TYPE>();

		return *this;
	}


	// EQUALITY

	// Check if another stack is equal to the stack
	bool equals(priority_stack<data_type>& compared_stack)
	{
		return my_stack == compared_stack.my_stack;
	}

	// Check if another stack is equal to the stack
	bool operator ==(priority_stack<data_type>& compared_stack)
	{
		return equals(compared_stack);
	}

	// Check if another stack is not equal to the stack
	bool operator !=(priority_stack<data_type>& compared_stack)
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

	// Returns the highest priority element without popping it
	data_type front()
	{
		return my_stack.front();
	}

	// Returns the highest priority element without popping it safely
	data_type peek()
	{
		if (my_stack.size() == 0)
		{
			return data_type();
		}

		return my_stack.front();
	}

	// Returns the lowest priority element
	data_type back()
	{
		return my_stack.back();
	}

	// Returns the lowest priority element safely
	data_type peek_back()
	{
		if (my_stack.size() == 0)
		{
			return data_type();
		}

		return my_stack.back();
	}

	// Returns the highest priority element and its priority without popping it
	std::tuple<data_type, PRIORITY_TYPE> front_with_priority()
	{
		return std::tuple<data_type, PRIORITY_TYPE>(my_stack.front(), priority.front());
	}

	// Returns the highest priority element and its priority without popping it safely
	std::tuple<data_type, PRIORITY_TYPE> peek_with_priority()
	{
		if (my_stack.size() == 0)
		{
			return std::tuple<data_type, PRIORITY_TYPE>(data_type(), 0);
		}

		return (my_stack.front(), priority.front());
	}

	// Returns the lowest priority element and its priority
	std::tuple<data_type, PRIORITY_TYPE> back_with_priority()
	{
		return std::tuple<data_type, PRIORITY_TYPE>(my_stack.back(), priority.back());
	}

	// Returns the lowest priority element and its priority safely
	std::tuple<data_type, PRIORITY_TYPE> peek_back_with_priority()
	{
		if (my_stack.size() == 0)
		{
			return std::tuple<data_type, PRIORITY_TYPE>(data_type(), 0);
		}

		return std::tuple<data_type, PRIORITY_TYPE>(my_stack.back(), priority.back());
	}


	// LOCATING ELEMENTS

	// Returns whether the stack contains at least one of the elements
	bool contains(data_type contained_data)
	{
		return std::find(my_stack.begin(), my_stack.end(), contained_data) != my_stack.end();
	}


	// MODIFIERS

	// Assigns the stack's elements from another stack's elements
	priority_stack<data_type>& assign(priority_stack<data_type>& new_data)
	{
		my_stack = std::list<data_type>(new_data.my_stack);

		return *this;
	}

	// Inserts a element of the given data into the stack based on its priority value
	priority_stack<data_type>& push(data_type data, PRIORITY_TYPE priority)
	{
		if (my_stack.size() == 0)
		{
			my_stack.push_back(data);

			this->priority.push_back(priority);

			return *this;
		}

		auto data_node = my_stack.begin();

		auto priority_node = this->priority.begin();

		for (int i = 0; i < my_stack.size(); i++)
		{
			if (priority >= *priority_node)
			{
				my_stack.insert(data_node, data);

				this->priority.insert(priority_node, priority);

				return *this;
			}

			data_node++;

			priority_node++;
		}

		my_stack.push_back(data);

		this->priority.push_back(priority);

		return *this;
	}

	// Creates and inserts a new element of the given data into the stack based on its priority value
	template<typename ... argument_types> priority_stack<data_type>& emplace(PRIORITY_TYPE priority, argument_types ... arguments)
	{
		if (my_stack.size() == 0)
		{
			my_stack.emplace_back(arguments...);

			this->priority.push_back(priority);

			return *this;
		}

		auto data_node = my_stack.begin();

		auto priority_node = this->priority.begin();

		for (int i = 0; i < my_stack.size(); i++)
		{
			if (priority >= *priority_node)
			{
				my_stack.emplace(data_node, arguments...);

				this->priority.insert(priority_node, priority);

				return *this;
			}

			data_node++;

			priority_node++;
		}

		my_stack.emplace_back(arguments...);

		this->priority.push_back(priority);

		return *this;
	}

	// Remove and return the element with the greatest priority from the stack
	data_type pop()
	{
		data_type element = my_stack.front();

		my_stack.pop_front();

		priority.pop_front();

		return element;
	}

	// Remove and return the element with the greatest priority from the stack with its priority
	std::tuple<data_type, PRIORITY_TYPE> pop_with_priority()
	{
		data_type element = my_stack.front();

		PRIORITY_TYPE priority = this->priority.front();

		my_stack.pop_front();

		this->priority.pop_front();

		return std::tuple<data_type, PRIORITY_TYPE>(element, priority);
	}

	// Remove and return the element with the greatest priority from the stack safely
	data_type safe_pop()
	{
		if (my_stack.size() == 0)
		{
			return data_type();
		}

		data_type element = my_stack.front();

		my_stack.pop_front();

		priority.pop_front();

		return element;
	}

	// Remove and return the element with the greatest priority from the stack safely with its priority
	std::tuple<data_type, PRIORITY_TYPE> safe_pop_with_priority()
	{
		if (my_stack.size() == 0)
		{
			return std::tuple<data_type, PRIORITY_TYPE>(data_type(), 0);
		}

		data_type element = my_stack.front();

		PRIORITY_TYPE priority = this->priority.front();

		my_stack.pop_front();

		this->priority.pop_front();

		return std::tuple<data_type, PRIORITY_TYPE>(element, priority);
	}

	// Clears the stack
	int clear()
	{
		int total = my_stack.size();

		my_stack.clear();

		priority.clear();

		return total;
	}


	// OPERATIONS

	// Swaps the stack with another stack
	priority_stack<data_type>& swap(priority_stack<data_type>& swapped_data)
	{
		std::list<data_type> data = my_stack;

		std::list<PRIORITY_TYPE> priority = this->priority;

		my_stack = swapped_data.my_stack;

		this->priority = swapped_data.priority;

		swapped_data.my_stack = data;

		swapped_data.priority = priority;

		return *this;
	}

	// Returns a copy of the stack's data
	priority_stack<data_type> copy()
	{
		return priority_stack<data_type>(*this);
	}


	// TO STRING

	// Converts the elements of the stack into a string
	std::string to_string(std::string(*priority_to_string_function) (data_type))
	{
		if (my_stack.size() == 0)
		{
			return "{ }";
		}

		data_type* data = to_new_array();

		PRIORITY_TYPE* priority = priority_to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < my_stack.size(); i++)
		{
			log += (data[i] + " : " + priority_to_string_function(priority[i]) + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		delete[] data;

		data = nullptr;

		delete[] priority;

		priority = nullptr;

		return log;
	}

	// Converts the elements of the stack into a string
	std::string to_string(std::string(*element_to_string_function) (data_type), std::string(*priority_to_string_function) (data_type))
	{
		if (my_stack.size() == 0)
		{
			return "{ }";
		}

		data_type* data = to_new_array();

		PRIORITY_TYPE* priority = priority_to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < my_stack.size(); i++)
		{
			log += (element_to_string_function(data[i]) + " : " + priority_to_string_function(priority[i]) + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		delete[] data;

		data = nullptr;

		delete[] priority;

		priority = nullptr;

		return log;
	}
};
