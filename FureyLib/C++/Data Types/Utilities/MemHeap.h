// .h
// Custom Memory Heap Class
// by Kyle Furey

#pragma once
#include <iostream>
#include <map>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <cstring>
#include <cstdint>


// MACROS

#ifndef MEMHEAP_THROWS
// Whether the Memory Heap class will throw exceptions.
#define MEMHEAP_THROWS 1
#endif

#ifndef MEMHEAP_DEFAULT_SIZE
// The default size of the Memory Heap class.
#define MEMHEAP_DEFAULT_SIZE 1024
#endif

#ifndef MEMHEAP_SINGLETON
// Whether the Memory Heap class will store a singleton named Heap.
#define MEMHEAP_SINGLETON 1
#endif


// MEMORY HEAP

/** A class that manages a fixed block of memory that can be used to allocate and deallocate blocks dynamically. */
template<size_t SIZE = MEMHEAP_DEFAULT_SIZE>
class MemHeap final {
	static_assert(SIZE != 0, "ERROR: Cannot allocate a heap with 0 bytes!");

	// DATA

	/** The number of bytes currently allocated in the heap. */
	size_t usage;

	/** The underlying block of memory managed by this heap. */
	uint8_t memory[SIZE];

	/** Each allocated block of memory and its size. */
	std::map<void*, size_t> blocks;

public:

	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor. */
	MemHeap(const bool ZeroMemory = false) : usage(0), memory(), blocks() {
		if (ZeroMemory) {
			std::memset(memory, 0, SIZE);
		}
	}

	/** Delete copy constructor. */
	MemHeap(const MemHeap&) = delete;

	/** Delete move constructor. */
	MemHeap(MemHeap&&) noexcept = delete;

	/** Destructor. */
	~MemHeap() {
		if (blocks.size() > 0) {
			std::cerr << "\n\nWARNING: Heap leaked " << blocks.size() << (blocks.size() == 1 ? " pointer on destruction!" : " pointers on destruction!") << std::endl;
		}
	}


	// OPERATORS

	/** Delete copy assignment operator. */
	MemHeap& operator=(const MemHeap&) = delete;

	/** Delete move assignment operator. */
	MemHeap& operator=(MemHeap&&) noexcept = delete;


	// SIZE

	/** Returns the total size of this heap. */
	size_t Size() const {
		return SIZE;
	}

	/** Returns the current number of dynamic allocations. */
	size_t Allocations() const {
		return blocks.size();
	}

	/** Returns the total number of bytes currently being used. */
	size_t Pressure() const {
		return usage;
	}

	/** Returns the total number of bytes currently not being used. */
	size_t Budget() const {
		return SIZE - usage;
	}

	/** Returns whether the given pointer was allocated by this heap. */
	bool IsAllocated(void* Pointer) const {
		return blocks.count(Pointer) != 0;
	}

	/** Returns the size of the given pointer's memory or zero if it was not allocated. */
	size_t SizeOf(void* Pointer) const {
		return blocks.count(Pointer) ? blocks.at(Pointer) : 0;
	}

	/** Returns whether the given blocks of memory overlap. */
	bool DoesMemoryOverlap(void* PointerA, const size_t SizeA, void* PointerB, const size_t SizeB) const {
		if (SizeA == 0 || SizeB == 0) {
			return false;
		}
		return (static_cast<uint8_t*>(PointerA) < static_cast<uint8_t*>(PointerB) + SizeB) && (static_cast<uint8_t*>(PointerB) < static_cast<uint8_t*>(PointerA) + SizeA);
	}

	/** Logs the current state of this heap. */
	void Dump() const {
		std::cout << "HEAP DUMP\n" << blocks.size() << (blocks.size() == 1 ? " ALLOCATED BLOCK\n" : " ALLOCATED BLOCKS\n");
		for (auto& Block : blocks) {
			std::cout << Block.first << " - " << Block.second << (Block.second == 1 ? " byte\n" : " bytes\n");
		}
		std::cout << "TOTAL: " << usage << " / " << SIZE << (SIZE == 1 ? " byte" : " bytes") << std::endl;
	}


