
// Static Select Statement Functions Script
// by Kyle Furey

#pragma once
#include <cstdarg> 

// Include this heading to use the library
#define "Select.h"

// Select from a boolean and return the chosen data
template <class DataType> static DataType select(bool condition, DataType trueData, DataType falseData)
{
	return condition ? trueData : falseData;
}

// Select from a integer and return the chosen data
template <class DataType> static DataType select(int n, DataType nData...)
{
	if (n == 0)
	{
		return nData;
	}

	va_list list;

	va_start(list, n);

	for (int i = 0; i < n - 1; i++)
	{
		va_arg(list, DataType);
	}

	DataType data = va_arg(list, DataType);

	va_end(list);

	return data;
}

// Select from a boolean and return the chosen data
template <class DataType> static DataType& selectref(bool condition, DataType& trueData, DataType& falseData)
{
	return condition ? trueData : falseData;
}

// Select from a integer and return the chosen data
template <class DataType> static DataType& selectref(int n, DataType& nData...)
{
	if (n == 0)
	{
		return nData;
	}

	va_list list;

	va_start(list, n);

	for (int i = 0; i < n - 1; i++)
	{
		va_arg(list, DataType);
	}

	DataType data = va_arg(list, DataType);

	va_end(list);

	return data;
}

// Compare two integers and return the chosen data
template <class DataType> static DataType greater_less_equal(int comparer, int compared, DataType greaterThanData, DataType lessThanData, DataType equalToData)
{
	if (comparer > compared)
	{
		return greaterThanData;
	}
	else if (comparer < compared)
	{
		return lessThanData;
	}
	else
	{
		return equalToData;
	}
}

// Compare two floats and return the chosen data
template <class DataType> static DataType greater_less_equal(float comparer, float compared, DataType greaterThanData, DataType lessThanData, DataType equalToData)
{
	if (comparer > compared)
	{
		return greaterThanData;
	}
	else if (comparer < compared)
	{
		return lessThanData;
	}
	else
	{
		return equalToData;
	}
}

// Compare two integers and return the chosen data
template <class DataType> static DataType& greater_less_equal_ref(int comparer, int compared, DataType& greaterThanData, DataType& lessThanData, DataType& equalToData)
{
	if (comparer > compared)
	{
		return greaterThanData;
	}
	else if (comparer < compared)
	{
		return lessThanData;
	}
	else
	{
		return equalToData;
	}
}

// Compare two floats and return the chosen data
template <class DataType> static DataType& greater_less_equal_ref(float comparer, float compared, DataType& greaterThanData, DataType& lessThanData, DataType& equalToData)
{
	if (comparer > compared)
	{
		return greaterThanData;
	}
	else if (comparer < compared)
	{
		return lessThanData;
	}
	else
	{
		return equalToData;
	}
}
