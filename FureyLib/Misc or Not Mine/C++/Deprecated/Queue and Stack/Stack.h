
// Stack and Priority Stack Data Types Script
// by Kyle Furey

#pragma once
#include <vector>
#include <map>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the class
#include "Stack.h"

// Data type used for priority value.
#define PRIORITY float

// A last in first out list of a specified data type.
template <class DataType> class stack
{
private:

	// Vector of data
	std::vector<DataType> s = std::vector<DataType>();

public:

	// Stack new data and return the index
	int stack_on(DataType data)
	{
		s.insert(s.begin(), data);

		return 0;
	}

	// Unstack and return the data with the highest priority
	DataType unstack()
	{
		DataType unstackedData = s[0];

		s.erase(s.begin());

		return unstackedData;
	}

	// Stack new data and return the index
	int push(DataType data)
	{
		return stack_on(data);
	}

	// Unstack and return the data with the highest priority
	DataType pop()
	{
		return unstack();
	}

	// Returns the data with the highest priority (without removing it from the stack)
	DataType peek()
	{
		return s[0];
	}

	// Returns the data with the lowest priority (without removing it from the stack)
	DataType peek_last()
	{
		return s[s.size() - 1];
	}

	// Returns the data at the given index
	DataType get(int index)
	{
		return s[index];
	}

	// Sets the data at the given index
	stack<DataType>& set(int index, DataType new_data)
	{
		s[index] = new_data;

		return *this;
	}

	// Clears the stack and returns the total number of cleared nodes
	int clear()
	{
		int total = s.size();

		s.clear();

		return total;
	}

	// Returns the size of the stack
	int count()
	{
		return stack.size();
	}

	// Returns if the stack is empty
	bool is_empty()
	{
		return s.size() == 0;
	}

	// Return the index of the given element, or -1 if it was not found
	int find(DataType data)
	{
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == data)
			{
				return i;
			}
		}

		return -1;
	}

	// Return whether the stack contains the given element
	bool contains(DataType data)
	{
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == data)
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

		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == data)
			{
				total++;
			}
		}

		return total;
	}

	// Returns a new pointer to a new array of the current stack (must be deallocated)
	DataType* to_new_array()
	{
		DataType* new_array = new DataType[s.size()];

		for (int i = 0; i < s.size(); i++)
		{
			new_array[i] = s[i];
		}

		return new_array;
	}

	// Returns a vector of the current stack data
	std::vector<DataType> to_vector()
	{
		return s;
	}

	// Default constructor
	stack()
	{
		s = std::vector<DataType>();
	}

	// Array constructor
	stack(int number_of_elements, DataType data[])
	{
		s = std::vector<DataType>();

		for (int i = 0; i < number_of_elements; i++)
		{
			s.insert(s.begin(), data[i]);
		}
	}

	// Vector constructor
	stack(std::vector<DataType> data)
	{
		s = data;
	}

	// Parameter constructor
	stack(int number_of_elements, DataType data...)
	{
		s = std::vector<DataType>();

		va_list list;

		va_start(list, number_of_elements);

		for (int i = 0; i < number_of_elements; i++)
		{
			s.insert(s.begin(), data);
			
			data = va_arg(list, DataType);
		}

		va_end(list);
	}

	// List constructor
	stack(const std::initializer_list<DataType> data)
	{
		s = std::vector<DataType>();

		for (int i = 0; i < data.size(); i++)
		{
			s.insert(s.begin(), data[i]);
		}
	}

	// Stack constructor
	stack(stack<DataType>&& data)
	{
		s = data.s;
	}
};

