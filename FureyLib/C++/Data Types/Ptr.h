
// Smart Pointer Classes
// by Kyle Furey

// REFERENCE: https://blog.devgenius.io/unique-pointer-and-implementation-in-c-ec6599a518e5

#pragma once
#include <map>

// Include this heading to use the classes
#include "Ptr.h"

// Forward declaration of the ptr class
template <typename DataType> class ptr;

// •  Base class for the pointer classes.
// •  Used as type safe storage for pointers of varying types.
// •  Provides a virtual destructor for the pointer classes to properly destroy its pointer regardless of their type.
class ptr_base
{
public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	ptr_base() { }

	// Pointer constructor
	template<typename DataType> ptr_base(DataType* data)
	{
		*this = ptr<DataType>(data);
	}

	// Virtual deconstructor used to properly deallocate the pointer class's pointer
	virtual ~ptr_base() { }


	// GET POINTER

	// Cast to shared pointer
	template<typename DataType> ptr<DataType>& get()
	{
		return *((ptr<DataType>*)this);
	}


	// ASSIGNMENT OPERATORS

	// Pointer assignment operator
	template<typename DataType> ptr<DataType> operator=(DataType* data)
	{
		return ptr<DataType>(data);
	}
};

// •  A wrapper for a newly created pointer that automatically deallocates on deconstruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the ptr_base storage class.
template <typename DataType> class ptr : public ptr_base
{
protected:

	// POINTER

	// The stored pointer
	DataType* data = nullptr;


	// COUNT

	// The total number of pointers to this pointer's memory (deallocates when this is the last pointer)
	static std::map<DataType*, int> count;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	ptr(DataType* ptr = nullptr)
	{
		// Set the pointer
		data = ptr;

		// Check if the data is not null
		if (ptr != nullptr)
		{
			// Increment the pointer count
			count[ptr]++;
		}
	}

	// Copy constructor
	ptr(const ptr<DataType>& ptr)
	{
		// Set the pointer
		data = ptr.data;

		// Check if the data is not null
		if (ptr.data != nullptr)
		{
			// Increment the pointer count
			count[ptr.data]++;
		}
	}

	// Move constructor
	ptr(ptr<DataType>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Deconstructor
	virtual ~ptr()
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete data;
			}

			data = nullptr;
		}
	}


	// FUNCTIONS

	// Delete cast
	template<typename DataType> ptr<DataType>& get() = delete;

	// Releases and returns the pointer
	virtual DataType* release()
	{
		DataType* ptr = data;

		if (data != nullptr)
		{
			count[data]--;

			data = nullptr;
		}

		return ptr;
	}

	// Resets the pointer
	virtual ptr<DataType>& reset(DataType* ptr = nullptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete data;
			}

			data = nullptr;
		}

		// Set the pointer
		data = ptr;

		// Check if the data is not null
		if (ptr != nullptr)
		{
			// Increment the pointer count
			count[ptr]++;
		}

		return *this;
	}

	// Resets the pointer
	virtual ptr<DataType>& reset(ptr<DataType>& ptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete data;
			}

			data = nullptr;
		}

		// Set the pointer
		data = ptr.data;

		// Check if the data is not null
		if (ptr.data != nullptr)
		{
			// Increment the pointer count
			count[ptr.data]++;
		}

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual ptr<DataType>& swap(DataType*& ptr)
	{
		if (this->data != nullptr)
		{
			// Decrement the pointer count
			count[this->data]--;
		}

		DataType* data = this->data;

		this->data = ptr;

		ptr = data;

		// Check if the data is not null
		if (ptr != nullptr)
		{
			// Increment the pointer count
			count[ptr]++;
		}

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual ptr<DataType>& swap(ptr<DataType>& ptr)
	{
		DataType* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual ptr<DataType>& destroy()
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete data;
			}

			data = nullptr;
		}

		// Set the pointer
		data = nullptr;

		return *this;
	}

	// Returns whether the pointer is null
	virtual bool is_null()
	{
		return data == nullptr;
	}

	// Returns whether the pointer is null
	virtual bool is_not_null()
	{
		return data != nullptr;
	}

	// Returns the total number of pointers sharing this pointer
	virtual int total()
	{
		if (data == nullptr)
		{
			return 0;
		}

		return count[data];
	}

	// Returns the total number of pointers sharing the given pointer
	static int total(DataType* ptr)
	{
		if (ptr == nullptr || !count.count(ptr))
		{
			return 0;
		}

		return count[ptr];
	}

	// Returns the total number of pointers sharing the given pointer
	static int total(ptr<DataType>& ptr)
	{
		if (ptr.data == nullptr || !count.count(ptr.data))
		{
			return 0;
		}

		return count[ptr.data];
	}

	// Returns if the given pointer is unique
	virtual bool is_unique()
	{
		if (data == nullptr)
		{
			return false;
		}

		return count[data] == 1;
	}

	// Returns if the given pointer is unique
	static bool is_unique(DataType* ptr)
	{
		if (ptr == nullptr || !count.count(ptr))
		{
			return false;
		}

		return count[ptr] == 1;
	}

	// Returns if the given pointer is unique
	static bool is_unique(ptr<DataType>& ptr)
	{
		if (ptr.data == nullptr || !count.count(ptr.data))
		{
			return false;
		}

		return count[ptr.data] == 1;
	}


	// OPERATORS

	// Copy assignment operator
	virtual ptr<DataType>& operator=(DataType* ptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete data;
			}
		}

		// Set the pointer
		data = ptr;

		// Check if the data is not null
		if (ptr != nullptr)
		{
			// Increment the pointer count
			count[ptr]++;
		}

		return *this;
	}

	// Copy assignment operator
	virtual ptr<DataType>& operator=(const ptr<DataType>& ptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete data;
			}
		}

		// Set the pointer
		data = ptr.data;

		// Check if the data is not null
		if (ptr.data != nullptr)
		{
			// Increment the pointer count
			count[ptr.data]++;
		}

		return *this;
	}

	// Move assignment operator
	virtual ptr<DataType>& operator=(ptr<DataType>&& ptr) noexcept
	{
		if (this != &ptr)
		{
			if (data != nullptr)
			{
				// Decrement the pointer count
				count[data]--;

				if (count[data] <= 0)
				{
					delete data;
				}
			}

			data = ptr.data;

			ptr.data = nullptr;
		}

		return *this;
	}

	// Dereferencing pointer operator
	virtual DataType& operator*()
	{
		return *data;
	}

	// Arrow pointer operator
	virtual DataType* operator->()
	{
		return data;
	}

	// Equality operator
	virtual bool operator==(DataType* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(ptr<DataType>&& ptr)
	{
		return data = ptr.data;
	}

	// Null check operator
	virtual operator bool()
	{
		return data != nullptr;
	}

	// Null check operator
	virtual bool operator!()
	{
		return data == nullptr;
	}
};

