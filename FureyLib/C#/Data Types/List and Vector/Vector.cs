
// Vector Data Type Class
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/vector/vector/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=net-8.0

using System.Collections;

// Data type used for sorting
using SortType = System.Single;

/// <summary>
/// Vector container class.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class Vector<DataType> : IEnumerable
{
    // VECTOR VARIABLES

    /// <summary>
    /// The array of the vector's data
    /// </summary>
    private DataType[] vectorData = new DataType[0];

    /// <summary>
    /// The current number of elements in the array holding data
    /// </summary>
    private int vectorCount = 0;

    /// <summary>
    /// The current maximum size of the array before needing to expand
    /// </summary>
    private int vectorCapacity = 1;

    /// <summary>
    /// The number of array expansions
    /// </summary>
    private int vectorExpansions = 0;

    /// <summary>
    /// Readonly count variable
    /// </summary>
    public int Count
    {
        get
        {
            return vectorCount;
        }
    }


    // REALLOCATE MEMORY

    /// <summary>
    /// Expands the capacity based on how many times it has been expanded
    /// </summary>
    /// <returns></returns>
    public Vector<DataType> Reallocate()
    {
        // Advance the number of expansions
        vectorExpansions++;

        // Duplicate the vector
        DataType[] temp = new DataType[vectorCount];

        for (int i = 0; i < vectorCount; i++)
        {
            temp[i] = vectorData[i];
        }

        // Allocate new space for the vector
        vectorCapacity *= 2;

        vectorData = new DataType[vectorCapacity];

        // Place the data back into the vector
        for (int i = 0; i < vectorCount; i++)
        {
            vectorData[i] = temp[i];
        }

        return this;
    }


    // TO ARRAY

    /// <summary>
    /// Returns an array of the current vector
    /// </summary>
    /// <returns></returns>
    public DataType[] ToArray()
    {
        // Copy the vector into an array
        DataType[] newArray = new DataType[vectorCount];

        for (int i = 0; i < vectorCount; i++)
        {
            newArray[i] = vectorData[i];
        }

        return newArray;
    }


    // VECTOR EQUALITY

    /// <summary>
    /// Check if another vector is equal to this vector
    /// </summary>
    /// <param name="comparedVector"></param>
    /// <returns></returns>
    public bool Equals(Vector<DataType> comparedVector)
    {
        // Check if the sizes are equal
        if (vectorCount != comparedVector.vectorCount)
        {
            return false;
        }

        // Loop through each element to check if they are not equal
        for (int i = 0; i < vectorCount; i++)
        {
            // Are they not equal
            if (!vectorData[i].Equals(comparedVector[i]))
            {
                return false;
            }
        }

        // The vectors are equal
        return true;
    }

    /// <summary>
    /// Check if another vector is equal to this vector
    /// </summary>
    /// <param name="vector"></param>
    /// <param name="comparedVector"></param>
    /// <returns></returns>
    public static bool operator ==(Vector<DataType> vector, Vector<DataType> comparedVector)
    {
        return vector.Equals(comparedVector);
    }

    /// <summary>
    /// Check if another vector is not equal to this vector
    /// </summary>
    /// <param name="vector"></param>
    /// <param name="comparedVector"></param>
    /// <returns></returns>
    public static bool operator !=(Vector<DataType> vector, Vector<DataType> comparedVector)
    {
        return !vector.Equals(comparedVector);
    }


    // ITERATORS

    /// <summary>
    /// Return the beginning data
    /// </summary>
    /// <returns></returns>
    public DataType Begin()
    {
        return vectorData[0];
    }

    /// <summary>
    /// Return the end data
    /// </summary>
    /// <returns></returns>
    public DataType End()
    {
        return vectorData[vectorCount - 1];
    }


    // CAPACITY

    /// <summary>
    /// Return the current size of the vector
    /// </summary>
    /// <returns></returns>
    public int Size()
    {
        return vectorCount;
    }

    /// <summary>
    /// Return the current size of the vector
    /// </summary>
    /// <returns></returns>
    public int Length()
    {
        return vectorCount;
    }

    /// <summary>
    /// Resizes the vector's size and removes out of bounds data or expands if necessary
    /// </summary>
    /// <param name="newSize"></param>
    /// <returns></returns>
    public Vector<DataType> Resize(int newSize)
    {
        // Check if the new size is identical
        if (vectorCount == newSize)
        {
            return this;
        }

        // Duplicate the current vector
        DataType[] temp = new DataType[vectorCount];

        for (int i = 0; i < vectorCount; i++)
        {
            temp[i] = vectorData[i];
        }

        // Expand the vector if needed
        if (newSize > vectorCapacity)
        {
            Reallocate();
        }

        // Allocate new space for the vector
        vectorData = new DataType[vectorCapacity];

        vectorCount = newSize;

        // Place the data back into the vector
        for (int i = 0; i < vectorCount; i++)
        {
            vectorData[i] = temp[i];
        }

        return this;
    }

    /// <summary>
    /// Return the maximum capacity of the vector before expanding
    /// </summary>
    /// <returns></returns>
    public int Capacity()
    {
        return vectorCapacity;
    }

    /// <summary>
    /// Return the maximum capacity of the vector before expanding
    /// </summary>
    /// <returns></returns>
    public int MaxSize()
    {
        return Capacity();
    }

    /// <summary>
    /// Return whether the vector is empty
    /// </summary>
    /// <returns></returns>
    public bool Empty()
    {
        return vectorCount == 0;
    }

    /// <summary>
    /// Return whether the vector is empty
    /// </summary>
    /// <returns></returns>
    public bool IsEmpty()
    {
        return Empty();
    }

    /// <summary>
    /// Expands the vector's capacity enough to hold the given amount (does not reduce the capacity)
    /// </summary>
    /// <param name="newCapacity"></param>
    /// <returns></returns>
    public Vector<DataType> Reserve(int newCapacity)
    {
        // Check if the new capacity is less
        if (newCapacity <= vectorCapacity)
        {
            return this;
        }

        // Advance the number of expansions
        vectorExpansions++;

        // Duplicate the current vector
        DataType[] temp = new DataType[vectorCount];

        for (int i = 0; i < vectorCount; i++)
        {
            temp[i] = vectorData[i];
        }

        // Allocate new space for the vector
        vectorCapacity = newCapacity;

        vectorData = new DataType[vectorCapacity];

        // Place the data back into the vector
        for (int i = 0; i < vectorCount; i++)
        {
            vectorData[i] = temp[i];
        }

        return this;
    }

    /// <summary>
    /// Expands the vector's capacity enough to hold the given amount (does not reduce the capacity)
    /// </summary>
    /// <param name="newCapacity"></param>
    /// <returns></returns>
    public Vector<DataType> EnsureCapacity(int newCapacity)
    {
        return Reserve(newCapacity);
    }

    /// <summary>
    /// Shrinks the capacity to the size
    /// </summary>
    /// <returns></returns>
    public Vector<DataType> ShrinkToFit()
    {
        // Duplicate the current vector
        DataType[] temp = new DataType[vectorCount];

        for (int i = 0; i < vectorCount; i++)
        {
            temp[i] = vectorData[i];
        }

        // Allocate new space for the vector
        vectorCapacity = vectorCount;

        vectorData = new DataType[vectorCapacity];

        // Place the data back into the vector
        for (int i = 0; i < vectorCount; i++)
        {
            vectorData[i] = temp[i];
        }

        // Reset the number of resizes
        vectorExpansions = 0;

        return this;
    }

    /// <summary>
    /// Shrinks the capacity to the size
    /// </summary>
    /// <returns></returns>
    public Vector<DataType> TrimExcess()
    {
        return ShrinkToFit();
    }

    /// <summary>
    /// Shrinks the capacity to the size
    /// </summary>
    /// <returns></returns>
    public Vector<DataType> Clean()
    {
        return ShrinkToFit();
    }

    /// <summary>
    /// Return the total number of expansions
    /// </summary>
    /// <returns></returns>
    public int Expansions()
    {
        return vectorExpansions;
    }

    /// <summary>
    /// Return the total number of expansions
    /// </summary>
    /// <returns></returns>
    public int Reallocations()
    {
        return Expansions();
    }

    /// <summary>
    /// Expands the vector's capacity by the given amount
    /// </summary>
    /// <param name="numberOfSpaces"></param>
    /// <returns></returns>
    public Vector<DataType> Expand(int numberOfSpaces)
    {
        return Reserve(vectorCapacity + numberOfSpaces);
    }


    // ELEMENT ACCESS

    /// <summary>
    /// Returns the element at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType At(int index)
    {
        return vectorData[index];
    }

    /// <summary>
    /// Returns the element at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType Get(int index)
    {
        return At(index);
    }

    /// <summary>
    /// Returns the element at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType Data(int index)
    {
        return At(index);
    }

    /// <summary>
    /// Returns the element at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType this[int index]
    {
        get => Get(index);
        set => Set(index, value);
    }

    /// <summary>
    /// Returns the first element in the vector
    /// </summary>
    /// <returns></returns>
    public DataType Front()
    {
        return vectorData[0];
    }

    /// <summary>
    /// Returns the first element in the vector
    /// </summary>
    /// <returns></returns>
    public DataType Back()
    {
        return vectorData[vectorCount - 1];
    }


    // MODIFIERS

    /// <summary>
    /// Assigns this vector's elements and capacity to the elements and capacity of another vector
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Vector<DataType> Assign(Vector<DataType> newData)
    {
        // Store the vector's size values
        vectorCount = newData.Size();

        vectorCapacity = vectorCount;

        vectorExpansions = 0;

        // Allocate the space from the new vector
        vectorData = new DataType[vectorCapacity];

        // Place the data back into the vector
        for (int i = 0; i < vectorCount; i++)
        {
            vectorData[i] = newData[i];
        }

        return this;
    }

    /// <summary>
    /// Adds a new element at the front of the vector
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    Vector<DataType> Push(DataType newData)
    {
        // Expand the vector if needed
        if (vectorCount + 1 > vectorCapacity)
        {
            Reallocate();
        }

        // Increase the vector size
        vectorCount++;

        // Shift vector elements forward
        for (int i = vectorCount - 1; i >= 1; i--)
        {
            vectorData[i] = vectorData[i - 1];
        }

        // Set the first element to the new data
        vectorData[0] = newData;

        return this;
    }

    /// <summary>
    /// Adds a new element at the front of the vector
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Vector<DataType> Enqueue(DataType newData)
    {
        return Push(newData);
    }

    /// <summary>
    /// Adds a new element at the front of the vector
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Vector<DataType> AddFront(DataType newData)
    {
        return Push(newData);
    }

    /// <summary>
    /// Adds a new element at the end of the vector
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Vector<DataType> PushBack(DataType newData)
    {
        // Expand the vector if needed
        if (vectorCount + 1 > vectorCapacity)
        {
            Reallocate();
        }

        // Increase the vector size
        vectorCount++;

        // Sets the last element to the new data
        vectorData[vectorCount - 1] = newData;

        return this;
    }

    /// <summary>
    /// Adds a new element at the end of the vector
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Vector<DataType> Add(DataType newData)
    {
        return PushBack(newData);
    }

    /// <summary>
    /// Remove and return the first element of the vector
    /// </summary>
    /// <returns></returns>
    public DataType Pop()
    {
        // Decrease the vector size if possible
        if (vectorCount == 0)
        {
            return vectorData[0];
        }

        vectorCount--;

        // Store the removed data
        DataType newData = vectorData[0];

        // Shift vector elements backward
        for (int i = 1; i <= vectorCount; i++)
        {
            vectorData[i - 1] = vectorData[i];
        }

        return newData;
    }

    /// <summary>
    /// Remove and return the first element of the vector
    /// </summary>
    /// <returns></returns>
    public DataType Dequeue()
    {
        return Pop();
    }

    /// <summary>
    /// Remove and return the last element of the vector
    /// </summary>
    /// <returns></returns>
    public DataType PopBack()
    {
        // Decrease the vector size if possible
        if (vectorCount == 0)
        {
            return vectorData[0];
        }

        vectorCount--;

        return vectorData[vectorCount];
    }

    /// <summary>
    /// Adds a new element in the vector at a given index and shift following elements forward
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Vector<DataType> Insert(int index, DataType newData)
    {
        // Check for out of bounds
        if (index < 0 || index >= vectorCount)
        {
            return this;
        }

        // Expand the vector if needed
        if (vectorCount + 1 > vectorCapacity)
        {
            Reallocate();
        }

        // Increase the vector size
        vectorCount++;

        // Shift elements at and past the new index forward
        for (int i = vectorCount - 1; i >= index; i--)
        {
            vectorData[i] = vectorData[i - 1];
        }

        // Replace the starting index with the new data
        vectorData[index] = newData;

        return this;
    }

    /// <summary>
    /// Removes a element in the vector at a given index and shift following elements back
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public Vector<DataType> Erase(int index)
    {
        // Check for out of bounds
        if (index < 0 || index >= vectorCount)
        {
            return this;
        }

        // Decrease the vector size
        vectorCount--;

        // Shift elements past the new index backward
        for (int i = index + 1; i <= vectorCount; i++)
        {
            vectorData[i - 1] = vectorData[i];
        }

        return this;
    }

    /// <summary>
    /// Removes a element in the vector at a given index and shift following elements back
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public Vector<DataType> RemoveAt(int index)
    {
        return Erase(index);
    }

    /// <summary>
    /// Swaps two elements at two given indicies
    /// </summary>
    /// <param name="index1"></param>
    /// <param name="index2"></param>
    /// <returns></returns>
    public Vector<DataType> Swap(int index1, int index2)
    {
        // Check for out of bounds
        if (index1 < 0 || index1 >= vectorCount || index2 < 0 || index2 >= vectorCount)
        {
            return this;
        }

        // Check if the indicies are the same
        if (index1 == index2)
        {
            return this;
        }

        // Store swapped data
        DataType temp = vectorData[index2];

        // Replace the swapped data
        vectorData[index2] = vectorData[index1];

        // Return the swapped data
        vectorData[index1] = temp;

        return this;
    }

    /// <summary>
    /// Clears the vector's data
    /// </summary>
    /// <returns></returns>
    public Vector<DataType> Clear()
    {
        // Reset vector variables
        vectorData = new DataType[1];

        vectorCount = 0;

        vectorCapacity = 1;

        vectorExpansions = 0;

        return this;
    }

    /// <summary>
    /// Adds an existing variable to a given index and shift following elements forward
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Vector<DataType> Emplace(int index, ref DataType newData)
    {
        // Check for out of bounds
        if (index < 0 || index >= vectorCount)
        {
            return this;
        }

        // Expand the vector if needed
        if (vectorCount + 1 > vectorCapacity)
        {
            Reallocate();
        }

        // Increase the vector size
        vectorCount++;

        // Shift elements at and past the new index forward
        for (int i = vectorCount - 1; i >= index; i--)
        {
            vectorData[i] = vectorData[i - 1];
        }

        // Replace the starting index with the new data
        vectorData[index] = newData;

        return this;
    }

    /// <summary>
    /// Adds an existing variable to the front of the vector
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Vector<DataType> Emplace(ref DataType newData)
    {
        // Expand the vector if needed
        if (vectorCount + 1 > vectorCapacity)
        {
            Reallocate();
        }

        // Increase the vector size
        vectorCount++;

        // Shift vector elements forward
        for (int i = vectorCount - 1; i >= 1; i--)
        {
            vectorData[i] = vectorData[i - 1];
        }

        // Set the first element to the new data
        vectorData[0] = newData;

        return this;
    }

    /// <summary>
    /// Adds an existing variable to the end of the vector
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Vector<DataType> EmplaceBack(ref DataType newData)
    {
        // Expand the vector if needed
        if (vectorCount + 1 > vectorCapacity)
        {
            Reallocate();
        }

        // Increase the vector size
        vectorCount++;

        // Sets the last element to the new data
        vectorData[vectorCount - 1] = newData;

        return this;
    }

    /// <summary>
    /// Returns a copy of the vector's data
    /// </summary>
    /// <returns></returns>
    public Vector<DataType> Copy()
    {
        Vector<DataType> newVector = new Vector<DataType>(this);

        return newVector;
    }

    /// <summary>
    /// Returns the first index of the given data in the vector, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int Find(DataType foundData)
    {
        // Loop through the vector for the matching element
        for (int i = 0; i < vectorCount; i++)
        {
            if (vectorData[i].Equals(foundData))
            {
                return i;
            }
        }

        return -1;
    }

    /// <summary>
    /// Returns the first index of the given data in the vector, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int IndexOf(DataType foundData)
    {
        return Find(foundData);
    }

    /// <summary>
    /// Returns the last index of the given data in the vector, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int FindLast(DataType foundData)
    {
        // Loop through the vector for the matching element
        for (int i = vectorCount - 1; i >= 0; i--)
        {
            if (vectorData[i].Equals(foundData))
            {
                return i;
            }
        }

        return -1;
    }

    /// <summary>
    /// Returns the last index of the given data in the vector, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int LastIndexOf(DataType foundData)
    {
        return FindLast(foundData);
    }

    /// <summary>
    /// Returns the total number of instances of the given data in the vector, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int Total(DataType foundData)
    {
        // Store the current count
        int count = 0;

        // Loop through the vector for matching elements
        for (int i = 0; i < vectorCount; i++)
        {
            if (vectorData[i].Equals(foundData))
            {
                count++;
            }
        }

        return count;
    }

    /// <summary>
    /// Returns whether the vector contains at least one of the elements 
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool Contains(DataType containedData)
    {
        return Find(containedData) != -1;
    }

    /// <summary>
    /// Returns whether the vector contains at least one of the elements 
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool Exists(DataType containedData)
    {
        return Contains(containedData);
    }

    /// <summary>
    /// Removes the first of a given element in the vector
    /// </summary>
    /// <param name="removedData"></param>
    /// <returns></returns>
    public Vector<DataType> Remove(DataType removedData)
    {
        return Erase(Find(removedData));
    }

    /// <summary>
    /// Removes the last of a given element in the vector
    /// </summary>
    /// <param name="removedData"></param>
    /// <returns></returns>
    public Vector<DataType> RemoveLast(DataType removedData)
    {
        return Erase(FindLast(removedData));
    }

    /// <summary>
    /// Removes all of the given element in the vector
    /// </summary>
    /// <param name="removedData"></param>
    /// <returns></returns>
    public Vector<DataType> RemoveAll(DataType removedData)
    {
        // Get the total number of elements
        int amount = Total(removedData);

        // Remove those elements
        for (int i = 0; i < amount; i++)
        {
            Remove(removedData);
        }

        return this;
    }

    /// <summary>
    /// Replaces the data at the given index with the given data
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Vector<DataType> Set(int index, DataType newData)
    {
        // Check for out of bounds
        if (index < 0 || index >= vectorCount)
        {
            return this;
        }

        // Replace the data at the index
        vectorData[index] = newData;

        return this;
    }

    /// <summary>
    /// Replaces the data at the given index with the given data
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Vector<DataType> Overwrite(int index, DataType newData)
    {
        return Set(index, newData);
    }

    /// <summary>
    /// Replaces the first of the found data with the given data
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Vector<DataType> Replace(DataType replacedData, DataType newData)
    {
        // Find the index of the found data
        int index = Find(replacedData);

        // Check if the data was not found
        if (index == -1)
        {
            return this;
        }

        // Replace the data at the index
        vectorData[index] = newData;

        return this;
    }

    /// <summary>
    /// Replaces the last of the found data with the given data
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Vector<DataType> ReplaceLast(DataType replacedData, DataType newData)
    {
        // Find the index of the found data
        int index = FindLast(replacedData);

        // Check if the data was not found
        if (index == -1)
        {
            return this;
        }

        // Replace the data at the index
        vectorData[index] = newData;

        return this;
    }

    /// <summary>
    /// Replaces all of the found data with the given data
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Vector<DataType> ReplaceAll(DataType replacedData, DataType newData)
    {
        // Get the total number of elements
        int amount = Total(replacedData);

        // Replace those elements
        for (int i = 0; i < amount; i++)
        {
            Replace(replacedData, newData);
        }

        return this;
    }

    /// <summary>
    /// Reverse the vector elements
    /// </summary>
    /// <returns></returns>
    public Vector<DataType> Reverse()
    {
        // Check length
        if (vectorCount <= 1)
        {
            return this;
        }

        // Loop through each element and swap it with the element across the end
        for (int i = 0; i < vectorCount / 2; i++)
        {
            Swap(i, vectorCount - i - 1);
        }

        return this;
    }

    /// <summary>
    /// Shifts the vector elements right
    /// </summary>
    /// <param name="numberOfShifts"></param>
    /// <returns></returns>
    public Vector<DataType> ShiftRight(int numberOfShifts)
    {
        // Check length
        if (vectorCount <= 1)
        {
            return this;
        }

        // Check if shifting the vector is unnecessary
        if (numberOfShifts % vectorCount == 0)
        {
            return this;
        }

        // Duplicate the vector
        DataType[] temp = new DataType[vectorCount];

        for (int i = 0; i < vectorCount; i++)
        {
            temp[i] = vectorData[i];
        }

        vectorData = new DataType[vectorCapacity];

        // Place the vector elements at their shifted location using modulo
        for (int i = 0; i < vectorCount; i++)
        {
            vectorData[i] = temp[((i - numberOfShifts) % vectorCount + vectorCount) % vectorCount];
        }

        return this;
    }

    /// <summary>
    /// Shifts the vector elements right
    /// </summary>
    /// <param name="numberOfShifts"></param>
    /// <returns></returns>
    public Vector<DataType> Shift(int numberOfShifts)
    {
        return ShiftRight(numberOfShifts);
    }

    /// <summary>
    /// Shifts the vector elements left
    /// </summary>
    /// <param name="numberOfShifts"></param>
    /// <returns></returns>
    public Vector<DataType> ShiftLeft(int numberOfShifts)
    {
        return ShiftRight(-numberOfShifts);
    }

    /// <summary>
    /// Bubble sorts the elements of the vector relative to the given sort order
    /// </summary>
    /// <param name="sortOrder"></param>
    /// <returns></returns>
    public Vector<DataType> Sort(SortType[] sortOrder)
    {
        // Check length
        if (vectorCount <= 1)
        {
            return this;
        }

        // Place the vector elements in the sorted order
        for (int i = 0; i < vectorCount - 1; i++)
        {
            for (int j = 0; j < vectorCount - i - 1; j++)
            {
                if (sortOrder[j] > sortOrder[j + 1])
                {
                    // Swap the two vector elements
                    Swap(j, j + 1);

                    // Swap the two sorting elements
                    SortType tempData = sortOrder[j];

                    sortOrder[j] = sortOrder[j + 1];
                    sortOrder[j + 1] = tempData;
                }
            }
        }

        return this;
    }

    /// <summary>
    /// Safely bubble sorts the elements of the vector relative to the given sort order
    /// </summary>
    /// <param name="sortOrder"></param>
    /// <returns></returns>
    public Vector<DataType> Sort(Vector<SortType> sortOrder)
    {
        SortType[] newSortOrder = sortOrder.ToArray();

        Sort(newSortOrder);

        return this;
    }

    /// <summary>
    /// Prints the elements of the vector
    /// </summary>
    public void Print()
    {
        for (int i = 0; i < vectorCount; i++)
        {
            Console.WriteLine(i + ". " + vectorData[i]);
        }
    }

    /// <summary>
    /// Converts the elements of the vector into a string
    /// </summary>
    /// <returns></returns>
    public string ToString()
    {
        string log = "";

        for (int i = 0; i < vectorCount; i++)
        {
            log += (i + ". " + vectorData[i] + "\n");
        }

        return log;
    }


    // CONSTRUCTORS AND DECONSTRUCTOR

    /// <summary>
    /// Default constructor
    /// </summary>
    public Vector()
    {
        vectorData = new DataType[1];

        vectorCount = 0;

        vectorCapacity = 1;

        vectorExpansions = 0;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copiedVector"></param>
    public Vector(Vector<DataType> copiedVector)
    {
        vectorCount = copiedVector.vectorCount;

        vectorCapacity = copiedVector.vectorCapacity;

        vectorExpansions = 0;

        vectorData = new DataType[vectorCapacity];

        for (int i = 0; i < vectorCount; i++)
        {
            vectorData[i] = copiedVector.vectorData[i];
        }
    }

    /// <summary>
    /// Capacity constructor
    /// </summary>
    /// <param name="maxCapacity"></param>
    public Vector(int maxCapacity)
    {
        vectorData = new DataType[maxCapacity];

        vectorCount = 0;

        vectorCapacity = maxCapacity;

        vectorExpansions = 0;
    }

    /// <summary>
    /// Fill constructor
    /// </summary>
    /// <param name="sizeAndCapacity"></param>
    /// <param name="newData"></param>
    public Vector(int sizeAndCapacity, DataType newData)
    {
        vectorData = new DataType[sizeAndCapacity];

        for (int i = 0; i < sizeAndCapacity; i++)
        {
            vectorData[i] = newData;
        }

        vectorCount = sizeAndCapacity;

        vectorCapacity = vectorCount;

        vectorExpansions = 0;
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="array"></param>
    /// <param name="arrayLength"></param>
    public Vector(DataType[] array, int arrayLength)
    {
        vectorData = new DataType[arrayLength];

        for (int i = 0; i < arrayLength; i++)
        {
            vectorData[i] = array[i];
        }

        vectorCount = arrayLength;

        vectorCapacity = vectorCount;

        vectorExpansions = 0;
    }


    // ENUMERATOR FUNCTION

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return vectorData.GetEnumerator();
    }
}
