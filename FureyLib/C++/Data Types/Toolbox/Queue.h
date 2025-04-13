// .h
// Queue Type
// by Kyle Furey

#pragma once
#include "List.h"

/** A collection of useful collection types in C++. */
namespace Toolbox {

	// QUEUE

	/** Represents a first-in, first-out, double-ended queue of the given type. */
	template<typename Type>
	class Queue final {

		// DATA

		/** The underlying list managing this queue. */
		List<Type> data;

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

		/** Deallocates the queue. */
		void Clear() {
			data.Clear();
		}

		/** Pushes a copy of the given data to the front of the queue. */
		void Push(const Type& Value) {
			data.PushFront(Value);
		}

		/** Pushes a copy of the given data to the end of the queue. */
		void PushLast(const Type& Value) {
			data.PushBack(Value);
		}

		/** Pushes a new element with the given arguments to the front of the quue. */
		template<typename... ArgumentTypes>
		void Emplace(ArgumentTypes&&... Arguments) {
			data.EmplaceFront(Arguments...);
		}

		/** Pushes a new element with the given arguments to the end of the queue. */
		template<typename... ArgumentTypes>
		void EmplaceLast(ArgumentTypes&&... Arguments) {
			data.EmplaceBack(Arguments...);
		}

		/** Removes and returns the next element in the queue. */
		Type Pop() {
			if (data.IsEmpty()) {
				throw std::runtime_error("ERROR: The queue is empty!");
			}
			Type front = data.Front();
			data.PopFront();
			return front;
		}

		/** Removes and returns the last element in the queue. */
		Type PopLast() {
			if (data.IsEmpty()) {
				throw std::runtime_error("ERROR: The queue is empty!");
			}
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


		// AS LIST

		/** Returns a reference to this queue's underlying list. */
		List<Type>& AsList() {
			return data;
		}

		/** Returns a constant reference to this queue's underlying list. */
		const List<Type>& AsList() const {
			return data;
		}
	};
}
