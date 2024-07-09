
// Static Print Functions Script
// by Kyle Furey

#pragma once
#include <iostream>
#include <string>
#include <cstdarg>

// Include this heading to use the library
#include "print.h"

// Prints a message to the console
#define PRINT(log) std::cout << (log) << std::endl;

// Prints a message to the console
template <typename data_type> static void print(data_type message)
{
	std::cout << message << std::endl;
}

// Prints messages to the console
template <typename data_type> static void print(int number_of_elements, data_type messages...)
{
	va_list list;

	va_start(list, number_of_elements);

	for (int i = 0; i < number_of_elements; i++)
	{
		std::cout << messages << " ";

		messages = va_arg(list, data_type);
	}

	va_end(list);

	std::cout << std::endl;
}
