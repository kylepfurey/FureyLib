
// Generic Object Class Script
// by Kyle Furey

// REFERENCE: https://learn.microsoft.com/en-us/dotnet/api/system.object?view=net-8.0

#pragma once
#include <string>

// Include this heading to use the class
#include "Object.h"

// Object class that functions as a universal container which can hold and return data of any type.
// •  Can be inherited from to share common methods and storage between different types.
// •  If you intend on storing the object in a vector, use vobject instead.
#define object object

// Object class that functions as a universal container which can hold and return data of any type.
// •  Can be inherited from to share common methods and storage between different types.
// •  If you intend on storing the object in a vector, use vobject instead.
class object
{
private:

	// VARIABLES

	// The data this object owns
	void* data = nullptr;

public:

	// Default constructor
	object()
	{
		data = nullptr;
	}

	// Remove copy constructor
	template <class DataType> object(const object& copied) = delete;

	// Move constructor
	template <class DataType> object(object&& moved) noexcept
	{
		data = moved.data;

		moved.data = nullptr;
	}

	// Data constructor
	template <class DataType> object(DataType data)
	{
		this->data = new DataType(data);
	}

	// Deconstructor (overridable)
	virtual ~object()
	{
		delete data;

		data = nullptr;
	}


	// FUNCTIONS

	// Get the data as a void pointer
	void* get()
	{
		return data;
	}

	// Get the data as the given type (use get_string() for strings)
	template <class DataType> DataType get()
	{
		return *(DataType*)data;
	}

	// Get the data as a string (prevents string length exceptions)
	std::string get_string()
	{
		return *(char**)data;
	}

	// Set the current data
	template <class DataType> object& set(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);

		return *this;
	}

	// Get data as the given type
	template <class DataType> DataType release()
	{
		DataType data = *(DataType*)this->data;

		delete this->data;

		this->data = nullptr;

		return data;
	}

	// Copy another object's data
	template <class DataType> object& copy(object& copied)
	{
		delete data;

		data = new DataType(*(DataType*)copied.data);

		return *this;
	}

	// Copy another object's data (overridable)
	virtual object& copy(object& copied)
	{
		return *this;
	}

	// Deallocate memory (overridable)
	virtual void destroy()
	{
		delete data;

		data = nullptr;
	}

	// Returns whether this object's instance is equal to another (overridable)
	virtual bool equals(object object)
	{
		return data == object.data;
	}

	// Returns whether this object's instance is equal to another (overridable)
	virtual bool ref_equals(object& object)
	{
		return data == object.data;
	}

	// Returns whether this object's value is equal to another object's value
	template <class DataType> bool equals(object& object)
	{
		return *(DataType*)data == *(DataType*)object.data;
	}

	// Returns whether two objects' instances are equal to each other
	static bool equals(object object1, object object2)
	{
		return object1.data == object2.data;
	}

	// Returns whether two objects' instances are equal to each other
	static bool ref_equals(object& object1, object& object2)
	{
		return object1.data == object2.data;
	}

	// Returns whether two objects' values are equal to each other
	template <class DataType> static bool equals(object& object1, object& object2)
	{
		return *(DataType*)object1.data == *(DataType*)object2.data;
	}

	// Retrieve a string representation of the given data (overridable)
	virtual std::string to_string()
	{
		return *(char**)data;
	}

	// Retrieve a string representation of the given data
	template <class DataType> std::string to_string()
	{
		return std::to_string(*(DataType*)data);
	}


	// OPERATORS

	// Remove copy assignment operator
	template <class DataType> object& operator=(const object& copied) = delete;

	// Move assignment operator
	template <class DataType> object& operator=(object&& moved) noexcept
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

	// Returns whether this object's instance is equal to another (overridable)
	virtual bool operator==(object& object)
	{
		return data == object.data;
	}

	// Returns whether this object's instance is not equal to another (overridable)
	virtual bool operator!=(object& object)
	{
		return data != object.data;
	}
};

