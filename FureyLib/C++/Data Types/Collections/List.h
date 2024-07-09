
// Linked List Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/list/list/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.linkedlist-1?view=net-8.0

#pragma once
#include <string>
#include <vector>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the class
#include "List.h"

// Data type used for sorting
#define SORT_TYPE float

// Forward declaration of list_node
template<typename DataType> class list_node;

// Class that stores data and connections to the previous and next nodes in a doubly linked list.
template<typename DataType> class list_node
{
public:

	// LINKED LIST NODE VARIABLES

	// A link to the previous node
	list_node<DataType>* previous = nullptr;

	// This node's data
	DataType data = DataType();

	// A link to the next node
	list_node<DataType>* next = nullptr;


	// LINKED LIST NODE CONSTRUCTOR

	// Default constructor
	list_node(list_node<DataType>* previous = nullptr, DataType data = DataType(), list_node<DataType>* next = nullptr)
	{
		this->previous = previous;

		this->data = data;

		this->next = next;
	}

	// Default constructor
	list_node(DataType data, list_node<DataType>* previous = nullptr, list_node<DataType>* next = nullptr)
	{
		this->data = data;

		this->previous = previous;

		this->next = next;
	}
};

// Class used to store a series of nodes with data in a circular doubly linked list.
template<typename DataType> class list
{
private:

	// LINKED LIST VARIABLES

	// The head (starting) node of the linked list
	list_node<DataType>* head = nullptr;

	// The current number of nodes in the linked list
	int node_size = 0;

	// Deallocates each of the linked list's node's memory
	void deallocate()
	{
		list_node<DataType>* node = head;

		for (int i = 0; i < node_size; i++)
		{
			list_node<DataType>* next_node = node->next;

			delete node;

			node = next_node;
		}
	}

public:

	// TO ARRAY AND VECTOR

	// Returns an array of the current linked list (MUST BE DEALLOCATED)
	DataType* to_new_array()
	{
		if (node_size == 0)
		{
			return nullptr;
		}

		// Copy the linked list into an array
		DataType* new_array = new DataType[node_size];

		// Set the current nodes
		list_node<DataType>* node = head;

		// Loop through each node and add it to the array
		for (int i = 0; i < node_size; i++)
		{
			new_array[i] = node->data;

			node = node->next;
		}

		return new_array;
	}

	// Returns a vector of the current linked list
	std::vector<DataType> to_vector()
	{
		if (node_size == 0)
		{
			return std::vector<DataType>();
		}

		// Copy the linked list into an list
		std::vector<DataType> new_list = std::vector<DataType>();

		// Set the current nodes
		list_node<DataType>* node = head;

		// Loop through each node and add it to the array
		for (int i = 0; i < node_size; i++)
		{
			new_list.push_back(node->data);

			node = node->next;
		}

		return new_list;
	}


	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	list()
	{
		head = nullptr;

		node_size = 0;
	}

	// Copy constructor
	list(const list<DataType>& copied_list)
	{
		if (copied_list.node_size == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		head = new list_node<DataType>(copied_list.head->data);

		node_size = copied_list.node_size;

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			DataType* array = copied_list.to_new_array();

			list_node<DataType>* node = head;

			for (int i = 1; i < node_size; i++)
			{
				list_node<DataType>* new_node = new list_node<DataType>(array[i]);

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;

			delete[] array;

			array = nullptr;
		}
	}

	// Move constructor
	list(list<DataType>&& moved_list) noexcept
	{
		head = moved_list.head;

		moved_list.head = nullptr;

		node_size = moved_list.node_size;

		moved_list.node_size = 0;
	}

	// Data constructor
	list(DataType data)
	{
		head = new list_node<DataType>(data);

		head->previous = head;

		head->next = head;

		node_size = 1;
	}

	// Array constructor
	list(int array_size, DataType* array)
	{
		if (array_size == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		head = new list_node<DataType>(array[0]);

		node_size = array_size;

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			list_node<DataType>* node = head;

			for (int i = 1; i < array_size; i++)
			{
				list_node<DataType>* new_node = new list_node<DataType>(array[i]);

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;
		}
	}

	// Array constructor
	list(int argc, DataType array ...)
	{
		if (argc == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		va_list _va_list;

		va_start(_va_list, argc);

		DataType* argv = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, DataType);
		}

		va_end(_va_list);

		head = new list_node<DataType>(argv[0]);

		node_size = argc;

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			list_node<DataType>* node = head;

			for (int i = 1; i < argc; i++)
			{
				list_node<DataType>* new_node = new list_node<DataType>(argv[i]);

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;
		}

		delete[] argv;

		argv = nullptr;
	}

	// Vector constructor
	list(std::vector<DataType> vector)
	{
		if (vector.size() == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		head = new list_node<DataType>(vector[0]);

		node_size = vector.size();

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			list_node<DataType>* node = head;

			for (int i = 1; i < vector.size(); i++)
			{
				list_node<DataType>* new_node = new list_node<DataType>(vector[i]);

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;
		}
	}

	// List constructor
	list(std::initializer_list<DataType> list)
	{
		if (list.size() == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		head = new list_node<DataType>(*list.begin());

		node_size = list.size();

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			list_node<DataType>* node = head;

			for (int i = 1; i < list.size(); i++)
			{
				list_node<DataType>* new_node = new list_node<DataType>(*(list.begin() + i));

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;
		}
	}

	// Node constructor
	list(list_node<DataType>* node)
	{
		head = node;

		head->previous = head;

		head->next = head;

		node_size = 1;
	}

	// Array constructor
	list(int array_size, list_node<DataType>** array)
	{
		if (array_size == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		head = array[0];

		node_size = array_size;

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			list_node<DataType>* node = head;

			for (int i = 1; i < array_size; i++)
			{
				node->next = array[i];

				array[i]->previous = node;

				node = array[i];
			}

			node->next = head;

			head->previous = node;
		}
	}

	// Array constructor
	list(int argc, list_node<DataType>* array ...)
	{
		if (argc == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		va_list _va_list;

		va_start(_va_list, argc);

		DataType* argv = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, DataType);
		}

		va_end(_va_list);

		head = argv[0];

		node_size = argc;

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			list_node<DataType>* node = head;

			for (int i = 1; i < argc; i++)
			{
				node->next = argv[i];

				argv[i]->previous = node;

				node = argv[i];
			}

			node->next = head;

			head->previous = node;
		}

		delete[] argv;

		argv = nullptr;
	}

	// Vector constructor
	list(std::vector<list_node<DataType>*> vector)
	{
		if (vector.size() == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		head = vector[0];

		node_size = vector.size();

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			list_node<DataType>* node = head;

			for (int i = 1; i < vector.size(); i++)
			{
				node->next = vector[i];

				vector[i]->previous = node;

				node = vector[i];
			}

			node->next = head;

			head->previous = node;
		}
	}

	// List constructor
	list(std::initializer_list<list_node<DataType>*> list)
	{
		if (list.size() == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		head = *list.begin();

		node_size = list.size();

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			list_node<DataType>* node = head;

			for (int i = 1; i < list.size(); i++)
			{
				node->next = (*(list.begin() + i));

				(*(list.begin() + i))->previous = node;

				node = (*(list.begin() + i));
			}

			node->next = head;

			head->previous = node;
		}
	}

	// Destructor
	virtual ~list()
	{
		deallocate();
	}


	// OPERATORS

	// Copy assignment operator
	list<DataType>& operator=(const list<DataType>& copied_list)
	{
		deallocate();

		if (copied_list.node_size == 0)
		{
			head = nullptr;

			node_size = 0;

			return *this;
		}

		head = new list_node<DataType>(copied_list.head->data);

		node_size = copied_list.node_size;

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			DataType* array = copied_list.to_new_array();

			list_node<DataType>* node = head;

			for (int i = 1; i < node_size; i++)
			{
				list_node<DataType>* new_node = new list_node<DataType>(array[i]);

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;

			delete[] array;

			array = nullptr;
		}

		return *this;
	}

	// Move assignment operator
	list<DataType>& operator=(list<DataType>&& moved_list) noexcept
	{
		deallocate();

		head = moved_list.head;

		moved_list.head = nullptr;

		node_size = moved_list.node_size;

		moved_list.node_size = 0;

		return *this;
	}


	// LINKED LIST EQUALITY

	// Check if another linked list is equal to the linked list
	bool equals(list<DataType> compared_list)
	{
		if (node_size == 0 || compared_list.node_size == 0)
		{
			return false;
		}

		// Check if the sizes are equal
		if (node_size != compared_list.node_size)
		{
			return false;
		}

		// Set the current nodes
		list_node<DataType>* node = head;

		list_node<DataType>* compared_node = compared_list->head;

		// Loop through each node to check if they are not equal
		for (int i = 0; i < node_size; i++)
		{
			// Are they not equal
			if (node->data != compared_node->data)
			{
				return false;
			}

			node = node->next;

			compared_node = compared_node->next;
		}

		// The lists are equal
		return true;
	}

	// Check if another linked list is equal to the linked list
	bool operator ==(list<DataType> compared_list)
	{
		return equals(compared_list);
	}

	// Check if another linked list is not equal to the linked list
	bool operator !=(list<DataType> compared_list)
	{
		return !equals(compared_list);
	}


	// SIZE

	// Return the current number of nodes of the linked list
	int size()
	{
		return node_size;
	}

	// Return whether the linked list is empty
	bool empty()
	{
		return node_size == 0;
	}


	// NODE AND DATA ACCESS

	// Returns the node at the given index
	list_node<DataType>* at(int index)
	{
		if (index < 0)
		{
			index = node_size + index;
		}

		index %= node_size;

		list_node<DataType>* node = head;

		int count = node_size / 2 - 1;

		if (index <= count)
		{
			for (int i = 0; i < index; i++)
			{
				node = node->next;
			}
		}
		else
		{
			count = node_size - index;

			for (int i = 0; i < count; i++)
			{
				node = node->previous;
			}
		}

		return node;
	}

	// Returns the node's data at the given index
	DataType& data(int index)
	{
		return at(index)->data;
	}

	// Returns the first node in the linked list
	list_node<DataType>* begin()
	{
		return head;
	}

	// Returns the last node in the linked list
	list_node<DataType>* end()
	{
		if (node_size == 0)
		{
			return nullptr;
		}

		return head->previous;
	}

	// Returns the node's data in the linked list
	DataType front()
	{
		return head->data;
	}

	// Returns the last node's data in the linked list
	DataType back()
	{
		return head->previous->data;
	}


	// LOCATING NODES

	// Finds the first matching node of the given data
	list_node<DataType>* find(DataType data)
	{
		if (node_size == 0)
		{
			return nullptr;
		}

		list_node<DataType>* node = head;

		for (int i = 0; i < node_size; i++)
		{
			if (node->data == data)
			{
				return node;
			}

			node = node->next;
		}

		return nullptr;
	}

	// Finds the last matching node of the given data
	list_node<DataType>* find_last(DataType data)
	{
		if (node_size == 0)
		{
			return nullptr;
		}

		list_node<DataType>* node = head->previous;

		for (int i = node_size - 1; i >= 0; i++)
		{
			if (node->data == data)
			{
				return node;
			}

			node = node->previous;
		}

		return nullptr;
	}

	// Returns the index of the given node, or -1 if nothing matched
	int index_of(DataType data)
	{
		if (node_size == 0)
		{
			return -1;
		}

		list_node<DataType>* node = head;

		for (int i = 0; i < node_size; i++)
		{
			if (node->data == data)
			{
				return i;
			}

			node = node->next;
		}

		return -1;
	}

	// Returns the index of the given node starting from the back, or -1 if nothing matched
	int last_index_of(DataType data)
	{
		if (node_size == 0)
		{
			return -1;
		}

		list_node<DataType>* node = head->previous;

		for (int i = node_size - 1; i >= 0; i++)
		{
			if (node->data == data)
			{
				return i;
			}

			node = node->previous;
		}

		return -1;
	}

	// Returns whether the linked list contains at least one of the elements
	bool contains(DataType contained_data)
	{
		return find(contained_data) != nullptr;
	}

	// Returns whether the linked list contains at least one of the elements, starting from the back
	bool contains_last(DataType contained_data)
	{
		return find_last(contained_data) != nullptr;
	}

	// Returns the index of the given node, or -1 if nothing matched
	int index_of(list_node<DataType>* data)
	{
		if (node_size == 0)
		{
			return -1;
		}

		list_node<DataType>* node = head;

		for (int i = 0; i < node_size; i++)
		{
			if (node == data)
			{
				return i;
			}

			node = node->next;
		}

		return -1;
	}

	// Returns the index of the given node starting from the back, or -1 if nothing matched
	int last_index_of(list_node<DataType>* data)
	{
		if (node_size == 0)
		{
			return -1;
		}

		list_node<DataType>* node = head->previous;

		for (int i = node_size - 1; i >= 0; i++)
		{
			if (node == data)
			{
				return i;
			}

			node = node->previous;
		}

		return -1;
	}

	// Returns whether the linked list contains the given node
	bool contains(list_node<DataType>* node)
	{
		return index_of(node) != -1;
	}

	// Returns whether the linked list contains the given node, starting from the back
	bool contains_last(list_node<DataType>* node)
	{
		return last_index_of(node) != -1;
	}

	// Returns the total number of instances of the given data in the linked list
	int total(DataType found_data)
	{
		if (node_size == 0)
		{
			return 0;
		}

		int count = 0;

		list_node<DataType>* node = head;

		for (int i = 0; i < node_size; i++)
		{
			if (node->data == found_data)
			{
				count++;
			}

			node = node->next;
		}

		return count;
	}


	// ADDING NODES

	// Inserts a new node of the given data at the end of the linked list
	list<DataType>& push_back(DataType data)
	{
		list_node<DataType>* new_node = new list_node<DataType>(data);

		if (node_size == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return *this;
		}

		new_node->previous = head->previous;

		new_node->next = head;

		head->previous->next = new_node;

		head->previous = new_node;

		node_size++;

		return *this;
	}

	// Inserts a range of new nodes of the given data at the end of the linked list
	list<DataType>& push_back_range(int array_size, DataType* array)
	{
		for (int i = 0; i < array_size; i++)
		{
			push_back(array[i]);
		}

		return *this;
	}

	// Inserts a range of new nodes of the given data at the end of the linked list
	list<DataType>& push_back_range(int argc, DataType data ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		DataType* argv = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = data;

			data = va_arg(_va_list, DataType);
		}

		va_end(_va_list);

		for (int i = 0; i < argc; i++)
		{
			push_back(argv[i]);
		}

		delete[] argv;

		argv = nullptr;

		return *this;
	}

	// Inserts a new node of the given data at the front of the linked list
	list<DataType>& push(DataType data)
	{
		list_node<DataType>* new_node = new list_node<DataType>(data);

		if (node_size == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return *this;
		}

		new_node->previous = head->previous;

		new_node->next = head;

		head->previous->next = new_node;

		head->previous = new_node;

		head = new_node;

		node_size++;

		return *this;
	}

	// Inserts a range of new nodes of the given data at the front of the linked list
	list<DataType>& push_range(int array_size, DataType* array)
	{
		for (int i = 0; i < array_size; i++)
		{
			push(array[i]);
		}

		return *this;
	}

	// Inserts a range of new nodes of the given data at the front of the linked list
	list<DataType>& push_range(int argc, DataType array ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		DataType* argv = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, DataType);
		}

		va_end(_va_list);

		for (int i = 0; i < argc; i++)
		{
			push(argv[i]);
		}

		delete[] argv;

		argv = nullptr;

		return *this;
	}

	// Inserts a new node of the given data before the given node
	list<DataType>& push_before(list_node<DataType>* node, DataType data)
	{
		list_node<DataType>* new_node = new list_node<DataType>(data);

		if (node_size == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return *this;
		}

		new_node->previous = node->previous;

		new_node->next = node;

		node->previous->next = new_node;

		node->previous = new_node;

		node_size++;

		return *this;
	}

	// Inserts a new node of the given data after the given node
	list<DataType>& push_after(list_node<DataType>* node, DataType data)
	{
		list_node<DataType>* new_node = new list_node<DataType>(data);

		if (node_size == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return *this;
		}

		new_node->previous = node;

		new_node->next = node->next;

		node->next->previous = new_node;

		node->next = new_node;

		node_size++;

		return *this;
	}

	// Adds a new node in the linked list at a given index
	list<DataType>& insert(int index, DataType new_data)
	{
		return push_before(at(index), new_data);
	}

	// Inserts a new node of the given data at the end of the linked list
	list<DataType>& push_back(list_node<DataType>* new_node)
	{
		if (node_size == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return *this;
		}

		new_node->previous = head->previous;

		new_node->next = head;

		head->previous->next = new_node;

		head->previous = new_node;

		node_size++;

		return *this;
	}

	// Inserts a range of new nodes of the given data at the end of the linked list
	list<DataType>& push_back_range(int array_size, list_node<DataType>* array)
	{
		for (int i = 0; i < array_size; i++)
		{
			push_back(array[i]);
		}

		return *this;
	}

	// Inserts a range of new nodes of the given data at the end of the linked list
	list<DataType>& push_back_range(int argc, list_node<DataType> array ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		list_node<DataType>* argv = new list_node<DataType>[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, list_node<DataType>);
		}

		va_end(_va_list);

		for (int i = 0; i < argc; i++)
		{
			push_back(argv[i]);
		}

		delete[] argv;

		argv = nullptr;

		return *this;
	}

	// Inserts a new node of the given data at the front of the linked list
	list<DataType>& push(list_node<DataType>* new_node)
	{
		if (node_size == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return *this;
		}

		new_node->previous = head->previous;

		new_node->next = head;

		head->previous->next = new_node;

		head->previous = new_node;

		head = new_node;

		node_size++;

		return *this;
	}

	// Inserts a range of new nodes of the given data at the front of the linked list
	list<DataType>& push_range(int array_size, list_node<DataType>* nodes)
	{
		for (int i = 0; i < array_size; i++)
		{
			push(nodes[i]);
		}

		return *this;
	}

	// Inserts a range of new nodes of the given data at the front of the linked list
	list<DataType>& push_range(int argc, list_node<DataType> array ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		list_node<DataType>* argv = new list_node<DataType>[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, list_node<DataType>);
		}

		va_end(_va_list);

		for (int i = 0; i < argc; i++)
		{
			push(argv[i]);
		}

		delete[] argv;

		argv = nullptr;

		return *this;
	}

	// Inserts a new node of the given data before the given node
	list<DataType>& push_before(list_node<DataType>* node, list_node<DataType>* new_node)
	{
		if (node_size == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return *this;
		}

		new_node->previous = node->previous;

		new_node->next = node;

		node->previous->next = new_node;

		node->previous = new_node;

		node_size++;

		return *this;
	}

	// Inserts a new node of the given data after the given node
	list<DataType>& push_after(list_node<DataType>* node, list_node<DataType>* new_node)
	{
		if (node_size == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return *this;
		}

		new_node->previous = node;

		new_node->next = node->next;

		node->next->previous = new_node;

		node->next = new_node;

		node_size++;

		return *this;
	}

	// Adds a new node in the linked list at a given index
	list<DataType>& insert(int index, list_node<DataType>* new_node)
	{
		return PushBefore(at(index), new_node);
	}


	// REMOVING NODES

	// Removes a node from its connected nodes and deallocates it
	list<DataType>& erase(list_node<DataType>* node)
	{
		node_size--;

		if (node_size <= 0)
		{
			delete node;

			node = nullptr;

			node_size = 0;

			head = nullptr;

			return *this;
		}

		node->previous->next = node->next;

		node->next->previous = node->previous;

		if (node == head)
		{
			head = head->next;
		}

		delete node;

		node = nullptr;

		return *this;
	}

	// Remove and return the first node of the given data
	list<DataType>& erase(DataType data)
	{
		list_node<DataType>* node = find(data);

		if (node == nullptr)
		{
			return *this;
		}

		erase(node);

		return *this;
	}

	// Remove the last node of the given data
	list<DataType>& erase_last(DataType data)
	{
		list_node<DataType>* node = find_last(data);

		if (node == nullptr)
		{
			return *this;
		}

		erase(node);

		return *this;
	}

	// Remove and return the first node from its connected nodes in the linked list
	DataType erase_first()
	{
		if (head == nullptr)
		{
			return DataType();
		}

		list_node<DataType>* node = head;

		DataType data = node->data;

		node_size--;

		if (node_size <= 0)
		{
			delete node;

			node_size = 0;

			head = nullptr;

			return data;
		}

		head->previous->next = head->next;

		head->next->previous = head->previous;

		head = head->next;

		delete node;

		return data;
	}

	// Remove and return the last node from its connected nodes in the linked list
	DataType erase_last()
	{
		if (head == nullptr)
		{
			return DataType();
		}

		list_node<DataType>* node = head->previous;

		DataType data = node->data;

		node_size--;

		if (node_size <= 0)
		{
			delete node;

			node_size = 0;

			head = nullptr;

			return data;
		}

		head->previous->previous->next = head;

		head->previous = head->previous->previous;

		delete node;

		return data;
	}

	// Remove and return a node at the given index
	DataType erase_at(int index)
	{
		list_node<DataType>* node = at(index);

		if (node == nullptr)
		{
			return DataType();
		}

		DataType data = node->data;

		erase(node);

		return data;
	}

	// Removes all of the given nodes that match with the data and return the total number of nodes erased
	int erase_all(DataType data)
	{
		int total = 0;

		list_node<DataType>* current = head;

		for (int i = 0; i < node_size; i++)
		{
			if (current == nullptr)
			{
				break;
			}

			if (current->data == data)
			{
				erase(current);

				total++;

				i--;
			}

			current = current->next;
		}

		return total;
	}

	// Clears the linked list's data
	int clear()
	{
		deallocate();

		int total = node_size;

		head = nullptr;

		node_size = 0;

		return total;
	}


	// NODE OPERATIONS

	// Replaces the first of the found data with the given data and return the index
	int replace(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = index_of(replaced_data);

		// Check if the data was not found
		if (index == -1)
		{
			return index;
		}

		list_node<DataType>* node = at(index);

		// Replace the data at the index
		node->data = new_data;

		return index;
	}

	// Replaces the last of the found data with the given data and return the index
	int replace_last(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = last_index_of(replaced_data);

		list_node<DataType>* node = at(index);

		// Check if the data was not found
		if (index == -1)
		{
			return index;
		}

		// Replace the data at the index
		node->data = new_data;

		return index;
	}

	// Replaces all of the found data with the given data and returns the total number of replacements
	int replace_all(DataType replaced_data, DataType new_data)
	{
		int total = 0;

		list_node<DataType>* current = head;

		for (int i = 0; i < node_size; i++)
		{
			if (current == nullptr)
			{
				break;
			}

			if (current->data == replaced_data)
			{
				current->data = new_data;

				total++;
			}

			current = current->next;
		}

		return total;
	}

	// Replaces the node with the given node
	list<DataType>& replace(list_node<DataType>* replaced_node, list_node<DataType>* new_node)
	{
		replaced_node->previous->next = new_node;

		replaced_node->next->previous = new_node;

		new_node->previous = replaced_node->previous;

		new_node->next = replaced_node->next;

		if (replaced_node == head)
		{
			head = new_node;
		}

		return *this;
	}

	// Replaces the node's data at the given index with the given data, returns the replaced data
	list_node<DataType>* set(int index, DataType new_data)
	{
		// Replace the data at the index
		list_node<DataType>* node = at(index);

		node->data = new_data;

		return node;
	}

	// Replaces the node's data at the given index with the given data, returns the replaced data
	list_node<DataType>* set(int index, list_node<DataType>* new_node)
	{
		// Replace the data at the index
		list_node<DataType>* node = at(index);

		replace(node, new_node);

		return node;
	}

	// Swaps two nodes' values
	list<DataType>& swap(list_node<DataType>* node1, list_node<DataType>* node2)
	{
		if (node1 == node2)
		{
			return *this;
		}

		DataType data = node1->data;

		node1->data = node2->data;

		node2->data = data;

		return *this;
	}

	// Swaps two nodes' values at two given indicies
	list<DataType>& swap(int index1, int index2)
	{
		// Check if the indicies are the same
		if (index1 == index2)
		{
			return *this;
		}

		return swap(at(index1), at(index2));
	}

	// Returns the node at the given index
	list_node<DataType>* operator[](int index)
	{
		return at(index);
	}


	// LINKED LIST OPERATIONS

	// Assigns the list's nodes from another list's nodes
	list<DataType>& assign(list<DataType> new_data)
	{
		deallocate();

		if (new_data.node_size == 0)
		{
			head = nullptr;

			node_size = 0;

			return *this;
		}

		head = new list_node<DataType>(new_data.head->data);

		node_size = new_data.node_size;

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			DataType* array = new_data.to_new_array();

			list_node<DataType>* node = head;

			for (int i = 1; i < node_size; i++)
			{
				list_node<DataType>* new_node = new list_node<DataType>(array[i]);

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;

			delete[] array;

			array = nullptr;
		}

		return *this;
	}

	// Returns a copy of the list's data
	list<DataType> copy()
	{
		list<DataType> new_list = list<DataType>(this);

		return new_list;
	}

	// Reverse the nodes
	list<DataType>& reverse()
	{
		// Check length
		if (node_size <= 1)
		{
			return *this;
		}

		// Loop through each element and swap it with the element across the end
		for (int i = 0; i < node_size / 2; i++)
		{
			swap(i, node_size - i - 1);
		}

		return *this;
	}

	// Shifts the nodes right
	list<DataType>& shift_right(int number_of_shifts)
	{
		if (number_of_shifts < 0)
		{
			return shift_left(-number_of_shifts);
		}

		number_of_shifts %= node_size;

		for (int i = 0; i < number_of_shifts; i++)
		{
			head = head->previous;
		}

		return *this;
	}

	// Shifts the nodes left
	list<DataType>& shift_left(int number_of_shifts)
	{
		if (number_of_shifts < 0)
		{
			return shift_right(-number_of_shifts);
		}

		number_of_shifts %= node_size;

		for (int i = 0; i < number_of_shifts; i++)
		{
			head = head->next;
		}

		return *this;
	}

	// Bubble sorts the nodes of the linked list relative to the given sort order
	list<DataType>& sort(SORT_TYPE* sort_order)
	{
		// Check length
		if (node_size <= 1)
		{
			return *this;
		}

		// Place the list elements in the sorted order
		for (int i = 0; i < node_size - 1; i++)
		{
			for (int j = 0; j < node_size - i - 1; j++)
			{
				if (sort_order[j] > sort_order[j + 1])
				{
					// Swap the two list elements
					swap(j, j + 1);

					// Swap the two sorting elements
					SORT_TYPE temp_data = sort_order[j];

					sort_order[j] = sort_order[j + 1];
					sort_order[j + 1] = temp_data;
				}
			}
		}

		return *this;
	}

	// Bubble sorts the nodes of the linked list relative to the given sort order
	list<DataType>& sort(SORT_TYPE array ...)
	{
		// Check length
		if (node_size <= 1)
		{
			return *this;
		}

		va_list _va_list;

		va_start(_va_list, node_size);

		SORT_TYPE* argv = new SORT_TYPE[node_size];

		for (int i = 0; i < node_size; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, SORT_TYPE);
		}

		va_end(_va_list);

		// Place the list elements in the sorted order
		for (int i = 0; i < node_size - 1; i++)
		{
			for (int j = 0; j < node_size - i - 1; j++)
			{
				if (argv[j] > argv[j + 1])
				{
					// Swap the two list elements
					swap(j, j + 1);

					// Swap the two sorting elements
					SORT_TYPE temp_data = argv[j];

					argv[j] = argv[j + 1];
					argv[j + 1] = temp_data;
				}
			}
		}

		delete[] argv;

		argv = nullptr;

		return *this;
	}

	// Bubble sorts the nodes of the linked list relative to the given sort order
	list<DataType>& sort(std::vector<SORT_TYPE> sort_order)
	{
		SORT_TYPE* order = new SORT_TYPE[node_size];

		for (int i = 0; i < node_size; i++)
		{
			order[i] = sort_order[i];
		}

		sort(order);

		delete[] order;

		order = nullptr;

		return *this;
	}


	// TO STRING

	// Converts the nodes of the linked list into a string
	std::string to_string()
	{
		if (node_size == 0)
		{
			return "{ }";
		}

		DataType* data = to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < node_size; i++)
		{
			log += (std::to_string(data[i]) + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		delete[] data;

		data = nullptr;

		return log;
	}
};

