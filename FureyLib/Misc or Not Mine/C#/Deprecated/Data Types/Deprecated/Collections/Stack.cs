
// Stack Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/stack/stack/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.stack?view=net-8.0

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

/// <summary>
/// Wrapper class of a linked list allowing first in last out access of its elements.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class Stack<DataType> : IEnumerable, IEnumerable<DataType>
{
    // VARIABLES

    /// <summary>
    /// The linked list holding the data of the stack
    /// </summary>
    private LinkedList<DataType> stack = new LinkedList<DataType>();


    // PROPERTIES

    /// <summary>
    /// Readonly count variable
    /// </summary>
    public int Count
    {
        get
        {
            return stack.Count;
        }
    }


    // TO ARRAY AND LIST

    /// <summary>
    /// Returns an array of the current stack
    /// </summary>
    /// <returns></returns>
    public DataType[] ToArray()
    {
        DataType[] array = new DataType[stack.Count];

        int i = 0;

        foreach (DataType node in stack)
        {
            array[i] = node;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a list of the current stack
    /// </summary>
    /// <returns></returns>
    public List<DataType> ToList()
    {
        List<DataType> list = new List<DataType>(stack.Count);

        int i = 0;

        foreach (DataType node in stack)
        {
            list.Add(node);

            i++;
        }

        return list;
    }


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Stack()
    {
        stack = new LinkedList<DataType>();
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copiedStack"></param>
    public Stack(Stack<DataType> copiedStack)
    {
        stack = new LinkedList<DataType>(copiedStack.stack);
    }

    /// <summary>
    /// Data constructor
    /// </summary>
    /// <param name="data"></param>
    public Stack(DataType data)
    {
        stack = new LinkedList<DataType>();

        stack.AddLast(data);
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="array"></param>
    public Stack(params DataType[] array)
    {
        stack = new LinkedList<DataType>();

        for (int i = 0; i < array.Length; i++)
        {
            stack.AddFirst(array[i]);
        }
    }

    /// <summary>
    /// Enumerable constructor
    /// </summary>
    /// <param name="list"></param>
    public Stack(IEnumerable<DataType> list)
    {
        stack = new LinkedList<DataType>();

        foreach (DataType data in list)
        {
            stack.AddFirst(data);
        }
    }


    // EQUALITY

    /// <summary>
    /// Check if another stack is equal to the stack
    /// </summary>
    /// <param name="comparedStack"></param>
    /// <returns></returns>
    public bool Equals(Stack<DataType> comparedStack)
    {
        return stack == comparedStack.stack;
    }

    /// <summary>
    /// Check if another stack is equal to the stack
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedStack"></param>
    /// <returns></returns>
    public static bool operator ==(Stack<DataType> list, Stack<DataType> comparedStack)
    {
        return list.Equals(comparedStack);
    }

    /// <summary>
    /// Check if another stack is not equal to the stack
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedStack"></param>
    /// <returns></returns>
    public static bool operator !=(Stack<DataType> list, Stack<DataType> comparedStack)
    {
        return !list.Equals(comparedStack);
    }


    // CAPACITY

    /// <summary>
    /// Returns whether the stack is empty
    /// </summary>
    /// <returns></returns>
    public bool Empty()
    {
        return stack.Count == 0;
    }

    /// <summary>
    /// Returns the current number of elements of the stack
    /// </summary>
    /// <returns></returns>
    public int Size()
    {
        return stack.Count;
    }


    // ELEMENT ACCESS

    /// <summary>
    /// Returns the most recent element without popping it
    /// </summary>
    /// <returns></returns>
    public DataType Peek()
    {
        return stack.First.Value;
    }

    /// <summary>
    /// Returns the oldest element
    /// </summary>
    /// <returns></returns>
    public DataType PeekLast()
    {
        return stack.Last.Value;
    }


    // LOCATING ELEMENTS

    /// <summary>
    /// Returns whether the stack contains at least one of the elements 
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool Contains(DataType containedData)
    {
        return stack.Contains(containedData);
    }


    // MODIFIERS

    /// <summary>
    /// Assigns the stack's elements from another stack's elements
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Stack<DataType> Assign(Stack<DataType> newData)
    {
        stack = new LinkedList<DataType>(newData.stack);

        return this;
    }

    /// <summary>
    /// Inserts a new element of the given data at the top of the stack
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public Stack<DataType> Push(DataType data)
    {
        stack.AddFirst(data);

        return this;
    }

    /// <summary>
    /// Remove and return the top element from the stack
    /// </summary>
    /// <returns></returns>
    public DataType Pop()
    {
        DataType element = stack.First.Value;

        stack.RemoveFirst();

        return element;
    }

    /// <summary>
    /// Clears the stack
    /// </summary>
    /// <returns></returns>
    public int Clear()
    {
        int total = stack.Count;

        stack.Clear();

        return total;
    }


    // OPERATIONS

    /// <summary>
    /// Swaps the stack with another stack
    /// </summary>
    /// <param name="swappedData"></param>
    /// <returns></returns>
    public Stack<DataType> Swap(Stack<DataType> swappedData)
    {
        LinkedList<DataType> data = stack;

        stack = swappedData.stack;

        swappedData.stack = data;

        return this;
    }

    /// <summary>
    /// Reverse the stack
    /// </summary>
    /// <returns></returns>
    public Stack<DataType> Reverse()
    {
        stack.Reverse();

        return this;
    }

    /// <summary>
    /// Returns a copy of the stack's data
    /// </summary>
    /// <returns></returns>
    public Stack<DataType> Copy()
    {
        return new Stack<DataType>(this);
    }


    // TO STRING

    /// <summary>
    /// Converts the elements of the stack into a string
    /// </summary>
    /// <returns></returns>
    public string ToString()
    {
        if (stack.Count == 0)
        {
            return "{ }";
        }

        DataType[] data = ToArray();

        string log = "{ ";

        for (int i = 0; i < data.Length; i++)
        {
            log += (data[i] + ", ");
        }

        log = log.Remove(log.Length - 2, 1);

        log += "}";

        return log;
    }


    // ENUMERATOR FUNCTIONS

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return ToArray().GetEnumerator();
    }

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    IEnumerator<DataType> IEnumerable<DataType>.GetEnumerator()
    {
        return (IEnumerator<DataType>)ToArray().GetEnumerator();
    }

    /// <summary>
    /// Inserts a new element of the given data at the top of the stack
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public Stack<DataType> Add(DataType data)
    {
        return Push(data);
    }
}
