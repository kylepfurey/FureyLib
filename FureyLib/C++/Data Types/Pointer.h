
// Type Safe Generic Pointer Script
// by Kyle Furey

#pragma once

// Include this heading to use the classes
#include "Pointer.h"

// Forward declaration of pointer class.
template <typename DataType> class pointer;

// •  Base class for the pointer class.
// •  Used as type safe storage for pointers of varying types.
// •  Provides a virtual destructor for the pointer class to properly destroy its pointer regardless of its type.
class pointer_base
{
public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor.
	pointer_base() { }

	// Pointer constructor.
	template<typename DataType> pointer_base(DataType* ptr)
	{
		*this = pointer<DataType>(ptr);
	}

	// Virtual deconstructor used to properly deallocate the pointer class's pointer.
	virtual ~pointer_base() { }


	// GET POINTER

	// Cast to shared pointer.
	template<typename DataType> std::shared_ptr<DataType>& get()
	{
		return ((pointer<DataType>*)this)->ptr;
	}


	// ASSIGNMENT OPERATORS

	// Pointer assignment operator.
	template<typename DataType> pointer<DataType> operator=(DataType* ptr)
	{
		return pointer<DataType>(ptr);
	}
};

// •  Represents a shared pointer that will be deallocated at the end of the program with type safety.
// •  Inherits from the pointer_base storage class.
template <typename DataType> class pointer : public pointer_base
{
public:

	// DATA

	// The stored pointer to be deallocated.
	std::shared_ptr<DataType> ptr = nullptr;


	// CONSTRUCTORS

	// Default constructor.
	pointer() { }

	// Pointer constructor.
	pointer(DataType* ptr)
	{
		this->ptr = std::shared_ptr<DataType>(ptr);
	}

private:

	// DELETE GET POINTER

	// Delete the cast function.
	std::shared_ptr<DataType>& get() = delete;
};

// Forward declaration of Pointer class.
template <typename DataType> class Pointer;

// •  Base class for the Pointer class.
// •  Used as type safe storage for pointers of varying types.
// •  Provides a virtual destructor for the Pointer class to properly destroy its pointer regardless of its type.
class PointerBase
{
public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor.
	PointerBase() { }

	// Pointer constructor.
	template<typename DataType> PointerBase(DataType* ptr)
	{
		*this = Pointer<DataType>(ptr);
	}

	// Virtual deconstructor used to properly deallocate the pointer class's pointer.
	virtual ~PointerBase() { }


	// GET POINTER

	// Cast to shared pointer.
	template<typename DataType> std::shared_ptr<DataType>& Get()
	{
		return ((pointer<DataType>*)this)->ptr;
	}


	// ASSIGNMENT OPERATORS

	// Pointer assignment operator.
	template<typename DataType> Pointer<DataType> operator=(DataType* ptr)
	{
		return Pointer<DataType>(ptr);
	}
};

// •  Represents a shared pointer that will be deallocated at the end of the program with type safety.
// •  Inherits from the PointerBase storage class.
template <typename DataType> class Pointer : public PointerBase
{
public:

	// DATA

	// The stored pointer to be deallocated.
	std::shared_ptr<DataType> ptr = nullptr;


	// CONSTRUCTORS

	// Default constructor.
	Pointer() { }

	// Pointer constructor.
	Pointer(DataType* ptr)
	{
		this->ptr = std::shared_ptr<DataType>(ptr);
	}

private:

	// DELETE GET POINTER

	// Delete the cast function.
	std::shared_ptr<DataType>& Get() = delete;
};
