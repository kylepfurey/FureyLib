
// Generic Object Class Script
// by Kyle Furey

// REQUIREMENTS: ptr.h

// REFERENCE: https://learn.microsoft.com/en-us/dotnet/api/system.object?view=net-8.0

#pragma once
#include <string>
#include "Ptr.h"

// Include this heading to use the class
#include "object.h"

// Type to be used for converting typeless objects.
#define CONVERSION_TYPE long long

// •  Object class that functions as a universal container which can hold and return data of any type.
// •  Inherit from the object class to share common methods and storage between different types.
// •  Preserves type safety of the data it is holding. Cannot safely store array pointers without a wrapper class.
class object
{
private:

	// DATA

	// The data this object owns
	ptr_base* data = nullptr;

public:

	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	object()
	{
		data = nullptr;
	}

	// Copy constructor
	object(const object& copied)
	{
		data = new sptr<CONVERSION_TYPE>(new CONVERSION_TYPE(*copied.data->get<CONVERSION_TYPE>()));
	}

	// Move constructor
	object(object&& moved) noexcept
	{
		data = moved.data;

		moved.data = nullptr;
	}

	// Data constructor
	template <typename data_type> object(data_type data)
	{
		this->data = new sptr<data_type>(new data_type(data));
	}

	// Pointer constructor
	template <typename data_type> object(data_type* data)
	{
		this->data = new sptr<data_type>(data);
	}

	// Destructor
	virtual ~object()
	{
		delete data;

		data = nullptr;
	}


	// GETTERS AND SETTERS

	// Get the data as an object
	virtual object get()
	{
		return *this;
	}

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

	// Set the current data to the given object's data
	virtual object& set(object obj)
	{
		delete data;

		data = new sptr<CONVERSION_TYPE>(new CONVERSION_TYPE(*obj.data->get<CONVERSION_TYPE>()));

		return *this;
	}

	// Set the current data to the given data
	template <typename data_type> object& set(data_type data)
	{
		delete this->data;

		this->data = new sptr<data_type>(new data_type(data));

		return *this;
	}

	// Set the current data to the given pointer
	template <typename data_type> object& set(data_type* data)
	{
		delete this->data;

		this->data = new sptr<data_type>(data);

		return *this;
	}


	// TO STRING

	// Retrieve a string representation of the given data
	virtual std::string to_string()
	{
		return *data->get<char*>();
	}

	// Retrieve a string representation of the given data after being casted to the given type
	template <typename data_type> std::string to_string()
	{
		return std::to_string(*data->get<data_type>());
	}


	// COPY AND MOVE

	// Copy another object's data
	virtual object& copy(object copied)
	{
		delete data;

		data = new sptr<CONVERSION_TYPE>(new CONVERSION_TYPE(*copied.data->get<CONVERSION_TYPE>()));

		return *this;
	}

	// Copy another object's data as the given type
	template <typename data_type> object& copy(object copied)
	{
		delete data;

		data = new sptr<data_type>(new data_type(*copied.data->get<data_type>()));

		return *this;
	}

	// Move another object's data to this object
	virtual object& move(object& moved)
	{
		data = moved.data;

		moved.data = nullptr;

		return *this;
	}

	// Swap this object's data with another object's data
	virtual object& swap(object& swapped)
	{
		ptr_base* data = this->data;

		this->data = swapped.data;

		swapped.data = data;

		return *this;
	}


	// CLONE

	// Returns a memberwise clone of this object
	virtual object memberwise_clone()
	{
		return object(*data->get<CONVERSION_TYPE>());
	}

	// Returns a reference to this object
	virtual object& ref()
	{
		return *this;
	}

	// Returns a pointer to this object
	virtual object* get_ptr()
	{
		return this;
	}


	// DESTROY AND RELEASE

	// Deallocate memory
	virtual void destroy()
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

	// Returns whether the given object is equal to this object
	virtual bool equals(object obj)
	{
		if (data == nullptr || obj.data == nullptr)
		{
			return data == obj.data;
		}

		return *data->get<CONVERSION_TYPE>() == *obj.data->get<CONVERSION_TYPE>();
	}

	// Returns whether the given data is equal to this object's data
	template<typename data_type> bool equals(data_type data)
	{
		return *this->data->get<data_type>() == data;
	}

