
// Smart Pointer Class
// by Kyle Furey

// REFERENCE: https://blog.devgenius.io/unique-pointer-and-implementation-in-c-ec6599a518e5

#pragma once

// Include this heading to use the class
#include "SmartPtr.h"

// Smart Pointer Class
template <class DataType> class smart_ptr
{
private:

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

	// Assignment operator
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

// Smart Pointer Class
template <class DataType> class SmartPtr
{
private:

	// The stored pointer
	DataType* Ptr = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	SmartPtr(DataType* new_ptr = nullptr)
	{
		// Set the pointer
		Ptr = new_ptr;
	}

	// Remove copy constructor
	SmartPtr(const SmartPtr<DataType>& new_ptr) = delete;

	// Move construtor
	SmartPtr(SmartPtr<DataType>&& new_ptr) noexcept
	{
		Ptr = new_ptr.Ptr;

		new_ptr.Ptr = nullptr;
	}

	// Deconstructor
	~SmartPtr()
	{
		delete Ptr;

		Ptr = nullptr;
	}


	// FUNCTIONS

	// Release function
	DataType* Release()
	{
		DataType* new_ptr = Ptr;

		Ptr = nullptr;

		return new_ptr;
	}

	// Reset function
	SmartPtr<DataType>& Reset(DataType* new_ptr = nullptr)
	{
		delete Ptr;

		Ptr = new_ptr;

		return *this;
	}

	// Delete function
	SmartPtr<DataType>& Destroy()
	{
		return Reset(nullptr);
	}


	// OPERATORS

	// Remove assignment operator
	SmartPtr<DataType>& operator=(DataType* new_ptr) = delete;

	// Assignment operator
	SmartPtr<DataType>& operator=(SmartPtr<DataType>&& new_ptr) noexcept
	{
		if (this != &new_ptr)
		{
			delete Ptr;

			Ptr = new_ptr.Ptr;

			new_ptr.Ptr = nullptr;
		}

		return *this;
	}

	// Dereferencing pointer operator
	DataType& operator*()
	{
		return *Ptr;
	}

	// Arrow pointer operator
	DataType* operator->()
	{
		return Ptr;
	}
};
