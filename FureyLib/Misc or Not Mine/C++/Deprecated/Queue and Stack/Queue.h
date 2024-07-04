
// Queue and Priority Queue Data Types Script
// by Kyle Furey

#pragma once
#include <vector>
#include <map>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the class
#include "Queue.h"

// Data type used for priority value.
#define PRIORITY float

// A first in first out list of a specified data type.
template <class DataType> class queue
{
private:

	// Vector of data
	std::vector<DataType> q = std::vector<DataType>();

public:

	// Enqueue new data and return the index
	int enqueue(DataType data)
	{
		q.push_back(data);

		return q.size() - 1;
	}

	// Dequeue and return the data with the highest priority
	DataType dequeue()
	{
		DataType dequeuedData = q[0];

		q.erase(q.begin());

		return dequeuedData;
	}

	// Enqueue new data and return the index
	int push(DataType data)
	{
		return enqueue(data);
	}

	// Dequeue and return the data with the highest priority
	DataType pop()
	{
		return dequeue();
	}

	// Returns the data with the highest priority (without removing it from the queue)
	DataType peek()
	{
		return q[0];
	}

	// Returns the data with the lowest priority (without removing it from the queue)
	DataType peek_last()
	{
		return q[q.size() - 1];
	}

	// Returns the data at the given index
	DataType get(int index)
	{
		return q[index];
	}

	// Sets the data at the given index
	queue<DataType>& set(int index, DataType new_data)
	{
		q[index] = new_data;

		return *this;
	}

	// Clears the queue and returns the total number of cleared nodes
	int clear()
	{
		int total = q.size();

		q.clear();

		return total;
	}

	// Returns the size of the queue
	int count()
	{
		return queue.size();
	}

	// Returns if the queue is empty
	bool is_empty()
	{
		return q.size() == 0;
	}

	// Return the index of the given element, or -1 if it was not found
	int find(DataType data)
	{
		for (int i = 0; i < q.size(); i++)
		{
			if (q[i] == data)
			{
				return i;
			}
		}

		return -1;
	}

	// Return whether the queue contains the given element
	bool contains(DataType data)
	{
		for (int i = 0; i < q.size(); i++)
		{
			if (q[i] == data)
			{
				return true;
			}
		}

		return false;
	}

	// Return the number of matching elements
	int total(DataType data)
	{
		int total = 0;

		for (int i = 0; i < q.size(); i++)
		{
			if (q[i] == data)
			{
				total++;
			}
		}

		return total;
	}

	// Returns a new pointer to a new array of the current queue (must be deallocated)
	DataType* to_new_array()
	{
		DataType* new_array = new DataType[q.size()];

		for (int i = 0; i < q.size(); i++)
		{
			new_array[i] = q[i];
		}

		return new_array;
	}

	// Returns a vector of the current queue data
	std::vector<DataType> to_vector()
	{
		return q;
	}

	// Default constructor
	queue()
	{
		q = std::vector<DataType>();
	}

	// Array constructor
	queue(int number_of_elements, DataType data[])
	{
		q = std::vector<DataType>();

		for (int i = 0; i < number_of_elements; i++)
		{
			q.push_back(data[i]);
		}
	}

	// Vector constructor
	queue(std::vector<DataType> data)
	{
		q = data;
	}

	// Parameter constructor
	queue(int number_of_elements, DataType data...)
	{
		q = std::vector<DataType>();

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_elements; i++)
		{
			q.push_back(va_arg(list, DataType));
		}

		va_end(list);
	}

	// List constructor
	queue(const std::initializer_list<DataType> data)
	{
		q = std::vector<DataType>();

		for (int i = 0; i < data.size(); i++)
		{
			q.push_back(data[i]);
		}
	}

	// Queue constructor
	queue(queue<DataType>&& data)
	{
		q = data.q;
	}
};

