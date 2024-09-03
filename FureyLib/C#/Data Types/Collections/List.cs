
// List Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/vector/vector/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=net-8.0

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

/// <summary>
/// Class used to store and dynamically reallocate an array for expanding storage.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class List<DataType> : IEnumerable, IEnumerable<DataType>
{
    // VARIABLES

    /// <summary>
    /// The array of the list's data
    /// </summary>
    private DataType[] list = new DataType[0];

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


    // PROPERTIES

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

        set
        {
            Resize(value);
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


    // REALLOCATE MEMORY

    /// <summary>
    /// Expands the capacity based on how many times it has been expanded
    /// </summary>
    /// <returns></returns>
    private List<DataType> Reallocate()
    {
        listExpansions++;

        DataType[] temp = new DataType[listCount];

        for (int i = 0; i < listCount; i++)
        {
            temp[i] = list[i];
        }

        listCapacity *= 2;

        list = new DataType[listCapacity];

        for (int i = 0; i < listCount; i++)
        {
            list[i] = temp[i];
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
        DataType[] newArray = new DataType[listCount];

        for (int i = 0; i < listCount; i++)
        {
            newArray[i] = list[i];
        }

        return newArray;
    }


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public List()
    {
        list = new DataType[1];

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

        list = new DataType[listCapacity];

        for (int i = 0; i < listCount; i++)
        {
            list[i] = copiedList.list[i];
        }
    }

    /// <summary>
    /// Capacity constructor
    /// </summary>
    /// <param name="maxCapacity"></param>
    public List(int maxCapacity)
    {
        list = new DataType[maxCapacity];

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
        list = new DataType[sizeAndCapacity];

        for (int i = 0; i < sizeAndCapacity; i++)
        {
            list[i] = newData;
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
        list = new DataType[capacity];

        for (int i = 0; i < array.Length; i++)
        {
            list[i] = array[i];
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
        list = new DataType[array.Length];

        for (int i = 0; i < array.Length; i++)
        {
            list[i] = array[i];
        }

        listCount = array.Length;

        listCapacity = listCount;

        listExpansions = 0;
    }

    /// <summary>
    /// Enumerable constructor
    /// </summary>
    /// <param name="list"></param>
    public List(IEnumerable<DataType> list)
    {
        listCount = list.Count();

        this.list = new DataType[listCount];

        int i = 0;

        foreach (DataType item in list)
        {
            this.list[i] = item;

            i++;
        }

        listCapacity = listCount;

        listExpansions = 0;
    }


    // EQUALITY

    /// <summary>
    /// Check if another list is equal to the list
    /// </summary>
    /// <param name="comparedList"></param>
    /// <returns></returns>
    public bool Equals(List<DataType> comparedList)
    {
        if (listCount != comparedList.listCount)
        {
            return false;
        }

        for (int i = 0; i < listCount; i++)
        {
            if (!list[i].Equals(comparedList[i]))
            {
                return false;
            }
        }

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


    // CAPACITY

    /// <summary>
    /// Returns the current size of the list
    /// </summary>
    /// <returns></returns>
    public int Size()
    {
        return listCount;
    }

    /// <summary>
    /// Returns the maximum capacity of the list before expanding
    /// </summary>
    /// <returns></returns>
    public int MaxSize()
    {
        return listCapacity;
    }

    /// <summary>
    /// Returns the total number of expansions
    /// </summary>
    /// <returns></returns>
    public int Reallocations()
    {
        return listExpansions;
    }

    /// <summary>
    /// Resizes the list's size and removes out of bounds data or expands if necessary, returns the difference
    /// </summary>
    /// <param name="newSize"></param>
    /// <returns></returns>
    public int Resize(int newSize)
    {
        if (listCount == newSize)
        {
            return 0;
        }

        int difference = newSize - listCapacity;

        DataType[] temp = new DataType[listCount];

        for (int i = 0; i < listCount; i++)
        {
            temp[i] = list[i];
        }

        if (newSize > listCapacity)
        {
            Reallocate();
        }

        list = new DataType[listCapacity];

        listCount = newSize;

        for (int i = 0; i < listCount; i++)
        {
            list[i] = temp[i];
        }

        return difference;
    }

    /// <summary>
    /// Returns whether the list is empty
    /// </summary>
    /// <returns></returns>
    public bool Empty()
    {
        return listCount == 0;
    }

    /// <summary>
    /// Expands the list's capacity enough to hold the given amount and return whether it was successful (does not reduce the capacity)
    /// </summary>
    /// <param name="newCapacity"></param>
    /// <returns></returns>
    public bool EnsureCapacity(int newCapacity)
    {
        if (newCapacity <= listCapacity)
        {
            return false;
        }

        listExpansions++;

        DataType[] temp = new DataType[listCount];

        for (int i = 0; i < listCount; i++)
        {
            temp[i] = list[i];
        }

        listCapacity = newCapacity;

        list = new DataType[listCapacity];

        for (int i = 0; i < listCount; i++)
        {
            list[i] = temp[i];
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

        DataType[] temp = new DataType[listCount];

        for (int i = 0; i < listCount; i++)
        {
            temp[i] = list[i];
        }

        listCapacity = listCount;

        list = new DataType[listCapacity];

        for (int i = 0; i < listCount; i++)
        {
            list[i] = temp[i];
        }

        listExpansions = 0;

        return difference;
    }


    // ELEMENT ACCESS

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

    /// <summary>
    /// Returns the element at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType Get(int index)
    {
        return list[index];
    }

    /// <summary>
    /// Returns the first element in the list
    /// </summary>
    /// <returns></returns>
    public DataType Front()
    {
        return list[0];
    }

    /// <summary>
    /// Returns the last element in the list
    /// </summary>
    /// <returns></returns>
    public DataType Back()
    {
        return list[listCount - 1];
    }

    /// <summary>
    /// Returns the list's data at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public ref DataType Data(int index)
    {
        return ref list[index];
    }


    // LOCATING ELEMENTS

    /// <summary>
    /// Returns the first index of the given data in the list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int IndexOf(DataType foundData)
    {
        for (int i = 0; i < listCount; i++)
        {
            if (list[i].Equals(foundData))
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
        for (int i = listCount - 1; i >= 0; i--)
        {
            if (list[i].Equals(foundData))
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
    /// Returns the total number of instances of the given data in the list
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int Total(DataType foundData)
    {
        int count = 0;

        for (int i = 0; i < listCount; i++)
        {
            if (list[i].Equals(foundData))
            {
                count++;
            }
        }

        return count;
    }


    // ADDING ELEMENTS

    /// <summary>
    /// Assigns the list's elements and capacity to the elements and capacity of another list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> Assign(List<DataType> newData)
    {
        listCount = newData.Size();

        listCapacity = listCount;

        listExpansions = 0;

        list = new DataType[listCapacity];

        for (int i = 0; i < listCount; i++)
        {
            list[i] = newData[i];
        }

        return this;
    }

    /// <summary>
    /// Adds a new element at the end of the list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> Add(DataType newData)
    {
        if (listCount + 1 > listCapacity)
        {
            Reallocate();
        }

        listCount++;

        list[listCount - 1] = newData;

        return this;
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

        return list[listCount];
    }

    /// <summary>
    /// Adds a new element at the front of the list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> AddFirst(DataType newData)
    {
        if (listCount + 1 > listCapacity)
        {
            Reallocate();
        }

        listCount++;

        for (int i = listCount - 1; i >= 1; i--)
        {
            list[i] = list[i - 1];
        }

        list[0] = newData;

        return this;
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

        DataType newData = list[0];

        for (int i = 1; i <= listCount; i++)
        {
            list[i - 1] = list[i];
        }

        return newData;
    }

    /// <summary>
    /// Adds a new element in the list at a given index and shift following elements forward
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public List<DataType> Insert(int index, DataType newData)
    {
        if (listCount + 1 > listCapacity)
        {
            Reallocate();
        }

        listCount++;

        for (int i = listCount - 1; i >= index; i--)
        {
            list[i] = list[i - 1];
        }

        list[index] = newData;

        return this;
    }

    /// <summary>
    /// Removes a element in the list at a given index and shift following elements back, returns the removed data
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType RemoveAt(int index)
    {
        listCount--;

        DataType data = list[index];

        for (int i = index + 1; i <= listCount; i++)
        {
            list[i - 1] = list[i];
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

        if (index != -1)
        {
            RemoveAt(index);
        }

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

        if (index != -1)
        {
            RemoveAt(index);
        }

        return index;
    }

    /// <summary>
    /// Swaps two elements at two given indicies
    /// </summary>
    /// <param name="index1"></param>
    /// <param name="index2"></param>
    /// <returns></returns>
    public List<DataType> Swap(int index1, int index2)
    {
        if (index1 == index2)
        {
            return this;
        }

        DataType temp = list[index2];

        list[index2] = list[index1];

        list[index1] = temp;

        return this;
    }

    /// <summary>
    /// Clears the list's data with a new capacity
    /// </summary>
    /// <param name="newCapacity"></param>
    /// <returns></returns>
    public int Clear(int newCapacity = 1)
    {
        int total = listCount;

        list = new DataType[newCapacity];

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
        DataType data = list[index];

        list[index] = newData;

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
        int index = IndexOf(replacedData);

        if (index == -1)
        {
            return index;
        }

        list[index] = newData;

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
        int index = LastIndexOf(replacedData);

        if (index == -1)
        {
            return index;
        }

        list[index] = newData;

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
            if (list[i].Equals(replacedData))
            {
                list[i] = newData;

                total++;
            }
        }

        return total;
    }


    // OPERATIONS

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
            if (list[i].Equals(removedData))
            {
                list[i] = list[i + 1];

                total++;

                i--;
            }
        }

        if (list[listCount - 1].Equals(removedData))
        {
            total++;
        }

        listCount -= total;

        return total;
    }

    /// <summary>
    /// Bubble sorts the elements of the list relative to the given sort order
    /// </summary>
    /// <param name="sortOrder"></param>
    /// <returns></returns>
    public List<DataType> Sort<SortType>(params SortType[] sortOrder) where SortType : IComparable
    {
        if (listCount <= 1)
        {
            return this;
        }

        for (int i = 0; i < listCount - 1; i++)
        {
            for (int j = 0; j < listCount - i - 1; j++)
            {
                if (sortOrder[j].CompareTo(sortOrder[j + 1]) > 0)
                {
                    Swap(j, j + 1);

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
    public List<DataType> Sort<SortType>(List<SortType> sortOrder) where SortType : IComparable
    {
        return Sort(sortOrder.ToArray());
    }

    /// <summary>
    /// Reverse the list elements
    /// </summary>
    /// <returns></returns>
    public List<DataType> Reverse()
    {
        if (listCount <= 1)
        {
            return this;
        }

        for (int i = 0; i < listCount / 2; i++)
        {
            Swap(i, listCount - i - 1);
        }

        return this;
    }

    /// <summary>
    /// Swaps the list's elements and capacity with the elements and capacity of another list
    /// </summary>
    /// <param name="swappedData"></param>
    /// <returns></returns>
    public List<DataType> Swap(List<DataType> swappedData)
    {
        DataType[] data = list;

        int count = listCount;

        int capacity = listCapacity;

        int expansions = listExpansions;

        list = swappedData.list;

        listCount = swappedData.listCount;

        listCapacity = swappedData.listCapacity;

        listExpansions = swappedData.listExpansions;

        swappedData.list = data;

        swappedData.listCount = count;

        swappedData.listCapacity = capacity;

        swappedData.listExpansions = expansions;

        return this;
    }

    /// <summary>
    /// Returns a copy of the list's data
    /// </summary>
    /// <returns></returns>
    public List<DataType> Copy()
    {
        return new List<DataType>(this);
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
            slice.Add(list[i]);
        }

        return slice;
    }

    /// <summary>
    /// Shifts the list elements right
    /// </summary>
    /// <param name="numberOfShifts"></param>
    /// <returns></returns>
    public List<DataType> ShiftRight(int numberOfShifts)
    {
        if (listCount <= 1)
        {
            return this;
        }

        if (numberOfShifts % listCount == 0)
        {
            return this;
        }

        DataType[] temp = new DataType[listCount];

        for (int i = 0; i < listCount; i++)
        {
            temp[i] = list[i];
        }

        list = new DataType[listCapacity];

        for (int i = 0; i < listCount; i++)
        {
            list[i] = temp[((i - numberOfShifts) % listCount + listCount) % listCount];
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
            log += (list[i] + ", ");
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
        return list.GetEnumerator();
    }

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    IEnumerator<DataType> IEnumerable<DataType>.GetEnumerator()
    {
        return (IEnumerator<DataType>)ToArray().GetEnumerator();
    }
}
