
// Generic Object Class Script
// by Kyle Furey

// REFERENCE: https://learn.microsoft.com/en-us/dotnet/api/system.object?view=net-8.0, https://www.geeksforgeeks.org/cpp-void-pointer/

#pragma once
#include <string>

// Include this heading to use the class
#include "Object.h"

// Define the variable used for conversions (must be larger then any variable).
#define CONVERSION_TYPE long long

// •  Object class that functions as a universal container which can hold and return data of any type.
// •  Inherit from object to share common methods and storage between different types.
#define object object

// The state of when an object or pointer has no memory allocated.
#define null nullptr

// •  Object class that functions as a universal container which can hold and return data of any type.
// •  Inherit from object to share common methods and storage between different types.
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

	// Copy constructor
	object(const object& copied)
	{
		if (copied.data == nullptr)
		{
			data = nullptr;

			return;
		}

		data = malloc(sizeof(copied.data));

		*(CONVERSION_TYPE*)data = *(CONVERSION_TYPE*)copied.data;
	}

	// Move constructor
	object(object&& moved) noexcept
	{
		data = moved.data;

		moved.data = nullptr;
	}

	// Data constructor
	template <class DataType> object(DataType data)
	{
		this->data = new DataType(data);
	}

	// Deconstructor
	virtual ~object()
	{
		delete data;

		data = nullptr;
	}


	// GETTERS AND SETTERS

	// Get the data as the given type
	template <class DataType> DataType get()
	{
		return *(DataType*)data;
	}

	// Retrieve a string representation of the given data (prevents string length exceptions)
	std::string get_string()
	{
		return *(char**)data;
	}

	// Set the current data to the given object's data
	object& set(object& object)
	{
		delete data;

		data = malloc(sizeof(object.data));

		*(CONVERSION_TYPE*)data = *(CONVERSION_TYPE*)object.data;

		return *this;
	}

	// Set the current data to the given data
	template <class DataType> object& set(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);

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
	template <class DataType> DataType release()
	{
		DataType data = *(DataType*)this->data;

		delete this->data;

		this->data = nullptr;

		return data;
	}


	// COPY AND MOVE

	// Copy another object's data
	object& copy(object& copied)
	{
		delete data;

		if (copied.data == nullptr)
		{
			data = nullptr;

			return *this;
		}

		data = malloc(sizeof(copied.data));

		*(CONVERSION_TYPE*)data = *(CONVERSION_TYPE*)copied.data;

		return *this;
	}

	// Copy another object's data
	template <class DataType> object& copy(object& copied)
	{
		delete data;

		data = new DataType(*(DataType*)copied.data);

		return *this;
	}

	// Move another object's data to this object
	object& move(object& moved)
	{
		if (this != &moved)
		{
			delete data;

			data = moved.data;

			moved.data = nullptr;
		}

		return *this;
	}


	// EQUALITY BY VALUE

	// Returns whether this object's data is equal to another object's data by value
	virtual bool equals(object& object)
	{
		if (data == nullptr || object.data == nullptr)
		{
			return data == object.data;
		}

		return *(CONVERSION_TYPE*)data == *(CONVERSION_TYPE*)object.data;
	}

	// Returns whether this object's data is equal to the given data by value
	template <class DataType> bool equals(DataType data)
	{
		if (this->data == nullptr || data == nullptr)
		{
			return this->data == data;
		}

		return *(DataType*)this->data == data;
	}

	// Returns whether this object's data is equal to another object's data by value
	static bool equals(object& object1, object object2)
	{
		if (object1.data == nullptr || object2.data == nullptr)
		{
			return object1.data == object2.data;
		}

		return *(CONVERSION_TYPE*)object1.data == *(CONVERSION_TYPE*)object2.data;
	}


	// EQUALITY BY REFERENCE

	// Returns whether this object's data is equal to another object's data by reference
	virtual bool ref_equals(object& object)
	{
		return data == object.data;
	}

	// Returns whether this object's data is equal to the given data by reference
	template <class DataType> bool ref_equals(DataType& data)
	{
		return this->data == &data;
	}

	// Returns whether this object's data is equal to another object's data by reference
	static bool ref_equals(object& object1, object& object2)
	{
		return object1.data == object2.data;
	}


	// TO STRING

	// Retrieve a string representation of the given data
	virtual std::string to_string()
	{
		return *(char**)data;
	}

	// Retrieve a string representation of the given data after being casted to the given type
	template <class DataType> std::string to_string()
	{
		return std::to_string(*(DataType*)data);
	}


	// NULL CHECK

	// Returns whether this object is null
	virtual bool is_null()
	{
		return data == nullptr;
	}

	// Returns whether the given object is null
	static bool is_null(object& object)
	{
		return object.data == nullptr;
	}

	// Returns whether this object is not null
	virtual bool is_not_null()
	{
		return data != nullptr;
	}

	// Returns whether the given object is not null
	static bool is_not_null(object& object)
	{
		return object.data != nullptr;
	}


	// ASSIGNMENT OPERATORS

	// Copy assignment operator
	object& operator=(const object& copied)
	{
		delete data;

		if (copied.data == nullptr)
		{
			data = nullptr;

			return *this;
		}

		data = malloc(sizeof(copied.data));

		*(CONVERSION_TYPE*)data = *(CONVERSION_TYPE*)copied.data;

		return *this;
	}

	// Move assignment operator
	object& operator=(object&& moved) noexcept
	{
		if (this != &moved)
		{
			delete data;

			data = moved.data;

			moved.data = nullptr;
		}

		return *this;
	}

	// Data assignment operator
	template <class DataType> object& operator=(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);

		return *this;
	}


	// EQUALITY OPERATORS

	// Returns whether this object's data is equal to another object's data by value
	bool operator==(object& object)
	{
		if (data == nullptr || object.data == nullptr)
		{
			return data == object.data;
		}

		return *(CONVERSION_TYPE*)data == *(CONVERSION_TYPE*)object.data;
	}

	// Returns whether this object's data is not equal to another object's data by value
	bool operator!=(object& object)
	{
		if (data == nullptr || object.data == nullptr)
		{
			return data != object.data;
		}

		return *(CONVERSION_TYPE*)data != *(CONVERSION_TYPE*)object.data;
	}

	// Returns whether this object's data is equal to the given data by value
	template <class DataType> bool operator==(DataType data)
	{
		if (this->data == nullptr || &data == nullptr)
		{
			return this->data == &data;
		}

		return *(DataType*)this->data == data;
	}

	// Returns whether this object's data is not equal to another object's data by value
	template <class DataType> bool operator!=(DataType data)
	{
		if (this->data == nullptr || &data == nullptr)
		{
			return this->data == &data;
		}

		return *(DataType*)this->data != data;
	}


	// NULL CHECK OPERATOR

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
// •  Can be inherited from to share common methods and storage between different types.
#define Object Object

