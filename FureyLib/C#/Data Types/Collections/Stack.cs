
// Stack and Priority Stack Containers Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/stack/stack/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.stack?view=net-8.0, https://en.cppreference.com/w/cpp/container/priority_queue, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.priorityqueue-2?view=net-8.0

using System;
using System.Collections;
using System.Collections.Generic;

// The priority type used for sorting
using PriorityType = System.Single;

/// <summary>
/// Wrapper class of a linked list allowing first in last out access of its elements.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class Stack<DataType> : IEnumerable
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
        List<DataType> array = new List<DataType>(stack.Count);

        int i = 0;

        foreach (DataType node in stack)
        {
            array[i] = node;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a linked list of the current stack
    /// </summary>
    /// <returns></returns>
    public LinkedList<DataType> ToLinkedList()
    {
        return new LinkedList<DataType>(stack);
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
        stack = new LinkedList<DataType>(array);
    }

    /// <summary>
    /// List constructor
    /// </summary>
    /// <param name="list"></param>
    public Stack(List<DataType> list)
    {
        stack = new LinkedList<DataType>(list);
    }

    /// <summary>
    /// Linked list constructor
    /// </summary>
    /// <param name="linkedList"></param>
    public Stack(LinkedList<DataType> linkedList)
    {
        stack = new LinkedList<DataType>(linkedList);
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
        return stack.Last.Value;
    }

    /// <summary>
    /// Returns the most recent element without popping it safely
    /// </summary>
    /// <returns></returns>
    public DataType TryPeek()
    {
        if (stack.Count == 0)
        {
            return default(DataType);
        }

        return stack.Last.Value;
    }

    /// <summary>
    /// Returns the oldest element
    /// </summary>
    /// <returns></returns>
    public DataType PeekLast()
    {
        return stack.First.Value;
    }

    /// <summary>
    /// Returns the oldest element safely
    /// </summary>
    /// <returns></returns>
    public DataType TryPeekLast()
    {
        if (stack.Count == 0)
        {
            return default(DataType);
        }

        return stack.First.Value;
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
        stack.AddLast(data);

        return this;
    }

    /// <summary>
    /// Inserts an existing element of the given data at the top of the stack
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public Stack<DataType> Emplace(ref DataType data)
    {
        stack.AddLast(data);

        return this;
    }

    /// <summary>
    /// Remove and return the top element from the stack
    /// </summary>
    /// <returns></returns>
    public DataType Pop()
    {
        DataType element = stack.Last.Value;

        stack.RemoveLast();

        return element;
    }

    /// <summary>
    /// Remove and return the top element from the stack safely
    /// </summary>
    /// <returns></returns>
    public DataType TryPop()
    {
        if (stack.Count == 0)
        {
            return default(DataType);
        }

        DataType element = stack.Last.Value;

        stack.RemoveLast();

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
    /// Inserts a new element of the given data at the top of the stack
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public Stack<DataType> Add(DataType data)
    {
        return Push(data);
    }
}

/// <summary>
/// •  Wrapper class of a linked list allowing first in last out access of its elements.<br/>
/// •  Each element has its own associated priority value used for automatic sorting on insertion.<br/>
/// •  Elements with higher priority are popped first.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class PriorityStack<DataType> : IEnumerable
{
    // VARIABLES

    /// <summary>
    /// The linked list holding the data of the stack
    /// </summary>
    private LinkedList<DataType> stack = new LinkedList<DataType>();

    /// <summary>
    /// The linked list holding the priority values of the stack
    /// </summary>
    private LinkedList<PriorityType> priority = new LinkedList<PriorityType>();


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
        List<DataType> array = new List<DataType>(stack.Count);

        int i = 0;

        foreach (DataType node in stack)
        {
            array[i] = node;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a linked list of the current stack
    /// </summary>
    /// <returns></returns>
    public LinkedList<DataType> ToLinkedList()
    {
        return new LinkedList<DataType>(stack);
    }

    /// <summary>
    /// Returns an array of the current stack's priority
    /// </summary>
    /// <returns></returns>
    public PriorityType[] PriorityToArray()
    {
        PriorityType[] array = new PriorityType[stack.Count];

        int i = 0;

        foreach (PriorityType node in priority)
        {
            array[i] = node;

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

        foreach (PriorityType node in priority)
        {
            array[i] = node;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a linked list of the current stack's priority
    /// </summary>
    /// <returns></returns>
    public LinkedList<PriorityType> PriorityToLinkedList()
    {
        return new LinkedList<PriorityType>(priority);
    }


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public PriorityStack()
    {
        stack = new LinkedList<DataType>();

        priority = new LinkedList<PriorityType>();
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copiedStack"></param>
    public PriorityStack(PriorityStack<DataType> copiedStack)
    {
        stack = new LinkedList<DataType>(copiedStack.stack);

        priority = new LinkedList<PriorityType>(copiedStack.priority);
    }

    /// <summary>
    /// Data constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityStack(DataType data, float priority)
    {
        stack = new LinkedList<DataType>();

        stack.AddLast(data);

        this.priority = new LinkedList<PriorityType>();

        this.priority.AddLast(priority);
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
        return stack.Last.Value;
    }

    /// <summary>
    /// Returns the highest priority element without popping it safely
    /// </summary>
    /// <returns></returns>
    public DataType TryPeek()
    {
        if (stack.Count == 0)
        {
            return default(DataType);
        }

        return stack.Last.Value;
    }

    /// <summary>
    /// Returns the lowest priority element
    /// </summary>
    /// <returns></returns>
    public DataType PeekLast()
    {
        return stack.First.Value;
    }

    /// <summary>
    /// Returns the lowest priority element safely
    /// </summary>
    /// <returns></returns>
    public DataType TryPeekLast()
    {
        if (stack.Count == 0)
        {
            return default(DataType);
        }

        return stack.First.Value;
    }

    /// <summary>
    /// Returns the highest priority element and its priority without popping it
    /// </summary>
    /// <returns></returns>
    public (DataType data, PriorityType priority) PeekWithPriority()
    {
        return (stack.Last.Value, priority.Last.Value);
    }

    /// <summary>
    /// Returns the highest priority element and its priority without popping it safely
    /// </summary>
    /// <returns></returns>
    public (DataType data, PriorityType priority) TryPeekWithPriority()
    {
        if (stack.Count == 0)
        {
            return (default(DataType), 0);
        }

        return (stack.Last.Value, priority.Last.Value);
    }

    /// <summary>
    /// Returns the lowest priority element and its priority
    /// </summary>
    /// <returns></returns>
    public (DataType data, PriorityType priority) PeekLastWithPriority()
    {
        return (stack.First.Value, priority.First.Value);
    }

    /// <summary>
    /// Returns the lowest priority element and its priority safely
    /// </summary>
    /// <returns></returns>
    public (DataType data, PriorityType priority) TryPeekLastWithPriority()
    {
        if (stack.Count == 0)
        {
            return (default(DataType), 0);
        }

        return (stack.First.Value, priority.First.Value);
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
    public PriorityStack<DataType> Assign(PriorityStack<DataType> newData)
    {
        stack = new LinkedList<DataType>(newData.stack);

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
            stack.AddLast(data);

            this.priority.AddLast(priority);

            return this;
        }

        LinkedListNode<DataType> dataNode = stack.First;

        LinkedListNode<PriorityType> priorityNode = this.priority.First;

        for (int i = 0; i < stack.Count; i++)
        {
            if (priority >= priorityNode.Value)
            {
                stack.AddBefore(dataNode, data);

                this.priority.AddBefore(priorityNode, priority);

                return this;
            }

            dataNode = dataNode.Next;

            priorityNode = priorityNode.Next;
        }

        stack.AddLast(data);

        this.priority.AddLast(priority);

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
            stack.AddLast(data);

            this.priority.AddLast(priority);

            return this;
        }

        LinkedListNode<DataType> dataNode = stack.First;

        LinkedListNode<PriorityType> priorityNode = this.priority.First;

        for (int i = 0; i < stack.Count; i++)
        {
            if (priority >= priorityNode.Value)
            {
                stack.AddBefore(dataNode, data);

                this.priority.AddBefore(priorityNode, priority);

                return this;
            }

            dataNode = dataNode.Next;

            priorityNode = priorityNode.Next;
        }

        stack.AddLast(data);

        this.priority.AddLast(priority);

        return this;
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the stack
    /// </summary>
    /// <returns></returns>
    public DataType Pop()
    {
        DataType element = stack.First.Value;

        stack.RemoveFirst();

        priority.RemoveFirst();

        return element;
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the stack and its priority
    /// </summary>
    /// <returns></returns>
    public (DataType data, PriorityType priority) PopWithPriority()
    {
        DataType element = stack.First.Value;

        PriorityType priority = this.priority.First.Value;

        stack.RemoveFirst();

        this.priority.RemoveFirst();

        return (element, priority);
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the stack safely
    /// </summary>
    /// <returns></returns>
    public DataType TryPop()
    {
        if (stack.Count == 0)
        {
            return default(DataType);
        }

        DataType element = stack.First.Value;

        stack.RemoveFirst();

        priority.RemoveFirst();

        return element;
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the stack safely and its priority
    /// </summary>
    /// <returns></returns>
    public (DataType data, PriorityType priority) TryPopWithPriority()
    {
        if (stack.Count == 0)
        {
            return (default(DataType), 0);
        }

        DataType element = stack.First.Value;

        PriorityType priority = this.priority.First.Value;

        stack.RemoveFirst();

        this.priority.RemoveFirst();

        return (element, priority);
    }

    /// <summary>
    /// Clears the stack
    /// </summary>
    /// <returns></returns>
    public int Clear()
    {
        int total = stack.Count;

        stack.Clear();

        priority.Clear();

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
        LinkedList<DataType> data = stack;

        LinkedList<PriorityType> priority = this.priority;

        stack = swappedData.stack;

        this.priority = swappedData.priority;

        swappedData.stack = data;

        swappedData.priority = priority;

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
        return queue.GetEnumerator();
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