// Static variable initialization
template <typename DataType> std::map<DataType*, int> ptr<DataType>::count = std::map<DataType*, int>();

// •  A wrapper for a newly created pointer that automatically deallocates on deconstruction.
// •  Pointer is unique and only allows one pointer to the stored memory at a time.
// •  Inherits from the ptr_base storage class.
template <typename DataType> class uptr : public ptr_base
{
protected:

	// POINTER

	// The stored pointer
	DataType* data = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	uptr(DataType* ptr = nullptr)
	{
		// Set the pointer
		data = ptr;
	}

	// Remove copy constructor
	uptr(const uptr<DataType>& ptr) = delete;

	// Move constructor
	uptr(uptr<DataType>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Deconstructor
	virtual ~uptr()
	{
		delete data;

		data = nullptr;
	}


	// FUNCTIONS

	// Delete cast
	template<typename DataType> ptr<DataType>& get() = delete;

	// Releases and returns the pointer
	virtual DataType* release()
	{
		DataType* ptr = data;

		data = nullptr;

		return ptr;
	}

	// Resets the pointer
	virtual uptr<DataType>& reset(DataType* ptr = nullptr)
	{
		delete data;

		data = ptr;

		return *this;
	}

	// Resets the pointer
	virtual uptr<DataType>& reset(uptr<DataType>& ptr)
	{
		delete data;

		data = ptr.data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual uptr<DataType>& swap(DataType*& ptr)
	{
		DataType* data = this->data;

		this->data = ptr;

		ptr = data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual uptr<DataType>& swap(uptr<DataType>& ptr)
	{
		DataType* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual uptr<DataType>& destroy()
	{
		delete data;

		data = nullptr;

		return *this;
	}

	// Returns whether the pointer is null
	virtual bool is_null()
	{
		return data == nullptr;
	}

	// Returns whether the pointer is null
	virtual bool is_not_null()
	{
		return data != nullptr;
	}


	// OPERATORS

	// Remove copy assignment operator
	virtual uptr<DataType>& operator=(DataType* ptr) = delete;

	// Remove copy assignment operator
	virtual uptr<DataType>& operator=(const uptr<DataType>&) = delete;

	// Move assignment operator
	virtual uptr<DataType>& operator=(uptr<DataType>&& ptr) noexcept
	{
		if (this != &ptr)
		{
			delete data;

			data = ptr.data;

			ptr.data = nullptr;
		}

		return *this;
	}

	// Dereferencing pointer operator
	virtual DataType& operator*()
	{
		return *data;
	}

	// Arrow pointer operator
	virtual DataType* operator->()
	{
		return data;
	}

	// Equality operator
	virtual bool operator==(DataType* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(uptr<DataType>&& ptr)
	{
		return data = ptr.data;
	}

	// Null check operator
	virtual operator bool()
	{
		return data != nullptr;
	}

	// Null check operator
	virtual bool operator!()
	{
		return data == nullptr;
	}
};

// Forward declaration of the pointer class
template <typename DataType> class Pointer;

// •  Base class for the pointer classes.
// •  Used as type safe storage for pointers of varying types.
// •  Provides a virtual destructor for the pointer classes to properly destroy its pointer regardless of their type.
class PointerBase
{
public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	PointerBase() { }

	// Pointer constructor
	template<typename DataType> PointerBase(DataType* data)
	{
		*this = Pointer<DataType>(data);
	}

	// Virtual deconstructor used to properly deallocate the pointer class's pointer
	virtual ~PointerBase() { }


	// GET POINTER

	// Cast to shared pointer
	template<typename DataType> Pointer<DataType>& Get()
	{
		return *((Pointer<DataType>*)this);
	}


	// ASSIGNMENT OPERATORS

	// Pointer assignment operator
	template<typename DataType> Pointer<DataType> operator=(DataType* data)
	{
		return Pointer<DataType>(data);
	}
};

// •  A wrapper for a newly created pointer that automatically deallocates on deconstruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the ptr_base storage class.
template <typename DataType> class Pointer : public PointerBase
{
protected:

	// POINTER

	// The stored pointer
	DataType* data = nullptr;


	// COUNT

	// The total number of pointers to this pointer's memory (deallocates when this is the last pointer)
	static std::map<DataType*, int> count;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	Pointer(DataType* ptr = nullptr)
	{
		// Set the pointer
		data = ptr;

		// Check if the data is not null
		if (ptr != nullptr)
		{
			// Increment the pointer count
			count[ptr]++;
		}
	}

	// Copy constructor
	Pointer(const Pointer<DataType>& ptr)
	{
		// Set the pointer
		data = ptr.data;

		// Check if the data is not null
		if (ptr.data != nullptr)
		{
			// Increment the pointer count
			count[ptr.data]++;
		}
	}

	// Move constructor
	Pointer(Pointer<DataType>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Deconstructor
	virtual ~Pointer()
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete data;
			}

			data = nullptr;
		}
	}


	// FUNCTIONS

	// Delete cast
	template<typename DataType> Pointer<DataType>& Get() = delete;

	// Releases and returns the pointer
	virtual DataType* Release()
	{
		DataType* ptr = data;

		if (data != nullptr)
		{
			count[data]--;

			data = nullptr;
		}

		return ptr;
	}

	// Resets the pointer
	virtual Pointer<DataType>& Reset(DataType* ptr = nullptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete data;
			}

			data = nullptr;
		}

		// Set the pointer
		data = ptr;

		// Check if the data is not null
		if (ptr != nullptr)
		{
			// Increment the pointer count
			count[ptr]++;
		}

		return *this;
	}

	// Resets the pointer
	virtual Pointer<DataType>& Reset(Pointer<DataType>& ptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete data;
			}

			data = nullptr;
		}

		// Set the pointer
		data = ptr.data;

		// Check if the data is not null
		if (ptr.data != nullptr)
		{
			// Increment the pointer count
			count[ptr.data]++;
		}

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual Pointer<DataType>& Swap(DataType*& ptr)
	{
		if (this->data != nullptr)
		{
			// Decrement the pointer count
			count[this->data]--;
		}

		DataType* data = this->data;

		this->data = ptr;

		ptr = data;

		// Check if the data is not null
		if (ptr != nullptr)
		{
			// Increment the pointer count
			count[ptr]++;
		}

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual Pointer<DataType>& Swap(Pointer<DataType>& ptr)
	{
		DataType* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual Pointer<DataType>& Destroy()
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete data;
			}

			data = nullptr;
		}

		// Set the pointer
		data = nullptr;

		return *this;
	}

	// Returns whether the pointer is null
	virtual bool IsNull()
	{
		return data == nullptr;
	}

	// Returns whether the pointer is null
	virtual bool IsNotNull()
	{
		return data != nullptr;
	}

	// Returns the total number of pointers sharing this pointer
	virtual int Total()
	{
		if (data == nullptr)
		{
			return 0;
		}

		return count[data];
	}

	// Returns the total number of pointers sharing the given pointer
	static int Total(DataType* ptr)
	{
		if (ptr == nullptr || !count.count(ptr))
		{
			return 0;
		}

		return count[ptr];
	}

	// Returns the total number of pointers sharing the given pointer
	static int Total(Pointer<DataType>& ptr)
	{
		if (ptr.data == nullptr || !count.count(ptr.data))
		{
			return 0;
		}

		return count[ptr.data];
	}

	// Returns if the given pointer is unique
	virtual bool IsUnique()
	{
		if (data == nullptr)
		{
			return false;
		}

		return count[data] == 1;
	}

	// Returns if the given pointer is unique
	static bool IsUnique(DataType* ptr)
	{
		if (ptr == nullptr || !count.count(ptr))
		{
			return false;
		}

		return count[ptr] == 1;
	}

	// Returns if the given pointer is unique
	static bool IsUnique(ptr<DataType>& ptr)
	{
		if (ptr.data == nullptr || !count.count(ptr.data))
		{
			return false;
		}

		return count[ptr.data] == 1;
	}


	// OPERATORS

	// Copy assignment operator
	virtual Pointer<DataType>& operator=(DataType* ptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete data;
			}
		}

		// Set the pointer
		data = ptr;

		// Check if the data is not null
		if (ptr != nullptr)
		{
			// Increment the pointer count
			count[ptr]++;
		}

		return *this;
	}

	// Copy assignment operator
	virtual Pointer<DataType>& operator=(const Pointer<DataType>& ptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete data;
			}
		}

		// Set the pointer
		data = ptr.data;

		// Check if the data is not null
		if (ptr.data != nullptr)
		{
			// Increment the pointer count
			count[ptr.data]++;
		}

		return *this;
	}

	// Move assignment operator
	virtual Pointer<DataType>& operator=(Pointer<DataType>&& ptr) noexcept
	{
		if (this != &ptr)
		{
			if (data != nullptr)
			{
				// Decrement the pointer count
				count[data]--;

				if (count[data] <= 0)
				{
					delete data;
				}
			}

			data = ptr.data;

			ptr.data = nullptr;
		}

		return *this;
	}

	// Dereferencing pointer operator
	virtual DataType& operator*()
	{
		return *data;
	}

	// Arrow pointer operator
	virtual DataType* operator->()
	{
		return data;
	}

	// Equality operator
	virtual bool operator==(DataType* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(Pointer<DataType>&& ptr)
	{
		return data = ptr.data;
	}

	// Null check operator
	virtual operator bool()
	{
		return data != nullptr;
	}

	// Null check operator
	virtual bool operator!()
	{
		return data == nullptr;
	}
};

