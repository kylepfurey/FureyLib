// .h
// Name
// Creator

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


// STRUCTURE

/** Template structure script. */
typedef struct {
	// VARIABLES

	/** Example x variable. */
	float x;

	/** Example y variable. */
	float y;

	// New variables here
} my_struct;


// CONSTRUCTORS AND DESTRUCTOR

/** Initializes a new structure. */
my_struct my_struct_new(const float x, const float y);

// New constructors here

/** Properly destroys the given structure. */
void my_struct_free(my_struct *self);


// FUNCTIONS

/** Returns the magnitude of the given structure. */
float my_struct_magnitude(const my_struct *self);

/** Normalizes the given structure. */
my_struct *my_struct_normalize(my_struct *self);

// New functions here