// Variant of the object class that allows it to be used in vectors.
// •  Inherit from the original object class to share common methods and storage between different types.
// •  Does not automatically deallocate when not in a vector!
#define vobject vobject

// Variant of the object class that allows it to be used in vectors.
// •  Inherit from the original object class to share common methods and storage between different types.
// •  Does not automatically deallocate when not in a vector!
class vobject : public object
{
private:

	// VARIABLES

	// The data this object owns
	void* data = nullptr;

public:

	// Default constructor
	vobject()
	{
		data = nullptr;
	}

	// Remove copy constructor
	template <class DataType> vobject(const vobject& copied) = delete;

	// Move constructor
	template <class DataType> vobject(vobject&& moved) noexcept
	{
		data = moved.data;

		moved.data = nullptr;
	}

	// Data constructor
	template <class DataType> vobject(DataType data)
	{
		this->data = new DataType(data);
	}

	// Deconstructor (overridable)
	virtual ~vobject()
	{

	}


	// FUNCTIONS

	// Get the data as a void pointer
	void* get()
	{
		return data;
	}

	// Get the data as the given type (use get_string() for strings)
	template <class DataType> DataType get()
	{
		return *(DataType*)data;
	}

	// Get the data as a string (prevents string length exceptions)
	std::string get_string()
	{
		return *(char**)data;
	}

	// Set the current data
	template <class DataType> vobject& set(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);

		return *this;
	}

	// Get data as the given type
	template <class DataType> DataType release()
	{
		DataType data = *(DataType*)this->data;

		delete this->data;

		this->data = nullptr;

		return data;
	}

	// Copy another object's data
	template <class DataType> vobject& copy(vobject& copied)
	{
		delete data;

		data = new DataType(*(DataType*)copied.data);

		return *this;
	}

	// Copy another object's data (overridable)
	virtual vobject& copy(vobject& copied)
	{
		return *this;
	}

	// Deallocate memory (overridable)
	virtual void destroy()
	{
		delete data;

		data = nullptr;
	}

	// Returns whether this object's instance is equal to another (overridable)
	virtual bool equals(vobject vobject)
	{
		return data == vobject.data;
	}

	// Returns whether this object's instance is equal to another (overridable)
	virtual bool ref_equals(vobject& vobject)
	{
		return data == vobject.data;
	}

	// Returns whether this object's value is equal to another object's value
	template <class DataType> bool equals(vobject& vobject)
	{
		return *(DataType*)data == *(DataType*)vobject.data;
	}

	// Returns whether two objects' instances are equal to each other
	static bool equals(vobject object1, vobject object2)
	{
		return object1.data == object2.data;
	}

	// Returns whether two objects' instances are equal to each other
	static bool ref_equals(vobject& object1, vobject& object2)
	{
		return object1.data == object2.data;
	}

	// Returns whether two objects' values are equal to each other
	template <class DataType> static bool equals(vobject& object1, vobject& object2)
	{
		return *(DataType*)object1.data == *(DataType*)object2.data;
	}

	// Retrieve a string representation of the given data (overridable)
	virtual std::string to_string()
	{
		return *(char**)data;
	}

	// Retrieve a string representation of the given data
	template <class DataType> std::string to_string()
	{
		return std::to_string(*(DataType*)data);
	}


	// OPERATORS

	// Remove copy assignment operator
	template <class DataType> vobject& operator=(const vobject& copied) = delete;

	// Move assignment operator
	template <class DataType> vobject& operator=(vobject&& moved) noexcept
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
	template <class DataType> vobject& operator=(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);

		return *this;
	}

	// Returns whether this object's instance is equal to another (overridable)
	virtual bool operator==(vobject& vobject)
	{
		return data == vobject.data;
	}

	// Returns whether this object's instance is not equal to another (overridable)
	virtual bool operator!=(vobject& vobject)
	{
		return data != vobject.data;
	}
};

