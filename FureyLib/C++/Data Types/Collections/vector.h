
// Vector Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/vector/vector/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=net-8.0

#pragma once
#include <string>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the class
#include "vector.h"

// The default data type used for sorting
#define SORT_TYPE float

// Class used to store and dynamically reallocate an array for expanding storage.
template<typename data_type> class vector
{
private:

	// VARIABLES

	// The array of the vector's data
	data_type* vector_data = nullptr;

	// The current number of elements in the array holding data
	int vector_size = 0;

	// The current maximum size of the array before needing to expand
	int vector_capacity = 1;

	// The number of array expansions
	int vector_expansions = 0;


	// REALLOCATE MEMORY

	// Expands the capacity based on how many times it has been expanded
	vector<data_type>& reallocate()
	{
		vector_expansions++;

		data_type* temp = new data_type[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			temp[i] = vector_data[i];
		}

		vector_capacity *= 2;

		delete[] vector_data;

		vector_data = new data_type[vector_capacity];

		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = temp[i];
		}

		delete[] temp;

		temp = nullptr;

		return *this;
	}

public:

	// TO ARRAY

	// Returns an array of the current vector (MUST BE DEALLOCATED)
	data_type* to_new_array()
	{
		if (vector_size == 0)
		{
			return nullptr;
		}

		data_type* new_array = new data_type[vector_size];

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
		vector_data = new data_type[1];

		vector_size = 0;

		vector_capacity = 1;

		vector_expansions = 0;
	}

	// Copy constructor
	vector(const vector<data_type>& copied_vector)
	{
		vector_size = copied_vector.vector_size;

		vector_capacity = copied_vector.vector_capacity;

		vector_expansions = 0;

		vector_data = new data_type[vector_capacity];

		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = copied_vector.vector_data[i];
		}
	}

	// Move constructor
	vector(vector<data_type>&& moved_vector) noexcept
	{
		vector_size = moved_vector.vector_size;

		vector_capacity = moved_vector.vector_capacity;

		vector_expansions = 0;

		vector_data = new data_type[vector_capacity];

		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = moved_vector.vector_data[i];
		}

		delete[] moved_vector.vector_data;

		moved_vector.vector_data = new data_type[1];

		moved_vector.vector_size = 0;

		moved_vector.vector_capacity = 1;

		moved_vector.vector_expansions = 0;
	}

	// Capacity constructor
	vector(int max_capacity)
	{
		vector_data = new data_type[max_capacity];

		vector_size = 0;

		vector_capacity = max_capacity;

		vector_expansions = 0;
	}

	// Fill constructor
	vector(int size_and_capacity, data_type new_data)
	{
		vector_data = new data_type[size_and_capacity];

		for (int i = 0; i < size_and_capacity; i++)
		{
			vector_data[i] = new_data;
		}

		vector_size = size_and_capacity;

		vector_capacity = vector_size;

		vector_expansions = 0;
	}

	// Array constructor
	vector(int array_length, data_type array[])
	{
		vector_data = new data_type[array_length];

		for (int i = 0; i < array_length; i++)
		{
			vector_data[i] = array[i];
		}

		vector_size = array_length;

		vector_capacity = vector_size;

		vector_expansions = 0;
	}

	// Array constructor
	vector(int argc, data_type array ...)
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

		vector_data = new data_type[argc];

		for (int i = 0; i < argc; i++)
		{
			vector_data[i] = argv[i];
		}

		vector_size = argc;

		vector_capacity = vector_size;

		vector_expansions = 0;

		delete[] argv;

		argv = nullptr;
	}

	// List constructor
	vector(std::initializer_list<data_type> list)
	{
		vector_data = new data_type[list.size()];

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
	vector<data_type>& operator=(const vector<data_type>& copied_vector)
	{
		vector_size = copied_vector.vector_size;

		vector_capacity = copied_vector.vector_capacity;

		vector_expansions = 0;

		delete[] vector_data;

		vector_data = new data_type[vector_capacity];

		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = copied_vector.vector_data[i];
		}

		return *this;
	}

	// Move assignment operator
	vector<data_type>& operator=(vector<data_type>&& moved_vector) noexcept
	{
		vector_size = moved_vector.vector_size;

		vector_capacity = moved_vector.vector_capacity;

		vector_expansions = 0;

		delete[] vector_data;

		vector_data = new data_type[vector_capacity];

		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = moved_vector.vector_data[i];
		}

		delete[] moved_vector.vector_data;

		moved_vector.vector_data = new data_type[1];

		moved_vector.vector_size = 0;

		moved_vector.vector_capacity = 1;

		moved_vector.vector_expansions = 0;

		return *this;
	}


	// EQUALITY

	// Check if another vector is equal to the vector
	bool equals(vector<data_type>& compared_vector)
	{
		if (vector_size != compared_vector.vector_size)
		{
			return false;
		}

		for (int i = 0; i < vector_size; i++)
		{
			if (vector_data[i] != compared_vector[i])
			{
				return false;
			}
		}

		return true;
	}

	// Check if another vector is equal to the vector
	bool operator ==(vector<data_type>& compared_vector)
	{
		return equals(compared_vector);
	}

	// Check if another vector is not equal to the vector
	bool operator !=(vector<data_type>& compared_vector)
	{
		return !equals(compared_vector);
	}


	// ITERATORS

	// Get a pointer to the beginning of the vector's array
	data_type* begin()
	{
		return vector_data;
	}

	// Get a pointer to the end of the vector's array
	data_type* end()
	{
		return vector_data + (vector_size - 1);
	}


	// CAPACITY

	// Returns the current size of the vector
	int size()
	{
		return vector_size;
	}

	// Returns the maximum capacity of the vector before expanding
	int max_size()
	{
		return vector_capacity;
	}

	// Returns the total number of expansions
	int reallocations()
	{
		return vector_expansions;
	}

	// Resizes the vector's size and removes out of bounds data or expands if necessary, returns the difference
	int resize(int new_size)
	{
		if (vector_size == new_size)
		{
			return 0;
		}

		int difference = new_size - vector_capacity;

		data_type* temp = new data_type[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			temp[i] = vector_data[i];
		}

		if (new_size > vector_capacity)
		{
			reallocate();
		}

		delete[] vector_data;

		vector_data = new data_type[vector_capacity];

		vector_size = new_size;

		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = temp[i];
		}

		delete[] temp;

		temp = nullptr;

		return difference;
	}

	// Returns whether the vector is empty
	bool empty()
	{
		return vector_size == 0;
	}

	// Expands the vector's capacity enough to hold the given amount and return whether it was successful (does not reduce the capacity)
	bool reserve(int new_capacity)
	{
		if (new_capacity <= vector_capacity)
		{
			return false;
		}

		vector_expansions++;

		data_type* temp = new data_type[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			temp[i] = vector_data[i];
		}

		vector_capacity = new_capacity;

		delete[] vector_data;

		vector_data = new data_type[vector_capacity];

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

		data_type* temp = new data_type[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			temp[i] = vector_data[i];
		}

		vector_capacity = vector_size;

		delete[] vector_data;

		vector_data = new data_type[vector_capacity];

		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = temp[i];
		}

		vector_expansions = 0;

		delete[] temp;

		temp = nullptr;

		return difference;
	}


	// ELEMENT ACCESS

	// Gets or sets the element at the given index
	data_type& operator[](int index)
	{
		return vector_data[index];
	}

	// Returns the element at the given index
	data_type at(int index)
	{
		return vector_data[index];
	}

	// Returns the first element in the vector
	data_type front()
	{
		return vector_data[0];
	}

	// Returns the last element in the vector
	data_type back()
	{
		return vector_data[vector_size - 1];
	}

	// Returns a reference to the element at the given index
	data_type& data(int index)
	{
		return *(vector_data + index);
	}


	// LOCATING ELEMENTS

	// Returns the first index of the given data in the vector, returns -1 if nothing matched
	int find(data_type found_data)
	{
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
	int find_last(data_type found_data)
	{
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
	bool contains(data_type contained_data)
	{
		return find(contained_data) != -1;
	}

	// Returns the total number of instances of the given data in the vector
	int count(data_type found_data)
	{
		int count = 0;

		for (int i = 0; i < vector_size; i++)
		{
			if (vector_data[i] == found_data)
			{
				count++;
			}
		}

		return count;
	}


	// MODIFIERS

	// Assigns the vector's elements and capacity to the elements and capacity of another vector
	vector<data_type>& assign(vector<data_type>& new_data)
	{
		vector_size = new_data.size();

		vector_capacity = vector_size;

		vector_expansions = 0;

		delete[] vector_data;

		vector_data = new data_type[vector_capacity];

		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = new_data[i];
		}

		return *this;
	}

	// Adds a new element at the end of the vector
	vector<data_type>& push_back(data_type new_data)
	{
		if (vector_size + 1 > vector_capacity)
		{
			reallocate();
		}

		vector_size++;

		vector_data[vector_size - 1] = new_data;

		return *this;
	}

	// Remove and return the last element of the vector
	data_type pop_back()
	{
		if (vector_size == 0)
		{
			return data_type();
		}

		vector_size--;

		return vector_data[vector_size];
	}

	// Adds a new element at the front of the vector
	vector<data_type>& push(data_type new_data)
	{
		if (vector_size + 1 > vector_capacity)
		{
			reallocate();
		}

		vector_size++;

		for (int i = vector_size - 1; i >= 1; i--)
		{
			vector_data[i] = vector_data[i - 1];
		}

		vector_data[0] = new_data;

		return *this;
	}

	// Remove and return the first element of the vector
	data_type pop()
	{
		if (vector_size == 0)
		{
			return data_type();
		}

		vector_size--;

		data_type new_data = vector_data[0];

		for (int i = 1; i <= vector_size; i++)
		{
			vector_data[i - 1] = vector_data[i];
		}

		return new_data;
	}

	// Adds a new element in the vector at a given index and shift following elements forward
	vector<data_type>& insert(int index, data_type new_data)
	{
		if (vector_size + 1 > vector_capacity)
		{
			reallocate();
		}

		vector_size++;

		for (int i = vector_size - 1; i >= index; i--)
		{
			vector_data[i] = vector_data[i - 1];
		}

		vector_data[index] = new_data;

		return *this;
	}

	// Removes a element in the vector at a given index and shift following elements back
	data_type erase(int index)
	{
		vector_size--;

		data_type data = vector_data[index];

		for (int i = index + 1; i <= vector_size; i++)
		{
			vector_data[i - 1] = vector_data[i];
		}

		return data;
	}

	// Removes the first of a given element in the vector
	int erase_first(data_type removed_data)
	{
		int index = find(removed_data);

		if (index != -1)
		{
			erase(index);
		}

		return index;
	}

	// Removes the last of a given element in the vector
	int erase_last(data_type removed_data)
	{
		int index = find_last(removed_data);

		if (index != -1)
		{
			erase(index);
		}

		return index;
	}

	// Swaps two elements at two given indicies
	vector<data_type>& swap(int index1, int index2)
	{
		if (index1 == index2)
		{
			return *this;
		}

		data_type temp = vector_data[index2];

		vector_data[index2] = vector_data[index1];

		vector_data[index1] = temp;

		return *this;
	}

	// Clears the vector's data with a new capacity
	int clear(int new_capacity = 1)
	{
		int total = vector_size;

		delete[] vector_data;

		vector_data = new data_type[new_capacity];

		vector_size = 0;

		vector_capacity = new_capacity;

		vector_expansions = 0;

		return total;
	}

	// Creates a new element in the vector at a given index and shift following elements forward
	template<typename ... argument_types> vector<data_type>& emplace(int index, argument_types ... arguments)
	{
		if (vector_size + 1 > vector_capacity)
		{
			reallocate();
		}

		vector_size++;

		for (int i = vector_size - 1; i >= index; i--)
		{
			vector_data[i] = vector_data[i - 1];
		}

		vector_data[index] = data_type(arguments...);

		return *this;
	}

	// Creates a new element at the end of the vector
	template<typename ... argument_types> vector<data_type>& emplace_back(argument_types ... arguments)
	{
		if (vector_size + 1 > vector_capacity)
		{
			reallocate();
		}

		vector_size++;

		vector_data[vector_size - 1] = data_type(arguments...);

		return *this;
	}

	// Creates a new element at the front of the vector
	template<typename ... argument_types> vector<data_type>& emplace_front(argument_types ... arguments)
	{
		if (vector_size + 1 > vector_capacity)
		{
			reallocate();
		}

		vector_size++;

		for (int i = vector_size - 1; i >= 1; i--)
		{
			vector_data[i] = vector_data[i - 1];
		}

		vector_data[0] = data_type(arguments...);

		return *this;
	}


	// ELEMENT OPERATIONS

	// Replaces the data at the given index with the given data
	data_type set(int index, data_type new_data)
	{
		data_type data = vector_data[index];

		vector_data[index] = new_data;

		return data;
	}

	// Replaces the first of the found data with the given data
	int replace(data_type replaced_data, data_type new_data)
	{
		int index = find(replaced_data);

		if (index == -1)
		{
			return index;
		}

		vector_data[index] = new_data;

		return index;
	}

	// Replaces the last of the found data with the given data
	int replace_last(data_type replaced_data, data_type new_data)
	{
		int index = find_last(replaced_data);

		if (index == -1)
		{
			return index;
		}

		vector_data[index] = new_data;

		return index;
	}

	// Replaces all of the found data with the given data and returns the total number of replacements
	int replace_all(data_type replaced_data, data_type new_data)
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


	// OPERATIONS

	// Removes all of the given element in the vector and returns the total elements removed
	int remove(data_type removed_data)
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

	// Bubble sorts the elements of the vector relative to the given sort order
	template<typename sort_type = SORT_TYPE> vector<data_type>& sort(sort_type array[])
	{
		if (vector_size <= 1)
		{
			return *this;
		}

		for (int i = 0; i < vector_size - 1; i++)
		{
			for (int j = 0; j < vector_size - i - 1; j++)
			{
				if (array[j] > array[j + 1])
				{
					swap(j, j + 1);

					sort_type tempData = array[j];

					array[j] = array[j + 1];

					array[j + 1] = tempData;
				}
			}
		}

		return *this;
	}

	// Bubble sorts the elements of the vector relative to the given sort order
	template<typename sort_type = SORT_TYPE> vector<data_type>& sort(sort_type sort_order ...)
	{
		if (vector_size <= 1)
		{
			return *this;
		}

		va_list _va_list;

		va_start(_va_list, vector_size);

		sort_type* argv = new sort_type[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			argv[i] = sort_order;

			sort_order = va_arg(_va_list, sort_type);
		}

		va_end(_va_list);

		for (int i = 0; i < vector_size - 1; i++)
		{
			for (int j = 0; j < vector_size - i - 1; j++)
			{
				if (argv[j] > argv[j + 1])
				{
					swap(j, j + 1);

					sort_type tempData = argv[j];

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
	template<typename sort_type = SORT_TYPE> vector<data_type>& sort(vector<sort_type>& sort_order)
	{
		data_type* array = sort_order.to_new_array();

		sort(array);

		delete[] array;

		array = nullptr;

		return *this;
	}

	// Reverse the vector elements
	vector<data_type>& reverse()
	{
		if (vector_size <= 1)
		{
			return *this;
		}

		for (int i = 0; i < vector_size / 2; i++)
		{
			swap(i, vector_size - i - 1);
		}

		return *this;
	}

	// Swaps the vector's elements and capacity with the elements and capacity of another vector
	vector<data_type>& swap(vector<data_type>& swapped_data)
	{
		data_type* data = vector_data;

		int count = vector_size;

		int capacity = vector_capacity;

		int expansions = vector_expansions;

		vector_data = swapped_data.vector_data;

		vector_size = swapped_data.vector_size;

		vector_capacity = swapped_data.vector_capacity;

		vector_expansions = swapped_data.vector_expansions;

		swapped_data.vector_data = data;

		swapped_data.vector_size = count;

		swapped_data.vector_capacity = capacity;

		swapped_data.vector_expansions = expansions;

		return this;
	}

	// Returns a copy of the vector's data
	vector<data_type> copy()
	{
		return vector<data_type>(*this);
	}

	// Returns a slice of the vector from the start index for the number of elements
	vector<data_type> slice(int start, int count)
	{
		vector<data_type> slice = vector<data_type>(count);

		for (int i = start; i < start + count || i >= vector_size; i++)
		{
			slice.push(vector_data[i]);
		}

		return slice;
	}

	// Shifts the vector elements right
	vector<data_type>& shift_right(int number_of_shifts)
	{
		if (vector_size <= 1)
		{
			return *this;
		}

		if (number_of_shifts % vector_size == 0)
		{
			return *this;
		}

		data_type* temp = new data_type[vector_size];

		for (int i = 0; i < vector_size; i++)
		{
			temp[i] = vector_data[i];
		}

		delete[] vector_data;

		vector_data = new data_type[vector_capacity];

		for (int i = 0; i < vector_size; i++)
		{
			vector_data[i] = temp[((i - number_of_shifts) % vector_size + vector_size) % vector_size];
		}

		delete[] temp;

		temp = nullptr;

		return *this;
	}

	// Shifts the vector elements left
	vector<data_type>& shift_left(int numberOfShifts)
	{
		return shift_right(-numberOfShifts);
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
			log += (vector_data[i] + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		return log;
	}

	// Converts the elements of the vector into a string
	std::string to_string(std::string(*to_string_function) (data_type))
	{
		if (vector_size == 0)
		{
			return "{ }";
		}

		std::string log = "{ ";

		for (int i = 0; i < vector_size; i++)
		{
			log += (to_string_function(vector_data[i]) + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		return log;
	}
};
