// .h
// Vector Type
// by Kyle Furey

#pragma once
#include <string>
#include <random>
#include <initializer_list>
#include <stdexcept>
#include "Toolbox/Sorting.h"

/** A collection of useful template types in C++. */
namespace Toolbox {

	// VECTOR

	/** Represents a dynamic array of the given type. */
	template<typename Type>
	class Vector final {

		// DATA

		/** The current size of the vector. */
		size_t size;

		/** The current maximum size of the vector. */
		size_t capacity;

		/** The underlying array of this type. */
		Type* data;

	public:

		// CONSTRUCTORS AND DESTRUCTOR

		/** Default constructor. */
		Vector() : size(0), capacity(0), data(nullptr) {}

		/** Fill constructor. */
		Vector(const size_t Size, const Type& Value = Type()) : size(Size), capacity(Size), data(new Type[Size]) {
			for (size_t Index = 0; Index < Size; ++Index) {
				data[Index] = Value;
			}
		}

		/** Array constructor. */
		Vector(const size_t Size, const Type* Array) : size(Size), capacity(Size), data(new Type[Size]) {
			if (Array == nullptr) {
				for (size_t Index = 0; Index < Size; ++Index) {
					data[Index] = Type();
				}
				return;
			}
			for (size_t Index = 0; Index < Size; ++Index) {
				data[Index] = Array[Index];
			}
		}

		/** Initializer list constructor. */
		Vector(const std::initializer_list<Type>& List) : size(List.size()), capacity(List.size()), data(new Type[List.size()]) {
			for (size_t Index = 0; Index < List.size(); ++Index) {
				data[Index] = *(List.begin() + Index);
			}
		}

		/** Copy constructor. */
		Vector(const Vector<Type>& Copied) : size(Copied.size), capacity(Copied.capacity), data(new Type[Copied.capacity]) {
			for (size_t Index = 0; Index < Copied.size; ++Index) {
				data[Index] = Copied.data[Index];
			}
		}

		/** Move constructor. */
		Vector(Vector<Type>&& Moved) noexcept : size(Moved.size), capacity(Moved.capacity), data(Moved.data) {
			Moved.size = 0;
			Moved.capacity = 0;
			Moved.data = nullptr;
		}

		/** Destructor. */
		~Vector() {
			size = 0;
			capacity = 0;
			delete[] data;
			data = nullptr;
		}


		// OPERATORS

		/** Copy assignment operator. */
		Vector<Type>& operator=(const Vector<Type>& Copied) {
			size = Copied.size;
			capacity = Copied.capacity;
			delete[] data;
			data = new Type[capacity];
			for (size_t Index = 0; Index < Copied.size; ++Index) {
				data[Index] = Copied.data[Index];
			}
			return *this;
		}

		/** Move assignment operator. */
		Vector<Type>& operator=(Vector<Type>&& Moved) noexcept {
			if (this == &Moved) {
				return *this;
			}
			size = Moved.size;
			capacity = Moved.capacity;
			delete[] data;
			data = Moved.data;
			Moved.size = 0;
			Moved.capacity = 0;
			Moved.data = nullptr;
			return *this;
		}