// Object class that functions as a universal container which can hold and return data of any type.
// •  Can be inherited from to share common methods and storage between different types.
// •  If you intend on storing the object in a vector, use VObject instead.
#define Object Object

// Object class that functions as a universal container which can hold and return data of any type.
// •  Can be inherited from to share common methods and storage between different types.
// •  If you intend on storing the object in a vector, use VObject instead.
class Object
{
private:

	// VARIABLES

	// The data this object owns
	void* data = nullptr;

public:

	// Default constructor
	Object()
	{
		data = nullptr;
	}

	// Remove copy constructor
	template <class DataType> Object(const Object& copied) = delete;

	// Move constructor
	template <class DataType> Object(Object&& moved) noexcept
	{
		data = moved.data;

		moved.data = nullptr;
	}

	// Data constructor
	template <class DataType> Object(DataType data)
	{
		this->data = new DataType(data);
	}

	// Deconstructor (overridable)
	virtual ~Object()
	{
		delete data;

		data = nullptr;
	}


	// FUNCTIONS

	// Get the data as a void pointer
	void* Get()
	{
		return data;
	}

	// Get the data as the given type (use GetString() for strings)
	template <class DataType> DataType Get()
	{
		return *(DataType*)data;
	}

	// Get the data as a string (prevents string length exceptions)
	std::string GetString()
	{
		return *(char**)data;
	}

	// Set the current data
	template <class DataType> Object& Set(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);

		return *this;
	}

	// Get data as the given type
	template <class DataType> DataType Release()
	{
		DataType data = *(DataType*)this->data;

		delete this->data;

		this->data = nullptr;

		return data;
	}

	// Copy another object's data
	template <class DataType> Object& Copy(Object& copied)
	{
		delete data;

		data = new DataType(*(DataType*)copied.data);

		return *this;
	}

	// Copy another object's data (overridable)
	virtual Object& Copy(Object& copied)
	{
		return *this;
	}

	// Deallocate memory (overridable)
	virtual void Destroy()
	{
		delete data;

		data = nullptr;
	}

	// Returns whether this object's instance is equal to another (overridable)
	virtual bool Equals(Object Object)
	{
		return data == Object.data;
	}

	// Returns whether this object's instance is equal to another (overridable)
	virtual bool ReferenceEquals(Object& Object)
	{
		return data == Object.data;
	}

	// Returns whether this object's value is equal to another object's value
	template <class DataType> bool Equals(Object& Object)
	{
		return *(DataType*)data == *(DataType*)Object.data;
	}

	// Returns whether two objects' instances are equal to each other
	static bool Equals(Object object1, Object object2)
	{
		return object1.data == object2.data;
	}

	// Returns whether two objects' instances are equal to each other
	static bool ReferenceEquals(Object& object1, Object& object2)
	{
		return object1.data == object2.data;
	}

	// Returns whether two objects' values are equal to each other
	template <class DataType> static bool Equals(Object& object1, Object& object2)
	{
		return *(DataType*)object1.data == *(DataType*)object2.data;
	}

	// Retrieve a string representation of the given data (overridable)
	virtual std::string ToString()
	{
		return *(char**)data;
	}

	// Retrieve a string representation of the given data
	template <class DataType> std::string ToString()
	{
		return std::to_string(*(DataType*)data);
	}


	// OPERATORS

	// Remove copy assignment operator
	template <class DataType> Object& operator=(const Object& copied) = delete;

	// Move assignment operator
	template <class DataType> Object& operator=(Object&& moved) noexcept
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

	// Returns whether this object's instance is equal to another (overridable)
	virtual bool operator==(Object& Object)
	{
		return data == Object.data;
	}

	// Returns whether this object's instance is not equal to another (overridable)
	virtual bool operator!=(Object& Object)
	{
		return data != Object.data;
	}
};