// A first in first out list of a specified data type with an associated priority value assigned to each element used for adding and removing data in a specific order.
template <class DataType> class priority_queue
{
private:

	// Vector of data
	std::vector<DataType> queue = std::vector<DataType>();

	// Vector of priority
	std::vector<PRIORITY> priority = std::vector<PRIORITY>();

public:

	// Enqueue new data and return the index
	int enqueue(DataType data, PRIORITY new_priority)
	{
		for (int i = 0; i < queue.size(); i++)
		{
			if (new_priority > priority[i])
			{
				queue.insert(queue.begin() + i, data);

				priority.insert(priority.begin() + i, new_priority);

				return i;
			}
		}

		queue.push_back(data);

		priority.push_back(new_priority);

		return queue.size() - 1;
	}

	// Dequeue and return the data with the highest priority
	DataType dequeue()
	{
		DataType dequeuedData = queue[0];

		queue.erase(queue.begin());

		priority.erase(priority.begin());

		return dequeuedData;
	}

	// Enqueue new data and return the index
	int push(DataType data, PRIORITY new_priority)
	{
		return enqueue(data, new_priority);
	}

	// Dequeue and return the data with the highest priority
	DataType pop()
	{
		return dequeue();
	}

	// Returns the data with the highest priority (without removing it from the queue)
	DataType peek()
	{
		return queue[0];
	}

	// Returns the data with the lowest priority (without removing it from the queue)
	DataType peek_last()
	{
		return queue[queue.size() - 1];
	}

	// Returns the data at the given index
	DataType get(int index)
	{
		return queue[index];
	}

	// Sets the data at the given index
	priority_queue<DataType>& set(int index, DataType new_data)
	{
		queue[index] = new_data;

		return *this;
	}

	// Sets the data at the given index
	priority_queue<DataType>& set(int index, DataType new_data, PRIORITY new_priority)
	{
		queue[index] = new_data;

		priority[index] = new_priority;

		return *this;
	}

	// Returns the highest priority value (the priority which is closest to being dequeued)
	PRIORITY highest_priority()
	{
		return priority[0];
	}

	// Returns the lowest priority value (the priority which is furthest from being dequeued)
	PRIORITY lowest_priority()
	{
		return priority[priority.size() - 1];
	}

	// Returns the priority value of the given data in the queue
	PRIORITY get_priority(DataType data)
	{
		PRIORITY priority = 0;

		for (int i = 0; i < queue.size(); i++)
		{
			if (queue[i] == data)
			{
				return this->priority[i];
			}
		}

		return priority;
	}

	// Returns the priority value at the given index in the queue
	PRIORITY get_priority_at(int index)
	{
		return priority[index];
	}

	// Sets the priority value of the given data
	priority_queue<DataType>& set_priority(DataType data, PRIORITY new_priority)
	{
		for (int i = 0; i < queue.size(); i++)
		{
			if (queue[i] == data)
			{
				priority[i] = new_priority;

				return *this;
			}
		}

		return *this;
	}

	// Sets the priority value at the given index
	priority_queue<DataType>& set_priority_at(int index, PRIORITY new_priority)
	{
		priority[index] = new_priority;

		return *this;
	}

	// Clears the queue and returns the total number of cleared nodes
	int clear()
	{
		int total = queue.size();

		queue.clear();

		priority.clear();

		return total;
	}

	// Returns the size of the queue
	int count()
	{
		return queue.size();
	}

	// Returns if the queue is empty
	bool is_empty()
	{
		return queue.size() == 0;
	}

	// Return the index of the given element, or -1 if it was not found
	int find(DataType data)
	{
		for (int i = 0; i < queue.size(); i++)
		{
			if (queue[i] == data)
			{
				return i;
			}
		}

		return -1;
	}

	// Return whether the queue contains the given element
	bool contains(DataType data)
	{
		for (int i = 0; i < queue.size(); i++)
		{
			if (queue[i] == data)
			{
				return true;
			}
		}

		return false;
	}

	// Return the number of matching elements
	int total(DataType data)
	{
		int total = 0;

		for (int i = 0; i < queue.size(); i++)
		{
			if (queue[i] == data)
			{
				total++;
			}
		}

		return total;
	}

	// Returns a new pointer to a new array of the current queue (must be deallocated)
	DataType* to_new_array()
	{
		DataType* new_array = new DataType[queue.size()];

		for (int i = 0; i < queue.size(); i++)
		{
			new_array[i] = queue[i];
		}

		return new_array;
	}

	// Returns a vector of the current queue data
	std::vector<DataType> to_vector()
	{
		return queue;
	}

	// Returns a new pointer to a new array of the current queue's priority values (must be deallocated)
	PRIORITY* priority_to_new_array()
	{
		PRIORITY* new_array = new PRIORITY[priority.size()];

		for (int i = 0; i < priority.size(); i++)
		{
			new_array[i] = priority[i];
		}

		return new_array;
	}

	// Returns a vector of the current queue's priority values
	std::vector<DataType> priority_to_vector()
	{
		return priority;
	}

	// Returns a dictionary of the current queue data and their priorities
	std::map<DataType, PRIORITY> to_map()
	{
		std::map<DataType, PRIORITY> map = std::map<DataType, PRIORITY>(queue.size());

		for (int i = 0; i < queue.size(); i++)
		{
			map[queue[i]] = priority[i];
		}

		return map;
	}

	// Default constructor
	priority_queue()
	{
		queue = std::vector<DataType>();

		priority = std::vector<PRIORITY>();
	}

	// Array constructor
	priority_queue(int number_of_elements, DataType data[], PRIORITY priority[])
	{
		queue = std::vector<DataType>();

		this->priority = std::vector<PRIORITY>();

		for (int i = 0; i < number_of_elements; i++)
		{
			enqueue(data[i], priority[i]);
		}
	}

	// Vector constructor
	priority_queue(std::vector<DataType> data, std::vector<PRIORITY> priority)
	{
		queue = std::vector<DataType>();

		this->priority = std::vector<PRIORITY>();

		for (int i = 0; i < data.size(); i++)
		{
			Enqueue(data[i], priority[i]);
		}
	}

	// Queue constructor
	priority_queue(priority_queue<DataType>&& data)
	{
		queue = data.queue;

		priority = data.priority;
	}
};