// Forward declaration of list_node
template<typename DataType> class ListNode;

// Class that stores data and connections to the previous and next nodes in a doubly linked list.
template<typename DataType> class ListNode
{
public:

	// LINKED LIST NODE VARIABLES

	// A link to the previous node
	ListNode<DataType>* previous = nullptr;

	// This node's data
	DataType data = DataType();

	// A link to the next node
	ListNode<DataType>* next = nullptr;


	// LINKED LIST NODE CONSTRUCTOR

	// Default constructor
	ListNode(ListNode<DataType>* previous = nullptr, DataType data = DataType(), ListNode<DataType>* next = nullptr)
	{
		this->previous = previous;

		this->data = data;

		this->next = next;
	}

	// Default constructor
	ListNode(DataType data, ListNode<DataType>* previous = nullptr, ListNode<DataType>* next = nullptr)
	{
		this->data = data;

		this->previous = previous;

		this->next = next;
	}
};

// Class used to store a series of nodes with data in a circular doubly linked list.
template<typename DataType> class List
{
private:

	// LINKED LIST VARIABLES

	// The head (starting) node of the linked list
	ListNode<DataType>* head = nullptr;

	// The current number of nodes in the linked list
	int nodeSize = 0;

	// Deallocates each of the linked list's node's memory
	void Deallocate()
	{
		ListNode<DataType>* node = head;

		for (int i = 0; i < nodeSize; i++)
		{
			ListNode<DataType>* next_node = node->next;

			delete node;

			node = next_node;
		}
	}

public:

	// TO ARRAY AND VECTOR

	// Returns an array of the current linked list (MUST BE DEALLOCATED)
	DataType* ToNewArray()
	{
		if (nodeSize == 0)
		{
			return nullptr;
		}

		// Copy the linked list into an array
		DataType* new_array = new DataType[nodeSize];

		// Set the current nodes
		ListNode<DataType>* node = head;

		// Loop through each node and add it to the array
		for (int i = 0; i < nodeSize; i++)
		{
			new_array[i] = node->data;

			node = node->next;
		}

		return new_array;
	}

	// Returns a vector of the current linked list
	std::vector<DataType> ToVector()
	{
		if (nodeSize == 0)
		{
			return std::vector<DataType>();
		}

		// Copy the linked list into an list
		std::vector<DataType> new_list = std::vector<DataType>();

		// Set the current nodes
		ListNode<DataType>* node = head;

		// Loop through each node and add it to the array
		for (int i = 0; i < nodeSize; i++)
		{
			new_list.push_back(node->data);

			node = node->next;
		}

		return new_list;
	}


	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	List()
	{
		head = nullptr;

		nodeSize = 0;
	}

	// Copy constructor
	List(const List<DataType>& copied_list)
	{
		if (copied_list.nodeSize == 0)
		{
			head = nullptr;

			nodeSize = 0;

			return;
		}

		head = new ListNode<DataType>(copied_list.head->data);

		nodeSize = copied_list.nodeSize;

		if (nodeSize == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			DataType* array = copied_list.ToNewArray();

			ListNode<DataType>* node = head;

			for (int i = 1; i < nodeSize; i++)
			{
				ListNode<DataType>* new_node = new ListNode<DataType>(array[i]);

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;

			delete[] array;

			array = nullptr;
		}
	}

	// Move constructor
	List(List<DataType>&& moved_list) noexcept
	{
		head = moved_list.head;

		moved_list.head = nullptr;

		nodeSize = moved_list.nodeSize;

		moved_list.nodeSize = 0;
	}

	// Data constructor
	List(DataType data)
	{
		head = new ListNode<DataType>(data);

		head->previous = head;

		head->next = head;

		nodeSize = 1;
	}

	// Array constructor
	List(int array_size, DataType* array)
	{
		if (array_size == 0)
		{
			head = nullptr;

			nodeSize = 0;

			return;
		}

		head = new ListNode<DataType>(array[0]);

		nodeSize = array_size;

		if (nodeSize == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			ListNode<DataType>* node = head;

			for (int i = 1; i < array_size; i++)
			{
				ListNode<DataType>* new_node = new ListNode<DataType>(array[i]);

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;
		}
	}

	// Array constructor
	List(int argc, DataType array ...)
	{
		if (argc == 0)
		{
			head = nullptr;

			nodeSize = 0;

			return;
		}

		va_list _va_list;

		va_start(_va_list, argc);

		DataType* argv = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, DataType);
		}

		va_end(_va_list);

		head = new ListNode<DataType>(argv[0]);

		nodeSize = argc;

		if (nodeSize == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			ListNode<DataType>* node = head;

			for (int i = 1; i < argc; i++)
			{
				ListNode<DataType>* new_node = new ListNode<DataType>(argv[i]);

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;
		}

		delete[] argv;

		argv = nullptr;
	}

	// Vector constructor
	List(std::vector<DataType> vector)
	{
		if (vector.size() == 0)
		{
			head = nullptr;

			nodeSize = 0;

			return;
		}

		head = new ListNode<DataType>(vector[0]);

		nodeSize = vector.size();

		if (nodeSize == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			ListNode<DataType>* node = head;

			for (int i = 1; i < vector.size(); i++)
			{
				ListNode<DataType>* new_node = new ListNode<DataType>(vector[i]);

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;
		}
	}

	// List constructor
	List(std::initializer_list<DataType> list)
	{
		if (list.size() == 0)
		{
			head = nullptr;

			nodeSize = 0;

			return;
		}

		head = new ListNode<DataType>(*list.begin());

		nodeSize = list.size();

		if (nodeSize == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			ListNode<DataType>* node = head;

			for (int i = 1; i < list.size(); i++)
			{
				ListNode<DataType>* new_node = new ListNode<DataType>(*(list.begin() + i));

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;
		}
	}

	// Node constructor
	List(ListNode<DataType>* node)
	{
		head = node;

		head->previous = head;

		head->next = head;

		nodeSize = 1;
	}

	// Array constructor
	List(int array_size, ListNode<DataType>** array)
	{
		if (array_size == 0)
		{
			head = nullptr;

			nodeSize = 0;

			return;
		}

		head = array[0];

		nodeSize = array_size;

		if (nodeSize == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			ListNode<DataType>* node = head;

			for (int i = 1; i < array_size; i++)
			{
				node->next = array[i];

				array[i]->previous = node;

				node = array[i];
			}

			node->next = head;

			head->previous = node;
		}
	}

	// Array constructor
	List(int argc, ListNode<DataType>* array ...)
	{
		if (argc == 0)
		{
			head = nullptr;

			nodeSize = 0;

			return;
		}

		va_list _va_list;

		va_start(_va_list, argc);

		DataType* argv = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, DataType);
		}

		va_end(_va_list);

		head = argv[0];

		nodeSize = argc;

		if (nodeSize == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			ListNode<DataType>* node = head;

			for (int i = 1; i < argc; i++)
			{
				node->next = argv[i];

				argv[i]->previous = node;

				node = argv[i];
			}

			node->next = head;

			head->previous = node;
		}

		delete[] argv;

		argv = nullptr;
	}

	// Vector constructor
	List(std::vector<ListNode<DataType>*> vector)
	{
		if (vector.size() == 0)
		{
			head = nullptr;

			nodeSize = 0;

			return;
		}

		head = vector[0];

		nodeSize = vector.size();

		if (nodeSize == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			ListNode<DataType>* node = head;

			for (int i = 1; i < vector.size(); i++)
			{
				node->next = vector[i];

				vector[i]->previous = node;

				node = vector[i];
			}

			node->next = head;

			head->previous = node;
		}
	}

	// List constructor
	List(std::initializer_list<ListNode<DataType>*> list)
	{
		if (list.size() == 0)
		{
			head = nullptr;

			nodeSize = 0;

			return;
		}

		head = *list.begin();

		nodeSize = list.size();

		if (nodeSize == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			ListNode<DataType>* node = head;

			for (int i = 1; i < list.size(); i++)
			{
				node->next = (*(list.begin() + i));

				(*(list.begin() + i))->previous = node;

				node = (*(list.begin() + i));
			}

			node->next = head;

			head->previous = node;
		}
	}

	// Destructor
	virtual ~List()
	{
		Deallocate();
	}


	// OPERATORS

	// Copy assignment operator
	List<DataType>& operator=(const List<DataType>& copied_list)
	{
		Deallocate();

		if (copied_list.nodeSize == 0)
		{
			head = nullptr;

			nodeSize = 0;

			return *this;
		}

		head = new ListNode<DataType>(copied_list.head->data);

		nodeSize = copied_list.nodeSize;

		if (nodeSize == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			DataType* array = copied_list.ToNewArray();

			ListNode<DataType>* node = head;

			for (int i = 1; i < nodeSize; i++)
			{
				ListNode<DataType>* new_node = new ListNode<DataType>(array[i]);

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;

			delete[] array;

			array = nullptr;
		}

		return *this;
	}

	// Move assignment operator
	List<DataType>& operator=(List<DataType>&& moved_list) noexcept
	{
		Deallocate();

		head = moved_list.head;

		moved_list.head = nullptr;

		nodeSize = moved_list.nodeSize;

		moved_list.nodeSize = 0;

		return *this;
	}


	// LINKED LIST EQUALITY

	// Check if another linked list is equal to the linked list
	bool Equals(List<DataType> compared_list)
	{
		if (nodeSize == 0 || compared_list.nodeSize == 0)
		{
			return false;
		}

		// Check if the sizes are equal
		if (nodeSize != compared_list.nodeSize)
		{
			return false;
		}

		// Set the current nodes
		ListNode<DataType>* node = head;

		ListNode<DataType>* compared_node = compared_list->head;

		// Loop through each node to check if they are not equal
		for (int i = 0; i < nodeSize; i++)
		{
			// Are they not equal
			if (node->data != compared_node->data)
			{
				return false;
			}

			node = node->next;

			compared_node = compared_node->next;
		}

		// The lists are equal
		return true;
	}

	// Check if another linked list is equal to the linked list
	bool operator ==(List<DataType> compared_list)
	{
		return Equals(compared_list);
	}

	// Check if another linked list is not equal to the linked list
	bool operator !=(List<DataType> compared_list)
	{
		return !Equals(compared_list);
	}


	// SIZE

	// Return the current number of nodes of the linked list
	int Size()
	{
		return nodeSize;
	}

	// Return whether the linked list is empty
	bool Empty()
	{
		return nodeSize == 0;
	}


	// NODE AND DATA ACCESS

	// Returns the node at the given index
	ListNode<DataType>* At(int index)
	{
		if (index < 0)
		{
			index = nodeSize + index;
		}

		index %= nodeSize;

		ListNode<DataType>* node = head;

		int count = nodeSize / 2 - 1;

		if (index <= count)
		{
			for (int i = 0; i < index; i++)
			{
				node = node->next;
			}
		}
		else
		{
			count = nodeSize - index;

			for (int i = 0; i < count; i++)
			{
				node = node->previous;
			}
		}

		return node;
	}

	// Returns the node's data at the given index
	DataType& Data(int index)
	{
		return At(index)->data;
	}

	// Returns the first node in the linked list
	ListNode<DataType>* Begin()
	{
		return head;
	}

	// Returns the last node in the linked list
	ListNode<DataType>* End()
	{
		if (nodeSize == 0)
		{
			return nullptr;
		}

		return head->previous;
	}

	// Returns the node's data in the linked list
	DataType Front()
	{
		return head->data;
	}

	// Returns the last node's data in the linked list
	DataType Back()
	{
		return head->previous->data;
	}


	// LOCATING NODES

	// Finds the first matching node of the given data
	ListNode<DataType>* Find(DataType data)
	{
		if (nodeSize == 0)
		{
			return nullptr;
		}

		ListNode<DataType>* node = head;

		for (int i = 0; i < nodeSize; i++)
		{
			if (node->data == data)
			{
				return node;
			}

			node = node->next;
		}

		return nullptr;
	}

	// Finds the last matching node of the given data
	ListNode<DataType>* FindLast(DataType data)
	{
		if (nodeSize == 0)
		{
			return nullptr;
		}

		ListNode<DataType>* node = head->previous;

		for (int i = nodeSize - 1; i >= 0; i++)
		{
			if (node->data == data)
			{
				return node;
			}

			node = node->previous;
		}

		return nullptr;
	}

	// Returns the index of the given node, or -1 if nothing matched
	int IndexOf(DataType data)
	{
		if (nodeSize == 0)
		{
			return -1;
		}

		ListNode<DataType>* node = head;

		for (int i = 0; i < nodeSize; i++)
		{
			if (node->data == data)
			{
				return i;
			}

			node = node->next;
		}

		return -1;
	}

	// Returns the index of the given node starting from the back, or -1 if nothing matched
	int LastIndexOf(DataType data)
	{
		if (nodeSize == 0)
		{
			return -1;
		}

		ListNode<DataType>* node = head->previous;

		for (int i = nodeSize - 1; i >= 0; i++)
		{
			if (node->data == data)
			{
				return i;
			}

			node = node->previous;
		}

		return -1;
	}

	// Returns whether the linked list contains at least one of the elements
	bool Contains(DataType contained_data)
	{
		return Find(contained_data) != nullptr;
	}

	// Returns whether the linked list contains at least one of the elements, starting from the back
	bool ContainsLast(DataType contained_data)
	{
		return FindLast(contained_data) != nullptr;
	}

	// Returns the index of the given node, or -1 if nothing matched
	int IndexOf(ListNode<DataType>* data)
	{
		if (nodeSize == 0)
		{
			return -1;
		}

		ListNode<DataType>* node = head;

		for (int i = 0; i < nodeSize; i++)
		{
			if (node == data)
			{
				return i;
			}

			node = node->next;
		}

		return -1;
	}

	// Returns the index of the given node starting from the back, or -1 if nothing matched
	int LastIndexOf(ListNode<DataType>* data)
	{
		if (nodeSize == 0)
		{
			return -1;
		}

		ListNode<DataType>* node = head->previous;

		for (int i = nodeSize - 1; i >= 0; i++)
		{
			if (node == data)
			{
				return i;
			}

			node = node->previous;
		}

		return -1;
	}

	// Returns whether the linked list contains the given node
	bool Contains(ListNode<DataType>* node)
	{
		return IndexOf(node) != -1;
	}

	// Returns whether the linked list contains the given node, starting from the back
	bool ContainsLast(ListNode<DataType>* node)
	{
		return LastIndexOf(node) != -1;
	}

	// Returns the total number of instances of the given data in the linked list
	int Total(DataType found_data)
	{
		if (nodeSize == 0)
		{
			return 0;
		}

		int count = 0;

		ListNode<DataType>* node = head;

		for (int i = 0; i < nodeSize; i++)
		{
			if (node->data == found_data)
			{
				count++;
			}

			node = node->next;
		}

		return count;
	}


	// ADDING NODES

	// Inserts a new node of the given data at the end of the linked list
	List<DataType>& PushBack(DataType data)
	{
		ListNode<DataType>* new_node = new ListNode<DataType>(data);

		if (nodeSize == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			nodeSize++;

			return *this;
		}

		new_node->previous = head->previous;

		new_node->next = head;

		head->previous->next = new_node;

		head->previous = new_node;

		nodeSize++;

		return *this;
	}

	// Inserts a range of new nodes of the given data at the end of the linked list
	List<DataType>& PushBackRange(int array_size, DataType* array)
	{
		for (int i = 0; i < array_size; i++)
		{
			PushBack(array[i]);
		}

		return *this;
	}

	// Inserts a range of new nodes of the given data at the end of the linked list
	List<DataType>& PushBackRange(int argc, DataType data ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		DataType* argv = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = data;

			data = va_arg(_va_list, DataType);
		}

		va_end(_va_list);

		for (int i = 0; i < argc; i++)
		{
			PushBack(argv[i]);
		}

		delete[] argv;

		argv = nullptr;

		return *this;
	}

	// Inserts a new node of the given data at the front of the linked list
	List<DataType>& Push(DataType data)
	{
		ListNode<DataType>* new_node = new ListNode<DataType>(data);

		if (nodeSize == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			nodeSize++;

			return *this;
		}

		new_node->previous = head->previous;

		new_node->next = head;

		head->previous->next = new_node;

		head->previous = new_node;

		head = new_node;

		nodeSize++;

		return *this;
	}

	// Inserts a range of new nodes of the given data at the front of the linked list
	List<DataType>& PushRange(int array_size, DataType* array)
	{
		for (int i = 0; i < array_size; i++)
		{
			Push(array[i]);
		}

		return *this;
	}

	// Inserts a range of new nodes of the given data at the front of the linked list
	List<DataType>& PushRange(int argc, DataType array ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		DataType* argv = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, DataType);
		}

		va_end(_va_list);

		for (int i = 0; i < argc; i++)
		{
			Push(argv[i]);
		}

		delete[] argv;

		argv = nullptr;

		return *this;
	}

	// Inserts a new node of the given data before the given node
	List<DataType>& PushBefore(ListNode<DataType>* node, DataType data)
	{
		ListNode<DataType>* new_node = new ListNode<DataType>(data);

		if (nodeSize == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			nodeSize++;

			return *this;
		}

		new_node->previous = node->previous;

		new_node->next = node;

		node->previous->next = new_node;

		node->previous = new_node;

		nodeSize++;

		return *this;
	}

	// Inserts a new node of the given data after the given node
	List<DataType>& PushAfter(ListNode<DataType>* node, DataType data)
	{
		ListNode<DataType>* new_node = new ListNode<DataType>(data);

		if (nodeSize == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			nodeSize++;

			return *this;
		}

		new_node->previous = node;

		new_node->next = node->next;

		node->next->previous = new_node;

		node->next = new_node;

		nodeSize++;

		return *this;
	}

	// Adds a new node in the linked list at a given index
	List<DataType>& Insert(int index, DataType new_data)
	{
		return PushBefore(At(index), new_data);
	}

	// Inserts a new node of the given data at the end of the linked list
	List<DataType>& PushBack(ListNode<DataType>* new_node)
	{
		if (nodeSize == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			nodeSize++;

			return *this;
		}

		new_node->previous = head->previous;

		new_node->next = head;

		head->previous->next = new_node;

		head->previous = new_node;

		nodeSize++;

		return *this;
	}

	// Inserts a range of new nodes of the given data at the end of the linked list
	List<DataType>& PushBackRange(int array_size, ListNode<DataType>* array)
	{
		for (int i = 0; i < array_size; i++)
		{
			Push(array[i]);
		}

		return *this;
	}

	// Inserts a range of new nodes of the given data at the end of the linked list
	List<DataType>& PushBackRange(int argc, ListNode<DataType> array ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		ListNode<DataType>* argv = new ListNode<DataType>[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, ListNode<DataType>);
		}

		va_end(_va_list);

		for (int i = 0; i < argc; i++)
		{
			PushBack(argv[i]);
		}

		delete[] argv;

		argv = nullptr;

		return *this;
	}

	// Inserts a new node of the given data at the front of the linked list
	List<DataType>& Push(ListNode<DataType>* new_node)
	{
		if (nodeSize == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			nodeSize++;

			return *this;
		}

		new_node->previous = head->previous;

		new_node->next = head;

		head->previous->next = new_node;

		head->previous = new_node;

		head = new_node;

		nodeSize++;

		return *this;
	}

	// Inserts a range of new nodes of the given data at the front of the linked list
	List<DataType>& PushRange(int array_size, ListNode<DataType>* nodes)
	{
		for (int i = 0; i < array_size; i++)
		{
			Push(nodes[i]);
		}

		return *this;
	}

	// Inserts a range of new nodes of the given data at the front of the linked list
	List<DataType>& PushRange(int argc, ListNode<DataType> array ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		ListNode<DataType>* argv = new ListNode<DataType>[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, ListNode<DataType>);
		}

		va_end(_va_list);

		for (int i = 0; i < argc; i++)
		{
			Push(argv[i]);
		}

		delete[] argv;

		argv = nullptr;

		return *this;
	}

	// Inserts a new node of the given data before the given node
	List<DataType>& PushBefore(ListNode<DataType>* node, ListNode<DataType>* new_node)
	{
		if (nodeSize == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			nodeSize++;

			return *this;
		}

		new_node->previous = node->previous;

		new_node->next = node;

		node->previous->next = new_node;

		node->previous = new_node;

		nodeSize++;

		return *this;
	}

	// Inserts a new node of the given data after the given node
	List<DataType>& PushAfter(ListNode<DataType>* node, ListNode<DataType>* new_node)
	{
		if (nodeSize == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			nodeSize++;

			return *this;
		}

		new_node->previous = node;

		new_node->next = node->next;

		node->next->previous = new_node;

		node->next = new_node;

		nodeSize++;

		return *this;
	}

	// Adds a new node in the linked list at a given index
	List<DataType>& Insert(int index, ListNode<DataType>* new_node)
	{
		return PushBefore(At(index), new_node);
	}


	// REMOVING NODES

	// Removes a node from its connected nodes and deallocates it
	List<DataType>& Erase(ListNode<DataType>* node)
	{
		nodeSize--;

		if (nodeSize <= 0)
		{
			delete node;

			node = nullptr;

			nodeSize = 0;

			head = nullptr;

			return *this;
		}

		node->previous->next = node->next;

		node->next->previous = node->previous;

		if (node == head)
		{
			head = head->next;
		}

		delete node;

		node = nullptr;

		return *this;
	}

	// Remove and return the first node of the given data
	List<DataType>& Erase(DataType data)
	{
		ListNode<DataType>* node = find(data);

		if (node == nullptr)
		{
			return *this;
		}

		Erase(node);

		return *this;
	}

	// Remove the last node of the given data
	List<DataType>& EraseLast(DataType data)
	{
		ListNode<DataType>* node = FindLast(data);

		if (node == nullptr)
		{
			return *this;
		}

		Erase(node);

		return *this;
	}

	// Remove and return the first node from its connected nodes in the linked list
	DataType EraseFirst()
	{
		if (head == nullptr)
		{
			return DataType();
		}

		ListNode<DataType>* node = head;

		DataType data = node->data;

		nodeSize--;

		if (nodeSize <= 0)
		{
			delete node;

			nodeSize = 0;

			head = nullptr;

			return data;
		}

		head->previous->next = head->next;

		head->next->previous = head->previous;

		head = head->next;

		delete node;

		return data;
	}

	// Remove and return the last node from its connected nodes in the linked list
	DataType EraseLast()
	{
		if (head == nullptr)
		{
			return DataType();
		}

		ListNode<DataType>* node = head->previous;

		DataType data = node->data;

		nodeSize--;

		if (nodeSize <= 0)
		{
			delete node;

			nodeSize = 0;

			head = nullptr;

			return data;
		}

		head->previous->previous->next = head;

		head->previous = head->previous->previous;

		delete node;

		return data;
	}

	// Remove and return a node at the given index
	DataType EraseAt(int index)
	{
		ListNode<DataType>* node = At(index);

		if (node == nullptr)
		{
			return DataType();
		}

		DataType data = node->data;

		Erase(node);

		return data;
	}

	// Removes all of the given nodes that match with the data and return the total number of nodes erased
	int EraseAll(DataType data)
	{
		int total = 0;

		ListNode<DataType>* current = head;

		for (int i = 0; i < nodeSize; i++)
		{
			if (current == nullptr)
			{
				break;
			}

			if (current->data == data)
			{
				Erase(current);

				total++;

				i--;
			}

			current = current->next;
		}

		return total;
	}

	// Clears the linked list's data
	int Clear()
	{
		Deallocate();

		int total = nodeSize;

		head = nullptr;

		nodeSize = 0;

		return total;
	}


	// NODE OPERATIONS

	// Replaces the first of the found data with the given data and return the index
	int Replace(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = IndexOf(replaced_data);

		// Check if the data was not found
		if (index == -1)
		{
			return index;
		}

		ListNode<DataType>* node = At(index);

		// Replace the data at the index
		node->data = new_data;

		return index;
	}

	// Replaces the last of the found data with the given data and return the index
	int ReplaceLast(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = LastIndexOf(replaced_data);

		ListNode<DataType>* node = At(index);

		// Check if the data was not found
		if (index == -1)
		{
			return index;
		}

		// Replace the data at the index
		node->data = new_data;

		return index;
	}

	// Replaces all of the found data with the given data and returns the total number of replacements
	int ReplaceAll(DataType replaced_data, DataType new_data)
	{
		int total = 0;

		ListNode<DataType>* current = head;

		for (int i = 0; i < nodeSize; i++)
		{
			if (current == nullptr)
			{
				break;
			}

			if (current->data == replaced_data)
			{
				current->data = new_data;

				total++;
			}

			current = current->next;
		}

		return total;
	}

	// Replaces the node with the given node
	List<DataType>& Replace(ListNode<DataType>* replaced_node, ListNode<DataType>* new_node)
	{
		replaced_node->previous->next = new_node;

		replaced_node->next->previous = new_node;

		new_node->previous = replaced_node->previous;

		new_node->next = replaced_node->next;

		if (replaced_node == head)
		{
			head = new_node;
		}

		return *this;
	}

	// Replaces the node's data at the given index with the given data, returns the replaced data
	ListNode<DataType>* Set(int index, DataType new_data)
	{
		// Replace the data at the index
		ListNode<DataType>* node = At(index);

		node->data = new_data;

		return node;
	}

	// Replaces the node's data at the given index with the given data, returns the replaced data
	ListNode<DataType>* Set(int index, ListNode<DataType>* new_node)
	{
		// Replace the data at the index
		ListNode<DataType>* node = At(index);

		Replace(node, new_node);

		return node;
	}

	// Swaps two nodes' values
	List<DataType>& Swap(ListNode<DataType>* node1, ListNode<DataType>* node2)
	{
		if (node1 == node2)
		{
			return *this;
		}

		DataType data = node1->data;

		node1->data = node2->data;

		node2->data = data;

		return *this;
	}

	// Swaps two nodes' values at two given indicies
	List<DataType>& Swap(int index1, int index2)
	{
		// Check if the indicies are the same
		if (index1 == index2)
		{
			return *this;
		}

		return Swap(At(index1), At(index2));
	}

	// Returns the node at the given index
	ListNode<DataType>* operator[](int index)
	{
		return At(index);
	}


	// LINKED LIST OPERATIONS

	// Assigns the list's nodes from another list's nodes
	List<DataType>& assign(List<DataType> new_data)
	{
		Deallocate();

		if (new_data.nodeSize == 0)
		{
			head = nullptr;

			nodeSize = 0;

			return *this;
		}

		head = new ListNode<DataType>(new_data.head->data);

		nodeSize = new_data.nodeSize;

		if (nodeSize == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			DataType* array = new_data.ToNewArray();

			ListNode<DataType>* node = head;

			for (int i = 1; i < nodeSize; i++)
			{
				ListNode<DataType>* new_node = new ListNode<DataType>(array[i]);

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;

			delete[] array;

			array = nullptr;
		}

		return *this;
	}

	// Returns a copy of the list's data
	List<DataType> Copy()
	{
		List<DataType> new_list = list<DataType>(this);

		return new_list;
	}

	// Reverse the nodes
	List<DataType>& Reverse()
	{
		// Check length
		if (nodeSize <= 1)
		{
			return *this;
		}

		// Loop through each element and swap it with the element across the end
		for (int i = 0; i < nodeSize / 2; i++)
		{
			Swap(i, nodeSize - i - 1);
		}

		return *this;
	}

	// Shifts the nodes right
	List<DataType>& ShiftRight(int number_of_shifts)
	{
		if (number_of_shifts < 0)
		{
			return ShiftLeft(-number_of_shifts);
		}

		number_of_shifts %= nodeSize;

		for (int i = 0; i < number_of_shifts; i++)
		{
			head = head->previous;
		}

		return *this;
	}

	// Shifts the nodes left
	List<DataType>& ShiftLeft(int number_of_shifts)
	{
		if (number_of_shifts < 0)
		{
			return ShiftRight(-number_of_shifts);
		}

		number_of_shifts %= nodeSize;

		for (int i = 0; i < number_of_shifts; i++)
		{
			head = head->next;
		}

		return *this;
	}

	// Bubble sorts the nodes of the linked list relative to the given sort order
	List<DataType>& Sort(SORT_TYPE* sort_order)
	{
		// Check length
		if (nodeSize <= 1)
		{
			return *this;
		}

		// Place the list elements in the sorted order
		for (int i = 0; i < nodeSize - 1; i++)
		{
			for (int j = 0; j < nodeSize - i - 1; j++)
			{
				if (sort_order[j] > sort_order[j + 1])
				{
					// Swap the two list elements
					Swap(j, j + 1);

					// Swap the two sorting elements
					SORT_TYPE temp_data = sort_order[j];

					sort_order[j] = sort_order[j + 1];
					sort_order[j + 1] = temp_data;
				}
			}
		}

		return *this;
	}

	// Bubble sorts the nodes of the linked list relative to the given sort order
	List<DataType>& Sort(SORT_TYPE array ...)
	{
		// Check length
		if (nodeSize <= 1)
		{
			return *this;
		}

		va_list _va_list;

		va_start(_va_list, nodeSize);

		SORT_TYPE* argv = new SORT_TYPE[nodeSize];

		for (int i = 0; i < nodeSize; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, SORT_TYPE);
		}

		va_end(_va_list);

		// Place the list elements in the sorted order
		for (int i = 0; i < nodeSize - 1; i++)
		{
			for (int j = 0; j < nodeSize - i - 1; j++)
			{
				if (argv[j] > argv[j + 1])
				{
					// Swap the two list elements
					Swap(j, j + 1);

					// Swap the two sorting elements
					SORT_TYPE temp_data = argv[j];

					argv[j] = argv[j + 1];
					argv[j + 1] = temp_data;
				}
			}
		}

		delete[] argv;

		argv = nullptr;

		return *this;
	}

	// Bubble sorts the nodes of the linked list relative to the given sort order
	List<DataType>& Sort(std::vector<SORT_TYPE> sort_order)
	{
		SORT_TYPE* order = new SORT_TYPE[nodeSize];

		for (int i = 0; i < nodeSize; i++)
		{
			order[i] = sort_order[i];
		}

		Sort(order);

		delete[] order;

		order = nullptr;

		return *this;
	}


	// TO STRING

	// Converts the nodes of the linked list into a string
	std::string ToString()
	{
		if (nodeSize == 0)
		{
			return "{ }";
		}

		DataType* data = ToNewArray();

		std::string log = "{ ";

		for (int i = 0; i < nodeSize; i++)
		{
			log += (std::to_string(data[i]) + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		delete[] data;

		data = nullptr;

		return log;
	}
};
