// .h
// Name
// Creator

#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>

/** Template class script. */
class my_class {

	// VARIABLES

	// New variables here

public:

	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor. */
	my_class();

	/** Copy constructor. */
	my_class(const my_class& copied);

	/** Move constructor. */
	my_class(my_class&& moved) noexcept;

	// New constructors here

	/** Destructor. */
	virtual ~my_class();


	// OPERATORS

	/** Copy assignment operator. */
	my_class& operator=(const my_class& copied);

	/** Move assignment operator. */
	my_class& operator=(my_class&& moved) noexcept;

	// New operators here


	// METHODS

	// New methods here
};
