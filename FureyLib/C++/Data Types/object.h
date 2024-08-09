
// Object Base Class Script
// by Kyle Furey

// REFERENCE: https://learn.microsoft.com/en-us/dotnet/api/system.object?view=net-8.0

#pragma once
#include <string>
#include <climits>
#include <typeinfo>

// Include this heading to use the class.
#include "object.h"

// •  Base class for all objects in a program.
// •  Inherit from object to share common methods and generic storage across any type.
// •  All new types should inherit from this class and at least provide a to_string() implementation.
class object
{
public:

	// CONSTRUCTOR AND DESTRUCTOR

	// Default constructor.
	object() { }

	// Virtual destructor.
	virtual ~object() = default;


	// DEALLOCATION

	// Releases this object's memory.
	virtual void destroy() { }


	// TO STRING

	// Returns a string interpretation of the given object.
	virtual std::string to_string()
	{
		return "";
	}

	// Returns a string interpretation of the given object.
	virtual operator std::string()
	{
		return to_string();
	}


	// HASH CODE

	// Returns a unique hash code representing this object's value.
	virtual int hash_code()
	{
		int code = 0;

		std::string str = to_string();

		for (int i = 0; i < str.length(); i++)
		{
			code += str[i] + CHAR_MAX * i;
		}

		return code;
	}


	// TYPE AND CASTING

	// Returns the unique hash code of this object's type.
	size_t type()
	{
		return typeid(*this).hash_code();
	}

	// Downcasts this object to the given derived type.
	template<typename data_type> data_type& cast()
	{
		return *(data_type*)(this);
	}


	// MEMBERWISE CLONE

	// Returns a memberwise clone of this object using its copy constructor.
	template<typename data_type> data_type clone()
	{
		return data_type(*(data_type*)(this));
	}


	// NULL CHECK

	// Returns whether this object is considered null.
	virtual bool is_null()
	{
		return false;
	}

	// Returns whether this object is considered null.
	virtual operator bool()
	{
		return !is_null();
	}

	// Returns whether this object is not considered null.
	virtual bool operator!()
	{
		return is_null();
	}


	// EQUALITY BY VALUE

	// Returns whether the given object is equal to this by value.
	virtual bool equals(object& other)
	{
		return to_string() == other.to_string();
	}

	// Returns whether the given objects are equal to each other by value.
	static bool equals(object& left, object& right)
	{
		return left.to_string() == right.to_string();
	}

	// Returns whether the given object is equal to this by value.
	virtual bool operator==(object& other)
	{
		return equals(other);
	}

	// Returns whether the given object is not equal to this by value.
	virtual bool operator!=(object& other)
	{
		return !equals(other);
	}


	// EQUALITY BY REFERENCE

	// Returns whether the given object shares the same memory address.
	virtual bool ref_equals(object& other)
	{
		return this == &other;
	}

	// Returns whether the given objects share the same memory addresses.
	static bool ref_equals(object& left, object& right)
	{
		return &left == &right;
	}


	// INSTANTIATION

	// Instantiates a new object of the given derived type.
	template <typename derived_type, typename ... argument_types> static derived_type instantiate(argument_types ... arguments)
	{
		return derived_type(arguments...);
	}

	// Instantiates a new derived object of the given template.
	template <typename derived_type> static derived_type instantiate(derived_type _template)
	{
		return derived_type(_template);
	}

	// Instantiates a new derived object of the given template.
	template <typename derived_type> static derived_type instantiate(derived_type* _template)
	{
		return derived_type(*_template);
	}


	// SERIALIZATION

	// Converts the object's values into a Json formatted string.
	virtual std::string to_json()
	{
		return "{}";
	}

	// •  Reads the given Json formatted string and assigns the object's values from the string.
	// •  It is recommended to assume the Json is formatted with indents.
	// •  Returns whether the Json string was successfully parsed.
	virtual bool read_json(std::string json)
	{
		return false;
	}
};

// •  Base class for all objects in a program.
// •  Inherit from object to share common methods and generic storage across any type.
// •  All new types should inherit from this and provide a to_string() implementation.
#define object object