// The state of when an object or pointer has no memory allocated.
#define Null nullptr

// •  Object class that functions as a universal container which can hold and return data of any type.
// •  Can be inherited from to share common methods and storage between different types.
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

	// Copy constructor
	Object(const Object& copied)
	{
		if (copied.data == nullptr)
		{
			data = nullptr;

			return;
		}

		data = malloc(sizeof(copied.data));

		*(CONVERSION_TYPE*)data = *(CONVERSION_TYPE*)copied.data;
	}

	// Move constructor
	Object(Object&& moved) noexcept
	{
		data = moved.data;

		moved.data = nullptr;
	}

	// Data constructor
	template <class DataType> Object(DataType data)
	{
		this->data = new DataType(data);
	}

	// Deconstructor
	virtual ~Object()
	{
		delete data;

		data = nullptr;
	}


	// GETTERS AND SETTERS

	// Get the data as the given type
	template <class DataType> DataType Get()
	{
		return *(DataType*)data;
	}

	// Retrieve a string representation of the given data (prevents string length exceptions)
	std::string GetString()
	{
		return *(char**)data;
	}

	// Set the current data to the given object's data
	Object& Set(Object& object)
	{
		delete data;

		data = malloc(sizeof(object.data));

		*(CONVERSION_TYPE*)data = *(CONVERSION_TYPE*)object.data;

		return *this;
	}

	// Set the current data to the given data
	template <class DataType> Object& Set(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);

		return *this;
	}


	// DESTROY AND RELEASE

	// Deallocate memory
	void Destroy()
	{
		delete data;

		data = nullptr;
	}

	// Get data as the given type and deallocate
	template <class DataType> DataType Release()
	{
		DataType data = *(DataType*)this->data;

		delete this->data;

		this->data = nullptr;

		return data;
	}


	// COPY AND MOVE

	// Copy another object's data
	Object& Copy(Object& copied)
	{
		delete data;

		if (copied.data == nullptr)
		{
			data = nullptr;

			return *this;
		}

		data = malloc(sizeof(copied.data));

		*(CONVERSION_TYPE*)data = *(CONVERSION_TYPE*)copied.data;

		return *this;
	}

	// Copy another object's data
	template <class DataType> Object& Copy(Object& copied)
	{
		delete data;

		data = new DataType(*(DataType*)copied.data);

		return *this;
	}

	// Move another object's data to this object
	Object& Move(Object& moved)
	{
		if (this != &moved)
		{
			delete data;

			data = moved.data;

			moved.data = nullptr;
		}

		return *this;
	}


	// EQUALITY BY VALUE

	// Returns whether this object's data is equal to another object's data by value
	virtual bool Equals(Object& object)
	{
		if (data == nullptr || object.data == nullptr)
		{
			return data == object.data;
		}

		return *(CONVERSION_TYPE*)data == *(CONVERSION_TYPE*)object.data;
	}

	// Returns whether this object's data is equal to the given data by value
	template <class DataType> bool Equals(DataType data)
	{
		if (this->data == nullptr || &data == nullptr)
		{
			return this->data == &data;
		}

		return *(DataType*)this->data == data;
	}

	// Returns whether this object's data is equal to another object's data by value
	static bool Equals(Object& object1, Object object2)
	{
		if (object1.data == nullptr || object2.data == nullptr)
		{
			return object1.data == object2.data;
		}

		return *(CONVERSION_TYPE*)object1.data == *(CONVERSION_TYPE*)object2.data;
	}


	// EQUALITY BY REFERENCE

	// Returns whether this object's data is equal to another object's data by reference
	virtual bool ReferenceEquals(Object& object)
	{
		return data == object.data;
	}

	// Returns whether this object's data is equal to the given data by reference
	template <class DataType> bool ReferenceEquals(DataType& data)
	{
		return this->data == &data;
	}

	// Returns whether this object's data is equal to another object's data by reference
	static bool ReferenceEquals(Object& object1, Object& object2)
	{
		return object1.data == object2.data;
	}


	// TO STRING

	// Retrieve a string representation of the given data
	virtual std::string ToString()
	{
		return *(char**)data;
	}

	// Retrieve a string representation of the given data after being casted to the given type
	template <class DataType> std::string ToString()
	{
		return std::to_string(*(DataType*)data);
	}


	// NULL CHECK

	// Returns whether this object is null
	virtual bool IsNull()
	{
		return data == nullptr;
	}

	// Returns whether the given object is null
	static bool IsNull(Object& object)
	{
		return object.data == nullptr;
	}

	// Returns whether this object is not null
	virtual bool IsNotNull()
	{
		return data != nullptr;
	}

	// Returns whether the given object is not null
	static bool IsNotNull(Object& object)
	{
		return object.data != nullptr;
	}


	// ASSIGNMENT OPERATORS

	// Copy assignment operator
	Object& operator=(const Object& copied)
	{
		delete data;

		if (copied.data == nullptr)
		{
			data = nullptr;

			return *this;
		}

		data = malloc(sizeof(copied.data));

		*(CONVERSION_TYPE*)data = *(CONVERSION_TYPE*)copied.data;

		return *this;
	}

	// Move assignment operator
	Object& operator=(Object&& moved) noexcept
	{
		if (this != &moved)
		{
			delete data;

			data = moved.data;

			moved.data = nullptr;
		}

		return *this;
	}

	// Data assignment operator
	template <class DataType> Object& operator=(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);

		return *this;
	}


	// EQUALITY OPERATORS

	// Returns whether this object's data is equal to another object's data by value
	bool operator==(Object& object)
	{
		if (data == nullptr || object.data == nullptr)
		{
			return data == object.data;
		}

		return *(CONVERSION_TYPE*)data == *(CONVERSION_TYPE*)object.data;
	}

	// Returns whether this object's data is not equal to another object's data by value
	bool operator!=(Object& object)
	{
		if (data == nullptr || object.data == nullptr)
		{
			return data != object.data;
		}

		return *(CONVERSION_TYPE*)data != *(CONVERSION_TYPE*)object.data;
	}

	// Returns whether this object's data is equal to the given data by value
	template <class DataType> bool operator==(DataType data)
	{
		if (this->data == nullptr || &data == nullptr)
		{
			return this->data == &data;
		}

		return *(DataType*)this->data == data;
	}

	// Returns whether this object's data is not equal to another object's data by value
	template <class DataType> bool operator!=(DataType data)
	{
		if (this->data == nullptr || &data == nullptr)
		{
			return this->data == &data;
		}

		return *(DataType*)this->data != data;
	}


	// NULL CHECK OPERATOR

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

// Implicitly-typed local variable.
#define var auto

// Iterates through each element of a collection.
#define foreach(expression) for(expression)

// Gets and stores a value from the following collection to the previous variable.
#define in :