// A last in first out list of a specified data type with an associated priority value assigned to each element used for adding and removing data in a specific order.
template <class DataType> class priority_stack
{
private:

	// Vector of data
	std::vector<DataType> stack = std::vector<DataType>();

	// Vector of priority
	std::vector<PRIORITY> priority = std::vector<PRIORITY>();

public:

	// Stack new data and return the index
	int stack_on(DataType data, PRIORITY new_priority)
	{
		for (int i = 0; i < stack.size(); i++)
		{
			if (new_priority >= priority[i])
			{
				stack.insert(stack.begin() + i, data);

				priority.insert(priority.begin() + i, new_priority);

				return i;
			}
		}

		stack.push_back(data);

		priority.push_back(new_priority);

		return stack.size() - 1;
	}

	// Unstack and return the data with the highest priority
	DataType unstack()
	{
		DataType unstackedData = stack[0];

		stack.erase(stack.begin());

		priority.erase(priority.begin());

		return unstackedData;
	}

	// Stack new data and return the index
	int push(DataType data, PRIORITY new_priority)
	{
		return stack_on(data, new_priority);
	}

	// Unstack and return the data with the highest priority
	DataType pop()
	{
		return unstack();
	}

	// Returns the data with the highest priority (without removing it from the stack)
	DataType peek()
	{
		return stack[0];
	}

	// Returns the data with the lowest priority (without removing it from the stack)
	DataType peek_last()
	{
		return stack[stack.size() - 1];
	}

	// Returns the data at the given index
	DataType get(int index)
	{
		return stack[index];
	}

	// Sets the data at the given index
	priority_stack<DataType>& set(int index, DataType new_data)
	{
		stack[index] = new_data;

		return *this;
	}

	// Sets the data at the given index
	priority_stack<DataType>& set(int index, DataType new_data, PRIORITY new_priority)
	{
		stack[index] = new_data;

		priority[index] = new_priority;

		return *this;
	}

	// Returns the highest priority value (the priority which is closest to being unstacked)
	PRIORITY highest_priority()
	{
		return priority[0];
	}

	// Returns the lowest priority value (the priority which is furthest from being unstacked)
	PRIORITY lowest_priority()
	{
		return priority[priority.size() - 1];
	}

	// Returns the priority value of the given data in the stack
	PRIORITY get_priority(DataType data)
	{
		PRIORITY priority = 0;

		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i] == data)
			{
				return this->priority[i];
			}
		}

		return priority;
	}

	// Returns the priority value at the given index in the stack
	PRIORITY get_priority_at(int index)
	{
		return priority[index];
	}

	// Sets the priority value of the given data
	priority_stack<DataType>& set_priority(DataType data, PRIORITY new_priority)
	{
		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i] == data)
			{
				priority[i] = new_priority;

				return *this;
			}
		}

		return *this;
	}

	// Sets the priority value at the given index
	priority_stack<DataType>& set_priority_at(int index, PRIORITY new_priority)
	{
		priority[index] = new_priority;

		return *this;
	}

	// Clears the stack and returns the total number of cleared nodes
	int clear()
	{
		int total = stack.size();

		stack.clear();

		priority.clear();

		return total;
	}

	// Returns the size of the stack
	int count()
	{
		return stack.size();
	}

	// Returns if the stack is empty
	bool is_empty()
	{
		return stack.size() == 0;
	}

	// Return the index of the given element, or -1 if it was not found
	int find(DataType data)
	{
		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i] == data)
			{
				return i;
			}
		}

		return -1;
	}

	// Return whether the stack contains the given element
	bool contains(DataType data)
	{
		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i] == data)
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

		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i] == data)
			{
				total++;
			}
		}

		return total;
	}

	// Returns a new pointer to a new array of the current stack (must be deallocated)
	DataType* to_new_array()
	{
		DataType* new_array = new DataType[stack.size()];

		for (int i = 0; i < stack.size(); i++)
		{
			new_array[i] = stack[i];
		}

		return new_array;
	}

	// Returns a vector of the current stack data
	std::vector<DataType> to_vector()
	{
		return stack;
	}

	// Returns a new pointer to a new array of the current stack's priority values (must be deallocated)
	PRIORITY* priority_to_new_array()
	{
		PRIORITY* new_array = new PRIORITY[priority.size()];

		for (int i = 0; i < priority.size(); i++)
		{
			new_array[i] = priority[i];
		}

		return new_array;
	}

	// Returns a vector of the current stack's priority values
	std::vector<DataType> priority_to_vector()
	{
		return priority;
	}

	// Returns a dictionary of the current stack data and their priorities
	std::map<DataType, PRIORITY> to_map()
	{
		std::map<DataType, PRIORITY> map = std::map<DataType, PRIORITY>(stack.size());

		for (int i = 0; i < stack.size(); i++)
		{
			map[stack[i]] = priority[i];
		}

		return map;
	}

	// Default constructor
	priority_stack()
	{
		stack = std::vector<DataType>();

		priority = std::vector<PRIORITY>();
	}

	// Array constructor
	priority_stack(int number_of_elements, DataType data[], PRIORITY priority[])
	{
		stack = std::vector<DataType>();

		this->priority = std::vector<PRIORITY>();

		for (int i = 0; i < number_of_elements; i++)
		{
			stack_on(data[i], priority[i]);
		}
	}

	// Vector constructor
	priority_stack(std::vector<DataType> data, std::vector<PRIORITY> priority)
	{
		stack = std::vector<DataType>();

		this->priority = std::vector<PRIORITY>();

		for (int i = 0; i < data.size(); i++)
		{
			stack_on(data[i], priority[i]);
		}
	}

	// Stack constructor
	priority_stack(priority_stack<DataType>&& data)
	{
		stack = data.stack;

		priority = data.priority;
	}
};

