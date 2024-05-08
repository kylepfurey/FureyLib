
// Generic Object Class Script
// by Kyle Furey

#pragma once

// Include this heading to use the class
#include "object.h"

// Object keyword macro
#define object object

// Generic object class.
class object
{
private:

	// DATA

	// The data this object owns
	void* data = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	object()
	{
		data = nullptr;
	}

	// Data constructor
	template <class DataType> object(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);
	}

	// Copy constructor
	object(object&& object) noexcept
	{
		this->data = object.data;
	}

	// Deconstructor
	~object()
	{
		delete data;

		data = nullptr;
	}


	// FUNCTIONS

	// Get function
	void*& get()
	{
		return data;
	}

	// Get function
	template <class DataType> DataType& get()
	{
		return *(DataType*)data;
	}

	// Set function
	template <class DataType> DataType& set(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);

		return *(DataType*)this->data;
	}

	// Set function
	object& set(object& object)
	{
		this->data = object.data;

		return *this;
	}

	// Data equals function
	template <class DataType> bool equals(DataType data)
	{
		return *(DataType*)this->data == data;
	}

	// Data not equals function
	template <class DataType> bool not_equals(DataType data)
	{
		return *(DataType*)this->data != data;
	}

	// Object equals function
	bool equals(object& object)
	{
		return this->data == object.data;
	}

	// Object not equals function
	bool not_equals(object& object)
	{
		return this->data != object.data;
	}

	// Deallocation function
	void destroy()
	{
		delete data;

		data = nullptr;
	}


	// OPERATORS

	// Dereference operator
	void*& operator*()
	{
		return data;
	}

	// Data assignment operator
	template <class DataType> DataType& operator=(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);

		return *(DataType*)this->data;
	}

	// Data equals operator
	template <class DataType> bool operator==(DataType data)
	{
		return *(DataType*)this->data == data;
	}

	// Data not equals operator
	template <class DataType> bool operator!=(DataType data)
	{
		return *(DataType*)this->data != data;
	}

	// Object assignment operator
	object& operator=(object& object)
	{
		this->data = object.data;

		return *this;
	}

	// Object equals operator
	bool operator==(object& object)
	{
		return this->data == object.data;
	}

	// Object not equals operator
	bool operator!=(object& object)
	{
		return this->data != object.data;
	}
};

// Generic object class.
class Object
{
private:

	// DATA

	// The data this object owns
	void* data = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	Object()
	{
		data = nullptr;
	}

	// Data constructor
	template <class DataType> Object(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);
	}

	// Copy constructor
	Object(Object&& object) noexcept
	{
		this->data = object.data;
	}

	// Deconstructor
	~Object()
	{
		delete data;

		data = nullptr;
	}


	// FUNCTIONS

	// Get function
	void*& Get()
	{
		return data;
	}

	// Get function
	template <class DataType> DataType& Get()
	{
		return *(DataType*)data;
	}

	// Set function
	template <class DataType> DataType& Set(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);

		return *(DataType*)this->data;
	}

	// Set function
	Object& Set(Object& object)
	{
		this->data = object.data;

		return *this;
	}

	// Data equals function
	template <class DataType> bool Equals(DataType data)
	{
		return *(DataType*)this->data == data;
	}

	// Data not equals function
	template <class DataType> bool NotEquals(DataType data)
	{
		return *(DataType*)this->data != data;
	}

	// Object equals function
	bool Equals(Object& object)
	{
		return this->data == object.data;
	}

	// Object not equals function
	bool NotEquals(Object& object)
	{
		return this->data != object.data;
	}

	// Deallocation function
	void Destroy()
	{
		delete data;

		data = nullptr;
	}


	// OPERATORS

	// Dereference operator
	void*& operator*()
	{
		return data;
	}

	// Data assignment operator
	template <class DataType> DataType& operator=(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);

		return *(DataType*)this->data;
	}

	// Data equals operator
	template <class DataType> bool operator==(DataType data)
	{
		return *(DataType*)this->data == data;
	}

	// Data not equals operator
	template <class DataType> bool operator!=(DataType data)
	{
		return *(DataType*)this->data != data;
	}

	// Object assignment operator
	Object& operator=(Object& object)
	{
		this->data = object.data;

		return *this;
	}

	// Object equals operator
	bool operator==(Object& object)
	{
		return this->data == object.data;
	}

	// Object not equals operator
	bool operator!=(Object& object)
	{
		return this->data != object.data;
	}
};
