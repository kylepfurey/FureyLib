
// List Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/vector/vector/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=net-8.0

using System;
using System.Collections;

// Data type used for sorting
using SortType = System.Single;

/// <summary>
/// Class used to store and dynamically reallocate an array for expanding storage.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class List<DataType> : IEnumerable
{
    // LIST DATA

    /// <summary>
    /// The array of the list's data
    /// </summary>
    private DataType[] listData = new DataType[0];

    /// <summary>
    /// The current number of elements in the array holding data
    /// </summary>
    private int listCount = 0;

    /// <summary>
    /// The current maximum size of the array before needing to expand
    /// </summary>
    private int listCapacity = 1;

    /// <summary>
    /// The number of array expansions
    /// </summary>
    private int listExpansions = 0;

    /// <summary>
    /// Readonly count variable
    /// </summary>
    public int Count
    {
        get
        {
            return listCount;
        }
    }

    /// <summary>
    /// Readonly capacity variable
    /// </summary>
    public int Capacity
    {
        get
        {
            return listCapacity;
        }
    }

    /// <summary>
    /// Readonly expansions variable
    /// </summary>
    public int Expansions
    {
        get
        {
            return listExpansions;
        }
    }


    // TO ARRAY

    /// <summary>
    /// Returns an array of the current list
    /// </summary>
    /// <returns></returns>
    public DataType[] ToArray()
    {
        // Copy the list into an array
        DataType[] newArray = new DataType[listCount];

        for (int i = 0; i < listCount; i++)
        {
            newArray[i] = listData[i];
        }

        return newArray;
    }


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public List()
    {
        listData = new DataType[1];

        listCount = 0;

        listCapacity = 1;

        listExpansions = 0;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copiedList"></param>
    public List(List<DataType> copiedList)
    {
        listCount = copiedList.listCount;

        listCapacity = copiedList.listCapacity;

        listExpansions = 0;

        listData = new DataType[listCapacity];

        for (int i = 0; i < listCount; i++)
        {
            listData[i] = copiedList.listData[i];
        }
    }

    /// <summary>
    /// Capacity constructor
    /// </summary>
    /// <param name="maxCapacity"></param>
    public List(int maxCapacity)
    {
        listData = new DataType[maxCapacity];

        listCount = 0;

        listCapacity = maxCapacity;

        listExpansions = 0;
    }

    /// <summary>
    /// Fill constructor
    /// </summary>
    /// <param name="sizeAndCapacity"></param>
    /// <param name="newData"></param>
    public List(int sizeAndCapacity, DataType newData)
    {
        listData = new DataType[sizeAndCapacity];

        for (int i = 0; i < sizeAndCapacity; i++)
        {
            listData[i] = newData;
        }

        listCount = sizeAndCapacity;

        listCapacity = listCount;

        listExpansions = 0;
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="arrayLength"></param>
    /// <param name="array"></param>
    public List(int capacity, DataType[] array)
    {
        listData = new DataType[capacity];

        for (int i = 0; i < array.Length; i++)
        {
            listData[i] = array[i];
        }

        listCount = array.Length;

        listCapacity = capacity;

        listExpansions = 0;
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="array"></param>
    public List(params DataType[] array)
    {
        listData = new DataType[array.Length];

        for (int i = 0; i < array.Length; i++)
        {
            listData[i] = array[i];
        }

        listCount = array.Length;

        listCapacity = listCount;

        listExpansions = 0;
    }


    // REALLOCATE MEMORY

    /// <summary>
    /// Expands the capacity based on how many times it has been expanded
    /// </summary>
    /// <returns></returns>
    public List<DataType> Reallocate()
    {
        // Advance the number of expansions
        listExpansions++;

        // Duplicate the list
        DataType[] temp = new DataType[listCount];

        for (int i = 0; i < listCount; i++)
        {
            temp[i] = listData[i];
        }

        // Allocate new space for the list
        listCapacity *= 2;

        listData = new DataType[listCapacity];

        // Place the data back into the list
        for (int i = 0; i < listCount; i++)
        {
            listData[i] = temp[i];
        }

        return this;
    }


    // LIST EQUALITY

    /// <summary>
    /// Check if another list is equal to the list
    /// </summary>
    /// <param name="comparedList"></param>
    /// <returns></returns>
    public bool Equals(List<DataType> comparedList)
    {
        // Check if the sizes are equal
        if (listCount != comparedList.listCount)
        {
            return false;
        }

        // Loop through each element to check if they are not equal
        for (int i = 0; i < listCount; i++)
        {
            // Are they not equal
            if (!listData[i].Equals(comparedList[i]))
            {
                return false;
            }
        }

        // The lists are equal
        return true;
    }

    /// <summary>
    /// Check if another list is equal to the list
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedList"></param>
    /// <returns></returns>
    public static bool operator ==(List<DataType> list, List<DataType> comparedList)
    {
        return list.Equals(comparedList);
    }

    /// <summary>
    /// Check if another list is not equal to the list
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedList"></param>
    /// <returns></returns>
    public static bool operator !=(List<DataType> list, List<DataType> comparedList)
    {
        return !list.Equals(comparedList);
    }


    // SIZE AND CAPACITY

    /// <summary>
    /// Return the current size of the list
    /// </summary>
    /// <returns></returns>
    public int Size()
    {
        return listCount;
    }

    /// <summary>
    /// Return the maximum capacity of the list before expanding
    /// </summary>
    /// <returns></returns>
    public int MaxSize()
    {
        return listCapacity;
    }

    /// <summary>
    /// Return the total number of expansions
    /// </summary>
    /// <returns></returns>
    public int Reallocations()
    {
        return listExpansions;
    }

    /// <summary>
    /// Return whether the list is empty
    /// </summary>
    /// <returns></returns>
    public bool Empty()
    {
        return listCount == 0;
    }

    /// <summary>
    /// Resizes the list's size and removes out of bounds data or expands if necessary, returns the difference
    /// </summary>
    /// <param name="newSize"></param>
    /// <returns></returns>
    public int Resize(int newSize)
    {
        // Check if the new size is identical
        if (listCount == newSize)
        {
            return 0;
        }

        int difference = newSize - listCapacity;

        // Duplicate the current list
        DataType[] temp = new DataType[listCount];

        for (int i = 0; i < listCount; i++)
        {
            temp[i] = listData[i];
        }

        // Expand the list if needed
        if (newSize > listCapacity)
        {
            Reallocate();
        }

        // Allocate new space for the list
        listData = new DataType[listCapacity];

        listCount = newSize;

        // Place the data back into the list
        for (int i = 0; i < listCount; i++)
        {
            listData[i] = temp[i];
        }

        return difference;
    }

    /// <summary>
    /// Expands the list's capacity enough to hold the given amount and return whether it was successful (does not reduce the capacity)
    /// </summary>
    /// <param name="newCapacity"></param>
    /// <returns></returns>
    public bool EnsureCapacity(int newCapacity)
    {
        // Check if the new capacity is less
        if (newCapacity <= listCapacity)
        {
            return false;
        }

        // Advance the number of expansions
        listExpansions++;

        // Duplicate the current list
        DataType[] temp = new DataType[listCount];

        for (int i = 0; i < listCount; i++)
        {
            temp[i] = listData[i];
        }

        // Allocate new space for the list
        listCapacity = newCapacity;

        listData = new DataType[listCapacity];

        // Place the data back into the list
        for (int i = 0; i < listCount; i++)
        {
            listData[i] = temp[i];
        }

        return true;
    }

    /// <summary>
    /// Expands the list's capacity by the given amount and return the new capacity
    /// </summary>
    /// <param name="numberOfSpaces"></param>
    /// <returns></returns>
    public int Expand(int numberOfSpaces)
    {
        EnsureCapacity(listCapacity + numberOfSpaces);

        return listCapacity;
    }

    /// <summary>
    /// Shrinks the capacity to the size and return the difference
    /// </summary>
    /// <returns></returns>
    public int TrimExcess()
    {
        int difference = listCapacity - listCount;

        // Duplicate the current list
        DataType[] temp = new DataType[listCount];

        for (int i = 0; i < listCount; i++)
        {
            temp[i] = listData[i];
        }

        // Allocate new space for the list
        listCapacity = listCount;

        listData = new DataType[listCapacity];

        // Place the data back into the list
        for (int i = 0; i < listCount; i++)
        {
            listData[i] = temp[i];
        }

        // Reset the number of resizes
        listExpansions = 0;

        return difference;
    }


    // ELEMENT ACCESS

    /// <summary>
    /// Returns the element at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType Get(int index)
    {
        return listData[index];
    }

    /// <summary>
    /// Returns the first element in the list
    /// </summary>
    /// <returns></returns>
    public DataType Front()
    {
        return listData[0];
    }

    /// <summary>
    /// Returns the last element in the list
    /// </summary>
    /// <returns></returns>
    public DataType Back()
    {
        return listData[listCount - 1];
    }


    // LOCATING ELEMENTS

    /// <summary>
    /// Returns the first index of the given data in the list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int IndexOf(DataType foundData)
    {
        // Loop through the list for the matching element
        for (int i = 0; i < listCount; i++)
        {
            if (listData[i].Equals(foundData))
            {
                return i;
            }
        }

        return -1;
    }

    /// <summary>
    /// Returns the last index of the given data in the list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int LastIndexOf(DataType foundData)
    {
        // Loop through the list for the matching element
        for (int i = listCount - 1; i >= 0; i--)
        {
            if (listData[i].Equals(foundData))
            {
                return i;
            }
        }

        return -1;
    }

    /// <summary>
    /// Returns whether the list contains at least one of the elements 
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool Contains(DataType containedData)
    {
        return IndexOf(containedData) != -1;
    }

    /// <summary>
    /// Returns whether the list contains at least one of the elements, starting from the back
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool ContainsLast(DataType containedData)
    {
        return LastIndexOf(containedData) != -1;
    }

    /// <summary>
    /// Returns the total number of instances of the given data in the list
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int Total(DataType foundData)
    {
        // Store the current count
        int count = 0;

        // Loop through the list for matching elements
        for (int i = 0; i < listCount; i++)
        {
            if (listData[i].Equals(foundData))
            {
                count++;
            }
        }

        return count;
    }


    // ADDING ELEMENTS

    /// <summary>
    /// Adds a new element at the end of the list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> Add(DataType newData)
    {
        // Expand the list if needed
        if (listCount + 1 > listCapacity)
        {
            Reallocate();
        }

        // Increase the list size
        listCount++;

        // Sets the last element to the new data
        listData[listCount - 1] = newData;

        return this;
    }

    /// <summary>
    /// Adds a range of new elements at the end of the list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> AddRange(params DataType[] newData)
    {
        EnsureCapacity(listCount + newData.Length);

        for (int i = 0; i < newData.Length; i++)
        {
            Add(newData[i]);
        }

        return this;
    }

    /// <summary>
    /// Adds a new element at the front of the list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> AddFront(DataType newData)
    {
        // Expand the list if needed
        if (listCount + 1 > listCapacity)
        {
            Reallocate();
        }

        // Increase the list size
        listCount++;

        // Shift list elements forward
        for (int i = listCount - 1; i >= 1; i--)
        {
            listData[i] = listData[i - 1];
        }

        // Set the first element to the new data
        listData[0] = newData;

        return this;
    }

    /// <summary>
    /// Adds a range of new elements at the front of the list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> AddFrontRange(params DataType[] newData)
    {
        EnsureCapacity(listCount + newData.Length);

        for (int i = 0; i < newData.Length; i++)
        {
            AddFront(newData[i]);
        }

        return this;
    }

    /// <summary>
    /// Adds a new element in the list at a given index and shift following elements forward
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> Insert(int index, DataType newData)
    {
        // Expand the list if needed
        if (listCount + 1 > listCapacity)
        {
            Reallocate();
        }

        // Increase the list size
        listCount++;

        // Shift elements at and past the new index forward
        for (int i = listCount - 1; i >= index; i--)
        {
            listData[i] = listData[i - 1];
        }

        // Replace the starting index with the new data
        listData[index] = newData;

        return this;
    }


    // REMOVING ELEMENTS

    /// <summary>
    /// Removes a element in the list at a given index and shift following elements back, returns the removed data
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType RemoveAt(int index)
    {
        // Decrease the list size
        listCount--;

        DataType data = listData[index];

        // Shift elements past the new index backward
        for (int i = index + 1; i <= listCount; i++)
        {
            listData[i - 1] = listData[i];
        }

        return data;
    }

    /// <summary>
    /// Removes the first of a given element in the list and return the index
    /// </summary>
    /// <param name="removedData"></param>
    /// <returns></returns>
    public int Remove(DataType removedData)
    {
        int index = IndexOf(removedData);

        RemoveAt(index);

        return index;
    }

    /// <summary>
    /// Removes the last of a given element in the list and return the index
    /// </summary>
    /// <param name="removedData"></param>
    /// <returns></returns>
    public int RemoveLast(DataType removedData)
    {
        int index = LastIndexOf(removedData);

        RemoveAt(index);

        return index;
    }

    /// <summary>
    /// Remove and return the first element of the list
    /// </summary>
    /// <returns></returns>
    public DataType RemoveFirst()
    {
        if (listCount == 0)
        {
            return default(DataType);
        }

        listCount--;

        // Store the removed data
        DataType newData = listData[0];

        // Shift list elements backward
        for (int i = 1; i <= listCount; i++)
        {
            listData[i - 1] = listData[i];
        }

        return newData;
    }

    /// <summary>
    /// Remove and return the last element of the list
    /// </summary>
    /// <returns></returns>
    public DataType RemoveLast()
    {
        if (listCount == 0)
        {
            return default(DataType);
        }

        listCount--;

        return listData[listCount];
    }

    /// <summary>
    /// Removes all of the given element in the list and returns the total elements removed
    /// </summary>
    /// <param name="removedData"></param>
    /// <returns></returns>
    public int RemoveAll(DataType removedData)
    {
        int total = 0;

        for (int i = 0; i < listCount - 1; i++)
        {
            if (listData[i].Equals(removedData))
            {
                listData[i] = listData[i + 1];

                total++;

                i--;
            }
        }

        if (listData[listCount - 1].Equals(removedData))
        {
            total++;
        }

        listCount -= total;

        return total;
    }

    /// <summary>
    /// Clears the list's data with a new capacity
    /// </summary>
    /// <param name="newCapacity"></param>
    /// <returns></returns>
    public int Clear(int newCapacity = 1)
    {
        int total = listCount;

        // Reset list variables
        listData = new DataType[newCapacity];

        listCount = 0;

        listCapacity = newCapacity;

        listExpansions = 0;

        return total;
    }


    // ELEMENT OPERATIONS

    /// <summary>
    /// Replaces the data at the given index with the given data, returns the replaced data
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public DataType Set(int index, DataType newData)
    {
        // Replace the data at the index
        DataType data = listData[index];

        listData[index] = newData;

        return data;
    }

    /// <summary>
    /// Replaces the first of the found data with the given data and return the index
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public int Replace(DataType replacedData, DataType newData)
    {
        // Find the index of the found data
        int index = IndexOf(replacedData);

        // Check if the data was not found
        if (index == -1)
        {
            return index;
        }

        // Replace the data at the index
        listData[index] = newData;

        return index;
    }

    /// <summary>
    /// Replaces the last of the found data with the given data and return the index
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public int ReplaceLast(DataType replacedData, DataType newData)
    {
        // Find the index of the found data
        int index = LastIndexOf(replacedData);

        // Check if the data was not found
        if (index == -1)
        {
            return index;
        }

        // Replace the data at the index
        listData[index] = newData;

        return index;
    }

    /// <summary>
    /// Replaces all of the found data with the given data and returns the total number of replacements
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public int ReplaceAll(DataType replacedData, DataType newData)
    {
        int total = 0;

        for (int i = 0; i < listCount; i++)
        {
            if (listData[i].Equals(replacedData))
            {
                listData[i] = newData;

                total++;
            }
        }

        return total;
    }

    /// <summary>
    /// Swaps two elements at two given indicies
    /// </summary>
    /// <param name="index1"></param>
    /// <param name="index2"></param>
    /// <returns></returns>
    public List<DataType> Swap(int index1, int index2)
    {
        // Check if the indicies are the same
        if (index1 == index2)
        {
            return this;
        }

        // Store swapped data
        DataType temp = listData[index2];

        // Replace the swapped data
        listData[index2] = listData[index1];

        // Return the swapped data
        listData[index1] = temp;

        return this;
    }

    /// <summary>
    /// Gets or sets the element at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType this[int index]
    {
        get => Get(index);
        set => Set(index, value);
    }


    // LIST OPERATIONS

    /// <summary>
    /// Assigns the list's elements and capacity to the elements and capacity of another list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> Assign(List<DataType> newData)
    {
        // Store the list's size values
        listCount = newData.Size();

        listCapacity = listCount;

        listExpansions = 0;

        // Allocate the space from the new list
        listData = new DataType[listCapacity];

        // Place the data back into the list
        for (int i = 0; i < listCount; i++)
        {
            listData[i] = newData[i];
        }

        return this;
    }

    /// <summary>
    /// Returns a copy of the list's data
    /// </summary>
    /// <returns></returns>
    public List<DataType> Copy()
    {
        List<DataType> newList = new List<DataType>(this);

        return newList;
    }

    /// <summary>
    /// Returns a slice of the list from the start index for the number of elements
    /// </summary>
    /// <param name="start"></param>
    /// <param name="count"></param>
    /// <returns></returns>
    public List<DataType> Slice(int start, int count)
    {
        List<DataType> slice = new List<DataType>(count);

        for (int i = start; i < start + count || i >= listCount; i++)
        {
            slice.Add(listData[i]);
        }

        return slice;
    }

    /// <summary>
    /// Reverse the list elements
    /// </summary>
    /// <returns></returns>
    public List<DataType> Reverse()
    {
        // Check length
        if (listCount <= 1)
        {
            return this;
        }

        // Loop through each element and swap it with the element across the end
        for (int i = 0; i < listCount / 2; i++)
        {
            Swap(i, listCount - i - 1);
        }

        return this;
    }

    /// <summary>
    /// Shifts the list elements right
    /// </summary>
    /// <param name="numberOfShifts"></param>
    /// <returns></returns>
    public List<DataType> ShiftRight(int numberOfShifts)
    {
        // Check length
        if (listCount <= 1)
        {
            return this;
        }

        // Check if shifting the list is unnecessary
        if (numberOfShifts % listCount == 0)
        {
            return this;
        }

        // Duplicate the list
        DataType[] temp = new DataType[listCount];

        for (int i = 0; i < listCount; i++)
        {
            temp[i] = listData[i];
        }

        listData = new DataType[listCapacity];

        // Place the list elements at their shifted location using modulo
        for (int i = 0; i < listCount; i++)
        {
            listData[i] = temp[((i - numberOfShifts) % listCount + listCount) % listCount];
        }

        return this;
    }

    /// <summary>
    /// Shifts the list elements left
    /// </summary>
    /// <param name="numberOfShifts"></param>
    /// <returns></returns>
    public List<DataType> ShiftLeft(int numberOfShifts)
    {
        return ShiftRight(-numberOfShifts);
    }

    /// <summary>
    /// Bubble sorts the elements of the list relative to the given sort order
    /// </summary>
    /// <param name="sortOrder"></param>
    /// <returns></returns>
    public List<DataType> Sort(params SortType[] sortOrder)
    {
        // Check length
        if (listCount <= 1)
        {
            return this;
        }

        // Place the list elements in the sorted order
        for (int i = 0; i < listCount - 1; i++)
        {
            for (int j = 0; j < listCount - i - 1; j++)
            {
                if (sortOrder[j] > sortOrder[j + 1])
                {
                    // Swap the two list elements
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
    /// Bubble sorts the elements of the list relative to the given sort order
    /// </summary>
    /// <param name="sortOrder"></param>
    /// <returns></returns>
    public List<DataType> Sort(List<SortType> sortOrder)
    {
        return Sort(sortOrder.ToArray());
    }


    // TO STRING

    /// <summary>
    /// Converts the elements of the list into a string
    /// </summary>
    /// <returns></returns>
    public string ToString()
    {
        if (listCount == 0)
        {
            return "{ }";
        }

        string log = "{ ";

        for (int i = 0; i < listCount; i++)
        {
            log += (listData[i] + ", ");
        }

        log = log.Remove(log.Length - 2, 1);

        log += "}";

        return log;
    }


    // ENUMERATOR FUNCTION

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return listData.GetEnumerator();
    }
}
