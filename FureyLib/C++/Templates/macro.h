
// Template Macro Library Script
// by Kyle Furey

#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>

// Include this heading to use the library
#include "macro.h"

// Example macro (use '\' to include the next line)
#define MACRO std::cout << "Macro inserted!" << std::endl;

// Values assigned to pointers with no memory address.
#define null nullptr

// Implicitly-typed local variable.
#define var auto

// Iterates through each element of a collection.
#define foreach(expression) for(expression)

// Gets and stores a value from the following collection to the previous variable.
#define in :

// •  Repeats the following block of code for the given number of times.
// •  You can get the current iteration with the "iteration" variable.
#define do(n) for (int iteration = 0; iteration < n; iteration++)
