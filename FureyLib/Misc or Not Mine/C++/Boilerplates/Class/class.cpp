// .cpp
// Name
// Creator

#include "class.h"


// CONSTRUCTORS AND DESTRUCTOR

// Default constructor.
my_class::my_class() {

}

// Copy constructor.
my_class::my_class(const my_class& copied) {

}

// Move constructor.
my_class::my_class(my_class&& moved) noexcept {

}

// New constructors here

// Destructor.
my_class::~my_class() {

}


// OPERATORS

// Copy assignment operator.
my_class& my_class::operator=(const my_class& copied) {
	if (this == &copied) {
		return *this;
	}
	return *this;
}

// Move assignment operator.
my_class& my_class::operator=(my_class&& moved) noexcept {
	if (this == &moved) {
		return *this;
	}
	return *this;
}

// New operators here


// METHODS

// New methods here
