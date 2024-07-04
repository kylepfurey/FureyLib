
// Stack and Priority Stack Data Types Script
// by Kyle Furey

using System.Collections;
using System.Collections.Generic;

// Data type used for priority value
using PriorityType = System.Single;

/// <summary>
/// A last in first out list of a specified data type.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class Stack<DataType> : IEnumerable
{
    /// <summary>
    /// The list of nodes in stack in order of newest to oldest
    /// </summary>
    private List<DataType> stack = new List<DataType>();

    /// <summary>
    /// Add a new node to the stack and return the index
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int StackOn(DataType data)
    {
        // Add the stacked node to the end of the list
        stack.Insert(0, data);

        return stack.Count - 1;
    }

    /// <summary>
    /// Removes and returns the newest node
    /// </summary>
    /// <returns></returns>
    public DataType Unstack()
    {
        // Check if the stack is empty
        if (stack.Count == 0)
        {
            return default(DataType);
        }

        // Store the newest node
        DataType unstackedNode = stack[0];

        // Remove the newest node from the stack
        stack.RemoveAt(0);

        // Return our removed node
        return unstackedNode;
    }

    /// <summary>
    /// Add a new node to the stack and return the index (identical to stack)
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int Push(DataType data)
    {
        return StackOn(data);
    }

    /// <summary>
    /// Removes and returns the newest node (identical to unstack)
    /// </summary>
    /// <returns></returns>
    public DataType Pop()
    {
        return Unstack();
    }

    /// <summary>
    /// Returns the newest data (without removing it from the stack)
    /// </summary>
    /// <returns></returns>
    public DataType Peek()
    {
        return stack[0];
    }

    /// <summary>
    /// Returns the newest data (without removing it from the stack)
    /// </summary>
    /// <returns></returns>
    public DataType PeekLast()
    {
        return stack[stack.Count - 1];
    }

    /// <summary>
    /// Returns the data at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType Get(int index)
    {
        return stack[index];
    }

    /// <summary>
    /// Sets the data at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Stack<DataType> Set(int index, DataType newData)
    {
        stack[index] = newData;

        return this;
    }

    /// <summary>
    /// Clears the stack and returns the total number of cleared nodes
    /// </summary>
    /// <returns></returns>
    public int Clear()
    {
        int total = stack.Count;

        stack.Clear();

        return total;
    }

    /// <summary>
    /// Returns the size of the stack
    /// </summary>
    /// <returns></returns>
    public int Count()
    {
        return stack.Count;
    }

    /// <summary>
    /// Returns if the stack is empty
    /// </summary>
    /// <returns></returns>
    public bool IsEmpty()
    {
        return stack.Count == 0;
    }

    /// <summary>
    /// Return the index of the given element, or -1 if it was not found
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int Find(DataType data)
    {
        for (int i = 0; i < stack.Count; i++)
        {
            if (stack[i].Equals(data))
            {
                return i;
            }
        }

        return -1;
    }

    /// <summary>
    /// Return whether the stack contains the given element
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public bool Contains(DataType data)
    {
        for (int i = 0; i < stack.Count; i++)
        {
            if (stack[i].Equals(data))
            {
                return true;
            }
        }

        return false;
    }

    /// <summary>
    /// Return the number of matching elements
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int Total(DataType data)
    {
        int total = 0;

        for (int i = 0; i < stack.Count; i++)
        {
            if (stack[i].Equals(data))
            {
                total++;
            }
        }

        return total;
    }

    /// <summary>
    /// Returns an array of the current stack data
    /// </summary>
    /// <returns></returns>
    public DataType[] ToArray()
    {
        return stack.ToArray();
    }

    /// <summary>
    /// Returns a list of the current stack data
    /// </summary>
    /// <returns></returns>
    public List<DataType> ToList()
    {
        return stack;
    }

    /// <summary>
    /// Default constructor
    /// </summary>
    public Stack()
    {
        stack = new List<DataType>();
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="data"></param>
    public Stack(params DataType[] data)
    {
        stack = new List<DataType>(data.Length);

        for (int i = 0; i < data.Length; i++)
        {
            stack.Insert(0, data[i]);
        }
    }

    /// <summary>
    /// List constructor
    /// </summary>
    /// <param name="data"></param>
    public Stack(List<DataType> data)
    {
        stack = data;
    }

    /// <summary>
    /// Stack constructor
    /// </summary>
    /// <param name="data"></param>
    public Stack(Stack<DataType> data)
    {
        stack = data.stack;
    }

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return stack.GetEnumerator();
    }
}

