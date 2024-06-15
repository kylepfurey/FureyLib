
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
#define malloc GC + malloc

// •  Collects and stores pointers to newly allocated memory for automatic deallocation at the end of the program.
// •  Do not make an instance of this class as there is already a global instance named "GC".
class GarbageCollector
{
private:

	// ALLOCATED MEMORY

	// All of the garbage collector's newly allocated memory.
	std::vector<void*> memory = std::vector<void*>();

public:

	// MEMORY DEALLOCATION

	// •  Deletes all of the garbage collector's current memory.
	// •  Automatically called when the garbage collector deconstructs at the end of the program.
	// •  Prints and returns the total number of bytes deallocated.
	int CollectGarbage()
	{
		int total = 0;

		for (int i = 0; i < memory.size(); i++)
		{
			total += sizeof(memory[i]);

			delete memory[i];

			memory[i] = nullptr;
		}

		memory.clear();

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
	template<typename DataType> DataType* AllocateNewMemory(DataType* ptr)
	{
		memory.push_back(ptr);

		return ptr;
	}

	// •  Allocates new memory in place of the malloc() function.
	// •  Stores the pointer in the garbage collector's memory before returning the new pointer.
	void* AllocateNewMemory(void* ptr)
	{
		memory.push_back(ptr);

		return ptr;
	}


	// MEMORY ALLOCATION OPERATOR

	// Operator used to take new pointers as a parameter in the new macro for the AllocateNewMemory() functions.
	template<typename DataType> DataType* operator+(DataType* ptr)
	{
		return AllocateNewMemory(ptr);
	}

	// Operator used to take new pointers as a parameter in the malloc macro for the AllocateNewMemory() functions.
	void* operator+(void* ptr)
	{
		return AllocateNewMemory(ptr);
	}
};

// This program's global instance of the garbage collector.
GarbageCollector GC = GarbageCollector();
