
// Map Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/map/map/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.dictionary-2?view=net-8.0

#pragma once
#include <string>
#include <vector>
#include <list>
#include <set>
#include <initializer_list>

// Include this heading to use the class
#include "map.h"

// Structure that represents a readonly pair of objects with one acting as the key to lookup the corresponding value object.
template<typename key_type, typename value_type> struct key_value_pair
{
public:

	// VARIABLES

	// The key object (used to find the value object)
	key_type first;

	// The value object (located using the key object)
	mutable value_type second;


	// CONSTRUCTORS

	// Default constructor
	key_value_pair()
	{
		first = key_type();

		second = value_type();
	}

	// Key value constructor
	key_value_pair(key_type key, value_type value)
	{
		first = key;

		second = value;
	}

	// Copy constructor
	key_value_pair(const key_value_pair& copied)
	{
		first = copied.first;

		second = copied.second;
	}


	// EQUALITY OPERATORS

	// Determines if this pair's key is less than another pair's key
	bool operator<(const key_value_pair<key_type, value_type>& pair) const noexcept
	{
		return first < pair.first;
	}

	// Check if the given pair's key matches this pair's key
	bool operator==(key_value_pair pair)
	{
		return *this->first == pair.first;
	}

	// Check if the given pair's key does not matches this pair's key
	bool operator!=(key_value_pair pair)
	{
		return *this->first != pair.first;
	}


	// TO STRING

	// Returns a string representation of this key value pair
	std::string to_string()
	{
		return "{ " + first + " : " + second + " }";
	}

	// Returns a string representation of this key value pair
	std::string to_string(std::string(*key_to_string_function) (key_type))
	{
		return "{ " + key_to_string_function(first) + " : " + second + " }";
	}

	// Returns a string representation of this key value pair
	std::string to_string(std::string(*key_to_string_function) (key_type), std::string(*value_to_string_function) (value_type))
	{
		return "{ " + key_to_string_function(first) + " : " + value_to_string_function(second) + " }";
	}
};

