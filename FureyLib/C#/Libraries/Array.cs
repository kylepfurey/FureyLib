
// Static Array Functions Script
// by Kyle Furey

using System;
using System.Diagnostics;

// New array functions.
public static class Array<DataType>
{
    // ARRAY LENGTH

    // Returns the length of the given array
    public static int Length(DataType[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return 0;
        }

        return array.Length;
    }


    // COPYING ARRAY

    // Returns a copy of the given array
    public static DataType[] Copy(DataType[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array
        DataType[] arrayCopy = new DataType[array.Length];

        // Duplicate the array over to the copy
        System.Array.Copy(array, arrayCopy, array.Length);

        return arrayCopy;
    }

    // Returns a copy of the given data
    public static DataType Copy(DataType data)
    {
        // Null check
        if (data == null)
        {
            Debug.Assert(false, "Element is null!");
            return data;
        }

        return data;
    }

    // Returns a copy of the given array's element
    public static DataType CopyElement(DataType[] array, int index)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return default;
        }

        if (index < 0 || index > array.Length - 1)
        {
            Debug.Assert(false, "Could not copy element! Index was outside the bounds of the array!");
            return default;
        }

        return array[index];
    }

    // Returns copies of the given array's elements
    public static DataType[] CopyElement(DataType[] array, int[] index)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array
        DataType[] arrayCopy = new DataType[index.Length];
        int arrayIndex = 0;

        for (int i = 0; i < index.Length; i++)
        {
            if (index[i] < 0 || index[i] > array.Length - 1)
            {
                Debug.Assert(false, "Could not copy element! Index was outside the bounds of the array!");
                return array;
            }

            arrayCopy[arrayIndex] = array[index[i]];
            arrayIndex++;
        }

        return arrayCopy;
    }


    // EMPTY ARRAY

    // Returns an empty version of the array type
    public static DataType[] Empty()
    {
        return new DataType[0];
    }

    // Returns an empty version of the data type
    public static DataType EmptyElement()
    {
        return default;
    }

    // Returns an empty version of the array
    public static DataType[] Clear(DataType[] array)
    {
        // Create a copy of the array
        DataType[] arrayCopy = new DataType[array.Length];

        return arrayCopy;
    }


    // READING ARRAY ELEMENTS

    // Prints all elements in an array
    public static void Read(DataType[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
        }
        else
        {
            // Array name
            Debug.Assert(false, "Array of length " + array.Length + ":    ");

            // Print each element in an array
            for (int i = 0; i < array.Length; i++)
            {
                Debug.Assert(false, "#" + i + "   " + array[i]);
            }

            // Print end
            Debug.Assert(false, "End of array.");
        }
    }

    // Prints all elements in an array on one line
    public static void Read(DataType[] array, bool oneLine)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
        }
        else
        {
            // Whether to print all on one line or a list
            if (oneLine)
            {
                // Array name
                string log = "Array of length " + array.Length + ":    ";

                // Store each element in an array
                for (int i = 0; i < array.Length; i++)
                {
                    log += "#" + i + "   " + array[i] + "    ";
                }

                // Print log and end
                Debug.Assert(false, log + "End of array.");
            }
            else
            {
                // Array name
                Debug.Assert(false, "Array of length " + array.Length + ":    ");

                // Print each element in an array
                for (int i = 0; i < array.Length; i++)
                {
                    Debug.Assert(false, "#" + i + "   " + array[i]);
                }

                // Print end
                Debug.Assert(false, "End of array.");
            }
        }
    }

    // Prints all elements in an array on one line and returns the log
    public static void Read(DataType[] array, bool oneLine, out string log)
    {
        // Null check
        if (array == null)
        {
            log = "";
            Debug.Assert(false, "Array is null!");
        }
        else
        {
            // Array name
            log = "Array of length " + array.Length + ":    ";

            // Store each element in an array
            for (int i = 0; i < array.Length; i++)
            {
                log += "#" + i + "   " + array[i] + "    ";
            }

            log += "End of array.";

            // Whether to print all on one line or a list
            if (oneLine)
            {
                // Print log and end
                Debug.Assert(false, log);
            }
            else
            {
                // Array name
                Debug.Assert(false, "Array of length " + array.Length + ":    ");

                // Print each element in an array
                for (int i = 0; i < array.Length; i++)
                {
                    Debug.Assert(false, "#" + i + "   " + array[i]);
                }

                // Print end
                Debug.Assert(false, "End of array.");
            }
        }
    }


    // ADDING ARRAY ELEMENTS

    // Adds a new element to an array of elements, returns a copy
    public static DataType[] Add(DataType[] array, DataType addedData)
    {
        // Null check
        if (array == null || addedData == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array + 1 extra space
        DataType[] arrayCopy = new DataType[array.Length + 1];

        // Duplicate the array over to the copy
        System.Array.Copy(array, arrayCopy, array.Length);

        // Set the extra space as the incoming element
        arrayCopy[arrayCopy.Length - 1] = addedData;

        // Return a copy of the new array
        return arrayCopy;
    }

    // Adds a new element to an array of elements at a specified index, returns a copy
    public static DataType[] Add(DataType[] array, DataType addedData, int index)
    {
        // Null check
        if (array == null || addedData == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (index >= 0 && index <= array.Length)
        {
            // Create a copy of the array + 1 extra space
            DataType[] arrayCopy = new DataType[array.Length + 1];

            // Duplicate the array over to the copy
            System.Array.Copy(array, arrayCopy, index);
            System.Array.Copy(array, index, arrayCopy, index + 1, array.Length - index);

            // Set the extra space as the incoming element
            arrayCopy[index] = addedData;

            // Return a copy of the new array
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not add! Index was outside the bounds of the array!");
            return array;
        }
    }

    // Adds new elements to an array of elements, returns a copy
    public static DataType[] AddArray(DataType[] array, DataType[] addedArray)
    {
        // Null check
        if (array == null || addedArray == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array + the required extra spaces
        DataType[] arrayCopy = new DataType[array.Length + addedArray.Length];

        // Duplicate the array over to the copy
        System.Array.Copy(array, arrayCopy, array.Length);

        // Set the extra space as the incoming elements
        System.Array.Copy(addedArray, 0, arrayCopy, array.Length, addedArray.Length);

        // Return a copy of the new array
        return arrayCopy;
    }

    // Adds new elements to an array of elements at a specified index, returns a copy
    public static DataType[] AddArray(DataType[] array, DataType[] addedArray, int index)
    {
        // Null check
        if (array == null || addedArray == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (index >= 0 && index <= array.Length)
        {
            // Create a copy of the array + the required extra spaces
            DataType[] arrayCopy = new DataType[array.Length + addedArray.Length];

            // Duplicate the array over to the copy
            System.Array.Copy(array, arrayCopy, index);
            System.Array.Copy(array, index, arrayCopy, index + addedArray.Length, array.Length - index);

            // Set the extra space as the incoming elements
            System.Array.Copy(addedArray, 0, arrayCopy, index, addedArray.Length);

            // Return a copy of the new array
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not add! Index was outside the bounds of the array!");
            return array;
        }
    }

    // Adds a new element to an array of elements only if the new element is unique, returns a copy
    public static DataType[] AddUnique(DataType[] array, DataType addedData)
    {
        // Null check
        if (array == null || addedData == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        if (!Contains(array, addedData))
        {
            // Create a copy of the array + 1 extra space
            DataType[] arrayCopy = new DataType[array.Length + 1];

            // Duplicate the array over to the copy
            System.Array.Copy(array, arrayCopy, array.Length);

            // Set the extra space as the incoming element
            arrayCopy[arrayCopy.Length - 1] = addedData;

            Debug.Assert(false, "Data added! No matching elements found in the array.");

            // Return a copy of the new array
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Did not add! Matching elements found in the array.");

            return array;
        }
    }

    // Adds a new element to an array of elements only if the new element is unique and return whether it was successful, returns a copy
    public static DataType[] AddUnique(DataType[] array, DataType addedData, out bool success)
    {
        // Null check
        if (array == null || addedData == null)
        {
            Debug.Assert(false, "Array is null!");
            success = false;
            return array;
        }

        if (!Contains(array, addedData))
        {
            // Create a copy of the array + 1 extra space
            DataType[] arrayCopy = new DataType[array.Length + 1];

            // Duplicate the array over to the copy
            System.Array.Copy(array, arrayCopy, array.Length);

            // Set the extra space as the incoming element
            arrayCopy[arrayCopy.Length - 1] = addedData;

            Debug.Assert(false, "Data added! No matching elements found in the array.");

            // Return a copy of the new array
            success = true;
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Did not add! Matching elements found in the array.");

            success = false;
            return array;
        }
    }

    // Adds a new element to an array of elements only if the new element is not unique, returns a copy
    public static DataType[] AddDuplicate(DataType[] array, DataType addedData)
    {
        // Null check
        if (array == null || addedData == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        if (Contains(array, addedData))
        {
            // Create a copy of the array + 1 extra space
            DataType[] arrayCopy = new DataType[array.Length + 1];

            // Duplicate the array over to the copy
            System.Array.Copy(array, arrayCopy, array.Length);

            // Set the extra space as the incoming element
            arrayCopy[arrayCopy.Length - 1] = addedData;

            Debug.Assert(false, "Data added! Matching elements found in the array.");

            // Return a copy of the new array
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Did not add! No matching elements found in the array.");

            return array;
        }
    }

    // Adds a new element to an array of elements only if the new element is not unique and return whether it was successful, returns a copy
    public static DataType[] AddDuplicate(DataType[] array, DataType addedData, out bool success)
    {
        // Null check
        if (array == null || addedData == null)
        {
            Debug.Assert(false, "Array is null!");
            success = false;
            return array;
        }

        if (Contains(array, addedData))
        {
            // Create a copy of the array + 1 extra space
            DataType[] arrayCopy = new DataType[array.Length + 1];

            // Duplicate the array over to the copy
            System.Array.Copy(array, arrayCopy, array.Length);

            // Set the extra space as the incoming element
            arrayCopy[arrayCopy.Length - 1] = addedData;

            Debug.Assert(false, "Data added! Matching elements found in the array.");

            // Return a copy of the new array
            success = true;
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Did not add! No matching elements found in the array.");

            success = false;
            return array;
        }
    }


    // REMOVING ARRAY ELEMENTS

    // Removes the first matching element from an array of elements, returns a copy
    public static DataType[] Remove(DataType[] array, DataType removedData)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Loop through the array to find matching elements
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the elements are equal
            if (array[i].Equals(removedData))
            {
                // Remove the matching element
                return RemoveIndex(array, i);
            }
        }

        // No matching elements
        Debug.Assert(false, "Could not remove! No matching elements in the array!");
        return array;
    }

    // Removes the first or last matching element from an array of elements, returns a copy
    public static DataType[] Remove(DataType[] array, DataType removedData, bool reverseSearch)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Loop through the array to find matching elements
        if (reverseSearch)
        {
            for (int i = 0; i < array.Length; i++)
            {
                // Check if the elements are equal
                if (array[array.Length - i - 1].Equals(removedData))
                {
                    // Remove the matching element
                    return RemoveIndex(array, array.Length - i - 1);
                }
            }
        }
        else
        {
            for (int i = 0; i < array.Length; i++)
            {
                // Check if the elements are equal
                if (array[i].Equals(removedData))
                {
                    // Remove the matching element
                    return RemoveIndex(array, i);
                }
            }
        }

        // No matching elements
        Debug.Assert(false, "Could not remove! No matching elements in the array!");
        return array;
    }

    // Removes the first matching element from an array of elements and return the index, returns a copy
    public static DataType[] Remove(DataType[] array, DataType removedData, out int removedIndex)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            removedIndex = -1;
            return array;
        }

        // Loop through the array to find matching elements
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the elements are equal
            if (array[i].Equals(removedData))
            {
                // Remove the matching element
                removedIndex = i;
                return RemoveIndex(array, i);
            }
        }

        // No matching elements
        Debug.Assert(false, "Could not remove! No matching elements in the array!");
        removedIndex = -1;
        return array;
    }

    // Removes the first or last matching element from an array of elements and return the index, returns a copy
    public static DataType[] Remove(DataType[] array, DataType removedData, bool reverseSearch, out int removedIndex)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            removedIndex = -1;
            return array;
        }

        // Loop through the array to find matching elements
        if (reverseSearch)
        {
            for (int i = 0; i < array.Length; i++)
            {
                // Check if the elements are equal
                if (array[array.Length - i - 1].Equals(removedData))
                {
                    // Remove the matching element
                    removedIndex = array.Length - i - 1;
                    return RemoveIndex(array, array.Length - i - 1);
                }
            }
        }
        else
        {
            for (int i = 0; i < array.Length; i++)
            {
                // Check if the elements are equal
                if (array[i].Equals(removedData))
                {
                    // Remove the matching element
                    removedIndex = i;
                    return RemoveIndex(array, i);
                }
            }
        }

        // No matching elements
        Debug.Assert(false, "Could not remove! No matching elements in the array!");
        removedIndex = -1;
        return array;
    }

    // Removes the first matching elements from an array of elements, returns a copy
    public static DataType[] Remove(DataType[] array, DataType[] removedData)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Initialize index array
        int[] indicies = new int[removedData.Length];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array and compare the given element with the array's elements
        for (int i = 0; i < removedData.Length; i++)
        {
            for (int j = 0; j < array.Length; j++)
            {
                // Matching element found
                if (array[j].Equals(removedData[i]))
                {
                    indicies[arrayIndex] = j;
                    arrayIndex++;
                    break;
                }
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        return arrayCopy;
    }

    // Removes the first or last matching elements from an array of elements, returns a copy
    public static DataType[] Remove(DataType[] array, DataType[] removedData, bool reverseSearch)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Initialize index array
        int[] indicies = new int[removedData.Length];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array and compare the given element with the array's elements
        if (reverseSearch)
        {
            for (int i = 0; i < removedData.Length; i++)
            {
                for (int j = 0; j < array.Length; j++)
                {
                    // Matching element found
                    if (array[array.Length - j - 1].Equals(removedData[i]))
                    {
                        indicies[arrayIndex] = array.Length - j - 1;
                        arrayIndex++;
                        break;
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < removedData.Length; i++)
            {
                for (int j = 0; j < array.Length; j++)
                {
                    // Matching element found
                    if (array[j].Equals(removedData[i]))
                    {
                        indicies[arrayIndex] = j;
                        arrayIndex++;
                        break;
                    }
                }
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        // Create a copy of the array - the number of removed spaces
        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        return arrayCopy;
    }

    // Removes the first matching elements from an array of elements and return the indicies, returns a copy
    public static DataType[] Remove(DataType[] array, DataType[] removedData, out int[] removedIndex)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            removedIndex = new int[0];
            return array;
        }

        // Initialize index array
        int[] indicies = new int[removedData.Length];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array and compare the given element with the array's elements
        for (int i = 0; i < removedData.Length; i++)
        {
            for (int j = 0; j < array.Length; j++)
            {
                // Matching element found
                if (array[j].Equals(removedData[i]))
                {
                    indicies[arrayIndex] = j;
                    arrayIndex++;
                    break;
                }
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            removedIndex = new int[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        removedIndex = indicies;
        return arrayCopy;
    }

    // Removes the first or last matching elements from an array of elements and return the indicies, returns a copy
    public static DataType[] Remove(DataType[] array, DataType[] removedData, bool reverseSearch, out int[] removedIndex)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            removedIndex = new int[0];
            return array;
        }

        // Initialize index array
        int[] indicies = new int[removedData.Length];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array and compare the given element with the array's elements
        if (reverseSearch)
        {
            for (int i = 0; i < removedData.Length; i++)
            {
                for (int j = 0; j < array.Length; j++)
                {
                    // Matching element found
                    if (array[array.Length - j - 1].Equals(removedData[i]))
                    {
                        indicies[arrayIndex] = array.Length - j - 1;
                        arrayIndex++;
                        break;
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < removedData.Length; i++)
            {
                for (int j = 0; j < array.Length; j++)
                {
                    // Matching element found
                    if (array[j].Equals(removedData[i]))
                    {
                        indicies[arrayIndex] = j;
                        arrayIndex++;
                        break;
                    }
                }
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            removedIndex = new int[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        // Create a copy of the array - the number of removed spaces
        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        removedIndex = indicies;
        return arrayCopy;
    }

    // Removes the set number of the first matching elements from an array of elements, returns a copy
    public static DataType[] Remove(DataType[] array, DataType removedData, int removeAmount)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Remove check
        if (removeAmount > array.Length)
        {
            Debug.Assert(false, "You cannot remove more elements than the length!");
        }

        // Initialize index array
        int[] indicies = new int[removeAmount];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array to find matching elements
        for (int i = 0; i < array.Length; i++)
        {
            if (arrayIndex == removeAmount)
            {
                // Found enough elements to remove
                break;
            }

            // Check if the elements are equal
            if (array[i].Equals(removedData))
            {
                // Store the matching index for removal
                indicies[arrayIndex] = i;
                arrayIndex++;
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        return arrayCopy;
    }

    // Removes the set number of the first or last matching elements from an array of elements, returns a copy
    public static DataType[] Remove(DataType[] array, DataType removedData, int removeAmount, bool reverseSearch)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Remove check
        if (removeAmount > array.Length)
        {
            Debug.Assert(false, "You cannot remove more elements than the length!");
        }

        // Initialize index array
        int[] indicies = new int[removeAmount];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array to find matching elements
        if (reverseSearch)
        {
            for (int i = 0; i < array.Length; i++)
            {
                if (arrayIndex == removeAmount)
                {
                    // Found enough elements to remove
                    break;
                }

                // Check if the elements are equal
                if (array[array.Length - i - 1].Equals(removedData))
                {
                    // Store the matching index for removal
                    indicies[arrayIndex] = array.Length - i - 1;
                    arrayIndex++;
                }
            }
        }
        else
        {
            for (int i = 0; i < array.Length; i++)
            {
                if (arrayIndex == removeAmount)
                {
                    // Found enough elements to remove
                    break;
                }

                // Check if the elements are equal
                if (array[i].Equals(removedData))
                {
                    // Store the matching index for removal
                    indicies[arrayIndex] = i;
                    arrayIndex++;
                }
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        return arrayCopy;
    }

    // Removes the set number of the first matching elements from an array of elements and returns the indicies of each removed element, returns a copy
    public static DataType[] Remove(DataType[] array, DataType removedData, int removeAmount, out int[] removedIndex)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            removedIndex = new int[0];
            return array;
        }

        // Remove check
        if (removeAmount > array.Length)
        {
            Debug.Assert(false, "You cannot remove more elements than the length!");
        }

        // Initialize index array
        int[] indicies = new int[removeAmount];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array to find matching elements
        for (int i = 0; i < array.Length; i++)
        {
            if (arrayIndex == removeAmount)
            {
                // Found enough elements to remove
                break;
            }

            // Check if the elements are equal
            if (array[i].Equals(removedData))
            {
                // Store the matching index for removal
                indicies[arrayIndex] = i;
                arrayIndex++;
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            removedIndex = new int[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        removedIndex = indicies;
        return arrayCopy;
    }

    // Removes the set number of the first or last matching elements from an array of elements and returns the indicies of each removed element, returns a copy
    public static DataType[] Remove(DataType[] array, DataType removedData, int removeAmount, bool reverseSearch, out int[] removedIndex)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            removedIndex = new int[0];
            return array;
        }

        // Remove check
        if (removeAmount > array.Length)
        {
            Debug.Assert(false, "You cannot remove more elements than the length!");
        }

        // Initialize index array
        int[] indicies = new int[removeAmount];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array to find matching elements
        if (reverseSearch)
        {
            for (int i = 0; i < array.Length; i++)
            {
                if (arrayIndex == removeAmount)
                {
                    // Found enough elements to remove
                    break;
                }

                // Check if the elements are equal
                if (array[array.Length - i - 1].Equals(removedData))
                {
                    // Store the matching index for removal
                    indicies[arrayIndex] = array.Length - i - 1;
                    arrayIndex++;
                }
            }
        }
        else
        {
            for (int i = 0; i < array.Length; i++)
            {
                if (arrayIndex == removeAmount)
                {
                    // Found enough elements to remove
                    break;
                }

                // Check if the elements are equal
                if (array[i].Equals(removedData))
                {
                    // Store the matching index for removal
                    indicies[arrayIndex] = i;
                    arrayIndex++;
                }
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            removedIndex = new int[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        removedIndex = indicies;
        return arrayCopy;
    }

    // Removes a set number of the first matching elements from an array of elements, returns a copy
    public static DataType[] Remove(DataType[] array, DataType[] removedData, int[] removeAmount)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Initialize index array
        int[] indicies = new int[array.Length];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array to find matching elements
        for (int i = 0; i < removedData.Length; i++)
        {
            for (int j = 0; j < array.Length; j++)
            {
                if (arrayIndex == removeAmount[i])
                {
                    // Found enough elements to remove
                    break;
                }

                // Check if the elements are equal
                if (array[j].Equals(removedData[i]))
                {
                    // Check if we have already stored this index
                    if (!Array<int>.Contains(indicies, j))
                    {
                        // Store the matching index for removal
                        indicies[arrayIndex] = j;
                        arrayIndex++;
                    }
                }
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        return arrayCopy;
    }

    // Removes a set number of the first or last matching elements from an array of elements, returns a copy
    public static DataType[] Remove(DataType[] array, DataType[] removedData, int[] removeAmount, bool reverseSearch)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Initialize index array
        int[] indicies = new int[array.Length];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array to find matching elements
        if (reverseSearch)
        {
            for (int i = 0; i < removedData.Length; i++)
            {
                for (int j = 0; j < array.Length; j++)
                {
                    if (arrayIndex == removeAmount[i])
                    {
                        // Found enough elements to remove
                        break;
                    }

                    // Check if the elements are equal
                    if (array[array.Length - j - 1].Equals(removedData[i]))
                    {
                        // Check if we have already stored this index
                        if (!Array<int>.Contains(indicies, array.Length - j - 1))
                        {
                            // Store the matching index for removal
                            indicies[arrayIndex] = array.Length - j - 1;
                            arrayIndex++;
                        }
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < removedData.Length; i++)
            {
                for (int j = 0; j < array.Length; j++)
                {
                    if (arrayIndex == removeAmount[i])
                    {
                        // Found enough elements to remove
                        break;
                    }

                    // Check if the elements are equal
                    if (array[j].Equals(removedData[i]))
                    {
                        // Check if we have already stored this index
                        if (!Array<int>.Contains(indicies, j))
                        {
                            // Store the matching index for removal
                            indicies[arrayIndex] = j;
                            arrayIndex++;
                        }
                    }
                }
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        return arrayCopy;
    }

    // Removes a set number of the first matching elements from an array of elements and returns the indicies of each removed element, returns a copy
    public static DataType[] Remove(DataType[] array, DataType[] removedData, int[] removeAmount, out int[] removedIndex)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            removedIndex = new int[0];
            return array;
        }

        // Initialize index array
        int[] indicies = new int[array.Length];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array to find matching elements
        for (int i = 0; i < removedData.Length; i++)
        {
            for (int j = 0; j < array.Length; j++)
            {
                if (arrayIndex == removeAmount[i])
                {
                    // Found enough elements to remove
                    break;
                }

                // Check if the elements are equal
                if (array[j].Equals(removedData[i]))
                {
                    // Check if we have already stored this index
                    if (!Array<int>.Contains(indicies, j))
                    {
                        // Store the matching index for removal
                        indicies[arrayIndex] = j;
                        arrayIndex++;
                    }
                }
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            removedIndex = new int[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        removedIndex = Array<int>.Trim(indicies, arrayIndex);
        return arrayCopy;
    }

    // Removes a set number of the first or last matching elements from an array of elements and returns the indicies of each removed element, returns a copy
    public static DataType[] Remove(DataType[] array, DataType[] removedData, int[] removeAmount, bool reverseSearch, out int[] removedIndex)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            removedIndex = new int[0];
            return array;
        }

        // Initialize index array
        int[] indicies = new int[array.Length];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array to find matching elements
        if (reverseSearch)
        {
            for (int i = 0; i < removedData.Length; i++)
            {
                for (int j = 0; j < array.Length; j++)
                {
                    if (arrayIndex == removeAmount[i])
                    {
                        // Found enough elements to remove
                        break;
                    }

                    // Check if the elements are equal
                    if (array[array.Length - j - 1].Equals(removedData[i]))
                    {
                        // Check if we have already stored this index
                        if (!Array<int>.Contains(indicies, array.Length - j - 1))
                        {
                            // Store the matching index for removal
                            indicies[arrayIndex] = array.Length - j - 1;
                            arrayIndex++;
                        }
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < removedData.Length; i++)
            {
                for (int j = 0; j < array.Length; j++)
                {
                    if (arrayIndex == removeAmount[i])
                    {
                        // Found enough elements to remove
                        break;
                    }

                    // Check if the elements are equal
                    if (array[j].Equals(removedData[i]))
                    {
                        // Check if we have already stored this index
                        if (!Array<int>.Contains(indicies, j))
                        {
                            // Store the matching index for removal
                            indicies[arrayIndex] = j;
                            arrayIndex++;
                        }
                    }
                }
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            removedIndex = new int[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        removedIndex = Array<int>.Trim(indicies, arrayIndex);
        return arrayCopy;
    }

    // Removes an element from an array of elements, returns a copy
    public static DataType[] RemoveIndex(DataType[] array, int removedIndex)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (removedIndex >= 0 && removedIndex < array.Length)
        {
            // Create a copy of the array - 1 extra space
            DataType[] arrayCopy = new DataType[array.Length - 1];

            // Duplicate the array over to the copy without the removed element
            System.Array.Copy(array, arrayCopy, removedIndex);
            System.Array.Copy(array, removedIndex + 1, arrayCopy, removedIndex, array.Length - removedIndex - 1);

            // Return a copy of the new array
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not remove! Index was outside the bounds of the array!");
            return array;
        }
    }

    // Removes elements from an array of elements, returns a copy
    public static DataType[] RemoveIndex(DataType[] array, int removedIndex, int removeAmount)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (removedIndex >= 0 && removedIndex < array.Length && removedIndex + removeAmount <= array.Length)
        {
            // Create a copy of the array - the number of removed spaces
            DataType[] arrayCopy = new DataType[array.Length - removeAmount];

            // Duplicate the array over to the copy without the removed elements
            System.Array.Copy(array, arrayCopy, removedIndex);
            System.Array.Copy(array, removedIndex + removeAmount, arrayCopy, removedIndex, array.Length - removedIndex - removeAmount);

            // Return a copy of the new array
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not remove! Index or amount was outside the bounds of the array!");
            return array;
        }
    }

    // Removes a list of elements from an array of elements, returns a copy
    public static DataType[] RemoveIndex(DataType[] array, int[] removedIndex)
    {
        // Null check
        if (array == null || removedIndex == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - removedIndex.Length];

        // Loop through the array to add back the unmarked elements
        int arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(removedIndex, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        return arrayCopy;
    }

    // Removes a list of elements from an array of elements and returns the removed elements, returns a copy
    public static DataType[] RemoveIndex(DataType[] array, int[] removedIndex, out DataType[] removedArray)
    {
        // Null check
        if (array == null || removedIndex == null)
        {
            Debug.Assert(false, "Array is null!");
            removedArray = new DataType[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - removedIndex.Length];
        removedArray = new DataType[removedIndex.Length];

        // Loop through the array to add back the unmarked elements
        int arrayIndex = 0;
        int arrayIndex2 = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(removedIndex, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
            else
            {
                // Copy that element back to the array
                removedArray[arrayIndex2] = array[i];
                arrayIndex2++;
            }
        }

        return arrayCopy;
    }

    // Removes a list of elements from an array of elements and returns the saved element indicies, returns a copy
    public static DataType[] RemoveIndex(DataType[] array, int[] removedIndex, out int[] savedIndex)
    {
        // Null check
        if (array == null || removedIndex == null)
        {
            Debug.Assert(false, "Array is null!");
            savedIndex = new int[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - removedIndex.Length];
        savedIndex = new int[removedIndex.Length];

        // Loop through the array to add back the unmarked elements
        int arrayIndex = 0;
        int arrayIndex2 = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(removedIndex, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
            else
            {
                savedIndex[arrayIndex2] = i;
                arrayIndex2++;
            }
        }

        return arrayCopy;
    }

    // Removes a list of elements from an array of elements and returns the removed elements and the saved element indicies, returns a copy
    public static DataType[] RemoveIndex(DataType[] array, int[] removedIndex, out DataType[] removedArray, out int[] savedIndex)
    {
        // Null check
        if (array == null || removedIndex == null)
        {
            Debug.Assert(false, "Array is null!");
            removedArray = new DataType[0];
            savedIndex = new int[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - removedIndex.Length];
        removedArray = new DataType[removedIndex.Length];
        savedIndex = new int[removedIndex.Length];

        // Loop through the array to add back the unmarked elements
        int arrayIndex = 0;
        int arrayIndex2 = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(removedIndex, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
            else
            {
                // Copy that element back to the array
                removedArray[arrayIndex2] = array[i];
                savedIndex[arrayIndex2] = i;
                arrayIndex2++;
            }
        }

        return arrayCopy;
    }

    // Removes all matching elements from an array of elements, returns a copy
    public static DataType[] RemoveAll(DataType[] array, DataType removedData)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Initialize index array
        int[] indicies = new int[array.Length];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array and compare the given element with the array's elements
        for (int i = 0; i < array.Length; i++)
        {
            // Matching element found
            if (array[i].Equals(removedData))
            {
                indicies[arrayIndex] = i;
                arrayIndex++;
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        // Create a copy of the array - the number of removed spaces
        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        return arrayCopy;
    }

    // Removes all matching elements from an array of elements and return the indicies, returns a copy
    public static DataType[] RemoveAll(DataType[] array, DataType removedData, out int[] removedIndex)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            removedIndex = new int[0];
            return array;
        }

        // Initialize index array
        int[] indicies = new int[array.Length];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array and compare the given element with the array's elements
        for (int i = 0; i < array.Length; i++)
        {
            // Matching element found
            if (array[i].Equals(removedData))
            {
                indicies[arrayIndex] = i;
                arrayIndex++;
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            removedIndex = new int[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        // Create a copy of the array - the number of removed spaces
        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        removedIndex = Array<int>.Trim(indicies, arrayIndex);
        return arrayCopy;
    }

    // Removes all matching elements from an array of elements, returns a copy
    public static DataType[] RemoveAll(DataType[] array, DataType[] removedData)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Initialize index array
        int[] indicies = new int[array.Length];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array and compare the given element with the array's elements
        for (int i = 0; i < removedData.Length; i++)
        {
            for (int j = 0; j < array.Length; j++)
            {
                // Matching element found
                if (array[j].Equals(removedData[i]))
                {
                    indicies[arrayIndex] = j;
                    arrayIndex++;
                }
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        // Loop through the array to add back the unmarked elements
        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        return arrayCopy;
    }

    // Removes all matching elements from an array of elements and return the indicies, returns a copy
    public static DataType[] RemoveAll(DataType[] array, DataType[] removedData, out int[] removedIndex)
    {
        // Null check
        if (array == null || removedData == null)
        {
            Debug.Assert(false, "Array is null!");
            removedIndex = new int[0];
            return array;
        }

        // Initialize index array
        int[] indicies = new int[array.Length];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array and compare the given element with the array's elements
        for (int i = 0; i < removedData.Length; i++)
        {
            for (int j = 0; j < array.Length; j++)
            {
                // Matching element found
                if (array[j].Equals(removedData[i]))
                {
                    indicies[arrayIndex] = j;
                    arrayIndex++;
                }
            }
        }

        // Check if any of the elements matched
        if (arrayIndex == 0)
        {
            Debug.Assert(false, "Could not remove! No matching elements in the array!");
            removedIndex = new int[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        // Loop through the array to add back the unmarked elements
        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        removedIndex = Array<int>.Trim(indicies, arrayIndex);
        return arrayCopy;
    }

    // Removes all duplicate elements from an array of elements, returns a copy
    public static DataType[] RemoveDuplicates(DataType[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = Copy(array);

        // Loop through the array to add back the unmarked elements
        for (int i = 0; i < arrayCopy.Length; i++)
        {
            // Check if the current element has duplicates
            Contains(arrayCopy, arrayCopy[i], out int total);

            if (total > 1)
            {
                // Remove duplicate
                arrayCopy = Remove(arrayCopy, arrayCopy[i], total - 1, true);
                i = 0;
            }
        }

        return arrayCopy;
    }

    // Removes all duplicate elements from an array of elements and returns their indicies, returns a copy
    public static DataType[] RemoveDuplicates(DataType[] array, out int[] removedIndex)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            removedIndex = new int[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = Copy(array);
        int[] removedIndexTotal = new int[array.Length];

        // Loop through the array to add back the unmarked elements
        for (int i = 0; i < arrayCopy.Length; i++)
        {
            // Check if the current element has duplicates
            Contains(arrayCopy, arrayCopy[i], out int total);

            if (total > 1)
            {
                // Remove duplicate
                arrayCopy = Remove(arrayCopy, arrayCopy[i], total - 1, false, out removedIndex);
                removedIndexTotal = Array<int>.AddArray(removedIndexTotal, removedIndex);
                i = 0;
            }
        }

        removedIndex = removedIndexTotal;
        return arrayCopy;
    }

    // Removes all front or back duplicate elements from an array of elements, returns a copy
    public static DataType[] RemoveDuplicates(DataType[] array, bool reverseSearch)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = Copy(array);

        // Loop through the array to add back the unmarked elements
        for (int i = 0; i < arrayCopy.Length; i++)
        {
            // Check if the current element has duplicates
            Contains(arrayCopy, arrayCopy[i], out int total);

            if (total > 1)
            {
                // Remove duplicate
                arrayCopy = Remove(arrayCopy, arrayCopy[i], total - 1, !reverseSearch);
                i = 0;
            }
        }

        return arrayCopy;
    }

    // Removes all front or back duplicate elements from an array of elements and returns their indicies, returns a copy
    public static DataType[] RemoveDuplicates(DataType[] array, out int[] removedIndex, bool reverseSearch)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            removedIndex = new int[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = Copy(array);
        int[] removedIndexTotal = new int[array.Length];

        // Loop through the array to add back the unmarked elements
        for (int i = 0; i < arrayCopy.Length; i++)
        {
            // Check if the current element has duplicates
            Contains(arrayCopy, arrayCopy[i], out int total);

            if (total > 1)
            {
                // Remove duplicate
                arrayCopy = Remove(arrayCopy, arrayCopy[i], total - 1, !reverseSearch, out removedIndex);
                removedIndexTotal = Array<int>.AddArray(removedIndexTotal, removedIndex);
                i = 0;
            }
        }

        removedIndex = removedIndexTotal;
        return arrayCopy;
    }


    // ISOLATING ARRAY ELEMENTS

    // Isolates a list of elements from an array of elements, returns a copy
    public static DataType[] Isolate(DataType[] array, int[] isolatedIndex)
    {
        // Null check
        if (array == null || isolatedIndex == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Remove duplicate indicies
        int[] isolated = Array<int>.RemoveDuplicates(isolatedIndex);

        if (isolated.Length > array.Length)
        {
            Debug.Assert(false, "Could not isolate! Index is longer than array!");
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[isolated.Length];

        // Loop through the array to add back the unmarked elements
        int arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be isolated
            if (Array<int>.Contains(isolated, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        return arrayCopy;
    }

    // Isolates a list of elements from an array of elements and returns the remaining elements, returns a copy
    public static DataType[] Isolate(DataType[] array, int[] isolatedIndex, out DataType[] remainingArray)
    {
        // Null check
        if (array == null || isolatedIndex == null)
        {
            Debug.Assert(false, "Array is null!");
            remainingArray = new DataType[0];
            return array;
        }

        // Remove duplicate indicies
        int[] isolated = Array<int>.RemoveDuplicates(isolatedIndex);

        if (isolated.Length > array.Length)
        {
            Debug.Assert(false, "Could not isolate! Index is longer than array!");
            remainingArray = new DataType[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[isolated.Length];
        remainingArray = new DataType[array.Length - isolated.Length];

        // Loop through the array to add back the unmarked elements
        int arrayIndex = 0;
        int arrayIndex2 = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is marked to be isolated
            if (Array<int>.Contains(isolated, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
            else
            {
                // Copy that element back to the array
                remainingArray[arrayIndex2] = array[i];
                arrayIndex2++;
            }
        }

        return arrayCopy;
    }

    // Isolates a list of elements from an array of elements and returns the remaining indicies, returns a copy
    public static DataType[] Isolate(DataType[] array, int[] isolatedIndex, out int[] remainingIndex)
    {
        // Null check
        if (array == null || isolatedIndex == null)
        {
            Debug.Assert(false, "Array is null!");
            remainingIndex = new int[0];
            return array;
        }

        // Remove duplicate indicies
        int[] isolated = Array<int>.RemoveDuplicates(isolatedIndex);

        if (isolated.Length > array.Length)
        {
            Debug.Assert(false, "Could not isolate! Index is longer than array!");
            remainingIndex = new int[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[isolated.Length];
        remainingIndex = new int[array.Length - isolated.Length];

        // Loop through the array to add back the unmarked elements
        int arrayIndex = 0;
        int arrayIndex2 = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is marked to be isolated
            if (Array<int>.Contains(isolated, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
            else
            {
                // Copy that element back to the array
                remainingIndex[arrayIndex2] = i;
                arrayIndex2++;
            }
        }

        return arrayCopy;
    }

    // Isolates a list of elements from an array of elements and returns the remaining elements and their indicies, returns a copy
    public static DataType[] Isolate(DataType[] array, int[] isolatedIndex, out DataType[] remainingArray, out int[] remainingIndex)
    {
        // Null check
        if (array == null || isolatedIndex == null)
        {
            Debug.Assert(false, "Array is null!");
            remainingArray = new DataType[0];
            remainingIndex = new int[0];
            return array;
        }

        // Remove duplicate indicies
        int[] isolated = Array<int>.RemoveDuplicates(isolatedIndex);

        if (isolated.Length > array.Length)
        {
            Debug.Assert(false, "Could not isolate! Index is longer than array!");
            remainingArray = new DataType[0];
            remainingIndex = new int[0];
            return array;
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[isolated.Length];
        remainingArray = new DataType[array.Length - isolated.Length];
        remainingIndex = new int[array.Length - isolated.Length];

        // Loop through the array to add back the unmarked elements
        int arrayIndex = 0;
        int arrayIndex2 = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is marked to be isolated
            if (Array<int>.Contains(isolated, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
            else
            {
                // Copy that element back to the array
                remainingArray[arrayIndex2] = array[i];
                remainingIndex[arrayIndex2] = i;
                arrayIndex2++;
            }
        }

        return arrayCopy;
    }


    // MOVING ARRAY ELEMENTS

    // Swaps two elements from an array of elements, returns a copy
    public static DataType[] Swap(DataType[] array, int swappedIndex1, int swappedIndex2)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (swappedIndex1 >= 0 && swappedIndex1 < array.Length && swappedIndex2 >= 0 && swappedIndex2 < array.Length)
        {
            // Create a copy of the array 
            DataType[] arrayCopy = new DataType[array.Length];
            System.Array.Copy(array, arrayCopy, array.Length);

            // Store the swapped element
            DataType swappedElement = arrayCopy[swappedIndex1];

            // Swap the two elements
            arrayCopy[swappedIndex1] = arrayCopy[swappedIndex2];
            arrayCopy[swappedIndex2] = swappedElement;

            // Return a copy of the swapped array
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not swap! Index was outside the bounds of the array!");
            return array;
        }
    }

    // Shifts all array elements by a selected amount, returns a copy
    public static DataType[] Shift(DataType[] array, int shiftAmount)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Check if shifting the array is unnecessary
        if (shiftAmount % array.Length == 0)
        {
            Debug.Assert(false, "Shifted array is identical to unshifted array!");
            return array;
        }

        // Create a copy of the array
        DataType[] arrayCopy = new DataType[array.Length];

        // Place the array elements at their shifted location using modulo
        for (int i = 0; i < array.Length; i++)
        {
            arrayCopy[i] = array[((i - shiftAmount) % array.Length + array.Length) % array.Length];
        }

        return arrayCopy;
    }

    // Shifts all array elements by a selected amount and returns the positive shift, returns a copy
    public static DataType[] Shift(DataType[] array, int shiftAmount, out int positiveShift)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            positiveShift = 0;
            return array;
        }

        // Check if shifting the array is unnecessary
        if (shiftAmount % array.Length == 0)
        {
            Debug.Assert(false, "Shifted array is identical to unshifted array!");
            positiveShift = 0;
            return array;
        }

        // Create a copy of the array
        DataType[] arrayCopy = new DataType[array.Length];

        // Place the array elements at their shifted location using modulo
        for (int i = 0; i < array.Length; i++)
        {
            arrayCopy[i] = array[((i - shiftAmount) % array.Length + array.Length) % array.Length];
        }

        positiveShift = (shiftAmount % array.Length + array.Length) % array.Length;
        return arrayCopy;
    }

    // Shifts all array elements by a selected amount and returns the positive shift and total shift, returns a copy
    public static DataType[] Shift(DataType[] array, int shiftAmount, out int positiveShift, out int totalShift)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            positiveShift = 0;
            totalShift = 0;
            return array;
        }

        // Check if shifting the array is unnecessary
        if (shiftAmount % array.Length == 0)
        {
            Debug.Assert(false, "Shifted array is identical to unshifted array!");
            positiveShift = 0;
            totalShift = 0;
            return array;
        }

        // Create a copy of the array
        DataType[] arrayCopy = new DataType[array.Length];

        // Place the array elements at their shifted location using modulo
        for (int i = 0; i < array.Length; i++)
        {
            arrayCopy[i] = array[((i - shiftAmount) % array.Length + array.Length) % array.Length];
        }

        positiveShift = (shiftAmount % array.Length + array.Length) % array.Length;
        totalShift = shiftAmount % array.Length;
        return arrayCopy;
    }


    // FINDING ARRAY ELEMENTS

    // Check if the array has a specific element
    public static bool Contains(DataType[] array, DataType data)
    {
        // Null check
        if (array == null || data == null)
        {
            Debug.Assert(false, "Array is null!");
            return false;
        }

        // Loop through the array and compare the given element with the array's elements
        for (int i = 0; i < array.Length; i++)
        {
            if (array[i].Equals(data))
            {
                // Matching element found
                return true;
            }
        }

        // No matching element found
        return false;
    }

    // Check if the array has a specific element and also returns the number of matching elements
    public static bool Contains(DataType[] array, DataType data, out int total)
    {
        // Null check
        if (array == null || data == null)
        {
            Debug.Assert(false, "Array is null!");
            total = 0;
            return false;
        }

        // Loop through the array and compare the given element with the array's elements
        total = 0;
        for (int i = 0; i < array.Length; i++)
        {
            if (array[i].Equals(data))
            {
                // Matching element found
                total++;
            }
        }

        if (total > 0)
        {
            return true;
        }

        // No matching element found
        return false;
    }

    // Check if the array has a specific element and return its index (returns -1 if nothing is found)
    public static int Find(DataType[] array, DataType data)
    {
        // Null check
        if (array == null || data == null)
        {
            Debug.Assert(false, "Array is null!");
            return -1;
        }

        // Loop through the array and compare the given element with the array's elements
        for (int i = 0; i < array.Length; i++)
        {
            if (array[i].Equals(data))
            {
                // Matching element found
                return i;
            }
        }

        Debug.Assert(false, "Could not find matching data!");
        return -1;
    }

    // Check if the array has a specific element and return its index (returns -1 if nothing is found)
    public static int Find(DataType[] array, DataType data, bool reverseSearch)
    {
        // Null check
        if (array == null || data == null)
        {
            Debug.Assert(false, "Array is null!");
            return -1;
        }

        // Loop through the array and compare the given element with the array's elements
        if (reverseSearch)
        {
            for (int i = 0; i < array.Length; i++)
            {
                if (array[array.Length - i - 1].Equals(data))
                {
                    // Matching element found
                    return i;
                }
            }
        }
        else
        {
            for (int i = 0; i < array.Length; i++)
            {
                if (array[i].Equals(data))
                {
                    // Matching element found
                    return i;
                }
            }
        }

        Debug.Assert(false, "Could not find matching data!");
        return -1;
    }

    // Check if the array has a specific element and return its index (returns empty if nothing is found)
    public static int[] FindAll(DataType[] array, DataType data)
    {
        // Null check
        if (array == null || data == null)
        {
            Debug.Assert(false, "Array is null!");
            return new int[0];
        }

        // Initialize array
        int[] indicies = new int[array.Length];
        int arrayIndex = 0;

        // Loop through the array and compare the given element with the array's elements
        for (int i = 0; i < array.Length; i++)
        {
            if (array[i].Equals(data))
            {
                // Matching element found
                indicies[arrayIndex] = i;
                arrayIndex++;
            }
        }

        // Trim off empty elements
        if (arrayIndex < indicies.Length)
        {
            indicies = Array<int>.Trim(indicies, arrayIndex);
        }

        // Check if any of the elements matched
        if (indicies.Length == 0)
        {
            Debug.Assert(false, "Could not find matching data!");
        }

        return indicies;
    }

    // Check if the array has a specific element and return its index (returns empty if nothing is found)
    public static int[] FindAll(DataType[] array, DataType data, bool reverseSearch)
    {
        // Null check
        if (array == null || data == null)
        {
            Debug.Assert(false, "Array is null!");
            return new int[0];
        }

        // Initialize array
        int[] indicies = new int[array.Length];
        int arrayIndex = 0;

        // Loop through the array and compare the given element with the array's elements
        if (reverseSearch)
        {
            for (int i = 0; i < array.Length; i++)
            {
                if (array[array.Length - i - 1].Equals(data))
                {
                    // Matching element found
                    indicies[arrayIndex] = array.Length - i - 1;
                    arrayIndex++;
                }
            }
        }
        else
        {
            for (int i = 0; i < array.Length; i++)
            {
                if (array[i].Equals(data))
                {
                    // Matching element found
                    indicies[arrayIndex] = i;
                    arrayIndex++;
                }
            }
        }

        // Trim off empty elements
        if (arrayIndex < indicies.Length)
        {
            indicies = Array<int>.Trim(indicies, arrayIndex);
        }

        // Check if any of the elements matched
        if (indicies.Length == 0)
        {
            Debug.Assert(false, "Could not find matching data!");
        }

        return indicies;
    }


    // REPLACING ARRAY ELEMENTS

    // Replaces a specific index in an array with the given replacement data, returns a copy
    public static DataType[] Replace(DataType[] array, int replacedIndex, DataType replacementData)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (replacedIndex >= 0 && replacedIndex < array.Length)
        {
            // Create a copy of the array 
            DataType[] arrayCopy = Copy(array);

            // Replace the following element
            arrayCopy[replacedIndex] = replacementData;

            // Return the copy
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not remove! Index was outside the bounds of the array!");
            return array;
        }
    }

    // Replaces a specific index in an array with the given replacement data and returns the replaced data, returns a copy
    public static DataType[] Replace(DataType[] array, int replacedIndex, DataType replacementData, out DataType replacedData)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            replacedData = default;
            return array;
        }

        // Make sure the index is within the array bounds
        if (replacedIndex >= 0 && replacedIndex < array.Length)
        {
            // Create a copy of the array 
            DataType[] arrayCopy = Copy(array);

            // Replace the following element
            arrayCopy[replacedIndex] = replacementData;

            // Return the copy
            replacedData = array[replacedIndex];
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not remove! Index was outside the bounds of the array!");
            replacedData = default;
            return array;
        }
    }

    // Replaces the specific indicies in an array with the given replacement data, returns a copy
    public static DataType[] Replace(DataType[] array, int[] index, DataType replacement)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array 
        DataType[] arrayCopy = Copy(array);

        // Replace the following elements
        foreach (int i in index)
        {
            arrayCopy[i] = replacement;
        }

        // Return the copy
        return arrayCopy;
    }

    // Replaces the specific indicies in an array with the given replacement data and return the replaced data, returns a copy
    public static DataType[] Replace(DataType[] array, int[] index, DataType replacement, out DataType[] replacedData)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            replacedData = new DataType[0];
            return array;
        }

        // Create a copy of the array 
        DataType[] arrayCopy = Copy(array);
        replacedData = new DataType[array.Length];
        int arrayIndex = 0;

        // Replace the following elements
        foreach (int i in index)
        {
            replacedData[arrayIndex] = arrayCopy[i];
            arrayCopy[i] = replacement;
            arrayIndex++;
        }

        // Return the copy
        return arrayCopy;
    }

    // Replaces the specific indicies in an array with the matching replacement data, returns a copy
    public static DataType[] Replace(DataType[] array, int[] index, DataType[] replacement)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Check length of index and replacement
        if (index.Length == replacement.Length)
        {
            // Create a copy of the array 
            DataType[] arrayCopy = Copy(array);

            // Replace the following elements
            for (int i = 0; i < index.Length; i++)
            {
                arrayCopy[i] = replacement[i];
            }

            // Return the copy
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not replace! Index and replacement do not have the same length!");
            return array;
        }
    }

    // Replaces the specific indicies in an array with the matching replacement data and return the replaced data, returns a copy
    public static DataType[] Replace(DataType[] array, int[] index, DataType[] replacement, out DataType[] replacedData)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            replacedData = new DataType[0];
            return array;
        }

        // Check length of index and replacement
        if (index.Length == replacement.Length)
        {
            // Create a copy of the array 
            DataType[] arrayCopy = Copy(array);
            replacedData = new DataType[array.Length];
            int arrayIndex = 0;

            // Replace the following elements
            for (int i = 0; i < index.Length; i++)
            {
                replacedData[arrayIndex] = arrayCopy[i];
                arrayCopy[i] = replacement[i];
                arrayIndex++;
            }

            // Return the copy
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not replace! Index and replacement do not have the same length!");
            replacedData = new DataType[0];
            return array;
        }
    }


    // REVERSING ARRAY ELEMENTS

    // Reverses an array, returns a copy
    public static DataType[] Reverse(DataType[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array 
        DataType[] arrayCopy = new DataType[array.Length];

        // Loop through the array and set the copy's elements backwards
        for (int i = 0; i < array.Length; i++)
        {
            // Reverse elements
            arrayCopy[i] = array[array.Length - i - 1];
        }

        return arrayCopy;
    }

    // Reverses an array starting from an index, returns a copy
    public static DataType[] Reverse(DataType[] array, int startingIndex)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array 
        DataType[] arrayCopy = new DataType[array.Length];

        // Loop through the array and set the copy's elements backwards
        for (int i = 0; i < array.Length; i++)
        {
            if (i < startingIndex)
            {
                // Copy elements
                arrayCopy[i] = array[i];
            }
            else
            {
                // Reverse elements
                arrayCopy[i] = array[array.Length - i - 1 + startingIndex];
            }
        }

        return arrayCopy;
    }

    // Reverses an array starting from an index backwards or forwards, returns a copy
    public static DataType[] Reverse(DataType[] array, int startingIndex, bool backwards)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array 
        DataType[] arrayCopy = new DataType[array.Length];

        if (backwards)
        {
            // Loop through the array and set the copy's elements backwards
            for (int i = 0; i < array.Length; i++)
            {
                if (i < startingIndex)
                {
                    // Reverse elements
                    arrayCopy[i] = array[array.Length - i - startingIndex - 2];
                }
                else
                {
                    // Copy elements
                    arrayCopy[i] = array[i];
                }
            }
        }
        else
        {
            // Loop through the array and set the copy's elements backwards
            for (int i = 0; i < array.Length; i++)
            {
                if (i < startingIndex)
                {
                    // Copy elements
                    arrayCopy[i] = array[i];
                }
                else
                {
                    // Reverse elements
                    arrayCopy[i] = array[array.Length - i - 1 + startingIndex];
                }
            }
        }

        return arrayCopy;
    }


    // CHANGING ARRAY SIZE

    // Returns a portion of the given array for only the given length, returns a copy
    public static DataType[] Shorten(DataType[] array, int length)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (length >= 0 && length <= array.Length)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[length];

            // Duplicate the array over to the copy
            System.Array.Copy(array, arrayCopy, length);

            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not shorten! Length was outside the bounds of the array!");
            return array;
        }
    }

    // Returns a portion of the given array for only the given length starting from the first or last element, returns a copy
    public static DataType[] Shorten(DataType[] array, int length, bool backwards)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (length >= 0 && length <= array.Length)
        {
            if (backwards)
            {
                // Create a copy of the array
                DataType[] arrayCopy = new DataType[length];

                // Duplicate the array over to the copy
                System.Array.Copy(array, array.Length - length, arrayCopy, 0, length);

                return arrayCopy;
            }
            else
            {
                // Create a copy of the array
                DataType[] arrayCopy = new DataType[length];

                // Duplicate the array over to the copy
                System.Array.Copy(array, arrayCopy, length);

                return arrayCopy;
            }
        }
        else
        {
            Debug.Assert(false, "Could not shorten! Length was outside the bounds of the array!");
            return array;
        }
    }

    // Returns a portion of the given array from the starting index, returns a copy
    public static DataType[] Slice(DataType[] array, int startingIndex)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (startingIndex >= 0 && startingIndex <= array.Length - 1)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[array.Length - startingIndex];

            // Duplicate the array over to the copy
            System.Array.Copy(array, startingIndex, arrayCopy, 0, array.Length - startingIndex);

            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not slice! Index was outside the bounds of the array!");
            return array;
        }
    }

    // Returns a portion of the given array from or behind the starting index, returns a copy
    public static DataType[] Slice(DataType[] array, int startingIndex, bool backwards)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (startingIndex >= 0 && startingIndex <= array.Length - 1)
        {
            if (backwards)
            {
                // Create a copy of the array
                DataType[] arrayCopy = new DataType[startingIndex];

                // Duplicate the array over to the copy
                System.Array.Copy(array, 0, arrayCopy, 0, startingIndex);

                return arrayCopy;
            }
            else
            {
                // Create a copy of the array
                DataType[] arrayCopy = new DataType[array.Length - startingIndex];

                // Duplicate the array over to the copy
                System.Array.Copy(array, startingIndex, arrayCopy, 0, array.Length - startingIndex);

                return arrayCopy;
            }
        }
        else
        {
            Debug.Assert(false, "Could not slice! Index was outside the bounds of the array!");
            return array;
        }
    }

    // Returns a portion of the given array from the starting index for only the given length, returns a copy
    public static DataType[] Cut(DataType[] array, int startingIndex, int length)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (length >= 0 && length <= array.Length && startingIndex >= 0 && startingIndex <= array.Length - 1 && array.Length - length >= startingIndex)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[length];

            // Duplicate the array over to the copy
            System.Array.Copy(array, startingIndex, arrayCopy, 0, length);

            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not cut! Length or index was outside the bounds of the array!");
            return array;
        }
    }

    // Returns a portion of the given array from or behind the starting index for only the given length, returns a copy
    public static DataType[] Cut(DataType[] array, int startingIndex, int length, bool backwards)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (length >= 0 && length <= array.Length && startingIndex >= 0 && startingIndex <= array.Length - 1 && ((array.Length - length >= startingIndex && !backwards) || (length <= startingIndex && backwards)))
        {
            if (backwards)
            {
                // Create a copy of the array
                DataType[] arrayCopy = new DataType[length];

                // Duplicate the array over to the copy
                System.Array.Copy(array, startingIndex - length, arrayCopy, 0, length);

                return arrayCopy;
            }
            else
            {
                // Create a copy of the array
                DataType[] arrayCopy = new DataType[length];

                // Duplicate the array over to the copy
                System.Array.Copy(array, startingIndex, arrayCopy, 0, length);

                return arrayCopy;
            }
        }
        else
        {
            Debug.Assert(false, "Could not cut! Length or index was outside the bounds of the array!");
            return array;
        }
    }

    // Removes all elements from an array of elements starting from an index, returns a copy
    public static DataType[] Trim(DataType[] array, int trimIndex)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (trimIndex >= 0 && trimIndex < array.Length)
        {
            // Create a copy of the array without any elements starting from the trim index
            DataType[] arrayCopy = new DataType[trimIndex];

            // Duplicate the array over to the copy without the removed elements
            System.Array.Copy(array, arrayCopy, trimIndex);

            // Return a copy of the new array
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not trim! Index was outside the bounds of the array!");
            return array;
        }
    }

    // Removes all elements from an array of elements starting from or behind an index, returns a copy
    public static DataType[] Trim(DataType[] array, int trimIndex, bool backwards)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (trimIndex >= 0 && trimIndex < array.Length)
        {
            if (backwards)
            {
                // Create a copy of the array without any elements before the trim index
                DataType[] arrayCopy = new DataType[array.Length - trimIndex - 1];

                // Duplicate the array over to the copy without the removed elements
                System.Array.Copy(array, trimIndex, arrayCopy, 0, array.Length - trimIndex - 1);

                // Return a copy of the new array
                return arrayCopy;
            }
            else
            {
                // Create a copy of the array without any elements starting from the trim index
                DataType[] arrayCopy = new DataType[trimIndex];

                // Duplicate the array over to the copy without the removed elements
                System.Array.Copy(array, arrayCopy, trimIndex);

                // Return a copy of the new array
                return arrayCopy;
            }
        }
        else
        {
            Debug.Assert(false, "Could not trim! Index was outside the bounds of the array!");
            return array;
        }
    }


    // ODD AND EVEN ARRAY ELEMENTS

    // Returns an array of all odd indicies of the given array
    public static DataType[] Odd(DataType[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array
        DataType[] arrayCopy = new DataType[array.Length / 2];

        // Duplicate the odd indexed elements over to the copy
        int index = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the index is odd
            if (i % 2 == 1)
            {
                arrayCopy[index] = array[i];
                index++;
            }
        }

        // Return a copy of the new array
        return arrayCopy;
    }

    // Returns an array of all even indicies of the given array
    public static DataType[] Even(DataType[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array that is as long as the total number of even values of the array
        DataType[] arrayCopy;
        if (array.Length % 2 == 1)
        {
            // Odd total
            arrayCopy = new DataType[array.Length / 2 + 1];
        }
        else
        {
            // Even total
            arrayCopy = new DataType[array.Length / 2];
        }

        // Duplicate the even indexed elements over to the copy
        int index = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the index is even
            if (i % 2 == 0)
            {
                arrayCopy[index] = array[i];
                index++;
            }
        }

        // Return a copy of the new array
        return arrayCopy;
    }


    // REMOVING NULL OR DEFAULT ELEMENTS

    // Removes any null or default values from an array, returns a copy
    public static DataType[] Clean(DataType[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Initialize index array
        int[] indicies = new int[array.Length];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array and compare the given element with the array's elements
        for (int i = 0; i < array.Length; i++)
        {
            // Matching element found
            if (IsNullOrDefault(array[i]))
            {
                indicies[arrayIndex] = i;
                arrayIndex++;
            }
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        // Loop through the array to add back the unmarked elements
        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        return arrayCopy;
    }

    // Removes any null or empty values from an array and return the indicies, returns a copy
    public static DataType[] Clean(DataType[] array, out int[] removedIndex)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            removedIndex = new int[0];
            return array;
        }

        // Initialize index array
        int[] indicies = new int[array.Length];
        int arrayIndex = 0;

        // Set all indicies to -1 (as they default to 0)
        for (int i = 0; i < indicies.Length; i++)
        {
            indicies[i] = -1;
        }

        // Loop through the array and compare the given element with the array's elements
        for (int i = 0; i < array.Length; i++)
        {
            // Matching element found
            if (IsNullOrDefault(array[i]))
            {
                indicies[arrayIndex] = i;
                arrayIndex++;
            }
        }

        // Create a copy of the array - the number of removed spaces
        DataType[] arrayCopy = new DataType[array.Length - arrayIndex];

        // Loop through the array to add back the unmarked elements
        arrayIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            // Check if the current element is not marked to be removed
            if (!Array<int>.Contains(indicies, i))
            {
                // Copy that element back to the array
                arrayCopy[arrayIndex] = array[i];
                arrayIndex++;
            }
        }

        removedIndex = Array<int>.Trim(indicies, arrayIndex);
        return arrayCopy;
    }


    // NULL OR EMPTY ARRAY

    // Returns true if the array is null
    public static bool IsNull(DataType[] array)
    {
        return array == null;
    }

    // Returns true if the array is empty
    public static bool IsEmpty(DataType[] array)
    {
        if (array == null)
        {
            Debug.Assert(false, "Array is null, not empty!");
            return false;
        }

        return array.Length == 0;
    }

    // Returns true if the array is null or empty
    public static bool IsNullOrEmpty(DataType[] array)
    {
        if (array == null)
        {
            return true;
        }

        return array.Length == 0;
    }


    // NULL OR DEFAULT DATA

    // Returns true if the data is null
    public static bool IsNull(DataType data)
    {
        return data == null;
    }

    // Returns true if the data is default
    public static bool IsDefault(DataType data)
    {
        if (data == null)
        {
            Debug.Assert(false, "Data is null, not empty!");
            return false;
        }

        return data.Equals(default(DataType));
    }

    // Returns true if the data is null or default
    public static bool IsNullOrDefault(DataType data)
    {
        if (data == null)
        {
            return true;
        }

        return data.Equals(default(DataType));
    }


    // SORTING ARRAY ELEMENTS

    // Bubble sort an array with an integer array, returns a copy
    public static DataType[] Sort(DataType[] array, int[] order)
    {
        // Null check
        if (array == null || order == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (order.Length == array.Length)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[array.Length];
            System.Array.Copy(array, arrayCopy, array.Length);

            // Create a copy of the order array
            int[] orderCopy = new int[order.Length];
            System.Array.Copy(order, orderCopy, order.Length);

            // Loop through the array with each element and swap with greater elements using the sorting order
            for (int i = 0; i < orderCopy.Length - 1; i++)
            {
                for (int j = 0; j < orderCopy.Length - i - 1; j++)
                {
                    if (orderCopy[j] > orderCopy[j + 1])
                    {
                        // Store the swapped element
                        DataType swappedElement = arrayCopy[j];

                        // Swap the two elements
                        arrayCopy[j] = arrayCopy[j + 1];
                        arrayCopy[j + 1] = swappedElement;

                        // Store the swapped element's order
                        int swappedElementOrder = orderCopy[j];

                        // Swap the two elements
                        orderCopy[j] = orderCopy[j + 1];
                        orderCopy[j + 1] = swappedElementOrder;
                    }
                }
            }

            // Return a copy of the new array
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not sort! Sorting order length does not match array!");
            return array;
        }
    }

    // Bubble sort an array with an integer array and also returns the sorted order, returns a copy
    public static DataType[] Sort(DataType[] array, int[] order, out int[] sortedOrder)
    {
        // Null check
        if (array == null || order == null)
        {
            Debug.Assert(false, "Array is null!");
            sortedOrder = new int[0];
            return array;
        }

        // Make sure the index is within the array bounds
        if (order.Length == array.Length)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[array.Length];
            System.Array.Copy(array, arrayCopy, array.Length);

            // Create a copy of the order array
            int[] orderCopy = new int[order.Length];
            System.Array.Copy(order, orderCopy, order.Length);

            // Loop through the array with each element and swap with greater elements using the sorting order
            for (int i = 0; i < orderCopy.Length - 1; i++)
            {
                for (int j = 0; j < orderCopy.Length - i - 1; j++)
                {
                    if (orderCopy[j] > orderCopy[j + 1])
                    {
                        // Store the swapped element
                        DataType swappedElement = arrayCopy[j];

                        // Swap the two elements
                        arrayCopy[j] = arrayCopy[j + 1];
                        arrayCopy[j + 1] = swappedElement;

                        // Store the swapped element's order
                        int swappedElementOrder = orderCopy[j];

                        // Swap the two elements
                        orderCopy[j] = orderCopy[j + 1];
                        orderCopy[j + 1] = swappedElementOrder;
                    }
                }
            }

            // Return a copy of the new array and the sorted order
            sortedOrder = orderCopy;
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not sort! Sorting order length does not match array!");
            sortedOrder = order;
            return array;
        }
    }

    // Bubble sort an array with a float array, returns a copy
    public static DataType[] Sort(DataType[] array, float[] order)
    {
        // Null check
        if (array == null || order == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (order.Length == array.Length)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[array.Length];
            System.Array.Copy(array, arrayCopy, array.Length);

            // Create a copy of the order array
            float[] orderCopy = new float[order.Length];
            System.Array.Copy(order, orderCopy, order.Length);

            // Loop through the array with each element and swap with greater elements using the sorting order
            for (int i = 0; i < orderCopy.Length - 1; i++)
            {
                for (int j = 0; j < orderCopy.Length - i - 1; j++)
                {
                    if (orderCopy[j] > orderCopy[j + 1])
                    {
                        // Store the swapped element
                        DataType swappedElement = arrayCopy[j];

                        // Swap the two elements
                        arrayCopy[j] = arrayCopy[j + 1];
                        arrayCopy[j + 1] = swappedElement;

                        // Store the swapped element's order
                        float swappedElementOrder = orderCopy[j];

                        // Swap the two elements
                        orderCopy[j] = orderCopy[j + 1];
                        orderCopy[j + 1] = swappedElementOrder;
                    }
                }
            }

            // Return a copy of the new array
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not sort! Sorting order length does not match array!");
            return array;
        }
    }

    // Bubble sort an array with a float array and also returns the sorted order, returns a copy
    public static DataType[] Sort(DataType[] array, float[] order, out float[] sortedOrder)
    {
        // Null check
        if (array == null || order == null)
        {
            Debug.Assert(false, "Array is null!");
            sortedOrder = new float[0];
            return array;
        }

        // Make sure the index is within the array bounds
        if (order.Length == array.Length)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[array.Length];
            System.Array.Copy(array, arrayCopy, array.Length);

            // Create a copy of the order array
            float[] orderCopy = new float[order.Length];
            System.Array.Copy(order, orderCopy, order.Length);

            // Loop through the array with each element and swap with greater elements using the sorting order
            for (int i = 0; i < orderCopy.Length - 1; i++)
            {
                for (int j = 0; j < orderCopy.Length - i - 1; j++)
                {
                    if (orderCopy[j] > orderCopy[j + 1])
                    {
                        // Store the swapped element
                        DataType swappedElement = arrayCopy[j];

                        // Swap the two elements
                        arrayCopy[j] = arrayCopy[j + 1];
                        arrayCopy[j + 1] = swappedElement;

                        // Store the swapped element's order
                        float swappedElementOrder = orderCopy[j];

                        // Swap the two elements
                        orderCopy[j] = orderCopy[j + 1];
                        orderCopy[j + 1] = swappedElementOrder;
                    }
                }
            }

            // Return a copy of the new array and the sorted order
            sortedOrder = orderCopy;
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not sort! Sorting order length does not match array!");
            sortedOrder = order;
            return array;
        }
    }

    // Bubble sort an array with a boolean array, returns a copy
    public static DataType[] Sort(DataType[] array, bool[] order)
    {
        // Null check
        if (array == null || order == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (order.Length == array.Length)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[array.Length];
            System.Array.Copy(array, arrayCopy, array.Length);

            // Create a copy of the order array as an integer array (0 or 1)
            int[] orderCopy = new int[order.Length];

            for (int i = 0; i < orderCopy.Length; i++)
            {
                if (order[i])
                {
                    orderCopy[i] = 1;
                }
                else
                {
                    orderCopy[i] = 0;
                }
            }

            // Loop through the array with each element and swap with greater elements using the sorting order
            for (int i = 0; i < orderCopy.Length - 1; i++)
            {
                for (int j = 0; j < orderCopy.Length - i - 1; j++)
                {
                    if (orderCopy[j] > orderCopy[j + 1])
                    {
                        // Store the swapped element
                        DataType swappedElement = arrayCopy[j];

                        // Swap the two elements
                        arrayCopy[j] = arrayCopy[j + 1];
                        arrayCopy[j + 1] = swappedElement;

                        // Store the swapped element's order
                        int swappedElementOrder = orderCopy[j];

                        // Swap the two elements
                        orderCopy[j] = orderCopy[j + 1];
                        orderCopy[j + 1] = swappedElementOrder;
                    }
                }
            }

            // Return a copy of the new array
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not sort! Sorting order length does not match array!");
            return array;
        }
    }

    // Bubble sort an array with a reversed boolean array and also returns the sorted order, returns a copy
    public static DataType[] Sort(DataType[] array, bool[] order, out bool[] sortedOrder)
    {
        // Null check
        if (array == null || order == null)
        {
            Debug.Assert(false, "Array is null!");
            sortedOrder = new bool[0];
            return array;
        }

        // Make sure the index is within the array bounds
        if (order.Length == array.Length)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[array.Length];
            System.Array.Copy(array, arrayCopy, array.Length);

            // Create a copy of the order array as an integer array (0 or 1)
            int[] orderCopy = new int[order.Length];

            for (int i = 0; i < orderCopy.Length; i++)
            {
                if (order[i])
                {
                    orderCopy[i] = 1;
                }
                else
                {
                    orderCopy[i] = 0;
                }
            }

            // Loop through the array with each element and swap with greater elements using the sorting order
            for (int i = 0; i < orderCopy.Length - 1; i++)
            {
                for (int j = 0; j < orderCopy.Length - i - 1; j++)
                {
                    if (orderCopy[j] > orderCopy[j + 1])
                    {
                        // Store the swapped element
                        DataType swappedElement = arrayCopy[j];

                        // Swap the two elements
                        arrayCopy[j] = arrayCopy[j + 1];
                        arrayCopy[j + 1] = swappedElement;

                        // Store the swapped element's order
                        int swappedElementOrder = orderCopy[j];

                        // Swap the two elements
                        orderCopy[j] = orderCopy[j + 1];
                        orderCopy[j + 1] = swappedElementOrder;
                    }
                }
            }

            // Create a copy of the order array as a boolean array
            bool[] orderCopy2 = new bool[order.Length];

            for (int i = 0; i < orderCopy.Length; i++)
            {
                if (orderCopy[i] == 0)
                {
                    orderCopy2[i] = false;
                }
                else
                {
                    orderCopy2[i] = true;
                }
            }

            // Return a copy of the new array and the sorted order
            sortedOrder = orderCopy2;
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not sort! Sorting order length does not match array!");
            sortedOrder = order;
            return array;
        }
    }

    // Bubble sort an array with a reversed boolean array, returns a copy
    public static DataType[] Sort(DataType[] array, bool[] order, bool trueFirst)
    {
        // Null check
        if (array == null || order == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (order.Length == array.Length)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[array.Length];
            System.Array.Copy(array, arrayCopy, array.Length);

            // Create a copy of the order array as an integer array (0 or 1)
            int[] orderCopy = new int[order.Length];

            for (int i = 0; i < orderCopy.Length; i++)
            {
                if (order[i])
                {
                    orderCopy[i] = 1;
                }
                else
                {
                    orderCopy[i] = 0;
                }
            }

            // Loop through the array with each element and swap with greater elements using the sorting order
            for (int i = 0; i < orderCopy.Length - 1; i++)
            {
                for (int j = 0; j < orderCopy.Length - i - 1; j++)
                {
                    if (orderCopy[j] > orderCopy[j + 1])
                    {
                        // Store the swapped element
                        DataType swappedElement = arrayCopy[j];

                        // Swap the two elements
                        arrayCopy[j] = arrayCopy[j + 1];
                        arrayCopy[j + 1] = swappedElement;

                        // Store the swapped element's order
                        int swappedElementOrder = orderCopy[j];

                        // Swap the two elements
                        orderCopy[j] = orderCopy[j + 1];
                        orderCopy[j + 1] = swappedElementOrder;
                    }
                }
            }

            // Return a copy of the new array
            if (trueFirst)
            {
                return Reverse(arrayCopy);
            }
            else
            {
                return arrayCopy;
            }
        }
        else
        {
            Debug.Assert(false, "Could not sort! Sorting order length does not match array!");
            return array;
        }
    }

    // Bubble sort an array with a boolean array and also returns the sorted order, returns a copy
    public static DataType[] Sort(DataType[] array, bool[] order, out bool[] sortedOrder, bool trueFirst)
    {
        // Null check
        if (array == null || order == null)
        {
            Debug.Assert(false, "Array is null!");
            sortedOrder = new bool[0];
            return array;
        }

        // Make sure the index is within the array bounds
        if (order.Length == array.Length)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[array.Length];
            System.Array.Copy(array, arrayCopy, array.Length);

            // Create a copy of the order array as an integer array (0 or 1)
            int[] orderCopy = new int[order.Length];

            for (int i = 0; i < orderCopy.Length; i++)
            {
                if (order[i])
                {
                    orderCopy[i] = 1;
                }
                else
                {
                    orderCopy[i] = 0;
                }
            }

            // Loop through the array with each element and swap with greater elements using the sorting order
            for (int i = 0; i < orderCopy.Length - 1; i++)
            {
                for (int j = 0; j < orderCopy.Length - i - 1; j++)
                {
                    if (orderCopy[j] > orderCopy[j + 1])
                    {
                        // Store the swapped element
                        DataType swappedElement = arrayCopy[j];

                        // Swap the two elements
                        arrayCopy[j] = arrayCopy[j + 1];
                        arrayCopy[j + 1] = swappedElement;

                        // Store the swapped element's order
                        int swappedElementOrder = orderCopy[j];

                        // Swap the two elements
                        orderCopy[j] = orderCopy[j + 1];
                        orderCopy[j + 1] = swappedElementOrder;
                    }
                }
            }

            // Create a copy of the order array as a boolean array
            bool[] orderCopy2 = new bool[order.Length];

            for (int i = 0; i < orderCopy.Length; i++)
            {
                if (orderCopy[i] == 0)
                {
                    orderCopy2[i] = false;
                }
                else
                {
                    orderCopy2[i] = true;
                }
            }

            // Return a copy of the new array and the sorted order
            if (trueFirst)
            {
                sortedOrder = Array<bool>.Reverse(orderCopy2);
                return Reverse(arrayCopy);
            }
            else
            {
                sortedOrder = orderCopy2;
                return arrayCopy;
            }
        }
        else
        {
            Debug.Assert(false, "Could not sort! Sorting order length does not match array!");
            sortedOrder = order;
            return array;
        }
    }

    // Bubble sort an array with a character array, returns a copy
    public static DataType[] Sort(DataType[] array, char[] order)
    {
        // Null check
        if (array == null || order == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (order.Length == array.Length)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[array.Length];
            System.Array.Copy(array, arrayCopy, array.Length);

            // Create a copy of the order array as an integer array (numeric character code)
            int[] orderCopy = new int[order.Length];

            for (int i = 0; i < orderCopy.Length; i++)
            {
                orderCopy[i] = order[i];
            }

            // Loop through the array with each element and swap with greater elements using the sorting order
            for (int i = 0; i < orderCopy.Length - 1; i++)
            {
                for (int j = 0; j < orderCopy.Length - i - 1; j++)
                {
                    if (orderCopy[j] > orderCopy[j + 1])
                    {
                        // Store the swapped element
                        DataType swappedElement = arrayCopy[j];

                        // Swap the two elements
                        arrayCopy[j] = arrayCopy[j + 1];
                        arrayCopy[j + 1] = swappedElement;

                        // Store the swapped element's order
                        int swappedElementOrder = orderCopy[j];

                        // Swap the two elements
                        orderCopy[j] = orderCopy[j + 1];
                        orderCopy[j + 1] = swappedElementOrder;
                    }
                }
            }

            // Return a copy of the new array
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not sort! Sorting order length does not match array!");
            return array;
        }
    }

    // Bubble sort an array with a character array and also returns the sorted order, returns a copy
    public static DataType[] Sort(DataType[] array, char[] order, out char[] sortedOrder)
    {
        // Null check
        if (array == null || order == null)
        {
            Debug.Assert(false, "Array is null!");
            sortedOrder = new char[0];
            return array;
        }

        // Make sure the index is within the array bounds
        if (order.Length == array.Length)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[array.Length];
            System.Array.Copy(array, arrayCopy, array.Length);

            // Create a copy of the order array as an integer array (numeric character code)
            int[] orderCopy = new int[order.Length];

            for (int i = 0; i < orderCopy.Length; i++)
            {
                orderCopy[i] = order[i];
            }

            // Loop through the array with each element and swap with greater elements using the sorting order
            for (int i = 0; i < orderCopy.Length - 1; i++)
            {
                for (int j = 0; j < orderCopy.Length - i - 1; j++)
                {
                    if (orderCopy[j] > orderCopy[j + 1])
                    {
                        // Store the swapped element
                        DataType swappedElement = arrayCopy[j];

                        // Swap the two elements
                        arrayCopy[j] = arrayCopy[j + 1];
                        arrayCopy[j + 1] = swappedElement;

                        // Store the swapped element's order
                        int swappedElementOrder = orderCopy[j];

                        // Swap the two elements
                        orderCopy[j] = orderCopy[j + 1];
                        orderCopy[j + 1] = swappedElementOrder;
                    }
                }
            }

            // Create a copy of the order array as a char array
            char[] orderCopy2 = new char[order.Length];

            for (int i = 0; i < orderCopy.Length; i++)
            {
                orderCopy2[i] = (char)orderCopy[i];
            }

            // Return a copy of the new array and the sorted order
            sortedOrder = orderCopy2;
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not sort! Sorting order length does not match array!");
            sortedOrder = order;
            return array;
        }
    }

    // Bubble sort an array with a character array as lowercase, returns a copy
    public static DataType[] Sort(DataType[] array, char[] order, bool sortLower)
    {
        // Null check
        if (array == null || order == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Make sure the index is within the array bounds
        if (order.Length == array.Length)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[array.Length];
            System.Array.Copy(array, arrayCopy, array.Length);

            // Create a copy of the order array as an integer array (numeric character code)
            int[] orderCopy = new int[order.Length];

            if (sortLower)
            {
                for (int i = 0; i < orderCopy.Length; i++)
                {
                    orderCopy[i] = new string(order).ToLower()[i];
                }
            }
            else
            {
                for (int i = 0; i < orderCopy.Length; i++)
                {
                    orderCopy[i] = order[i];
                }
            }


            // Loop through the array with each element and swap with greater elements using the sorting order
            for (int i = 0; i < orderCopy.Length - 1; i++)
            {
                for (int j = 0; j < orderCopy.Length - i - 1; j++)
                {
                    if (orderCopy[j] > orderCopy[j + 1])
                    {
                        // Store the swapped element
                        DataType swappedElement = arrayCopy[j];

                        // Swap the two elements
                        arrayCopy[j] = arrayCopy[j + 1];
                        arrayCopy[j + 1] = swappedElement;

                        // Store the swapped element's order
                        int swappedElementOrder = orderCopy[j];

                        // Swap the two elements
                        orderCopy[j] = orderCopy[j + 1];
                        orderCopy[j + 1] = swappedElementOrder;
                    }
                }
            }

            // Return a copy of the new array
            return arrayCopy;
        }
        else
        {
            Debug.Assert(false, "Could not sort! Sorting order length does not match array!");
            return array;
        }
    }

    // Bubble sort an array with a character array as lowercase and also returns the sorted order, returns a copy
    public static DataType[] Sort(DataType[] array, char[] order, out char[] sortedOrder, bool sortLower)
    {
        // Null check
        if (array == null || order == null)
        {
            Debug.Assert(false, "Array is null!");
            sortedOrder = new char[0];
            return array;
        }

        // Make sure the index is within the array bounds
        if (order.Length == array.Length)
        {
            // Create a copy of the array
            DataType[] arrayCopy = new DataType[array.Length];
            System.Array.Copy(array, arrayCopy, array.Length);

            // Create a copy of the order array as an integer array (numeric character code)
            int[] orderCopy = new int[order.Length];

            if (sortLower)
            {
                for (int i = 0; i < orderCopy.Length; i++)
                {
                    orderCopy[i] = new string(order).ToLower()[i];
                }

                // Create a copy of the order array as a char array
                char[] orderCopy2 = new char[order.Length];
                System.Array.Copy(order, orderCopy2, order.Length);

                // Loop through the array with each element and swap with greater elements using the sorting order
                for (int i = 0; i < orderCopy.Length - 1; i++)
                {
                    for (int j = 0; j < orderCopy.Length - i - 1; j++)
                    {
                        if (orderCopy[j] > orderCopy[j + 1])
                        {
                            // Store the swapped element
                            DataType swappedElement = arrayCopy[j];

                            // Swap the two elements
                            arrayCopy[j] = arrayCopy[j + 1];
                            arrayCopy[j + 1] = swappedElement;

                            // Store the swapped element's order
                            int swappedElementOrder = orderCopy[j];

                            // Swap the two elements
                            orderCopy[j] = orderCopy[j + 1];
                            orderCopy[j + 1] = swappedElementOrder;

                            // Store the swapped element's order
                            char swappedElementOrder2 = orderCopy2[j];

                            // Swap the two elements
                            orderCopy2[j] = orderCopy2[j + 1];
                            orderCopy2[j + 1] = swappedElementOrder2;
                        }
                    }
                }

                // Return a copy of the new array and the sorted order
                sortedOrder = orderCopy2;
                return arrayCopy;
            }
            else
            {
                for (int i = 0; i < orderCopy.Length; i++)
                {
                    orderCopy[i] = order[i];
                }

                // Loop through the array with each element and swap with greater elements using the sorting order
                for (int i = 0; i < orderCopy.Length - 1; i++)
                {
                    for (int j = 0; j < orderCopy.Length - i - 1; j++)
                    {
                        if (orderCopy[j] > orderCopy[j + 1])
                        {
                            // Store the swapped element
                            DataType swappedElement = arrayCopy[j];

                            // Swap the two elements
                            arrayCopy[j] = arrayCopy[j + 1];
                            arrayCopy[j + 1] = swappedElement;

                            // Store the swapped element's order
                            int swappedElementOrder = orderCopy[j];

                            // Swap the two elements
                            orderCopy[j] = orderCopy[j + 1];
                            orderCopy[j + 1] = swappedElementOrder;
                        }
                    }
                }

                // Create a copy of the order array as a char array
                char[] orderCopy2 = new char[order.Length];

                for (int i = 0; i < orderCopy.Length; i++)
                {
                    orderCopy2[i] = (char)orderCopy[i];
                }

                // Return a copy of the new array and the sorted order
                sortedOrder = orderCopy2;
                return arrayCopy;
            }
        }
        else
        {
            Debug.Assert(false, "Could not sort! Sorting order length does not match array!");
            sortedOrder = order;
            return array;
        }
    }

    // Bubble sort an array with a string, returns a copy
    public static DataType[] Sort(DataType[] array, string String)
    {
        // Null check
        if (array == null || String == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Return a copy of the new array
        return Sort(array, String.ToCharArray());
    }

    // Bubble sort an array with a string and also returns the sorted order, returns a copy
    public static DataType[] Sort(DataType[] array, string String, out string sortedOrder)
    {
        // Null check
        if (array == null || String == null)
        {
            Debug.Assert(false, "Array is null!");
            sortedOrder = "";
            return array;
        }

        // Return a copy of the new array and the sorted order
        char[] sortedCharArray;

        DataType[] arrayCopy = Sort(array, String.ToCharArray(), out sortedCharArray);

        sortedOrder = new string(sortedCharArray);

        return arrayCopy;
    }

    // Bubble sort an array with a string as lowercase, returns a copy
    public static DataType[] Sort(DataType[] array, string String, bool sortLower)
    {
        // Null check
        if (array == null || String == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Return a copy of the new array
        if (sortLower)
        {
            return Sort(array, String.ToLower().ToCharArray());
        }
        else
        {
            return Sort(array, String.ToCharArray());
        }
    }

    // Bubble sort an array with a string as lowercase and also returns the sorted order, returns a copy
    public static DataType[] Sort(DataType[] array, string String, out string sortedOrder, bool sortLower)
    {
        // Null check
        if (array == null || String == null)
        {
            Debug.Assert(false, "Array is null!");
            sortedOrder = "";
            return array;
        }

        // Initalize array
        char[] sortedCharArray;

        // Return a copy of the new array and the sorted order
        if (sortLower)
        {
            DataType[] arrayCopy = Sort(array, String.ToLower().ToCharArray(), out sortedCharArray, true);

            sortedOrder = new string(sortedCharArray);

            return arrayCopy;
        }
        else
        {
            DataType[] arrayCopy = Sort(array, String.ToCharArray(), out sortedCharArray);

            sortedOrder = new string(sortedCharArray);

            return arrayCopy;
        }
    }

    // Bubble sort an integer array, returns a copy
    public static int[] Sort(int[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array
        int[] arrayCopy = new int[array.Length];
        System.Array.Copy(array, arrayCopy, array.Length);

        // Loop through the array with each element and swap with greater elements
        for (int i = 0; i < arrayCopy.Length - 1; i++)
        {
            for (int j = 0; j < arrayCopy.Length - i - 1; j++)
            {
                if (arrayCopy[j] > arrayCopy[j + 1])
                {
                    // Store the swapped element
                    int swappedElement = arrayCopy[j];

                    // Swap the two elements
                    arrayCopy[j] = arrayCopy[j + 1];
                    arrayCopy[j + 1] = swappedElement;
                }
            }
        }

        // Return a copy of the new array
        return arrayCopy;
    }

    // Bubble sort a float array, returns a copy
    public static float[] Sort(float[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array
        float[] arrayCopy = new float[array.Length];
        System.Array.Copy(array, arrayCopy, array.Length);

        // Loop through the array with each element and swap with greater elements
        for (int i = 0; i < arrayCopy.Length - 1; i++)
        {
            for (int j = 0; j < arrayCopy.Length - i - 1; j++)
            {
                if (arrayCopy[j] > arrayCopy[j + 1])
                {
                    // Store the swapped element
                    float swappedElement = arrayCopy[j];

                    // Swap the two elements
                    arrayCopy[j] = arrayCopy[j + 1];
                    arrayCopy[j + 1] = swappedElement;
                }
            }
        }

        // Return a copy of the new array
        return arrayCopy;
    }

    // Bubble sort a boolean array, returns a copy
    public static bool[] Sort(bool[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array as an integer array (0 or 1)
        int[] arrayCopy = new int[array.Length];

        for (int i = 0; i < arrayCopy.Length; i++)
        {
            if (array[i])
            {
                arrayCopy[i] = 1;
            }
            else
            {
                arrayCopy[i] = 0;
            }
        }

        // Return a copy of the new array
        return Array<bool>.Sort(array, arrayCopy);
    }

    // Bubble sort a boolean array, returns a reversed copy
    public static bool[] Sort(bool[] array, bool trueFirst)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array as an integer array (0 or 1)
        int[] arrayCopy = new int[array.Length];

        for (int i = 0; i < arrayCopy.Length; i++)
        {
            if (array[i])
            {
                arrayCopy[i] = 1;
            }
            else
            {
                arrayCopy[i] = 0;
            }
        }

        // Return a copy of the new array
        if (trueFirst)
        {
            return Array<bool>.Reverse(Array<bool>.Sort(array, arrayCopy));
        }
        else
        {
            return Array<bool>.Sort(array, arrayCopy);
        }
    }

    // Bubble sort a character array, returns a copy
    public static char[] Sort(char[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array as an integer array (numeric character code)
        int[] arrayCopy = new int[array.Length];

        for (int i = 0; i < arrayCopy.Length; i++)
        {
            arrayCopy[i] = array[i];
        }

        // Return a copy of the new array
        return Array<char>.Sort(array, arrayCopy);
    }

    // Bubble sort a character array as lowercase, returns a copy
    public static char[] Sort(char[] array, bool sortLower)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array as an integer array (numeric character code)
        int[] arrayCopy = new int[array.Length];

        if (sortLower)
        {
            for (int i = 0; i < arrayCopy.Length; i++)
            {
                arrayCopy[i] = new string(array).ToLower()[i];
            }
        }
        else
        {
            for (int i = 0; i < arrayCopy.Length; i++)
            {
                arrayCopy[i] = array[i];
            }
        }

        // Return a copy of the new array
        return Array<char>.Sort(array, arrayCopy);
    }

    // Bubble sort a string, returns a copy
    public static string Sort(string String)
    {
        // Null check
        if (String == null)
        {
            Debug.Assert(false, "String is null!");
            return String;
        }

        // Return a copy of the new array
        return new string(Sort(String.ToCharArray()));
    }

    // Bubble sort a string as lowercase, returns a copy
    public static string Sort(string String, bool sortLower)
    {
        // Null check
        if (String == null)
        {
            Debug.Assert(false, "String is null!");
            return String;
        }

        // Return a copy of the new array
        if (sortLower)
        {
            return new string(Array<char>.Sort(String.ToCharArray(), String.ToLower()));
        }
        else
        {
            return new string(Sort(String.ToCharArray()));
        }
    }
}

// New array functions used just for sorting specific data types.
public static class Array
{
    // SORTING ARRAY ELEMENTS

    // Bubble sort an integer array, returns a copy
    public static int[] Sort(int[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array
        int[] arrayCopy = new int[array.Length];
        System.Array.Copy(array, arrayCopy, array.Length);

        // Loop through the array with each element and swap with greater elements
        for (int i = 0; i < arrayCopy.Length - 1; i++)
        {
            for (int j = 0; j < arrayCopy.Length - i - 1; j++)
            {
                if (arrayCopy[j] > arrayCopy[j + 1])
                {
                    // Store the swapped element
                    int swappedElement = arrayCopy[j];

                    // Swap the two elements
                    arrayCopy[j] = arrayCopy[j + 1];
                    arrayCopy[j + 1] = swappedElement;
                }
            }
        }

        // Return a copy of the new array
        return arrayCopy;
    }

    // Bubble sort a float array, returns a copy
    public static float[] Sort(float[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array
        float[] arrayCopy = new float[array.Length];
        System.Array.Copy(array, arrayCopy, array.Length);

        // Loop through the array with each element and swap with greater elements
        for (int i = 0; i < arrayCopy.Length - 1; i++)
        {
            for (int j = 0; j < arrayCopy.Length - i - 1; j++)
            {
                if (arrayCopy[j] > arrayCopy[j + 1])
                {
                    // Store the swapped element
                    float swappedElement = arrayCopy[j];

                    // Swap the two elements
                    arrayCopy[j] = arrayCopy[j + 1];
                    arrayCopy[j + 1] = swappedElement;
                }
            }
        }

        // Return a copy of the new array
        return arrayCopy;
    }

    // Bubble sort a boolean array, returns a copy
    public static bool[] Sort(bool[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array as an integer array (0 or 1)
        int[] arrayCopy = new int[array.Length];

        for (int i = 0; i < arrayCopy.Length; i++)
        {
            if (array[i])
            {
                arrayCopy[i] = 1;
            }
            else
            {
                arrayCopy[i] = 0;
            }
        }

        // Return a copy of the new array
        return Array<bool>.Sort(array, arrayCopy);
    }

    // Bubble sort a boolean array, returns a reversed copy
    public static bool[] Sort(bool[] array, bool trueFirst)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array as an integer array (0 or 1)
        int[] arrayCopy = new int[array.Length];

        for (int i = 0; i < arrayCopy.Length; i++)
        {
            if (array[i])
            {
                arrayCopy[i] = 1;
            }
            else
            {
                arrayCopy[i] = 0;
            }
        }

        // Return a copy of the new array
        if (trueFirst)
        {
            return Array<bool>.Reverse(Array<bool>.Sort(array, arrayCopy));
        }
        else
        {
            return Array<bool>.Sort(array, arrayCopy);
        }
    }

    // Bubble sort a character array, returns a copy
    public static char[] Sort(char[] array)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array as an integer array (numeric character code)
        int[] arrayCopy = new int[array.Length];

        for (int i = 0; i < arrayCopy.Length; i++)
        {
            arrayCopy[i] = array[i];
        }

        // Return a copy of the new array
        return Array<char>.Sort(array, arrayCopy);
    }

    // Bubble sort a character array as lowercase, returns a copy
    public static char[] Sort(char[] array, bool sortLower)
    {
        // Null check
        if (array == null)
        {
            Debug.Assert(false, "Array is null!");
            return array;
        }

        // Create a copy of the array as an integer array (numeric character code)
        int[] arrayCopy = new int[array.Length];

        if (sortLower)
        {
            for (int i = 0; i < arrayCopy.Length; i++)
            {
                arrayCopy[i] = new string(array).ToLower()[i];
            }
        }
        else
        {
            for (int i = 0; i < arrayCopy.Length; i++)
            {
                arrayCopy[i] = array[i];
            }
        }

        // Return a copy of the new array
        return Array<char>.Sort(array, arrayCopy);
    }

    // Bubble sort a string, returns a copy
    public static string Sort(string String)
    {
        // Null check
        if (String == null)
        {
            Debug.Assert(false, "String is null!");
            return String;
        }

        // Return a copy of the new array
        return new string(Sort(String.ToCharArray()));
    }

    // Bubble sort a string as lowercase, returns a copy
    public static string Sort(string String, bool sortLower)
    {
        // Null check
        if (String == null)
        {
            Debug.Assert(false, "String is null!");
            return String;
        }

        // Return a copy of the new array
        if (sortLower)
        {
            return new string(Array<char>.Sort(String.ToCharArray(), String.ToLower()));
        }
        else
        {
            return new string(Sort(String.ToCharArray()));
        }
    }
}
