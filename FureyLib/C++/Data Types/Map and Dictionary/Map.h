
// Map Data Type Class
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/map/map/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.dictionary-2?view=net-8.0

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
#include <any>

// Map Class
template <class KeyType, class ValueType> class map
{
private:

	// KEY VALUE CLASS
	class key_value_pair
	{
	public:

		// The key of this pair
		KeyType key = KeyType();

		// The value of this pair
		ValueType value = ValueType();
	};


	// MAP VARIABLES

	// The map's keys and values
	std::vector<key_value_pair> key_values = std::vector<key_value_pair>();

public:


};
