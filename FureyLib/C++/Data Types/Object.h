
// Generic Object Class Script
// by Kyle Furey

// REQUIREMENTS: Ptr.h

// REFERENCE: https://learn.microsoft.com/en-us/dotnet/api/system.object?view=net-8.0

#pragma once
#include <string>
#include "Ptr.h"

// Include this heading to use the class
#include "Object.h"

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

	// CONSTRUCTORS AND DECONSTRUCTOR

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
	template <typename DataType> object(DataType data)
	{
		this->data = new sptr<DataType>(new DataType(data));
	}

	// Pointer constructor
	template <typename DataType> object(DataType* data)
	{
		this->data = new sptr<DataType>(data);
	}

	// Deconstructor
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
	template <typename DataType> DataType get()
	{
		return *data->get<DataType>();
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
	template <typename DataType> object& set(DataType data)
	{
		delete this->data;

		this->data = new sptr<DataType>(new DataType(data));

		return *this;
	}

	// Set the current data to the given pointer
	template <typename DataType> object& set(DataType* data)
	{
		delete this->data;

		this->data = new sptr<DataType>(data);

		return *this;
	}


	// TO STRING

	// Retrieve a string representation of the given data
	virtual std::string to_string()
	{
		return *data->get<char*>();
	}

	// Retrieve a string representation of the given data after being casted to the given type
	template <typename DataType> std::string to_string()
	{
		return std::to_string(*data->get<DataType>());
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
	template <typename DataType> object& copy(object copied)
	{
		delete data;

		data = new sptr<DataType>(new DataType(*copied.data->get<DataType>()));

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
	template <typename DataType> DataType release()
	{
		DataType data = *this->data->get<DataType>();

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
	template<typename DataType> bool equals(DataType data)
	{
		return *this->data->get<DataType>() == data;
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
	template<typename DataType> bool ref_equals(DataType* data)
	{
		if (this->data == nullptr || data == nullptr)
		{
			return false;
		}

		return *this->data->get<DataType*>() == data;
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
	template<typename DataType> bool type_equals(DataType data)
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
	template <typename DataType> object& operator=(DataType data)
	{
		delete this->data;

		this->data = new sptr<DataType>(new DataType(data));

		return *this;
	}

	// Pointer assignment operator
	template <typename DataType> object& operator=(DataType* data)
	{
		delete this->data;

		this->data = new sptr<DataType>(data);

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
	template <typename DataType> bool operator==(DataType data)
	{
		return *this->data->get<DataType>() == data;
	}

	// Returns whether this object's data is not equal to another object's data 
	template <typename DataType> bool operator!=(DataType data)
	{
		return *this->data->get<DataType>() != data;
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
// •  Inherit from the Object class to share common methods and storage between different types.
// •  Preserves type safety of the data it is holding. Cannot safely store array pointers without a wrapper class.
class Object
{
private:

	// DATA

	// The data this object owns
	PointerBase* data = nullptr;

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
		data = new SharedPointer<CONVERSION_TYPE>(new CONVERSION_TYPE(*copied.data->Get<CONVERSION_TYPE>()));
	}

	// Move constructor
	Object(Object&& moved) noexcept
	{
		data = moved.data;

		moved.data = nullptr;
	}

	// Data constructor
	template <typename DataType> Object(DataType data)
	{
		this->data = new SharedPointer<DataType>(new DataType(data));
	}

	// Data constructor
	template <typename DataType> Object(DataType* data)
	{
		this->data = new SharedPointer<DataType>(data);
	}

	// Deconstructor
	virtual ~Object()
	{
		delete data;

		data = nullptr;
	}


	// GETTERS AND SETTERS

	// Get the data as an object
	virtual Object Get()
	{
		return *this;
	}

	// Get the data as the given type (use GetString() for std::string casting)
	template <typename DataType> DataType Get()
	{
		return *data->Get<DataType>();
	}

	// Retrieve a string representation of the given data (prevents string length exceptions)
	std::string GetString()
	{
		return *data->Get<char*>();
	}

	// Set the current data to the given object's data
	virtual Object& Set(Object obj)
	{
		delete data;

		data = new SharedPointer<CONVERSION_TYPE>(new CONVERSION_TYPE(*obj.data->Get<CONVERSION_TYPE>()));

		return *this;
	}

	// Set the current data to the given data
	template <typename DataType> Object& Set(DataType data)
	{
		delete this->data;

		this->data = new SharedPointer<DataType>(new DataType(data));

		return *this;
	}

	// Set the current data to the given pointer
	template <typename DataType> Object& Set(DataType* data)
	{
		delete this->data;

		this->data = new SharedPointer<DataType>(data);

		return *this;
	}


	// TO STRING

	// Retrieve a string representation of the given data
	virtual std::string ToString()
	{
		return *data->Get<char*>();
	}

	// Retrieve a string representation of the given data after being casted to the given type
	template <typename DataType> std::string ToString()
	{
		return std::to_string(*data->Get<DataType>());
	}


	// COPY AND MOVE

	// Copy another object's data
	virtual Object& Copy(Object copied)
	{
		delete data;

		data = new SharedPointer<CONVERSION_TYPE>(new CONVERSION_TYPE(*copied.data->Get<CONVERSION_TYPE>()));

		return *this;
	}

	// Copy another object's data as the given type
	template <typename DataType> Object& Copy(Object copied)
	{
		delete data;

		data = new SharedPointer<DataType>(new DataType(*copied.data->Get<DataType>()));

		return *this;
	}

	// Move another object's data to this object
	virtual Object& Move(Object& moved)
	{
		data = moved.data;

		moved.data = nullptr;

		return *this;
	}

	// Swap this object's data with another object's data
	virtual Object& Swap(Object& swapped)
	{
		PointerBase* data = this->data;

		this->data = swapped.data;

		swapped.data = data;

		return *this;
	}


	// CLONE

	// Returns a memberwise clone of this object
	virtual Object MemberwiseClone()
	{
		return Object(*data->Get<CONVERSION_TYPE>());
	}

	// Returns a reference to this object
	virtual Object& Reference()
	{
		return *this;
	}

	// Returns a pointer to this object
	virtual Object* GetPointer()
	{
		return this;
	}


	// DESTROY AND RELEASE

	// Deallocate memory
	virtual void Destroy()
	{
		delete data;

		data = nullptr;
	}

	// Get data as the given type and deallocate
	template <typename DataType> DataType Release()
	{
		DataType data = *this->data->Get<DataType>();

		delete this->data;

		this->data = nullptr;

		return data;
	}


	// EQUALITY

	// Returns whether the given object is equal to this object
	virtual bool Equals(Object obj)
	{
		if (data == nullptr || obj.data == nullptr)
		{
			return data == obj.data;
		}

		return *data->Get<CONVERSION_TYPE>() == *obj.data->Get<CONVERSION_TYPE>();
	}

	// Returns whether the given data is equal to this object's data
	template<typename DataType> bool Equals(DataType data)
	{
		return *this->data->Get<DataType>() == data;
	}

	// Returns whether the given objects are equal
	static bool Equals(Object object1, Object object2)
	{
		if (object1.data == nullptr || object2.data == nullptr)
		{
			return object1.data == object2.data;
		}

		return *object1.data->Get<CONVERSION_TYPE>() == *object2.data->Get<CONVERSION_TYPE>();
	}

	// Returns whether the given object is equal to this object
	virtual bool ReferenceEquals(Object* obj)
	{
		if (data == nullptr || obj->data == nullptr)
		{
			return false;
		}

		return data == obj->data;
	}

	// Returns whether the given data is equal to this object's data
	template<typename DataType> bool ReferenceEquals(DataType* data)
	{
		if (this->data == nullptr || data == nullptr)
		{
			return false;
		}

		return *this->data->Get<DataType*>() == data;
	}

	// Returns whether the given objects are equal
	static bool ReferenceEquals(Object* object1, Object* object2)
	{
		if (object1->data == nullptr || object2->data == nullptr)
		{
			return false;
		}

		return object1->data == object2->data;
	}

	// Returns whether the given object's type is equal to this object's type
	virtual bool TypeEquals(Object obj)
	{
		return typeid(*this) == typeid(obj);
	}

	// Returns whether the given data's type is equal to this object's type
	template<typename DataType> bool TypeEquals(DataType data)
	{
		return typeid(*this) == typeid(data);
	}

	// Returns whether the given objects' types are equal
	static bool TypeEquals(Object object1, Object object2)
	{
		return typeid(object1) == typeid(object2);
	}


	// NULL CHECK

	// Returns whether this object is null
	virtual bool IsNull()
	{
		return data == nullptr;
	}

	// Returns whether the given object is null
	static bool IsNull(Object obj)
	{
		return obj.data == nullptr;
	}

	// Returns whether this object is not null
	virtual bool IsNotNull()
	{
		return data != nullptr;
	}

	// Returns whether the given object is not null
	static bool IsNotNull(Object& obj)
	{
		return obj.data != nullptr;
	}


	// ASSIGNMENT OPERATORS

	// Copy assignment operator
	virtual Object& operator=(const Object& copied)
	{
		delete data;

		data = new SharedPointer<CONVERSION_TYPE>(new CONVERSION_TYPE(*copied.data->Get<CONVERSION_TYPE>()));

		return *this;
	}

	// Move assignment operator
	virtual Object& operator=(Object&& moved) noexcept
	{
		data = moved.data;

		moved.data = nullptr;

		return *this;
	}

	// Data assignment operator
	template <typename DataType> Object& operator=(DataType data)
	{
		delete this->data;

		this->data = new SharedPointer<DataType>(new DataType(data));

		return *this;
	}

	// Pointer assignment operator
	template <typename DataType> Object& operator=(DataType* data)
	{
		delete this->data;

		this->data = new SharedPointer<DataType>(data);

		return *this;
	}


	// EQUALITY OPERATORS

	// Returns whether this object's data is equal to another object's data 
	virtual bool operator==(Object obj)
	{
		if (data == nullptr || obj.data == nullptr)
		{
			return data == obj.data;
		}

		return *data->Get<CONVERSION_TYPE>() == *obj.data->Get<CONVERSION_TYPE>();
	}

	// Returns whether this object's data is not equal to another object's data 
	virtual bool operator!=(Object obj)
	{
		if (data == nullptr || obj.data == nullptr)
		{
			return data != obj.data;
		}

		return *data->Get<CONVERSION_TYPE>() != *obj.data->Get<CONVERSION_TYPE>();
	}

	// Returns whether this object's data is equal to the given data 
	template <typename DataType> bool operator==(DataType data)
	{
		return *this->data->Get<DataType>() == data;
	}

	// Returns whether this object's data is not equal to another object's data 
	template <typename DataType> bool operator!=(DataType data)
	{
		return *this->data->Get<DataType>() != data;
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

// •  Object class that functions as a universal container which can hold and return data of any type.
// •  Inherit from the Object class to share common methods and storage between different types.
// •  Preserves type safety of the data it is holding. Cannot safely store array pointers without a wrapper class.
#define Object Object

// •  Object class that functions as a universal container which can hold and return data of any type.
// •  Inherit from the Object class to share common methods and storage between different types.
// •  Preserves type safety of the data it is holding. Cannot safely store array pointers without a wrapper class.
#define Obj Object

// The state of when an object or pointer has no memory allocated.
#define null nullptr

// The state of when an object or pointer has no memory allocated.
#define Null nullptr

// Implicitly-typed local variable.
#define var auto

// Iterates through each element of a collection.
#define foreach(expression) for(expression)

// Gets and stores a value from the following collection to the previous variable.
#define in :
