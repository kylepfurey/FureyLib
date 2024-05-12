
// Linked List Data Types Class
// by Kyle Furey

// REFERENCES: https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.linkedlist-1?view=net-8.0

#pragma once
#include <iostream>
#include <string>
#include <cstdarg>
#include <initializer_list>

// Linked List Class
template <class DataType> class linked_list
{
private:

	// LINK CLASS
	class link
	{
	public:

		// The data of this link
		DataType data = DataType();

		// The next linked data
		link* next = nullptr;
	};

public:


};

// Doubly Linked List Class
template <class DataType> class doubly_linked_list
{
private:

	// LINK CLASS
	class link
	{
	public:

		// The previous linked data
		link* previous = nullptr;

		// The data of this link
		DataType data = DataType();

		// The next linked data
		link* next = nullptr;
	};

public:


};
