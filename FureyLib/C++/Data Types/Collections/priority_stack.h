
// Priority Stack Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/queue/priority_queue/?kw=priority_queue, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.priorityqueue-2?view=net-8.0

#pragma once
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the class
#include "priority_stack.h"

// The default priority type used for sorting
#define PRIORITY_TYPE float

// Forward declaration of priority_stack
template<typename data_type, typename priority_type = PRIORITY_TYPE> class priority_stack;

// Class that stores data and its priority value for insertion in a priority stack.
template<typename data_type, typename priority_type = PRIORITY_TYPE> class priority_stack_node
{
public:

	// VARIABLES

	// This node's priority stack
	priority_stack<data_type, priority_type>* my_stack = nullptr;

	// This node's data
	data_type data = data_type();

	// This node's priority
	priority_type priority = priority_type();


	// CONSTRUCTOR

	// Default constructor
	priority_stack_node(priority_stack<data_type, priority_type>* stack = nullptr, data_type data = data_type(), priority_type priority = priority_type())
	{
		this->my_stack = stack;

		this->data = data;

		this->priority = priority;
	}
};

// •  Wrapper class of a linked list allowing first in last out access of its elements.
// •  Each element has its own associated priority value used for automatic sorting on insertion.
// •  Elements with higher priority are popped first.
template<typename data_type, typename priority_type> class priority_stack
{
private:

	// VARIABLES

	// The linked list holding the data and priority values of the stack
	std::list<priority_stack_node<data_type, priority_type>> my_stack = std::list<priority_stack_node<data_type, priority_type>>();

public:

	// TO ARRAY AND VECTOR

	// Returns an array of the current stack (MUST BE DEALLOCATED)
	data_type* to_new_array()
	{
		data_type* array = new data_type[my_stack.size()];

		int i = 0;

		for (priority_stack_node<data_type, priority_type> node : my_stack)
		{
			array[i] = node.data;

			i++;
		}

		return array;
	}

	// Returns an array of the current stack's priority (MUST BE DEALLOCATED)
	priority_type* priority_to_new_array()
	{
		priority_type* array = new priority_type[my_stack.size()];

		int i = 0;

		for (priority_stack_node<data_type, priority_type> node : my_stack)
		{
			array[i] = node.priority;

			i++;
		}

		return array;
	}

	// Returns a vector of the current stack's data
	std::vector<data_type> to_vector()
	{
		std::vector<data_type> vector = std::vector<data_type>();

		int i = 0;

		for (priority_stack_node<data_type, priority_type> node : my_stack)
		{
			vector.push_back(node.data);

			i++;
		}

		return vector;
	}

	// Returns a vector of the current stack's priority
	std::vector<priority_type> priority_to_vector()
	{
		std::vector<priority_type> vector = std::vector<priority_type>();

		int i = 0;

		for (priority_stack_node<data_type, priority_type> node : my_stack)
		{
			vector.push_back(node.priority);

			i++;
		}

		return vector;
	}


	// CONSTRUCTORS

	// Default constructor
	priority_stack()
	{
		my_stack = std::list<priority_stack_node<data_type, priority_type>>();
	}

	// Copy constructor
	priority_stack(const priority_stack<data_type, priority_stack>& copied_stack)
	{
		my_stack = std::list<priority_stack<data_type, priority_stack>>(copied_stack.my_stack);
	}

	// Move constructor
	priority_stack(priority_stack<data_type, priority_stack>&& moved_stack) noexcept
	{
		my_stack = moved_stack.my_stack;

		moved_stack.my_stack = std::list<priority_stack<data_type, priority_stack>>();
	}

	// Data constructor
	priority_stack(data_type data, priority_type priority)
	{
		my_stack = std::list<priority_stack_node<data_type, priority_type>>();

		my_stack.push_back(priority_stack_node<data_type, priority_type>(this, data, priority));
	}

	// Node tuple constructor
	priority_stack(std::initializer_list<std::tuple<data_type, priority_type>> nodes)
	{
		my_stack = std::list<priority_stack_node<data_type, priority_type>>();

		for (int i = 0; i < nodes.size(); i++)
		{
			priority_stack_node<data_type, priority_type> node = priority_stack_node<data_type, priority_type>(this, std::get<0>(*(nodes.begin() + i)), std::get<1>(*(nodes.begin() + i)));

			push(node);
		}
	}


	// OPERATORS

	// Copy assignment operator
	priority_stack<data_type, priority_stack>& operator=(const priority_stack<data_type, priority_stack>& copied_stack)
	{
		my_stack = std::list<priority_stack<data_type, priority_stack>>(copied_stack.my_stack);

		return *this;
	}

	// Move assignment operator
	priority_stack<data_type, priority_stack>& operator=(priority_stack<data_type, priority_stack>&& moved_stack) noexcept
	{
		my_stack = moved_stack.my_stack;

		moved_stack.my_stack = std::list<priority_stack<data_type, priority_stack>>();

		return *this;
	}


	// EQUALITY

	// Check if another stack is equal to the stack
	bool equals(priority_stack<data_type, priority_type>& compared_stack)
	{
		return my_stack == compared_stack.my_stack;
	}

	// Check if another stack is equal to the stack
	bool operator ==(priority_stack<data_type, priority_type>& compared_stack)
	{
		return equals(compared_stack);
	}

	// Check if another stack is not equal to the stack
	bool operator !=(priority_stack<data_type, priority_type>& compared_stack)
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
	data_type top()
	{
		return my_stack.front().data;
	}

	// Returns the lowest priority element
	data_type bottom()
	{
		return my_stack.back().data;
	}

	// Returns the highest priority element and its priority without popping it
	priority_stack_node<data_type, priority_type> top_node()
	{
		return my_stack.front();
	}

	// Returns the lowest priority element and its priority
	priority_stack_node<data_type, priority_type> bottom_node()
	{
		return my_stack.back();
	}


	// LOCATING ELEMENTS

	// Returns whether the stack contains at least one of the elements
	bool contains(data_type contained_data)
	{
		for (priority_stack_node<data_type, priority_type> node : my_stack)
		{
			if (node.data == contained_data)
			{
				return true;
			}
		}

		return false;
	}


	// MODIFIERS

	// Assigns the stack's elements from another stack's elements
	priority_stack<data_type, priority_type>& assign(priority_stack<data_type, priority_type>& new_data)
	{
		my_stack = std::list<priority_stack_node<data_type, priority_type>>(new_data.my_stack);

		return *this;
	}

	// Inserts a new element of the given data into the stack based on its priority value
	priority_stack<data_type, priority_type>& push(data_type data, priority_type priority)
	{
		if (my_stack.size() == 0)
		{
			my_stack.push_back(priority_stack_node<data_type, priority_type>(this, data, priority));

			return *this;
		}

		auto node = my_stack.begin();

		for (int i = 0; i < my_stack.size(); i++)
		{
			if (priority >= node->priority)
			{
				my_stack.insert(node, priority_stack_node<data_type, priority_type>(this, data, priority));

				return *this;
			}

			node++;
		}

		my_stack.push_back(priority_stack_node<data_type, priority_type>(this, data, priority));

		return *this;
	}

	// Inserts a priority stack node into the stack based on its priority value
	priority_stack<data_type, priority_type>& push(priority_stack_node<data_type, priority_type> new_node)
	{
		if (my_stack.size() == 0)
		{
			new_node.my_stack = this;

			my_stack.push_back(new_node);

			return *this;
		}

		auto node = my_stack.begin();

		for (int i = 0; i < my_stack.size(); i++)
		{
			if (new_node.priority >= node->priority)
			{
				new_node.my_stack = this;

				my_stack.insert(node, new_node);

				return *this;
			}

			node++;
		}

		new_node.my_stack = this;

		my_stack.push_back(new_node);

		return *this;
	}

	// Creates and inserts a new element of the given data into the stack based on its priority value
	template<typename ... argument_types> priority_stack<data_type, priority_type>& emplace(priority_type priority, argument_types ... arguments)
	{
		if (my_stack.size() == 0)
		{
			my_stack.push_back(priority_stack_node<data_type, priority_type>(this, data_type(arguments...), priority));

			return *this;
		}

		auto node = my_stack.begin();

		for (int i = 0; i < my_stack.size(); i++)
		{
			if (priority >= node->priority)
			{
				my_stack.insert(node, priority_stack_node<data_type, priority_type>(this, data_type(arguments...), priority));

				return *this;
			}

			node++;
		}

		my_stack.push_back(priority_stack_node<data_type, priority_type>(this, data_type(arguments...), priority));

		return *this;
	}

	// Remove and return the element with the greatest priority from the stack
	data_type pop()
	{
		data_type element = my_stack.front().data;

		my_stack.pop_front();

		return element;
	}

	// Remove and return the element with the greatest priority from the stack with its priority
	priority_stack_node<data_type, priority_type> pop_node()
	{
		priority_stack_node<data_type, priority_type> element = my_stack.front();

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
	priority_stack<data_type, priority_type>& swap(priority_stack<data_type, priority_type>& swapped_data)
	{
		std::list<priority_stack_node<data_type, priority_type>> data = my_stack;

		my_stack = swapped_data.my_stack;

		swapped_data.my_stack = data;

		return *this;
	}

	// Returns a copy of the stack's data
	priority_stack<data_type, priority_type> copy()
	{
		return priority_stack<data_type, priority_type>(*this);
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

		priority_type* data = priority_to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < my_stack.size(); i++)
		{
			log += (data[i] + " : " + priority[i] + ", ");
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
	std::string to_string(std::string(*priority_to_string_function) (data_type))
	{
		if (my_stack.size() == 0)
		{
			return "{ }";
		}

		data_type* data = to_new_array();

		priority_type* data = priority_to_new_array();

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
	std::string to_string(std::string(*to_string_function) (data_type), std::string(*priority_to_string_function) (data_type))
	{
		if (my_stack.size() == 0)
		{
			return "{ }";
		}

		data_type* data = to_new_array();

		priority_type* data = priority_to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < my_stack.size(); i++)
		{
			log += (to_string_function(data[i]) + " : " + priority_to_string_function(priority[i]) + ", ");
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