// A first in first out list of a specified data type.
template <class DataType> class Queue
{
private:

	// Vector of data
	std::vector<DataType> queue = std::vector<DataType>();

public:

	// Enqueue new data and return the index
	int Enqueue(DataType data)
	{
		queue.push_back(data);

		return queue.size() - 1;
	}

	// Dequeue and return the data with the highest priority
	DataType Dequeue()
	{
		DataType dequeuedData = queue[0];

		queue.erase(queue.begin());

		return dequeuedData;
	}

	// Enqueue new data and return the index
	int Push(DataType data)
	{
		return Enqueue(data);
	}

	// Dequeue and return the data with the highest priority
	DataType Pop()
	{
		return Dequeue();
	}

	// Returns the data with the highest priority (without removing it from the queue)
	DataType Peek()
	{
		return queue[0];
	}

	// Returns the data with the lowest priority (without removing it from the queue)
	DataType PeekLast()
	{
		return queue[queue.size() - 1];
	}

	// Returns the data at the given index
	DataType Get(int index)
	{
		return queue[index];
	}

	// Sets the data at the given index
	Queue<DataType>& Set(int index, DataType new_data)
	{
		queue[index] = new_data;

		return *this;
	}

	// Clears the queue and returns the total number of cleared nodes
	int Clear()
	{
		int total = queue.size();

		queue.clear();

		return total;
	}

	// Returns the size of the queue
	int Count()
	{
		return queue.size();
	}

	// Returns if the queue is empty
	bool IsEmpty()
	{
		return queue.size() == 0;
	}

	// Return the index of the given element, or -1 if it was not found
	int Find(DataType data)
	{
		for (int i = 0; i < queue.size(); i++)
		{
			if (queue[i] == data)
			{
				return i;
			}
		}

		return -1;
	}

	// Return whether the queue contains the given element
	bool Contains(DataType data)
	{
		for (int i = 0; i < queue.size(); i++)
		{
			if (queue[i] == data)
			{
				return true;
			}
		}

		return false;
	}

	// Return the number of matching elements
	int Total(DataType data)
	{
		int total = 0;

		for (int i = 0; i < queue.size(); i++)
		{
			if (queue[i] == data)
			{
				total++;
			}
		}

		return total;
	}

	// Returns a new pointer to a new array of the current queue (must be deallocated)
	DataType* ToNewArray()
	{
		DataType* new_array = new DataType[queue.size()];

		for (int i = 0; i < queue.size(); i++)
		{
			new_array[i] = queue[i];
		}

		return new_array;
	}

	// Returns a vector of the current queue data
	std::vector<DataType> ToVector()
	{
		return queue;
	}

	// Default constructor
	Queue()
	{
		queue = std::vector<DataType>();
	}

	// Array constructor
	Queue(int number_of_elements, DataType data[])
	{
		queue = std::vector<DataType>();

		for (int i = 0; i < number_of_elements; i++)
		{
			queue.push_back(data[i]);
		}
	}

	// Vector constructor
	Queue(std::vector<DataType> data)
	{
		queue = data;
	}

	// Parameter constructor
	Queue(int number_of_elements, DataType data...)
	{
		queue = std::vector<DataType>();

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_elements; i++)
		{
			queue.push_back(va_arg(list, DataType));
		}

		va_end(list);
	}

	// List constructor
	Queue(const std::initializer_list<DataType> data)
	{
		queue = std::vector<DataType>();

		for (int i = 0; i < data.size(); i++)
		{
			queue.push_back(data[i]);
		}
	}
};