		/** Returns a reference to the data at the given index. */
		Type& operator[](const size_t Index) {
			if (!IsValidIndex(Index)) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Index) +
					" is out of bounds of the vector of size " +
					std::to_string(size) + ".");
			}
			return data[Index];
		}

		/** Returns a constant reference to the data at the given index. */
		const Type& operator[](const size_t Index) const {
			if (!IsValidIndex(Index)) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Index) +
					" is out of bounds of the vector of size " +
					std::to_string(size) + ".");
			}
			return data[Index];
		}


		// ITERATORS

		/** Returns a pointer to the first element in the vector. */
		Type* begin() {
			return data;
		}

		/** Returns a constant pointer to the first element in the vector. */
		const Type* begin() const {
			return data;
		}

		/** Returns a pointer to the last element in the vector. */
		Type* end() {
			return data + size;
		}

		/** Returns a constant pointer to the last element in the vector. */
		const Type* end() const {
			return data + size;
		}


		// GETTERS

		/** Returns the number of elements in the vector. */
		size_t Size() const {
			return size;
		}

		/** Returns the current maximum number of elements in the vector. */
		size_t Capacity() const {
			return capacity;
		}

		/** Returns whether the given index is a valid index in the vector. */
		bool IsValidIndex(const size_t Index) const {
			return Index < size;
		}

		/** Returns a reference to the data at the given index. */
		Type& Get(const size_t Index) {
			if (!IsValidIndex(Index)) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Index) +
					" is out of bounds of the vector of size " +
					std::to_string(size) + ".");
			}
			return data[Index];
		}

		/** Returns a constant reference to the data at the given index. */
		const Type& Get(const size_t Index) const {
			if (!IsValidIndex(Index)) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Index) +
					" is out of bounds of the vector of size " +
					std::to_string(size) + ".");
			}
			return data[Index];
		}

		/** Returns a reference to the data at the front of the vector. */
		Type& Front() {
			if (size == 0) {
				throw std::runtime_error("ERROR: The vector is empty!");
			}
			return data[0];
		}

		/** Returns a constant reference to the data at the front of the vector. */
		const Type& Front() const {
			if (size == 0) {
				throw std::runtime_error("ERROR: The vector is empty!");
			}
			return data[0];
		}

		/** Returns a reference to the data at the back of the vector. */
		Type& Back() {
			if (size == 0) {
				throw std::runtime_error("ERROR: The vector is empty!");
			}
			return data[size - 1];
		}

		/** Returns a constant reference to the data at the back of the vector. */
		const Type& Back() const {
			if (size == 0) {
				throw std::runtime_error("ERROR: The vector is empty!");
			}
			return data[size - 1];
		}

		/** Returns the index of the first matching value in the vector, or -1 if no match is found. */
		ptrdiff_t Find(const Type& Value) const {
			for (ptrdiff_t Index = 0; Index < static_cast<ptrdiff_t>(size); ++Index) {
				if (data[Index] == Value) {
					return Index;
				}
			}
			return -1;
		}

		/** Returns the index of the last matching value in the vector, or -1 if no match is found. */
		ptrdiff_t FindLast(const Type& Value) const {
			if (size == 0) {
				return -1;
			}
			for (ptrdiff_t Index = size - 1; Index >= 0; --Index) {
				if (data[Index] == Value) {
					return Index;
				}
			}
			return -1;
		}

		/** Returns whether the given value is present in the vector. */
		bool Contains(const Type& Value) const {
			return Find(Value) != -1;
		}

		/** Returns the total number of elements that match the given value in the vector. */
		size_t Total(const Type& Value) const {
			size_t Total = 0;
			for (size_t Index = 0; Index < size; ++Index) {
				if (data[Index] == Value) {
					++Total;
				}
			}
			return Total;
		}

		/** Returns whether the vector is sorted using Type's > operator. */
		bool IsSorted() const {
			return Sorting::IsSorted<Vector, Type>(size, *this);
		}

		/** Returns whether the vector is empty. */
		bool IsEmpty() const {
			return size == 0;
		}


		// SETTERS

		/** Sets the data at the given index with a copy of the given value. */
		void Set(const size_t Index, const Type& Value) {
			if (!IsValidIndex(Index)) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Index) +
					" is out of bounds of the vector of size " +
					std::to_string(size) + ".");
			}
			data[Index] = Value;
		}

		/** Swaps the given elements at the given indicies. */
		void Swap(const size_t Left, const size_t Right) {
			if (!IsValidIndex(Left)) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Left) +
					" is out of bounds of the vector of size " +
					std::to_string(size) + ".");
			}
			if (!IsValidIndex(Right)) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Right) +
					" is out of bounds of the vector of size " +
					std::to_string(size) + ".");
			}
			const Type Swapped = data[Left];
			data[Left] = data[Right];
			data[Right] = Swapped;
		}

		/** Fills the vector with a copy of the given value. */
		void Fill(const Type& Value) {
			for (size_t Index = 0; Index < size; ++Index) {
				data[Index] = Value;
			}
		}

		/** Bubble sorts the vector using Type's > operator. */
		void BubbleSort() {
			Sorting::BubbleSort<Vector, Type>(size, *this);
		}

		/** Merge sorts the vector using Type's > operator. */
		void MergeSort() {
			Sorting::MergeSort<Vector, Type>(size, *this);
		}

		/** Quick sorts the vector using Type's > operator. */
		void QuickSort() {
			Sorting::QuickSort<Vector, Type>(size, *this);
		}

		/** Reverses the vector. */
		void Reverse() {
			for (size_t Index = 0; Index < size / 2; ++Index) {
				const Type Swapped = data[Index];
				data[Index] = data[size - Index - 1];
				data[size - Index - 1] = Swapped;
			}
		}

		/** Shuffles the vector. */
		void Shuffle() {
			for (size_t Index = 0; Index < size; ++Index) {
				const Type Swapped = data[Index];
				const size_t Random = std::rand() % size;
				data[Index] = data[Random];
				data[Random] = Swapped;
			}
		}


		// EXPANSION

		/**
		  * Relocates the vector to new memory to contain the given capacity.
		  * If NewCapacity is less than the current size, elements at and following NewCapacity are deleted.
		  */
		void Resize(const size_t NewCapacity) {
			if (capacity == NewCapacity) {
				return;
			}
			size = size < NewCapacity ? size : NewCapacity;
			capacity = NewCapacity;
			if (NewCapacity > 0) {
				Type* Array = new Type[NewCapacity];
				for (size_t Index = 0; Index < size; ++Index) {
					Array[Index] = data[Index];
				}
				for (size_t Index = size; Index < capacity; ++Index) {
					Array[Index] = Type();
				}
				delete[] data;
				data = Array;
			}
			else {
				delete[] data;
				data = nullptr;
			}
		}

		/** Doubles the current capacity of the vector. */
		void Expand() {
			Resize(capacity > 0 ? capacity * 2 : 1);
		}

		/** Resizes the vector's capacity to its current size. */
		void Shrink() {
			Resize(size);
		}

		/** Sets the vector's size to zero. */
		void Clear() {
			size = 0;
		}

		/** Deallocates the vector. */
		void Reset() {
			size = 0;
			capacity = 0;
			delete[] data;
			data = nullptr;
		}

		/** Inserts a copy of the given data at the given index in the vector. */
		Type& Insert(const size_t Index, const Type& Value) {
			if (Index > size) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Index) +
					" is out of bounds of the vector of size " +
					std::to_string(size) + ".");
			}
			if (size + 1 > capacity) {
				Expand();
			}
			++size;
			for (size_t Current = size - 1; Current > Index; --Current) {
				data[Current] = data[Current - 1];
			}
			return data[Index] = Value;
		}

		/** Pushes a copy of the given data to the front of the vector. */
		Type& PushFront(const Type& Value) {
			return Insert(0, Value);
		}

		/** Pushes a copy of the given data to the back of the vector. */
		Type& PushBack(const Type& Value) {
			return Insert(size, Value);
		}

		/** Inserts a new element with the given arguments at the given index in the vector. */
		template<typename... ArgumentTypes>
		Type& Emplace(const size_t Index, ArgumentTypes&&... Arguments) {
			if (Index > size) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Index) +
					" is out of bounds of the vector of size " +
					std::to_string(size) + ".");
			}
			if (size + 1 > capacity) {
				Expand();
			}
			++size;
			for (size_t Current = size - 1; Current > Index; --Current) {
				data[Current] = data[Current - 1];
			}
			return data[Index] = Type(Arguments...);
		}

		/** Pushes a new element with the given arguments to the front of the vector. */
		template<typename... ArgumentTypes>
		Type& EmplaceFront(ArgumentTypes&&... Arguments) {
			return Emplace(0, Arguments...);
		}

		/** Pushes a new element with the given arguments to the back of the vector. */
		template<typename... ArgumentTypes>
		Type& EmplaceBack(ArgumentTypes&&... Arguments) {
			return Emplace(size, Arguments...);
		}

		/** Removes the element at the given index. */
		void Erase(const size_t Index) {
			if (Index >= size) {
				throw std::runtime_error(
					std::string("ERROR: Index ") +
					std::to_string(Index) +
					" is out of bounds of the vector of size " +
					std::to_string(size) + ".");
			}
			for (size_t Current = Index; Current < size - 1; ++Current) {
				data[Current] = data[Current + 1];
			}
			--size;
		}

		/** Removes the element at the front of the vector. */
		void PopFront() {
			Erase(0);
		}

		/** Removes the element at the back of the vector. */
		void PopBack() {
			Erase(size - 1);
		}


		// TO STRING

		/** Returns the vector as a string. */
		std::string ToString(const bool ShowCapacity = false) const {
			std::string String = "{ ";
			for (size_t Index = 0; Index < size; ++Index) {
				String += std::to_string(data[Index]);
				String += (Index != (ShowCapacity ? capacity : size) - 1) ? ", " : " ";
			}
			if (ShowCapacity) {
				for (size_t Index = size; Index < capacity; ++Index) {
					String += "X";
					String += (Index != capacity - 1) ? ", " : " ";
				}
			}
			return String += "}";
		}
	};
}
