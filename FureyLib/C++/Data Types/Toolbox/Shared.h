// .h
// Shared Smart Pointer Type
// by Kyle Furey

#pragma once
#include "Unique.h"

/** A collection of useful template types in C++. */
namespace Toolbox {

	// WEAK POINTER

	/** A wrapper for a pointer that can read from other smart pointers' memory without owning it. */
	template<typename Type, void(*DELETE_FUNC)(Type*)>
	class Weak;


	// SHARED POINTER

	/** A wrapper for a pointer that automatically manages its memory and tracks new references to it. */
	template<typename Type, void(*DELETE_FUNC)(Type*) = Delete>
	class Shared final {
		static_assert(DELETE_FUNC != nullptr, "ERROR: Cannot pass a null function as a template parameter!");

		// FRIENDS

		friend class Weak<Type, DELETE_FUNC>;

	public:

		// WEAK POINTER

		/** A wrapper for a pointer that can read from other smart pointers' memory without owning it. */
		using Weak = Weak<Type, DELETE_FUNC>;


		// NODE

		/** A shared region of memory that tracks references to it. */
		struct Node final {
		private:

			// DATA

			/** The underlying pointer this node manages. */
			Type* data;

			/** The current total number of shared pointers pointing to this node. */
			size_t shared;

			/** The current total number of weak pointers pointing to this node. */
			size_t weak;

		public:

			// CONSTRUCTOR

			/** Default constructor. */
			Node(Type* Data = nullptr) : data(Data), shared(0), weak(0) {
			}


			// GETTERS

			/** Returns a copy of the underlying raw pointer. */
			Type* Data() {
				return data;
			}

			/** Returns a constant copy of the underlying raw pointer. */
			const Type* Data() const {
				return data;
			}

			/** Returns the total number of shared pointers pointing to this node. */
			size_t SharedCount() const {
				return shared;
			}

			/** Returns the total number of weak pointers pointing to this node. */
			size_t WeakCount() const {
				return weak;
			}

			/** Returns whether this node's memory is still valid has not been freed yet. */
			bool IsValid() const {
				return data != nullptr;
			}


			// SETTERS

			/** Deletes this node's memory. */
			bool Delete() {
				if (data != nullptr) {
					DELETE_FUNC(data);
					data = nullptr;
					return true;
				}
				return false;
			}

			/** Safely replaces this node's memory with the given pointer. */
			void Replace(Type* Data) {
				if (data != Data) {
					DELETE_FUNC(data);
					data = Data;
				}
			}

			/**
			 * Releases this node's memory as a raw pointer.<br/>
			 * NOTE: The pointer must still be deleted!
			 */
			Type* Release() {
				Type* Data = data;
				data = nullptr;
				return Data;
			}


			// MEMORY MANAGEMENT

			/** Increments the total number of shared pointers. */
			void IncrementShared() {
				++shared;
			}

			/** Decrements the total number of shared pointers, freeing the memory if 0 remain. */
			void DecrementShared() {
				if (shared > 0) {
					--shared;
					if (shared == 0) {
						DELETE_FUNC(data);
						data = nullptr;
						if (weak == 0) {
							delete this;
						}
					}
				}
			}

			/** Increments the total number of weak pointers. */
			void IncrementWeak() {
				++weak;
			}

			/** Decrements the total number of weak pointers, freeing the memory if 0 remain. */
			void DecrementWeak() {
				if (weak > 0) {
					--weak;
					if (shared == 0 && weak == 0) {
						delete this;
					}
				}
			}
		};

	private:

		// DATA

		/** The underlying pointer to the memory node this shared pointer manages. */
		Node* node;

	public:

		// CONSTRUCTORS AND DESTRUCTOR

		/** Default constructor. */
		Shared() : node(nullptr) {
		}

		/** Pointer constructor. */
		Shared(Type* Data) : node() {
			if (Data != nullptr) {
				node = new Node(Data);
				node->IncrementShared();
			}
		}

