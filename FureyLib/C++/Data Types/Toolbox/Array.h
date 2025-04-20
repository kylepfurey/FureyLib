// .h
// Fixed Array Type
// by Kyle Furey

#pragma once
#include <string>
#include <random>
#include <initializer_list>
#include <stdexcept>
#include "Toolbox/Sorting.h"

/** A collection of useful template types in C++. */
namespace Toolbox {

	// ARRAY

	/** Represents a fixed size array of the given type. */
	template<typename Type, size_t SIZE>
	class Array final {
		static_assert(SIZE != 0, "ERROR: Cannot initialize an array of size 0!");

		// DATA

		/** The underlying array of this type. */
		Type data[SIZE];

	public:

		// CONSTRUCTORS AND DESTRUCTOR

		/** Fill constructor. */
		Array(const Type& Value = Type()) : data() {
			for (size_t Index = 0; Index < SIZE; ++Index) {
				data[Index] = Value;
			}
		}

		/** Array constructor. */
		Array(const Type* Array) : data() {
			if (Array == nullptr) {
				for (size_t Index = 0; Index < SIZE; ++Index) {
					data[Index] = Type();
				}
				return;
			}
			for (size_t Index = 0; Index < SIZE; ++Index) {
				data[Index] = Array[Index];
			}
		}

		/** Initializer list constructor. */
		Array(const std::initializer_list<Type>& List) : data() {
			for (size_t Index = 0; Index < SIZE; ++Index) {
				data[Index] = 0;
			}
			size_t Count = List.size() > SIZE ? SIZE : List.size();
			for (size_t Index = 0; Index < Count; ++Index) {
				data[Index] = *(List.begin() + Index);
			}
		}


		// OPERATORS

		/** Returns a reference to the data at the given index. */
		Type& operator[](const size_t Index) {
			if (!IsValidIndex(Index)) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Index) +
					" is out of bounds of the array of size " +
					std::to_string(SIZE) + ".");
			}
			return data[Index];
		}

		/** Returns a constant reference to the data at the given index. */
		const Type& operator[](const size_t Index) const {
			if (!IsValidIndex(Index)) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Index) +
					" is out of bounds of the array of size " +
					std::to_string(SIZE) + ".");
			}
			return data[Index];
		}


		// ITERATORS

		/** Returns a pointer to the first element in the array. */
		Type* begin() {
			return data;
		}

		/** Returns a constant pointer to the first element in the array. */
		const Type* begin() const {
			return data;
		}

		/** Returns a pointer to after the last element in the array. */
		Type* end() {
			return data + SIZE;
		}

		/** Returns a constant pointer to after the last element in the array. */
		const Type* end() const {
			return data + SIZE;
		}


		// GETTERS

		/** Returns the number of elements in the array. */
		size_t Size() const {
			return SIZE;
		}

		/** Returns whether the given index is a valid index in the array. */
		bool IsValidIndex(const size_t Index) const {
			return Index < SIZE;
		}

		/** Returns a reference to the data at the given index. */
		Type& Get(const size_t Index) {
			if (!IsValidIndex(Index)) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Index) +
					" is out of bounds of the array of size " +
					std::to_string(SIZE) + ".");
			}
			return data[Index];
		}

		/** Returns a constant reference to the data at the given index. */
		const Type& Get(const size_t Index) const {
			if (!IsValidIndex(Index)) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Index) +
					" is out of bounds of the array of size " +
					std::to_string(SIZE) + ".");
			}
			return data[Index];
		}

		/** Returns a reference to the data at the front of the array. */
		Type& Front() {
			return data[0];
		}

		/** Returns a constant reference to the data at the front of the array. */
		const Type& Front() const {
			return data[0];
		}

		/** Returns a reference to the data at the back of the array. */
		Type& Back() {
			return data[SIZE - 1];
		}

		/** Returns a constant reference to the data at the back of the array. */
		const Type& Back() const {
			return data[SIZE - 1];
		}

		/** Returns the index of the first matching value in the array, or -1 if no match is found. */
		ptrdiff_t Find(const Type& Value) const {
			for (ptrdiff_t Index = 0; Index < static_cast<ptrdiff_t>(SIZE); ++Index) {
				if (data[Index] == Value) {
					return Index;
				}
			}
			return -1;
		}

		/** Returns the index of the last matching value in the array, or -1 if no match is found. */
		ptrdiff_t FindLast(const Type& Value) const {
			for (ptrdiff_t Index = SIZE - 1; Index >= 0; --Index) {
				if (data[Index] == Value) {
					return Index;
				}
			}
			return -1;
		}

		/** Returns whether the given value is present in the array. */
		bool Contains(const Type& Value) const {
			return Find(Value) != -1;
		}

		/** Returns the total number of elements that match the given value in the array. */
		size_t Total(const Type& Value) const {
			size_t Total = 0;
			for (size_t Index = 0; Index < SIZE; ++Index) {
				if (data[Index] == Value) {
					++Total;
				}
			}
			return Total;
		}

		/** Returns whether the array is sorted using Type's > operator. */
		bool IsSorted() const {
			return Sorting::IsSorted<Array, Type>(SIZE, *this);
		}


		// SETTERS

		/** Sets the data at the given index with a copy of the given value. */
		void Set(const size_t Index, const Type& Value) {
			if (!IsValidIndex(Index)) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Index) +
					" is out of bounds of the array of size " +
					std::to_string(SIZE) + ".");
			}
			data[Index] = Value;
		}

		/** Swaps the given elements at the given indicies. */
		void Swap(const size_t Left, const size_t Right) {
			if (!IsValidIndex(Left)) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Left) +
					" is out of bounds of the array of size " +
					std::to_string(SIZE) + ".");
			}
			if (!IsValidIndex(Right)) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Right) +
					" is out of bounds of the array of size " +
					std::to_string(SIZE) + ".");
			}
			const Type Swapped = data[Left];
			data[Left] = data[Right];
			data[Right] = Swapped;
		}

		/** Fills the array with a copy of the given value. */
		void Fill(const Type& Value) {
			for (size_t Index = 0; Index < SIZE; ++Index) {
				data[Index] = Value;
			}
		}

		/** Bubble sorts the array using Type's > operator. */
		void BubbleSort() {
			Sorting::BubbleSort<Array, Type>(SIZE, *this);
		}

		/** Merge sorts the array using Type's > operator. */
		void MergeSort() {
			Sorting::MergeSort<Array, Type>(SIZE, *this);
		}

		/** Quick sorts the array using Type's > operator. */
		void QuickSort() {
			Sorting::QuickSort<Array, Type>(SIZE, *this);
		}

		/** Reverses the array. */
		void Reverse() {
			for (size_t Index = 0; Index < SIZE / 2; ++Index) {
				const Type Swapped = data[Index];
				data[Index] = data[SIZE - Index - 1];
				data[SIZE - Index - 1] = Swapped;
			}
		}

		/** Shuffles the array. */
		void Shuffle() {
			for (size_t Index = 0; Index < SIZE; ++Index) {
				const Type Swapped = data[Index];
				const size_t Random = std::rand() % SIZE;
				data[Index] = data[Random];
				data[Random] = Swapped;
			}
		}


		// TO STRING

		/** Returns the array as a string. */
		std::string ToString() const {
			std::string String = "[ ";
			for (size_t Index = 0; Index < SIZE; ++Index) {
				String += std::to_string(data[Index]);
				String += (Index != SIZE - 1) ? ", " : " ";
			}
			return String += "]";
		}
	};
}
