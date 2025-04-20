// .h
// Hash Map Type
// by Kyle Furey

#pragma once
#include "Set.h"

/** A collection of useful template types in C++. */
namespace Toolbox {

	// HASH MAP

	/** A collection of key value pairs that allow fast value lookups via hashing a key. */
	template<typename KeyType, typename ValueType, Hash(*HASH_FUNC)(const KeyType&) = Hashify>
	class Map final {
		static_assert(HASH_FUNC != nullptr, "ERROR: Cannot pass a null function as a template parameter!");

		// PAIR

		/** A key value pair used to access the pair's value via finding its key. */
		struct Pair final {

			// DATA

			/** The key used to lookup this pair's value. */
			KeyType key;

			/** The value this pair is storing. */
			ValueType value;


			// CONSTRUCTOR

			/** Default constructor. */
			Pair(const KeyType& Key = KeyType(), const ValueType& Value = ValueType()) : key(Key), value(Value) {
			}
		};


		// DATA

		/** The current number of pairs stored in the map. */
		size_t size;

		/** The underlying array of buckets containing each of the map's pairs. */
		Vector<List<Pair>> buckets;

	public:

		// CONSTRUCTORS

		/** Default constructor. */
		Map(const size_t BucketCount = 8) : size(0), buckets(BucketCount == 0 ? 1 : BucketCount) {
		}

		/** Copy constructor. */
		Map(const Map<KeyType, ValueType, HASH_FUNC>& Copied) : size(Copied.size), buckets(Copied.buckets) {
		}

		/** Move constructor. */
		Map(Map<KeyType, ValueType, HASH_FUNC>&& Moved) noexcept : size(Moved.size), buckets(std::move(Moved.buckets)) {
			Moved.size = 0;
		}


		// OPERATORS

		/** Copy assignment operator. */
		Map<KeyType, ValueType, HASH_FUNC>& operator=(const Map<KeyType, ValueType, HASH_FUNC>& Copied) {
			size = Copied.size;
			buckets = Copied.buckets;
			return *this;
		}

		/** Move assignment operator. */
		Map<KeyType, ValueType, HASH_FUNC>& operator=(Map<KeyType, ValueType, HASH_FUNC>&& Moved) noexcept {
			size = Moved.size;
			buckets = std::move(Moved.buckets);
			Moved.size = 0;
			return *this;
		}

		/** Returns a reference to the given key's value, or inserts a new value with the given key. */
		ValueType& operator[](const KeyType& Key) {
			auto Value = Find(Key);
			if (Value) {
				return *Value;
			}
			return Insert(Key, ValueType());
		}


		// GETTERS

		/** Returns the number of pairs in the map. */
		size_t Size() const {
			return size;
		}

		/** Returns the number of buckets in the map. */
		size_t Buckets() const {
			return buckets.Size();
		}

		/** Returns this map's hash function. */
		Hash(*HashFunction() const)(const KeyType&) {
			return HASH_FUNC;
		}

		/** Finds and returns a pointer to the given key's value in the map, or nullptr if it does not exist. */
		ValueType* Find(const KeyType& Key) {
			size_t Index = HASH_FUNC(Key) % buckets.Size();
			size_t ElementIndex = 0;
			for (auto& Pair : buckets[Index]) {
				if (Pair.key == Key) {
					return &buckets[Index][ElementIndex].value;
				}
				++ElementIndex;
			}
			return nullptr;
		}

		/** Finds and returns a constant pointer to the given key's value in the map, or nullptr if it does not exist. */
		const ValueType* Find(const KeyType& Key) const {
			size_t Index = HASH_FUNC(Key) % buckets.Size();
			size_t ElementIndex = 0;
			for (auto& Pair : buckets[Index]) {
				if (Pair.key == Key) {
					return &buckets[Index][ElementIndex].value;
				}
				++ElementIndex;
			}
			return nullptr;
		}

		/** Returns whether the given key is present in the map. */
		bool ContainsKey(const KeyType& Key) const {
			return Find(Key) != nullptr;
		}

