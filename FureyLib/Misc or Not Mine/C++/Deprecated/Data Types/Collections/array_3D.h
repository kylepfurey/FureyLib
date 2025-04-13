
// Multidimensional Array Class Script
// by Kyle Furey

#pragma once
#include <map>
#include <tuple>
#include <stdexcept>

// Include this heading to use the classes.
#include "array_3D.h"

// •  2D array wrapper class.
// •  Stores a fixed-sized map that can be accessed via operator[].
// •  Access values with my_array[{x, y}].
template<typename data_type> class array_2D
{
private:

	// The underlying map.
	std::map<std::tuple<int, int>, data_type> map = std::map<std::tuple<int, int>, data_type>();

	// X size.
	int x = 0;

	// Y size.
	int y = 0;

public:

	// Size constructor.
	array_2D(int size_x, int size_y)
	{
		map = std::map<std::tuple<int, int>, data_type>();

		this->x = size_x;

		this->y = size_y;
	}

	// Element access operator.
	data_type& operator[](std::tuple<int, int> coordinate)
	{
		int x = std::get<0>(coordinate);

		int y = std::get<1>(coordinate);

		if (x < 0 || y < 0)
		{
			throw std::out_of_range("ERROR: array_2D cannot be accessed at negative indicies!");
		}

		if (x >= this->x || y >= this->y)
		{
			throw std::out_of_range("ERROR: array_2D cannot be accessed at or beyond its set size!");
		}

		return map[{x, y}];
	}

	// Get size of X dimension.
	int size_x() { return x; }

	// Get size of Y dimension.
	int size_y() { return y; }
};

// •  3D array wrapper class.
// •  Stores a fixed-sized map that can be accessed via operator[].
// •  Access values with my_array[{x, y, z}].
template<typename data_type> class array_3D
{
private:

	// The underlying map.
	std::map<std::tuple<int, int, int>, data_type> map = std::map<std::tuple<int, int, int>, data_type>();

	// X size.
	int x = 0;

	// Y size.
	int y = 0;

	// Z size.
	int z = 0;

public:

	// Size constructor.
	array_3D(int size_x, int size_y, int size_z)
	{
		map = std::map<std::tuple<int, int, int>, data_type>();

		this->x = size_x;

		this->y = size_y;

		this->z = size_z;
	}

	// Element access operator.
	data_type& operator[](std::tuple<int, int, int> coordinate)
	{
		int x = std::get<0>(coordinate);

		int y = std::get<1>(coordinate);

		int z = std::get<2>(coordinate);

		if (x < 0 || y < 0 || z < 0)
		{
			throw std::out_of_range("ERROR: array_3D cannot be accessed at negative indicies!");
		}

		if (x >= this->x || y >= this->y || z >= this->z)
		{
			throw std::out_of_range("ERROR: array_3D cannot be accessed at or beyond its set size!");
		}

		return map[coordinate];
	}

	// Get size of X dimension.
	int size_x() { return x; }

	// Get size of Y dimension.
	int size_y() { return y; }

	// Get size of Z dimension.
	int size_z() { return z; }
};
