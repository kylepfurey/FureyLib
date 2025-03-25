// .h
// Queue Type
// by Kyle Furey

#pragma once
#include "Vector.h"

/** A collection of useful collection types in C++. */
namespace Toolbox {

	// QUEUE

	/** Represents a first-in, first-out, double-ended queue of the given type. */
	template<typename Type>
	class Queue final {

		// DATA

		/** The underlying vector managing this queue. */
		Vector<Type> data;

	public:

		// CONSTRUCTORS AND DESTRUCTOR

		/** Default constructor. */
		Queue() : data() {}

		/** Fill constructor. */
		Queue(const size_t Size, const Type& Value = Type()) : data(Size, Value) {
		}

		/** Array constructor. */
		Queue(const size_t Size, const Type* Array) : data(Size, Array) {
		}

		/** Initializer list constructor. */
		Queue(const std::initializer_list<Type>& List) : data(List) {
		}


		// GETTERS

		/** Returns the number of elements in the queue. */
		size_t Size() const {
			return data.Size();
		}

		/** Returns the current maximum number of elements in the queue. */
		size_t Capacity() const {
			return data.Capacity();
		}

		/** Returns a constant reference to the next element in the queue. */
		const Type& Peek() const {
			if (data.IsEmpty()) {
				throw std::runtime_error("ERROR: The queue is empty!");
			}
			return data.Front();
		}

		/** Returns a constant reference to the last element in the queue. */
		const Type& PeekLast() const {
			if (data.IsEmpty()) {
				throw std::runtime_error("ERROR: The queue is empty!");
			}
			return data.Back();
		}

		/** Returns whether the given value is present in the queue. */
		bool Contains(const Type& Value) const {
			return data.Contains(Value);
		}

		/** Returns the total number of elements that match the given value in the queue. */
		size_t Total(const Type& Value) const {
			return data.Total(Value);
		}

		/** Returns whether the queue is empty. */
		bool IsEmpty() const {
			return data.IsEmpty();
		}


		// SETTERS

		/** Reverses the queue. */
		void Reverse() {
			data.Reverse();
		}


		// EXPANSION

		/** Sets the queue's size to zero. */
		void Clear() {
			data.Clear();
		}

		/** Deallocates the queue. */
		void Reset() {
			data.Reset();
		}

		/** Pushes a copy of the given data to the front of the queue. */
		Type& Push(const Type& Value) {
			return data.PushFront(Value);
		}

		/** Pushes a copy of the given data to the end of the queue. */
		Type& PushLast(const Type& Value) {
			return data.PushBack(Value);
		}

		/** Pushes a new element with the given arguments to the front of the quue. */
		template<typename... ArgumentTypes>
		Type& Emplace(ArgumentTypes&&... Arguments) {
			return data.EmplaceFront(Arguments...);
		}

		/** Pushes a new element with the given arguments to the end of the queue. */
		template<typename... ArgumentTypes>
		Type& EmplaceLast(ArgumentTypes&&... Arguments) {
			return data.EmplaceBack(Arguments...);
		}

		/** Removes and returns the next element in the queue. */
		Type Pop() {
			Type front = data.Front();
			data.PopFront();
			return front;
		}

		/** Removes and returns the last element in the queue. */
		Type PopLast() {
			Type back = data.Back();
			data.PopBack();
			return back;
		}


		// TO STRING

		/** Returns the queue as a string. */
		std::string ToString() const {
			std::string String;
			for (size_t Index = 0; Index < data.Size(); ++Index) {
				String += "{ " + std::to_string(data[Index]) + " } -> ";
			}
			if (!String.empty()) {
				String.erase(String.length() - 4, 4);
			}
			else {
				return "{ }";
			}
			return String;
		}


		// AS VECTOR

		/** Returns a reference to this queue's underlying vector. */
		Vector<Type>& AsVector() {
			return data;
		}

		/** Returns a constant reference to this queue's underlying vector. */
		const Vector<Type>& AsVector() const {
			return data;
		}
	};
}
