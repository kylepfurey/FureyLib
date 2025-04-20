// .h
// Multicast Delegate Type
// by Kyle Furey

#pragma once
#include <utility>
#include "Vector.h"

// Whether delegates should throw an exception when invoked with a null function.
#define THROW_ON_NULL_INVOKE 1

/** A collection of useful template types in C++. */
namespace Toolbox {

	// FUNCTION

	/** Represents a pointer to a function with the given return type and argument types. */
	template <typename ReturnType, typename ... ArgumentTypes>
	using Function = ReturnType(*)(ArgumentTypes...);


	// MULTICAST DELEGATE

	/** A hook for multiple functions that can be bound, unbound, and invoked at once. */
	template<typename ReturnType, typename ... ArgumentTypes>
	class Delegate final {
	public:

		// FUNCTION

		/** Represents the function pointer type that fits within this delegate. */
		using Function = ReturnType(*)(ArgumentTypes...);

	private:

		// DATA

		/** The underlying array of bound functions to be invoked. */
		Vector<Function> bindings;

	public:

		// CONSTRUCTORS

		/** Default constructor. */
		Delegate(const size_t Capacity = 8) : bindings() {
			bindings.Resize(Capacity);
		}

		/** Function constructor. */
		Delegate(const Function Function) : bindings() {
			bindings.Resize(8);
			Bind(Function);
		}

		/** Initializer list constructor. */
		Delegate(const std::initializer_list<Function>& List) : bindings() {
			bindings.Resize(List.size());
			for (size_t Index = 0; Index < List.size(); ++Index) {
				Bind(*(List.begin() + Index));
			}
		}


		// OPERATORS

		/** Bind operator. */
		Delegate& operator+=(const Function Function) {
			Bind(Function);
			return *this;
		}

		/** Unbind operator. */
		Delegate& operator-=(const Function Function) {
			Unbind(Function);
			return *this;
		}

		/** Invoke operator. */
		Delegate& operator()(ArgumentTypes&&... Arguments) {
			Invoke(std::forward<ArgumentTypes>(Arguments)...);
			return *this;
		}

		/** Constant invoke operator. */
		const Delegate& operator()(ArgumentTypes&&... Arguments) const {
			Invoke(Arguments...);
			return *this;
		}


		// GETTERS

		/** Returns the current number of bound functions. */
		size_t Size() const {
			return bindings.Size();
		}

		/** Returns whether the given function is bound to this delegate. */
		bool IsBound(const Function Function) const {
			return bindings.Contains(Function);
		}

		/** Returns the total number of times the given function is bound to this delegate. */
		size_t Total(const Function Function) const {
			return bindings.Total(Function);
		}

		/** Returns whether the delegate has no bindings. */
		bool IsEmpty() const {
			return bindings.IsEmpty();
		}


		// BINDING

		/** Unbinds all functions from this delegate. */
		void UnbindAll() {
			bindings.Clear();
		}

		/** Unbinds the given function once from this delegate and returns whether it was successful. */
		bool Unbind(const Function Function) {
			const ptrdiff_t Index = bindings.Find(Function);
			if (Index == -1) {
				return false;
			}
			bindings.Erase(static_cast<size_t>(Index));
			return true;
		}

		/** Binds the given function to this delegate. */
		void Bind(const Function Function) {
			if (Function == nullptr) {
#if THROW_ON_NULL_INVOKE
				throw std::runtime_error("ERROR: Cannot bind a null function to a delegate!");
#endif
				return;
			}
			bindings.PushBack(Function);
		}

		/** Invokes each function bound to this delegate with the given arguments. */
		void Invoke(ArgumentTypes&&... Arguments) {
			for (auto Function : bindings) {
				if (Function == nullptr) {
#if THROW_ON_NULL_INVOKE
					throw std::runtime_error("ERROR: A delegate attempted to invoke a null function!");
#endif
					continue;
				}
				Function(std::forward<ArgumentTypes>(Arguments)...);
			}
		}

		/** Invokes each function bound to this delegate with the given constant arguments. */
		void Invoke(ArgumentTypes&&... Arguments) const {
			for (auto Function : bindings) {
				if (Function == nullptr) {
#if THROW_ON_NULL_INVOKE
					throw std::runtime_error("ERROR: A delegate attempted to invoke a null function!");
#endif
					continue;
				}
				Function(std::forward<ArgumentTypes>(Arguments)...);
			}
		}


		// AS VECTOR

		/** Returns a reference to this delegate as a vector. */
		Vector<Function>& AsVector() {
			return bindings;
		}

		/** Returns a constant reference to this delegate as a vector. */
		const Vector<Function>& AsVector() const {
			return bindings;
		}
	};


	// MULTICAST EVENT TYPE

	/** A hook for multiple void-returning functions that can be bound, unbound, and invoked at once. */
	template<typename ... ArgumentTypes>
	using Event = Delegate<void, ArgumentTypes...>;
}
