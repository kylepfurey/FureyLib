
// Queue and Priority Queue Data Types Script
// by Kyle Furey

#pragma once
#include <vector>

// Include this heading to use the class
#include "PriorityQueue.h"

// Queue Class
template <class DataType> class queue
{
private:

	// Vector of data
	std::vector<DataType> q = std::vector<DataType>(0);


public:

	// Constructors
	queue() { }

	// Deconstructor
	~queue() { }

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

	// Clears the queue and returns the total number of cleared nodes
	int clear()
	{
		int total = q.size();

		q.clear();

		return total;
	}

	// Returns the size of the queue
	int size()
	{
		return queue.size();
	}

	// Returns if the queue is empty
	bool is_empty()
	{
		return q.size() == 0;
	}
};

// Queue Class
template <class DataType> class Queue
{
private:

	// Vector of data
	std::vector<DataType> queue = std::vector<DataType>(0);


public:

	// Constructors
	Queue() { }

	// Deconstructor
	~Queue() { }

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

	// Clears the queue and returns the total number of cleared nodes
	int Clear()
	{
		int total = queue.size();

		queue.clear();

		return total;
	}

	// Returns the size of the queue
	int Size()
	{
		return queue.size();
	}

	// Returns if the queue is empty
	bool IsEmpty()
	{
		return queue.size() == 0;
	}
};

// Priority Queue Class
template <class DataType> class priority_queue
{
private:

	// Vector of data
	std::vector<DataType> queue = std::vector<DataType>(0);

	// Vector of priority
	std::vector<float> priority = std::vector<float>(0);

public:
	
	// Constructors
	priority_queue() { }

	// Deconstructor
	~priority_queue() { }

	// Enqueue new data and return the index
	int enqueue(DataType data, float newPriority)
	{
		for (int i = 0; i < queue.size(); i++)
		{
			if (newPriority < priority[i])
			{
				queue.insert(queue.begin() + i, data);

				priority.insert(priority.begin() + i, newPriority);

				return i;
			}
		}

		queue.push_back(data);

		priority.push_back(newPriority);

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
	int push(DataType data, float newPriority)
	{
		return enqueue(data, newPriority);
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

	// Returns the highest priority value (the priority which is closest to being dequeued)
	int highest_priority()
	{
		return priority[0];
	}

	// Returns the lowest priority value (the priority which is furthest from being dequeued)
	int lowest_priority()
	{
		return priority[priority.size() - 1];
	}

	// Clears the queue and returns the total number of cleared nodes
	int clear()
	{
		int total = queue.size();

		queue.clear();

		return total;
	}

	// Returns the size of the queue
	int size()
	{
		return queue.size();
	}

	// Returns if the queue is empty
	bool is_empty()
	{
		return queue.size() == 0;
	}
};

// Priority Queue Class
template <class DataType> class PriorityQueue
{
private:

	// Vector of data
	std::vector<DataType> queue = std::vector<DataType>(0);

	// Vector of priority
	std::vector<float> priority = std::vector<float>(0);

public:

	// Constructors
	PriorityQueue() { }

	// Deconstructor
	~PriorityQueue() { }

	// Enqueue new data and return the index
	int Enqueue(DataType data, float newPriority)
	{
		for (int i = 0; i < queue.size(); i++)
		{
			if (newPriority < priority[i])
			{
				queue.insert(queue.begin() + i, data);

				priority.insert(priority.begin() + i, newPriority);

				return i;
			}
		}

		queue.push_back(data);

		priority.push_back(newPriority);

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
	int Push(DataType data, float newPriority)
	{
		return Enqueue(data, newPriority);
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

	// Returns the highest priority value (the priority which is closest to being dequeued)
	int HighestPriority()
	{
		return priority[0];
	}

	// Returns the lowest priority value (the priority which is furthest from being dequeued)
	int LowestPriority()
	{
		return priority[priority.size() - 1];
	}

	// Clears the queue and returns the total number of cleared nodes
	int Clear()
	{
		int total = queue.size();

		queue.clear();

		return total;
	}

	// Returns the size of the queue
	int Size()
	{
		return queue.size();
	}

	// Returns if the queue is empty
	bool IsEmpty()
	{
		return queue.size() == 0;
	}
};