		/** Weak pointer constructor. */
		Shared(Weak& Data) : node(Data.node) {
			if (node != nullptr) {
				node->IncrementShared();
			}
		}

		/** Node constructor. */
		Shared(Node* Node) : node(Node) {
			if (node != nullptr) {
				node->IncrementShared();
			}
		}

		/** Copy constructor. */
		Shared(const Shared& Copied) : node(Copied.node) {
			if (node != nullptr) {
				node->IncrementShared();
			}
		}

		/** Move constructor. */
		Shared(Shared&& Moved) noexcept : node(Moved.node) {
			Moved.node = nullptr;
		}

		/** Destructor. */
		~Shared() {
			if (node != nullptr) {
				node->DecrementShared();
			}
		}


		// OPERATORS

		/** Pointer assignment operator. */
		Shared& operator=(Type* Data) {
			if (node != nullptr) {
				if (node->Data() == Data) {
					return *this;
				}
				node->DecrementShared();
			}
			node = new Node(Data);
			node->IncrementShared();
			return *this;
		}

		/** Weak pointer assignment operator. */
		Shared& operator=(Weak& Data) {
			if (node != nullptr) {
				if (node == Data.node) {
					return *this;
				}
				node->DecrementShared();
			}
			node = Data.node;
			if (node != nullptr) {
				node->IncrementShared();
			}
			return *this;
		}

		/** Node assignment operator. */
		Shared& operator=(Node* Node) {
			if (node == Node) {
				return *this;
			}
			if (node != nullptr) {
				node->DecrementShared();
			}
			node = Node;
			if (node != nullptr) {
				node->IncrementShared();
			}
			return *this;
		}

		/** Copy assignment operator. */
		Shared& operator=(const Shared& Copied) {
			if (node == Copied.node) {
				return *this;
			}
			if (node != nullptr) {
				node->DecrementShared();
			}
			node = Copied.node;
			if (node != nullptr) {
				node->IncrementShared();
			}
			return *this;
		}

		/** Move assignment operator. */
		Shared& operator=(Shared&& Moved) noexcept {
			if (node == Moved.node) {
				return *this;
			}
			if (node != nullptr) {
				node->DecrementShared();
			}
			node = Moved.node;
			Moved.node = nullptr;
			return *this;
		}

		/** Null assignment operator. */
		Shared& operator=(std::nullptr_t) {
			if (node != nullptr) {
				node->DecrementShared();
			}
			node = nullptr;
			return *this;
		}

		/** Equality operator. */
		bool operator==(const Shared& Other) const {
			return node == Other.node;
		}

		/** Inequality operator. */
		bool operator!=(const Shared& Other) const {
			return !(*this == Other);
		}

		/** Weak pointer equality operator. */
		bool operator==(const Weak& Other) const {
			return node == Other.node;
		}

		/** Weak pointer inequality operator. */
		bool operator!=(const Weak& Other) const {
			return !(*this == Other);
		}

		/** Dereference operator. */
		Type& operator*() {
			if (!IsValid()) {
				throw std::runtime_error("ERROR: Dereferencing a null pointer!");
			}
			return *node->Data();
		}

		/** Constant dereference operator. */
		const Type& operator*() const {
			if (!IsValid()) {
				throw std::runtime_error("ERROR: Dereferencing a null pointer!");
			}
			return *node->Data();
		}

		/** Arrow operator. */
		Type* operator->() {
			if (!IsValid()) {
				throw std::runtime_error("ERROR: Dereferencing a null pointer!");
			}
			return node->Data();
		}

		/** Constant arrow operator. */
		const Type* operator->() const {
			if (!IsValid()) {
				throw std::runtime_error("ERROR: Dereferencing a null pointer!");
			}
			return node->Data();
		}

		/** Array operator. */
		Type& operator[](const size_t Index) {
			static_assert(DELETE_FUNC == DeleteArray, "ERROR: Cannot use array operator on non-array pointers!");
			if (!IsValid()) {
				throw std::runtime_error("ERROR: Dereferencing a null pointer!");
			}
			return node->Data()[Index];
		}

