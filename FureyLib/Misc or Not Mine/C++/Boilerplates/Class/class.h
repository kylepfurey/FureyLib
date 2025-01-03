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
protected:

	// VARIABLES

	// New variables here

public:

	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor. */
	my_class();

	// New constructors here

	/** Delete copy constructor. */
	my_class(const my_class& copied) = delete;

	/** Delete move constructor. */
	my_class(my_class&& moved) = delete;

	/** Delete copy assignment operator. */
	my_class& operator=(const my_class& copied) = delete;

	/** Delete move assignment operator. */
	my_class& operator=(my_class&& moved) = delete;

	/** Destructor. */
	virtual ~my_class();


	// FUNCTIONS

	// New functions here
};