// A last in first out list of a specified data type.
template <class DataType> class Stack
{
private:

	// Vector of data
	std::vector<DataType> stack = std::vector<DataType>();

public:

	// Stack new data and return the index
	int StackOn(DataType data)
	{
		stack.insert(stack.begin(), data);

		return 0;
	}

	// Unstack and return the data with the highest priority
	DataType Unstack()
	{
		DataType unstackedData = stack[0];

		stack.erase(stack.begin());

		return unstackedData;
	}

	// Stack new data and return the index
	int Push(DataType data)
	{
		return StackOn(data);
	}

	// Unstack and return the data with the highest priority
	DataType Pop()
	{
		return Unstack();
	}

	// Returns the data with the highest priority (without removing it from the stack)
	DataType Peek()
	{
		return stack[0];
	}

	// Returns the data with the lowest priority (without removing it from the stack)
	DataType PeekLast()
	{
		return stack[stack.size() - 1];
	}

	// Returns the data at the given index
	DataType Get(int index)
	{
		return stack[index];
	}

	// Sets the data at the given index
	Stack<DataType>& Set(int index, DataType new_data)
	{
		stack[index] = new_data;

		return *this;
	}

	// Clears the stack and returns the total number of cleared nodes
	int Clear()
	{
		int total = stack.size();

		stack.clear();

		return total;
	}

	// Returns the size of the stack
	int Count()
	{
		return stack.size();
	}

	// Returns if the stack is empty
	bool IsEmpty()
	{
		return stack.size() == 0;
	}

	// Return the index of the given element, or -1 if it was not found
	int Find(DataType data)
	{
		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i] == data)
			{
				return i;
			}
		}

		return -1;
	}

	// Return whether the stack contains the given element
	bool Contains(DataType data)
	{
		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i] == data)
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

		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i] == data)
			{
				total++;
			}
		}

		return total;
	}

	// Returns a new pointer to a new array of the current stack (must be deallocated)
	DataType* ToNewArray()
	{
		DataType* new_array = new DataType[stack.size()];

		for (int i = 0; i < stack.size(); i++)
		{
			new_array[i] = stack[i];
		}

		return new_array;
	}

	// Returns a vector of the current stack data
	std::vector<DataType> ToVector()
	{
		return stack;
	}

	// Default constructor
	Stack()
	{
		stack = std::vector<DataType>();
	}

	// Array constructor
	Stack(int number_of_elements, DataType data[])
	{
		stack = std::vector<DataType>();

		for (int i = 0; i < number_of_elements; i++)
		{
			stack.insert(stack.begin(), data[i]);
		}
	}

	// Vector constructor
	Stack(std::vector<DataType> data)
	{
		stack = data;
	}

	// Parameter constructor
	Stack(int number_of_elements, DataType data...)
	{
		stack = std::vector<DataType>();

		va_list list;

		va_start(list, number_of_elements);

		for (int i = 0; i < number_of_elements; i++)
		{
			stack.insert(stack.begin(), data);
			
			data = va_arg(list, DataType);
		}

		va_end(list);
	}

	// List constructor
	Stack(const std::initializer_list<DataType> data)
	{
		stack = std::vector<DataType>();

		for (int i = 0; i < data.size(); i++)
		{
			stack.insert(stack.begin(), data[i]);
		}
	}

	// Stack constructor
	Stack(Stack<DataType>&& data)
	{
		stack = data.stack;
	}
};

