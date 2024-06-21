
// Smart Pointer Classes
// by Kyle Furey

// REFERENCES: https://blog.devgenius.io/unique-pointer-and-implementation-in-c-ec6599a518e5, https://www.geeksforgeeks.org/smart-pointers-cpp/

#pragma once
#include <map>

// Include this heading to use the classes
#include "Ptr.h"

// Forward declaration of the ptr class
template <typename DataType> class sptr;

// •  Base class for the smart pointer classes.
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
		*this = sptr<DataType>(data);
	}

	// Virtual deconstructor used to properly deallocate the pointer class's pointer
	virtual ~ptr_base() { }


	// GET POINTER

	// Cast to shared pointer
	template<typename DataType> sptr<DataType>& get()
	{
		return *((sptr<DataType>*)this);
	}


	// ASSIGNMENT OPERATORS

	// Pointer assignment operator
	template<typename DataType> sptr<DataType> operator=(DataType* data)
	{
		return sptr<DataType>(data);
	}
};

// •  A wrapper for a newly created pointer that automatically deallocates on deconstruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the ptr_base storage class.
template <typename DataType> class sptr : public ptr_base
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
	sptr(DataType* ptr = nullptr)
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
	sptr(const sptr<DataType>& ptr)
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
	sptr(sptr<DataType>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Deconstructor
	virtual ~sptr()
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
	template<typename DataType> sptr<DataType>& get() = delete;

	// Returns a pointer to the given data
	virtual DataType* get()
	{
		return data;
	}

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
	virtual sptr<DataType>& reset(DataType* ptr = nullptr)
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
	virtual sptr<DataType>& reset(sptr<DataType>& ptr)
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
	virtual sptr<DataType>& swap(DataType*& ptr)
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
	virtual sptr<DataType>& swap(sptr<DataType>& ptr)
	{
		DataType* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual sptr<DataType>& destroy()
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
	static int total(sptr<DataType>& ptr)
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
	static bool is_unique(sptr<DataType>& ptr)
	{
		if (ptr.data == nullptr || !count.count(ptr.data))
		{
			return false;
		}

		return count[ptr.data] == 1;
	}


	// OPERATORS

	// Copy assignment operator
	virtual sptr<DataType>& operator=(DataType* ptr)
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
	virtual sptr<DataType>& operator=(const sptr<DataType>& ptr)
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
	virtual sptr<DataType>& operator=(sptr<DataType>&& ptr) noexcept
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
	virtual bool operator==(sptr<DataType>&& ptr)
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

// •  A wrapper for a newly created array pointer that automatically deallocates on deconstruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the ptr_base storage class.
template <typename DataType> class sptr<DataType[]> : public ptr_base
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
	sptr(DataType* ptr = nullptr)
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
	sptr(const sptr<DataType[]>& ptr)
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
	sptr(sptr<DataType[]>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Deconstructor
	virtual ~sptr()
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete[] data;
			}

			data = nullptr;
		}
	}


	// FUNCTIONS

	// Delete cast
	template<typename DataType> sptr<DataType[]>& get() = delete;

	// Returns a pointer to the given data
	virtual DataType* get()
	{
		return data;
	}

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
	virtual sptr<DataType[]>& reset(DataType* ptr = nullptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete[] data;
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
	virtual sptr<DataType[]>& reset(sptr<DataType[]>& ptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete[] data;
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
	virtual sptr<DataType[]>& swap(DataType*& ptr)
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
	virtual sptr<DataType[]>& swap(sptr<DataType[]>& ptr)
	{
		DataType* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual sptr<DataType[]>& destroy()
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete[] data;
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
	static int total(sptr<DataType[]>& ptr)
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
	static bool is_unique(sptr<DataType[]>& ptr)
	{
		if (ptr.data == nullptr || !count.count(ptr.data))
		{
			return false;
		}

		return count[ptr.data] == 1;
	}


	// OPERATORS

	// Copy assignment operator
	virtual sptr<DataType[]>& operator=(DataType* ptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete[] data;
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
	virtual sptr<DataType[]>& operator=(const sptr<DataType[]>& ptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete[] data;
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
	virtual sptr<DataType[]>& operator=(sptr<DataType[]>&& ptr) noexcept
	{
		if (this != &ptr)
		{
			if (data != nullptr)
			{
				// Decrement the pointer count
				count[data]--;

				if (count[data] <= 0)
				{
					delete[] data;
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

	// Array index operator
	virtual DataType& operator[](int index)
	{
		return data[index];
	}

	// Equality operator
	virtual bool operator==(DataType* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(sptr<DataType[]>&& ptr)
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

// •  A wrapper for a newly created void pointer that automatically deallocates on deconstruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the ptr_base storage class.
template <> class sptr<void> : public ptr_base
{
protected:

	// POINTER

	// The stored pointer
	void* data = nullptr;


	// COUNT

	// The total number of pointers to this pointer's memory (deallocates when this is the last pointer)
	static std::map<void*, int> count;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	sptr(void* ptr = nullptr)
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
	sptr(const sptr<void>& ptr)
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
	sptr(sptr<void>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Deconstructor
	virtual ~sptr()
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
	template<typename DataType> sptr<DataType>& get() = delete;

	// Returns a pointer to the given data
	virtual void* get()
	{
		return data;
	}

	// Releases and returns the pointer
	virtual void* release()
	{
		void* ptr = data;

		if (data != nullptr)
		{
			count[data]--;

			data = nullptr;
		}

		return ptr;
	}

	// Resets the pointer
	virtual sptr<void>& reset(void* ptr = nullptr)
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
	virtual sptr<void>& reset(sptr<void>& ptr)
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
	virtual sptr<void>& swap(void*& ptr)
	{
		if (this->data != nullptr)
		{
			// Decrement the pointer count
			count[this->data]--;
		}

		void* data = this->data;

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
	virtual sptr<void>& swap(sptr<void>& ptr)
	{
		void* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual sptr<void>& destroy()
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
	static int total(void* ptr)
	{
		if (ptr == nullptr || !count.count(ptr))
		{
			return 0;
		}

		return count[ptr];
	}

	// Returns the total number of pointers sharing the given pointer
	static int total(sptr<void>& ptr)
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
	static bool is_unique(void* ptr)
	{
		if (ptr == nullptr || !count.count(ptr))
		{
			return false;
		}

		return count[ptr] == 1;
	}

	// Returns if the given pointer is unique
	static bool is_unique(sptr<void>& ptr)
	{
		if (ptr.data == nullptr || !count.count(ptr.data))
		{
			return false;
		}

		return count[ptr.data] == 1;
	}


	// OPERATORS

	// Copy assignment operator
	virtual sptr<void>& operator=(void* ptr)
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
	virtual sptr<void>& operator=(const sptr<void>& ptr)
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
	virtual sptr<void>& operator=(sptr<void>&& ptr) noexcept
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

	// Equality operator
	virtual bool operator==(void* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(sptr<void>&& ptr)
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
template <typename DataType> std::map<DataType*, int> sptr<DataType>::count = std::map<DataType*, int>();
template <typename DataType> std::map<DataType*, int> sptr<DataType[]>::count = std::map<DataType*, int>();
std::map<void*, int> sptr<void>::count = std::map<void*, int>();

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
	template<typename DataType> sptr<DataType>& get() = delete;

	// Returns a pointer to the given data
	virtual DataType* get()
	{
		return data;
	}

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

// •  A wrapper for a newly created array pointer that automatically deallocates on deconstruction.
// •  Pointer is unique and only allows one pointer to the stored memory at a time.
// •  Inherits from the ptr_base storage class.
template <typename DataType> class uptr<DataType[]> : public ptr_base
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
	uptr(const uptr<DataType[]>& ptr) = delete;

	// Move constructor
	uptr(uptr<DataType[]>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Deconstructor
	virtual ~uptr()
	{
		delete[] data;

		data = nullptr;
	}


	// FUNCTIONS

	// Delete cast
	template<typename DataType> sptr<DataType[]>& get() = delete;

	// Returns a pointer to the given data
	virtual DataType* get()
	{
		return data;
	}

	// Releases and returns the pointer
	virtual DataType* release()
	{
		DataType* ptr = data;

		data = nullptr;

		return ptr;
	}

	// Resets the pointer
	virtual uptr<DataType[]>& reset(DataType* ptr = nullptr)
	{
		delete[] data;

		data = ptr;

		return *this;
	}

	// Resets the pointer
	virtual uptr<DataType[]>& reset(uptr<DataType[]>& ptr)
	{
		delete[] data;

		data = ptr.data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual uptr<DataType[]>& swap(DataType*& ptr)
	{
		DataType* data = this->data;

		this->data = ptr;

		ptr = data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual uptr<DataType[]>& swap(uptr<DataType[]>& ptr)
	{
		DataType* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual uptr<DataType[]>& destroy()
	{
		delete[] data;

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
	virtual uptr<DataType[]>& operator=(DataType* ptr) = delete;

	// Remove copy assignment operator
	virtual uptr<DataType[]>& operator=(const uptr<DataType[]>&) = delete;

	// Move assignment operator
	virtual uptr<DataType[]>& operator=(uptr<DataType[]>&& ptr) noexcept
	{
		if (this != &ptr)
		{
			delete[] data;

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

	// Array index operator
	virtual DataType& operator[](int index)
	{
		return data[index];
	}

	// Equality operator
	virtual bool operator==(DataType* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(uptr<DataType[]>&& ptr)
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

// •  A wrapper for a newly created void pointer that automatically deallocates on deconstruction.
// •  Pointer is unique and only allows one pointer to the stored memory at a time.
// •  Inherits from the ptr_base storage class.
template <> class uptr<void> : public ptr_base
{
protected:

	// POINTER

	// The stored pointer
	void* data = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	uptr(void* ptr = nullptr)
	{
		// Set the pointer
		data = ptr;
	}

	// Remove copy constructor
	uptr(const uptr<void>& ptr) = delete;

	// Move constructor
	uptr(uptr<void>&& ptr) noexcept
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
	template<typename DataType> sptr<DataType>& get() = delete;

	// Returns a pointer to the given data
	virtual void* get()
	{
		return data;
	}

	// Releases and returns the pointer
	virtual void* release()
	{
		void* ptr = data;

		data = nullptr;

		return ptr;
	}

	// Resets the pointer
	virtual uptr<void>& reset(void* ptr = nullptr)
	{
		delete data;

		data = ptr;

		return *this;
	}

	// Resets the pointer
	virtual uptr<void>& reset(uptr<void>& ptr)
	{
		delete data;

		data = ptr.data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual uptr<void>& swap(void*& ptr)
	{
		void* data = this->data;

		this->data = ptr;

		ptr = data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual uptr<void>& swap(uptr<void>& ptr)
	{
		void* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual uptr<void>& destroy()
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
	virtual uptr<void>& operator=(void* ptr) = delete;

	// Remove copy assignment operator
	virtual uptr<void>& operator=(const uptr<void>&) = delete;

	// Move assignment operator
	virtual uptr<void>& operator=(uptr<void>&& ptr) noexcept
	{
		if (this != &ptr)
		{
			delete data;

			data = ptr.data;

			ptr.data = nullptr;
		}

		return *this;
	}

	// Equality operator
	virtual bool operator==(void* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(uptr<void>&& ptr)
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

// •  A wrapper for a shared pointer that does not own the original pointer: a weak pointer.
// •  Useful if there is a circular dependency between shared pointers to ensure memory does not persist.
// •  Use check() and get() to test and receive a shared pointer of the original pointer.
// •  Inherits from the ptr_base storage class.
template <typename DataType> class wptr : public ptr_base
{
protected:

	// POINTER

	// The stored pointer
	sptr<DataType>* shared = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	wptr() { shared = nullptr; }

	// Shared pointer constructor
	wptr(sptr<DataType>& shared)
	{
		this->shared = &shared;
	}

	// Deconstructor
	virtual ~wptr() { }


	// FUNCTIONS

	// Delete cast
	template<typename DataType> sptr<DataType>& get() = delete;

	// Check if the shared pointer is valid
	virtual bool check()
	{
		return shared->is_not_null();
	}

	// Receive the shared pointer
	virtual sptr<DataType> get()
	{
		return *shared;
	}


	// OPERATORS

	// Set the shared pointer
	virtual wptr<DataType>& operator=(sptr<DataType>& shared)
	{
		this->shared = &shared;

		return *this;
	}

	// Receive the shared pointer
	virtual sptr<DataType> operator*()
	{
		return *shared;
	}

	// Check if the shared pointer is valid
	virtual operator bool()
	{
		return shared->is_not_null();
	}
};

// •  A wrapper for a shared array pointer that does not own the original pointer: a weak pointer.
// •  Useful if there is a circular dependency between shared pointers to ensure memory does not persist.
// •  Use check() and get() to test and receive a shared pointer of the original pointer.
// •  Inherits from the ptr_base storage class.
template <typename DataType> class wptr<DataType[]> : public ptr_base
{
protected:

	// POINTER

	// The stored pointer
	sptr<DataType[]>* shared = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	wptr() { shared = nullptr; }

	// Shared pointer constructor
	wptr(sptr<DataType[]>& shared)
	{
		this->shared = &shared;
	}

	// Deconstructor
	virtual ~wptr() { }


	// FUNCTIONS

	// Delete cast
	template<typename DataType> sptr<DataType[]>& get() = delete;

	// Check if the shared pointer is valid
	virtual bool check()
	{
		return shared->is_not_null();
	}

	// Receive the shared pointer
	virtual sptr<DataType[]> get()
	{
		return *shared;
	}


	// OPERATORS

	// Set the shared pointer
	virtual wptr<DataType[]>& operator=(sptr<DataType[]>& shared)
	{
		this->shared = &shared;

		return *this;
	}

	// Receive the shared pointer
	virtual sptr<DataType[]> operator*()
	{
		return *shared;
	}

	// Check if the shared pointer is valid
	virtual operator bool()
	{
		return shared->is_not_null();
	}
};

// •  A wrapper for a shared void pointer that does not own the original pointer: a weak pointer.
// •  Useful if there is a circular dependency between shared pointers to ensure memory does not persist.
// •  Use check() and get() to test and receive a shared pointer of the original pointer.
// •  Inherits from the ptr_base storage class.
template <> class wptr<void> : public ptr_base
{
protected:

	// POINTER

	// The stored pointer
	sptr<void>* shared = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	wptr() { shared = nullptr; }

	// Shared pointer constructor
	wptr(sptr<void>& shared)
	{
		this->shared = &shared;
	}

	// Deconstructor
	virtual ~wptr() { }


	// FUNCTIONS

	// Delete cast
	template<typename DataType> sptr<DataType>& get() = delete;

	// Check if the shared pointer is valid
	virtual bool check()
	{
		return shared->is_not_null();
	}

	// Receive the shared pointer
	virtual sptr<void> get()
	{
		return *shared;
	}


	// OPERATORS

	// Set the shared pointer
	virtual wptr<void>& operator=(sptr<void>& shared)
	{
		this->shared = &shared;

		return *this;
	}

	// Receive the shared pointer
	virtual sptr<void> operator*()
	{
		return *shared;
	}

	// Check if the shared pointer is valid
	virtual operator bool()
	{
		return shared->is_not_null();
	}
};

// Forward declaration of the Pointer class
template <typename DataType> class SharedPointer;

// •  Base class for the smart pointer classes.
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
		*this = SharedPointer<DataType>(data);
	}

	// Virtual deconstructor used to properly deallocate the pointer class's pointer
	virtual ~PointerBase() { }


	// GET POINTER

	// Cast to shared pointer
	template<typename DataType> SharedPointer<DataType>& Get()
	{
		return *((SharedPointer<DataType>*)this);
	}


	// ASSIGNMENT OPERATORS

	// Pointer assignment operator
	template<typename DataType> SharedPointer<DataType> operator=(DataType* data)
	{
		return SharedPointer<DataType>(data);
	}
};

// •  A wrapper for a newly created pointer that automatically deallocates on deconstruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the PointerBase storage class.
template <typename DataType> class SharedPointer : public PointerBase
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
	SharedPointer(DataType* ptr = nullptr)
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
	SharedPointer(const SharedPointer<DataType>& ptr)
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
	SharedPointer(SharedPointer<DataType>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Deconstructor
	virtual ~SharedPointer()
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
	template<typename DataType> SharedPointer<DataType>& get() = delete;

	// Returns a pointer to the given data
	virtual DataType* Get()
	{
		return data;
	}

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
	virtual SharedPointer<DataType>& Reset(DataType* ptr = nullptr)
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
	virtual SharedPointer<DataType>& Reset(SharedPointer<DataType>& ptr)
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
	virtual SharedPointer<DataType>& Swap(DataType*& ptr)
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
	virtual SharedPointer<DataType>& Swap(SharedPointer<DataType>& ptr)
	{
		DataType* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual SharedPointer<DataType>& Destroy()
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
	static int Total(SharedPointer<DataType>& ptr)
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
	static bool IsUnique(SharedPointer<DataType>& ptr)
	{
		if (ptr.data == nullptr || !count.count(ptr.data))
		{
			return false;
		}

		return count[ptr.data] == 1;
	}


	// OPERATORS

	// Copy assignment operator
	virtual SharedPointer<DataType>& operator=(DataType* ptr)
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
	virtual SharedPointer<DataType>& operator=(const SharedPointer<DataType>& ptr)
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
	virtual SharedPointer<DataType>& operator=(SharedPointer<DataType>&& ptr) noexcept
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
	virtual bool operator==(SharedPointer<DataType>&& ptr)
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

// •  A wrapper for a newly created array pointer that automatically deallocates on deconstruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the PointerBase storage class.
template <typename DataType> class SharedPointer<DataType[]> : public PointerBase
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
	SharedPointer(DataType* ptr = nullptr)
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
	SharedPointer(const SharedPointer<DataType[]>& ptr)
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
	SharedPointer(SharedPointer<DataType[]>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Deconstructor
	virtual ~SharedPointer()
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete[] data;
			}

			data = nullptr;
		}
	}


	// FUNCTIONS

	// Delete cast
	template<typename DataType> SharedPointer<DataType[]>& get() = delete;

	// Returns a pointer to the given data
	virtual DataType* Get()
	{
		return data;
	}

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
	virtual SharedPointer<DataType[]>& Reset(DataType* ptr = nullptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete[] data;
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
	virtual SharedPointer<DataType[]>& Reset(SharedPointer<DataType[]>& ptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete[] data;
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
	virtual SharedPointer<DataType[]>& Swap(DataType*& ptr)
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
	virtual SharedPointer<DataType[]>& Swap(SharedPointer<DataType[]>& ptr)
	{
		DataType* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual SharedPointer<DataType[]>& Destroy()
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete[] data;
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
	static int Total(SharedPointer<DataType[]>& ptr)
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
	static bool IsUnique(SharedPointer<DataType[]>& ptr)
	{
		if (ptr.data == nullptr || !count.count(ptr.data))
		{
			return false;
		}

		return count[ptr.data] == 1;
	}


	// OPERATORS

	// Copy assignment operator
	virtual SharedPointer<DataType[]>& operator=(DataType* ptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete[] data;
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
	virtual SharedPointer<DataType[]>& operator=(const SharedPointer<DataType[]>& ptr)
	{
		if (data != nullptr)
		{
			// Decrement the pointer count
			count[data]--;

			if (count[data] <= 0)
			{
				delete[] data;
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
	virtual SharedPointer<DataType[]>& operator=(SharedPointer<DataType[]>&& ptr) noexcept
	{
		if (this != &ptr)
		{
			if (data != nullptr)
			{
				// Decrement the pointer count
				count[data]--;

				if (count[data] <= 0)
				{
					delete[] data;
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

	// Array index operator
	virtual DataType& operator[](int index)
	{
		return data[index];
	}

	// Equality operator
	virtual bool operator==(DataType* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(SharedPointer<DataType[]>&& ptr)
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

// •  A wrapper for a newly created void pointer that automatically deallocates on deconstruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the PointerBase storage class.
template <> class SharedPointer<void> : public PointerBase
{
protected:

	// POINTER

	// The stored pointer
	void* data = nullptr;


	// COUNT

	// The total number of pointers to this pointer's memory (deallocates when this is the last pointer)
	static std::map<void*, int> count;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	SharedPointer(void* ptr = nullptr)
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
	SharedPointer(const SharedPointer<void>& ptr)
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
	SharedPointer(SharedPointer<void>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Deconstructor
	virtual ~SharedPointer()
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
	template<typename DataType> SharedPointer<DataType>& Get() = delete;

	// Returns a pointer to the given data
	virtual void* Get()
	{
		return data;
	}

	// Releases and returns the pointer
	virtual void* Release()
	{
		void* ptr = data;

		if (data != nullptr)
		{
			count[data]--;

			data = nullptr;
		}

		return ptr;
	}

	// Resets the pointer
	virtual SharedPointer<void>& Reset(void* ptr = nullptr)
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
	virtual SharedPointer<void>& Reset(SharedPointer<void>& ptr)
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
	virtual SharedPointer<void>& Swap(void*& ptr)
	{
		if (this->data != nullptr)
		{
			// Decrement the pointer count
			count[this->data]--;
		}

		void* data = this->data;

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
	virtual SharedPointer<void>& Swap(SharedPointer<void>& ptr)
	{
		void* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual SharedPointer<void>& Destroy()
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
	static int Total(void* ptr)
	{
		if (ptr == nullptr || !count.count(ptr))
		{
			return 0;
		}

		return count[ptr];
	}

	// Returns the total number of pointers sharing the given pointer
	static int Total(SharedPointer<void>& ptr)
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
	static bool IsUnique(void* ptr)
	{
		if (ptr == nullptr || !count.count(ptr))
		{
			return false;
		}

		return count[ptr] == 1;
	}

	// Returns if the given pointer is unique
	static bool IsUnique(SharedPointer<void>& ptr)
	{
		if (ptr.data == nullptr || !count.count(ptr.data))
		{
			return false;
		}

		return count[ptr.data] == 1;
	}


	// OPERATORS

	// Copy assignment operator
	virtual SharedPointer<void>& operator=(void* ptr)
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
	virtual SharedPointer<void>& operator=(const SharedPointer<void>& ptr)
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
	virtual SharedPointer<void>& operator=(SharedPointer<void>&& ptr) noexcept
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

	// Equality operator
	virtual bool operator==(void* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(SharedPointer<void>&& ptr)
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
template <typename DataType> std::map<DataType*, int> SharedPointer<DataType>::count = std::map<DataType*, int>();
template <typename DataType> std::map<DataType*, int> SharedPointer<DataType[]>::count = std::map<DataType*, int>();
std::map<void*, int> SharedPointer<void>::count = std::map<void*, int>();

// •  A wrapper for a newly created pointer that automatically deallocates on deconstruction.
// •  Pointer is unique and only allows one pointer to the stored memory at a time.
// •  Inherits from the PointerBase storage class.
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
	template<typename DataType> SharedPointer<DataType>& get() = delete;

	// Returns a pointer to the given data
	virtual DataType* Get()
	{
		return data;
	}

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

// •  A wrapper for a newly created array pointer that automatically deallocates on deconstruction.
// •  Pointer is unique and only allows one pointer to the stored memory at a time.
// •  Inherits from the PointerBase storage class.
template <typename DataType> class UniquePointer<DataType[]> : public PointerBase
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
	UniquePointer(const UniquePointer<DataType[]>& ptr) = delete;

	// Move constructor
	UniquePointer(UniquePointer<DataType[]>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Deconstructor
	virtual ~UniquePointer()
	{
		delete[] data;

		data = nullptr;
	}


	// FUNCTIONS

	// Delete cast
	template<typename DataType> SharedPointer<DataType[]>& get() = delete;

	// Returns a pointer to the given data
	virtual DataType* Get()
	{
		return data;
	}

	// Releases and returns the pointer
	virtual DataType* Release()
	{
		DataType* ptr = data;

		data = nullptr;

		return ptr;
	}

	// Resets the pointer
	virtual UniquePointer<DataType[]>& Reset(DataType* ptr = nullptr)
	{
		delete[] data;

		data = ptr;

		return *this;
	}

	// Resets the pointer
	virtual UniquePointer<DataType[]>& Reset(UniquePointer<DataType[]>& ptr)
	{
		delete[] data;

		data = ptr.data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual UniquePointer<DataType[]>& Swap(DataType*& ptr)
	{
		DataType* data = this->data;

		this->data = ptr;

		ptr = data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual UniquePointer<DataType[]>& Swap(UniquePointer<DataType[]>& ptr)
	{
		DataType* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual UniquePointer<DataType[]>& Destroy()
	{
		delete[] data;

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
	virtual UniquePointer<DataType[]>& operator=(DataType* ptr) = delete;

	// Remove copy assignment operator
	virtual UniquePointer<DataType[]>& operator=(const UniquePointer<DataType[]>&) = delete;

	// Move assignment operator
	virtual UniquePointer<DataType[]>& operator=(UniquePointer<DataType[]>&& ptr) noexcept
	{
		if (this != &ptr)
		{
			delete[] data;

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

	// Array index operator
	virtual DataType& operator[](int index)
	{
		return data[index];
	}

	// Equality operator
	virtual bool operator==(DataType* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(UniquePointer<DataType[]>&& ptr)
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

// •  A wrapper for a newly created void pointer that automatically deallocates on deconstruction.
// •  Pointer is unique and only allows one pointer to the stored memory at a time.
// •  Inherits from the PointerBase storage class.
template <> class UniquePointer<void> : public PointerBase
{
protected:

	// POINTER

	// The stored pointer
	void* data = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	UniquePointer(void* ptr = nullptr)
	{
		// Set the pointer
		data = ptr;
	}

	// Remove copy constructor
	UniquePointer(const UniquePointer<void>& ptr) = delete;

	// Move constructor
	UniquePointer(UniquePointer<void>&& ptr) noexcept
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
	template<typename DataType> SharedPointer<DataType>& get() = delete;

	// Returns a pointer to the given data
	virtual void* Get()
	{
		return data;
	}

	// Releases and returns the pointer
	virtual void* Release()
	{
		void* ptr = data;

		data = nullptr;

		return ptr;
	}

	// Resets the pointer
	virtual UniquePointer<void>& Reset(void* ptr = nullptr)
	{
		delete data;

		data = ptr;

		return *this;
	}

	// Resets the pointer
	virtual UniquePointer<void>& Reset(UniquePointer<void>& ptr)
	{
		delete data;

		data = ptr.data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual UniquePointer<void>& Swap(void*& ptr)
	{
		void* data = this->data;

		this->data = ptr;

		ptr = data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual UniquePointer<void>& Swap(UniquePointer<void>& ptr)
	{
		void* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual UniquePointer<void>& Destroy()
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
	virtual UniquePointer<void>& operator=(void* ptr) = delete;

	// Remove copy assignment operator
	virtual UniquePointer<void>& operator=(const UniquePointer<void>&) = delete;

	// Move assignment operator
	virtual UniquePointer<void>& operator=(UniquePointer<void>&& ptr) noexcept
	{
		if (this != &ptr)
		{
			delete data;

			data = ptr.data;

			ptr.data = nullptr;
		}

		return *this;
	}

	// Equality operator
	virtual bool operator==(void* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(UniquePointer<void>&& ptr)
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

// •  A wrapper for a shared pointer that does not own the original pointer: a weak pointer.
// •  Useful if there is a circular dependency between shared pointers to ensure memory does not persist.
// •  Use Check() and Get() to test and receive a shared pointer of the original pointer.
// •  Inherits from the PointerBase storage class.
template <typename DataType> class WeakPointer : public PointerBase
{
protected:

	// POINTER

	// The stored pointer
	SharedPointer<DataType>* shared = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	WeakPointer() { shared = nullptr; }

	// Shared pointer constructor
	WeakPointer(SharedPointer<DataType>& shared)
	{
		this->shared = &shared;
	}

	// Deconstructor
	virtual ~WeakPointer() { }


	// FUNCTIONS

	// Delete cast
	template<typename DataType> SharedPointer<DataType>& get() = delete;

	// Check if the shared pointer is valid
	virtual bool Check()
	{
		return shared->IsNotNull();
	}

	// Receive the shared pointer
	virtual SharedPointer<DataType> Get()
	{
		return *shared;
	}


	// OPERATORS

	// Set the shared pointer
	virtual WeakPointer<DataType>& operator=(SharedPointer<DataType>& shared)
	{
		this->shared = &shared;

		return *this;
	}

	// Receive the shared pointer
	virtual SharedPointer<DataType> operator*()
	{
		return *shared;
	}

	// Check if the shared pointer is valid
	virtual operator bool()
	{
		return shared->IsNotNull();
	}
};

// •  A wrapper for a shared array pointer that does not own the original pointer: a weak pointer.
// •  Useful if there is a circular dependency between shared pointers to ensure memory does not persist.
// •  Use Check() and Get() to test and receive a shared pointer of the original pointer.
// •  Inherits from the PointerBase storage class.
template <typename DataType> class WeakPointer<DataType[]> : public PointerBase
{
protected:

	// POINTER

	// The stored pointer
	SharedPointer<DataType[]>* shared = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	WeakPointer() { shared = nullptr; }

	// Shared pointer constructor
	WeakPointer(SharedPointer<DataType[]>& shared)
	{
		this->shared = &shared;
	}

	// Deconstructor
	virtual ~WeakPointer() { }


	// FUNCTIONS

	// Delete cast
	template<typename DataType> SharedPointer<DataType[]>& get() = delete;

	// Check if the shared pointer is valid
	virtual bool Check()
	{
		return shared->IsNotNull();
	}

	// Receive the shared pointer
	virtual SharedPointer<DataType[]> Get()
	{
		return *shared;
	}


	// OPERATORS

	// Set the shared pointer
	virtual WeakPointer<DataType[]>& operator=(SharedPointer<DataType[]>& shared)
	{
		this->shared = &shared;

		return *this;
	}

	// Receive the shared pointer
	virtual SharedPointer<DataType[]> operator*()
	{
		return *shared;
	}

	// Check if the shared pointer is valid
	virtual operator bool()
	{
		return shared->IsNotNull();
	}
};

// •  A wrapper for a shared void pointer that does not own the original pointer: a weak pointer.
// •  Useful if there is a circular dependency between shared pointers to ensure memory does not persist.
// •  Use Check() and Get() to test and receive a shared pointer of the original pointer.
// •  Inherits from the PointerBase storage class.
template <> class WeakPointer<void> : public PointerBase
{
protected:

	// POINTER

	// The stored pointer
	SharedPointer<void>* shared = nullptr;

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	WeakPointer() { shared = nullptr; }

	// Shared pointer constructor
	WeakPointer(SharedPointer<void>& shared)
	{
		this->shared = &shared;
	}

	// Deconstructor
	virtual ~WeakPointer() { }


	// FUNCTIONS

	// Delete cast
	template<typename DataType> SharedPointer<DataType>& get() = delete;

	// Check if the shared pointer is valid
	virtual bool Check()
	{
		return shared->IsNotNull();
	}

	// Receive the shared pointer
	virtual SharedPointer<void> Get()
	{
		return *shared;
	}


	// OPERATORS

	// Set the shared pointer
	virtual WeakPointer<void>& operator=(SharedPointer<void>& shared)
	{
		this->shared = &shared;

		return *this;
	}

	// Receive the shared pointer
	virtual SharedPointer<void> operator*()
	{
		return *shared;
	}

	// Check if the shared pointer is valid
	virtual operator bool()
	{
		return shared->IsNotNull();
	}
};

// •  A wrapper for a newly created pointer that automatically deallocates on deconstruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the ptr_base storage class.
#define ptr sptr

// •  A wrapper for a newly created pointer that automatically deallocates on deconstruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the ptr_base storage class.
#define smart_ptr sptr

// •  A wrapper for a newly created pointer that automatically deallocates on deconstruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the PointerBase storage class.
#define Pointer SharedPointer

// •  A wrapper for a newly created pointer that automatically deallocates on deconstruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the PointerBase storage class.
#define SmartPointer SharedPointer
