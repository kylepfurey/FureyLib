
// Smart Pointer Classes
// by Kyle Furey

// REFERENCES: https://blog.devgenius.io/unique-pointer-and-implementation-in-c-ec6599a518e5, https://www.geeksforgeeks.org/smart-pointers-cpp/

#pragma once
#include <map>

// Include this heading to use the classes
#include "ptr.h"

// Forward declaration of sptr
template <typename data_type> class sptr;

// •  Base class for the smart pointer classes.
// •  Used as type safe storage for pointers of varying types.
// •  Provides a virtual destructor for the pointer classes to properly destroy its pointer regardless of their type.
class ptr_base
{
public:

	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	ptr_base() { }

	// Pointer constructor
	template<typename data_type> ptr_base(data_type* data)
	{
		*this = sptr<data_type>(data);
	}

	// Virtual destructor used to properly deallocate the pointer class's pointer
	virtual ~ptr_base() { }


	// GET POINTER

	// Cast to shared pointer
	template<typename data_type> sptr<data_type>& get()
	{
		return *((sptr<data_type>*)this);
	}


	// ASSIGNMENT OPERATORS

	// Pointer assignment operator
	template<typename data_type> sptr<data_type> operator=(data_type* data)
	{
		return sptr<data_type>(data);
	}
};