// A first in first out list of a specified data type with an associated priority value assigned to each element used for adding and removing data in a specific order.
template <class DataType> class PriorityQueue
{
private:

	// Vector of data
	std::vector<DataType> queue = std::vector<DataType>();

	// Vector of priority
	std::vector<PRIORITY> priority = std::vector<PRIORITY>();

public:

	// Enqueue new data and return the index
	int Enqueue(DataType data, PRIORITY new_priority)
	{
		for (int i = 0; i < queue.size(); i++)
		{
			if (new_priority > priority[i])
			{
				queue.insert(queue.begin() + i, data);

				priority.insert(priority.begin() + i, new_priority);

				return i;
			}
		}

		queue.push_back(data);

		priority.push_back(new_priority);

		return queue.size() - 1;
	}

	// Dequeue and return the data with the highest priority
	DataType Dequeue()
	{
		DataType dequeuedData = queue[0];

		queue.erase(queue.begin());

		priority.erase(priority.begin());

		return dequeuedData;
	}

	// Enqueue new data and return the index
	int Push(DataType data, PRIORITY new_priority)
	{
		return Enqueue(data, new_priority);
	}

	// Dequeue and return the data with the highest priority
	DataType Pop()
	{
		return Dequeue();
	}

	// Returns the data with the highest priority (without removing it from the queue)
	DataType Peek()
	{
		return queue[0];
	}

	// Returns the data with the lowest priority (without removing it from the queue)
	DataType PeekLast()
	{
		return queue[queue.size() - 1];
	}

	// Returns the data at the given index
	DataType Get(int index)
	{
		return queue[index];
	}

	// Sets the data at the given index
	PriorityQueue<DataType>& Set(int index, DataType new_data)
	{
		queue[index] = new_data;

		return *this;
	}

	// Sets the data at the given index
	PriorityQueue<DataType>& Set(int index, DataType new_data, PRIORITY new_priority)
	{
		queue[index] = new_data;

		priority[index] = new_priority;

		return *this;
	}

	// Returns the highest priority value (the priority which is closest to being dequeued)
	PRIORITY HighestPriority()
	{
		return priority[0];
	}

	// Returns the lowest priority value (the priority which is furthest from being dequeued)
	PRIORITY LowestPriority()
	{
		return priority[priority.size() - 1];
	}

	// Returns the priority value of the given data in the queue
	PRIORITY GetPriority(DataType data)
	{
		PRIORITY priority = 0;

		for (int i = 0; i < queue.size(); i++)
		{
			if (queue[i] == data)
			{
				return this->priority[i];
			}
		}

		return priority;
	}

	// Returns the priority value at the given index in the queue
	PRIORITY GetPriorityAt(int index)
	{
		return priority[index];
	}

	// Sets the priority value of the given data
	PriorityQueue<DataType>& SetPriority(DataType data, PRIORITY new_priority)
	{
		for (int i = 0; i < queue.size(); i++)
		{
			if (queue[i] == data)
			{
				priority[i] = new_priority;

				return *this;
			}
		}

		return *this;
	}

	// Sets the priority value at the given index
	PriorityQueue<DataType>& SetPriorityAt(int index, PRIORITY new_priority)
	{
		priority[index] = new_priority;

		return *this;
	}

	// Clears the queue and returns the total number of cleared nodes
	int Clear()
	{
		int total = queue.size();

		queue.clear();

		priority.clear();

		return total;
	}

	// Returns the size of the queue
	int Count()
	{
		return queue.size();
	}

	// Returns if the queue is empty
	bool IsEmpty()
	{
		return queue.size() == 0;
	}

	// Return the index of the given element, or -1 if it was not found
	int Find(DataType data)
	{
		for (int i = 0; i < queue.size(); i++)
		{
			if (queue[i] == data)
			{
				return i;
			}
		}

		return -1;
	}

	// Return whether the queue contains the given element
	bool Contains(DataType data)
	{
		for (int i = 0; i < queue.size(); i++)
		{
			if (queue[i] == data)
			{
				return true;
			}
		}

		return false;
	}

	// Return the number of matching elements
	int Total(DataType data)
	{
		int total = 0;

		for (int i = 0; i < queue.size(); i++)
		{
			if (queue[i] == data)
			{
				total++;
			}
		}

		return total;
	}

	// Returns a new pointer to a new array of the current queue (must be deallocated)
	DataType* ToNewArray()
	{
		DataType* new_array = new DataType[queue.size()];

		for (int i = 0; i < queue.size(); i++)
		{
			new_array[i] = queue[i];
		}

		return new_array;
	}

	// Returns a vector of the current queue data
	std::vector<DataType> ToVector()
	{
		return queue;
	}

	// Returns a new pointer to a new array of the current queue's priority values (must be deallocated)
	PRIORITY* PriorityToNewArray()
	{
		PRIORITY* new_array = new PRIORITY[priority.size()];

		for (int i = 0; i < priority.size(); i++)
		{
			new_array[i] = priority[i];
		}

		return new_array;
	}

	// Returns a vector of the current queue's priority values
	std::vector<DataType> PriorityToVector()
	{
		return priority;
	}

	// Returns a dictionary of the current queue data and their priorities
	std::map<DataType, PRIORITY> ToMap()
	{
		std::map<DataType, PRIORITY> map = std::map<DataType, PRIORITY>(queue.size());

		for (int i = 0; i < queue.size(); i++)
		{
			map[queue[i]] = priority[i];
		}

		return map;
	}

	// Default constructor
	PriorityQueue()
	{
		queue = std::vector<DataType>();

		priority = std::vector<PRIORITY>();
	}

	// Array constructor
	PriorityQueue(int number_of_elements, DataType data[], PRIORITY priority[])
	{
		queue = std::vector<DataType>();

		this->priority = std::vector<PRIORITY>();

		for (int i = 0; i < number_of_elements; i++)
		{
			Enqueue(data[i], priority[i]);
		}
	}

	// Vector constructor
	PriorityQueue(std::vector<DataType> data, std::vector<PRIORITY> priority)
	{
		queue = std::vector<DataType>();

		this->priority = std::vector<PRIORITY>();

		for (int i = 0; i < data.size(); i++)
		{
			Enqueue(data[i], priority[i]);
		}
	}
};