		/** Constant array operator. */
		const Type& operator[](const size_t Index) const {
			static_assert(DELETE_FUNC == DeleteArray, "ERROR: Cannot use array operator on non-array pointers!");
			if (!IsValid()) {
				throw std::runtime_error("ERROR: Dereferencing a null pointer!");
			}
			return node->Data()[Index];
		}

		/** Not null check operator. */
		operator bool() const {
			return IsValid();
		}

		/** Null check operator. */
		bool operator!() const {
			return !IsValid();
		}

		/** Pointer operator. */
		operator Type* () {
			return node != nullptr ? node->Data() : nullptr;
		}

		/** Constant pointer operator. */
		operator const Type* () const {
			return node != nullptr ? node->Data() : nullptr;
		}

		/** Weak pointer operator. */
		operator Weak() {
			return Weak(node);
		}

		/** Constant weak pointer operator. */
		operator const Weak() const {
			return Weak(node);
		}


		// GETTERS

		/** Returns the function used to delete memory. */
		void(*DeleteFunction() const)(Type*) {
			return DELETE_FUNC;
		}

		/** Returns a copy of the raw pointer of this shared pointer. */
		Type* Raw() {
			return node != nullptr ? node->Data() : nullptr;
		}

		/** Returns a constant copy of the raw pointer of this shared pointer. */
		const Type* Raw() const {
			return node != nullptr ? node->Data() : nullptr;
		}

		/** Returns a weak pointer to this shared pointer's shared memory. */
		Weak MakeWeak() {
			return Weak(node);
		}

		/** Returns a constant weak pointer to this shared pointer's shared memory. */
		const Weak MakeWeak() const {
			return Weak(node);
		}

		/** Returns the total number of shared pointers referencing this shared pointer's shared memory. */
		size_t SharedCount() const {
			return node != nullptr ? node->SharedCount() : 0;
		}

		/** Returns the total number of weak pointers referencing this shared pointer's shared memory. */
		size_t WeakCount() const {
			return node != nullptr ? node->WeakCount() : 0;
		}

		/** Returns the total number of pointers referencing this shared pointer's shared memory. */
		size_t Total() const {
			return node != nullptr ? node->SharedCount() + node->WeakCount() : 0;
		}

		/** Returns whether this shared pointer is not null. */
		bool IsValid() const {
			return node != nullptr && node->IsValid();
		}


		// SETTERS

		/** Swaps this shared pointer's memory with the given shared pointer's memory. */
		void Swap(Shared& Other) {
			Node* Node = node;
			node = Other.node;
			Other.node = Node;
		}

		/** Swaps this shared pointer's memory with the given weak pointer's memory. */
		void Swap(Weak& Other) {
			Node* Node = node;
			node = Other.node;
			Other.node = Node;
		}

		/** Deletes this shared pointer's shared memory. */
		bool Delete() {
			if (node == nullptr) {
				return false;
			}
			return node->Delete();
		}

		/** Safely replaces this shared pointer's shared memory with the given pointer. */
		void Replace(Type* Data) {
			if (node != nullptr) {
				node->Replace(Data);
			}
		}

		/**
		 * Releases this shared pointer's shared memory as a raw pointer.<br/>
		 * NOTE: The pointer must still be deleted!
		 */
		Type* Release() {
			if (node == nullptr) {
				return nullptr;
			}
			return node->Release();
		}

		/** Clears this shared pointer's reference its shared memory. */
		bool Clear() {
			if (node == nullptr) {
				return false;
			}
			node->DecrementShared();
			node = nullptr;
			return true;
		}

		/** Resets this shared pointer to a new pointer. */
		void Reset(Type* Data) {
			if (node != nullptr) {
				if (node->Data() == Data) {
					return;
				}
				node->DecrementShared();
			}
			node = new Node(Data);
			node->IncrementShared();
		}
	};


	// SHARED ARRAY POINTER

	/** A wrapper for an array pointer that automatically manages its memory and tracks new references to it. */
	template <typename Type>
	using SharedArray = Shared<Type, DeleteArray>;
}
