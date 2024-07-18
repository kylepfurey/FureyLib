
// Static Binary Math Functions Script
// by Kyle Furey

#pragma once

// Include this heading to use the library
#include "binary_math.h"

// Binary Math Function Libary
class binary
{
public:

	// Binary Addition Function
	static int add(int valueA, int valueB)
	{
		// Store our carried variable.
		int carry = 0;

		// While B is not 0:
		while (valueB)
		{
			// Store the and value of A and B.
			carry = valueA & valueB;

			// Set A to the exclusive or value of A and B.
			valueA ^= valueB;

			// Set B to our carry shifted left.
			valueB = carry << 1;
		}

		// Return our result.
		return valueA;
	}

	// Binary ++ Function
	static int increment(int value)
	{
		return add(value, 1);
	}

	// Binary ++ Function
	static int plus_plus(int value)
	{
		return add(value, 1);
	}

	// Binary Subtraction Function
	static int subtract(int valueA, int valueB)
	{
		// Check if we are are subtracting nothing.
		if (!valueB)
		{
			// Return our result.
			return valueA;
		}

		// Subtract the exclusive or value of A and B by the and value of not A and B, shifted left.
		return subtract(valueA ^ valueB, (~valueA & valueB) << 1);
	}

	// Binary -- Function
	static int minus_minus(int value)
	{
		return subtract(value, 1);
	}

	// Binary -- Function
	static int decrement(int value)
	{
		return subtract(value, 1);
	}

	// Binary Multiplication Function
	static int multiply(int valueA, int valueB)
	{
		// Store our result variable.
		int product = 0;

		// Check if B is positive or negative.
		if (valueB >= 0)
		{
			// While B is not 0:
			while (valueB)
			{
				// If B is odd, add A to the result.
				if (valueB & 1)
				{
					product = add(product, valueA);
				}

				// Double A.
				valueA <<= 1;

				// Halve B.
				valueB >>= 1;
			}

			// Return our result.
			return product;
		}
		else
		{
			valueB = subtract(0, valueB);

			// While B is not 0:
			while (valueB)
			{
				// If B is odd, subtract the result by A.
				if (valueB & 1)
				{
					product = subtract(product, valueA);
				}

				// Double A.
				valueA <<= 1;

				// Halve B.
				valueB >>= 1;
			}

			// Return our result.
			return product;
		}
	}

	// Binary Square Function
	static int square(int value)
	{
		return multiply(value, value);
	}

	// Binary Exponent Function
	static int power(int valueA, int valueB)
	{
		if (!valueB)
		{
			return 1;
		}

		int product = valueA;

		for (int i = 1; i < valueB; i = plus_plus(i))
		{
			product = multiply(product, valueA);
		}

		return product;
	}

	// Binary Division Function
	static int divide(int valueA, int valueB)
	{
		// Check for division by zero.
		if (!valueB)
		{
			return 0;
		}

		// Store our result variable.
		int quotient = 0;

		// Check if A is positive or negative.
		if (valueA >= 0)
		{
			// Check if B is positive or negative.
			if (valueB > 0)
			{
				// Positive A, Positive B

				// While A is greater than B:
				while (valueA >= valueB)
				{
					// Subtract B from A.
					valueA = subtract(valueA, valueB);

					// Add 1 to our result.
					quotient = plus_plus(quotient);
				}
			}
			else
			{
				// Positive A, Negative B
				valueB = subtract(0, valueB);

				// While A is greater than B:
				while (valueA >= valueB)
				{
					// Subtract B from A.
					valueA = subtract(valueA, valueB);

					// Add 1 to our result.
					quotient = plus_plus(quotient);
				}

				quotient = subtract(0, quotient);
			}
		}
		else
		{
			// Check if B is positive or negative.
			if (valueB > 0)
			{
				// Negative A, Positive B
				valueA = subtract(0, valueA);

				// While A is greater than B:
				while (valueA >= valueB)
				{
					// Subtract B from A.
					valueA = subtract(valueA, valueB);

					// Add 1 to our result.
					quotient = plus_plus(quotient);
				}

				quotient = subtract(0, quotient);
			}
			else
			{
				// Negative A, Negative B
				valueA = subtract(0, valueA);
				valueB = subtract(0, valueB);

				// While A is greater than B:
				while (valueA >= valueB)
				{
					// Subtract B from A.
					valueA = subtract(valueA, valueB);

					// Add 1 to our result.
					quotient = plus_plus(quotient);
				}
			}
		}

		// Return our result.
		return quotient;
	}

	// Binary Modulo Function
	static int modulo(int valueA, int valueB)
	{
		if ((valueA < 0) ^ (valueB < 0))
		{
			return add(subtract(valueA, multiply(divide(valueA, valueB), valueB)), valueB);
		}
		else
		{
			return subtract(valueA, multiply(divide(valueA, valueB), valueB));
		}
	}
};
