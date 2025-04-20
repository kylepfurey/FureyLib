// .h
// Hash Set Type
// by Kyle Furey

#pragma once
#include <functional>
#include <utility>
#include <cstdint>
#include "Vector.h"
#include "List.h"

// The maximum number of elements allowed in a bucket before rehashing.
#define REHASH_MAX 3

/** A collection of useful template types in C++. */
namespace Toolbox {

	// HASH FUNCTION

	/** A unique value that represents the current state of an instance. */
	using Hash = size_t;

	/** Returns a unique unsigned number representing the state of the given value's binary. */
	template<typename Type>
	static Hash Hashify(const Type& Value) {
		return std::hash<Type>{}(Value);
		/*
		void* Memory = (void*)&Value;
		switch (sizeof(Type)) {
		case 1:
			return (Hash)(*(uint8_t*)Memory);
		case 2:
		case 3:
			return (Hash)(*(uint16_t*)Memory);
		case 4:
		case 5:
		case 6:
		case 7:
			return (Hash)(*(uint32_t*)Memory);
		default:
			return (Hash)(*(uint64_t*)Memory);
		}
		*/
	}


	// HASH SET

	/** A collection of values that allow fast lookups via hashing. */
	template<typename Type, Hash(*HASH_FUNC)(const Type&) = Hashify>
	class Set final {
		static_assert(HASH_FUNC != nullptr, "ERROR: Cannot pass a null function as a template parameter!");

		// DATA

		/** The current number of values stored in the set. */
		size_t size;

		/** The underlying array of buckets containing each of the set's values. */
		Vector<List<Type>> buckets;

	public:

		// CONSTRUCTORS

		/** Default constructor. */
		Set(const size_t BucketCount = 8) : size(0), buckets(BucketCount == 0 ? 1 : BucketCount) {
		}

		/** Copy constructor. */
		Set(const Set<Type, HASH_FUNC>& Copied) : size(Copied.size), buckets(Copied.buckets) {
		}

		/** Move constructor. */
		Set(Set<Type, HASH_FUNC>&& Moved) noexcept : size(Moved.size), buckets(std::move(Moved.buckets)) {
			Moved.size = 0;
		}


		// OPERATORS

		/** Copy assignment operator. */
		Set<Type, HASH_FUNC>& operator=(const Set<Type, HASH_FUNC>& Copied) {
			size = Copied.size;
			buckets = Copied.buckets;
			return *this;
		}

		/** Move assignment operator. */
		Set<Type, HASH_FUNC>& operator=(Set<Type, HASH_FUNC>&& Moved) noexcept {
			size = Moved.size;
			buckets = std::move(Moved.buckets);
			Moved.size = 0;
			return *this;
		}

		/** Returns whether the given value is present in the set. */
		bool operator[](const Type& Value) {
			return Contains(Value);
		}


		// GETTERS

		/** Returns the number of values in the set. */
		size_t Size() const {
			return size;
		}

		/** Returns the number of buckets in the set. */
		size_t Buckets() const {
			return buckets.Size();
		}

		/** Returns this set's hash function. */
		Hash(*HashFunction() const)(const Type&) {
			return HASH_FUNC;
		}

		/** Returns whether the given value is present in the set. */
		bool Contains(const Type& Value) const {
			size_t Index = HASH_FUNC(Value) % buckets.Size();
			for (auto& Element : buckets[Index]) {
				if (Element == Value) {
					return true;
				}
			}
			return false;
		}

		/** Returns whether the set is empty. */
		bool IsEmpty() const {
			return size == 0;
		}

		/** Returns a copy of each of the values in the set in a vector. */
		Vector<Type> Values() const {
			Vector<Type> Values(size);
			size_t Index = 0;
			for (auto& Bucket : buckets) {
				for (auto& Element : Bucket) {
					Values[Index] = Element;
					++Index;
				}
			}
			return Values;
		}


		// EXPANSION

		/** Deallocates the set. */
		void Clear() {
			for (auto& Bucket : buckets) {
				Bucket.Clear();
			}
			size = 0;
		}

		/** Inserts a copy of the given value into the set and returns whether a new element was successfully inserted. */
		bool Insert(const Type& Value) {
			size_t Index = HASH_FUNC(Value) % buckets.Size();
			size_t ElementIndex = 0;
			for (auto& Element : buckets[Index]) {
				if (Element == Value) {
					buckets[Index][ElementIndex] = Value;
					return false;
				}
				++ElementIndex;
			}
			buckets[Index].PushBack(Value);
			++size;
			if (buckets[Index].Size() > REHASH_MAX) {
				Rehash(buckets.Size() * 2);
			}
			return true;
		}

		/** Erases any matching value found in the set and returns whether the value was found and successfully erased. */
		bool Erase(const Type& Value) {
			size_t Index = HASH_FUNC(Value) % buckets.Size();
			size_t ElementIndex = 0;
			for (auto& Element : buckets[Index]) {
				if (Element == Value) {
					buckets[Index].Erase(ElementIndex);
					--size;
					return true;
				}
				++ElementIndex;
			}
			return false;
		}

		/**
		 * Resizes the set's number of buckets to the given number.<br/>
		 * All values are copied into the new buckets based on their hash value.
		 */
		void Rehash(const size_t BucketCount) {
			if (BucketCount == 0 || BucketCount == buckets.Size()) {
				return;
			}
			Vector<List<Type>> Buckets(BucketCount);
			for (auto& Bucket : buckets) {
				for (auto& Element : Bucket) {
					Buckets[HASH_FUNC(Element) % Buckets.Size()].PushBack(Element);
				}
			}
			buckets = Buckets;
		}


		// TO STRING

		/** Returns the set as a string. */
		std::string ToString(const bool NewlineBuckets = false) const {
			if (NewlineBuckets) {
				std::string String = "{";
				for (auto& Bucket : buckets) {
					if (Bucket.Size() > 0) {
						String += "\n\t";
						for (auto& Element : Bucket) {
							String += std::to_string(Element) + ", ";
						}
					}
					else {
						String += "\n\t_, ";
					}
				}
				if (size > 0) {
					String.erase(String.length() - 2, 2);
					String += "\n";
				}
				String += "}";
				return String;
			}
			else {
				std::string String = "{ ";
				for (auto& Bucket : buckets) {
					for (auto& Element : Bucket) {
						String += std::to_string(Element) + ", ";
					}
				}
				if (size > 0) {
					String.erase(String.length() - 2, 2);
					String += " }";
				}
				else {
					String += "}";
				}
				return String;
			}
		}


		// AS VECTOR

		/** Returns a reference to this set's underlying vector. */
		Vector<List<Type>>& AsVector() {
			return buckets;
		}

		/** Returns a constant reference to this set's underlying vector. */
		const Vector<List<Type>>& AsVector() const {
			return buckets;
		}
	};
}
