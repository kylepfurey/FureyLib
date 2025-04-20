// .h
// Unique Smart Pointer Type
// by Kyle Furey

#pragma once
#include <exception>

/** A collection of useful template types in C++. */
namespace Toolbox {

	// DELETION

	/** Deletes the given pointer. */
	template <typename Type>
	static void Delete(Type* Data) {
		delete Data;
	}

	/** Deletes the given array pointer. */
	template <typename Type>
	static void DeleteArray(Type* Data) {
		delete[] Data;
	}


	// UNIQUE POINTER

	/** A wrapper for a pointer that automatically manages its memory without shared usage. */
	template<typename Type, void(*DELETE_FUNC)(Type*) = Delete>
	class Unique final {
		static_assert(DELETE_FUNC != nullptr, "ERROR: Cannot pass a null function as a template parameter!");

		// DATA

		/** The underlying pointer this unique pointer manages. */
		Type* data;

	public:

		// CONSTRUCTORS AND DESTRUCTOR

		/** Default constructor. */
		Unique() : data(nullptr) {
		}

		/** Pointer constructor. */
		Unique(Type* Data) : data(Data) {
		}

		/** Delete copy constructor. */
		Unique(const Unique&) = delete;

		/** Move constructor. */
		Unique(Unique&& Moved) noexcept : data(Moved.data) {
			Moved.data = nullptr;
		}

		/** Destructor. */
		~Unique() {
			DELETE_FUNC(data);
			data = nullptr;
		}


		// OPERATORS

		/** Pointer assignment operator. */
		Unique& operator=(Type* Data) {
			if (data == Data) {
				return *this;
			}
			DELETE_FUNC(data);
			data = Data;
			return *this;
		}

		/** Delete copy assignment operator. */
		Unique& operator=(const Unique&) = delete;

		/** Move assignment operator. */
		Unique& operator=(Unique&& Moved) noexcept {
			if (data == Moved.data) {
				return *this;
			}
			DELETE_FUNC(data);
			data = Moved.data;
			Moved.data = nullptr;
			return *this;
		}

		/** Null assignment operator. */
		Unique& operator=(std::nullptr_t) {
			DELETE_FUNC(data);
			data = nullptr;
			return *this;
		}

		/** Equality operator. */
		bool operator==(const Unique& Other) const {
			return data == Other.data;
		}

		/** Inequality operator. */
		bool operator!=(const Unique& Other) const {
			return !(*this == Other);
		}

		/** Dereference operator. */
		Type& operator*() {
			if (!IsValid()) {
				throw std::runtime_error("ERROR: Dereferencing a null pointer!");
			}
			return *data;
		}

		/** Constant dereference operator. */
		const Type& operator*() const {
			if (!IsValid()) {
				throw std::runtime_error("ERROR: Dereferencing a null pointer!");
			}
			return *data;
		}

		/** Arrow operator. */
		Type* operator->() {
			if (!IsValid()) {
				throw std::runtime_error("ERROR: Dereferencing a null pointer!");
			}
			return data;
		}

		/** Constant arrow operator. */
		const Type* operator->() const {
			if (!IsValid()) {
				throw std::runtime_error("ERROR: Dereferencing a null pointer!");
			}
			return data;
		}

		/** Array operator. */
		Type& operator[](const size_t Index) {
			static_assert(DELETE_FUNC == DeleteArray, "ERROR: Cannot use array operator on non-array pointers!");
			if (!IsValid()) {
				throw std::runtime_error("ERROR: Dereferencing a null pointer!");
			}
			return data[Index];
		}

		/** Constant array operator. */
		const Type& operator[](const size_t Index) const {
			static_assert(DELETE_FUNC == DeleteArray, "ERROR: Cannot use array operator on non-array pointers!");
			if (!IsValid()) {
				throw std::runtime_error("ERROR: Dereferencing a null pointer!");
			}
			return data[Index];
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
			return data;
		}

		/** Constant pointer operator. */
		operator const Type* () const {
			return data;
		}


		// GETTERS

		/** Returns the function used to delete memory. */
		void(*DeleteFunction() const)(Type*) {
			return DELETE_FUNC;
		}

		/** Returns a copy of the raw pointer of this unique pointer. */
		Type* Raw() {
			return data;
		}

		/** Returns a constant copy of the raw pointer of this unique pointer. */
		const Type* Raw() const {
			return data;
		}

		/** Returns whether this unique pointer is not null. */
		bool IsValid() const {
			return data != nullptr;
		}


		// SETTERS

		/** Swaps this unique pointer's memory with the given unique pointer's memory. */
		void Swap(Unique& Other) {
			Type* Data = data;
			data = Other.data;
			Other.data = Data;
		}

		/** Deletes this unique pointer's memory. */
		bool Delete() {
			if (IsValid()) {
				DELETE_FUNC(data);
				data = nullptr;
				return true;
			}
			return false;
		}

		/** Safely replaces this unique pointer's memory with the given pointer. */
		void Replace(Type* Data) {
			if (data != Data) {
				DELETE_FUNC(data);
				data = Data;
			}
		}

		/**
		 * Releases this unique pointer's memory as a raw pointer.<br/>
		 * NOTE: The pointer must still be deleted!
		 */
		Type* Release() {
			Type* Data = data;
			data = nullptr;
			return Data;
		}
	};


	// UNIQUE ARRAY POINTER

	/** A wrapper for an array pointer that automatically manages its memory without shared usage. */
	template <typename Type>
	using UniqueArray = Unique<Type, DeleteArray>;
}
