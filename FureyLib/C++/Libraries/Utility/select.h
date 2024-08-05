
// Static Select Statement Functions Script
// by Kyle Furey

#pragma once
#include <cstdarg> 

// Include this heading to use the library
#define "select.h"

// Select from a boolean and return the chosen data
template <typename data_type> static data_type select(bool condition, data_type true_data, data_type false_data)
{
	return condition ? true_data : false_data;
}

// Select from a integer and return the chosen data
template <typename data_type> static data_type select(int n, data_type n_data...)
{
	if (n == 0)
	{
		return n_data;
	}

	va_list list;

	va_start(list, n);

	for (int i = 0; i < n - 1; i++)
	{
		va_arg(list, data_type);
	}

	data_type data = va_arg(list, data_type);

	va_end(list);

	return data;
}

// Select from a boolean and return the chosen data
template <typename data_type> static data_type& selectref(bool condition, data_type& true_data, data_type& false_data)
{
	return condition ? true_data : false_data;
}

// Select from a integer and return the chosen data
template <typename data_type> static data_type& selectref(int n, data_type& n_data...)
{
	if (n == 0)
	{
		return n_data;
	}

	va_list list;

	va_start(list, n);

	for (int i = 0; i < n - 1; i++)
	{
		va_arg(list, data_type);
	}

	data_type data = va_arg(list, data_type);

	va_end(list);

	return data;
}

// Compare two integers and return the chosen data
template <typename data_type> static data_type greater_less_equal(int comparer, int compared, data_type greater_than_data, data_type less_than_data, data_type equal_to_data)
{
	if (comparer > compared)
	{
		return greater_than_data;
	}
	else if (comparer < compared)
	{
		return less_than_data;
	}
	else
	{
		return equal_to_data;
	}
}

// Compare two floats and return the chosen data
template <typename data_type> static data_type greater_less_equal(float comparer, float compared, data_type greater_than_data, data_type less_than_data, data_type equal_to_data)
{
	if (comparer > compared)
	{
		return greater_than_data;
	}
	else if (comparer < compared)
	{
		return less_than_data;
	}
	else
	{
		return equal_to_data;
	}
}

// Compare two integers and return the chosen data
template <typename data_type> static data_type& greater_less_equal_ref(int comparer, int compared, data_type& greater_than_data, data_type& less_than_data, data_type& equal_to_data)
{
	if (comparer > compared)
	{
		return greater_than_data;
	}
	else if (comparer < compared)
	{
		return less_than_data;
	}
	else
	{
		return equal_to_data;
	}
}

// Compare two floats and return the chosen data
template <typename data_type> static data_type& greater_less_equal_ref(float comparer, float compared, data_type& greater_than_data, data_type& less_than_data, data_type& equal_to_data)
{
	if (comparer > compared)
	{
		return greater_than_data;
	}
	else if (comparer < compared)
	{
		return less_than_data;
	}
	else
	{
		return equal_to_data;
	}
}
