
// Automatic Garbage Collector Script
// by Kyle Furey

#pragma once
#include <memory>
#include <iostream>
#include <list>
#include <algorithm>

// Include this heading to enable safe garbage collection
#include "gc.h"

// Forward declaration of garbage
template <typename data_type> class garbage;

// •  Base class for the garbage class.
// •  Used as type safe storage for pointers of varying types.
// •  Provides a virtual destructor for the garbage class to properly destroy its pointer regardless of its type.
class garbage_base
{
public:

	// CONSTRUCTOR AND DESTRUCTOR

	// Default constructor.
	garbage_base() = default;

	// Virtual destructor used to properly deallocate the pointer class's pointer.
	virtual ~garbage_base() = default;


	// CASTING

	// Cast to shared pointer.
	template<typename data_type> std::shared_ptr<data_type>& cast()
	{
		return ((garbage<data_type>*)this)->ptr;
	}
};

// •  Represents a shared pointer that will be deallocated at the end of the program with type safety.
// •  Inherits from the garbage_base storage class.
template <typename data_type> class garbage : public garbage_base
{
public:

	// The stored pointer to be deallocated.
	std::shared_ptr<data_type> ptr = nullptr;

	// Garbage constructor.
	garbage(data_type* ptr)
	{
		this->ptr = std::shared_ptr<data_type>(ptr);
	}

	// Delete the cast function.
	std::shared_ptr<data_type>& get() = delete;
};

// •  Collects and stores pointers to newly allocated memory for automatic deallocation at the end of the program.
// •  Do not make an instance of this class as there is already a global instance named "gc".
// •  Note:  Use containers such as std::array and std::vector for allocation of multiple variables instead of C arrays.
class garbage_collector
{
private:

	// ALLOCATED MEMORY

	// All of the garbage collector's newly allocated memory using the new keyword.
	std::list<garbage_base*> cpp_memory = std::list<garbage_base*>();

	// All of the garbage collector's newly allocated memory using the malloc() functions.
	std::list<void*> c_memory = std::list<void*>();


	// GARBAGE COLLECTION

	// •  Deletes all of the garbage collector's current memory.
	// •  Automatically called when the garbage collector destructs at the end of the program.
	// •  Returns the total number of bytes deallocated.
	int collect_garbage()
	{
		int total = 0;

		for (auto current : cpp_memory)
		{
			total++;

			delete current;
		}

		cpp_memory.clear();

		for (auto current : c_memory)
		{
			total++;

			free(current);
		}

		c_memory.clear();

		return total;
	}

public:

	// DESTRUCTOR

	// Deallocates the garbage collector's remaining memory when the program closes.
	~garbage_collector()
	{
		int total = collect_garbage();

		std::cout << std::endl << "Garbage Collector automatically deallocated " << total << (total == 1 ? " pointer successfully." : " total pointers successfully.") << std::endl;
	}


	// MEMORY ALLOCATION

	// •  Allocates new memory in place of the new keyword.
	// •  Stores the pointer in the garbage collector's memory before returning the new pointer.
	template<typename data_type> data_type* allocate_cpp_memory(data_type* ptr)
	{
		cpp_memory.push_back(new garbage<data_type>(ptr));

		return ptr;
	}

	// •  Allocates new memory in place of the malloc() functions.
	// •  Stores the pointer in the garbage collector's memory before returning the new pointer.
	void* allocate_c_memory(void* ptr)
	{
		c_memory.push_back(ptr);

		return ptr;
	}


	// MEMORY ALLOCATION OPERATOR

	// Operator used to take new pointers as a parameter for the allocate_cpp_memory() function.
	template<typename data_type> data_type* operator+=(data_type* ptr)
	{
		return allocate_cpp_memory(ptr);
	}

	// Operator used to take new pointers as a parameter for the allocate_c_memory() function.
	void* operator+(void* ptr)
	{
		return allocate_c_memory(ptr);
	}


	// MEMORY DEALLOCATION

	// •  Deallocates new memory in place of the delete keyword.
	// •  Removes the pointer from the garbage collector's memory.
	template <typename data_type> void deallocate_cpp_memory(data_type*& ptr)
	{
		if (ptr != nullptr)
		{
			for (auto current : cpp_memory)
			{
				if (current->cast<data_type>().get() == ptr)
				{
					delete current;

					cpp_memory.erase(std::find(cpp_memory.begin(), cpp_memory.end(), current));

					break;
				}
			}

			ptr = nullptr;
		}
	}

	// •  Deallocates new memory in place of the free() function.
	// •  Removes the pointer from the garbage collector's memory.
	template <typename data_type> void deallocate_c_memory(data_type*& ptr)
	{
		if (ptr != nullptr)
		{
			for (auto current : c_memory)
			{
				if (current == ptr)
				{
					free(current);

					c_memory.erase(std::find(c_memory.begin(), c_memory.end(), current));

					break;
				}
			}

			ptr = nullptr;
		}
	}

	// •  Deallocates new memory in place of the free() function.
	// •  Removes the pointer from the garbage collector's memory.
	void deallocate_c_memory(void*& ptr)
	{
		if (ptr != nullptr)
		{
			for (auto current : c_memory)
			{
				if (current == ptr)
				{
					free(current);

					c_memory.erase(std::find(c_memory.begin(), c_memory.end(), current));

					break;
				}
			}

			ptr = nullptr;
		}
	}


	// MEMORY DEALLOCATION OPERATOR

	// Operator used to take new pointers as a parameter for the deallocate_cpp_memory() function.
	template<typename data_type> void operator-=(data_type*& ptr)
	{
		deallocate_cpp_memory(ptr);
	}
};

// Overrides the new keyword to store newly allocated memory to the garbage collector.
#define new gc += new

// Overrides the malloc() function to store newly allocated memory to the garbage collector.
#define malloc gc + malloc

// Overrides the calloc() function to store newly allocated memory to the garbage collector.
#define calloc gc + calloc

// Overrides the realloc() function to store newly allocated memory to the garbage collector.
#define realloc gc + realloc

// Overrides the delete keyword to safely delete and remove memory from the garbage collector.
#define delete gc -=

// Overrides the free() function to safely delete and remove memory from the garbage collector.
#define free gc.deallocate_c_memory

// This program's global instance of the garbage collector.
garbage_collector gc = garbage_collector();
