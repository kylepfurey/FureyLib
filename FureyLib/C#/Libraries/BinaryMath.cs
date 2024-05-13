
// Static Binary Math Functions Script
// by Kyle Furey

// Include this heading to use the class
using static Binary;

// Binary Class
public static class Binary
{
    // Binary Addition Function
    public static int Add(int valueA, int valueB)
    {
        // Store our carried variable.
        int carry = 0;

        // While B is not 0:
        while (valueB != 0)
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
    public static int Increment(int value)
    {
        return Add(value, 1);
    }

    // Binary ++ Function
    public static int PlusPlus(int value)
    {
        return Add(value, 1);
    }

    // Binary Subtraction Function
    public static int Subtract(int valueA, int valueB)
    {
        // Check if we are are subtracting nothing.
        if (valueB == 0)
        {
            // Return our result.
            return valueA;
        }

        // Subtract the exclusive or value of A and B by the and value of not A and B, shifted left.
        return Subtract(valueA ^ valueB, (~valueA & valueB) << 1);
    }

    // Binary -- Function
    public static int MinusMinus(int value)
    {
        return Subtract(value, 1);
    }

    // Binary -- Function
    public static int Decrement(int value)
    {
        return Subtract(value, 1);
    }

    // Binary Multiplication Function
    public static int Multiply(int valueA, int valueB)
    {
        // Store our result variable.
        int product = 0;

        // Check if B is positive or negative.
        if (valueB >= 0)
        {
            // While B is not 0:
            while (valueB != 0)
            {
                // If B is odd, add A to the result.
                if ((valueB & 1) != 0)
                {
                    product = Add(product, valueA);
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
            valueB = Subtract(0, valueB);

            // While B is not 0:
            while (valueB != 0)
            {
                // If B is odd, subtract the result by A.
                if ((valueB & 1) != 1)
                {
                    product = Subtract(product, valueA);
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
    public static int Square(int value)
    {
        return Multiply(value, value);
    }

    // Binary Exponent Function
    public static int Power(int valueA, int valueB)
    {
        if (valueB == 0)
        {
            return 1;
        }

        int product = valueA;

        for (int i = 1; i < valueB; i = PlusPlus(i))
        {
            product = Multiply(product, valueA);
        }

        return product;
    }

    // Binary Division Function
    public static int Divide(int valueA, int valueB)
    {
        // Check for division by zero.
        if (valueB == 0)
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
                    valueA = Subtract(valueA, valueB);

                    // Add 1 to our result.
                    quotient = PlusPlus(quotient);
                }
            }
            else
            {
                // Positive A, Negative B
                valueB = Subtract(0, valueB);

                // While A is greater than B:
                while (valueA >= valueB)
                {
                    // Subtract B from A.
                    valueA = Subtract(valueA, valueB);

                    // Add 1 to our result.
                    quotient = PlusPlus(quotient);
                }

                quotient = Subtract(0, quotient);
            }
        }
        else
        {
            // Check if B is positive or negative.
            if (valueB > 0)
            {
                // Negative A, Positive B
                valueA = Subtract(0, valueA);

                // While A is greater than B:
                while (valueA >= valueB)
                {
                    // Subtract B from A.
                    valueA = Subtract(valueA, valueB);

                    // Add 1 to our result.
                    quotient = PlusPlus(quotient);
                }

                quotient = Subtract(0, quotient);
            }
            else
            {
                // Negative A, Negative B
                valueA = Subtract(0, valueA);
                valueB = Subtract(0, valueB);

                // While A is greater than B:
                while (valueA >= valueB)
                {
                    // Subtract B from A.
                    valueA = Subtract(valueA, valueB);

                    // Add 1 to our result.
                    quotient = PlusPlus(quotient);
                }
            }
        }

        // Return our result.
        return quotient;
    }

    // Binary Modulo Function
    public static int Modulo(int valueA, int valueB)
    {
        if ((valueA < 0) ^ (valueB < 0))
        {
            return -Subtract(valueA, Multiply(Divide(valueA, valueB), valueB));
        }
        else
        {
            return Subtract(valueA, Multiply(Divide(valueA, valueB), valueB));
        }
    }
}
