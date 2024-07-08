
// Vector Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/vector/vector/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=net-8.0

#pragma once
#include <string>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the class
#include "Vector.h"

// Data type used for sorting
#define SORT_TYPE float

// Class used to store and dynamically reallocate an array for expanding storage.
template<typename DataType> class vector
{
private:

	// VECTOR DATA

	// The array of the vector's data
	DataType* vector_data = nullptr;

	// The current number of elements in the array holding data
	int vector_size = 0;

	// The current maximum size of the array before needing to expand
	int vector_capacity = 1;

	// The number of array expansions
	int vector_expansions = 0;

public:

	// TO ARRAY

	// Returns an array of the current vector (MUST BE DEALLOCATED)
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


	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	vector()
	{
		vector_data = new DataType[1];

		vector_size = 0;

		vector_capacity = 1;

		vector_expansions = 0;
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

	// Move constructor
	vector(vector<DataType>&& moved_vector) noexcept
	{
		vector_size = moved_vector.vector_size;

		vector_capacity = moved_vector.vector_capacity;

		vector_expansions = 0;

		vector_data = new DataType[vector_capacity];

		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = moved_vector.vector_data[i];
		}

		delete[] moved_vector.vector_data;

		moved_vector.vector_data = new DataType[1];

		moved_vector.vector_size = 0;

		moved_vector.vector_capacity = 1;

		moved_vector.vector_expansions = 0;
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
	vector(int array_length, DataType array[])
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

	// Varadic argument constructor
	vector(int argc, DataType array ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		DataType* argv = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			argv.push_back(array);

			array = va_arg(_va_list, DataType);
		}

		va_end(_va_list);

		vector_data = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			vector_data[i] = argv[i];
		}

		vector_size = argc;

		vector_capacity = vector_size;

		vector_expansions = 0;

		delete argv;

		argv = nullptr;
	}

	// List constructor
	vector(std::initializer_list<DataType> list)
	{
		vector_data = new DataType[list.size()];

		for (int i = 0; i < list.size(); i++)
		{
			vector_data[i] = *(list.begin() + i);
		}

		vector_size = list.size();

		vector_capacity = vector_size;

		vector_expansions = 0;
	}

	// Destructor
	virtual ~vector()
	{
		delete[] vector_data;

		vector_data = nullptr;
	}


	// OPERATORS

	// Copy assignment operator
	vector<DataType>& operator=(const vector<DataType>& copied_vector)
	{
		vector_size = copied_vector.vector_size;

		vector_capacity = copied_vector.vector_capacity;

		vector_expansions = 0;

		delete[] vector_data;

		vector_data = new DataType[vector_capacity];

		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = copied_vector.vector_data[i];
		}

		return *this;
	}

	// Move assignment operator
	vector<DataType>& operator=(vector<DataType>&& moved_vector) noexcept
	{
		vector_size = moved_vector.vector_size;

		vector_capacity = moved_vector.vector_capacity;

		vector_expansions = 0;

		delete[] vector_data;

		vector_data = new DataType[vector_capacity];

		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = moved_vector.vector_data[i];
		}

		delete[] moved_vector.vector_data;

		moved_vector.vector_data = new DataType[1];

		moved_vector.vector_size = 0;

		moved_vector.vector_capacity = 1;

		moved_vector.vector_expansions = 0;

		return *this;
	}


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

		// Allocate new space for the vector
		vector_capacity *= 2;

		delete[] vector_data;

		vector_data = new DataType[vector_capacity];

		// Place the data back into the vector
		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = temp[i];
		}

		delete[] temp;

		temp = nullptr;

		return *this;
	}


	// VECTOR EQUALITY

	// Check if another vector is equal to the vector
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

	// Check if another vector is equal to the vector
	bool operator ==(vector<DataType> compared_vector)
	{
		return equals(compared_vector);
	}

	// Check if another vector is not equal to the vector
	bool operator !=(vector<DataType> compared_vector)
	{
		return !equals(compared_vector);
	}


	// ITERATORS

	// Get a pointer to the beginning of the vector's array
	DataType* begin()
	{
		return vector_data;
	}

	// Get a pointer to the end of the vector's array
	DataType* end()
	{
		return vector_data + (vector_size - 1);
	}

	// Returns the pointer to the element at the given index
	DataType* data(int index)
	{
		return vector_data + index;
	}


	// SIZE AND CAPACITY

	// Return the current size of the vector
	int size()
	{
		return vector_size;
	}

	// Return the maximum capacity of the vector before expanding
	int max_size()
	{
		return vector_capacity;
	}

	// Return the total number of expansions
	int reallocations()
	{
		return vector_expansions;
	}

	// Return whether the vector is empty
	bool empty()
	{
		return vector_size == 0;
	}

	// Resizes the vector's size and removes out of bounds data or expands if necessary, returns the difference
	int resize(int new_size)
	{
		// Check if the new size is identical
		if (vector_size == new_size)
		{
			return 0;
		}

		int difference = new_size - vector_capacity;

		// Duplicate the current vector
		DataType* temp = new DataType[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			temp[i] = vector_data[i];
		}

		// Expand the vector if needed
		if (new_size > vector_capacity)
		{
			reallocate();
		}

		// Allocate new space for the vector
		delete[] vector_data;

		vector_data = new DataType[vector_capacity];

		vector_size = new_size;

		// Place the data back into the vector
		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = temp[i];
		}

		delete[] temp;

		temp = nullptr;

		return difference;
	}

	// Expands the vector's capacity enough to hold the given amount and return whether it was successful (does not reduce the capacity)
	bool reserve(int new_capacity)
	{
		// Check if the new capacity is less
		if (new_capacity <= vector_capacity)
		{
			return false;
		}

		// Advance the number of expansions
		vector_expansions++;

		// Duplicate the current vector
		DataType* temp = new DataType[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			temp[i] = vector_data[i];
		}

		// Allocate new space for the vector
		vector_capacity = new_capacity;

		delete[] vector_data;

		vector_data = new DataType[vector_capacity];

		// Place the data back into the vector
		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = temp[i];
		}

		delete[] temp;

		temp = nullptr;

		return true;
	}

	// Expands the vector's capacity by the given amount and return the new capacity
	int expand(int number_of_spaces)
	{
		reserve(vector_capacity + number_of_spaces);

		return vector_capacity;
	}

	// Shrinks the capacity to the size and return the difference
	int shrink_to_fit()
	{
		int difference = vector_capacity - vector_size;

		// Duplicate the current vector
		DataType* temp = new DataType[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			temp[i] = vector_data[i];
		}

		// Allocate new space for the vector
		vector_capacity = vector_size;

		delete[] vector_data;

		vector_data = new DataType[vector_capacity];

		// Place the data back into the vector
		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = temp[i];
		}

		// Reset the number of resizes
		vector_expansions = 0;

		delete[] temp;

		temp = nullptr;

		return difference;
	}


	// ELEMENT ACCESS

	// Returns the element at the given index
	DataType at(int index)
	{
		return vector_data[index];
	}

	// Returns the first element in the vector
	DataType front()
	{
		return vector_data[0];
	}

	// Returns the last element in the vector
	DataType back()
	{
		return vector_data[vector_size - 1];
	}


	// LOCATING ELEMENTS

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

	// Returns whether the vector contains at least one of the elements
	bool contains(DataType contained_data)
	{
		return find(contained_data) != -1;
	}

	// Returns whether the vector contains at least one of the elements, starting from the back
	bool contains_last(DataType contained_data)
	{
		return find_last(contained_data) != -1;
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


	// ADDING ELEMENTS

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

	// Adds a range of new elements at the end of the vector
	vector<DataType>& push_back_range(int array_length, DataType array[])
	{
		reserve(vector_size + array_length);

		for (int i = 0; i < array_length; i++)
		{
			push(array[i]);
		}

		return *this;
	}

	// Adds a range of new elements at the end of the vector
	vector<DataType>& push_back_range(int argc, DataType new_data ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		DataType* argv = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = new_data;

			new_data = va_arg(_va_list, DataType);
		}

		va_end(_va_list);

		reserve(vector_size + argc);

		for (int i = 0; i < argc; i++)
		{
			push(argv[i]);
		}

		delete[] argv;

		argv = nullptr;

		return *this;
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

	// Adds a range of new elements at the front of the vector
	vector<DataType>& push_range(int array_length, DataType array[])
	{
		reserve(vector_size + array_length);

		for (int i = 0; i < array_length; i++)
		{
			push_front(array[i]);
		}

		return *this;
	}

	// Adds a range of new elements at the front of the vector
	vector<DataType>& push_range(int argc, DataType new_data ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		DataType* argv = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = new_data;

			new_data = va_arg(_va_list, DataType);
		}

		va_end(_va_list);

		reserve(vector_size + argc);

		for (int i = 0; i < argc; i++)
		{
			push_front(argv[i]);
		}

		delete[] argv;

		argv = nullptr;

		return *this;
	}

	// Adds a new element in the vector at a given index and shift following elements forward
	vector<DataType>& insert(int index, DataType new_data)
	{
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


	// REMOVING ELEMENTS

	// Removes a element in the vector at a given index and shift following elements back
	DataType erase_at(int index)
	{
		// Decrease the vector size
		vector_size--;

		DataType data = vector_data[index];

		// Shift elements past the new index backward
		for (int i = index + 1; i <= vector_size; i++)
		{
			vector_data[i - 1] = vector_data[i];
		}

		return data;
	}

	// Removes the first of a given element in the vector
	int erase(DataType removed_data)
	{
		int index = find(removed_data);

		erase_at(index);

		return index;
	}

	// Removes the last of a given element in the vector
	int erase_last(DataType removed_data)
	{
		int index = find_last(removed_data);

		erase_at(index);

		return index;
	}

	// Remove and return the first element of the vector
	DataType erase_first()
	{
		if (vector_size == 0)
		{
			return DataType();
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
	DataType erase_last()
	{
		if (vector_size == 0)
		{
			return DataType();
		}

		vector_size--;

		return vector_data[vector_size];
	}

	// Removes all of the given element in the vector and returns the total elements removed
	int erase_all(DataType removed_data)
	{
		int total = 0;

		for (int i = 0; i < vector_size - 1; i++)
		{
			if (vector_data[i] == removed_data)
			{
				vector_data[i] = vector_data[i + 1];

				total++;

				i--;
			}
		}

		if (vector_data[vector_size - 1] == removed_data)
		{
			total++;
		}

		vector_size -= total;

		return total;
	}

	// Clears the vector's data with a new capacity
	int clear(int new_capacity = 1)
	{
		int total = vector_size;

		// Reset vector variables
		delete[] vector_data;

		vector_data = new DataType[new_capacity];

		vector_size = 0;

		vector_capacity = new_capacity;

		vector_expansions = 0;

		return total;
	}


	// ELEMENT OPERATIONS

	// Replaces the data at the given index with the given data
	DataType set(int index, DataType new_data)
	{
		// Replace the data at the index
		DataType data = vector_data[index];

		vector_data[index] = new_data;

		return data;
	}

	// Replaces the first of the found data with the given data
	int replace(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = find(replaced_data);

		// Check if the data was not found
		if (index == -1)
		{
			return index;
		}

		// Replace the data at the index
		vector_data[index] = new_data;

		return index;
	}

	// Replaces the last of the found data with the given data
	int replace_last(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = find_last(replaced_data);

		// Check if the data was not found
		if (index == -1)
		{
			return index;
		}

		// Replace the data at the index
		vector_data[index] = new_data;

		return index;
	}

	// Replaces all of the found data with the given data and returns the total number of replacements
	int replace_all(DataType replaced_data, DataType new_data)
	{
		int total = 0;

		for (int i = 0; i < vector_size; i++)
		{
			if (vector_data[i] == replaced_data)
			{
				vector_data[i] = new_data;

				total++;
			}
		}

		return total;
	}

	// Swaps two elements at two given indicies
	vector<DataType>& swap(int index1, int index2)
	{
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

	// Gets or sets the element at the given index
	DataType& operator[](int index)
	{
		return vector_data[index];
	}


	// VECTOR OPERATIONS

	// Assigns the vector's elements and capacity to the elements and capacity of another vector
	vector<DataType>& assign(vector<DataType>& new_data)
	{
		// Store the vector's size values
		vector_size = new_data.size();

		vector_capacity = vector_size;

		vector_expansions = 0;

		// Allocate the space from the new vector
		delete[] vector_data;

		vector_data = new DataType[vector_capacity];

		// Place the data back into the vector
		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = new_data[i];
		}

		return *this;
	}

	// Returns a copy of the vector's data
	vector<DataType> copy()
	{
		vector<DataType> new_vector = vector<DataType>(*this);

		return new_vector;
	}

	// Returns a slice of the vector from the start index for the number of elements
	vector<DataType> slice(int start, int count)
	{
		vector<DataType> slice = vector<DataType>(count);

		for (int i = start; i < start + count || i >= vector_size; i++)
		{
			slice.push(vector_data[i]);
		}

		return slice;
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

		delete[] vector_data;

		vector_data = new DataType[vector_capacity];

		// Place the vector elements at their shifted location using modulo
		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = temp[((i - number_of_shifts) % vector_size + vector_size) % vector_size];
		}

		delete[] temp;

		temp = nullptr;

		return *this;
	}

	// Shifts the vector elements left
	vector<DataType>& shift_left(int numberOfShifts)
	{
		return shift_right(-numberOfShifts);
	}

	// Bubble sorts the elements of the vector relative to the given sort order
	vector<DataType>& sort(SORT_TYPE array[])
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
				if (array[j] > array[j + 1])
				{
					// Swap the two vector elements
					swap(j, j + 1);

					// Swap the two sorting elements
					SORT_TYPE tempData = array[j];

					array[j] = array[j + 1];
					array[j + 1] = tempData;
				}
			}
		}

		return *this;
	}

	// Bubble sorts the elements of the vector relative to the given sort order
	vector<DataType>& sort(SORT_TYPE sort_order ...)
	{
		// Check length
		if (vector_size <= 1)
		{
			return *this;
		}

		va_list _va_list;

		va_start(_va_list, vector_size);

		SORT_TYPE* argv = new SORT_TYPE[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			argv[i] = sort_order;

			sort_order = va_arg(_va_list, SORT_TYPE);
		}

		va_end(_va_list);

		// Place the vector elements in the sorted order
		for (int i = 0; i < vector_size - 1; i++)
		{
			for (int j = 0; j < vector_size - i - 1; j++)
			{
				if (argv[j] > argv[j + 1])
				{
					// Swap the two vector elements
					swap(j, j + 1);

					// Swap the two sorting elements
					SORT_TYPE tempData = argv[j];

					argv[j] = argv[j + 1];
					argv[j + 1] = tempData;
				}
			}
		}

		delete[] argv;

		argv = nullptr;

		return *this;
	}

	// Bubble sorts the elements of the vector relative to the given sort order
	vector<DataType>& sort(vector<SORT_TYPE> sort_order)
	{
		DataType* array = sort_order.to_new_array();

		sort(array);

		delete[] array;

		return *this;
	}


	// TO STRING

	// Converts the elements of the vector into a string
	std::string to_string()
	{
		if (vector_size == 0)
		{
			return "{ }";
		}

		std::string log = "{ ";

		for (int i = 0; i < vector_size; i++)
		{
			log += std::to_string(vector_data[i]) + ", ";
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		return log;
	}
};

