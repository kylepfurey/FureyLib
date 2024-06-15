
// List Data Type Class
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/vector/vector/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=net-8.0

using System.Collections;

// Data type used for sorting
using SortType = System.Single;

/// <summary>
/// List container class.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class List<DataType> : IEnumerable
{
    // LIST VARIABLES

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


    // LIST EQUALITY

    /// <summary>
    /// Check if another list is equal to this list
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
    /// Check if another list is equal to this list
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedList"></param>
    /// <returns></returns>
    public static bool operator ==(List<DataType> list, List<DataType> comparedList)
    {
        return list.Equals(comparedList);
    }

    /// <summary>
    /// Check if another list is not equal to this list
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedList"></param>
    /// <returns></returns>
    public static bool operator !=(List<DataType> list, List<DataType> comparedList)
    {
        return !list.Equals(comparedList);
    }


    // ITERATORS

    /// <summary>
    /// Return the beginning data
    /// </summary>
    /// <returns></returns>
    public DataType Begin()
    {
        return listData[0];
    }

    /// <summary>
    /// Return the end data
    /// </summary>
    /// <returns></returns>
    public DataType End()
    {
        return listData[listCount - 1];
    }


    // CAPACITY

    /// <summary>
    /// Return the current size of the list
    /// </summary>
    /// <returns></returns>
    public int Size()
    {
        return listCount;
    }

    /// <summary>
    /// Return the current size of the list
    /// </summary>
    /// <returns></returns>
    public int Length()
    {
        return listCount;
    }

    /// <summary>
    /// Resizes the list's size and removes out of bounds data or expands if necessary
    /// </summary>
    /// <param name="newSize"></param>
    /// <returns></returns>
    public List<DataType> Resize(int newSize)
    {
        // Check if the new size is identical
        if (listCount == newSize)
        {
            return this;
        }

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

        return this;
    }

    /// <summary>
    /// Return the maximum capacity of the list before expanding
    /// </summary>
    /// <returns></returns>
    public int Capacity()
    {
        return listCapacity;
    }

    /// <summary>
    /// Return the maximum capacity of the list before expanding
    /// </summary>
    /// <returns></returns>
    public int MaxSize()
    {
        return Capacity();
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
    /// Return whether the list is empty
    /// </summary>
    /// <returns></returns>
    public bool IsEmpty()
    {
        return Empty();
    }

    /// <summary>
    /// Expands the list's capacity enough to hold the given amount (does not reduce the capacity)
    /// </summary>
    /// <param name="newCapacity"></param>
    /// <returns></returns>
    public List<DataType> Reserve(int newCapacity)
    {
        // Check if the new capacity is less
        if (newCapacity <= listCapacity)
        {
            return this;
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

        return this;
    }

    /// <summary>
    /// Expands the list's capacity enough to hold the given amount (does not reduce the capacity)
    /// </summary>
    /// <param name="newCapacity"></param>
    /// <returns></returns>
    public List<DataType> EnsureCapacity(int newCapacity)
    {
        return Reserve(newCapacity);
    }

    /// <summary>
    /// Shrinks the capacity to the size
    /// </summary>
    /// <returns></returns>
    public List<DataType> ShrinkToFit()
    {
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

        return this;
    }

    /// <summary>
    /// Shrinks the capacity to the size
    /// </summary>
    /// <returns></returns>
    public List<DataType> TrimExcess()
    {
        return ShrinkToFit();
    }

    /// <summary>
    /// Shrinks the capacity to the size
    /// </summary>
    /// <returns></returns>
    public List<DataType> Clean()
    {
        return ShrinkToFit();
    }

    /// <summary>
    /// Return the total number of expansions
    /// </summary>
    /// <returns></returns>
    public int Expansions()
    {
        return listExpansions;
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
    /// Expands the list's capacity by the given amount
    /// </summary>
    /// <param name="numberOfSpaces"></param>
    /// <returns></returns>
    public List<DataType> Expand(int numberOfSpaces)
    {
        return Reserve(listCapacity + numberOfSpaces);
    }


    // ELEMENT ACCESS

    /// <summary>
    /// Returns the element at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType At(int index)
    {
        return listData[index];
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
    /// Returns the first element in the list
    /// </summary>
    /// <returns></returns>
    public DataType Front()
    {
        return listData[0];
    }

    /// <summary>
    /// Returns the first element in the list
    /// </summary>
    /// <returns></returns>
    public DataType Back()
    {
        return listData[listCount - 1];
    }


    // MODIFIERS

    /// <summary>
    /// Assigns this list's elements and capacity to the elements and capacity of another list
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
    /// Adds a new element at the front of the list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    List<DataType> Push(DataType newData)
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
    /// Adds a new element at the front of the list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> Enqueue(DataType newData)
    {
        return Push(newData);
    }

    /// <summary>
    /// Adds a new element at the front of the list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> AddFront(DataType newData)
    {
        return Push(newData);
    }

    /// <summary>
    /// Adds a new element at the end of the list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> PushBack(DataType newData)
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
    /// Adds a new element at the end of the list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> Add(DataType newData)
    {
        return PushBack(newData);
    }

    /// <summary>
    /// Remove and return the first element of the list
    /// </summary>
    /// <returns></returns>
    public DataType Pop()
    {
        // Decrease the list size if possible
        if (listCount == 0)
        {
            return listData[0];
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
    /// Remove and return the first element of the list
    /// </summary>
    /// <returns></returns>
    public DataType Dequeue()
    {
        return Pop();
    }

    /// <summary>
    /// Remove and return the last element of the list
    /// </summary>
    /// <returns></returns>
    public DataType PopBack()
    {
        // Decrease the list size if possible
        if (listCount == 0)
        {
            return listData[0];
        }

        listCount--;

        return listData[listCount];
    }

    /// <summary>
    /// Adds a new element in the list at a given index and shift following elements forward
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> Insert(int index, DataType newData)
    {
        // Check for out of bounds
        if (index < 0 || index >= listCount)
        {
            return this;
        }

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

    /// <summary>
    /// Removes a element in the list at a given index and shift following elements back
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public List<DataType> Erase(int index)
    {
        // Check for out of bounds
        if (index < 0 || index >= listCount)
        {
            return this;
        }

        // Decrease the list size
        listCount--;

        // Shift elements past the new index backward
        for (int i = index + 1; i <= listCount; i++)
        {
            listData[i - 1] = listData[i];
        }

        return this;
    }

    /// <summary>
    /// Removes a element in the list at a given index and shift following elements back
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public List<DataType> RemoveAt(int index)
    {
        return Erase(index);
    }

    /// <summary>
    /// Swaps two elements at two given indicies
    /// </summary>
    /// <param name="index1"></param>
    /// <param name="index2"></param>
    /// <returns></returns>
    public List<DataType> Swap(int index1, int index2)
    {
        // Check for out of bounds
        if (index1 < 0 || index1 >= listCount || index2 < 0 || index2 >= listCount)
        {
            return this;
        }

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
    /// Clears the list's data
    /// </summary>
    /// <returns></returns>
    public List<DataType> Clear()
    {
        // Reset list variables
        listData = new DataType[1];

        listCount = 0;

        listCapacity = 1;

        listExpansions = 0;

        return this;
    }

    /// <summary>
    /// Adds an existing variable to a given index and shift following elements forward
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> Emplace(int index, ref DataType newData)
    {
        // Check for out of bounds
        if (index < 0 || index >= listCount)
        {
            return this;
        }

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

    /// <summary>
    /// Adds an existing variable to the front of the list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> Emplace(ref DataType newData)
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
    /// Adds an existing variable to the end of the list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> EmplaceBack(ref DataType newData)
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
    /// Returns a copy of the list's data
    /// </summary>
    /// <returns></returns>
    public List<DataType> Copy()
    {
        List<DataType> newList = new List<DataType>(this);

        return newList;
    }

    /// <summary>
    /// Returns the first index of the given data in the list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int Find(DataType foundData)
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
    /// Returns the first index of the given data in the list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int IndexOf(DataType foundData)
    {
        return Find(foundData);
    }

    /// <summary>
    /// Returns the last index of the given data in the list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int FindLast(DataType foundData)
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
    /// Returns the last index of the given data in the list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int LastIndexOf(DataType foundData)
    {
        return FindLast(foundData);
    }

    /// <summary>
    /// Returns the total number of instances of the given data in the list, returns -1 if nothing matched
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

    /// <summary>
    /// Returns whether the list contains at least one of the elements 
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool Contains(DataType containedData)
    {
        return Find(containedData) != -1;
    }

    /// <summary>
    /// Returns whether the list contains at least one of the elements 
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool Exists(DataType containedData)
    {
        return Contains(containedData);
    }

    /// <summary>
    /// Removes the first of a given element in the list
    /// </summary>
    /// <param name="removedData"></param>
    /// <returns></returns>
    public List<DataType> Remove(DataType removedData)
    {
        return Erase(Find(removedData));
    }

    /// <summary>
    /// Removes the last of a given element in the list
    /// </summary>
    /// <param name="removedData"></param>
    /// <returns></returns>
    public List<DataType> RemoveLast(DataType removedData)
    {
        return Erase(FindLast(removedData));
    }

    /// <summary>
    /// Removes all of the given element in the list
    /// </summary>
    /// <param name="removedData"></param>
    /// <returns></returns>
    public List<DataType> RemoveAll(DataType removedData)
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
    public List<DataType> Set(int index, DataType newData)
    {
        // Check for out of bounds
        if (index < 0 || index >= listCount)
        {
            return this;
        }

        // Replace the data at the index
        listData[index] = newData;

        return this;
    }

    /// <summary>
    /// Replaces the data at the given index with the given data
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> Overwrite(int index, DataType newData)
    {
        return Set(index, newData);
    }

    /// <summary>
    /// Replaces the first of the found data with the given data
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> Replace(DataType replacedData, DataType newData)
    {
        // Find the index of the found data
        int index = Find(replacedData);

        // Check if the data was not found
        if (index == -1)
        {
            return this;
        }

        // Replace the data at the index
        listData[index] = newData;

        return this;
    }

    /// <summary>
    /// Replaces the last of the found data with the given data
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> ReplaceLast(DataType replacedData, DataType newData)
    {
        // Find the index of the found data
        int index = FindLast(replacedData);

        // Check if the data was not found
        if (index == -1)
        {
            return this;
        }

        // Replace the data at the index
        listData[index] = newData;

        return this;
    }

    /// <summary>
    /// Replaces all of the found data with the given data
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> ReplaceAll(DataType replacedData, DataType newData)
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
    /// Shifts the list elements right
    /// </summary>
    /// <param name="numberOfShifts"></param>
    /// <returns></returns>
    public List<DataType> Shift(int numberOfShifts)
    {
        return ShiftRight(numberOfShifts);
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
    public List<DataType> Sort(SortType[] sortOrder)
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
    /// Safely bubble sorts the elements of the list relative to the given sort order
    /// </summary>
    /// <param name="sortOrder"></param>
    /// <returns></returns>
    public List<DataType> Sort(List<SortType> sortOrder)
    {
        SortType[] newSortOrder = sortOrder.ToArray();

        Sort(newSortOrder);

        return this;
    }

    /// <summary>
    /// Prints the elements of the list
    /// </summary>
    public void Print()
    {
        for (int i = 0; i < listCount; i++)
        {
            Console.WriteLine(i + ". " + listData[i]);
        }
    }

    /// <summary>
    /// Converts the elements of the list into a string
    /// </summary>
    /// <returns></returns>
    public string ToString()
    {
        string log = "";

        for (int i = 0; i < listCount; i++)
        {
            log += (i + ". " + listData[i] + "\n");
        }

        return log;
    }


    // CONSTRUCTORS AND DECONSTRUCTOR

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
    /// <param name="array"></param>
    /// <param name="arrayLength"></param>
    public List(DataType[] array, int arrayLength)
    {
        listData = new DataType[arrayLength];

        for (int i = 0; i < arrayLength; i++)
        {
            listData[i] = array[i];
        }

        listCount = arrayLength;

        listCapacity = listCount;

        listExpansions = 0;
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
