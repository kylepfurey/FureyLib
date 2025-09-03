// .h
// Singleton Base Class
// by Kyle Furey

#pragma once


// SINGLETON

/** Allows a derived class to have a single global instance via T::instance(). */
template<typename T>
class singleton {
public:

	// METHODS

	/** Returns the singleton instance of this class. */
	static T& instance() {
		static T instance;
		return instance;
	}
};