	// ALLOCATION

	/** Allocates a new pointer to raw memory of the given size. */
	void* Malloc(const size_t Size) {
		if (Size == 0) {
#if MEMHEAP_THROWS
			std::cerr << "\n\nERROR: Allocating zero bytes of memory!" << std::endl;
			throw std::runtime_error("ERROR: Allocating zero bytes of memory!");
#else
			return nullptr;
#endif
		}
		if (Size > SIZE) {
#if MEMHEAP_THROWS
			std::cerr << "\n\nERROR: Allocating more memory than the heap!" << std::endl;
			throw std::runtime_error("ERROR: Allocating more memory than the heap!");
#else
			return nullptr;
#endif
		}
		uint8_t* NextBlock = memory;
		bool Success = NextBlock + Size <= memory + SIZE;
		if (Success) {
			for (auto& Block : blocks) {
				if (DoesMemoryOverlap(NextBlock, Size, Block.first, Block.second)) {
					Success = false;
					break;
				}
			}
			if (Success) {
				blocks.emplace(NextBlock, Size);
				usage += Size;
				return NextBlock;
			}
		}
		for (auto& Block1 : blocks) {
			NextBlock = static_cast<uint8_t*>(Block1.first) + Block1.second;
			Success = NextBlock + Size <= memory + SIZE;
			if (Success) {
				for (auto& Block2 : blocks) {
					if (Block1.first == Block2.first) {
						continue;
					}
					if (DoesMemoryOverlap(NextBlock, Size, Block2.first, Block2.second)) {
						Success = false;
						break;
					}
				}
				if (Success) {
					blocks.emplace(NextBlock, Size);
					usage += Size;
					return NextBlock;
				}
			}
		}
#if MEMHEAP_THROWS
		std::cerr << "\n\nERROR: Out of heap memory!" << std::endl;
		throw std::runtime_error("ERROR: Out of heap memory!");
#else
		return nullptr;
#endif
	}

	/**
	 * Allocates a new pointer to raw memory of the given size and count.<br/>
	 * The new block of memory is zero-initialized and stored contiguously.
	 */
	void* Calloc(const size_t Count, const size_t Size) {
		if (Size != 0 && Count > SIZE / Size) {
#if MEMHEAP_THROWS
			std::cerr << "\n\nERROR: Calloc overflow (Count * Size > SIZE_MAX)!" << std::endl;
			throw std::runtime_error("ERROR: Calloc overflow (Count * Size > SIZE_MAX)!");
#else
			return nullptr;
#endif
		}
		const size_t Total = Count * Size;
		uint8_t* Pointer = static_cast<uint8_t*>(Malloc(Total));
#if !MEMHEAP_THROWS
		if (Pointer == nullptr) {
			return nullptr;
		}
#endif
		return std::memset(Pointer, 0, Total);
	}

	/**
	 * Reallocates the given pointer to hold the given size.<br/>
	 * This is done either by expanding, shrinking, or moving the given pointer's block of raw memory.
	 */
	void* Realloc(void* Pointer, const size_t NewSize) {
		if (Pointer == nullptr) {
			return Malloc(NewSize);
		}
		if (!blocks.count(Pointer)) {
#if MEMHEAP_THROWS
			std::cerr << "\n\nERROR: Reallocating memory not owned by this heap!" << std::endl;
			throw std::runtime_error("ERROR: Reallocating memory not owned by this heap!");
#else
			return nullptr;
#endif
		}
		if (NewSize == 0) {
#if MEMHEAP_THROWS
			std::cerr << "\n\nERROR: Reallocating memory to zero bytes!" << std::endl;
			throw std::runtime_error("ERROR: Reallocating memory to zero bytes!");
#else
			return nullptr;
#endif
		}
		size_t& Size = blocks.at(Pointer);
		if (NewSize == Size) {
			return Pointer;
		}
		if (NewSize < Size) {
			Size = NewSize;
			return Pointer;
		}
		else {
			for (auto& Block : blocks) {
				if (Pointer != Block.first && DoesMemoryOverlap(Pointer, NewSize, Block.first, Block.second)) {
					uint8_t* NewPointer = static_cast<uint8_t*>(Malloc(NewSize));
#if MEMHEAP_THROWS
					std::memcpy(NewPointer, Pointer, Size);
					blocks.erase(Pointer);
					blocks.emplace(NewPointer, NewSize);
					return NewPointer;
#else
					if (NewPointer != nullptr) {
						std::memcpy(NewPointer, Pointer, Size);
						blocks.erase(Pointer);
						blocks.emplace(NewPointer, NewSize);
						return NewPointer;
					}
					else {
						return Pointer;
					}
#endif
				}
			}
			if (static_cast<uint8_t*>(Pointer) + NewSize > memory + SIZE) {
#if MEMHEAP_THROWS
				std::cerr << "\n\nERROR: Out of heap memory!" << std::endl;
				throw std::runtime_error("ERROR: Out of heap memory!");
#else
				return Pointer;
#endif
			}
			Size = NewSize;
			return Pointer;
		}
	}