		/** Returns whether the given value is present in the map. */
		bool ContainsValue(const ValueType& Value) const {
			for (auto& Bucket : buckets) {
				for (auto& Pair : Bucket) {
					if (Pair.value == Value) {
						return true;
					}
				}
			}
			return false;
		}

		/** Returns the total number of matching values in the map. */
		size_t Total(const ValueType& Value) const {
			size_t Total = 0;
			for (auto& Bucket : buckets) {
				for (auto& Pair : Bucket) {
					if (Pair.value == Value) {
						++Total;
					}
				}
			}
			return Total;
		}

		/** Returns whether the map is empty. */
		bool IsEmpty() const {
			return size == 0;
		}

		/** Returns a copy of each of the keys in the map in a vector. */
		Vector<KeyType> Keys() const {
			Vector<KeyType> Keys(size);
			size_t Index = 0;
			for (auto& Bucket : buckets) {
				for (auto& Pair : Bucket) {
					Keys[Index] = Pair.key;
					++Index;
				}
			}
			return Keys;
		}

		/** Returns a copy of each of the values in the map in a vector. */
		Vector<ValueType> Values() const {
			Vector<ValueType> Values(size);
			size_t Index = 0;
			for (auto& Bucket : buckets) {
				for (auto& Pair : Bucket) {
					Values[Index] = Pair.value;
					++Index;
				}
			}
			return Values;
		}


		// EXPANSION

		/** Deallocates the map. */
		void Clear() {
			for (auto& Bucket : buckets) {
				Bucket.Clear();
			}
			size = 0;
		}

		/** Inserts a copy of the given value into the map with the given key and returns a reference to the value. */
		ValueType& Insert(const KeyType& Key, const ValueType& Value) {
			size_t Index = HASH_FUNC(Key) % buckets.Size();
			size_t ElementIndex = 0;
			for (auto& Pair : buckets[Index]) {
				if (Pair.key == Key) {
					buckets[Index][ElementIndex].value = Value;
					return buckets[Index][ElementIndex].value;
				}
				++ElementIndex;
			}
			buckets[Index].PushBack(Pair(Key, Value));
			++size;
			ValueType* NewValue = &buckets[Index].Back().value;
			if (buckets[Index].Size() > REHASH_MAX) {
				Rehash(buckets.Size() * 2);
			}
			return *NewValue;
		}

		/** Erases any matching key found in the map and returns whether a pair was found and successfully erased. */
		bool Erase(const KeyType& Key) {
			size_t Index = HASH_FUNC(Key) % buckets.Size();
			size_t ElementIndex = 0;
			for (auto& Pair : buckets[Index]) {
				if (Pair.key == Key) {
					buckets[Index].Erase(ElementIndex);
					--size;
					return true;
				}
				++ElementIndex;
			}
			return false;
		}

		/**
		 * Resizes the map's number of buckets to the given number.<br/>
		 * All pairs are copied into the new buckets based on their key's hash value.
		 */
		void Rehash(const size_t BucketCount) {
			if (BucketCount == 0 || BucketCount == buckets.Size()) {
				return;
			}
			Vector<List<Pair>> Buckets(BucketCount);
			for (auto& Bucket : buckets) {
				for (auto& Element : Bucket) {
					Buckets[HASH_FUNC(Element.key) % Buckets.Size()].PushBack(Pair(Element.key, Element.value));
				}
			}
			buckets = Buckets;
		}


		// TO STRING

		/** Returns the map as a string. */
		std::string ToString(const bool NewlineBuckets = false) const {
			if (NewlineBuckets) {
				std::string String = "{";
				for (auto& Bucket : buckets) {
					if (Bucket.Size() > 0) {
						String += "\n\t";
						for (auto& Pair : Bucket) {
							String += "( " + std::to_string(Pair.key) + " : " + std::to_string(Pair.value) + " ), ";
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
					for (auto& Pair : Bucket) {
						String += "( " + std::to_string(Pair.key) + " : " + std::to_string(Pair.value) + " ), ";
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

		/** Returns a reference to this map's underlying vector. */
		Vector<List<Pair>>& AsVector() {
			return buckets;
		}

		/** Returns a constant reference to this map's underlying vector. */
		const Vector<List<Pair>>& AsVector() const {
			return buckets;
		}
	};
}
