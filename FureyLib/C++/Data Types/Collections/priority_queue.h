
// Priority Queue Container Script
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
#include "priority_queue.h"

// The default priority type used for sorting
#define PRIORITY_TYPE float

// Forward declaration of priority_queue
template<typename data_type, typename priority_type = PRIORITY_TYPE> class priority_queue;

// Class that stores data and its priority value for insertion in a priority queue.
template<typename data_type, typename priority_type = PRIORITY_TYPE> class priority_queue_node
{
public:

	// VARIABLES

	// This node's priority queue
	priority_queue<data_type, priority_type>* my_queue = nullptr;

	// This node's data
	data_type data = data_type();

	// This node's priority
	priority_type priority = priority_type();


	// CONSTRUCTOR

	// Default constructor
	priority_queue_node(priority_queue<data_type, priority_type>* queue = nullptr, data_type data = data_type(), priority_type priority = priority_type())
	{
		this->my_queue = queue;

		this->data = data;

		this->priority = priority;
	}
};

// •  Wrapper class of a linked list allowing first in first out access of its elements.
// •  Each element has its own associated priority value used for automatic sorting on insertion.
// •  Elements with higher priority are popped first.
template<typename data_type, typename priority_type> class priority_queue
{
private:

	// VARIABLES

	// The linked list holding the data and priority values of the queue
	std::list<priority_queue_node<data_type, priority_type>> my_queue = std::list<priority_queue_node<data_type, priority_type>>();

public:

	// TO ARRAY AND LIST

	// Returns an array of the current queue (MUST BE DEALLOCATED)
	priority_queue_node<data_type, priority_type>* to_new_array()
	{
		priority_queue_node<data_type, priority_type>* array = new priority_queue_node<data_type, priority_type>[my_queue.size()];

		int i = 0;

		for (priority_queue_node<data_type, priority_type> node : my_queue)
		{
			array[i] = node;

			i++;
		}

		return array;
	}

	// Returns an array of the current queue (MUST BE DEALLOCATED)
	data_type* data_to_new_array()
	{
		data_type* array = new data_type[my_queue.size()];

		int i = 0;

		for (priority_queue_node<data_type, priority_type> node : my_queue)
		{
			array[i] = node.data;

			i++;
		}

		return array;
	}

	// Returns an array of the current queue's priority (MUST BE DEALLOCATED)
	priority_type* priority_to_new_array()
	{
		priority_type* array = new priority_type[my_queue.size()];

		int i = 0;

		for (priority_queue_node<data_type, priority_type> node : my_queue)
		{
			array[i] = node.priority;

			i++;
		}

		return array;
	}

	// Returns a vector of the current queue
	std::vector<priority_queue_node<data_type, priority_type>> to_vector()
	{
		std::vector<priority_queue_node<data_type, priority_type>> vector = std::vector<priority_queue_node<data_type, priority_type>>();

		int i = 0;

		for (priority_queue_node<data_type, priority_type> node : my_queue)
		{
			vector.push_back(node);

			i++;
		}

		return vector;
	}

	// Returns a vector of the current queue's data
	std::vector<data_type> data_to_vector()
	{
		std::vector<data_type> vector = std::vector<data_type>();

		int i = 0;

		for (priority_queue_node<data_type, priority_type> node : my_queue)
		{
			vector.push_back(node.data);

			i++;
		}

		return vector;
	}

	// Returns a vector of the current queue's priority
	std::vector<priority_type> priority_to_vector()
	{
		std::vector<priority_type> vector = std::vector<priority_type>();

		int i = 0;

		for (priority_queue_node<data_type, priority_type> node : my_queue)
		{
			vector.push_back(node.priority);

			i++;
		}

		return vector;
	}

	// Returns a linked list of the current queue
	std::list<priority_queue_node<data_type, priority_type>> to_list()
	{
		return std::list<priority_queue_node<data_type, priority_type>>(my_queue);
	}

	// Returns a linked list of the current queue's data
	std::list<data_type> data_to_list()
	{
		std::list<data_type> list = std::list<data_type>();

		for (priority_queue_node<data_type, priority_type> node : my_queue)
		{
			list.push_back(node.data);
		}

		return list;
	}

	// Returns a linked list of the current queue's priority
	std::list<priority_type> priority_to_list()
	{
		std::list<priority_type> list = std::list<priority_type>();

		for (priority_queue_node<data_type, priority_type> node : my_queue)
		{
			list.push_back(node.priority);
		}

		return list;
	}


	// CONSTRUCTORS

	// Default constructor
	priority_queue()
	{
		my_queue = std::list<priority_queue_node<data_type, priority_type>>();
	}

	// Copy constructor
	priority_queue(const priority_queue<data_type, priority_queue>& copied_queue)
	{
		my_queue = std::list<priority_queue<data_type, priority_queue>>(copied_queue.my_queue);
	}

	// Move constructor
	priority_queue(priority_queue<data_type, priority_queue>&& moved_queue) noexcept
	{
		my_queue = moved_queue.my_queue;

		moved_queue.my_queue = std::list<priority_queue<data_type, priority_queue>>();
	}

	// Data constructor
	priority_queue(data_type data, priority_type priority)
	{
		my_queue = std::list<priority_queue_node<data_type, priority_type>>();

		my_queue.push_back(priority_queue_node<data_type, priority_type>(this, data, priority));
	}

	// Node constructor
	priority_queue(priority_queue_node<data_type, priority_type> node)
	{
		my_queue = std::list<priority_queue_node<data_type, priority_type>>();

		node.my_queue = this;

		my_queue.push_back(node);
	}

	// Node array constructor
	priority_queue(int array_size, priority_queue_node<data_type, priority_type>* nodes)
	{
		my_queue = std::list<priority_queue_node<data_type, priority_type>>();

		for (int i = 0; i < array_size; i++)
		{
			push(nodes[i]);
		}
	}

	// Node array constructor
	priority_queue(int argc, priority_queue_node<data_type, priority_type> array ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		priority_queue_node<data_type, priority_type>* argv = new priority_queue_node<data_type, priority_type>[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = ((sizeof(priority_queue_node<data_type, priority_type>) > sizeof(__int64) || (sizeof(priority_queue_node<data_type, priority_type>) & (sizeof(priority_queue_node<data_type, priority_type>) - 1)) != 0) ? **(priority_queue_node<data_type, priority_type>**)((_va_list += sizeof(__int64)) - sizeof(__int64)) : *(priority_queue_node<data_type, priority_type>*)((_va_list += sizeof(__int64)) - sizeof(__int64)));
		}

		va_end(_va_list);

		my_queue = std::list<priority_queue_node<data_type, priority_type>>();

		for (int i = 0; i < argc; i++)
		{
			push(argv[i]);
		}

		delete[] argv;

		argv = nullptr;
	}

	// Node vector constructor
	priority_queue(std::vector<priority_queue_node<data_type, priority_type>> nodes)
	{
		my_queue = std::list<priority_queue_node<data_type, priority_type>>();

		for (int i = 0; i < nodes.size(); i++)
		{
			push(nodes[i]);
		}
	}

	// Node linked list constructor
	priority_queue(std::list<priority_queue_node<data_type, priority_type>> nodes)
	{
		my_queue = std::list<priority_queue_node<data_type, priority_type>>();

		for (priority_queue_node<data_type, priority_type> node : nodes)
		{
			push(node);
		}
	}

	// Node list constructor
	priority_queue(std::initializer_list<priority_queue_node<data_type, priority_type>> nodes)
	{
		my_queue = std::list<priority_queue_node<data_type, priority_type>>();

		for (int i = 0; i < nodes.size(); i++)
		{
			push(*(nodes.begin() + i));
		}
	}

	// Node tuple constructor
	priority_queue(std::initializer_list<std::tuple<data_type, priority_type>> nodes)
	{
		my_queue = std::list<priority_queue_node<data_type, priority_type>>();

		for (int i = 0; i < nodes.size(); i++)
		{
			priority_queue_node<data_type, priority_type> node = priority_queue_node<data_type, priority_type>(this, std::get<0>(*(nodes.begin() + i)), std::get<1>(*(nodes.begin() + i)));

			push(node);
		}
	}


	// OPERATORS

	// Copy assignment operator
	priority_queue<data_type, priority_queue>& operator=(const priority_queue<data_type, priority_queue>& copied_queue)
	{
		my_queue = std::list<priority_queue<data_type, priority_queue>>(copied_queue.my_queue);

		return *this;
	}

	// Move assignment operator
	priority_queue<data_type, priority_queue>& operator=(priority_queue<data_type, priority_queue>&& moved_queue) noexcept
	{
		my_queue = moved_queue.my_queue;

		moved_queue.my_queue = std::list<priority_queue<data_type, priority_queue>>();

		return *this;
	}


	// EQUALITY

	// Check if another queue is equal to the queue
	bool equals(priority_queue<data_type, priority_type>& compared_queue)
	{
		return my_queue == compared_queue.my_queue;
	}

	// Check if another queue is equal to the queue
	bool operator ==(priority_queue<data_type, priority_type>& compared_queue)
	{
		return equals(compared_queue);
	}

	// Check if another queue is not equal to the queue
	bool operator !=(priority_queue<data_type, priority_type>& compared_queue)
	{
		return !equals(compared_queue);
	}


	// CAPACITY

	// Returns whether the queue is empty
	bool empty()
	{
		return my_queue.size() == 0;
	}

	// Returns the current number of elements of the queue
	int size()
	{
		return my_queue.size();
	}


	// ELEMENT ACCESS

	// Returns the highest priority element without popping it
	data_type top()
	{
		return my_queue.front().data;
	}

	// Returns the highest priority element without popping it safely
	data_type peek()
	{
		if (my_queue.size() == 0)
		{
			return data_type();
		}

		return my_queue.front().data;
	}

	// Returns the lowest priority element
	data_type bottom()
	{
		return my_queue.back().data;
	}

	// Returns the lowest priority element safely
	data_type peek_back()
	{
		if (my_queue.size() == 0)
		{
			return data_type();
		}

		return my_queue.back().data;
	}

	// Returns the highest priority element and its priority without popping it
	priority_queue_node<data_type, priority_type> top_node()
	{
		return my_queue.front();
	}

	// Returns the highest priority element and its priority without popping it safely
	priority_queue_node<data_type, priority_type> peek_node()
	{
		if (my_queue.size() == 0)
		{
			return nullptr;
		}

		return my_queue.front();
	}

	// Returns the lowest priority element and its priority
	priority_queue_node<data_type, priority_type> bottom_node()
	{
		return my_queue.back();
	}

	// Returns the lowest priority element and its priority safely
	priority_queue_node<data_type, priority_type> peek_back_node()
	{
		if (my_queue.size() == 0)
		{
			return nullptr;
		}

		return my_queue.back();
	}


	// LOCATING ELEMENTS

	// Returns whether the queue contains at least one of the elements
	bool contains(data_type contained_data)
	{
		for (priority_queue_node<data_type, priority_type> node : my_queue)
		{
			if (node.data == contained_data)
			{
				return true;
			}
		}

		return false;
	}


	// MODIFIERS

	// Assigns the queue's elements from another queue's elements
	priority_queue<data_type, priority_type>& assign(priority_queue<data_type, priority_type>& new_data)
	{
		my_queue = std::list<priority_queue_node<data_type, priority_type>>(new_data.my_queue);

		return *this;
	}

	// Inserts a new element of the given data into the queue based on its priority value
	priority_queue<data_type, priority_type>& push(data_type data, priority_type priority)
	{
		if (my_queue.size() == 0)
		{
			my_queue.push_back(priority_queue_node<data_type, priority_type>(this, data, priority));

			return *this;
		}

		auto node = my_queue.begin();

		for (int i = 0; i < my_queue.size(); i++)
		{
			if (priority > node->priority)
			{
				my_queue.insert(node, priority_queue_node<data_type, priority_type>(this, data, priority));

				return *this;
			}

			node++;
		}

		my_queue.push_back(priority_queue_node<data_type, priority_type>(this, data, priority));

		return *this;
	}

	// Inserts a priority queue node into the queue based on its priority value
	priority_queue<data_type, priority_type>& push(priority_queue_node<data_type, priority_type> new_node)
	{
		if (my_queue.size() == 0)
		{
			new_node.my_queue = this;

			my_queue.push_back(new_node);

			return *this;
		}

		auto node = my_queue.begin();

		for (int i = 0; i < my_queue.size(); i++)
		{
			if (new_node.priority > node->priority)
			{
				new_node.my_queue = this;

				my_queue.insert(node, new_node);

				return *this;
			}

			node++;
		}

		new_node.my_queue = this;

		my_queue.push_back(new_node);

		return *this;
	}

	// Creates and inserts a new element of the given data into the queue based on its priority value
	template<typename ... argument_types> priority_queue<data_type, priority_type>& emplace(priority_type priority, argument_types ... arguments)
	{
		if (my_queue.size() == 0)
		{
			my_queue.push_back(priority_queue_node<data_type, priority_type>(this, data_type(arguments...), priority));

			return *this;
		}

		auto node = my_queue.begin();

		for (int i = 0; i < my_queue.size(); i++)
		{
			if (priority > node->priority)
			{
				my_queue.insert(node, priority_queue_node<data_type, priority_type>(this, data_type(arguments...), priority));

				return *this;
			}

			node++;
		}

		my_queue.push_back(priority_queue_node<data_type, priority_type>(this, data_type(arguments...), priority));

		return *this;
	}

	// Remove and return the element with the greatest priority from the queue
	data_type pop()
	{
		data_type element = my_queue.front().data;

		my_queue.pop_front();

		return element;
	}

	// Remove and return the element with the greatest priority from the queue with its priority
	priority_queue_node<data_type, priority_type> pop_node()
	{
		priority_queue_node<data_type, priority_type> element = my_queue.front();

		my_queue.pop_front();

		return element;
	}

	// Remove and return the element with the greatest priority from the queue safely
	data_type safe_pop()
	{
		if (my_queue.size() == 0)
		{
			return data_type();
		}

		data_type element = my_queue.front().data;

		my_queue.pop_front();

		return element;
	}

	// Remove and return the element with the greatest priority from the queue safely with its priority
	priority_queue_node<data_type, priority_type> safe_pop_node()
	{
		if (my_queue.size() == 0)
		{
			return nullptr;
		}

		priority_queue_node<data_type, priority_type> element = my_queue.front();

		my_queue.pop_front();

		return element;
	}

	// Clears the queue
	int clear()
	{
		int total = my_queue.size();

		my_queue.clear();

		return total;
	}


	// OPERATIONS

	// Swaps the queue with another queue
	priority_queue<data_type, priority_type>& swap(priority_queue<data_type, priority_type>& swapped_data)
	{
		std::list<priority_queue_node<data_type, priority_type>> data = my_queue;

		my_queue = swapped_data.my_queue;

		swapped_data.my_queue = data;

		return *this;
	}

	// Returns a copy of the queue's data
	priority_queue<data_type, priority_type> copy()
	{
		return priority_queue<data_type, priority_type>(*this);
	}


	// TO STRING

	// Converts the elements of the queue into a string
	std::string to_string()
	{
		if (my_queue.size() == 0)
		{
			return "{ }";
		}

		priority_queue_node<data_type, priority_type>* data = to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < my_queue.size(); i++)
		{
			log += (data[i].data + " : " + data[i].priority + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		delete[] data;

		data = nullptr;

		return log;
	}

	// Converts the elements of the queue into a string
	std::string to_string(std::string(*priority_to_string_function) (data_type))
	{
		if (my_queue.size() == 0)
		{
			return "{ }";
		}

		priority_queue_node<data_type, priority_type>* data = to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < my_queue.size(); i++)
		{
			log += (data[i].data + " : " + priority_to_string_function(data[i].priority) + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		delete[] data;

		data = nullptr;

		return log;
	}

	// Converts the elements of the queue into a string
	std::string to_string(std::string(*data_to_string_function) (data_type), std::string(*priority_to_string_function) (data_type))
	{
		if (my_queue.size() == 0)
		{
			return "{ }";
		}

		priority_queue_node<data_type, priority_type>* data = to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < my_queue.size(); i++)
		{
			log += (data_to_string_function(data[i].data) + " : " + priority_to_string_function(data[i].priority) + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		delete[] data;

		data = nullptr;

		return log;
	}
};