// Static variable initialization
template <typename DataType> std::map<DataType*, int> Pointer<DataType>::count = std::map<DataType*, int>();

// •  A wrapper for a newly created pointer that automatically deallocates on deconstruction.
// •  Pointer is unique and only allows one pointer to the stored memory at a time.
// •  Inherits from the ptr_base storage class.
template <typename DataType> class UniquePointer : public PointerBase
{
protected:

	// POINTER

	// The stored pointer
	DataType* data = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	UniquePointer(DataType* ptr = nullptr)
	{
		// Set the pointer
		data = ptr;
	}

	// Remove copy constructor
	UniquePointer(const UniquePointer<DataType>& ptr) = delete;

	// Move constructor
	UniquePointer(UniquePointer<DataType>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Deconstructor
	virtual ~UniquePointer()
	{
		delete data;

		data = nullptr;
	}


	// FUNCTIONS

	// Delete cast
	template<typename DataType> Pointer<DataType>& Get() = delete;

	// Releases and returns the pointer
	virtual DataType* Release()
	{
		DataType* ptr = data;

		data = nullptr;

		return ptr;
	}

	// Resets the pointer
	virtual UniquePointer<DataType>& Reset(DataType* ptr = nullptr)
	{
		delete data;

		data = ptr;

		return *this;
	}

	// Resets the pointer
	virtual UniquePointer<DataType>& Reset(UniquePointer<DataType>& ptr)
	{
		delete data;

		data = ptr.data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual UniquePointer<DataType>& Swap(DataType*& ptr)
	{
		DataType* data = this->data;

		this->data = ptr;

		ptr = data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual UniquePointer<DataType>& Swap(UniquePointer<DataType>& ptr)
	{
		DataType* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual UniquePointer<DataType>& Destroy()
	{
		delete data;

		data = nullptr;

		return *this;
	}

	// Returns whether the pointer is null
	virtual bool IsNull()
	{
		return data == nullptr;
	}

	// Returns whether the pointer is null
	virtual bool IsNotNull()
	{
		return data != nullptr;
	}


	// OPERATORS

	// Remove copy assignment operator
	virtual UniquePointer<DataType>& operator=(DataType* ptr) = delete;

	// Remove copy assignment operator
	virtual UniquePointer<DataType>& operator=(const UniquePointer<DataType>&) = delete;

	// Move assignment operator
	virtual UniquePointer<DataType>& operator=(UniquePointer<DataType>&& ptr) noexcept
	{
		if (this != &ptr)
		{
			delete data;

			data = ptr.data;

			ptr.data = nullptr;
		}

		return *this;
	}

	// Dereferencing pointer operator
	virtual DataType& operator*()
	{
		return *data;
	}

	// Arrow pointer operator
	virtual DataType* operator->()
	{
		return data;
	}

	// Equality operator
	virtual bool operator==(DataType* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(UniquePointer<DataType>&& ptr)
	{
		return data = ptr.data;
	}

	// Null check operator
	virtual operator bool()
	{
		return data != nullptr;
	}

	// Null check operator
	virtual bool operator!()
	{
		return data == nullptr;
	}
};