// A last in first out list of a specified data type with an associated priority value assigned to each element used for adding and removing data in a specific order.
template <class DataType> class PriorityStack
{
private:

	// Vector of data
	std::vector<DataType> stack = std::vector<DataType>();

	// Vector of priority
	std::vector<PRIORITY> priority = std::vector<PRIORITY>();

public:

	// Stack new data and return the index
	int StackOn(DataType data, PRIORITY new_priority)
	{
		for (int i = 0; i < stack.size(); i++)
		{
			if (new_priority >= priority[i])
			{
				stack.insert(stack.begin() + i, data);

				priority.insert(priority.begin() + i, new_priority);

				return i;
			}
		}

		stack.push_back(data);

		priority.push_back(new_priority);

		return stack.size() - 1;
	}

	// Unstack and return the data with the highest priority
	DataType Unstack()
	{
		DataType unstackedData = stack[0];

		stack.erase(stack.begin());

		priority.erase(priority.begin());

		return unstackedData;
	}

	// Stack new data and return the index
	int Push(DataType data, PRIORITY new_priority)
	{
		return StackOn(data, new_priority);
	}

	// Unstack and return the data with the highest priority
	DataType Pop()
	{
		return Unstack();
	}

	// Returns the data with the highest priority (without removing it from the stack)
	DataType Peek()
	{
		return stack[0];
	}

	// Returns the data with the lowest priority (without removing it from the stack)
	DataType PeekLast()
	{
		return stack[stack.size() - 1];
	}

	// Returns the data at the given index
	DataType Get(int index)
	{
		return stack[index];
	}

	// Sets the data at the given index
	PriorityStack<DataType>& Set(int index, DataType new_data)
	{
		stack[index] = new_data;

		return *this;
	}

	// Sets the data at the given index
	PriorityStack<DataType>& Set(int index, DataType new_data, PRIORITY new_priority)
	{
		stack[index] = new_data;

		priority[index] = new_priority;

		return *this;
	}

	// Returns the highest priority value (the priority which is closest to being unstacked)
	PRIORITY HighestPriority()
	{
		return priority[0];
	}

	// Returns the lowest priority value (the priority which is furthest from being unstacked)
	PRIORITY LowestPriority()
	{
		return priority[priority.size() - 1];
	}

	// Returns the priority value of the given data in the stack
	PRIORITY GetPriority(DataType data)
	{
		PRIORITY priority = 0;

		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i] == data)
			{
				return this->priority[i];
			}
		}

		return priority;
	}

	// Returns the priority value at the given index in the stack
	PRIORITY GetPriorityAt(int index)
	{
		return priority[index];
	}

	// Sets the priority value of the given data
	PriorityStack<DataType>& SetPriority(DataType data, PRIORITY new_priority)
	{
		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i] == data)
			{
				priority[i] = new_priority;

				return *this;
			}
		}

		return *this;
	}

	// Sets the priority value at the given index
	PriorityStack<DataType>& SetPriorityAt(int index, PRIORITY new_priority)
	{
		priority[index] = new_priority;

		return *this;
	}

	// Clears the stack and returns the total number of cleared nodes
	int Clear()
	{
		int total = stack.size();

		stack.clear();

		priority.clear();

		return total;
	}

	// Returns the size of the stack
	int Count()
	{
		return stack.size();
	}

	// Returns if the stack is empty
	bool IsEmpty()
	{
		return stack.size() == 0;
	}

	// Return the index of the given element, or -1 if it was not found
	int Find(DataType data)
	{
		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i] == data)
			{
				return i;
			}
		}

		return -1;
	}

	// Return whether the stack contains the given element
	bool Contains(DataType data)
	{
		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i] == data)
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

		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i] == data)
			{
				total++;
			}
		}

		return total;
	}

	// Returns a new pointer to a new array of the current stack (must be deallocated)
	DataType* ToNewArray()
	{
		DataType* new_array = new DataType[stack.size()];

		for (int i = 0; i < stack.size(); i++)
		{
			new_array[i] = stack[i];
		}

		return new_array;
	}

	// Returns a vector of the current stack data
	std::vector<DataType> ToVector()
	{
		return stack;
	}

	// Returns a new pointer to a new array of the current stack's priority values (must be deallocated)
	PRIORITY* PriorityToNewArray()
	{
		PRIORITY* new_array = new PRIORITY[priority.size()];

		for (int i = 0; i < priority.size(); i++)
		{
			new_array[i] = priority[i];
		}

		return new_array;
	}

	// Returns a vector of the current stack's priority values
	std::vector<DataType> PriorityToVector()
	{
		return priority;
	}

	// Returns a dictionary of the current stack data and their priorities
	std::map<DataType, PRIORITY> ToMap()
	{
		std::map<DataType, PRIORITY> map = std::map<DataType, PRIORITY>(stack.size());

		for (int i = 0; i < stack.size(); i++)
		{
			map[stack[i]] = priority[i];
		}

		return map;
	}

	// Default constructor
	PriorityStack()
	{
		stack = std::vector<DataType>();

		priority = std::vector<PRIORITY>();
	}

	// Array constructor
	PriorityStack(int number_of_elements, DataType data[], PRIORITY priority[])
	{
		stack = std::vector<DataType>();

		this->priority = std::vector<PRIORITY>();

		for (int i = 0; i < number_of_elements; i++)
		{
			StackOn(data[i], priority[i]);
		}
	}

	// Vector constructor
	PriorityStack(std::vector<DataType> data, std::vector<PRIORITY> priority)
	{
		stack = std::vector<DataType>();

		this->priority = std::vector<PRIORITY>();

		for (int i = 0; i < data.size(); i++)
		{
			StackOn(data[i], priority[i]);
		}
	}

	// Stack constructor
	PriorityStack(PriorityStack<DataType>&& data)
	{
		stack = data.stack;

		priority = data.priority;
	}
};
