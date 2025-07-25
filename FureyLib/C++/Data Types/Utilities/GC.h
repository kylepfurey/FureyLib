// .h
// Compile-time Garbage Collector Class
// by Kyle Furey

#pragma once
#include <iostream>
#include <list>
#include <stdexcept>


// MACROS

#ifndef GC_COMPILED
// Whether the Garbage Collector was compiled.
#define GC_COMPILED 1
#endif


// GARBAGE COLLECTOR

#if GC_COMPILED

/**
 * A singleton class used to automatically manage and free memory at the end of a program's life in C++.<br/>
 * NOTE: Dynamic arrays must be allocated with classes as the Garbage Collector cannot properly delete array pointers.
 */
class GarbageCollector final {

	// GARBAGE

	/** A type with a virtual destructor to ensure type safe deletion of pointers. */
	struct Garbage {

		// DESTRUCTOR

		/** Virtual destructor. */
		virtual ~Garbage() = default;


		// MEMORY

		/** Returns a constant pointer to the memory that this garbage is storing. */
		template<typename Type>
		const Type* Memory() {
			TemplatedGarbage<Type>* Garbage = dynamic_cast<TemplatedGarbage<Type>*>(this);
			if (Garbage == nullptr) {
				return nullptr;
			}
			return Garbage->Memory();
		}
	};


	// TEMPLATED GARBAGE

	/** A type derived from Garbage that ensures type safe deletion of stored pointers. */
	template <typename Type>
	struct TemplatedGarbage final : public Garbage {
	private:

		// DATA

		/** The underlying pointer to the managed memory. */
		Type* memory;

	public:

		// CONSTRUCTOR AND DESTRUCTOR

		/** Default constructor. */
		TemplatedGarbage(Type* Memory = nullptr) : memory(Memory) {
		}

		/** Destructor. */
		~TemplatedGarbage() {
			delete memory;
			memory = nullptr;
		}


		// MEMORY

		/** Returns a constant pointer to the memory that this garbage is storing. */
		const Type* Memory() {
			return memory;
		}
	};


	// DATA

	/** Whether the Garbage Collector is currently enabled. */
	static bool enabled;

	/** A linked list of pointers to the Garbage Collector's managed memory. */
	std::list<Garbage*> garbage;

public:

	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor. */
	GarbageCollector() {
		if (enabled) {
			std::cerr << "\n\nERROR: Only one Garbage Collector may be instantiated at a time!\nUse GC for global access." << std::endl;
			throw std::runtime_error("ERROR: Only one Garbage Collector may be instantiated at a time!\nUse GC for global access.");
		}
		enabled = true;
	}

	/** Destructor. */
	~GarbageCollector() {
		Collect(true);
		enabled = false;
	}


	// OPERATORS

	/** Adds a new pointer to the Garbage Collector. */
	template<typename Type>
	Type* operator+=(Type* Memory) {
		return Track<Type>(Memory);
	}

	/** Removes a pointer from the Garbage Collector and frees it. */
	template<typename Type>
	bool operator-=(Type*& Memory) {
		return Delete<Type>(Memory);
	}


	// GARBAGE COLLECTION

	/** Returns whether the Garbage Collector is currently enabled. */
	static bool IsEnabled() {
		return enabled;
	}

	/** Returns how many pointers are currently stored within the Garbage Collector. */
	size_t Count() const {
		return garbage.size();
	}

	/** Returns whether the given pointer is already referenced in the Garbage Collector. */
	template<typename Type>
	bool IsTracked(const Type* Memory) const {
		if (Memory == nullptr) {
			return false;
		}
		for (auto Garbage : garbage) {
			if (Garbage != nullptr && Garbage->Memory<Type>() == Memory) {
				return true;
			}
		}
		return false;
	}

	/** Adds a new pointer to the Garbage Collector. */
	template<typename Type>
	Type* Track(Type* Memory) {
		if (Memory == nullptr || IsTracked(Memory)) {
			return Memory;
		}
		garbage.push_front(new TemplatedGarbage<Type>(Memory));
		return Memory;
	}

	/** Removes a pointer from the Garbage Collector and frees it. */
	template<typename Type>
	bool Delete(Type*& Memory) {
		if (Memory == nullptr) {
			return false;
		}
		auto Iterator = garbage.begin();
		for (auto& Garbage : garbage) {
			if (Garbage != nullptr && Garbage->Memory<Type>() == Memory) {
				delete Garbage;
				Garbage = nullptr;
				garbage.erase(Iterator);
				Memory = nullptr;
				return true;
			}
			++Iterator;
		}
		return false;
	}

	/**
	 * Deletes ALL of the Garbage Collector's pointers and returns how many were collected.<br/>
	 * NOTE: This is DANGEROUS to manually call as it causes dangling pointers.
	 */
	size_t Collect(bool Log = false) {
		size_t Count = garbage.size();
		for (auto& Garbage : garbage) {
			delete Garbage;
			Garbage = nullptr;
		}
		garbage.clear();
		if (Log) {
			if (Count > 0) {
				std::cout << "\n\nGarbage Collector successfully deleted " << Count << (Count == 1 ? " pointer." : " pointers.") << std::endl;
			}
			else {
				std::cout << "\n\nGarbage Collector had no memory to clean up. Nice work!" << std::endl;
			}
		}
		return Count;
	}
};


// STATIC VARIABLE INITIALIZATION

// Whether the Garbage Collector is currently enabled.
bool GarbageCollector::enabled = false;

/** The global instance of the Garbage Collector. */
GarbageCollector GC;


// KEYWORD OVERRIDES

// Garbage Collector new keyword override.
#define new GC += new

// Garbage Collector delete keyword override.
#define delete GC -=

#endif	// GC_COMPILED


// GARBAGE COLLECTOR

/** Returns whether the Garbage Collector is enabled. */
static bool GCEnabled() {
#if GC_COMPILED
	return GarbageCollector::IsEnabled();
#else
	return false;
#endif
}