	/** Allocates a new pointer of the given type after calling its constructor with the given arguments. */
	template<typename Type, typename ... ArgumentTypes>
	Type* New(ArgumentTypes&&... Arguments) {
		Type* Pointer = static_cast<Type*>(Malloc(sizeof(Type)));
#if !MEMHEAP_THROWS
		if (Pointer == nullptr) {
			return nullptr;
		}
#endif
		return new (Pointer) Type(std::forward<ArgumentTypes>(Arguments)...);
	}

	/** Allocates a new pointer to an array of the given type after default constructing each element. */
	template<typename Type>
	Type* NewArray(const size_t Count) {
		if (Count == 0) {
			return nullptr;
		}
		Type* Pointer = static_cast<Type*>(Malloc(sizeof(Type) * Count));
#if !MEMHEAP_THROWS
		if (Pointer == nullptr) {
			return nullptr;
		}
#endif
		for (size_t Index = 0; Index < Count; ++Index) {
			new (Pointer + Index) Type();
		}
		return Pointer;
	}


	// DEALLOCATION

	/** Frees the given pointer's memory from this heap. */
	void Free(void* Pointer) {
		if (Pointer != nullptr) {
			if (blocks.count(Pointer)) {
				usage -= blocks.at(Pointer);
				blocks.erase(Pointer);
			}
#if MEMHEAP_THROWS
			else {
				std::cerr << "\n\nERROR: Deleting memory that is not owned by this heap!" << std::endl;
				throw std::runtime_error("ERROR: Deleting memory that is not owned by this heap!");
			}
#endif
		}
	}

	/** Frees the given pointer to the given type's memory from this heap after calling its destructor. */
	template<typename Type>
	void Delete(Type* Pointer) {
		if (Pointer != nullptr) {
			if (blocks.count(Pointer)) {
				Pointer->~Type();
				blocks.erase(Pointer);
			}
#if MEMHEAP_THROWS
			else {
				std::cerr << "\n\nERROR: Deleting memory that is not owned by this heap!" << std::endl;
				throw std::runtime_error("ERROR: Deleting memory that is not owned by this heap!");
			}
#endif
		}
	}

	/** Frees the given pointer to an array of the given type after calling each element's destructor. */
	template<typename Type>
	void DeleteArray(Type* Pointer) {
		if (Pointer != nullptr) {
			if (blocks.count(Pointer)) {
				const size_t Count = blocks.at(Pointer) / sizeof(Type);
				for (size_t Index = 0; Index < Count; ++Index) {
					Pointer[Index].~Type();
				}
				blocks.erase(Pointer);
			}
#if MEMHEAP_THROWS
			else {
				std::cerr << "\n\nERROR: Deleting memory that is not owned by this heap!" << std::endl;
				throw std::runtime_error("ERROR: Deleting memory that is not owned by this heap!");
			}
#endif
		}
	}
};


// STATIC VARIABLE INITIALIZATION

#if MEMHEAP_SINGLETON
/** The global instance of the Memory Heap. */
MemHeap<> Heap;
#endif	// MEMHEAP_SINGLETON
