
// Automatic Garbage Collector Script
// by Kyle Furey

#pragma once
#include <iostream>
#include <vector>

// Include this heading to enable safe garbage collection
#include "GC.h"

// Overrides the new keyword to store newly allocated memory to the garbage collector.
#define new GC += new

// Overrides the malloc() function to store newly allocated memory to the garbage collector.
#define malloc GC + malloc

// Overrides the calloc() function to store newly allocated memory to the garbage collector.
#define calloc GC + calloc

// Overrides the realloc() function to store newly allocated memory to the garbage collector.
#define realloc GC + realloc

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

	// MEMORY ALLOCATION

	// •  Allocates new memory in place of the new keyword.
	// •  Stores the pointer in the garbage collector's memory before returning the new pointer.
	template<typename DataType> DataType*& AllocateCPPMemory(DataType*& ptr)
	{
		cppMemory.push_back(ptr);

		return ptr;
	}

	// •  Allocates new memory in place of the malloc() functions.
	// •  Stores the pointer in the garbage collector's memory before returning the new pointer.
	void*& AllocateCMemory(void*& ptr)
	{
		cMemory.push_back(ptr);

		return ptr;
	}


	// MEMORY ALLOCATION OPERATOR

	// Operator used to take new pointers as a parameter for the AllocateCPPMemory() function.
	template<typename DataType> DataType*& operator+=(DataType* ptr)
	{
		return AllocateCPPMemory(ptr);
	}

	// Operator used to take new pointers as a parameter for the AllocateCMemory() function.
	void*& operator+(void* ptr)
	{
		return AllocateCMemory(ptr);
	}


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

	// •  Deallocates new memory in place of the delete keyword.
	// •  Removes the pointer from the garbage collector's memory.
	template <typename DataType> void DeallocateCPPMemory(DataType*& ptr)
	{
		if (ptr != nullptr)
		{
			for (int i = 0; i < cppMemory.size(); i++)
			{
				if (cppMemory[i] == ptr)
				{
					cppMemory[i] = nullptr;

					cppMemory.erase(cppMemory.begin() + i);

					break;
				}
			}

			delete ptr;

			ptr = nullptr;
		}
	}

	// •  Deallocates new memory in place of the free() function.
	// •  Removes the pointer from the garbage collector's memory.
	template <typename DataType> void DeallocateCMemory(DataType*& ptr)
	{
		if (ptr != nullptr)
		{
			for (int i = 0; i < cMemory.size(); i++)
			{
				if (cMemory[i] == ptr)
				{
					cMemory[i] = nullptr;

					cMemory.erase(cMemory.begin() + i);

					break;
				}
			}

			free(ptr);

			ptr = nullptr;
		}
	}

	// •  Deallocates new memory in place of the free() function.
	// •  Removes the pointer from the garbage collector's memory.
	void DeallocateCMemory(void*& ptr)
	{
		if (ptr != nullptr)
		{
			for (int i = 0; i < cMemory.size(); i++)
			{
				if (cMemory[i] == ptr)
				{
					cMemory[i] = nullptr;

					cMemory.erase(cMemory.begin() + i);

					break;
				}
			}

			free(ptr);

			ptr = nullptr;
		}
	}


	// MEMORY DEALLOCATION OPERATOR

	// Operator used to take new pointers as a parameter for the DeallocateCPPMemory() function.
	template<typename DataType> void operator-=(DataType*& ptr)
	{
		DeallocateCPPMemory(ptr);
	}


	// DECONSTRUCTOR

	// Deallocates the garbage collector's remaining memory when the program closes.
	~GarbageCollector()
	{
		CollectGarbage();
	}
};

// Overrides the delete keyword to safely delete and remove memory from the garbage collector while also deleteing the memory.
#define delete GC -= 

// Overrides the free() function to safely delete and remove memory from the garbage collector.
#define free GC.DeallocateCMemory

// This program's global instance of the garbage collector.
GarbageCollector GC = GarbageCollector();
