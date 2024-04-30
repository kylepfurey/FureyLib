
// List Data Type Class
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/vector/vector/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=net-8.0

#pragma once
#include <iostream>
#include <string>
#include <initializer_list>

// Include this heading to use the class
#include "List.h"

// Data type used for sorting
#define SORT_TYPE float

// List Class
template <class DataType> class list
{
private:

	// LIST VARIABLES

	// The array of pointers representing the list's data
	DataType* list_data = new DataType[1];

	// The current number of pointers in the array holding data
	int list_size = 0;

	// The current maximum size of the array before needing to expand
	int list_capacity = 1;

	// The number of array expansions
	int list_expansions = 0;

public:

	// REALLOCATE MEMORY

	// Expands the capacity based on how many times it has been expanded
	list<DataType>& reallocate()
	{
		// Advance the number of expansions
		list_expansions++;

		// Duplicate the list
		DataType* temp = new DataType[list_size];

		for (int i = 0; i < list_size; i++)
		{
			temp[i] = list_data[i];
		}

		// Delete the old list's data
		delete[] list_data;

		// Allocate new space for the list
		list_capacity *= 2;

		list_data = new DataType[list_capacity];

		// Place the data back into the list
		for (int i = 0; i < list_size; i++)
		{
			list_data[i] = temp[i];
		}

		delete[] temp;

		return *this;
	}


	// TO ARRAY

	// Returns a pointer to a new array of the current list
	DataType* to_new_array()
	{
		// Copy the list into an array
		DataType* new_array = new DataType[list_size];

		for (int i = 0; i < list_size; i++)
		{
			new_array[i] = list_data[i];
		}

		return new_array;
	}


	// LIST EQUALITY

	// Check if another list is equal to this list
	bool equals(list<DataType> compared_list)
	{
		// Check if the sizes are equal
		if (list_size != compared_list.list_size())
		{
			return false;
		}

		// Loop through each element to check if they are not equal
		for (int i = 0; i < list_size; i++)
		{
			// Are they not equal
			if (list_data[i] != compared_list[i])
			{
				return false;
			}
		}

		// The lists are equal
		return true;
	}

	// Check if another list is equal to this list
	bool operator==(list<DataType> compared_list)
	{
		return equals();
	}

	// Check if another list is not equal to this list
	bool not_equals(list<DataType> compared_list)
	{
		return !equals();
	}

	// Check if another list is not equal to this list
	bool operator!=(list<DataType> compared_list)
	{
		return !equals();
	}


	// ITERATORS

	// Return a pointer to the beginning
	DataType* begin()
	{
		DataType* pointer = &list_data[0];

		return pointer;
	}

	// Return a pointer to the beginning
	DataType* ptr()
	{
		return begin();
	}

	// Return a pointer to the beginning
	DataType* pointer()
	{
		return begin();
	}

	// Returns a pointer to the beginning
	DataType* operator*()
	{
		return begin();
	}

	// Return a pointer to the end
	DataType* end()
	{
		DataType* pointer = &list_data[list_size - 1];

		return pointer;
	}

	// Return a pointer to the end
	DataType* ptr_end()
	{
		return end();
	}

	// Return a pointer to the end
	DataType* pointer_end()
	{
		return end();
	}

	// Return a pointer to the given index
	DataType* ptr(int index)
	{
		DataType* pointer = &list_data[index];

		return pointer;
	}

	// Return a pointer to the given index
	DataType* pointer(int index)
	{
		return ptr(index);
	}


	// CAPACITY

	// Return the current size of the list
	int size()
	{
		return list_size;
	}

	// Return the current size of the list
	int count()
	{
		return list_size;
	}

	// Return the current size of the list
	int length()
	{
		return list_size;
	}

	// Resizes the list's size and removes out of bounds data or expands if necessary
	list<DataType>& resize(int new_size)
	{
		// Check if the new size is identical
		if (list_size == new_size)
		{
			return *this;
		}

		// Duplicate the current list
		DataType* temp = new DataType[list_size];

		for (int i = 0; i < list_size; i++)
		{
			temp[i] = list_data[i];
		}

		// Delete the old list's data
		delete[] list_data;

		// Expand the list if needed
		if (new_size > list_capacity)
		{
			reallocate();
		}

		// Allocate new space for the list
		list_data = new DataType[list_capacity];

		list_size = new_size;

		// Place the data back into the list
		for (int i = 0; i < list_size; i++)
		{
			list_data[i] = temp[i];
		}

		delete[] temp;

		return *this;
	}

	// Return the maximum capacity of the list before expanding
	int capacity()
	{
		return list_capacity;
	}

	// Return the maximum capacity of the list before expanding
	int max_size()
	{
		return capacity();
	}

	// Return whether the list is empty
	bool empty()
	{
		return list_size == 0;
	}

	// Return whether the list is empty
	bool is_empty()
	{
		return empty();
	}

	// Expands the list's capacity enough to hold the given amount (does not reduce the capacity)
	list<DataType>& reserve(int new_capacity)
	{
		// Check if the new capacity is less
		if (new_capacity <= list_capacity)
		{
			return *this;
		}

		// Advance the number of expansions
		list_expansions++;

		// Duplicate the current list
		DataType* temp = new DataType[list_size];

		for (int i = 0; i < list_size; i++)
		{
			temp[i] = list_data[i];
		}

		// Delete the old list's data
		delete[] list_data;

		// Allocate new space for the list
		list_capacity = new_capacity;

		list_data = new DataType[list_capacity];

		// Place the data back into the list
		for (int i = 0; i < list_size; i++)
		{
			list_data[i] = temp[i];
		}

		delete[] temp;

		return *this;
	}

	// Expands the list's capacity enough to hold the given amount (does not reduce the capacity)
	list<DataType>& ensure_capacity(int new_capacity)
	{
		return reserve(new_capacity);
	}

	// Shrinks the capacity to the size
	list<DataType>& shrink_to_fit()
	{
		// Duplicate the current list
		DataType* temp = new DataType[list_size];

		for (int i = 0; i < list_size; i++)
		{
			temp[i] = list_data[i];
		}

		// Delete the old list's data
		delete[] list_data;

		// Allocate new space for the list
		list_capacity = list_size;

		list_data = new DataType[list_capacity];

		// Place the data back into the list
		for (int i = 0; i < list_size; i++)
		{
			list_data[i] = temp[i];
		}

		// Reset the number of resizes
		list_expansions = 0;

		delete[] temp;

		return *this;
	}

	// Shrinks the capacity to the size
	list<DataType>& trim_excess()
	{
		return shrink_to_fit();
	}

	// Shrinks the capacity to the size
	list<DataType>& clean()
	{
		return shrink_to_fit();
	}

	// Return the total number of expansions
	int expansions()
	{
		return list_expansions;
	}

	// Return the total number of expansions
	int reallocations()
	{
		return expansions();
	}

	// Expands the list's capacity by the given amount
	list<DataType>& expand(int number_of_spaces)
	{
		return reserve(list_capacity + number_of_spaces);
	}


	// ELEMENT ACCESS

	// Returns the element at the given index
	DataType& at(int index)
	{
		return list_data[index];
	}

	// Returns the element at the given index
	DataType& get(int index)
	{
		return at(index);
	}

	// Returns the element at the given index
	DataType& operator[](int index)
	{
		return at(index);
	}

	// Returns the first element in the list
	DataType& front()
	{
		return list_data[0];
	}

	// Returns the first element in the list
	DataType& back()
	{
		return list_data[list_size - 1];
	}

	// Return a pointer to the given index
	DataType* data(int index)
	{
		return ptr(index);
	}


	// MODIFIERS

	// Assigns this list's elements and capacity to the elements and capacity of another list
	list<DataType>& assign(list<DataType> new_data)
	{
		// Delete the old list's data
		delete[] list_data;

		// Store the list's size values
		list_size = new_data.size();

		list_capacity = list_size;

		list_expansions = 0;

		// Allocate the space from the new list
		list_data = new DataType[list_capacity];

		// Place the data back into the list
		for (int i = 0; i < list_size; i++)
		{
			list_data[i] = new_data[i];
		}

		return *this;
	}

	// Assigns this list's elements and capacity to the elements and capacity of another list
	list<DataType>& set(list<DataType> new_data)
	{
		return assign(new_data);
	}

	// Assigns this list's elements and capacity to the elements and capacity of another list
	list<DataType>& operator=(list<DataType> new_data)
	{
		return assign(new_data);
	}

	// Adds a new element at the front of the list
	list<DataType>& push(DataType new_data)
	{
		// Expand the list if needed
		if (list_size + 1 > list_capacity)
		{
			reallocate();
		}

		// Increase the list size
		list_size++;

		// Shift list elements forward
		for (int i = list_size - 1; i >= 1; i--)
		{
			list_data[i] = list_data[i - 1];
		}

		// Set the first element to the new data
		list_data[0] = new_data;

		return *this;
	}

	// Adds a new element at the front of the list
	list<DataType>& enqueue(DataType new_data)
	{
		return push(new_data);
	}

	// Adds a new element at the front of the list
	list<DataType>& add_front(DataType new_data)
	{
		return push(new_data);
	}

	// Adds a new element at the end of the list
	list<DataType>& push_back(DataType new_data)
	{
		// Expand the list if needed
		if (list_size + 1 > list_capacity)
		{
			reallocate();
		}

		// Increase the list size
		list_size++;

		// Sets the last element to the new data
		list_data[list_size - 1] = new_data;

		return *this;
	}

	// Adds a new element at the end of the list
	list<DataType>& add(DataType new_data)
	{
		return push_back(new_data);
	}

	// Adds a new element at the end of the list
	list<DataType>& operator+(DataType new_data)
	{
		return push_back(new_data);
	}

	// Remove and return the first element of the list
	DataType pop()
	{
		// Decrease the list size if possible
		if (list_size == 0)
		{
			return list_data[0];
		}

		list_size--;

		// Store the removed data
		DataType new_data = list_data[0];

		// Shift list elements backward
		for (int i = 1; i <= list_size; i++)
		{
			list_data[i - 1] = list_data[i];
		}

		return new_data;
	}

	// Remove and return the first element of the list
	DataType dequeue()
	{
		return pop();
	}

	// Remove and return the last element of the list
	DataType pop_back()
	{
		// Decrease the list size if possible
		if (list_size == 0)
		{
			return list_data[0];
		}

		list_size--;

		return list_data[list_size];
	}

	// Adds a new element in the list at a given index and shift following elements forward
	list<DataType>& insert(int index, DataType new_data)
	{
		// Check for out of bounds
		if (index < 0 || index >= list_size)
		{
			return *this;
		}

		// Expand the list if needed
		if (list_size + 1 > list_capacity)
		{
			reallocate();
		}

		// Increase the list size
		list_size++;

		// Shift elements at and past the new index forward
		for (int i = list_size - 1; i >= index; i--)
		{
			list_data[i] = list_data[i - 1];
		}

		// Replace the starting index with the new data
		list_data[index] = new_data;

		return *this;
	}

	// Removes a element in the list at a given index and shift following elements back
	list<DataType>& erase(int index)
	{
		// Check for out of bounds
		if (index < 0 || index >= list_size)
		{
			return *this;
		}

		// Decrease the list size
		list_size--;

		// Shift elements past the new index backward
		for (int i = index + 1; i <= list_size; i++)
		{
			list_data[i - 1] = list_data[i];
		}

		return *this;
	}

	// Removes a element in the list at a given index and shift following elements back
	list<DataType>& remove_at(int index)
	{
		return erase(index);
	}

	// Swaps two elements at two given indicies
	list<DataType>& swap(int index1, int index2)
	{
		// Check for out of bounds
		if (index1 < 0 || index1 >= list_size || index2 < 0 || index2 >= list_size)
		{
			return *this;
		}

		// Check if the indicies are the same
		if (index1 == index2)
		{
			return *this;
		}

		// Store swapped data
		DataType temp = list_data[index2];

		// Replace the swapped data
		list_data[index2] = list_data[index1];

		// Return the swapped data
		list_data[index1] = temp;

		return *this;
	}

	// Clears the list's data
	list<DataType>& clear()
	{
		// Delete the list's data
		delete[] list_data;

		// Reset list variables
		list_data = new DataType[1];

		list_size = 0;

		list_capacity = 1;

		list_expansions = 0;

		return *this;
	}

	// Adds a new element in the list at a given index and shift following elements forward
	list<DataType>& emplace(int index, DataType& new_data)
	{
		// Check for out of bounds
		if (index < 0 || index >= list_size)
		{
			return *this;
		}

		// Expand the list if needed
		if (list_size + 1 > list_capacity)
		{
			reallocate();
		}

		// Increase the list size
		list_size++;

		// Shift elements at and past the new index forward
		for (int i = list_size - 1; i >= index; i--)
		{
			list_data[i] = list_data[i - 1];
		}

		// Replace the starting index with the new data
		list_data[index] = new_data;

		return *this;
	}

	// Adds a new element at the front of the list
	list<DataType>& emplace(DataType& new_data)
	{
		// Expand the list if needed
		if (list_size + 1 > list_capacity)
		{
			reallocate();
		}

		// Increase the list size
		list_size++;

		// Shift list elements forward
		for (int i = list_size - 1; i >= 1; i--)
		{
			list_data[i] = list_data[i - 1];
		}

		// Set the first element to the new data
		list_data[0] = new_data;

		return *this;
	}

	// Adds a new element at the end of the list
	list<DataType>& emplace_back(DataType& new_data)
	{
		// Expand the list if needed
		if (list_size + 1 > list_capacity)
		{
			reallocate();
		}

		// Increase the list size
		list_size++;

		// Sets the last element to the new data
		list_data[list_size - 1] = new_data;

		return *this;
	}

	// Returns a copy of the list's data
	list<DataType> copy()
	{
		list<DataType> newList = list<DataType>(*this);

		return newList;
	}

	// Returns the first index of the given data in the list, returns -1 if nothing matched
	int find(DataType found_data)
	{
		// Loop through the list for the matching element
		for (int i = 0; i < list_size; i++)
		{
			if (list_data[i] == found_data)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns the first index of the given data in the list, returns -1 if nothing matched
	int index_of(DataType found_data)
	{
		return find(found_data);
	}

	// Returns the last index of the given data in the list, returns -1 if nothing matched
	int find_last(DataType found_data)
	{
		// Loop through the list for the matching element
		for (int i = list_size - 1; i >= 0; i--)
		{
			if (list_data[i] == found_data)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns the last index of the given data in the list, returns -1 if nothing matched
	int last_index_of(DataType found_data)
	{
		return find_last(found_data);
	}

	// Returns the total number of instances of the given data in the list, returns -1 if nothing matched
	int total(DataType found_data)
	{
		// Store the current count
		int count = 0;

		// Loop through the list for matching elements
		for (int i = 0; i < list_size; i++)
		{
			if (list_data[i] == found_data)
			{
				count++;
			}
		}

		return count;
	}

	// Returns whether the list contains at least one of the elements 
	bool contains(DataType contained_data)
	{
		return find(contained_data) != -1;
	}

	// Returns whether the list contains at least one of the elements 
	bool exists(DataType contained_data)
	{
		return contains(contained_data);
	}

	// Removes the first of a given element in the list
	list<DataType>& remove(DataType removed_data)
	{
		return erase(find(removed_data));
	}

	// Removes the last of a given element in the list
	list<DataType>& remove_last(DataType removed_data)
	{
		return erase(find_last(removed_data));
	}

	// Removes the last of a given element in the list
	list<DataType>& operator-(DataType new_data)
	{
		return remove_last(new_data);
	}

	// Removes all of the given element in the list
	list<DataType>& remove_all(DataType removed_data)
	{
		// Get the total number of elements
		int amount = total(removed_data);

		// Remove those elements
		for (int i = 0; i < amount; i++)
		{
			remove(removed_data);
		}

		return *this;
	}

	// Replaces the data at the given index with the given data
	list<DataType>& fill(int index, DataType new_data)
	{
		// Check for out of bounds
		if (index < 0 || index >= list_size)
		{
			return *this;
		}

		// Replace the data at the index
		list_data[index] = new_data;

		return *this;
	}

	// Replaces the data at the given index with the given data
	list<DataType>& overwrite(int index, DataType new_data)
	{
		return fill(index, new_data);
	}

	// Replaces the first of the found data with the given data
	list<DataType>& replace(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = find(replaced_data);

		// Check if the data was not found
		if (index == -1)
		{
			return *this;
		}

		// Replace the data at the index
		list_data[index] = new_data;

		return *this;
	}

	// Replaces the last of the found data with the given data
	list<DataType>& replace_last(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = find_last(replaced_data);

		// Check if the data was not found
		if (index == -1)
		{
			return *this;
		}

		// Replace the data at the index
		list_data[index] = new_data;

		return *this;
	}

	// Replaces all of the found data with the given data
	list<DataType>& replace_all(DataType replaced_data, DataType new_data)
	{
		// Get the total number of elements
		int amount = total(replaced_data);

		// Replace those elements
		for (int i = 0; i < amount; i++)
		{
			replace(replaced_data, new_data);
		}

		return *this;
	}

	// Reverse the list elements
	list<DataType>& reverse()
	{
		// Check length
		if (list_size <= 1)
		{
			return *this;
		}

		// Loop through each element and swap it with the element across the end
		for (int i = 0; i < list_size / 2; i++)
		{
			swap(i, list_size - i - 1);
		}

		return *this;
	}

	// Reverse the list elements
	list<DataType>& operator~()
	{
		return reverse();
	}

	// Shifts the list elements right
	list<DataType>& shift_right(int number_of_shifts)
	{
		// Check length
		if (list_size <= 1)
		{
			return *this;
		}

		// Check if shifting the list is unnecessary
		if (number_of_shifts % list_size == 0)
		{
			return *this;
		}

		// Duplicate the list
		DataType* temp = new DataType[list_size];

		for (int i = 0; i < list_size; i++)
		{
			temp[i] = list_data[i];
		}

		// Delete the old list's data
		delete[] list_data;

		list_data = new DataType[list_capacity];

		// Place the list elements at their shifted location using modulo
		for (int i = 0; i < list_size; i++)
		{
			list_data[i] = temp[((i - number_of_shifts) % list_size + list_size) % list_size];
		}

		delete[] temp;

		return *this;
	}

	// Shifts the list elements right
	list<DataType>& shift(int number_of_shifts)
	{
		return shift_right(number_of_shifts);
	}

	// Shifts the list elements right
	list<DataType>& operator>>(int number_of_shifts)
	{
		return shift_right(number_of_shifts);
	}

	// Shifts the list elements left
	list<DataType>& shift_left(int number_of_shifts)
	{
		return shift_right(-number_of_shifts);
	}

	// Shifts the list elements left
	list<DataType>& operator<<(int number_of_shifts)
	{
		return shift_right(-number_of_shifts);
	}

	// Bubble sorts the elements of the list relative to the given sort order
	list<DataType>& sort(SORT_TYPE sort_order[])
	{
		// Check length
		if (list_size <= 1)
		{
			return *this;
		}

		// Place the list elements in the sorted order
		for (int i = 0; i < list_size - 1; i++)
		{
			for (int j = 0; j < list_size - i - 1; j++)
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

	// Safely bubble sorts the elements of the list relative to the given sort order
	list<DataType>& sort(list<SORT_TYPE> sort_order)
	{
		DataType* new_sort_order = sort_order.to_new_array();

		sort(new_sort_order);

		delete[] new_sort_order;

		return *this;
	}

	// Bubble sorts the elements of the list relative to the given sort order (converts the sort order to the given sort type)
	template<class SortData> list<DataType>& sort(SortData sort_order[])
	{
		SORT_TYPE* new_sort_order = new SORT_TYPE[list_size];

		for (int i = 0; i < list_size; i++)
		{
			new_sort_order[i] = static_cast<SORT_TYPE>(sort_order[i]);
		}

		sort(new_sort_order);

		delete[] new_sort_order;

		return *this;
	}

	// Safely bubble sorts the elements of the list relative to the given sort order (converts the sort order to the given sort type)
	template<class SortData> list<DataType>& sort(list<SortData> sort_order)
	{
		SORT_TYPE* new_sort_order = new SORT_TYPE[list_size];

		for (int i = 0; i < list_size; i++)
		{
			new_sort_order[i] = static_cast<SORT_TYPE>(sort_order[i]);
		}

		sort(new_sort_order);

		delete[] new_sort_order;

		return *this;
	}

	// Prints the elements of the list
	void print()
	{
		for (int i = 0; i < list_size; i++)
		{
			std::cout << i << ". " << list_data[i] << std::endl;
		}
	}

	// Converts the elements of the list into a string
	std::string to_string()
	{
		std::string log = "";

		for (int i = 0; i < list_size; i++)
		{
			log += std::to_string(i) + ". " + std::to_string(list_data[i]) + "\n";
		}

		return log;
	}


	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	list()
	{
		list_data = new DataType[1];

		list_size = 0;

		list_capacity = 1;

		list_expansions = 0;
	}

	// List constructor
	list(const std::initializer_list<DataType> new_list)
	{
		list_size = new_list.size();

		list_capacity = new_list.size();

		list_expansions = 0;

		list_data = new DataType[list_capacity];

		for (int i = 0; i < list_size; i++)
		{
			list_data[i] = *(new_list.begin() + i);
		}
	}

	// Copy constructor
	list(const list<DataType>& copied_list)
	{
		list_size = copied_list.list_size;

		list_capacity = copied_list.list_capacity;

		list_expansions = 0;

		list_data = new DataType[list_capacity];

		for (int i = 0; i < list_size; i++)
		{
			list_data[i] = copied_list.list_data[i];
		}
	}

	// Capacity constructor
	list(int max_capacity)
	{
		list_data = new DataType[max_capacity];

		list_size = 0;

		list_capacity = max_capacity;

		list_expansions = 0;
	}

	// Fill constructor
	list(int size_and_capacity, DataType new_data)
	{
		list_data = new DataType[size_and_capacity];

		for (int i = 0; i < size_and_capacity; i++)
		{
			list_data[i] = new_data;
		}

		list_size = size_and_capacity;

		list_capacity = list_size;

		list_expansions = 0;
	}

	// Array constructor
	list(DataType array[], int array_length)
	{
		list_data = new DataType[array_length];

		for (int i = 0; i < array_length; i++)
		{
			list_data[i] = array[i];
		}

		list_size = array_length;

		list_capacity = list_size;

		list_expansions = 0;
	}

	// Deconstructor
	~list()
	{
		// Delete the list's data
		delete[] list_data;

		list_data = nullptr;
	}
};

// List Class
template <class DataType> class List
{
private:

	// LIST VARIABLES

	// The array of pointers representing the list's data
	DataType* listData = new DataType[1];

	// The current number of pointers in the array holding data
	int listSize = 0;

	// The current maximum size of the array before needing to expand
	int listCapacity = 1;

	// The number of array expansions
	int listExpansions = 0;

public:

	// REALLOCATE MEMORY

	// Expands the capacity based on how many times it has been expanded
	List<DataType>& Reallocate()
	{
		// Advance the number of expansions
		listExpansions++;

		// Duplicate the list
		DataType* temp = new DataType[listSize];

		for (int i = 0; i < listSize; i++)
		{
			temp[i] = listData[i];
		}

		// Delete the old list's data
		delete[] listData;

		// Allocate new space for the list
		listCapacity *= 2;

		listData = new DataType[listCapacity];

		// Place the data back into the list
		for (int i = 0; i < listSize; i++)
		{
			listData[i] = temp[i];
		}

		delete[] temp;

		return *this;
	}


	// TO ARRAY

	// Returns a pointer to a new array of the current list
	DataType* ToNewArray()
	{
		// Copy the list into an array
		DataType* new_array = new DataType[listSize];

		for (int i = 0; i < listSize; i++)
		{
			new_array[i] = listData[i];
		}

		return new_array;
	}


	// LIST EQUALITY

	// Check if another list is equal to this list
	bool Equals(List<DataType> compared_list)
	{
		// Check if the sizes are equal
		if (listSize != compared_list.listSize())
		{
			return false;
		}

		// Loop through each element to check if they are not equal
		for (int i = 0; i < listSize; i++)
		{
			// Are they not equal
			if (listData[i] != compared_list[i])
			{
				return false;
			}
		}

		// The lists are equal
		return true;
	}

	// Check if another list is equal to this list
	bool operator==(List<DataType> compared_list)
	{
		return Equals();
	}

	// Check if another list is not equal to this list
	bool NotEquals(List<DataType> compared_list)
	{
		return !Equals();
	}

	// Check if another list is not equal to this list
	bool operator!=(List<DataType> compared_list)
	{
		return !Equals();
	}


	// ITERATORS

	// Return a pointer to the beginning
	DataType* Begin()
	{
		DataType* pointer = &listData[0];

		return pointer;
	}

	// Return a pointer to the beginning
	DataType* Pointer()
	{
		return Begin();
	}

	// Return a pointer to the beginning
	DataType* Ptr()
	{
		return Begin();
	}

	// Returns a pointer to the beginning
	DataType* operator*()
	{
		return Begin();
	}

	// Return a pointer to the end
	DataType* End()
	{
		DataType* pointer = &listData[listSize - 1];

		return pointer;
	}

	// Return a pointer to the end
	DataType* PointerEnd()
	{
		return End();
	}

	// Return a pointer to the end
	DataType* PtrEnd()
	{
		return End();
	}

	// Return a pointer to the given index
	DataType* Pointer(int index)
	{
		DataType* pointer = &listData[index];

		return pointer;
	}

	// Return a pointer to the given index
	DataType* Ptr(int index)
	{
		return Pointer(index);
	}


	// CAPACITY

	// Return the current size of the list
	int Size()
	{
		return listSize;
	}

	// Return the current size of the list
	int Count()
	{
		return listSize;
	}

	// Return the current size of the list
	int Length()
	{
		return listSize;
	}

	// Resizes the list's size and removes out of bounds data or expands if necessary
	List<DataType>& Resize(int new_size)
	{
		// Check if the new size is identical
		if (listSize == new_size)
		{
			return *this;
		}

		// Duplicate the current list
		DataType* temp = new DataType[listSize];

		for (int i = 0; i < listSize; i++)
		{
			temp[i] = listData[i];
		}

		// Delete the old list's data
		delete[] listData;

		// Expand the list if needed
		if (new_size > listCapacity)
		{
			Reallocate();
		}

		// Allocate new space for the list
		listData = new DataType[listCapacity];

		listSize = new_size;

		// Place the data back into the list
		for (int i = 0; i < listSize; i++)
		{
			listData[i] = temp[i];
		}

		delete[] temp;

		return *this;
	}

	// Return the maximum capacity of the list before expanding
	int Capacity()
	{
		return listCapacity;
	}

	// Return the maximum capacity of the list before expanding
	int MaxSize()
	{
		return Capacity();
	}

	// Return whether the list is empty
	bool Empty()
	{
		return listSize == 0;
	}

	// Return whether the list is empty
	bool IsEmpty()
	{
		return Empty();
	}

	// Expands the list's capacity enough to hold the given amount (does not reduce the capacity)
	List<DataType>& Reserve(int new_capacity)
	{
		// Check if the new capacity is less
		if (new_capacity <= listCapacity)
		{
			return *this;
		}

		// Advance the number of expansions
		listExpansions++;

		// Duplicate the current list
		DataType* temp = new DataType[listSize];

		for (int i = 0; i < listSize; i++)
		{
			temp[i] = listData[i];
		}

		// Delete the old list's data
		delete[] listData;

		// Allocate new space for the list
		listCapacity = new_capacity;

		listData = new DataType[listCapacity];

		// Place the data back into the list
		for (int i = 0; i < listSize; i++)
		{
			listData[i] = temp[i];
		}

		delete[] temp;

		return *this;
	}

	// Expands the list's capacity enough to hold the given amount (does not reduce the capacity)
	List<DataType>& EnsureCapacity(int new_capacity)
	{
		return Reserve(new_capacity);
	}

	// Shrinks the capacity to the size
	List<DataType>& ShrinkToFit()
	{
		// Duplicate the current list
		DataType* temp = new DataType[listSize];

		for (int i = 0; i < listSize; i++)
		{
			temp[i] = listData[i];
		}

		// Delete the old list's data
		delete[] listData;

		// Allocate new space for the list
		listCapacity = listSize;

		listData = new DataType[listCapacity];

		// Place the data back into the list
		for (int i = 0; i < listSize; i++)
		{
			listData[i] = temp[i];
		}

		// Reset the number of resizes
		listExpansions = 0;

		delete[] temp;

		return *this;
	}

	// Shrinks the capacity to the size
	List<DataType>& TrimExcess()
	{
		return ShrinkToFit();
	}

	// Shrinks the capacity to the size
	List<DataType>& Clean()
	{
		return ShrinkToFit();
	}

	// Return the total number of expansions
	int Expansions()
	{
		return listExpansions;
	}

	// Return the total number of expansions
	int Reallocations()
	{
		return Expansions();
	}

	// Expands the list's capacity by the given amount
	List<DataType>& Expand(int number_of_spaces)
	{
		return Reserve(listCapacity + number_of_spaces);
	}


	// ELEMENT ACCESS

	// Returns the element at the given index
	DataType& At(int index)
	{
		return listData[index];
	}

	// Returns the element at the given index
	DataType& Get(int index)
	{
		return At(index);
	}

	// Returns the element at the given index
	DataType& operator[](int index)
	{
		return At(index);
	}

	// Returns the first element in the list
	DataType& Front()
	{
		return listData[0];
	}

	// Returns the first element in the list
	DataType& Back()
	{
		return listData[listSize - 1];
	}

	// Return a pointer to the given index
	DataType* Data(int index)
	{
		return Pointer(index);
	}


	// MODIFIERS

	// Assigns this list's elements and capacity to the elements and capacity of another list
	List<DataType>& Assign(List<DataType> new_data)
	{
		// Delete the old list's data
		delete[] listData;

		// Store the list's size values
		listSize = new_data.Size();

		listCapacity = listSize;

		listExpansions = 0;

		// Allocate the space from the new list
		listData = new DataType[listCapacity];

		// Place the data back into the list
		for (int i = 0; i < listSize; i++)
		{
			listData[i] = new_data[i];
		}

		return *this;
	}

	// Assigns this list's elements and capacity to the elements and capacity of another list
	List<DataType>& Set(List<DataType> new_data)
	{
		return Assign(new_data);
	}

	// Assigns this list's elements and capacity to the elements and capacity of another list
	List<DataType>& operator=(List<DataType> new_data)
	{
		return Assign(new_data);
	}

	// Adds a new element at the front of the list
	List<DataType>& Push(DataType new_data)
	{
		// Expand the list if needed
		if (listSize + 1 > listCapacity)
		{
			Reallocate();
		}

		// Increase the list size
		listSize++;

		// Shift list elements forward
		for (int i = listSize - 1; i >= 1; i--)
		{
			listData[i] = listData[i - 1];
		}

		// Set the first element to the new data
		listData[0] = new_data;

		return *this;
	}

	// Adds a new element at the front of the list
	List<DataType>& Enqueue(DataType new_data)
	{
		return Push(new_data);
	}

	// Adds a new element at the front of the list
	List<DataType>& AddFront(DataType new_data)
	{
		return Push(new_data);
	}

	// Adds a new element at the end of the list
	List<DataType>& PushBack(DataType new_data)
	{
		// Expand the list if needed
		if (listSize + 1 > listCapacity)
		{
			Reallocate();
		}

		// Increase the list size
		listSize++;

		// Sets the last element to the new data
		listData[listSize - 1] = new_data;

		return *this;
	}

	// Adds a new element at the end of the list
	List<DataType>& Add(DataType new_data)
	{
		return PushBack(new_data);
	}

	// Adds a new element at the end of the list
	List<DataType>& operator+(DataType new_data)
	{
		return PushBack(new_data);
	}

	// Remove and return the first element of the list
	DataType Pop()
	{
		// Decrease the list size if possible
		if (listSize == 0)
		{
			return listData[0];
		}

		listSize--;

		// Store the removed data
		DataType new_data = listData[0];

		// Shift list elements backward
		for (int i = 1; i <= listSize; i++)
		{
			listData[i - 1] = listData[i];
		}

		return new_data;
	}

	// Remove and return the first element of the list
	DataType Dequeue()
	{
		return Pop();
	}

	// Remove and return the last element of the list
	DataType PopBack()
	{
		// Decrease the list size if possible
		if (listSize == 0)
		{
			return listData[0];
		}

		listSize--;

		return listData[listSize];
	}

	// Adds a new element in the list at a given index and shift following elements forward
	List<DataType>& Insert(int index, DataType new_data)
	{
		// Check for out of bounds
		if (index < 0 || index >= listSize)
		{
			return *this;
		}

		// Expand the list if needed
		if (listSize + 1 > listCapacity)
		{
			Reallocate();
		}

		// Increase the list size
		listSize++;

		// Shift elements at and past the new index forward
		for (int i = listSize - 1; i >= index; i--)
		{
			listData[i] = listData[i - 1];
		}

		// Replace the starting index with the new data
		listData[index] = new_data;

		return *this;
	}

	// Removes a element in the list at a given index and shift following elements back
	List<DataType>& Erase(int index)
	{
		// Check for out of bounds
		if (index < 0 || index >= listSize)
		{
			return *this;
		}

		// Decrease the list size
		listSize--;

		// Shift elements past the new index backward
		for (int i = index + 1; i <= listSize; i++)
		{
			listData[i - 1] = listData[i];
		}

		return *this;
	}

	// Removes a element in the list at a given index and shift following elements back
	List<DataType>& RemoveAt(int index)
	{
		return Erase(index);
	}

	// Swaps two elements at two given indicies
	List<DataType>& Swap(int index1, int index2)
	{
		// Check for out of bounds
		if (index1 < 0 || index1 >= listSize || index2 < 0 || index2 >= listSize)
		{
			return *this;
		}

		// Check if the indicies are the same
		if (index1 == index2)
		{
			return *this;
		}

		// Store swapped data
		DataType temp = listData[index2];

		// Replace the swapped data
		listData[index2] = listData[index1];

		// Return the swapped data
		listData[index1] = temp;

		return *this;
	}

	// Clears the list's data
	List<DataType>& Clear()
	{
		// Delete the list's data
		delete[] listData;

		// Reset list variables
		listData = new DataType[1];

		listSize = 0;

		listCapacity = 1;

		listExpansions = 0;

		return *this;
	}

	// Adds a new element in the list at a given index and shift following elements forward
	List<DataType>& Emplace(int index, DataType& new_data)
	{
		// Check for out of bounds
		if (index < 0 || index >= listSize)
		{
			return *this;
		}

		// Expand the list if needed
		if (listSize + 1 > listCapacity)
		{
			Reallocate();
		}

		// Increase the list size
		listSize++;

		// Shift elements at and past the new index forward
		for (int i = listSize - 1; i >= index; i--)
		{
			listData[i] = listData[i - 1];
		}

		// Replace the starting index with the new data
		listData[index] = new_data;

		return *this;
	}

	// Adds a new element at the front of the list
	List<DataType>& Emplace(DataType& new_data)
	{
		// Expand the list if needed
		if (listSize + 1 > listCapacity)
		{
			Reallocate();
		}

		// Increase the list size
		listSize++;

		// Shift list elements forward
		for (int i = listSize - 1; i >= 1; i--)
		{
			listData[i] = listData[i - 1];
		}

		// Set the first element to the new data
		listData[0] = new_data;

		return *this;
	}

	// Adds a new element at the end of the list
	List<DataType>& EmplaceBack(DataType& new_data)
	{
		// Expand the list if needed
		if (listSize + 1 > listCapacity)
		{
			Reallocate();
		}

		// Increase the list size
		listSize++;

		// Sets the last element to the new data
		listData[listSize - 1] = new_data;

		return *this;
	}

	// Returns a copy of the list's data
	List<DataType> Copy()
	{
		List<DataType> newList = List<DataType>(*this);

		return newList;
	}

	// Returns the first index of the given data in the list, returns -1 if nothing matched
	int Find(DataType found_data)
	{
		// Loop through the list for the matching element
		for (int i = 0; i < listSize; i++)
		{
			if (listData[i] == found_data)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns the first index of the given data in the list, returns -1 if nothing matched
	int IndexOf(DataType found_data)
	{
		return Find(found_data);
	}

	// Returns the last index of the given data in the list, returns -1 if nothing matched
	int FindLast(DataType found_data)
	{
		// Loop through the list for the matching element
		for (int i = listSize - 1; i >= 0; i--)
		{
			if (listData[i] == found_data)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns the last index of the given data in the list, returns -1 if nothing matched
	int LastIndexOf(DataType found_data)
	{
		return FindLast(found_data);
	}

	// Returns the total number of instances of the given data in the list, returns -1 if nothing matched
	int Total(DataType found_data)
	{
		// Store the current count
		int count = 0;

		// Loop through the list for matching elements
		for (int i = 0; i < listSize; i++)
		{
			if (listData[i] == found_data)
			{
				count++;
			}
		}

		return count;
	}

	// Returns whether the list contains at least one of the elements 
	bool Contains(DataType contained_data)
	{
		return Find(contained_data) != -1;
	}

	// Returns whether the list contains at least one of the elements 
	bool Exists(DataType contained_data)
	{
		return Contains(contained_data);
	}

	// Removes the first of a given element in the list
	List<DataType>& Remove(DataType removed_data)
	{
		return Erase(Find(removed_data));
	}

	// Removes the last of a given element in the list
	List<DataType>& RemoveLast(DataType removed_data)
	{
		return Erase(FindLast(removed_data));
	}

	// Removes the last of a given element in the list
	List<DataType>& operator-(DataType new_data)
	{
		return RemoveLast(new_data);
	}

	// Removes all of the given element in the list
	List<DataType>& RemoveAll(DataType removed_data)
	{
		// Get the total number of elements
		int amount = Total(removed_data);

		// Remove those elements
		for (int i = 0; i < amount; i++)
		{
			Remove(removed_data);
		}

		return *this;
	}

	// Replaces the data at the given index with the given data
	List<DataType>& Fill(int index, DataType new_data)
	{
		// Check for out of bounds
		if (index < 0 || index >= listSize)
		{
			return *this;
		}

		// Replace the data at the index
		listData[index] = new_data;

		return *this;
	}

	// Replaces the data at the given index with the given data
	List<DataType>& Overwrite(int index, DataType new_data)
	{
		return Fill(index, new_data);
	}

	// Replaces the first of the found data with the given data
	List<DataType>& Replace(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = Find(replaced_data);

		// Check if the data was not found
		if (index == -1)
		{
			return *this;
		}

		// Replace the data at the index
		listData[index] = new_data;

		return *this;
	}

	// Replaces the last of the found data with the given data
	List<DataType>& ReplaceLast(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = FindLast(replaced_data);

		// Check if the data was not found
		if (index == -1)
		{
			return *this;
		}

		// Replace the data at the index
		listData[index] = new_data;

		return *this;
	}

	// Replaces all of the found data with the given data
	List<DataType>& ReplaceAll(DataType replaced_data, DataType new_data)
	{
		// Get the total number of elements
		int amount = Total(replaced_data);

		// Replace those elements
		for (int i = 0; i < amount; i++)
		{
			Replace(replaced_data, new_data);
		}

		return *this;
	}

	// Reverse the list elements
	List<DataType>& Reverse()
	{
		// Check length
		if (listSize <= 1)
		{
			return *this;
		}

		// Loop through each element and swap it with the element across the end
		for (int i = 0; i < listSize / 2; i++)
		{
			Swap(i, listSize - i - 1);
		}

		return *this;
	}

	// Reverse the list elements
	List<DataType>& operator~()
	{
		return Reverse();
	}

	// Shifts the list elements right
	List<DataType>& ShiftRight(int number_of_shifts)
	{
		// Check length
		if (listSize <= 1)
		{
			return *this;
		}

		// Check if shifting the list is unnecessary
		if (number_of_shifts % listSize == 0)
		{
			return *this;
		}

		// Duplicate the list
		DataType* temp = new DataType[listSize];

		for (int i = 0; i < listSize; i++)
		{
			temp[i] = listData[i];
		}

		// Delete the old list's data
		delete[] listData;

		listData = new DataType[listCapacity];

		// Place the list elements at their shifted location using modulo
		for (int i = 0; i < listSize; i++)
		{
			listData[i] = temp[((i - number_of_shifts) % listSize + listSize) % listSize];
		}

		delete[] temp;

		return *this;
	}

	// Shifts the list elements right
	List<DataType>& Shift(int number_of_shifts)
	{
		return ShiftRight(number_of_shifts);
	}

	// Shifts the list elements right
	List<DataType>& operator>>(int number_of_shifts)
	{
		return ShiftRight(number_of_shifts);
	}

	// Shifts the list elements left
	List<DataType>& ShiftLeft(int number_of_shifts)
	{
		return ShiftRight(-number_of_shifts);
	}

	// Shifts the list elements left
	List<DataType>& operator<<(int number_of_shifts)
	{
		return ShiftRight(-number_of_shifts);
	}

	// Bubble sorts the elements of the list relative to the given sort order
	List<DataType>& Sort(SORT_TYPE sort_order[])
	{
		// Check length
		if (listSize <= 1)
		{
			return *this;
		}

		// Place the list elements in the sorted order
		for (int i = 0; i < listSize - 1; i++)
		{
			for (int j = 0; j < listSize - i - 1; j++)
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

	// Safely bubble sorts the elements of the list relative to the given sort order
	List<DataType>& Sort(List<SORT_TYPE> sort_order)
	{
		DataType* new_sort_order = sort_order.ToNewArray();

		sort(new_sort_order);

		delete[] new_sort_order;

		return *this;
	}

	// Bubble sorts the elements of the list relative to the given sort order (converts the sort order to the given sort type)
	template<class SortData> List<DataType>& Sort(SortData sort_order[])
	{
		SORT_TYPE* new_sort_order = new SORT_TYPE[listSize];

		for (int i = 0; i < listSize; i++)
		{
			new_sort_order[i] = static_cast<SORT_TYPE>(sort_order[i]);
		}

		sort(new_sort_order);

		delete[] new_sort_order;

		return *this;
	}

	// Safely bubble sorts the elements of the list relative to the given sort order (converts the sort order to the given sort type)
	template<class SortData> List<DataType>& Sort(List<SortData> sort_order)
	{
		SORT_TYPE* new_sort_order = new SORT_TYPE[listSize];

		for (int i = 0; i < listSize; i++)
		{
			new_sort_order[i] = static_cast<SORT_TYPE>(sort_order[i]);
		}

		sort(new_sort_order);

		delete[] new_sort_order;

		return *this;
	}

	// Prints the elements of the list
	void Print()
	{
		for (int i = 0; i < listSize; i++)
		{
			std::cout << i << ". " << listData[i] << std::endl;
		}
	}

	// Converts the elements of the list into a string
	std::string ToString()
	{
		std::string log = "";

		for (int i = 0; i < listSize; i++)
		{
			log += std::to_string(i) + ". " + std::to_string(listData[i]) + "\n";
		}

		return log;
	}


	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	List()
	{
		listData = new DataType[1];

		listSize = 0;

		listCapacity = 1;

		listExpansions = 0;
	}

	// List constructor
	List(const std::initializer_list<DataType> new_list)
	{
		listSize = new_list.size();

		listCapacity = new_list.size();

		listExpansions = 0;

		listData = new DataType[listCapacity];

		for (int i = 0; i < listSize; i++)
		{
			listData[i] = *(new_list.begin() + i);
		}
	}

	// Copy constructor
	List(const List<DataType>& copied_list)
	{
		listSize = copied_list.listSize;

		listCapacity = copied_list.listCapacity;

		listExpansions = 0;

		listData = new DataType[listCapacity];

		for (int i = 0; i < listSize; i++)
		{
			listData[i] = copied_list.listData[i];
		}
	}

	// Capacity constructor
	List(int max_capacity)
	{
		listData = new DataType[max_capacity];

		listSize = 0;

		listCapacity = max_capacity;

		listExpansions = 0;
	}

	// Fill constructor
	List(int size_and_capacity, DataType new_data)
	{
		listData = new DataType[size_and_capacity];

		for (int i = 0; i < size_and_capacity; i++)
		{
			listData[i] = new_data;
		}

		listSize = size_and_capacity;

		listCapacity = listSize;

		listExpansions = 0;
	}

	// Array constructor
	List(DataType array[], int array_length)
	{
		listData = new DataType[array_length];

		for (int i = 0; i < array_length; i++)
		{
			listData[i] = array[i];
		}

		listSize = array_length;

		listCapacity = listSize;

		listExpansions = 0;
	}

	// Deconstructor
	~List()
	{
		// Delete the list's data
		delete[] listData;

		listData = nullptr;
	}
};