	// Returns whether the given objects are equal
	static bool equals(object object1, object object2)
	{
		if (object1.data == nullptr || object2.data == nullptr)
		{
			return object1.data == object2.data;
		}

		return *object1.data->get<CONVERSION_TYPE>() == *object2.data->get<CONVERSION_TYPE>();
	}

	// Returns whether the given object pointer is equal to this object
	virtual bool ref_equals(object* obj)
	{
		if (data == nullptr || obj->data == nullptr)
		{
			return false;
		}

		return data == obj->data;
	}

	// Returns whether the given pointer is equal to this object's data
	template<typename data_type> bool ref_equals(data_type* data)
	{
		if (this->data == nullptr || data == nullptr)
		{
			return false;
		}

		return *this->data->get<data_type*>() == data;
	}

	// Returns whether the given object pointers are equal
	static bool ref_equals(object* object1, object* object2)
	{
		if (object1->data == nullptr || object2->data == nullptr)
		{
			return false;
		}

		return object1->data == object2->data;
	}

	// Returns whether the given object's type is equal to this object's type
	virtual bool type_equals(object obj)
	{
		return typeid(*this) == typeid(obj);
	}

	// Returns whether the given data's type is equal to this object's type
	template<typename data_type> bool type_equals(data_type data)
	{
		return typeid(*this) == typeid(data);
	}

	// Returns whether the given objects' types are equal
	static bool type_equal(object object1, object object2)
	{
		return typeid(object1) == typeid(object2);
	}


	// NULL CHECK

	// Returns whether this object is null
	virtual bool is_null()
	{
		return data == nullptr;
	}

	// Returns whether the given object is null
	static bool is_null(object obj)
	{
		return obj.data == nullptr;
	}

	// Returns whether this object is not null
	virtual bool is_not_null()
	{
		return data != nullptr;
	}

	// Returns whether the given object is not null
	static bool is_not_null(object& obj)
	{
		return obj.data != nullptr;
	}


	// ASSIGNMENT OPERATORS

	// Copy assignment operator
	virtual object& operator=(const object& copied)
	{
		delete data;

		data = new sptr<CONVERSION_TYPE>(new CONVERSION_TYPE(*copied.data->get<CONVERSION_TYPE>()));

		return *this;
	}

	// Move assignment operator
	virtual object& operator=(object&& moved) noexcept
	{
		data = moved.data;

		moved.data = nullptr;

		return *this;
	}

	// Data assignment operator
	template <typename data_type> object& operator=(data_type data)
	{
		delete this->data;

		this->data = new sptr<data_type>(new data_type(data));

		return *this;
	}

	// Pointer assignment operator
	template <typename data_type> object& operator=(data_type* data)
	{
		delete this->data;

		this->data = new sptr<data_type>(data);

		return *this;
	}


	// EQUALITY OPERATORS

	// Returns whether this object's data is equal to another object's data 
	virtual bool operator==(object obj)
	{
		if (data == nullptr || obj.data == nullptr)
		{
			return data == obj.data;
		}

		return *data->get<CONVERSION_TYPE>() == *obj.data->get<CONVERSION_TYPE>();
	}

	// Returns whether this object's data is not equal to another object's data 
	virtual bool operator!=(object obj)
	{
		if (data == nullptr || obj.data == nullptr)
		{
			return data != obj.data;
		}

		return *data->get<CONVERSION_TYPE>() != *obj.data->get<CONVERSION_TYPE>();
	}

	// Returns whether this object's data is equal to the given data 
	template <typename data_type> bool operator==(data_type data)
	{
		return *this->data->get<data_type>() == data;
	}

	// Returns whether this object's data is not equal to another object's data 
	template <typename data_type> bool operator!=(data_type data)
	{
		return *this->data->get<data_type>() != data;
	}


	// NULL CHECK OPERATORS

	// Returns whether this object is not null
	virtual operator bool()
	{
		return data != nullptr;
	}

	// Returns whether this object is null
	virtual bool operator!()
	{
		return data == nullptr;
	}
};

// •  Object class that functions as a universal container which can hold and return data of any type.
// •  Inherit from the object class to share common methods and storage between different types.
// •  Preserves type safety of the data it is holding. Cannot safely store array pointers without a wrapper class.
#define object object

// •  Object class that functions as a universal container which can hold and return data of any type.
// •  Inherit from the object class to share common methods and storage between different types.
// •  Preserves type safety of the data it is holding. Cannot safely store array pointers without a wrapper class.
#define obj object
