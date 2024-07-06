
// Vector Data Type Class
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/vector/vector/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=net-8.0

#pragma once
#include <iostream>
#include <string>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the class
#include "Vector.h"

// Data type used for sorting.
#define SORT_TYPE float

// Vector container class.
template <class DataType> class vector
{
private:

	// VECTOR VARIABLES

	// The array of pointers representing the vector's data
	DataType* vector_data = new DataType[1];

	// The current number of pointers in the array holding data
	int vector_size = 0;

	// The current maximum size of the array before needing to expand
	int vector_capacity = 1;

	// The number of array expansions
	int vector_expansions = 0;

public:

	// REALLOCATE MEMORY

	// Expands the capacity based on how many times it has been expanded
	vector<DataType>& reallocate()
	{
		// Advance the number of expansions
		vector_expansions++;

		// Duplicate the vector
		DataType* temp = new DataType[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			temp[i] = vector_data[i];
		}

		// Delete the old vector's data
		delete[] vector_data;

		// Allocate new space for the vector
		vector_capacity *= 2;

		vector_data = new DataType[vector_capacity];

		// Place the data back into the vector
		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = temp[i];
		}

		delete[] temp;

		return *this;
	}


	// TO ARRAY

	// Returns a new pointer to a new array of the current vector (must be deallocated)
	DataType* to_new_array()
	{
		// Copy the vector into an array
		DataType* new_array = new DataType[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			new_array[i] = vector_data[i];
		}

		return new_array;
	}


	// VECTOR EQUALITY

	// Check if another vector is equal to this vector
	bool equals(vector<DataType> compared_vector)
	{
		// Check if the sizes are equal
		if (vector_size != compared_vector.vector_size)
		{
			return false;
		}

		// Loop through each element to check if they are not equal
		for (int i = 0; i < vector_size; i++)
		{
			// Are they not equal
			if (vector_data[i] != compared_vector[i])
			{
				return false;
			}
		}

		// The vectors are equal
		return true;
	}

	// Check if another vector is equal to this vector
	bool operator==(vector<DataType> compared_vector)
	{
		return equals(compared_vector);
	}

	// Check if another vector is not equal to this vector
	bool operator!=(vector<DataType> compared_vector)
	{
		return !equals(compared_vector);
	}


	// ITERATORS

	// Return a pointer to the beginning
	DataType* begin()
	{
		DataType* pointer = &vector_data[0];

		return pointer;
	}

	// Return a pointer to the beginning
	DataType* ptr()
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
		DataType* pointer = &vector_data[vector_size - 1];

		return pointer;
	}

	// Return a pointer to the end
	DataType* ptr_end()
	{
		return end();
	}

	// Return a pointer to the given index
	DataType* ptr(int index)
	{
		DataType* pointer = &vector_data[index];

		return pointer;
	}


	// CAPACITY

	// Return the current size of the vector
	int size()
	{
		return vector_size;
	}

	// Return the current size of the vector
	int count()
	{
		return vector_size;
	}

	// Return the current size of the vector
	int length()
	{
		return vector_size;
	}

	// Resizes the vector's size and removes out of bounds data or expands if necessary
	vector<DataType>& resize(int new_size)
	{
		// Check if the new size is identical
		if (vector_size == new_size)
		{
			return *this;
		}

		// Duplicate the current vector
		DataType* temp = new DataType[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			temp[i] = vector_data[i];
		}

		// Delete the old vector's data
		delete[] vector_data;

		// Expand the vector if needed
		if (new_size > vector_capacity)
		{
			reallocate();
		}

		// Allocate new space for the vector
		vector_data = new DataType[vector_capacity];

		vector_size = new_size;

		// Place the data back into the vector
		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = temp[i];
		}

		delete[] temp;

		return *this;
	}

	// Return the maximum capacity of the vector before expanding
	int capacity()
	{
		return vector_capacity;
	}

	// Return the maximum capacity of the vector before expanding
	int max_size()
	{
		return capacity();
	}

	// Return whether the vector is empty
	bool empty()
	{
		return vector_size == 0;
	}

	// Return whether the vector is empty
	bool is_empty()
	{
		return empty();
	}

	// Expands the vector's capacity enough to hold the given amount (does not reduce the capacity)
	vector<DataType>& reserve(int new_capacity)
	{
		// Check if the new capacity is less
		if (new_capacity <= vector_capacity)
		{
			return *this;
		}

		// Advance the number of expansions
		vector_expansions++;

		// Duplicate the current vector
		DataType* temp = new DataType[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			temp[i] = vector_data[i];
		}

		// Delete the old vector's data
		delete[] vector_data;

		// Allocate new space for the vector
		vector_capacity = new_capacity;

		vector_data = new DataType[vector_capacity];

		// Place the data back into the vector
		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = temp[i];
		}

		delete[] temp;

		return *this;
	}

	// Expands the vector's capacity enough to hold the given amount (does not reduce the capacity)
	vector<DataType>& ensure_capacity(int new_capacity)
	{
		return reserve(new_capacity);
	}

	// Shrinks the capacity to the size
	vector<DataType>& shrink_to_fit()
	{
		// Duplicate the current vector
		DataType* temp = new DataType[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			temp[i] = vector_data[i];
		}

		// Delete the old vector's data
		delete[] vector_data;

		// Allocate new space for the vector
		vector_capacity = vector_size;

		vector_data = new DataType[vector_capacity];

		// Place the data back into the vector
		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = temp[i];
		}

		// Reset the number of resizes
		vector_expansions = 0;

		delete[] temp;

		return *this;
	}

	// Shrinks the capacity to the size
	vector<DataType>& trim_excess()
	{
		return shrink_to_fit();
	}

	// Shrinks the capacity to the size
	vector<DataType>& clean()
	{
		return shrink_to_fit();
	}

	// Return the total number of expansions
	int expansions()
	{
		return vector_expansions;
	}

	// Return the total number of expansions
	int reallocations()
	{
		return expansions();
	}

	// Expands the vector's capacity by the given amount
	vector<DataType>& expand(int number_of_spaces)
	{
		return reserve(vector_capacity + number_of_spaces);
	}


	// ELEMENT ACCESS

	// Returns the element at the given index
	DataType& at(int index)
	{
		return vector_data[index];
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

	// Returns the first element in the vector
	DataType& front()
	{
		return vector_data[0];
	}

	// Returns the first element in the vector
	DataType& back()
	{
		return vector_data[vector_size - 1];
	}

	// Return a pointer to the given index
	DataType* data(int index)
	{
		return ptr(index);
	}


	// MODIFIERS

	// Assigns this vector's elements and capacity to the elements and capacity of another vector
	vector<DataType>& assign(vector<DataType> new_data)
	{
		// Delete the old vector's data
		delete[] vector_data;

		// Store the vector's size values
		vector_size = new_data.size();

		vector_capacity = vector_size;

		vector_expansions = 0;

		// Allocate the space from the new vector
		vector_data = new DataType[vector_capacity];

		// Place the data back into the vector
		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = new_data[i];
		}

		return *this;
	}

	// Assigns this vector's elements and capacity to the elements and capacity of another vector
	vector<DataType>& operator=(vector<DataType> new_data)
	{
		return assign(new_data);
	}

	// Adds a new element at the front of the vector
	vector<DataType>& push(DataType new_data)
	{
		// Expand the vector if needed
		if (vector_size + 1 > vector_capacity)
		{
			reallocate();
		}

		// Increase the vector size
		vector_size++;

		// Shift vector elements forward
		for (int i = vector_size - 1; i >= 1; i--)
		{
			vector_data[i] = vector_data[i - 1];
		}

		// Set the first element to the new data
		vector_data[0] = new_data;

		return *this;
	}

	// Adds a new element at the front of the vector
	vector<DataType>& enqueue(DataType new_data)
	{
		return push(new_data);
	}

	// Adds a new element at the front of the vector
	vector<DataType>& add_front(DataType new_data)
	{
		return push(new_data);
	}

	// Adds a new element at the end of the vector
	vector<DataType>& push_back(DataType new_data)
	{
		// Expand the vector if needed
		if (vector_size + 1 > vector_capacity)
		{
			reallocate();
		}

		// Increase the vector size
		vector_size++;

		// Sets the last element to the new data
		vector_data[vector_size - 1] = new_data;

		return *this;
	}

	// Adds a new element at the end of the vector
	vector<DataType>& add(DataType new_data)
	{
		return push_back(new_data);
	}

	// Remove and return the first element of the vector
	DataType pop()
	{
		// Decrease the vector size if possible
		if (vector_size == 0)
		{
			return vector_data[0];
		}

		vector_size--;

		// Store the removed data
		DataType new_data = vector_data[0];

		// Shift vector elements backward
		for (int i = 1; i <= vector_size; i++)
		{
			vector_data[i - 1] = vector_data[i];
		}

		return new_data;
	}

	// Remove and return the last element of the vector
	DataType pop_back()
	{
		// Decrease the vector size if possible
		if (vector_size == 0)
		{
			return vector_data[0];
		}

		vector_size--;

		return vector_data[vector_size];
	}

	// Remove and return the last element of the vector
	DataType dequeue()
	{
		return pop_back();
	}

	// Adds a new element in the vector at a given index and shift following elements forward
	vector<DataType>& insert(int index, DataType new_data)
	{
		// Check for out of bounds
		if (index < 0 || index >= vector_size)
		{
			return *this;
		}

		// Expand the vector if needed
		if (vector_size + 1 > vector_capacity)
		{
			reallocate();
		}

		// Increase the vector size
		vector_size++;

		// Shift elements at and past the new index forward
		for (int i = vector_size - 1; i >= index; i--)
		{
			vector_data[i] = vector_data[i - 1];
		}

		// Replace the starting index with the new data
		vector_data[index] = new_data;

		return *this;
	}

	// Removes a element in the vector at a given index and shift following elements back
	vector<DataType>& erase(int index)
	{
		// Check for out of bounds
		if (index < 0 || index >= vector_size)
		{
			return *this;
		}

		// Decrease the vector size
		vector_size--;

		// Shift elements past the new index backward
		for (int i = index + 1; i <= vector_size; i++)
		{
			vector_data[i - 1] = vector_data[i];
		}

		return *this;
	}

	// Removes a element in the vector at a given index and shift following elements back
	vector<DataType>& remove_at(int index)
	{
		return erase(index);
	}

	// Swaps two elements at two given indicies
	vector<DataType>& swap(int index1, int index2)
	{
		// Check for out of bounds
		if (index1 < 0 || index1 >= vector_size || index2 < 0 || index2 >= vector_size)
		{
			return *this;
		}

		// Check if the indicies are the same
		if (index1 == index2)
		{
			return *this;
		}

		// Store swapped data
		DataType temp = vector_data[index2];

		// Replace the swapped data
		vector_data[index2] = vector_data[index1];

		// Return the swapped data
		vector_data[index1] = temp;

		return *this;
	}

	// Clears the vector's data
	vector<DataType>& clear()
	{
		// Delete the vector's data
		delete[] vector_data;

		// Reset vector variables
		vector_data = new DataType[1];

		vector_size = 0;

		vector_capacity = 1;

		vector_expansions = 0;

		return *this;
	}

	// Adds an existing variable to a given index and shift following elements forward
	vector<DataType>& emplace(int index, DataType& new_data)
	{
		// Check for out of bounds
		if (index < 0 || index >= vector_size)
		{
			return *this;
		}

		// Expand the vector if needed
		if (vector_size + 1 > vector_capacity)
		{
			reallocate();
		}

		// Increase the vector size
		vector_size++;

		// Shift elements at and past the new index forward
		for (int i = vector_size - 1; i >= index; i--)
		{
			vector_data[i] = vector_data[i - 1];
		}

		// Replace the starting index with the new data
		vector_data[index] = new_data;

		return *this;
	}

	// Adds an existing variable to the front of the vector
	vector<DataType>& emplace(DataType& new_data)
	{
		// Expand the vector if needed
		if (vector_size + 1 > vector_capacity)
		{
			reallocate();
		}

		// Increase the vector size
		vector_size++;

		// Shift vector elements forward
		for (int i = vector_size - 1; i >= 1; i--)
		{
			vector_data[i] = vector_data[i - 1];
		}

		// Set the first element to the new data
		vector_data[0] = new_data;

		return *this;
	}

	// Adds an existing variable to the end of the vector
	vector<DataType>& emplace_back(DataType& new_data)
	{
		// Expand the vector if needed
		if (vector_size + 1 > vector_capacity)
		{
			reallocate();
		}

		// Increase the vector size
		vector_size++;

		// Sets the last element to the new data
		vector_data[vector_size - 1] = new_data;

		return *this;
	}

	// Returns a copy of the vector's data
	vector<DataType> copy()
	{
		vector<DataType> newvector = vector<DataType>(*this);

		return newvector;
	}

	// Returns the first index of the given data in the vector, returns -1 if nothing matched
	int find(DataType found_data)
	{
		// Loop through the vector for the matching element
		for (int i = 0; i < vector_size; i++)
		{
			if (vector_data[i] == found_data)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns the first index of the given data in the vector, returns -1 if nothing matched
	int index_of(DataType found_data)
	{
		return find(found_data);
	}

	// Returns the last index of the given data in the vector, returns -1 if nothing matched
	int find_last(DataType found_data)
	{
		// Loop through the vector for the matching element
		for (int i = vector_size - 1; i >= 0; i--)
		{
			if (vector_data[i] == found_data)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns the last index of the given data in the vector, returns -1 if nothing matched
	int last_index_of(DataType found_data)
	{
		return find_last(found_data);
	}

	// Returns the total number of instances of the given data in the vector
	int total(DataType found_data)
	{
		// Store the current count
		int count = 0;

		// Loop through the vector for matching elements
		for (int i = 0; i < vector_size; i++)
		{
			if (vector_data[i] == found_data)
			{
				count++;
			}
		}

		return count;
	}

	// Returns whether the vector contains at least one of the elements 
	bool contains(DataType contained_data)
	{
		return find(contained_data) != -1;
	}

	// Returns whether the vector contains at least one of the elements 
	bool exists(DataType contained_data)
	{
		return contains(contained_data);
	}

	// Removes the first of a given element in the vector
	vector<DataType>& remove(DataType removed_data)
	{
		return erase(find(removed_data));
	}

	// Removes the last of a given element in the vector
	vector<DataType>& remove_last(DataType removed_data)
	{
		return erase(find_last(removed_data));
	}

	// Removes all of the given element in the vector
	vector<DataType>& remove_all(DataType removed_data)
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
	vector<DataType>& set(int index, DataType new_data)
	{
		// Check for out of bounds
		if (index < 0 || index >= vector_size)
		{
			return *this;
		}

		// Replace the data at the index
		vector_data[index] = new_data;

		return *this;
	}

	// Replaces the data at the given index with the given data
	vector<DataType>& overwrite(int index, DataType new_data)
	{
		return set(index, new_data);
	}

	// Replaces the first of the found data with the given data
	vector<DataType>& replace(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = find(replaced_data);

		// Check if the data was not found
		if (index == -1)
		{
			return *this;
		}

		// Replace the data at the index
		vector_data[index] = new_data;

		return *this;
	}

	// Replaces the last of the found data with the given data
	vector<DataType>& replace_last(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = find_last(replaced_data);

		// Check if the data was not found
		if (index == -1)
		{
			return *this;
		}

		// Replace the data at the index
		vector_data[index] = new_data;

		return *this;
	}

	// Replaces all of the found data with the given data
	vector<DataType>& replace_all(DataType replaced_data, DataType new_data)
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

	// Reverse the vector elements
	vector<DataType>& reverse()
	{
		// Check length
		if (vector_size <= 1)
		{
			return *this;
		}

		// Loop through each element and swap it with the element across the end
		for (int i = 0; i < vector_size / 2; i++)
		{
			swap(i, vector_size - i - 1);
		}

		return *this;
	}

	// Shifts the vector elements right
	vector<DataType>& shift_right(int number_of_shifts)
	{
		// Check length
		if (vector_size <= 1)
		{
			return *this;
		}

		// Check if shifting the vector is unnecessary
		if (number_of_shifts % vector_size == 0)
		{
			return *this;
		}

		// Duplicate the vector
		DataType* temp = new DataType[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			temp[i] = vector_data[i];
		}

		// Delete the old vector's data
		delete[] vector_data;

		vector_data = new DataType[vector_capacity];

		// Place the vector elements at their shifted location using modulo
		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = temp[((i - number_of_shifts) % vector_size + vector_size) % vector_size];
		}

		delete[] temp;

		return *this;
	}

	// Shifts the vector elements right
	vector<DataType>& shift(int number_of_shifts)
	{
		return shift_right(number_of_shifts);
	}

	// Shifts the vector elements left
	vector<DataType>& shift_left(int number_of_shifts)
	{
		return shift_right(-number_of_shifts);
	}

	// Bubble sorts the elements of the vector relative to the given sort order
	vector<DataType>& sort(SORT_TYPE sort_order[])
	{
		// Check length
		if (vector_size <= 1)
		{
			return *this;
		}

		// Place the vector elements in the sorted order
		for (int i = 0; i < vector_size - 1; i++)
		{
			for (int j = 0; j < vector_size - i - 1; j++)
			{
				if (sort_order[j] > sort_order[j + 1])
				{
					// Swap the two vector elements
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

	// Safely bubble sorts the elements of the vector relative to the given sort order
	vector<DataType>& sort(vector<SORT_TYPE> sort_order)
	{
		SORT_TYPE* new_sort_order = sort_order.to_new_array();

		sort(new_sort_order);

		delete[] new_sort_order;

		return *this;
	}

	// Prints the elements of the vector
	void print()
	{
		for (int i = 0; i < vector_size; i++)
		{
			std::cout << i << ". " << vector_data[i] << std::endl;
		}
	}

	// Converts the elements of the vector into a string
	std::string to_string()
	{
		std::string log = "";

		for (int i = 0; i < vector_size; i++)
		{
			log += std::to_string(i) + ". " + std::to_string(vector_data[i]) + "\n";
		}

		return log;
	}


	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	vector()
	{
		vector_data = new DataType[1];

		vector_size = 0;

		vector_capacity = 1;

		vector_expansions = 0;
	}

	// List constructor
	vector(const std::initializer_list<DataType> new_vector)
	{
		vector_size = new_vector.size();

		vector_capacity = new_vector.size();

		vector_expansions = 0;

		vector_data = new DataType[vector_capacity];

		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = *(new_vector.begin() + i);
		}
	}

	// Copy constructor
	vector(const vector<DataType>& copied_vector)
	{
		vector_size = copied_vector.vector_size;

		vector_capacity = copied_vector.vector_capacity;

		vector_expansions = 0;

		vector_data = new DataType[vector_capacity];

		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = copied_vector.vector_data[i];
		}
	}

	// Capacity constructor
	vector(int max_capacity)
	{
		vector_data = new DataType[max_capacity];

		vector_size = 0;

		vector_capacity = max_capacity;

		vector_expansions = 0;
	}

	// Fill constructor
	vector(int size_and_capacity, DataType new_data)
	{
		vector_data = new DataType[size_and_capacity];

		for (int i = 0; i < size_and_capacity; i++)
		{
			vector_data[i] = new_data;
		}

		vector_size = size_and_capacity;

		vector_capacity = vector_size;

		vector_expansions = 0;
	}

	// Array constructor
	vector(DataType array[], int array_length)
	{
		vector_data = new DataType[array_length];

		for (int i = 0; i < array_length; i++)
		{
			vector_data[i] = array[i];
		}

		vector_size = array_length;

		vector_capacity = vector_size;

		vector_expansions = 0;
	}

	// List constructor
	vector(int array_length, DataType data...)
	{
		vector_data = new DataType[array_length];

		va_list list;

		va_start(list, array_length);

		for (int i = 0; i < array_length; i++)
		{
			vector_data[i] = va_arg(list, DataType);
		}

		va_end(list);

		vector_size = array_length;

		vector_capacity = vector_size;

		vector_expansions = 0;
	}

	// Deconstructor
	~vector()
	{
		// Delete the vector's data
		delete[] vector_data;

		vector_data = nullptr;
	}
};

// Vector container class.
template <class DataType> class Vector
{
private:

	// VECTOR VARIABLES

	// The array of pointers representing the vector's data
	DataType* vectorData = new DataType[1];

	// The current number of pointers in the array holding data
	int vectorSize = 0;

	// The current maximum size of the array before needing to expand
	int vectorCapacity = 1;

	// The number of array expansions
	int vectorExpansions = 0;

public:

	// REALLOCATE MEMORY

	// Expands the capacity based on how many times it has been expanded
	Vector<DataType>& Reallocate()
	{
		// Advance the number of expansions
		vectorExpansions++;

		// Duplicate the vector
		DataType* temp = new DataType[vectorSize];

		for (int i = 0; i < vectorSize; i++)
		{
			temp[i] = vectorData[i];
		}

		// Delete the old vector's data
		delete[] vectorData;

		// Allocate new space for the vector
		vectorCapacity *= 2;

		vectorData = new DataType[vectorCapacity];

		// Place the data back into the vector
		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = temp[i];
		}

		delete[] temp;

		return *this;
	}


	// TO ARRAY

	// Returns a pointer to a new array of the current vector
	DataType* ToNewArray()
	{
		// Copy the vector into an array
		DataType* new_array = new DataType[vectorSize];

		for (int i = 0; i < vectorSize; i++)
		{
			new_array[i] = vectorData[i];
		}

		return new_array;
	}


	// VECTOR EQUALITY

	// Check if another vector is equal to this vector
	bool Equals(Vector<DataType> compared_vector)
	{
		// Check if the sizes are equal
		if (vectorSize != compared_vector.vectorSize)
		{
			return false;
		}

		// Loop through each element to check if they are not equal
		for (int i = 0; i < vectorSize; i++)
		{
			// Are they not equal
			if (vectorData[i] != compared_vector[i])
			{
				return false;
			}
		}

		// The vectors are equal
		return true;
	}

	// Check if another vector is equal to this vector
	bool operator==(Vector<DataType> compared_vector)
	{
		return Equals();
	}

	// Check if another vector is not equal to this vector
	bool operator!=(Vector<DataType> compared_vector)
	{
		return !Equals();
	}


	// ITERATORS

	// Return a pointer to the beginning
	DataType* Begin()
	{
		DataType* pointer = &vectorData[0];

		return pointer;
	}

	// Return a pointer to the beginning
	DataType* Pointer()
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
		DataType* pointer = &vectorData[vectorSize - 1];

		return pointer;
	}

	// Return a pointer to the end
	DataType* PointerEnd()
	{
		return End();
	}

	// Return a pointer to the given index
	DataType* Pointer(int index)
	{
		DataType* pointer = &vectorData[index];

		return pointer;
	}


	// CAPACITY

	// Return the current size of the vector
	int Size()
	{
		return vectorSize;
	}

	// Return the current size of the vector
	int Count()
	{
		return vectorSize;
	}

	// Return the current size of the vector
	int Length()
	{
		return vectorSize;
	}

	// Resizes the vector's size and removes out of bounds data or expands if necessary
	Vector<DataType>& Resize(int new_size)
	{
		// Check if the new size is identical
		if (vectorSize == new_size)
		{
			return *this;
		}

		// Duplicate the current vector
		DataType* temp = new DataType[vectorSize];

		for (int i = 0; i < vectorSize; i++)
		{
			temp[i] = vectorData[i];
		}

		// Delete the old vector's data
		delete[] vectorData;

		// Expand the vector if needed
		if (new_size > vectorCapacity)
		{
			Reallocate();
		}

		// Allocate new space for the vector
		vectorData = new DataType[vectorCapacity];

		vectorSize = new_size;

		// Place the data back into the vector
		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = temp[i];
		}

		delete[] temp;

		return *this;
	}

	// Return the maximum capacity of the vector before expanding
	int Capacity()
	{
		return vectorCapacity;
	}

	// Return the maximum capacity of the vector before expanding
	int MaxSize()
	{
		return Capacity();
	}

	// Return whether the vector is empty
	bool Empty()
	{
		return vectorSize == 0;
	}

	// Return whether the vector is empty
	bool IsEmpty()
	{
		return Empty();
	}

	// Expands the vector's capacity enough to hold the given amount (does not reduce the capacity)
	Vector<DataType>& Reserve(int new_capacity)
	{
		// Check if the new capacity is less
		if (new_capacity <= vectorCapacity)
		{
			return *this;
		}

		// Advance the number of expansions
		vectorExpansions++;

		// Duplicate the current vector
		DataType* temp = new DataType[vectorSize];

		for (int i = 0; i < vectorSize; i++)
		{
			temp[i] = vectorData[i];
		}

		// Delete the old vector's data
		delete[] vectorData;

		// Allocate new space for the vector
		vectorCapacity = new_capacity;

		vectorData = new DataType[vectorCapacity];

		// Place the data back into the vector
		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = temp[i];
		}

		delete[] temp;

		return *this;
	}

	// Expands the vector's capacity enough to hold the given amount (does not reduce the capacity)
	Vector<DataType>& EnsureCapacity(int new_capacity)
	{
		return Reserve(new_capacity);
	}

	// Shrinks the capacity to the size
	Vector<DataType>& ShrinkToFit()
	{
		// Duplicate the current vector
		DataType* temp = new DataType[vectorSize];

		for (int i = 0; i < vectorSize; i++)
		{
			temp[i] = vectorData[i];
		}

		// Delete the old vector's data
		delete[] vectorData;

		// Allocate new space for the vector
		vectorCapacity = vectorSize;

		vectorData = new DataType[vectorCapacity];

		// Place the data back into the vector
		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = temp[i];
		}

		// Reset the number of resizes
		vectorExpansions = 0;

		delete[] temp;

		return *this;
	}

	// Shrinks the capacity to the size
	Vector<DataType>& TrimExcess()
	{
		return ShrinkToFit();
	}

	// Shrinks the capacity to the size
	Vector<DataType>& Clean()
	{
		return ShrinkToFit();
	}

	// Return the total number of expansions
	int Expansions()
	{
		return vectorExpansions;
	}

	// Return the total number of expansions
	int Reallocations()
	{
		return Expansions();
	}

	// Expands the vector's capacity by the given amount
	Vector<DataType>& Expand(int number_of_spaces)
	{
		return Reserve(vectorCapacity + number_of_spaces);
	}


	// ELEMENT ACCESS

	// Returns the element at the given index
	DataType& At(int index)
	{
		return vectorData[index];
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

	// Returns the first element in the vector
	DataType& Front()
	{
		return vectorData[0];
	}

	// Returns the first element in the vector
	DataType& Back()
	{
		return vectorData[vectorSize - 1];
	}

	// Return a pointer to the given index
	DataType* Data(int index)
	{
		return Pointer(index);
	}


	// MODIFIERS

	// Assigns this vector's elements and capacity to the elements and capacity of another vector
	Vector<DataType>& Assign(Vector<DataType> new_data)
	{
		// Delete the old vector's data
		delete[] vectorData;

		// Store the vector's size values
		vectorSize = new_data.Size();

		vectorCapacity = vectorSize;

		vectorExpansions = 0;

		// Allocate the space from the new vector
		vectorData = new DataType[vectorCapacity];

		// Place the data back into the vector
		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = new_data[i];
		}

		return *this;
	}

	// Assigns this vector's elements and capacity to the elements and capacity of another vector
	Vector<DataType>& operator=(Vector<DataType> new_data)
	{
		return Assign(new_data);
	}

	// Adds a new element at the front of the vector
	Vector<DataType>& Push(DataType new_data)
	{
		// Expand the vector if needed
		if (vectorSize + 1 > vectorCapacity)
		{
			Reallocate();
		}

		// Increase the vector size
		vectorSize++;

		// Shift vector elements forward
		for (int i = vectorSize - 1; i >= 1; i--)
		{
			vectorData[i] = vectorData[i - 1];
		}

		// Set the first element to the new data
		vectorData[0] = new_data;

		return *this;
	}

	// Adds a new element at the front of the vector
	Vector<DataType>& Enqueue(DataType new_data)
	{
		return Push(new_data);
	}

	// Adds a new element at the front of the vector
	Vector<DataType>& AddFront(DataType new_data)
	{
		return Push(new_data);
	}

	// Adds a new element at the end of the vector
	Vector<DataType>& PushBack(DataType new_data)
	{
		// Expand the vector if needed
		if (vectorSize + 1 > vectorCapacity)
		{
			Reallocate();
		}

		// Increase the vector size
		vectorSize++;

		// Sets the last element to the new data
		vectorData[vectorSize - 1] = new_data;

		return *this;
	}

	// Adds a new element at the end of the vector
	Vector<DataType>& Add(DataType new_data)
	{
		return PushBack(new_data);
	}

	// Remove and return the first element of the vector
	DataType Pop()
	{
		// Decrease the vector size if possible
		if (vectorSize == 0)
		{
			return vectorData[0];
		}

		vectorSize--;

		// Store the removed data
		DataType new_data = vectorData[0];

		// Shift vector elements backward
		for (int i = 1; i <= vectorSize; i++)
		{
			vectorData[i - 1] = vectorData[i];
		}

		return new_data;
	}

	// Remove and return the last element of the vector
	DataType PopBack()
	{
		// Decrease the vector size if possible
		if (vectorSize == 0)
		{
			return vectorData[0];
		}

		vectorSize--;

		return vectorData[vectorSize];
	}

	// Remove and return the last element of the vector
	DataType Dequeue()
	{
		return PopBack();
	}

	// Adds a new element in the vector at a given index and shift following elements forward
	Vector<DataType>& Insert(int index, DataType new_data)
	{
		// Check for out of bounds
		if (index < 0 || index >= vectorSize)
		{
			return *this;
		}

		// Expand the vector if needed
		if (vectorSize + 1 > vectorCapacity)
		{
			Reallocate();
		}

		// Increase the vector size
		vectorSize++;

		// Shift elements at and past the new index forward
		for (int i = vectorSize - 1; i >= index; i--)
		{
			vectorData[i] = vectorData[i - 1];
		}

		// Replace the starting index with the new data
		vectorData[index] = new_data;

		return *this;
	}

	// Removes a element in the vector at a given index and shift following elements back
	Vector<DataType>& Erase(int index)
	{
		// Check for out of bounds
		if (index < 0 || index >= vectorSize)
		{
			return *this;
		}

		// Decrease the vector size
		vectorSize--;

		// Shift elements past the new index backward
		for (int i = index + 1; i <= vectorSize; i++)
		{
			vectorData[i - 1] = vectorData[i];
		}

		return *this;
	}

	// Removes a element in the vector at a given index and shift following elements back
	Vector<DataType>& RemoveAt(int index)
	{
		return Erase(index);
	}

	// Swaps two elements at two given indicies
	Vector<DataType>& Swap(int index1, int index2)
	{
		// Check for out of bounds
		if (index1 < 0 || index1 >= vectorSize || index2 < 0 || index2 >= vectorSize)
		{
			return *this;
		}

		// Check if the indicies are the same
		if (index1 == index2)
		{
			return *this;
		}

		// Store swapped data
		DataType temp = vectorData[index2];

		// Replace the swapped data
		vectorData[index2] = vectorData[index1];

		// Return the swapped data
		vectorData[index1] = temp;

		return *this;
	}

	// Clears the vector's data
	Vector<DataType>& Clear()
	{
		// Delete the vector's data
		delete[] vectorData;

		// Reset vector variables
		vectorData = new DataType[1];

		vectorSize = 0;

		vectorCapacity = 1;

		vectorExpansions = 0;

		return *this;
	}

	// Adds an existing variable to a given index and shift following elements forward
	Vector<DataType>& Emplace(int index, DataType& new_data)
	{
		// Check for out of bounds
		if (index < 0 || index >= vectorSize)
		{
			return *this;
		}

		// Expand the vector if needed
		if (vectorSize + 1 > vectorCapacity)
		{
			Reallocate();
		}

		// Increase the vector size
		vectorSize++;

		// Shift elements at and past the new index forward
		for (int i = vectorSize - 1; i >= index; i--)
		{
			vectorData[i] = vectorData[i - 1];
		}

		// Replace the starting index with the new data
		vectorData[index] = new_data;

		return *this;
	}

	// Adds an existing variable to the front of the vector
	Vector<DataType>& Emplace(DataType& new_data)
	{
		// Expand the vector if needed
		if (vectorSize + 1 > vectorCapacity)
		{
			Reallocate();
		}

		// Increase the vector size
		vectorSize++;

		// Shift vector elements forward
		for (int i = vectorSize - 1; i >= 1; i--)
		{
			vectorData[i] = vectorData[i - 1];
		}

		// Set the first element to the new data
		vectorData[0] = new_data;

		return *this;
	}

	// Adds an existing variable to the end of the vector
	Vector<DataType>& EmplaceBack(DataType& new_data)
	{
		// Expand the vector if needed
		if (vectorSize + 1 > vectorCapacity)
		{
			Reallocate();
		}

		// Increase the vector size
		vectorSize++;

		// Sets the last element to the new data
		vectorData[vectorSize - 1] = new_data;

		return *this;
	}

	// Returns a copy of the vector's data
	Vector<DataType> Copy()
	{
		Vector<DataType> newvector = Vector<DataType>(*this);

		return newvector;
	}

	// Returns the first index of the given data in the vector, returns -1 if nothing matched
	int Find(DataType found_data)
	{
		// Loop through the vector for the matching element
		for (int i = 0; i < vectorSize; i++)
		{
			if (vectorData[i] == found_data)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns the first index of the given data in the vector, returns -1 if nothing matched
	int IndexOf(DataType found_data)
	{
		return Find(found_data);
	}

	// Returns the last index of the given data in the vector, returns -1 if nothing matched
	int FindLast(DataType found_data)
	{
		// Loop through the vector for the matching element
		for (int i = vectorSize - 1; i >= 0; i--)
		{
			if (vectorData[i] == found_data)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns the last index of the given data in the vector, returns -1 if nothing matched
	int LastIndexOf(DataType found_data)
	{
		return FindLast(found_data);
	}

	// Returns the total number of instances of the given data in the vector
	int Total(DataType found_data)
	{
		// Store the current count
		int count = 0;

		// Loop through the vector for matching elements
		for (int i = 0; i < vectorSize; i++)
		{
			if (vectorData[i] == found_data)
			{
				count++;
			}
		}

		return count;
	}

	// Returns whether the vector contains at least one of the elements 
	bool Contains(DataType contained_data)
	{
		return Find(contained_data) != -1;
	}

	// Returns whether the vector contains at least one of the elements 
	bool Exists(DataType contained_data)
	{
		return Contains(contained_data);
	}

	// Removes the first of a given element in the vector
	Vector<DataType>& Remove(DataType removed_data)
	{
		return Erase(Find(removed_data));
	}

	// Removes the last of a given element in the vector
	Vector<DataType>& RemoveLast(DataType removed_data)
	{
		return Erase(FindLast(removed_data));
	}

	// Removes all of the given element in the vector
	Vector<DataType>& RemoveAll(DataType removed_data)
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
	Vector<DataType>& Set(int index, DataType new_data)
	{
		// Check for out of bounds
		if (index < 0 || index >= vectorSize)
		{
			return *this;
		}

		// Replace the data at the index
		vectorData[index] = new_data;

		return *this;
	}

	// Replaces the data at the given index with the given data
	Vector<DataType>& Overwrite(int index, DataType new_data)
	{
		return Set(index, new_data);
	}

	// Replaces the first of the found data with the given data
	Vector<DataType>& Replace(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = Find(replaced_data);

		// Check if the data was not found
		if (index == -1)
		{
			return *this;
		}

		// Replace the data at the index
		vectorData[index] = new_data;

		return *this;
	}

	// Replaces the last of the found data with the given data
	Vector<DataType>& ReplaceLast(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = FindLast(replaced_data);

		// Check if the data was not found
		if (index == -1)
		{
			return *this;
		}

		// Replace the data at the index
		vectorData[index] = new_data;

		return *this;
	}

	// Replaces all of the found data with the given data
	Vector<DataType>& ReplaceAll(DataType replaced_data, DataType new_data)
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

	// Reverse the vector elements
	Vector<DataType>& Reverse()
	{
		// Check length
		if (vectorSize <= 1)
		{
			return *this;
		}

		// Loop through each element and swap it with the element across the end
		for (int i = 0; i < vectorSize / 2; i++)
		{
			Swap(i, vectorSize - i - 1);
		}

		return *this;
	}

	// Shifts the vector elements right
	Vector<DataType>& ShiftRight(int number_of_shifts)
	{
		// Check length
		if (vectorSize <= 1)
		{
			return *this;
		}

		// Check if shifting the vector is unnecessary
		if (number_of_shifts % vectorSize == 0)
		{
			return *this;
		}

		// Duplicate the vector
		DataType* temp = new DataType[vectorSize];

		for (int i = 0; i < vectorSize; i++)
		{
			temp[i] = vectorData[i];
		}

		// Delete the old vector's data
		delete[] vectorData;

		vectorData = new DataType[vectorCapacity];

		// Place the vector elements at their shifted location using modulo
		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = temp[((i - number_of_shifts) % vectorSize + vectorSize) % vectorSize];
		}

		delete[] temp;

		return *this;
	}

	// Shifts the vector elements right
	Vector<DataType>& Shift(int number_of_shifts)
	{
		return ShiftRight(number_of_shifts);
	}

	// Shifts the vector elements left
	Vector<DataType>& ShiftLeft(int number_of_shifts)
	{
		return ShiftRight(-number_of_shifts);
	}

	// Bubble sorts the elements of the vector relative to the given sort order
	Vector<DataType>& Sort(SORT_TYPE sort_order[])
	{
		// Check length
		if (vectorSize <= 1)
		{
			return *this;
		}

		// Place the vector elements in the sorted order
		for (int i = 0; i < vectorSize - 1; i++)
		{
			for (int j = 0; j < vectorSize - i - 1; j++)
			{
				if (sort_order[j] > sort_order[j + 1])
				{
					// Swap the two vector elements
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

	// Safely bubble sorts the elements of the vector relative to the given sort order
	Vector<DataType>& Sort(Vector<SORT_TYPE> sort_order)
	{
		SORT_TYPE* new_sort_order = sort_order.ToNewArray();

		Sort(new_sort_order);

		delete[] new_sort_order;

		return *this;
	}

	// Prints the elements of the vector
	void Print()
	{
		for (int i = 0; i < vectorSize; i++)
		{
			std::cout << i << ". " << vectorData[i] << std::endl;
		}
	}

	// Converts the elements of the vector into a string
	std::string ToString()
	{
		std::string log = "";

		for (int i = 0; i < vectorSize; i++)
		{
			log += std::to_string(i) + ". " + std::to_string(vectorData[i]) + "\n";
		}

		return log;
	}


	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	Vector()
	{
		vectorData = new DataType[1];

		vectorSize = 0;

		vectorCapacity = 1;

		vectorExpansions = 0;
	}

	// List constructor
	Vector(const std::initializer_list<DataType> new_vector)
	{
		vectorSize = new_vector.size();

		vectorCapacity = new_vector.size();

		vectorExpansions = 0;

		vectorData = new DataType[vectorCapacity];

		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = *(new_vector.begin() + i);
		}
	}

	// Copy constructor
	Vector(const Vector<DataType>& copied_vector)
	{
		vectorSize = copied_vector.vectorSize;

		vectorCapacity = copied_vector.vectorCapacity;

		vectorExpansions = 0;

		vectorData = new DataType[vectorCapacity];

		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = copied_vector.vectorData[i];
		}
	}

	// Capacity constructor
	Vector(int max_capacity)
	{
		vectorData = new DataType[max_capacity];

		vectorSize = 0;

		vectorCapacity = max_capacity;

		vectorExpansions = 0;
	}

	// Fill constructor
	Vector(int size_and_capacity, DataType new_data)
	{
		vectorData = new DataType[size_and_capacity];

		for (int i = 0; i < size_and_capacity; i++)
		{
			vectorData[i] = new_data;
		}

		vectorSize = size_and_capacity;

		vectorCapacity = vectorSize;

		vectorExpansions = 0;
	}

	// Array constructor
	Vector(DataType array[], int array_length)
	{
		vectorData = new DataType[array_length];

		for (int i = 0; i < array_length; i++)
		{
			vectorData[i] = array[i];
		}

		vectorSize = array_length;

		vectorCapacity = vectorSize;

		vectorExpansions = 0;
	}

	// List constructor
	Vector(int array_length, DataType data...)
	{
		vectorData = new DataType[array_length];

		va_list list;

		va_start(list, array_length);

		for (int i = 0; i < array_length; i++)
		{
			vectorData[i] = va_arg(list, DataType);
		}

		va_end(list);

		vectorSize = array_length;

		vectorCapacity = vectorSize;

		vectorExpansions = 0;
	}

	// Deconstructor
	~Vector()
	{
		// Delete the vector's data
		delete[] vectorData;

		vectorData = nullptr;
	}
};