// Class used for fast access to value objects based on unique corresponding key objects.
template<typename key_type, typename value_type> class map
{
private:

	// VARIABLES

	// A binary tree storing each unique key object and its value object
	std::set<key_value_pair<key_type, value_type>> my_map = std::set<key_value_pair<key_type, value_type>>();

public:

	// TO ARRAY AND LIST

	// Returns a new array of the current map (must be deallocated)
	key_value_pair<key_type, value_type>* to_new_array()
	{
		key_value_pair<key_type, value_type>* new_array = new key_value_pair<key_type, value_type>[my_map.size()];

		int i = 0;

		for (key_value_pair<key_type, value_type> pair : my_map)
		{
			new_array[i] = pair;

			i++;
		}

		return new_array;
	}

	// Returns a list of the current map
	std::vector<key_value_pair<key_type, value_type>> to_vector()
	{
		std::vector<key_value_pair<key_type, value_type>> new_vector = std::vector<key_value_pair<key_type, value_type>>();

		for (key_value_pair<key_type, value_type> pair : my_map)
		{
			new_vector.push_back(pair);
		}

		return new_vector;
	}

	// Returns a new array of the current map's keys (must be deallocated)
	key_type* keys_to_new_array()
	{
		key_type* new_array = new key_type[my_map.size()];

		int i = 0;

		for (key_value_pair<key_type, value_type> pair : my_map)
		{
			new_array[i] = pair.first;

			i++;
		}

		return new_array;
	}

	// Returns a list of the current map's keys
	std::vector<key_type> keys_to_vector()
	{
		std::vector<key_type> new_vector = std::vector<key_type>();

		for (key_value_pair<key_type, value_type> pair : my_map)
		{
			new_vector.push_back(pair.first);
		}

		return new_vector;
	}

	// Returns a new array of the current map's values (must be deallocated)
	value_type* values_to_new_array()
	{
		value_type* new_array = new value_type[my_map.size()];

		int i = 0;

		for (key_value_pair<key_type, value_type> pair : my_map)
		{
			new_array[i] = pair.second;

			i++;
		}

		return new_array;
	}

	// Returns a list of the current map's values
	std::vector<value_type> values_to_vector()
	{
		std::vector<value_type> new_vector = std::vector<value_type>();

		for (key_value_pair<key_type, value_type> pair : my_map)
		{
			new_vector.push_back(pair.second);
		}

		return new_vector;
	}


	// CONSTRUCTORS

	// Default constructor
	map()
	{
		my_map = std::set<key_value_pair<key_type, value_type>>();
	}

	// Copy constructor
	map(const map<key_type, value_type>& copied_map)
	{
		my_map = std::set<key_value_pair<key_type, value_type>>(copied_map.my_map);
	}

	// Move constructor
	map(map<key_type, value_type>&& moved_map) noexcept
	{
		my_map = moved_map.my_map;

		moved_map.my_map = std::set<key_value_pair<key_type, value_type>>();
	}

	// Key value constructor
	map(key_type key, value_type value)
	{
		my_map = std::set<key_value_pair<key_type, value_type>>();

		my_map.insert(key_value_pair<key_type, value_type>(key, value));
	}

	// Key value tuple constructor
	map(std::initializer_list<std::tuple<key_type, value_type>> pairs)
	{
		my_map = std::list<key_value_pair<key_type, value_type>>();

		for (int i = 0; i < pairs.size(); i++)
		{
			key_value_pair<key_type, value_type> pair = key_value_pair<key_type, value_type>(std::get<0>(*(pairs.begin() + i)), std::get<1>(*(pairs.begin() + i)));

			my_map.insert(pair);
		}
	}


	// OPERATORS

	// Copy assignment operator
	map<key_type, value_type>& operator=(const map<key_type, value_type>& copied_map)
	{
		my_map = std::set<key_value_pair<key_type, value_type>>(copied_map.my_map);

		return *this;
	}

	// Move assignment operator
	map<key_type, value_type>& operator=(map<key_type, value_type>&& moved_map) noexcept
	{
		my_map = moved_map.my_map;

		moved_map.my_map = std::set<key_value_pair<key_type, value_type>>();

		return *this;
	}


	// EQUALITY

	// Check if another map is equal to the map
	bool equals(map<key_type, value_type>& compared_map)
	{
		return my_map == compared_map.my_map;
	}

	// Check if another map is equal to the map
	bool operator==(map<key_type, value_type>& compared_map)
	{
		return equals(compared_map);
	}

	// Check if another map is not equal to the map
	bool operator!=(map<key_type, value_type>& compared_map)
	{
		return !equals(compared_map);
	}


	// CAPACITY

	// Returns whether the map is empty
	bool empty()
	{
		return my_map.size() == 0;
	}

	// Returns the current number of pairs in the map
	int size()
	{
		return my_map.size();
	}


	// ELEMENT ACCESS

	// Gets or sets the value with the given key.
	// Note: This operator will NOT throw an exception if a new key is accessed.
	// It will instead create a new default-initialized value for that key.
	value_type& operator[](key_type key)
	{
		auto result = my_map.find(key_value_pair<key_type, value_type>(key, value_type()));

		if (result != std::end(my_map))
		{
			return result->second;
		}
		else
		{
			key_value_pair<key_type, value_type> new_pair = key_value_pair<key_type, value_type>(key, value_type());

			my_map.insert(new_pair);

			return my_map.find(new_pair)->second;
		}
	}

	// Returns the value with the given key
	value_type at(key_type key)
	{
		auto result = my_map.find(key_value_pair<key_type, value_type>(key, value_type()));

		if (result != std::end(my_map))
		{
			return result->second;
		}
		else
		{
			throw std::exception();
		}
	}

	// Returns the value with the given key if it exists
	bool try_get(key_type key, value_type& value)
	{
		auto result = my_map.find(key_value_pair<key_type, value_type>(key, value_type()));

		if (result != std::end(my_map))
		{
			value = result->second;

			return true;
		}
		else
		{
			value = value_type();

			return false;
		}
	}


	// LOCATING ELEMENTS

	// Returns whether the map contains the given key
	bool contains_key(key_type key)
	{
		return my_map.count(key_value_pair<key_type, value_type>(key, value_type()));
	}

	// Returns whether the map contains at least one of the given value
	bool contains_value(value_type value)
	{
		for (key_value_pair<key_type, value_type> pair : my_map)
		{
			if (pair.second == value)
			{
				return true;
			}
		}

		return false;
	}

	// Returns the total number of the given value in the map
	int count(value_type value)
	{
		int total = 0;

		for (key_value_pair<key_type, value_type> pair : my_map)
		{
			if (pair.second == value)
			{
				total++;
			}
		}

		return total;
	}


	// MODIFIERS

	// Assigns the map's data from another map's data
	map<key_type, value_type>& assign(map<key_type, value_type>& new_data)
	{
		my_map = std::set<key_value_pair<key_type, value_type>>(new_data.my_map);

		return *this;
	}

	// Adds a new value or replaces an existing value in the map at the given key
	map<key_type, value_type>& insert(key_type key, value_type value)
	{
		key_value_pair<key_type, value_type> pair = key_value_pair<key_type, value_type>(key, value);

		// Ensures the value is replaced
		my_map.erase(pair);

		my_map.insert(pair);

		return *this;
	}

	// Attempts to add a new value to the map at the given key but does not replace any existing values
	bool try_insert(key_type key, value_type value)
	{
		if (contains_key(key))
		{
			return false;
		}

		insert(key, value);

		return true;
	}

	// Removes a value from the map at the given key
	value_type erase(key_type key)
	{
		value_type value;

		if (try_get(key, value))
		{
			my_map.erase(key_value_pair<key_type, value_type>(key, value));

			return value;
		}
		else
		{
			return value_type();
		}
	}

	// Swaps the map's data with the data of another map
	map<key_type, value_type>& swap(map<key_type, value_type>& swapped_data)
	{
		std::set<key_value_pair<key_type, value_type>> swapped_map = swapped_data.my_map;

		swapped_data.my_map = my_map;

		my_map = swapped_map;

		return *this;
	}

	// Clears the map's data
	int clear()
	{
		int count = my_map.size();

		my_map.clear();

		return count;
	}


	// TO STRING

	// Converts the keys and values of the map into a string
	std::string to_string()
	{
		if (my_map.size() == 0)
		{
			return "{ }";
		}

		std::string log = "{ ";

		for (key_value_pair<key_type, value_type> pair : my_map)
		{
			log += (pair.first + " : " + pair.second + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		return log;
	}

	// Converts the keys and values of the map into a string
	std::string to_string(std::string(*key_to_string_function) (key_type))
	{
		if (my_map.size() == 0)
		{
			return "{ }";
		}

		std::string log = "{ ";

		for (key_value_pair<key_type, value_type> pair : my_map)
		{
			log += (key_to_string_function(pair.first) + " : " + pair.second + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		return log;
	}

	// Converts the keys and values of the map into a string
	std::string to_string(std::string(*key_to_string_function) (key_type), std::string(*value_to_string_function) (value_type))
	{
		if (my_map.size() == 0)
		{
			return "{ }";
		}

		std::string log = "{ ";

		for (key_value_pair<key_type, value_type> pair : my_map)
		{
			log += (key_to_string_function(pair.first) + " : " + value_to_string_function(pair.second) + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		return log;
	}
};
