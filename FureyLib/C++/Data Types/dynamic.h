
// Dynamic Type Class Script
// by Kyle Furey

// REQUIREMENTS: ptr.h

// REFERENCE: https://learn.microsoft.com/en-us/dotnet/csharp/advanced-topics/interop/using-type-dynamic

#pragma once
#include <string>
#include "ptr.h"

// Include this heading to use the class
#include "dynamic.h"

// Type to be used for converting typeless dynamics.
#define CONVERSION_TYPE long long

// •  Dynamic class that functions as a universal container which can hold and return data of any type.
// •  Preserves type safety of the data it is holding. Cannot safely store array pointers without a wrapper class.
class dynamic
{
private:

	// DATA

	// The data this dynamic owns
	ptr_base* data = nullptr;

public:

	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	dynamic()
	{
		data = nullptr;
	}

	// Copy constructor
	dynamic(const dynamic& copied)
	{
		data = new sptr<CONVERSION_TYPE>(new CONVERSION_TYPE(*copied.data->get<CONVERSION_TYPE>()));
	}

	// Move constructor
	dynamic(dynamic&& moved) noexcept
	{
		data = moved.data;

		moved.data = nullptr;
	}

	// Data constructor
	template <typename data_type> dynamic(data_type data)
	{
		this->data = new sptr<data_type>(new data_type(data));
	}

	// Pointer constructor
	template <typename data_type> dynamic(data_type* data)
	{
		this->data = new sptr<data_type>(data);
	}

	// Destructor
	virtual ~dynamic()
	{
		delete data;

		data = nullptr;
	}


	// GETTERS AND SETTERS

	// Get the data as the given type (use get_string() for std::string casting)
	template <typename data_type> data_type get()
	{
		return *data->get<data_type>();
	}

	// Retrieve a string representation of the given data (prevents string length exceptions)
	std::string get_string()
	{
		return *data->get<char*>();
	}

	// Set the current data to the given dynamic's data
	dynamic& set(dynamic& obj)
	{
		delete data;

		data = new sptr<CONVERSION_TYPE>(new CONVERSION_TYPE(*obj.data->get<CONVERSION_TYPE>()));

		return *this;
	}

	// Set the current data to the given data
	template <typename data_type> dynamic& set(data_type data)
	{
		delete this->data;

		this->data = new sptr<data_type>(new data_type(data));

		return *this;
	}

	// Set the current data to the given pointer
	template <typename data_type> dynamic& set(data_type* data)
	{
		delete this->data;

		this->data = new sptr<data_type>(data);

		return *this;
	}


	// COPY AND MOVE

	// Copy another dynamic's data
	dynamic& copy(dynamic copied)
	{
		delete data;

		data = new sptr<CONVERSION_TYPE>(new CONVERSION_TYPE(*copied.data->get<CONVERSION_TYPE>()));

		return *this;
	}

	// Copy another dynamic's data as the given type
	template <typename data_type> dynamic& copy(dynamic copied)
	{
		delete data;

		data = new sptr<data_type>(new data_type(*copied.data->get<data_type>()));

		return *this;
	}

	// Move another dynamic's data to this dynamic
	dynamic& move(dynamic& moved)
	{
		data = moved.data;

		moved.data = nullptr;

		return *this;
	}

	// Swap this dynamic's data with another dynamic's data
	dynamic& swap(dynamic& swapped)
	{
		ptr_base* data = this->data;

		this->data = swapped.data;

		swapped.data = data;

		return *this;
	}


	// DESTROY AND RELEASE

	// Deallocate memory
	void destroy()
	{
		delete data;

		data = nullptr;
	}

	// Get data as the given type and deallocate
	template <typename data_type> data_type release()
	{
		data_type data = *this->data->get<data_type>();

		delete this->data;

		this->data = nullptr;

		return data;
	}


	// EQUALITY

	// Returns whether the given dynamic is equal to this dynamic
	bool equals(dynamic& obj)
	{
		if (data == nullptr || obj.data == nullptr)
		{
			return data == obj.data;
		}

		return *data->get<CONVERSION_TYPE>() == *obj.data->get<CONVERSION_TYPE>();
	}

	// Returns whether the given data is equal to this dynamic's data
	template<typename data_type> bool equals(data_type data)
	{
		return *this->data->get<data_type>() == data;
	}


	// NULL CHECK

	// Returns whether this dynamic is null
	bool is_null()
	{
		return data == nullptr;
	}


	// ASSIGNMENT OPERATORS

	// Copy assignment operator
	dynamic& operator=(const dynamic& copied)
	{
		delete data;

		data = new sptr<CONVERSION_TYPE>(new CONVERSION_TYPE(*copied.data->get<CONVERSION_TYPE>()));

		return *this;
	}

	// Move assignment operator
	dynamic& operator=(dynamic&& moved) noexcept
	{
		data = moved.data;

		moved.data = nullptr;

		return *this;
	}

	// Data assignment operator
	template <typename data_type> dynamic& operator=(data_type data)
	{
		delete this->data;

		this->data = new sptr<data_type>(new data_type(data));

		return *this;
	}

	// Pointer assignment operator
	template <typename data_type> dynamic& operator=(data_type* data)
	{
		delete this->data;

		this->data = new sptr<data_type>(data);

		return *this;
	}


	// EQUALITY OPERATORS

	// Returns whether this dynamic's data is equal to another dynamic's data 
	bool operator==(dynamic& obj)
	{
		if (data == nullptr || obj.data == nullptr)
		{
			return data == obj.data;
		}

		return *data->get<CONVERSION_TYPE>() == *obj.data->get<CONVERSION_TYPE>();
	}

	// Returns whether this dynamic's data is not equal to another dynamic's data 
	bool operator!=(dynamic& obj)
	{
		if (data == nullptr || obj.data == nullptr)
		{
			return data != obj.data;
		}

		return *data->get<CONVERSION_TYPE>() != *obj.data->get<CONVERSION_TYPE>();
	}

	// Returns whether this dynamic's data is equal to the given data 
	template <typename data_type> bool operator==(data_type data)
	{
		return *this->data->get<data_type>() == data;
	}

	// Returns whether this dynamic's data is not equal to another dynamic's data 
	template <typename data_type> bool operator!=(data_type data)
	{
		return *this->data->get<data_type>() != data;
	}


	// NULL CHECK OPERATORS

	// Returns whether this dynamic is not null
	operator bool()
	{
		return data != nullptr;
	}

	// Returns whether this dynamic is null
	bool operator!()
	{
		return data == nullptr;
	}
};

// •  Dynamic class that functions as a universal container which can hold and return data of any type.
// •  Preserves type safety of the data it is holding. Cannot safely store array pointers without a wrapper class.
#define dynamic dynamic
