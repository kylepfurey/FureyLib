
// Template Static Function Library Script
// by Kyle Furey

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>

// Include this heading to use the library
#include "Function.h"

// Example function
static void function()
{
	std::cout << "Function called!" << std::endl;
}

// Prints a message to the console
template <class DataType> static void print(DataType message)
{
	std::cout << message << std::endl;
}

// Prints messages to the console
template <class DataType> static void print(int number_of_elements, DataType messages...)
{
	va_list list;

	va_start(list, 1);

	for (int i = 0; i < number_of_elements; i++)
	{
		std::cout << va_arg(list, DataType) << " ";
	}

	va_end(list);

	std::cout << std::endl;
}
