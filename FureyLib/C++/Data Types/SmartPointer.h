
// Smart Pointer Class
// by Kyle Furey

// REFERENCE: https://blog.devgenius.io/unique-pointer-and-implementation-in-c-ec6599a518e5

#pragma once

// Include this heading to use the class
#include "SmartPointer.h"

// An exclusive wrapper for a newly created pointer that automatically deallocates on deconstruction.
template <class DataType> class smart_ptr
{
private:

	// POINTER

	// The stored pointer
	DataType* ptr = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default onstructor
	smart_ptr(DataType* new_ptr = nullptr)
	{
		// Set the pointer
		ptr = new_ptr;
	}

	// Remove copy constructor
	smart_ptr(const smart_ptr<DataType>& new_ptr) = delete;

	// Move constructor
	smart_ptr(smart_ptr<DataType>&& new_ptr) noexcept
	{
		ptr = new_ptr.ptr;

		new_ptr.ptr = nullptr;
	}

	// Deconstructor
	~smart_ptr()
	{
		delete ptr;

		ptr = nullptr;
	}


	// FUNCTIONS

	// Release function
	DataType* release()
	{
		DataType* new_ptr = ptr;

		ptr = nullptr;

		return new_ptr;
	}

	// Reset function
	smart_ptr<DataType>& reset(DataType* new_ptr = nullptr)
	{
		delete ptr;

		ptr = new_ptr;

		return *this;
	}

	// Delete function
	smart_ptr<DataType>& destroy()
	{
		return reset(nullptr);
	}


	// OPERATORS

	// Remove assignment operator
	smart_ptr<DataType>& operator=(DataType* new_ptr) = delete;

	// Move operator
	smart_ptr<DataType>& operator=(smart_ptr<DataType>&& new_ptr) noexcept
	{
		if (this != &new_ptr)
		{
			delete ptr;

			ptr = new_ptr.ptr;

			new_ptr.ptr = nullptr;
		}

		return *this;
	}

	// Dereferencing pointer operator
	DataType& operator*()
	{
		return *ptr;
	}

	// Arrow pointer operator
	DataType* operator->()
	{
		return ptr;
	}
};

// An exclusive wrapper for a newly created pointer that automatically deallocates on deconstruction.
template <class DataType> class SmartPointer
{
private:

	// POINTER

	// The stored pointer
	DataType* ptr = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	SmartPointer(DataType* new_ptr = nullptr)
	{
		// Set the pointer
		ptr = new_ptr;
	}

	// Remove copy constructor
	SmartPointer(const SmartPointer<DataType>& new_ptr) = delete;

	// Move construtor
	SmartPointer(SmartPointer<DataType>&& new_ptr) noexcept
	{
		ptr = new_ptr.ptr;

		new_ptr.ptr = nullptr;
	}

	// Deconstructor
	~SmartPointer()
	{
		delete ptr;

		ptr = nullptr;
	}


	// FUNCTIONS

	// Release function
	DataType* Release()
	{
		DataType* new_ptr = ptr;

		ptr = nullptr;

		return new_ptr;
	}

	// Reset function
	SmartPointer<DataType>& Reset(DataType* new_ptr = nullptr)
	{
		delete ptr;

		ptr = new_ptr;

		return *this;
	}

	// Delete function
	SmartPointer<DataType>& Destroy()
	{
		return Reset(nullptr);
	}


	// OPERATORS

	// Remove assignment operator
	SmartPointer<DataType>& operator=(DataType* new_ptr) = delete;

	// Move operator
	SmartPointer<DataType>& operator=(SmartPointer<DataType>&& new_ptr) noexcept
	{
		if (this != &new_ptr)
		{
			delete ptr;

			ptr = new_ptr.ptr;

			new_ptr.ptr = nullptr;
		}

		return *this;
	}

	// Dereferencing pointer operator
	DataType& operator*()
	{
		return *ptr;
	}

	// Arrow pointer operator
	DataType* operator->()
	{
		return ptr;
	}
};
