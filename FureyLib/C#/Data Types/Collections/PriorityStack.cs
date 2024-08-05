
// Priority Stack Container Script
// by Kyle Furey

// REFERENCES: https://en.cppreference.com/w/cpp/container/priority_queue, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.priorityqueue-2?view=net-8.0

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

// The default priority type used for sorting
using PriorityType = System.Single;

/// <summary>
/// •  Wrapper class of a linked list allowing first in last out access of its elements.<br/>
/// •  Each element has its own associated priority value used for automatic sorting on insertion.<br/>
/// •  Elements with higher priority are popped first.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class PriorityStack<DataType> : IEnumerable, IEnumerable<DataType>
{
    // VARIABLES

    /// <summary>
    /// The linked list holding the data and priority values of the stack
    /// </summary>
    private LinkedList<PriorityStackNode<DataType>> stack = new LinkedList<PriorityStackNode<DataType>>();


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

        foreach (PriorityStackNode<DataType> node in stack)
        {
            array[i] = node.data;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns an array of the current stack's priority
    /// </summary>
    /// <returns></returns>
    public PriorityType[] PriorityToArray()
    {
        PriorityType[] array = new PriorityType[stack.Count];

        int i = 0;

        foreach (PriorityStackNode<DataType> node in stack)
        {
            array[i] = node.priority;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a list of the current stack's data
    /// </summary>
    /// <returns></returns>
    public List<DataType> ToList()
    {
        List<DataType> list = new List<DataType>(stack.Count);

        int i = 0;

        foreach (PriorityStackNode<DataType> node in stack)
        {
            list.Add(node.data);

            i++;
        }

        return list;
    }

    /// <summary>
    /// Returns a list of the current stack's priority
    /// </summary>
    /// <returns></returns>
    public List<PriorityType> PriorityToList()
    {
        List<PriorityType> list = new List<PriorityType>(stack.Count);

        int i = 0;

        foreach (PriorityStackNode<DataType> node in stack)
        {
            list.Add(node.priority);

            i++;
        }

        return list;
    }


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public PriorityStack()
    {
        stack = new LinkedList<PriorityStackNode<DataType>>();
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copiedStack"></param>
    public PriorityStack(PriorityStack<DataType> copiedStack)
    {
        stack = new LinkedList<PriorityStackNode<DataType>>(copiedStack.stack);
    }

    /// <summary>
    /// Data constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityStack(DataType data, PriorityType priority)
    {
        stack = new LinkedList<PriorityStackNode<DataType>>();

        stack.AddLast(new PriorityStackNode<DataType>(this, data, priority));
    }


    // EQUALITY

    /// <summary>
    /// Check if another stack is equal to the stack
    /// </summary>
    /// <param name="comparedStack"></param>
    /// <returns></returns>
    public bool Equals(PriorityStack<DataType> comparedStack)
    {
        return stack == comparedStack.stack;
    }

    /// <summary>
    /// Check if another stack is equal to the stack
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedStack"></param>
    /// <returns></returns>
    public static bool operator ==(PriorityStack<DataType> list, PriorityStack<DataType> comparedStack)
    {
        return list.Equals(comparedStack);
    }

    /// <summary>
    /// Check if another stack is not equal to the stack
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedStack"></param>
    /// <returns></returns>
    public static bool operator !=(PriorityStack<DataType> list, PriorityStack<DataType> comparedStack)
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
    /// Returns the highest priority element without popping it
    /// </summary>
    /// <returns></returns>
    public DataType Peek()
    {
        return stack.First.Value.data;
    }

    /// <summary>
    /// Returns the lowest priority element
    /// </summary>
    /// <returns></returns>
    public DataType PeekLast()
    {
        return stack.Last.Value.data;
    }

    /// <summary>
    /// Returns the highest priority element and its priority without popping it
    /// </summary>
    /// <returns></returns>
    public PriorityStackNode<DataType> PeekNode()
    {
        return stack.First.Value;
    }

    /// <summary>
    /// Returns the lowest priority element and its priority
    /// </summary>
    /// <returns></returns>
    public PriorityStackNode<DataType> PeekLastNode()
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
        foreach (PriorityStackNode<DataType> node in stack)
        {
            if (node.data.Equals(containedData))
            {
                return true;
            }
        }

        return false;
    }

    /// <summary>
    /// Returns the highest priority value
    /// </summary>
    /// <returns></returns>
    public PriorityType HighestPriority()
    {
        return stack.First.Value.priority;
    }

    /// <summary>
    /// Returns the lowest priority value
    /// </summary>
    /// <returns></returns>
    public PriorityType LowestPriority()
    {
        return stack.Last.Value.priority;
    }


    // MODIFIERS

    /// <summary>
    /// Assigns the stack's elements from another stack's elements
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public PriorityStack<DataType> Assign(PriorityStack<DataType> newData)
    {
        stack = new LinkedList<PriorityStackNode<DataType>>(newData.stack);

        return this;
    }

    /// <summary>
    /// Inserts a new element of the given data into the stack based on its priority value
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public PriorityStack<DataType> Push(DataType data, PriorityType priority)
    {
        if (stack.Count == 0)
        {
            stack.AddLast(new PriorityStackNode<DataType>(this, data, priority));

            return this;
        }

        LinkedListNode<PriorityStackNode<DataType>> node = stack.First;

        for (int i = 0; i < stack.Count; i++)
        {
            if (priority >= node.Value.priority)
            {
                stack.AddBefore(node, new PriorityStackNode<DataType>(this, data, priority));

                return this;
            }

            node = node.Next;
        }

        stack.AddLast(new PriorityStackNode<DataType>(this, data, priority));

        return this;
    }

    /// <summary>
    /// Inserts a priority stack node into the stack based on its priority value
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public PriorityStack<DataType> Push(PriorityStackNode<DataType> newNode)
    {
        if (stack.Count == 0)
        {
            newNode.stack = this;

            stack.AddLast(newNode);

            return this;
        }

        LinkedListNode<PriorityStackNode<DataType>> node = stack.First;

        for (int i = 0; i < stack.Count; i++)
        {
            if (newNode.priority >= node.Value.priority)
            {
                newNode.stack = this;

                stack.AddBefore(node, newNode);

                return this;
            }

            node = node.Next;
        }

        newNode.stack = this;

        stack.AddLast(newNode);

        return this;
    }

    /// <summary>
    /// Inserts an existing element of the given data into the stack based on its priority value
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public PriorityStack<DataType> Emplace(ref DataType data, PriorityType priority)
    {
        if (stack.Count == 0)
        {
            stack.AddLast(new PriorityStackNode<DataType>(this, data, priority));

            return this;
        }

        LinkedListNode<PriorityStackNode<DataType>> node = stack.First;

        for (int i = 0; i < stack.Count; i++)
        {
            if (priority >= node.Value.priority)
            {
                stack.AddBefore(node, new PriorityStackNode<DataType>(this, data, priority));

                return this;
            }

            node = node.Next;
        }

        stack.AddLast(new PriorityStackNode<DataType>(this, data, priority));

        return this;
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the stack
    /// </summary>
    /// <returns></returns>
    public DataType Pop()
    {
        DataType element = stack.First.Value.data;

        stack.RemoveFirst();

        return element;
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the stack with its priority
    /// </summary>
    /// <returns></returns>
    public PriorityStackNode<DataType> PopNode()
    {
        PriorityStackNode<DataType> element = stack.First.Value;

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
    public PriorityStack<DataType> Swap(PriorityStack<DataType> swappedData)
    {
        LinkedList<PriorityStackNode<DataType>> data = stack;

        stack = swappedData.stack;

        swappedData.stack = data;

        return this;
    }

    /// <summary>
    /// Returns a copy of the stack's data
    /// </summary>
    /// <returns></returns>
    public PriorityStack<DataType> Copy()
    {
        return new PriorityStack<DataType>(this);
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

        PriorityType[] priority = PriorityToArray();

        string log = "{ ";

        for (int i = 0; i < data.Length; i++)
        {
            log += (data[i] + " : " + priority[i] + ", ");
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
    /// Inserts a new element of the given data into the stack based on its priority value
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public PriorityStack<DataType> Add(DataType data, PriorityType priority)
    {
        return Push(data, priority);
    }
}

/// <summary>
/// Class that stores data and its priority value for insertion in a priority stack.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class PriorityStackNode<DataType>
{
    // VARIABLES

    /// <summary>
    /// This node's priority stack
    /// </summary>
    public PriorityStack<DataType> stack = null;

    /// <summary>
    /// This node's data
    /// </summary>
    public DataType data = default(DataType);

    /// <summary>
    /// This node's priority
    /// </summary>
    public PriorityType priority = default(PriorityType);


    // PROPERTIES

    /// <summary>
    /// Readonly stack variable
    /// </summary>
    public PriorityStack<DataType> Stack
    {
        get
        {
            return stack;
        }
    }

    /// <summary>
    /// Readonly data variable
    /// </summary>
    public DataType Value
    {
        get
        {
            return data;
        }
    }

    /// <summary>
    /// Readonly priority variable
    /// </summary>
    public PriorityType Priority
    {
        get
        {
            return priority;
        }
    }


    // CONSTRUCTOR

    /// <summary>
    /// Default constructor
    /// </summary>
    /// <param name="stack"></param>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityStackNode(PriorityStack<DataType> stack = null, DataType data = default(DataType), PriorityType priority = default(PriorityType))
    {
        this.stack = stack;

        this.data = data;

        this.priority = priority;
    }
}

/// <summary>
/// •  Wrapper class of a linked list allowing first in last out access of its elements.<br/>
/// •  Each element has its own associated priority value used for automatic sorting on insertion.<br/>
/// •  Elements with higher priority are popped first.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class PriorityStack<DataType, PriorityType> : IEnumerable, IEnumerable<DataType> where PriorityType : IComparable, IComparable<DataType>
{
    // VARIABLES

    /// <summary>
    /// The linked list holding the data and priority values of the stack
    /// </summary>
    private LinkedList<PriorityStackNode<DataType, PriorityType>> stack = new LinkedList<PriorityStackNode<DataType, PriorityType>>();


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

        foreach (PriorityStackNode<DataType, PriorityType> node in stack)
        {
            array[i] = node.data;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns an array of the current stack's priority
    /// </summary>
    /// <returns></returns>
    public PriorityType[] PriorityToArray()
    {
        PriorityType[] array = new PriorityType[stack.Count];

        int i = 0;

        foreach (PriorityStackNode<DataType, PriorityType> node in stack)
        {
            array[i] = node.priority;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a list of the current stack's data
    /// </summary>
    /// <returns></returns>
    public List<DataType> ToList()
    {
        List<DataType> array = new List<DataType>(stack.Count);

        int i = 0;

        foreach (PriorityStackNode<DataType, PriorityType> node in stack)
        {
            array[i] = node.data;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a list of the current stack's priority
    /// </summary>
    /// <returns></returns>
    public List<PriorityType> PriorityToList()
    {
        List<PriorityType> array = new List<PriorityType>(stack.Count);

        int i = 0;

        foreach (PriorityStackNode<DataType, PriorityType> node in stack)
        {
            array[i] = node.priority;

            i++;
        }

        return array;
    }


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public PriorityStack()
    {
        stack = new LinkedList<PriorityStackNode<DataType, PriorityType>>();
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copiedStack"></param>
    public PriorityStack(PriorityStack<DataType, PriorityType> copiedStack)
    {
        stack = new LinkedList<PriorityStackNode<DataType, PriorityType>>(copiedStack.stack);
    }

    /// <summary>
    /// Data constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityStack(DataType data, PriorityType priority)
    {
        stack = new LinkedList<PriorityStackNode<DataType, PriorityType>>();

        stack.AddLast(new PriorityStackNode<DataType, PriorityType>(this, data, priority));
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityStack(PriorityStackNode<DataType, PriorityType> node)
    {
        stack = new LinkedList<PriorityStackNode<DataType, PriorityType>>();

        node.stack = this;

        stack.AddLast(node);
    }

    /// <summary>
    /// Node array constructor
    /// </summary>
    /// <param name="nodes"></param>
    public PriorityStack(params PriorityStackNode<DataType, PriorityType>[] nodes)
    {
        stack = new LinkedList<PriorityStackNode<DataType, PriorityType>>();

        for (int i = 0; i < nodes.Length; i++)
        {
            Push(nodes[i]);
        }
    }

    /// <summary>
    /// Enumerable constructor
    /// </summary>
    /// <param name="nodes"></param>
    public PriorityStack(IEnumerable<PriorityStackNode<DataType, PriorityType>> nodes)
    {
        stack = new LinkedList<PriorityStackNode<DataType, PriorityType>>();

        foreach (PriorityStackNode<DataType, PriorityType> node in nodes)
        {
            Push(node);
        }
    }


    // EQUALITY

    /// <summary>
    /// Check if another stack is equal to the stack
    /// </summary>
    /// <param name="comparedStack"></param>
    /// <returns></returns>
    public bool Equals(PriorityStack<DataType, PriorityType> comparedStack)
    {
        return stack == comparedStack.stack;
    }

    /// <summary>
    /// Check if another stack is equal to the stack
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedStack"></param>
    /// <returns></returns>
    public static bool operator ==(PriorityStack<DataType, PriorityType> list, PriorityStack<DataType, PriorityType> comparedStack)
    {
        return list.Equals(comparedStack);
    }

    /// <summary>
    /// Check if another stack is not equal to the stack
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedStack"></param>
    /// <returns></returns>
    public static bool operator !=(PriorityStack<DataType, PriorityType> list, PriorityStack<DataType, PriorityType> comparedStack)
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
    /// Returns the highest priority element without popping it
    /// </summary>
    /// <returns></returns>
    public DataType Peek()
    {
        return stack.First.Value.data;
    }

    /// <summary>
    /// Returns the lowest priority element
    /// </summary>
    /// <returns></returns>
    public DataType PeekLast()
    {
        return stack.Last.Value.data;
    }

    /// <summary>
    /// Returns the highest priority element and its priority without popping it
    /// </summary>
    /// <returns></returns>
    public PriorityStackNode<DataType, PriorityType> PeekNode()
    {
        return stack.First.Value;
    }

    /// <summary>
    /// Returns the lowest priority element and its priority
    /// </summary>
    /// <returns></returns>
    public PriorityStackNode<DataType, PriorityType> PeekLastNode()
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
        foreach (PriorityStackNode<DataType, PriorityType> node in stack)
        {
            if (node.data.Equals(containedData))
            {
                return true;
            }
        }

        return false;
    }

    /// <summary>
    /// Returns the highest priority value
    /// </summary>
    /// <returns></returns>
    public PriorityType HighestPriority()
    {
        return stack.First.Value.priority;
    }

    /// <summary>
    /// Returns the lowest priority value
    /// </summary>
    /// <returns></returns>
    public PriorityType LowestPriority()
    {
        return stack.Last.Value.priority;
    }


    // MODIFIERS

    /// <summary>
    /// Assigns the stack's elements from another stack's elements
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public PriorityStack<DataType, PriorityType> Assign(PriorityStack<DataType, PriorityType> newData)
    {
        stack = new LinkedList<PriorityStackNode<DataType, PriorityType>>(newData.stack);

        return this;
    }

    /// <summary>
    /// Inserts a new element of the given data into the stack based on its priority value
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public PriorityStack<DataType, PriorityType> Push(DataType data, PriorityType priority)
    {
        if (stack.Count == 0)
        {
            stack.AddLast(new PriorityStackNode<DataType, PriorityType>(this, data, priority));

            return this;
        }

        LinkedListNode<PriorityStackNode<DataType, PriorityType>> node = stack.First;

        for (int i = 0; i < stack.Count; i++)
        {
            if (priority.CompareTo(node.Value.priority) >= 0)
            {
                stack.AddBefore(node, new PriorityStackNode<DataType, PriorityType>(this, data, priority));

                return this;
            }

            node = node.Next;
        }

        stack.AddLast(new PriorityStackNode<DataType, PriorityType>(this, data, priority));

        return this;
    }

    /// <summary>
    /// Inserts a priority stack node into the stack based on its priority value
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public PriorityStack<DataType, PriorityType> Push(PriorityStackNode<DataType, PriorityType> newNode)
    {
        if (stack.Count == 0)
        {
            newNode.stack = this;

            stack.AddLast(newNode);

            return this;
        }

        LinkedListNode<PriorityStackNode<DataType, PriorityType>> node = stack.First;

        for (int i = 0; i < stack.Count; i++)
        {
            if (newNode.priority.CompareTo(node.Value.priority) >= 0)
            {
                newNode.stack = this;

                stack.AddBefore(node, newNode);

                return this;
            }

            node = node.Next;
        }

        newNode.stack = this;

        stack.AddLast(newNode);

        return this;
    }

    /// <summary>
    /// Inserts an existing element of the given data into the stack based on its priority value
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public PriorityStack<DataType, PriorityType> Emplace(ref DataType data, PriorityType priority)
    {
        if (stack.Count == 0)
        {
            stack.AddLast(new PriorityStackNode<DataType, PriorityType>(this, data, priority));

            return this;
        }

        LinkedListNode<PriorityStackNode<DataType, PriorityType>> node = stack.First;

        for (int i = 0; i < stack.Count; i++)
        {
            if (priority.CompareTo(node.Value.priority) >= 0)
            {
                stack.AddBefore(node, new PriorityStackNode<DataType, PriorityType>(this, data, priority));

                return this;
            }

            node = node.Next;
        }

        stack.AddLast(new PriorityStackNode<DataType, PriorityType>(this, data, priority));

        return this;
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the stack
    /// </summary>
    /// <returns></returns>
    public DataType Pop()
    {
        DataType element = stack.First.Value.data;

        stack.RemoveFirst();

        return element;
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the stack with its priority
    /// </summary>
    /// <returns></returns>
    public PriorityStackNode<DataType, PriorityType> PopNode()
    {
        PriorityStackNode<DataType, PriorityType> element = stack.First.Value;

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
    public PriorityStack<DataType, PriorityType> Swap(PriorityStack<DataType, PriorityType> swappedData)
    {
        LinkedList<PriorityStackNode<DataType, PriorityType>> data = stack;

        stack = swappedData.stack;

        swappedData.stack = data;

        return this;
    }

    /// <summary>
    /// Returns a copy of the stack's data
    /// </summary>
    /// <returns></returns>
    public PriorityStack<DataType, PriorityType> Copy()
    {
        return new PriorityStack<DataType, PriorityType>(this);
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

        PriorityType[] priority = PriorityToArray();

        string log = "{ ";

        for (int i = 0; i < data.Length; i++)
        {
            log += (data[i] + " : " + priority[i] + ", ");
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
    /// Inserts a new element of the given data into the stack based on its priority value
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public PriorityStack<DataType, PriorityType> Add(DataType data, PriorityType priority)
    {
        return Push(data, priority);
    }
}

/// <summary>
/// Class that stores data and its priority value for insertion in a priority stack.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class PriorityStackNode<DataType, PriorityType> where PriorityType : IComparable, IComparable<DataType>
{
    // VARIABLES

    /// <summary>
    /// This node's priority stack
    /// </summary>
    public PriorityStack<DataType, PriorityType> stack = null;

    /// <summary>
    /// This node's data
    /// </summary>
    public DataType data = default(DataType);

    /// <summary>
    /// This node's priority
    /// </summary>
    public PriorityType priority = default(PriorityType);


    // PROPERTIES

    /// <summary>
    /// Readonly stack variable
    /// </summary>
    public PriorityStack<DataType, PriorityType> Stack
    {
        get
        {
            return stack;
        }
    }

    /// <summary>
    /// Readonly data variable
    /// </summary>
    public DataType Value
    {
        get
        {
            return data;
        }
    }

    /// <summary>
    /// Readonly priority variable
    /// </summary>
    public PriorityType Priority
    {
        get
        {
            return priority;
        }
    }


    // CONSTRUCTOR

    /// <summary>
    /// Default constructor
    /// </summary>
    /// <param name="stack"></param>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityStackNode(PriorityStack<DataType, PriorityType> stack = null, DataType data = default(DataType), PriorityType priority = default(PriorityType))
    {
        this.stack = stack;

        this.data = data;

        this.priority = priority;
    }
}
