
// Linked List Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/list/list/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.linkedlist-1?view=net-8.0

#pragma once
#include <string>
#include <vector>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the class
#include "list.h"

// The default data type used for sorting
#define SORT_TYPE float

// Forward declaration of list
template <typename data_type > class list;

// Forward declaration of list_node
template <typename data_type > class list_node;

// Class that stores data and connections to the previous and next nodes in a doubly linked list.
template <typename data_type > class list_node
{
public:

	// VARIABLES

	// This node's data
	data_type data = data_type();

	// A link to the previous node
	list_node<data_type>* previous = nullptr;

	// A link to the next node
	list_node<data_type>* next = nullptr;


	// CONSTRUCTOR

	// Default constructor
	list_node(data_type data = data_type(), list_node<data_type>* previous = nullptr, list_node<data_type>* next = nullptr)
	{
		this->data = data;

		this->previous = previous;

		this->next = next;
	}
};

// Class used to store a series of nodes with data in a circular doubly linked list.
template <typename data_type > class list
{
private:

	// VARIABLES

	// The head (starting) node of the linked list
	list_node<data_type>* head = nullptr;

	// The current number of nodes in the linked list
	int node_size = 0;

	// Deallocates each of the linked list's node's memory
	void deallocate()
	{
		list_node<data_type>* node = head;

		for (int i = 0; i < node_size; i++)
		{
			list_node<data_type>* next_node = node->next;

			delete node;

			node = next_node;
		}
	}

public:

	// TO ARRAY AND VECTOR

	// Returns an array of the current linked list (MUST BE DEALLOCATED)
	data_type* to_new_array()
	{
		if (node_size == 0)
		{
			return nullptr;
		}

		data_type* new_array = new data_type[node_size];

		list_node<data_type>* node = head;

		for (int i = 0; i < node_size; i++)
		{
			new_array[i] = node->data;

			node = node->next;
		}

		return new_array;
	}

	// Returns a vector of the current linked list
	std::vector<data_type> to_vector()
	{
		if (node_size == 0)
		{
			return std::vector<data_type>();
		}

		std::vector<data_type> new_list = std::vector<data_type>();

		list_node<data_type>* node = head;

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
	list(const list<data_type>& copied_list)
	{
		if (copied_list.node_size == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		head = new list_node<data_type>(copied_list.head->data);

		node_size = copied_list.node_size;

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			data_type* array = copied_list.to_new_array();

			list_node<data_type>* node = head;

			for (int i = 1; i < node_size; i++)
			{
				list_node<data_type>* new_node = new list_node<data_type>(array[i]);

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
	list(list<data_type>&& moved_list) noexcept
	{
		head = moved_list.head;

		moved_list.head = nullptr;

		node_size = moved_list.node_size;

		moved_list.node_size = 0;

		list_node<data_type>* current = head;

		for (int i = 0; i < node_size; i++)
		{
			current->my_list = this;

			current = current->next;
		}
	}

	// Data constructor
	list(data_type data)
	{
		head = new list_node<data_type>(data);

		head->previous = head;

		head->next = head;

		node_size = 1;
	}

	// Array constructor
	list(int array_size, data_type* array)
	{
		if (array_size == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		head = new list_node<data_type>(array[0]);

		node_size = array_size;

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			list_node<data_type>* node = head;

			for (int i = 1; i < array_size; i++)
			{
				list_node<data_type>* new_node = new list_node<data_type>(array[i]);

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;
		}
	}

	// Array constructor
	list(int argc, data_type array ...)
	{
		if (argc == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		va_list _va_list;

		va_start(_va_list, argc);

		data_type* argv = new data_type[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, data_type);
		}

		va_end(_va_list);

		head = new list_node<data_type>(argv[0]);

		node_size = argc;

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			list_node<data_type>* node = head;

			for (int i = 1; i < argc; i++)
			{
				list_node<data_type>* new_node = new list_node<data_type>(argv[i]);

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
	list(std::vector<data_type> vector)
	{
		if (vector.size() == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		head = new list_node<data_type>(vector[0]);

		node_size = vector.size();

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			list_node<data_type>* node = head;

			for (int i = 1; i < vector.size(); i++)
			{
				list_node<data_type>* new_node = new list_node<data_type>(vector[i]);

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;
		}
	}

	// List constructor
	list(std::initializer_list<data_type> list)
	{
		if (list.size() == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		head = new list_node<data_type>(*list.begin());

		node_size = list.size();

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			list_node<data_type>* node = head;

			for (int i = 1; i < list.size(); i++)
			{
				list_node<data_type>* new_node = new list_node<data_type>(*(list.begin() + i));

				node->next = new_node;

				new_node->previous = node;

				node = new_node;
			}

			node->next = head;

			head->previous = node;
		}
	}

	// Node constructor
	list(list_node<data_type>* node)
	{
		node->my_list = this;

		head = node;

		head->previous = head;

		head->next = head;

		node_size = 1;
	}

	// Array constructor
	list(int array_size, list_node<data_type>** array)
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
			list_node<data_type>* node = head;

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
	list(int argc, list_node<data_type>* array ...)
	{
		if (argc == 0)
		{
			head = nullptr;

			node_size = 0;

			return;
		}

		va_list _va_list;

		va_start(_va_list, argc);

		data_type* argv = new data_type[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, data_type);
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
			list_node<data_type>* node = head;

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
	list(std::vector<list_node<data_type>*> vector)
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
			list_node<data_type>* node = head;

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
	list(std::initializer_list<list_node<data_type>*> list)
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
			list_node<data_type>* node = head;

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
	list<data_type>& operator=(const list<data_type>& copied_list)
	{
		deallocate();

		if (copied_list.node_size == 0)
		{
			head = nullptr;

			node_size = 0;

			return *this;
		}

		head = new list_node<data_type>(copied_list.head->data);

		node_size = copied_list.node_size;

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			data_type* array = copied_list.to_new_array();

			list_node<data_type>* node = head;

			for (int i = 1; i < node_size; i++)
			{
				list_node<data_type>* new_node = new list_node<data_type>(array[i]);

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
	list<data_type>& operator=(list<data_type>&& moved_list) noexcept
	{
		deallocate();

		head = moved_list.head;

		moved_list.head = nullptr;

		node_size = moved_list.node_size;

		moved_list.node_size = 0;

		list_node<data_type>* current = head;

		for (int i = 0; i < node_size; i++)
		{
			current->my_list = this;

			current = current->next;
		}

		return *this;
	}


	// EQUALITY

	// Check if another linked list is equal to the linked list
	bool equals(list<data_type>& compared_list)
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
		list_node<data_type>* node = head;

		list_node<data_type>* compared_node = compared_list->head;

		// Loop through each node to check if they are not equal
		for (int i = 0; i < node_size; i++)
		{
			if (node->data != compared_node->data)
			{
				return false;
			}

			node = node->next;

			compared_node = compared_node->next;
		}

		return true;
	}

	// Check if another linked list is equal to the linked list
	bool operator ==(list<data_type>& compared_list)
	{
		return equals(compared_list);
	}

	// Check if another linked list is not equal to the linked list
	bool operator !=(list<data_type>& compared_list)
	{
		return !equals(compared_list);
	}


	// ITERATORS

	// Returns the first node in the linked list
	list_node<data_type>* begin()
	{
		return head;
	}

	// Returns the last node in the linked list
	list_node<data_type>* end()
	{
		if (node_size == 0)
		{
			return nullptr;
		}

		return head->previous;
	}


	// CAPACITY

	// Returns whether the linked list is empty
	bool empty()
	{
		return node_size == 0;
	}

	// Returns the current number of nodes of the linked list
	int size()
	{
		return node_size;
	}


	// ELEMENT ACCESS

	// Returns the node's data in the linked list
	data_type front()
	{
		return head->data;
	}

	// Returns the last node's data in the linked list
	data_type back()
	{
		return head->previous->data;
	}


	// LOCATING ELEMENTS

	// Finds the first matching node of the given data
	list_node<data_type>* find(data_type data)
	{
		if (node_size == 0)
		{
			return nullptr;
		}

		list_node<data_type>* node = head;

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
	list_node<data_type>* find_last(data_type data)
	{
		if (node_size == 0)
		{
			return nullptr;
		}

		list_node<data_type>* node = head->previous;

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

	// Returns whether the linked list contains at least one of the elements
	bool contains(data_type contained_data)
	{
		return find(contained_data) != nullptr;
	}

	// Returns whether the linked list contains the given node
	bool contains(list_node<data_type>* node)
	{
		list_node<data_type>* current = head;

		for (int i = 0; i < node_size; i++)
		{
			if (current == node)
			{
				return true;
			}
			else
			{
				current = current->next;
			}
		}

		return false;
	}

	// Returns the total number of instances of the given data in the linked list
	int count(data_type found_data)
	{
		if (node_size == 0)
		{
			return 0;
		}

		int count = 0;

		list_node<data_type>* node = head;

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

	// Returns the total number of instances of the given data in the linked list
	int count(list_node<data_type>* node)
	{
		return count(node->data);
	}


	// MODIFIERS

	// Assigns the linked list's nodes from another linked list's nodes
	list<data_type>& assign(list<data_type>& new_data)
	{
		deallocate();

		if (new_data.node_size == 0)
		{
			head = nullptr;

			node_size = 0;

			return *this;
		}

		head = new list_node<data_type>(new_data.head->data);

		node_size = new_data.node_size;

		if (node_size == 1)
		{
			head->previous = head;

			head->next = head;
		}
		else
		{
			data_type* array = new_data.to_new_array();

			list_node<data_type>* node = head;

			for (int i = 1; i < node_size; i++)
			{
				list_node<data_type>* new_node = new list_node<data_type>(array[i]);

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

	// Creates and inserts a new node of the given arguments at the front of the linked list
	template<typename ... argument_types> list_node<data_type>* emplace_front(argument_types ... arguments)
	{
		list_node<data_type>* new_node = new list_node<data_type>(data_type(arguments...));

		if (node_size == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return new_node;
		}

		new_node->previous = head->previous;

		new_node->next = head;

		head->previous->next = new_node;

		head->previous = new_node;

		head = new_node;

		node_size++;

		return new_node;
	}

	// Inserts a new node of the given data at the front of the linked list
	list_node<data_type>* push_front(data_type data)
	{
		list_node<data_type>* new_node = new list_node<data_type>(data);

		if (node_size == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return new_node;
		}

		new_node->previous = head->previous;

		new_node->next = head;

		head->previous->next = new_node;

		head->previous = new_node;

		head = new_node;

		node_size++;

		return new_node;
	}

	// Inserts a new node of the given data at the front of the linked list
	list<data_type>& push_front(list_node<data_type>* new_node)
	{
		if (node_size == 0)
		{
			new_node->my_list = this;

			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return *this;
		}

		new_node->my_list = this;

		new_node->previous = head->previous;

		new_node->next = head;

		head->previous->next = new_node;

		head->previous = new_node;

		head = new_node;

		node_size++;

		return *this;
	}

	// Remove and return the first node from its connected nodes in the linked list
	data_type pop_front()
	{
		if (head == nullptr)
		{
			return data_type();
		}

		list_node<data_type>* node = head;

		data_type data = node->data;

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

	// Creates and inserts a new node of the given arguments at the end of the linked list
	template<typename ... argument_types> list_node<data_type>* emplace_back(argument_types ... arguments)
	{
		list_node<data_type>* new_node = new list_node<data_type>(data_type(arguments...));

		if (node_size == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return new_node;
		}

		new_node->previous = head->previous;

		new_node->next = head;

		head->previous->next = new_node;

		head->previous = new_node;

		node_size++;

		return new_node;
	}

	// Inserts a new node of the given data at the end of the linked list
	list_node<data_type>* push_back(data_type data)
	{
		list_node<data_type>* new_node = new list_node<data_type>(data);

		if (node_size == 0)
		{
			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return new_node;
		}

		new_node->previous = head->previous;

		new_node->next = head;

		head->previous->next = new_node;

		head->previous = new_node;

		node_size++;

		return new_node;
	}

	// Inserts a new node of the given data at the end of the linked list
	list<data_type>& push_back(list_node<data_type>* new_node)
	{
		if (node_size == 0)
		{
			new_node->my_list = this;

			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return *this;
		}

		new_node->my_list = this;

		new_node->previous = head->previous;

		new_node->next = head;

		head->previous->next = new_node;

		head->previous = new_node;

		node_size++;

		return *this;
	}

	// Remove and return the last node from its connected nodes in the linked list
	data_type pop_back()
	{
		if (head == nullptr)
		{
			return data_type();
		}

		list_node<data_type>* node = head->previous;

		data_type data = node->data;

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

	// Inserts a new node of the given data before the given node
	list<data_type>& insert(list_node<data_type>* node, data_type data)
	{
		list_node<data_type>* new_node = new list_node<data_type>(data);

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

		if (node == head)
		{
			head = new_node;
		}

		return *this;
	}

	// Inserts a new node of the given data before the given node
	list<data_type>& insert(list_node<data_type>* node, list_node<data_type>* new_node)
	{
		if (node_size == 0)
		{
			new_node->my_list = this;

			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return *this;
		}

		new_node->my_list = this;

		new_node->previous = node->previous;

		new_node->next = node;

		node->previous->next = new_node;

		node->previous = new_node;

		node_size++;

		if (node == head)
		{
			head = new_node;
		}

		return *this;
	}

	// Inserts a new node of the given data after the given node
	list<data_type>& insert_after(list_node<data_type>* node, list_node<data_type>* new_node)
	{
		if (node_size == 0)
		{
			new_node->my_list = this;

			head = new_node;

			head->next = head;

			head->previous = head;

			node_size++;

			return *this;
		}

		new_node->my_list = this;

		new_node->previous = node;

		new_node->next = node->next;

		node->next->previous = new_node;

		node->next = new_node;

		node_size++;

		return *this;
	}

	// Inserts a new node of the given data after the given node
	list<data_type>& insert_after(list_node<data_type>* node, data_type data)
	{
		list_node<data_type>* new_node = new list_node<data_type>(data);

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

	// Remove and return the first node of the given data
	list_node<data_type>* erase(data_type data)
	{
		list_node<data_type>* node = find(data);

		if (node == nullptr)
		{
			return *this;
		}

		erase(node);

		return node;
	}

	// Removes a node from its connected nodes and deallocates it
	list<data_type>& erase(list_node<data_type>* node)
	{
		if (!contains(node))
		{
			return *this;
		}

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

	// Remove and return the last node of the given data
	list_node<data_type>* erase_last(data_type data)
	{
		list_node<data_type>* node = find_last(data);

		if (node == nullptr)
		{
			return *this;
		}

		erase(node);

		return node;
	}

	// Swaps two nodes' values
	list<data_type>& swap(list_node<data_type>* node1, list_node<data_type>* node2)
	{
		if (node1 == node2)
		{
			return *this;
		}

		data_type data = node1->data;

		node1->data = node2->data;

		node2->data = data;

		return *this;
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


	// ELEMENT OPERATIONS

	// Replaces the first of the found data with the given data
	list_node<data_type>* replace(data_type replaced_data, data_type new_data)
	{
		list_node<data_type>* node = find(replaced_data);

		if (node != nullptr)
		{
			node->data = new_data;
		}

		return node;
	}

	// Replaces the node with the given node
	list<data_type>& replace(list_node<data_type>* replaced_node, list_node<data_type>* new_node)
	{
		new_node->my_list = this;

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

	// Replaces the last of the found data with the given data
	list_node<data_type>* replace_last(data_type replaced_data, data_type new_data)
	{
		list_node<data_type>* node = find_last(replaced_data);

		if (node != nullptr)
		{
			node->data = new_data;
		}

		return node;
	}

	// Replaces all of the found data with the given data and returns the total number of replacements
	int replace_all(data_type replaced_data, data_type new_data)
	{
		int total = 0;

		list_node<data_type>* current = head;

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


	// OPERATIONS

	// Transfers another linked list's nodes to this linked list
	list<data_type>& splice(list_node<data_type>* start_node, list<data_type>& new_data)
	{
		for (int i = 0; i < new_data.node_size; i++)
		{
			insert(start_node, new_data.head);

			new_data.pop_front();

			start_node = start_node->next;
		}

		return *this;
	}

	// Removes all of the given nodes that match with the data and return the total number of nodes erased
	int remove(data_type data)
	{
		int total = 0;

		list_node<data_type>* current = head;

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

	// Removes duplicate values from this linked list and return the total number of removals
	int unique()
	{
		int current_count = 0;

		list_node<data_type>* node = head;

		do
		{
			int total = count(node->data) - 1;

			current_count += total;

			for (int i = 0; i < total; i++)
			{
				pop_back(node->data);
			}

			node = node->next;
		} while (node != head);

		return current_count;
	}

	// Merges the given linked list into this linked list
	list<data_type>& merge(list<data_type>& new_data)
	{
		for (int i = 0; i < new_data.node_size; i++)
		{
			push_back(new_data.head);

			new_data.pop_front();
		}

		return *this;
	}

	// Bubble sorts the nodes of the linked list relative to the given sort order
	template<typename sort_type = SORT_TYPE> list<data_type>& sort(sort_type* sort_order)
	{
		if (node_size <= 1)
		{
			return *this;
		}

		for (int i = 0; i < node_size - 1; i++)
		{
			for (int j = 0; j < node_size - i - 1; j++)
			{
				list_node<data_type>* node = head;

				if (sort_order[j] > sort_order[j + 1])
				{
					swap(node, node->next);

					sort_type temp_data = sort_order[j];

					sort_order[j] = sort_order[j + 1];

					sort_order[j + 1] = temp_data;
				}

				node = node->next;
			}
		}

		return *this;
	}

	// Bubble sorts the nodes of the linked list relative to the given sort order
	template<typename sort_type = SORT_TYPE> list<data_type>& sort(sort_type array ...)
	{
		if (node_size <= 1)
		{
			return *this;
		}

		va_list _va_list;

		va_start(_va_list, node_size);

		sort_type* argv = new sort_type[node_size];

		for (int i = 0; i < node_size; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, sort_type);
		}

		va_end(_va_list);

		for (int i = 0; i < node_size - 1; i++)
		{
			for (int j = 0; j < node_size - i - 1; j++)
			{
				if (argv[j] > argv[j + 1])
				{
					swap(j, j + 1);

					sort_type temp_data = argv[j];

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
	template<typename sort_type = SORT_TYPE> list<data_type>& sort(std::vector<sort_type>& sort_order)
	{
		sort_type* order = new sort_type[node_size];

		for (int i = 0; i < node_size; i++)
		{
			order[i] = sort_order[i];
		}

		sort(order);

		delete[] order;

		order = nullptr;

		return *this;
	}

	// Bubble sorts the elements of the vector relative to the given sort order
	template<typename sort_type = SORT_TYPE> list<data_type>& sort(list<sort_type>& sort_order)
	{
		data_type* array = sort_order.to_new_array();

		sort(array);

		delete[] array;

		array = nullptr;

		return *this;
	}

	// Reverse the nodes
	list<data_type>& reverse()
	{
		if (node_size <= 1)
		{
			return *this;
		}

		list_node<data_type> node = head;

		list_node<data_type> end_node = head->previous;

		for (int i = 0; i < node_size / 2; i++)
		{
			swap(node, end_node);

			node = node->next;

			end_node = end_node->previous;
		}

		return *this;
	}

	// Swaps the linked list's nodes from another linked list's nodes
	list<data_type>& swap(list<data_type>& swapped_data)
	{
		list_node<data_type> data = head;

		int current_count = node_size;

		head = swapped_data.head;

		node_size = swapped_data.node_size;

		swapped_data.head = data;

		swapped_data.node_size = current_count;

		list_node<data_type>* current = swapped_data->head;

		for (int i = 0; i < swapped_data.node_size; i++)
		{
			current->my_list = swapped_data;

			current = current->next;
		}

		current = head;

		for (int i = 0; i < node_size; i++)
		{
			current->my_list = this;

			current = current->next;
		}

		return *this;
	}

	// Returns a copy of the list's data
	list<data_type> copy()
	{
		return list<data_type>(*this);
	}

	// Shifts the nodes right
	list<data_type>& shift_right(int number_of_shifts)
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
	list<data_type>& shift_left(int number_of_shifts)
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


	// TO STRING

	// Converts the nodes of the linked list into a string
	std::string to_string()
	{
		if (node_size == 0)
		{
			return "{ }";
		}

		data_type* data = to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < node_size; i++)
		{
			log += (data[i] + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		delete[] data;

		data = nullptr;

		return log;
	}

	// Converts the nodes of the linked list into a string
	std::string to_string(std::string(*to_string_function) (data_type))
	{
		if (node_size == 0)
		{
			return "{ }";
		}

		data_type* data = to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < node_size; i++)
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