// •  A wrapper for a newly created pointer that automatically deallocates on destruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the ptr_base storage class.
template <typename data_type> class sptr : public ptr_base
{
protected:

	// POINTER

	// The stored pointer
	data_type* data = nullptr;


	// COUNT

	// The total number of pointers to this pointer's memory (deallocates when this is the last pointer)
	static std::map<data_type*, int> count;

public:

	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	sptr(data_type* ptr = nullptr)
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
	sptr(const sptr<data_type>& ptr)
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
	sptr(sptr<data_type>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Destructor
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
	template<typename data_type> sptr<data_type>& get() = delete;

	// Returns a pointer to the given data
	virtual data_type* get()
	{
		return data;
	}

	// Releases and returns the pointer
	virtual data_type* release()
	{
		data_type* ptr = data;

		if (data != nullptr)
		{
			count[data]--;

			data = nullptr;
		}

		return ptr;
	}

	// Resets the pointer
	virtual sptr<data_type>& reset(data_type* ptr = nullptr)
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
	virtual sptr<data_type>& reset(sptr<data_type>& ptr)
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
	virtual sptr<data_type>& swap(data_type*& ptr)
	{
		if (this->data != nullptr)
		{
			// Decrement the pointer count
			count[this->data]--;
		}

		data_type* data = this->data;

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
	virtual sptr<data_type>& swap(sptr<data_type>& ptr)
	{
		data_type* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual sptr<data_type>& destroy()
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
	static int total(data_type* ptr)
	{
		if (ptr == nullptr || !count.count(ptr))
		{
			return 0;
		}

		return count[ptr];
	}

	// Returns the total number of pointers sharing the given pointer
	static int total(sptr<data_type>& ptr)
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
	static bool is_unique(data_type* ptr)
	{
		if (ptr == nullptr || !count.count(ptr))
		{
			return false;
		}

		return count[ptr] == 1;
	}

	// Returns if the given pointer is unique
	static bool is_unique(sptr<data_type>& ptr)
	{
		if (ptr.data == nullptr || !count.count(ptr.data))
		{
			return false;
		}

		return count[ptr.data] == 1;
	}


	// OPERATORS

	// Copy assignment operator
	virtual sptr<data_type>& operator=(data_type* ptr)
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
	virtual sptr<data_type>& operator=(const sptr<data_type>& ptr)
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
	virtual sptr<data_type>& operator=(sptr<data_type>&& ptr) noexcept
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
	virtual data_type& operator*()
	{
		return *data;
	}

	// Arrow pointer operator
	virtual data_type* operator->()
	{
		return data;
	}

	// Equality operator
	virtual bool operator==(data_type* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(sptr<data_type>&& ptr)
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

// •  A wrapper for a newly created array pointer that automatically deallocates on destruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the ptr_base storage class.
template <typename data_type> class sptr<data_type[]> : public ptr_base
{
protected:

	// POINTER

	// The stored pointer
	data_type* data = nullptr;


	// COUNT

	// The total number of pointers to this pointer's memory (deallocates when this is the last pointer)
	static std::map<data_type*, int> count;

public:

	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	sptr(data_type* ptr = nullptr)
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
	sptr(const sptr<data_type[]>& ptr)
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
	sptr(sptr<data_type[]>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Destructor
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
	template<typename data_type> sptr<data_type[]>& get() = delete;

	// Returns a pointer to the given data
	virtual data_type* get()
	{
		return data;
	}

	// Releases and returns the pointer
	virtual data_type* release()
	{
		data_type* ptr = data;

		if (data != nullptr)
		{
			count[data]--;

			data = nullptr;
		}

		return ptr;
	}

	// Resets the pointer
	virtual sptr<data_type[]>& reset(data_type* ptr = nullptr)
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
	virtual sptr<data_type[]>& reset(sptr<data_type[]>& ptr)
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
	virtual sptr<data_type[]>& swap(data_type*& ptr)
	{
		if (this->data != nullptr)
		{
			// Decrement the pointer count
			count[this->data]--;
		}

		data_type* data = this->data;

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
	virtual sptr<data_type[]>& swap(sptr<data_type[]>& ptr)
	{
		data_type* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual sptr<data_type[]>& destroy()
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
	static int total(data_type* ptr)
	{
		if (ptr == nullptr || !count.count(ptr))
		{
			return 0;
		}

		return count[ptr];
	}

	// Returns the total number of pointers sharing the given pointer
	static int total(sptr<data_type[]>& ptr)
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
	static bool is_unique(data_type* ptr)
	{
		if (ptr == nullptr || !count.count(ptr))
		{
			return false;
		}

		return count[ptr] == 1;
	}

	// Returns if the given pointer is unique
	static bool is_unique(sptr<data_type[]>& ptr)
	{
		if (ptr.data == nullptr || !count.count(ptr.data))
		{
			return false;
		}

		return count[ptr.data] == 1;
	}


	// OPERATORS

	// Copy assignment operator
	virtual sptr<data_type[]>& operator=(data_type* ptr)
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
	virtual sptr<data_type[]>& operator=(const sptr<data_type[]>& ptr)
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
	virtual sptr<data_type[]>& operator=(sptr<data_type[]>&& ptr) noexcept
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
	virtual data_type& operator*()
	{
		return *data;
	}

	// Arrow pointer operator
	virtual data_type* operator->()
	{
		return data;
	}

	// Array index operator
	virtual data_type& operator[](int index)
	{
		return data[index];
	}

	// Equality operator
	virtual bool operator==(data_type* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(sptr<data_type[]>&& ptr)
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

// •  A wrapper for a newly created void pointer that automatically deallocates on destruction.
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

	// CONSTRUCTORS AND DESTRUCTOR

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

	// Destructor
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
	template<typename data_type> sptr<data_type>& get() = delete;

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

// •  A wrapper for a newly created pointer that automatically deallocates on destruction.
// •  Pointer is unique and only allows one pointer to the stored memory at a time.
// •  Inherits from the ptr_base storage class.
template <typename data_type> class uptr : public ptr_base
{
protected:

	// POINTER

	// The stored pointer
	data_type* data = nullptr;

public:

	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	uptr(data_type* ptr = nullptr)
	{
		// Set the pointer
		data = ptr;
	}

	// Remove copy constructor
	uptr(const uptr<data_type>& ptr) = delete;

	// Move constructor
	uptr(uptr<data_type>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Destructor
	virtual ~uptr()
	{
		delete data;

		data = nullptr;
	}


	// FUNCTIONS

	// Delete cast
	template<typename data_type> sptr<data_type>& get() = delete;

	// Returns a pointer to the given data
	virtual data_type* get()
	{
		return data;
	}

	// Releases and returns the pointer
	virtual data_type* release()
	{
		data_type* ptr = data;

		data = nullptr;

		return ptr;
	}

	// Resets the pointer
	virtual uptr<data_type>& reset(data_type* ptr = nullptr)
	{
		delete data;

		data = ptr;

		return *this;
	}

	// Resets the pointer
	virtual uptr<data_type>& reset(uptr<data_type>& ptr)
	{
		delete data;

		data = ptr.data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual uptr<data_type>& swap(data_type*& ptr)
	{
		data_type* data = this->data;

		this->data = ptr;

		ptr = data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual uptr<data_type>& swap(uptr<data_type>& ptr)
	{
		data_type* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual uptr<data_type>& destroy()
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
	virtual uptr<data_type>& operator=(data_type* ptr) = delete;

	// Remove copy assignment operator
	virtual uptr<data_type>& operator=(const uptr<data_type>&) = delete;

	// Move assignment operator
	virtual uptr<data_type>& operator=(uptr<data_type>&& ptr) noexcept
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
	virtual data_type& operator*()
	{
		return *data;
	}

	// Arrow pointer operator
	virtual data_type* operator->()
	{
		return data;
	}

	// Equality operator
	virtual bool operator==(data_type* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(uptr<data_type>&& ptr)
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

// •  A wrapper for a newly created array pointer that automatically deallocates on destruction.
// •  Pointer is unique and only allows one pointer to the stored memory at a time.
// •  Inherits from the ptr_base storage class.
template <typename data_type> class uptr<data_type[]> : public ptr_base
{
protected:

	// POINTER

	// The stored pointer
	data_type* data = nullptr;

public:

	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	uptr(data_type* ptr = nullptr)
	{
		// Set the pointer
		data = ptr;
	}

	// Remove copy constructor
	uptr(const uptr<data_type[]>& ptr) = delete;

	// Move constructor
	uptr(uptr<data_type[]>&& ptr) noexcept
	{
		data = ptr.data;

		ptr.data = nullptr;
	}

	// Destructor
	virtual ~uptr()
	{
		delete[] data;

		data = nullptr;
	}


	// FUNCTIONS

	// Delete cast
	template<typename data_type> sptr<data_type[]>& get() = delete;

	// Returns a pointer to the given data
	virtual data_type* get()
	{
		return data;
	}

	// Releases and returns the pointer
	virtual data_type* release()
	{
		data_type* ptr = data;

		data = nullptr;

		return ptr;
	}

	// Resets the pointer
	virtual uptr<data_type[]>& reset(data_type* ptr = nullptr)
	{
		delete[] data;

		data = ptr;

		return *this;
	}

	// Resets the pointer
	virtual uptr<data_type[]>& reset(uptr<data_type[]>& ptr)
	{
		delete[] data;

		data = ptr.data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual uptr<data_type[]>& swap(data_type*& ptr)
	{
		data_type* data = this->data;

		this->data = ptr;

		ptr = data;

		return *this;
	}

	// Swaps the pointer's data with another pointer
	virtual uptr<data_type[]>& swap(uptr<data_type[]>& ptr)
	{
		data_type* data = this->data;

		this->data = ptr.data;

		ptr.data = data;

		return *this;
	}

	// Deletes the pointer
	virtual uptr<data_type[]>& destroy()
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
	virtual uptr<data_type[]>& operator=(data_type* ptr) = delete;

	// Remove copy assignment operator
	virtual uptr<data_type[]>& operator=(const uptr<data_type[]>&) = delete;

	// Move assignment operator
	virtual uptr<data_type[]>& operator=(uptr<data_type[]>&& ptr) noexcept
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
	virtual data_type& operator*()
	{
		return *data;
	}

	// Arrow pointer operator
	virtual data_type* operator->()
	{
		return data;
	}

	// Array index operator
	virtual data_type& operator[](int index)
	{
		return data[index];
	}

	// Equality operator
	virtual bool operator==(data_type* ptr)
	{
		return data = ptr;
	}

	// Equality operator
	virtual bool operator==(uptr<data_type[]>&& ptr)
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

// •  A wrapper for a newly created void pointer that automatically deallocates on destruction.
// •  Pointer is unique and only allows one pointer to the stored memory at a time.
// •  Inherits from the ptr_base storage class.
template <> class uptr<void> : public ptr_base
{
protected:

	// POINTER

	// The stored pointer
	void* data = nullptr;

public:

	// CONSTRUCTORS AND DESTRUCTOR

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

	// Destructor
	virtual ~uptr()
	{
		delete data;

		data = nullptr;
	}


	// FUNCTIONS

	// Delete cast
	template<typename data_type> sptr<data_type>& get() = delete;

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
template <typename data_type> class wptr : public ptr_base
{
protected:

	// POINTER

	// The stored pointer
	sptr<data_type>* shared = nullptr;

public:

	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	wptr() { shared = nullptr; }

	// Shared pointer constructor
	wptr(sptr<data_type>& shared)
	{
		this->shared = &shared;
	}

	// Destructor
	virtual ~wptr() { }


	// FUNCTIONS

	// Delete cast
	template<typename data_type> sptr<data_type>& get() = delete;

	// Check if the shared pointer is valid
	virtual bool check()
	{
		return shared->is_not_null();
	}

	// Receive the shared pointer
	virtual sptr<data_type> get()
	{
		return *shared;
	}


	// OPERATORS

	// Set the shared pointer
	virtual wptr<data_type>& operator=(sptr<data_type>& shared)
	{
		this->shared = &shared;

		return *this;
	}

	// Receive the shared pointer
	virtual sptr<data_type> operator*()
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
template <typename data_type> class wptr<data_type[]> : public ptr_base
{
protected:

	// POINTER

	// The stored pointer
	sptr<data_type[]>* shared = nullptr;

public:

	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	wptr() { shared = nullptr; }

	// Shared pointer constructor
	wptr(sptr<data_type[]>& shared)
	{
		this->shared = &shared;
	}

	// Destructor
	virtual ~wptr() { }


	// FUNCTIONS

	// Delete cast
	template<typename data_type> sptr<data_type[]>& get() = delete;

	// Check if the shared pointer is valid
	virtual bool check()
	{
		return shared->is_not_null();
	}

	// Receive the shared pointer
	virtual sptr<data_type[]> get()
	{
		return *shared;
	}


	// OPERATORS

	// Set the shared pointer
	virtual wptr<data_type[]>& operator=(sptr<data_type[]>& shared)
	{
		this->shared = &shared;

		return *this;
	}

	// Receive the shared pointer
	virtual sptr<data_type[]> operator*()
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

	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor
	wptr() { shared = nullptr; }

	// Shared pointer constructor
	wptr(sptr<void>& shared)
	{
		this->shared = &shared;
	}

	// Destructor
	virtual ~wptr() { }


	// FUNCTIONS

	// Delete cast
	template<typename data_type> sptr<data_type>& get() = delete;

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

// Static variable initialization
template <typename data_type> std::map<data_type*, int> sptr<data_type>::count = std::map<data_type*, int>();
template <typename data_type> std::map<data_type*, int> sptr<data_type[]>::count = std::map<data_type*, int>();
std::map<void*, int> sptr<void>::count = std::map<void*, int>();

// •  A wrapper for a newly created pointer that automatically deallocates on destruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the ptr_base storage class.
#define ptr sptr

// •  A wrapper for a newly created pointer that automatically deallocates on destruction.
// •  Pointer is shared and only deallocates when it is the last pointer to the stored memory.
// •  Inherits from the ptr_base storage class.
#define smart_ptr sptr
