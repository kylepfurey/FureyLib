// .h
// Mark and Sweep Garbage Collector
// by Kyle Furey

#pragma once
#include <unordered_set>
#include <unordered_map>
#include <cstdint>

/** The minimum alignment of pointers to check for references. */
#define GC_ALIGN 1

/** Manages dynamic memory and automatically frees when no references remain. */
class GarbageCollector final {

	/** Concrete base class for dynamic memory. */
	class GarbageBase {
	public:
		/** The size of this dynamic memory. */
		const size_t SIZE;

		/** Base constructor. */
		GarbageBase(size_t size) : SIZE(size) {
		}

		/** Virtual destructor. */
		virtual ~GarbageBase() = default;
	};

	/** Templated class for dynamic memory. */
	template<typename T>
	class Garbage final : public GarbageBase {
		T* memory;

	public:
		/** Constructor. */
		Garbage(T* memory) : GarbageBase(sizeof(T)), memory(memory) {
		}

		/** Destructor. */
		~Garbage() final {
			delete memory;
			memory = nullptr;
		}
	};

	/** The underlying memory of the garbage collector. */
	std::unordered_map<void*, GarbageBase*> managed;

	/** The address of the start of the stack. */
	uint8_t* stackStart;

public:

	/** Constructor. */
	GarbageCollector() {
		Init();
	}

	/** Destructor. */
	~GarbageCollector() {
		for (auto& memory : managed) {
			delete memory.second;
		}
		managed.clear();
	}

	/** Initializes the garbage collector. */
	void Init() {
		volatile uint8_t start;
		stackStart = (uint8_t*)&start;
	}

	/** Initializes the garbage collector. */
	void operator*() {
		Init();
	}

	/** Adds dynamic memory to the garbage collector. */
	template<typename T>
	T* Mark(T* memory) {
		if (memory == nullptr || managed.count(static_cast<void*>(memory))) {
			return memory;
		}
		managed.emplace(static_cast<void*>(memory), new Garbage<T>(memory));
		return memory;
	}

	/** Adds dynamic memory to the garbage collector. */
	template<typename T>
	T* operator+=(T* memory) {
		return Mark<T>(memory);
	}

	/** Deletes dynamic memory from the garbage collector. */
	template<typename T>
	bool Release(T* memory) {
		if (!managed.count(static_cast<void*>(memory))) {
			return false;
		}
		delete managed.at(static_cast<void*>(memory));
		managed.erase(static_cast<void*>(memory));
		return true;
	}

	/** Deletes dynamic memory from the garbage collector. */
	template<typename T>
	bool operator-=(T* memory) {
		return Release<T>(memory);
	}

	/** Deletes all unreferenced dynamic memory. */
	size_t Sweep() {
		if (managed.empty()) {
			return 0;
		}
		size_t count = 0;
		std::unordered_set<void*> marked;

		// Mark stack references
		do {
			volatile uint8_t end;
			uint8_t* stackEnd = (uint8_t*)&end;
			if (stackStart < stackEnd) {
				uint8_t* begin = stackStart;
				uint8_t* end = begin + static_cast<size_t>(stackEnd - stackStart) - sizeof(void*) + 1;
				for (; begin < end; begin += GC_ALIGN) {
					void* ref = *reinterpret_cast<void**>(begin);
					if (ref != nullptr) {
						marked.insert(ref);
					}
				}
			}
			else {
				uint8_t* begin = stackEnd;
				uint8_t* end = begin + static_cast<size_t>(stackStart - stackEnd) - sizeof(void*) + 1;
				for (; begin < end; begin += GC_ALIGN) {
					void* ref = *reinterpret_cast<void**>(begin);
					if (ref != nullptr) {
						marked.insert(ref);
					}
				}
			}
		} while (false);

		// Mark dynamic memory references
		for (auto& memory : managed) {
			void* address = memory.first;
			GarbageBase* garbage = memory.second;
			uint8_t* begin = reinterpret_cast<uint8_t*>(address);
			uint8_t* end = begin + garbage->SIZE - sizeof(void*) + 1;
			for (; begin < end; begin += GC_ALIGN) {
				void* ref = *reinterpret_cast<void**>(begin);
				if (ref != nullptr) {
					marked.insert(ref);
				}
			}
		}

		// Sweep unreferenced memory
		std::unordered_map<void*, GarbageBase*> copy(managed);
		for (auto& memory : copy) {
			void* address = memory.first;
			if (!marked.count(address)) {
				delete managed.at(address);
				managed.erase(address);
				++count;
			}
		}

		return count;
	}

	/** Deletes all unreferenced dynamic memory. */
	size_t operator()() {
		return Sweep();
	}

	/** Returns whether the garbage collector manages the given dynamic memory. */
	template<typename T>
	bool IsTracked(const T* memory) const {
		return managed.count(memory);
	}

	/** Returns whether the garbage collector manages the given dynamic memory. */
	template<typename T>
	bool operator()(const T* memory) const {
		return IsTracked(memory);
	}
};

/** The global instance of the garbage collector. */
static GarbageCollector GC;

/** Allocates and adds dynamic memory to the garbage collector. */
#define gcnew GC += new

/** Deletes dynamic memory from the garbage collector. */
#define gcdelete GC -=
