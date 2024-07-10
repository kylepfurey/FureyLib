
// Queue and Priority Queue Containers Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/queue/queue/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.queue-1?view=net-8.0, https://en.cppreference.com/w/cpp/container/priority_queue, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.priorityqueue-2?view=net-8.0

#pragma once
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the class
#include "queue.h"

// The priority type used for sorting
#define PRIORITY_TYPE float

// Wrapper class of a linked list allowing first in first out access of its elements.
template<typename data_type> class queue
{
private:

	// VARIABLES

	// The linked list holding the data of the queue
	std::list<data_type> my_queue = std::list<data_type>();

public:

	// TO ARRAY AND LIST

	// Returns an array of the current queue (MUST BE DEALLOCATED)
	data_type* to_new_array()
	{
		data_type* array = new data_type[my_queue.size()];

		int i = 0;

		for (data_type node : my_queue)
		{
			array[i] = node;

			i++;
		}

		return array;
	}

	// Returns a vector of the current queue
	std::vector<data_type> to_vector()
	{
		std::vector<data_type> vector = std::vector<data_type>();

		int i = 0;

		for (data_type node : my_queue)
		{
			vector.push_back(node);

			i++;
		}

		return vector;
	}

	// Returns a linked list of the current queue
	std::list<data_type> to_list()
	{
		return std::list<data_type>(my_queue);
	}


	// CONSTRUCTORS

	// Default constructor
	queue()
	{
		my_queue = std::list<data_type>();
	}

	// Copy constructor
	queue(const queue<data_type>& copied_queue)
	{
		my_queue = std::list<data_type>(copied_queue.my_queue);
	}

	// Move constructor
	queue(queue<data_type>&& moved_queue) noexcept
	{
		my_queue = moved_queue.my_queue;

		moved_queue.my_queue = std::list<data_type>();
	}

	// Data constructor
	queue(data_type data)
	{
		my_queue = std::list<data_type>();

		my_queue.push_back(data);
	}

	// Array constructor
	queue(int array_size, data_type* array)
	{
		my_queue = std::list<data_type>();

		for (int i = 0; i < array_size; i++)
		{
			my_queue.push_back(array[i]);
		}
	}

	// Array constructor
	queue(int argc, data_type* array ...)
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

		my_queue = std::list<data_type>();

		for (int i = 0; i < argc; i++)
		{
			my_queue.push_back(argv[i]);
		}

		delete[] argv;

		argv = nullptr;
	}

	// Vector constructor
	queue(std::vector<data_type> vector)
	{
		my_queue = std::list<data_type>();

		for (int i = 0; i < vector.size(); i++)
		{
			my_queue.push_back(vector[i]);
		}
	}

	// Linked list constructor
	queue(std::list<data_type> list)
	{
		my_queue = std::list<data_type>(list);
	}

	// List constructor
	queue(std::initializer_list<data_type> list)
	{
		my_queue = std::list<data_type>();

		for (int i = 0; i < list.size(); i++)
		{
			my_queue.push_back(*(list.begin() + i));
		}
	}


	// OPERATORS

	// Copy assignment operator
	queue<data_type>& operator=(const queue<data_type>& copied_queue)
	{
		my_queue = std::list<data_type>(copied_queue.my_queue);

		return *this;
	}

	// Move assignment operator
	queue<data_type>& operator=(queue<data_type>&& moved_queue) noexcept
	{
		my_queue = moved_queue.my_queue;

		moved_queue.my_queue = std::list<data_type>();

		return *this;
	}


	// EQUALITY

	// Check if another queue is equal to the queue
	bool equals(queue<data_type>& compared_queue)
	{
		return my_queue == compared_queue.my_queue;
	}

	// Check if another queue is equal to the queue
	bool operator ==(queue<data_type>& compared_queue)
	{
		return equals(compared_queue);
	}

	// Check if another queue is not equal to the queue
	bool operator !=(queue<data_type>& compared_queue)
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

	// Returns the oldest element without popping it
	data_type front()
	{
		return my_queue.front();
	}

	// Returns the oldest element without popping it safely
	data_type peek()
	{
		if (my_queue.size() == 0)
		{
			return data_type();
		}

		return my_queue.front();
	}

	// Returns the most recent element
	data_type back()
	{
		return my_queue.back();
	}

	// Returns the most recent element safely
	data_type peek_back()
	{
		if (my_queue.size() == 0)
		{
			return data_type();
		}

		return my_queue.back();
	}


	// LOCATING ELEMENTS

	// Returns whether the queue contains at least one of the elements
	bool contains(data_type contained_data)
	{
		return std::find(my_queue.begin(), my_queue.end(), contained_data) != my_queue.end();
	}


	// MODIFIERS

	// Assigns the queue's elements from another queue's elements
	queue<data_type>& assign(queue<data_type>& new_data)
	{
		my_queue = std::list<data_type>(new_data.my_queue);

		return *this;
	}

	// Inserts a new element of the given data at the end of the queue
	queue<data_type>& push(data_type data)
	{
		my_queue.push_back(data);

		return *this;
	}

	// Creates a new element of the given data at the end of the queue
	template<typename  ... argument_types> queue<data_type>& emplace(argument_types ... arguments)
	{
		my_queue.emplace_back(arguments...);

		return *this;
	}

	// Remove and return the last element from the queue
	data_type pop()
	{
		data_type element = my_queue.front();

		my_queue.pop_front();

		return element;
	}

	// Remove and return the last element from the queue safely
	data_type safe_pop()
	{
		if (my_queue.size() == 0)
		{
			return data_type();
		}

		data_type element = my_queue.front();

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
	queue<data_type>& swap(queue<data_type>& swapped_data)
	{
		std::list<data_type> data = my_queue;

		my_queue = swapped_data.my_queue;

		swapped_data.my_queue = data;

		return *this;
	}

	// Reverse the queue
	queue<data_type>& reverse()
	{
		std::list<data_type> new_queue = std::list<data_type>(my_queue);

		for (int i = 0; i < my_queue.size(); i++)
		{
			my_queue.push_back(new_queue.back());

			my_queue.pop_front();

			new_queue.pop_back();
		}

		return *this;
	}

	// Returns a copy of the queue's data
	queue<data_type> copy()
	{
		return queue<data_type>(*this);
	}


	// TO STRING

	// Converts the elements of the queue into a string
	std::string to_string()
	{
		if (my_queue.size() == 0)
		{
			return "{ }";
		}

		data_type* data = to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < my_queue.size(); i++)
		{
			log += (data[i] + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		delete[] data;

		data = nullptr;

		return log;
	}

	// Converts the elements of the queue into a string
	std::string to_string(std::string(*to_string_function) (data_type))
	{
		if (my_queue.size() == 0)
		{
			return "{ }";
		}

		data_type* data = to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < my_queue.size(); i++)
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

// •  Wrapper class of a linked list allowing first in first out access of its elements.
// •  Each element has its own associated priority value used for automatic sorting on insertion.
// •  Elements with higher priority are dequeued first.
template<typename data_type> class priority_queue
{
private:

	// VARIABLES

	// The linked list holding the data of the queue
	std::list<data_type> my_queue = std::list<data_type>();

	// The linked list holding the priority values of the queue
	std::list<PRIORITY_TYPE> priority = std::list<PRIORITY_TYPE>();

public:

	// TO ARRAY AND LIST

	// Returns an array of the current queue (MUST BE DEALLOCATED)
	data_type* to_new_array()
	{
		data_type* array = new data_type[my_queue.size()];

		int i = 0;

		for (data_type node : my_queue)
		{
			array[i] = node;

			i++;
		}

		return array;
	}

	// Returns a vector of the current queue
	std::vector<data_type> to_vector()
	{
		std::vector<data_type> vector = std::vector<data_type>();

		int i = 0;

		for (data_type node : my_queue)
		{
			vector.push_back(node);

			i++;
		}

		return vector;
	}

	// Returns a linked list of the current queue
	std::list<data_type> to_list()
	{
		return std::list<data_type>(my_queue);
	}

	// Returns an array of the current queue's priority (MUST BE DEALLOCATED)
	PRIORITY_TYPE* priority_to_new_array()
	{
		PRIORITY_TYPE* array = new PRIORITY_TYPE[my_queue.size()];

		int i = 0;

		for (PRIORITY_TYPE node : priority)
		{
			array[i] = node;

			i++;
		}

		return array;
	}

	// Returns a vector of the current queue's priority
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

	// Returns a linked list of the current queue's priority
	std::list<PRIORITY_TYPE> priority_to_list()
	{
		return std::list<PRIORITY_TYPE>(priority);
	}


	// CONSTRUCTORS

	// Default constructor
	priority_queue()
	{
		my_queue = std::list<data_type>();

		priority = std::list<PRIORITY_TYPE>();
	}

	// Copy constructor
	priority_queue(priority_queue<data_type>& copied_queue)
	{
		my_queue = std::list<data_type>(copied_queue.my_queue);

		priority = std::list<PRIORITY_TYPE>(copied_queue.priority);
	}

	// Move constructor
	priority_queue(priority_queue<data_type>&& moved_queue) noexcept
	{
		my_queue = moved_queue.my_queue;

		priority = moved_queue.priority;

		moved_queue.my_queue = std::list<data_type>();

		moved_queue.priority = std::list<PRIORITY_TYPE>();
	}

	// Data constructor
	priority_queue(data_type data, float priority)
	{
		my_queue = std::list<data_type>();

		my_queue.push_back(data);

		this->priority = std::list<PRIORITY_TYPE>();

		this->priority.push_back(priority);
	}

	// List constructor
	priority_queue(std::initializer_list<std::tuple<data_type, PRIORITY_TYPE>> list)
	{
		my_queue = std::list<data_type>();

		for (int i = 0; i < list.size(); i++)
		{
			push(std::get<0>(*(list.begin() + i)), std::get<1>(*(list.begin() + i)));
		}
	}


	// OPERATORS

	// Copy assignment operator
	priority_queue<data_type>& operator=(const priority_queue<data_type>& copied_queue)
	{
		my_queue = std::list<data_type>(copied_queue.my_queue);

		priority = std::list<PRIORITY_TYPE>(copied_queue.priority);

		return *this;
	}

	// Move assignment operator
	priority_queue<data_type>& operator=(priority_queue<data_type>&& moved_queue) noexcept
	{
		my_queue = moved_queue.my_queue;

		priority = moved_queue.priority;

		moved_queue.my_queue = std::list<data_type>();

		moved_queue.priority = std::list<PRIORITY_TYPE>();

		return *this;
	}


	// EQUALITY

	// Check if another queue is equal to the queue
	bool equals(priority_queue<data_type>& compared_queue)
	{
		return my_queue == compared_queue.my_queue;
	}

	// Check if another queue is equal to the queue
	bool operator ==(priority_queue<data_type>& compared_queue)
	{
		return equals(compared_queue);
	}

	// Check if another queue is not equal to the queue
	bool operator !=(priority_queue<data_type>& compared_queue)
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
	data_type front()
	{
		return my_queue.front();
	}

	// Returns the highest priority element without popping it safely
	data_type peek()
	{
		if (my_queue.size() == 0)
		{
			return data_type();
		}

		return my_queue.front();
	}

	// Returns the lowest priority element
	data_type back()
	{
		return my_queue.back();
	}

	// Returns the lowest priority element safely
	data_type peek_back()
	{
		if (my_queue.size() == 0)
		{
			return data_type();
		}

		return my_queue.back();
	}

	// Returns the oldest element and its priority without popping it
	std::tuple<data_type, PRIORITY_TYPE> front_with_priority()
	{
		return std::tuple<data_type, PRIORITY_TYPE>(my_queue.front(), priority.front());
	}

	// Returns the oldest element and its priority without popping it safely
	std::tuple<data_type, PRIORITY_TYPE> peek_with_priority()
	{
		if (my_queue.size() == 0)
		{
			return std::tuple<data_type, PRIORITY_TYPE>(data_type(), 0);
		}

		return (my_queue.front(), priority.front());
	}

	// Returns the lowest priority element and its priority
	std::tuple<data_type, PRIORITY_TYPE> back_with_priority()
	{
		return std::tuple<data_type, PRIORITY_TYPE>(my_queue.back(), priority.back());
	}

	// Returns the lowest priority element and its priority safely
	std::tuple<data_type, PRIORITY_TYPE> peek_back_with_priority()
	{
		if (my_queue.size() == 0)
		{
			return std::tuple<data_type, PRIORITY_TYPE>(data_type(), 0);
		}

		return std::tuple<data_type, PRIORITY_TYPE>(my_queue.back(), priority.back());
	}


	// LOCATING ELEMENTS

	// Returns whether the queue contains at least one of the elements
	bool contains(data_type contained_data)
	{
		return std::find(my_queue.begin(), my_queue.end(), contained_data) != my_queue.end();
	}


	// MODIFIERS

	// Assigns the queue's elements from another queue's elements
	priority_queue<data_type>& assign(priority_queue<data_type>& new_data)
	{
		my_queue = std::list<data_type>(new_data.my_queue);

		return *this;
	}

	// Inserts a element of the given data into the queue based on its priority value
	priority_queue<data_type>& push(data_type data, PRIORITY_TYPE priority)
	{
		if (my_queue.size() == 0)
		{
			my_queue.push_back(data);

			this->priority.push_back(priority);

			return *this;
		}

		auto data_node = my_queue.begin();

		auto priority_node = this->priority.begin();

		for (int i = 0; i < my_queue.size(); i++)
		{
			if (priority > *priority_node)
			{
				my_queue.insert(data_node, data);

				this->priority.insert(priority_node, priority);

				return *this;
			}

			data_node++;

			priority_node++;
		}

		my_queue.push_back(data);

		this->priority.push_back(priority);

		return *this;
	}

	// Creates and inserts a new element of the given data into the queue based on its priority value
	template<typename ... argument_types> priority_queue<data_type>& emplace(PRIORITY_TYPE priority, argument_types ... arguments)
	{
		if (my_queue.size() == 0)
		{
			my_queue.emplace_back(arguments...);

			this->priority.push_back(priority);

			return *this;
		}

		auto data_node = my_queue.begin();

		auto priority_node = this->priority.begin();

		for (int i = 0; i < my_queue.size(); i++)
		{
			if (priority > *priority_node)
			{
				my_queue.emplace(data_node, arguments...);

				this->priority.insert(priority_node, priority);

				return *this;
			}

			data_node++;

			priority_node++;
		}

		my_queue.emplace_back(arguments...);

		this->priority.push_back(priority);

		return *this;
	}

	// Remove and return the element with the greatest priority from the queue
	data_type pop()
	{
		data_type element = my_queue.front();

		my_queue.pop_front();

		priority.pop_front();

		return element;
	}

	// Remove and return the element with the greatest priority from the queue with its priority
	std::tuple<data_type, PRIORITY_TYPE> pop_with_priority()
	{
		data_type element = my_queue.front();

		PRIORITY_TYPE priority = this->priority.front();

		my_queue.pop_front();

		this->priority.pop_front();

		return std::tuple<data_type, PRIORITY_TYPE>(element, priority);
	}

	// Remove and return the element with the greatest priority from the queue safely
	data_type safe_pop()
	{
		if (my_queue.size() == 0)
		{
			return data_type();
		}

		data_type element = my_queue.front();

		my_queue.pop_front();

		priority.pop_front();

		return element;
	}

	// Remove and return the element with the greatest priority from the queue safely with its priority
	std::tuple<data_type, PRIORITY_TYPE> safe_pop_with_priority()
	{
		if (my_queue.size() == 0)
		{
			return std::tuple<data_type, PRIORITY_TYPE>(data_type(), 0);
		}

		data_type element = my_queue.front();

		PRIORITY_TYPE priority = this->priority.front();

		my_queue.pop_front();

		this->priority.pop_front();

		return std::tuple<data_type, PRIORITY_TYPE>(element, priority);
	}

	// Clears the queue
	int clear()
	{
		int total = my_queue.size();

		my_queue.clear();

		priority.clear();

		return total;
	}


	// OPERATIONS

	// Swaps the queue with another queue
	priority_queue<data_type>& swap(priority_queue<data_type>& swapped_data)
	{
		std::list<data_type> data = my_queue;

		std::list<PRIORITY_TYPE> priority = this->priority;

		my_queue = swapped_data.my_queue;

		this->priority = swapped_data.priority;

		swapped_data.my_queue = data;

		swapped_data.priority = priority;

		return *this;
	}

	// Returns a copy of the queue's data
	priority_queue<data_type> copy()
	{
		return priority_queue<data_type>(*this);
	}


	// TO STRING

	// Converts the elements of the queue into a string
	std::string to_string(std::string(*priority_to_string_function) (data_type))
	{
		if (my_queue.size() == 0)
		{
			return "{ }";
		}

		data_type* data = to_new_array();

		PRIORITY_TYPE* priority = priority_to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < my_queue.size(); i++)
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

	// Converts the elements of the queue into a string
	std::string to_string(std::string(*element_to_string_function) (data_type), std::string(*priority_to_string_function) (data_type))
	{
		if (my_queue.size() == 0)
		{
			return "{ }";
		}

		data_type* data = to_new_array();

		PRIORITY_TYPE* priority = priority_to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < my_queue.size(); i++)
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
