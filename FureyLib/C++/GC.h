
// Automatic Garbage Collector Script
// by Kyle Furey

#pragma once
#include <iostream>
#include <vector>

// Include this heading to enable safe garbage collection
#include "GC.h"

// Overrides the new keyword to store newly allocated memory to the garbage collector.
#define new GC + new

// Overrides the malloc() function to store newly allocated memory to the garbage collector.
#define malloc GC - malloc

// Overrides the calloc() function to store newly allocated memory to the garbage collector.
#define calloc GC - calloc

// Overrides the realloc() function to store newly allocated memory to the garbage collector.
#define realloc GC - realloc

// •  Collects and stores pointers to newly allocated memory for automatic deallocation at the end of the program.
// •  Do not make an instance of this class as there is already a global instance named "GC".
// •  Note:  Use containers such as std::array and std::vector for allocation of multiple variables instead of C arrays.
class GarbageCollector
{
private:

	// ALLOCATED MEMORY

	// All of the garbage collector's newly allocated memory using the new keyword.
	std::vector<void*> cppMemory = std::vector<void*>();

	// All of the garbage collector's newly allocated memory using the malloc() functions.
	std::vector<void*> cMemory = std::vector<void*>();

public:

	// MEMORY DEALLOCATION

	// •  Deletes all of the garbage collector's current memory.
	// •  Automatically called when the garbage collector deconstructs at the end of the program.
	// •  Prints and returns the total number of bytes deallocated.
	int CollectGarbage()
	{
		int total = 0;

		for (int i = 0; i < cppMemory.size(); i++)
		{
			total += sizeof(cppMemory[i]);

			delete cppMemory[i];

			cppMemory[i] = nullptr;
		}

		cppMemory.clear();

		for (int i = 0; i < cMemory.size(); i++)
		{
			total += sizeof(cMemory[i]);

			free(cMemory[i]);

			cMemory[i] = nullptr;
		}

		cMemory.clear();

		std::cout << std::endl << "Garbage Collector successfully deallocated " << total << " total bytes of memory." << std::endl;

		return total;
	}


	// DECONSTRUCTOR

	// Deallocates the garbage collector's remaining memory when the program closes.
	~GarbageCollector()
	{
		CollectGarbage();
	}


	// MEMORY ALLOCATION

	// •  Allocates new memory in place of the new keyword.
	// •  Stores the pointer in the garbage collector's memory before returning the new pointer.
	template<typename DataType> DataType* AllocateNewCPPMemory(DataType* ptr)
	{
		cppMemory.push_back(ptr);

		return ptr;
	}

	// •  Allocates new memory in place of the malloc() functions.
	// •  Stores the pointer in the garbage collector's memory before returning the new pointer.
	void* AllocateNewCMemory(void* ptr)
	{
		cMemory.push_back(ptr);

		return ptr;
	}


	// MEMORY ALLOCATION OPERATOR

	// Operator used to take new pointers as a parameter in the new macro for the AllocateNewCPPMemory() functions.
	template<typename DataType> DataType* operator+(DataType* ptr)
	{
		return AllocateNewCPPMemory(ptr);
	}

	// Operator used to take new pointers as a parameter in the malloc macro for the AllocateNewCMemory() functions.
	void* operator-(void* ptr)
	{
		return AllocateNewCMemory(ptr);
	}
};

// This program's global instance of the garbage collector.
GarbageCollector GC = GarbageCollector();