// Class used to store and dynamically reallocate an array for expanding storage.
template<typename DataType> class Vector
{
private:

	// VECTOR DATA

	// The array of the vector's data
	DataType* vectorData = nullptr;

	// The current number of elements in the array holding data
	int vectorSize = 0;

	// The current maximum size of the array before needing to expand
	int vectorCapacity = 1;

	// The number of array expansions
	int vectorExpansions = 0;

public:

	// TO ARRAY

	// Returns an array of the current vector (MUST BE DEALLOCATED)
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


	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	Vector()
	{
		vectorData = new DataType[1];

		vectorSize = 0;

		vectorCapacity = 1;

		vectorExpansions = 0;
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

	// Move constructor
	Vector(Vector<DataType>&& moved_vector) noexcept
	{
		vectorSize = moved_vector.vectorSize;

		vectorCapacity = moved_vector.vectorCapacity;

		vectorExpansions = 0;

		vectorData = new DataType[vectorCapacity];

		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = moved_vector.vectorData[i];
		}

		delete[] moved_vector.vectorData;

		moved_vector.vectorData = new DataType[1];

		moved_vector.vectorSize = 0;

		moved_vector.vectorCapacity = 1;

		moved_vector.vectorExpansions = 0;
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
	Vector(int array_length, DataType array[])
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

	// Varadic argument constructor
	Vector(int argc, DataType array ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		DataType* argv = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			argv.push_back(array);

			array = va_arg(_va_list, DataType);
		}

		va_end(_va_list);

		vectorData = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			vectorData[i] = argv[i];
		}

		vectorSize = argc;

		vectorCapacity = vectorSize;

		vectorExpansions = 0;

		delete argv;

		argv = nullptr;
	}

	// List constructor
	Vector(std::initializer_list<DataType> list)
	{
		vectorData = new DataType[list.size()];

		for (int i = 0; i < list.size(); i++)
		{
			vectorData[i] = *(list.begin() + i);
		}

		vectorSize = list.size();

		vectorCapacity = vectorSize;

		vectorExpansions = 0;
	}

	// Destructor
	virtual ~Vector()
	{
		delete[] vectorData;

		vectorData = nullptr;
	}


	// OPERATORS

	// Copy assignment operator
	Vector<DataType>& operator=(const Vector<DataType>& copied_vector)
	{
		vectorSize = copied_vector.vectorSize;

		vectorCapacity = copied_vector.vectorCapacity;

		vectorExpansions = 0;

		delete[] vectorData;

		vectorData = new DataType[vectorCapacity];

		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = copied_vector.vectorData[i];
		}

		return *this;
	}

	// Move assignment operator
	Vector<DataType>& operator=(Vector<DataType>&& moved_vector) noexcept
	{
		vectorSize = moved_vector.vectorSize;

		vectorCapacity = moved_vector.vectorCapacity;

		vectorExpansions = 0;

		delete[] vectorData;

		vectorData = new DataType[vectorCapacity];

		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = moved_vector.vectorData[i];
		}

		delete[] moved_vector.vectorData;

		moved_vector.vectorData = new DataType[1];

		moved_vector.vectorSize = 0;

		moved_vector.vectorCapacity = 1;

		moved_vector.vectorExpansions = 0;

		return *this;
	}


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

		// Allocate new space for the vector
		vectorCapacity *= 2;

		delete[] vectorData;

		vectorData = new DataType[vectorCapacity];

		// Place the data back into the vector
		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = temp[i];
		}

		delete[] temp;

		temp = nullptr;

		return *this;
	}


	// VECTOR EQUALITY

	// Check if another vector is equal to the vector
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

	// Check if another vector is equal to the vector
	bool operator ==(Vector<DataType> compared_vector)
	{
		return Equals(compared_vector);
	}

	// Check if another vector is not equal to the vector
	bool operator !=(Vector<DataType> compared_vector)
	{
		return !Equals(compared_vector);
	}


	// ITERATORS

	// Get a pointer to the beginning of the vector's array
	DataType* Begin()
	{
		return vectorData;
	}

	// Get a pointer to the end of the vector's array
	DataType* End()
	{
		return vectorData + (vectorSize - 1);
	}

	// Returns the pointer to the element at the given index
	DataType* Data(int index)
	{
		return vectorData + index;
	}


	// SIZE AND CAPACITY

	// Return the current size of the vector
	int Size()
	{
		return vectorSize;
	}

	// Return the maximum capacity of the vector before expanding
	int MaxSize()
	{
		return vectorCapacity;
	}

	// Return the total number of expansions
	int Reallocations()
	{
		return vectorExpansions;
	}

	// Return whether the vector is empty
	bool Empty()
	{
		return vectorSize == 0;
	}

	// Resizes the vector's size and removes out of bounds data or expands if necessary, returns the difference
	int Resize(int new_size)
	{
		// Check if the new size is identical
		if (vectorSize == new_size)
		{
			return 0;
		}

		int difference = new_size - vectorCapacity;

		// Duplicate the current vector
		DataType* temp = new DataType[vectorSize];

		for (int i = 0; i < vectorSize; i++)
		{
			temp[i] = vectorData[i];
		}

		// Expand the vector if needed
		if (new_size > vectorCapacity)
		{
			Reallocate();
		}

		// Allocate new space for the vector
		delete[] vectorData;

		vectorData = new DataType[vectorCapacity];

		vectorSize = new_size;

		// Place the data back into the vector
		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = temp[i];
		}

		delete[] temp;

		temp = nullptr;

		return difference;
	}

	// Expands the vector's's capacity enough to hold the given amount and return whether it was successful (does not reduce the capacity)
	bool Reserve(int new_capacity)
	{
		// Check if the new capacity is less
		if (new_capacity <= vectorCapacity)
		{
			return false;
		}

		// Advance the number of expansions
		vectorExpansions++;

		// Duplicate the current vector
		DataType* temp = new DataType[vectorSize];

		for (int i = 0; i < vectorSize; i++)
		{
			temp[i] = vectorData[i];
		}

		// Allocate new space for the vector
		vectorCapacity = new_capacity;

		delete[] vectorData;

		vectorData = new DataType[vectorCapacity];

		// Place the data back into the vector
		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = temp[i];
		}

		delete[] temp;

		temp = nullptr;

		return true;
	}

	// Expands the vector's capacity by the given amount and return the new capacity
	int Expand(int number_of_spaces)
	{
		Reserve(vectorCapacity + number_of_spaces);

		return vectorCapacity;
	}

	// Shrinks the capacity to the size and return the difference
	int ShrinkToFit()
	{
		int difference = vectorCapacity - vectorSize;

		// Duplicate the current vector
		DataType* temp = new DataType[vectorSize];

		for (int i = 0; i < vectorSize; i++)
		{
			temp[i] = vectorData[i];
		}

		// Allocate new space for the vector
		vectorCapacity = vectorSize;

		delete[] vectorData;

		vectorData = new DataType[vectorCapacity];

		// Place the data back into the vector
		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = temp[i];
		}

		// Reset the number of resizes
		vectorExpansions = 0;

		delete[] temp;

		temp = nullptr;

		return difference;
	}


	// ELEMENT ACCESS

	// Returns the element at the given index
	DataType At(int index)
	{
		return vectorData[index];
	}

	// Returns the first element in the vector
	DataType Front()
	{
		return vectorData[0];
	}

	// Returns the last element in the vector
	DataType Back()
	{
		return vectorData[vectorSize - 1];
	}


	// LOCATING ELEMENTS

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

	// Returns whether the vector contains at least one of the elements
	bool Contains(DataType contained_data)
	{
		return Find(contained_data) != -1;
	}

	// Returns whether the vector contains at least one of the elements, starting from the back
	bool ContainsLast(DataType contained_data)
	{
		return FindLast(contained_data) != -1;
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


	// ADDING ELEMENTS

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

	// Adds a range of new elements at the end of the vector
	Vector<DataType>& PushBackRange(int array_length, DataType array[])
	{
		Reserve(vectorSize + array_length);

		for (int i = 0; i < array_length; i++)
		{
			Push(array[i]);
		}

		return *this;
	}

	// Adds a range of new elements at the end of the vector
	Vector<DataType>& PushBackRange(int argc, DataType new_data ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		DataType* argv = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = new_data;

			new_data = va_arg(_va_list, DataType);
		}

		va_end(_va_list);

		Reserve(vectorSize + argc);

		for (int i = 0; i < argc; i++)
		{
			Push(argv[i]);
		}

		delete[] argv;

		argv = nullptr;

		return *this;
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

	// Adds a range of new elements at the front of the vector
	Vector<DataType>& PushRange(int array_length, DataType array[])
	{
		Reserve(vectorSize + array_length);

		for (int i = 0; i < array_length; i++)
		{
			push_front(array[i]);
		}

		return *this;
	}

	// Adds a range of new elements at the front of the vector
	Vector<DataType>& PushRange(int argc, DataType new_data ...)
	{
		va_list _va_list;

		va_start(_va_list, argc);

		DataType* argv = new DataType[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = new_data;

			new_data = va_arg(_va_list, DataType);
		}

		va_end(_va_list);

		Reserve(vectorSize + argc);

		for (int i = 0; i < argc; i++)
		{
			push_front(argv[i]);
		}

		delete[] argv;

		argv = nullptr;

		return *this;
	}

	// Adds a new element in the vector at a given index and shift following elements forward
	Vector<DataType>& Insert(int index, DataType new_data)
	{
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


	// REMOVING ELEMENTS

	// Removes a element in the vector at a given index and shift following elements back
	DataType EraseAt(int index)
	{
		// Decrease the vector size
		vectorSize--;

		DataType data = vectorData[index];

		// Shift elements past the new index backward
		for (int i = index + 1; i <= vectorSize; i++)
		{
			vectorData[i - 1] = vectorData[i];
		}

		return data;
	}

	// Removes the first of a given element in the vector
	int Erase(DataType removed_data)
	{
		int index = Find(removed_data);

		EraseAt(index);

		return index;
	}

	// Removes the last of a given element in the vector
	int EraseLast(DataType removed_data)
	{
		int index = FindLast(removed_data);

		EraseAt(index);

		return index;
	}

	// Remove and return the first element of the vector
	DataType EraseFirst()
	{
		if (vectorSize == 0)
		{
			return DataType();
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
	DataType EraseLast()
	{
		if (vectorSize == 0)
		{
			return DataType();
		}

		vectorSize--;

		return vectorData[vectorSize];
	}

	// Removes all of the given element in the vector and returns the total elements removed
	int EraseAll(DataType removed_data)
	{
		int total = 0;

		for (int i = 0; i < vectorSize - 1; i++)
		{
			if (vectorData[i] == removed_data)
			{
				vectorData[i] = vectorData[i + 1];

				total++;

				i--;
			}
		}

		if (vectorData[vectorSize - 1] == removed_data)
		{
			total++;
		}

		vectorSize -= total;

		return total;
	}

	// Clears the vector's data with a new capacity
	int Clear(int new_capacity = 1)
	{
		int total = vectorSize;

		// Reset vector variables
		delete[] vectorData;

		vectorData = new DataType[new_capacity];

		vectorSize = 0;

		vectorCapacity = new_capacity;

		vectorExpansions = 0;

		return total;
	}


	// ELEMENT OPERATIONS

	// Replaces the data at the given index with the given data
	DataType Set(int index, DataType new_data)
	{
		// Replace the data at the index
		DataType data = vectorData[index];

		vectorData[index] = new_data;

		return data;
	}

	// Replaces the first of the found data with the given data
	int Replace(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = Find(replaced_data);

		// Check if the data was not found
		if (index == -1)
		{
			return index;
		}

		// Replace the data at the index
		vectorData[index] = new_data;

		return index;
	}

	// Replaces the last of the found data with the given data
	int ReplaceLast(DataType replaced_data, DataType new_data)
	{
		// Find the index of the found data
		int index = FindLast(replaced_data);

		// Check if the data was not found
		if (index == -1)
		{
			return index;
		}

		// Replace the data at the index
		vectorData[index] = new_data;

		return index;
	}

	// Replaces all of the found data with the given data and returns the total number of replacements
	int ReplaceAll(DataType replaced_data, DataType new_data)
	{
		int total = 0;

		for (int i = 0; i < vectorSize; i++)
		{
			if (vectorData[i] == replaced_data)
			{
				vectorData[i] = new_data;

				total++;
			}
		}

		return total;
	}

	// Swaps two elements at two given indicies
	Vector<DataType>& Swap(int index1, int index2)
	{
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

	// Gets or sets the element at the given index
	DataType& operator[](int index)
	{
		return vectorData[index];
	}


	// VECTOR OPERATIONS

	// Assigns the vector's elements and capacity to the elements and capacity of another vector
	Vector<DataType>& Assign(Vector<DataType>& new_data)
	{
		// Store the vector's size values
		vectorSize = new_data.Size();

		vectorCapacity = vectorSize;

		vectorExpansions = 0;

		// Allocate the space from the new vector
		delete[] vectorData;

		vectorData = new DataType[vectorCapacity];

		// Place the data back into the vector
		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = new_data[i];
		}

		return *this;
	}

	// Returns a copy of the vector's data
	Vector<DataType> Copy()
	{
		Vector<DataType> new_vector = Vector<DataType>(*this);

		return new_vector;
	}

	// Returns a slice of the vector from the start index for the number of elements
	Vector<DataType> Slice(int start, int count)
	{
		Vector<DataType> slice = Vector<DataType>(count);

		for (int i = start; i < start + count || i >= vectorSize; i++)
		{
			slice.Push(vectorData[i]);
		}

		return slice;
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

		delete[] vectorData;

		vectorData = new DataType[vectorCapacity];

		// Place the vector elements at their shifted location using modulo
		for (int i = 0; i < vectorSize; i++)
		{
			vectorData[i] = temp[((i - number_of_shifts) % vectorSize + vectorSize) % vectorSize];
		}

		delete[] temp;

		temp = nullptr;

		return *this;
	}

	// Shifts the vector elements left
	Vector<DataType>& ShiftLeft(int numberOfShifts)
	{
		return ShiftRight(-numberOfShifts);
	}

	// Bubble sorts the elements of the vector relative to the given sort order
	Vector<DataType>& Sort(SORT_TYPE array[])
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
				if (array[j] > array[j + 1])
				{
					// Swap the two vector elements
					Swap(j, j + 1);

					// Swap the two sorting elements
					SORT_TYPE tempData = array[j];

					array[j] = array[j + 1];
					array[j + 1] = tempData;
				}
			}
		}

		return *this;
	}

	// Bubble sorts the elements of the vector relative to the given sort order
	Vector<DataType>& Sort(SORT_TYPE sort_order ...)
	{
		// Check length
		if (vectorSize <= 1)
		{
			return *this;
		}

		va_list _va_list;

		va_start(_va_list, vectorSize);

		SORT_TYPE* argv = new SORT_TYPE[vectorSize];

		for (int i = 0; i < vectorSize; i++)
		{
			argv[i] = sort_order;

			sort_order = va_arg(_va_list, SORT_TYPE);
		}

		va_end(_va_list);

		// Place the vector elements in the sorted order
		for (int i = 0; i < vectorSize - 1; i++)
		{
			for (int j = 0; j < vectorSize - i - 1; j++)
			{
				if (argv[j] > argv[j + 1])
				{
					// Swap the two vector elements
					Swap(j, j + 1);

					// Swap the two sorting elements
					SORT_TYPE tempData = argv[j];

					argv[j] = argv[j + 1];
					argv[j + 1] = tempData;
				}
			}
		}

		delete[] argv;

		argv = nullptr;

		return *this;
	}

	// Bubble sorts the elements of the vector relative to the given sort order
	Vector<DataType>& Sort(Vector<SORT_TYPE> sort_order)
	{
		DataType* array = sort_order.ToNewArray();

		sort(array);

		delete[] array;

		return *this;
	}


	// TO STRING

	// Converts the elements of the vector into a string
	std::string ToString()
	{
		if (vectorSize == 0)
		{
			return "{ }";
		}

		std::string log = "{ ";

		for (int i = 0; i < vectorSize; i++)
		{
			log += std::to_string(vectorData[i]) + ", ";
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		return log;
	}
};
