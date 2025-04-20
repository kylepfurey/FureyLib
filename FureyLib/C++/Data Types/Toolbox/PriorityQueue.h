// .h
// Priority Queue Type
// by Kyle Furey

#pragma once
#include "Queue.h"

/** A collection of useful template types in C++. */
namespace Toolbox {

	// PRIORITY QUEUE

	/** Represents a first-in, first-out queue where elements are given a priority to be sorted with. */
	template<typename Type, typename PriorityType = double>
	class PriorityQueue final {

		// NODE

		/** Represents an element's data and its priority in the queue. */
		struct Node final {
		private:

			// DATA

			/** The data of this node. */
			Type data;

			/** The priority value of this node. */
			PriorityType priority;

		public:

			// CONSTRUCTOR

			/** Default constructor. */
			Node(const Type Data = Type(), const PriorityType Priority = 0) : data(Data), priority(Priority) {
			}


			// GETTERS

			/** Returns a constant reference to the data of this node. */
			const Type& Data() const {
				return data;
			}

			/** Returns the priority of this node. */
			PriorityType Priority() const {
				return priority;
			}
		};


		// DATA

		/** The underlying queue managing this priority queue. */
		Queue<Node> queue;

	public:

		// CONSTRUCTOR

		/** Default constructor. */
		PriorityQueue() : queue() {}


		// GETTERS

		/** Returns the number of elements in the queue. */
		size_t Size() const {
			return queue.Size();
		}

		/** Returns a constant reference to the next element in the queue. */
		const Type& Peek() const {
			return queue.Peek().Data();
		}

		/** Returns a constant reference to the last element in the queue. */
		const Type& PeekLast() const {
			return queue.PeekLast().Data();
		}

		/** Returns the current lowest priority value in the queue (the closest to being popped). */
		PriorityType LowestPriority() const {
			return queue.Peek().Priority();
		}

		/** Returns the current highest priority value in the queue (the furthest from being popped). */
		PriorityType HighestPriority() const {
			return queue.PeekLast().Priority();
		}

		/** Returns whether the queue is empty. */
		bool IsEmpty() const {
			return queue.IsEmpty();
		}


		// EXPANSION

		/** Deallocates the queue. */
		void Clear() {
			queue.Clear();
		}

		/** Pushes a copy of the given data to the queue relative to its priority value. */
		void Push(const Type& Value, const PriorityType Priority) {
			Node NewNode(Value, Priority);
			size_t Index = 0;
			for (auto& Node : queue.AsList()) {
				if (Priority < Node.Priority()) {
					break;
				}
				++Index;
			}
			queue.AsList().Insert(Index, NewNode);
		}

		/** Removes and returns the element with the lowest priority in the queue. */
		Type Pop() {
			if (queue.IsEmpty()) {
				throw std::runtime_error("ERROR: The priority queue is empty!");
			}
			return queue.Pop().Data();
		}

		/** Removes and returns the element with the highest priority in the queue. */
		Type PopLast() {
			if (queue.IsEmpty()) {
				throw std::runtime_error("ERROR: The priority queue is empty!");
			}
			return queue.PopLast().Data();
		}


		// TO STRING

		/** Returns the queue as a string. */
		std::string ToString() const {
			std::string String;
			for (size_t Index = 0; Index < queue.Size(); ++Index) {
				String += "{ " + std::to_string(queue.AsList()[Index].Data()) + " : " + std::to_string(queue.AsList()[Index].Priority()) + " } -> ";
			}
			if (!String.empty()) {
				String.erase(String.length() - 4, 4);
			}
			else {
				return "{ }";
			}
			return String;
		}


		// AS QUEUE

		/** Returns a reference to this priority queue's underlying queue. */
		Queue<Node>& AsQueue() {
			return queue;
		}

		/** Returns a constant reference to this priority queue's underlying queue. */
		const Queue<Node>& AsQueue() const {
			return queue;
		}
	};
}
