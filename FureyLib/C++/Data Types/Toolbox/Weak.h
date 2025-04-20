// .h
// Weak Smart Pointer Type
// by Kyle Furey

#pragma once
#include "Shared.h"

/** A collection of useful template types in C++. */
namespace Toolbox {

	// WEAK POINTER

	/** A wrapper for a pointer that can read from other smart pointers' memory without owning it. */
	template<typename Type, void(*DELETE_FUNC)(Type*) = Delete>
	class Weak final {
		static_assert(DELETE_FUNC != nullptr, "ERROR: Cannot pass a null function as a template parameter!");

		// FRIENDS

		friend class Shared<Type, DELETE_FUNC>;

	public:

		// SHARED POINTER

		/** A wrapper for a pointer that automatically manages its memory and tracks new references to it. */
		using Shared = Shared<Type, DELETE_FUNC>;


		// NODE

		/** A shared region of memory that tracks references to it. */
		using Node = typename Shared::Node;

	private:

		// DATA

		/** The underlying pointer to the memory node this weak pointer manages. */
		Node* node;

	public:

		// CONSTRUCTORS AND DESTRUCTOR

		/** Default constructor. */
		Weak() : node(nullptr) {
		}

		/** Shared pointer constructor. */
		Weak(Shared& Data) : node(Data.node) {
			if (node != nullptr) {
				node->IncrementWeak();
			}
		}

		/** Node constructor. */
		Weak(Node* Node) : node(Node) {
			if (node != nullptr) {
				node->IncrementWeak();
			}
		}

		/** Copy constructor. */
		Weak(const Weak& Copied) : node(Copied.node) {
			if (node != nullptr) {
				node->IncrementWeak();
			}
		}

		/** Move constructor. */
		Weak(Weak&& Moved) noexcept : node(Moved.node) {
			Moved.node = nullptr;
		}

		/** Null constructor. */
		Weak(std::nullptr_t) : node(nullptr) {
		}

		/** Destructor. */
		~Weak() {
			if (node != nullptr) {
				node->DecrementWeak();
			}
		}


		// OPERATORS

		/** Shared pointer assignment operator. */
		Weak& operator=(Shared& Data) {
			if (node != nullptr) {
				if (node == Data.node) {
					return *this;
				}
				node->DecrementWeak();
			}
			node = Data.node;
			if (node != nullptr) {
				node->IncrementWeak();
			}
			return *this;
		}

		/** Node assignment operator. */
		Weak& operator=(Node* Node) {
			if (node == Node) {
				return *this;
			}
			if (node != nullptr) {
				node->DecrementWeak();
			}
			node = Node;
			if (node != nullptr) {
				node->IncrementWeak();
			}
			return *this;
		}

		/** Copy assignment operator. */
		Weak& operator=(const Weak& Copied) {
			if (node == Copied.node) {
				return *this;
			}
			if (node != nullptr) {
				node->DecrementWeak();
			}
			node = Copied.node;
			if (node != nullptr) {
				node->IncrementWeak();
			}
			return *this;
		}

		/** Move assignment operator. */
		Weak& operator=(Weak&& Moved) noexcept {
			if (node == Moved.node) {
				return *this;
			}
			if (node != nullptr) {
				node->DecrementWeak();
			}
			node = Moved.node;
			Moved.node = nullptr;
			return *this;
		}

		/** Null assignment operator. */
		Weak& operator=(std::nullptr_t) {
			if (node != nullptr) {
				node->DecrementWeak();
			}
			node = nullptr;
			return *this;
		}

		/** Equality operator. */
		bool operator==(const Weak& Other) const {
			return node == Other.node;
		}

		/** Inequality operator. */
		bool operator!=(const Weak& Other) const {
			return !(*this == Other);
		}

		/** Shared pointer equality operator. */
		bool operator==(const Weak& Other) const {
			return node == Other.node;
		}

		/** Shared pointer inequality operator. */
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
		Shared operator->() {
			if (!IsValid()) {
				throw std::runtime_error("ERROR: Dereferencing a null pointer!");
			}
			return Shared(node);
		}

		/** Constant arrow operator. */
		const Shared operator->() const {
			if (!IsValid()) {
				throw std::runtime_error("ERROR: Dereferencing a null pointer!");
			}
			return Shared(node);
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

		/** Shared pointer operator. */
		operator Shared() {
			return Shared(node);
		}

		/** Constant shared pointer operator. */
		operator const Shared() const {
			return Shared(node);
		}


		// GETTERS

		/** Returns the function used to delete memory. */
		void(*DeleteFunction() const)(Type*) {
			return DELETE_FUNC;
		}

		/** Returns a copy of the raw pointer of this weak pointer. */
		Type* Raw() {
			return node != nullptr ? node->Data() : nullptr;
		}

		/** Returns a constant copy of the raw pointer of this weak pointer. */
		const Type* Raw() const {
			return node != nullptr ? node->Data() : nullptr;
		}

		/** Upgrades this weak pointer to a shared pointer. */
		Shared MakeShared() {
			return Shared(node);
		}

		/** Upgrades this weak pointer to a constant shared pointer. */
		const Shared MakeShared() const {
			return Shared(node);
		}

		/** Returns the total number of shared pointers referencing this weak pointer's shared memory. */
		size_t SharedCount() const {
			return node != nullptr ? node->SharedCount() : 0;
		}

		/** Returns the total number of weak pointers referencing this weak pointer's shared memory. */
		size_t WeakCount() const {
			return node != nullptr ? node->WeakCount() : 0;
		}

		/** Returns the total number of pointers referencing this weak pointer's shared memory. */
		size_t Total() const {
			return node != nullptr ? node->SharedCount() + node->WeakCount() : 0;
		}

		/** Returns whether this weak pointer is not null. */
		bool IsValid() const {
			return node != nullptr && node->IsValid();
		}


		// SETTERS

		/** Swaps this weak pointer's memory with the given weak pointer's memory. */
		void Swap(Weak& Other) {
			Node* Node = node;
			node = Other.node;
			Other.node = Node;
		}

		/** Swaps this weak pointer's memory with the given shared pointer's memory. */
		void Swap(Shared& Other) {
			Node* Node = node;
			node = Other.node;
			Other.node = Node;
		}

		/** Deletes this weak pointer's shared memory. */
		bool Delete() {
			if (node == nullptr) {
				return false;
			}
			return node->Delete();
		}

		/** Safely replaces this weak pointer's shared memory with the given pointer. */
		void Replace(Type* Data) {
			if (node != nullptr) {
				node->Replace(Data);
			}
		}

		/**
		 * Releases this weak pointer's shared memory as a raw pointer.<br/>
		 * NOTE: The pointer must still be deleted!
		 */
		Type* Release() {
			if (node == nullptr) {
				return nullptr;
			}
			return node->Release();
		}

		/** Clears this weak pointer's reference its shared memory. */
		bool Clear() {
			if (node == nullptr) {
				return false;
			}
			node->DecrementWeak();
			node = nullptr;
			return true;
		}

		/** Resets this weak pointer to a new shared pointer. */
		void Reset(Shared& Data) {
			if (node != nullptr) {
				if (node->Data() == Data.node) {
					return;
				}
				node->DecrementWeak();
			}
			node = Data.node;
			if (node != nullptr) {
				node->IncrementWeak();
			}
		}
	};


	// WEAK ARRAY POINTER

	/** A wrapper for an array pointer that can read from other smart pointers' memory without owning it. */
	template <typename Type>
	using WeakArray = Weak<Type, DeleteArray>;
}