// Variant of the Object class that allows it to be used in vectors.
// •  Inherit from the original Object class to share common methods and storage between different types.
// •  Does not automatically deallocate when not in a vector!
#define VObject VObject

// Variant of the Object class that allows it to be used in vectors.
// •  Inherit from the original Object class to share common methods and storage between different types.
// •  Does not automatically deallocate when not in a vector!
class VObject : public Object
{
private:

	// VARIABLES

	// The data this object owns
	void* data = nullptr;

public:

	// Default constructor
	VObject()
	{
		data = nullptr;
	}

	// Remove copy constructor
	template <class DataType> VObject(const VObject& copied) = delete;

	// Move constructor
	template <class DataType> VObject(VObject&& moved) noexcept
	{
		data = moved.data;

		moved.data = nullptr;
	}

	// Data constructor
	template <class DataType> VObject(DataType data)
	{
		this->data = new DataType(data);
	}

	// Deconstructor (overridable)
	virtual ~VObject()
	{

	}


	// FUNCTIONS

	// Get the data as a void pointer
	void* Get()
	{
		return data;
	}

	// Get the data as the given type (use GetString() for strings)
	template <class DataType> DataType Get()
	{
		return *(DataType*)data;
	}

	// Get the data as a string (prevents string length exceptions)
	std::string GetString()
	{
		return *(char**)data;
	}

	// Set the current data
	template <class DataType> VObject& Set(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);

		return *this;
	}

	// Get data as the given type
	template <class DataType> DataType Release()
	{
		DataType data = *(DataType*)this->data;

		delete this->data;

		this->data = nullptr;

		return data;
	}

	// Copy another object's data
	template <class DataType> VObject& Copy(VObject& copied)
	{
		delete data;

		data = new DataType(*(DataType*)copied.data);

		return *this;
	}

	// Copy another object's data (overridable)
	virtual VObject& Copy(VObject& copied)
	{
		return *this;
	}

	// Deallocate memory (overridable)
	virtual void Destroy()
	{
		delete data;

		data = nullptr;
	}

	// Returns whether this object's instance is equal to another (overridable)
	virtual bool Equals(VObject Object)
	{
		return data == Object.data;
	}

	// Returns whether this object's instance is equal to another (overridable)
	virtual bool ReferenceEquals(VObject& Object)
	{
		return data == Object.data;
	}

	// Returns whether this object's value is equal to another object's value
	template <class DataType> bool Equals(VObject& Object)
	{
		return *(DataType*)data == *(DataType*)Object.data;
	}

	// Returns whether two objects' instances are equal to each other
	static bool Equals(VObject object1, VObject object2)
	{
		return object1.data == object2.data;
	}

	// Returns whether two objects' instances are equal to each other
	static bool ReferenceEquals(VObject& object1, VObject& object2)
	{
		return object1.data == object2.data;
	}

	// Returns whether two objects' values are equal to each other
	template <class DataType> static bool Equals(VObject& object1, VObject& object2)
	{
		return *(DataType*)object1.data == *(DataType*)object2.data;
	}

	// Retrieve a string representation of the given data (overridable)
	virtual std::string ToString()
	{
		return *(char**)data;
	}

	// Retrieve a string representation of the given data
	template <class DataType> std::string ToString()
	{
		return std::to_string(*(DataType*)data);
	}


	// OPERATORS

	// Remove copy assignment operator
	template <class DataType> VObject& operator=(const VObject& copied) = delete;

	// Move assignment operator
	template <class DataType> VObject& operator=(VObject&& moved) noexcept
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
	template <class DataType> VObject& operator=(DataType data)
	{
		delete this->data;

		this->data = new DataType(data);

		return *this;
	}

	// Returns whether this object's instance is equal to another (overridable)
	virtual bool operator==(VObject& Object)
	{
		return data == Object.data;
	}

	// Returns whether this object's instance is not equal to another (overridable)
	virtual bool operator!=(VObject& Object)
	{
		return data != Object.data;
	}
};