/// <summary>
/// A last in first out list of a specified data type with an associated priority value assigned to each element used for adding and removing data in a specific order.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class PriorityStack<DataType>
{
    /// <summary>
    /// The list of nodes in stack in order of newest to oldest and lowest priority to highest priority
    /// </summary>
    private List<DataType> stack = new List<DataType>();

    /// <summary>
    /// The list of priority corresponding with the list of nodes
    /// </summary>
    private List<PriorityType> priority = new List<PriorityType>();

    /// <summary>
    /// Add a new node to the stack and return the index
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public int Stack(DataType data, PriorityType priority)
    {
        for (int i = 0; i < stack.Count; i++)
        {
            if (priority >= this.priority[i])
            {
                stack.Insert(i, data);

                this.priority.Insert(i, priority);

                return i;
            }
        }

        stack.Add(data);

        this.priority.Add(priority);

        return stack.Count - 1;
    }

    /// <summary>
    /// Removes the newest node with the lowest priority and return the removed node
    /// </summary>
    /// <returns></returns>
    public DataType Unstack()
    {
        DataType unstackedData = stack[0];

        stack.RemoveAt(0);

        return unstackedData;
    }

    /// <summary>
    /// Add a new node to the stack and return the index (identical to stack)
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public int Push(DataType data, PriorityType priority)
    {
        return Stack(data, priority);
    }

    /// <summary>
    /// Removes the newest node with the lowest priority and return the removed node (identical to unstack)
    /// </summary>
    /// <returns></returns>
    public DataType Pop()
    {
        return Unstack();
    }

    /// <summary>
    /// Returns the data with the highest priority (without removing it from the stack)
    /// </summary>
    /// <returns></returns>
    public DataType Peek()
    {
        return stack[0];
    }

    /// <summary>
    /// Returns the data with the lowest priority (without removing it from the stack)
    /// </summary>
    /// <returns></returns>
    public DataType PeekLast()
    {
        return stack[stack.Count - 1];
    }

    /// <summary>
    /// Returns the data at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType Get(int index)
    {
        return stack[index];
    }

    /// <summary>
    /// Returns the data at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public DataType Get(int index, out PriorityType priority)
    {
        priority = this.priority[index];

        return stack[index];
    }

    /// <summary>
    /// Sets the data at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public PriorityStack<DataType> Set(int index, DataType newData)
    {
        stack[index] = newData;

        return this;
    }

    /// <summary>
    /// Sets the data at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <param name="newPriority"></param>
    /// <returns></returns>
    public PriorityStack<DataType> Set(int index, DataType newData, PriorityType newPriority)
    {
        stack[index] = newData;

        priority[index] = newPriority;

        return this;
    }

    /// <summary>
    /// Returns the highest priority value (the priority which is closest to being unstacked)
    /// </summary>
    /// <returns></returns>
    public PriorityType HighestPriority()
    {
        return priority[0];
    }

    /// <summary>
    /// Returns the lowest priority value (the priority which is furthest from being unstacked)
    /// </summary>
    /// <returns></returns>
    public PriorityType LowestPriority()
    {
        return priority[priority.Count - 1];
    }

    /// <summary>
    /// Returns the priority value of the given data in the stack
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public PriorityType GetPriority(DataType data)
    {
        PriorityType priority = 0;

        for (int i = 0; i < stack.Count; i++)
        {
            if (stack[i].Equals(data))
            {
                return this.priority[i];
            }
        }

        return priority;
    }

    /// <summary>
    /// Returns the priority value at the given index in the stack
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public PriorityType GetPriorityAt(int index)
    {
        return priority[index];
    }

    /// <summary>
    /// Sets the priority value of the given data
    /// </summary>
    /// <param name="data"></param>
    /// <param name="newPriority"></param>
    /// <returns></returns>
    public PriorityStack<DataType> SetPriority(DataType data, PriorityType newPriority)
    {
        for (int i = 0; i < stack.Count; i++)
        {
            if (stack[i].Equals(data))
            {
                priority[i] = newPriority;

                return this;
            }
        }

        return this;
    }

    /// <summary>
    /// Sets the priority value at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newPriority"></param>
    /// <returns></returns>
    public PriorityStack<DataType> SetPriorityAt(int index, PriorityType newPriority)
    {
        priority[index] = newPriority;

        return this;
    }

    /// <summary>
    /// Clears the stack and returns the total number of cleared nodes
    /// </summary>
    /// <returns></returns>
    public int Clear()
    {
        int total = stack.Count;

        stack.Clear();

        priority.Clear();

        return total;
    }

    /// <summary>
    /// Returns the size of the stack
    /// </summary>
    /// <returns></returns>
    public int Count()
    {
        return stack.Count;
    }

    /// <summary>
    /// Returns if the stack is empty
    /// </summary>
    /// <returns></returns>
    public bool IsEmpty()
    {
        return stack.Count == 0;
    }

    /// <summary>
    /// Return the index of the given element, or -1 if it was not found
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int Find(DataType data)
    {
        for (int i = 0; i < stack.Count; i++)
        {
            if (stack[i].Equals(data))
            {
                return i;
            }
        }

        return -1;
    }

    /// <summary>
    /// Return whether the stack contains the given element
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public bool Contains(DataType data)
    {
        for (int i = 0; i < stack.Count; i++)
        {
            if (stack[i].Equals(data))
            {
                return true;
            }
        }

        return false;
    }

    /// <summary>
    /// Return the number of matching elements
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int Total(DataType data)
    {
        int total = 0;

        for (int i = 0; i < stack.Count; i++)
        {
            if (stack[i].Equals(data))
            {
                total++;
            }
        }

        return total;
    }

    /// <summary>
    /// Returns an array of the current stack data
    /// </summary>
    /// <returns></returns>
    public DataType[] ToArray()
    {
        return stack.ToArray();
    }

    /// <summary>
    /// Returns a list of the current stack data
    /// </summary>
    /// <returns></returns>
    public List<DataType> ToList()
    {
        return stack;
    }

    /// <summary>
    /// Returns an array of the current stack's priority values
    /// </summary>
    /// <returns></returns>
    public PriorityType[] PriorityToArray()
    {
        return priority.ToArray();
    }

    /// <summary>
    /// Returns a list of the current stack's priority values
    /// </summary>
    /// <returns></returns>
    public List<PriorityType> PriorityToList()
    {
        return priority;
    }

    /// <summary>
    /// Returns a dictionary of the current stack data and their priorities
    /// </summary>
    /// <returns></returns>
    public Dictionary<DataType, PriorityType> ToDictionary()
    {
        Dictionary<DataType, PriorityType> dictionary = new Dictionary<DataType, PriorityType>(stack.Count);

        for (int i = 0; i < stack.Count; i++)
        {
            dictionary[stack[i]] = priority[i];
        }

        return dictionary;
    }

    /// <summary>
    /// Default constructor
    /// </summary>
    public PriorityStack()
    {
        stack = new List<DataType>();

        priority = new List<PriorityType>();
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityStack(DataType[] data, PriorityType[] priority)
    {
        stack = new List<DataType>(data.Length);

        this.priority = new List<PriorityType>(data.Length);

        for (int i = 0; i < data.Length; i++)
        {
            Stack(data[i], priority[i]);
        }
    }

    /// <summary>
    /// List constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityStack(List<DataType> data, List<PriorityType> priority)
    {
        stack = new List<DataType>(data.Count);

        this.priority = new List<PriorityType>(data.Count);

        for (int i = 0; i < data.Count; i++)
        {
            Stack(data[i], priority[i]);
        }
    }

    /// <summary>
    /// Stack constructor
    /// </summary>
    /// <param name="data"></param>
    public PriorityStack(PriorityStack<DataType> data)
    {
        stack = data.stack;

        priority = data.priority;
    }
}
