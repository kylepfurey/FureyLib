
// Stack and Priority Stack Data Types Script
// by Kyle Furey

using System.Collections;
using System.Collections.Generic;

// Data type used for priority value
using PriorityType = System.Single;

// A last in first out list of a specified data type.
public class Stack<DataType> : IEnumerable
{
    // The list of nodes in stack in order of newest to oldest
    private List<DataType> stack = new List<DataType>();

    // Add a new node to the stack and return the index
    public int StackOn(DataType data)
    {
        // Add the stacked node to the end of the list
        stack.Insert(0, data);

        return stack.Count - 1;
    }

    // Removes and returns the newest node
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

    // Add a new node to the stack and return the index (identical to stack)
    public int Push(DataType data)
    {
        return StackOn(data);
    }

    // Removes and returns the newest node (identical to unstack)
    public DataType Pop()
    {
        return Unstack();
    }

    // Returns the newest data (without removing it from the stack)
    public DataType Peek()
    {
        return stack[0];
    }

    // Returns the newest data (without removing it from the stack)
    public DataType PeekLast()
    {
        return stack[stack.Count - 1];
    }

    // Returns the data at the given index
    public DataType Get(int index)
    {
        return stack[index];
    }

    // Sets the data at the given index
    public Stack<DataType> Set(int index, DataType newData)
    {
        stack[index] = newData;

        return this;
    }

    // Clears the stack and returns the total number of cleared nodes
    public int Clear()
    {
        int total = stack.Count;

        stack.Clear();

        return total;
    }

    // Returns the size of the stack
    public int Count()
    {
        return stack.Count;
    }

    // Returns if the stack is empty
    public bool IsEmpty()
    {
        return stack.Count == 0;
    }

    // Return the index of the given element, or -1 if it was not found
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

    // Return whether the stack contains the given element
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

    // Return the number of matching elements
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

    // Returns an array of the current stack data
    public DataType[] ToArray()
    {
        return stack.ToArray();
    }

    // Returns a list of the current stack data
    public List<DataType> ToList()
    {
        return stack;
    }

    // Default constructor
    public Stack()
    {
        stack = new List<DataType>();
    }

    // Array constructor
    public Stack(params DataType[] data)
    {
        stack = new List<DataType>(data.Length);

        for (int i = 0; i < data.Length; i++)
        {
            stack.Insert(0, data[i]);
        }
    }

    // List constructor
    public Stack(List<DataType> data)
    {
        stack = data;
    }

    // Stack constructor
    public Stack(Stack<DataType> data)
    {
        stack = data.stack;
    }

    // Enumerator implementation
    public IEnumerator GetEnumerator()
    {
        return stack.GetEnumerator();
    }
}

// A last in first out list of a specified data type with an associated priority value assigned to each element used for adding and removing data in a specific order.
public class PriorityStack<DataType>
{
    // The list of nodes in stack in order of newest to oldest and lowest priority to highest priority
    private List<DataType> stack = new List<DataType>();

    // The list of priority corresponding with the list of nodes
    private List<PriorityType> priority = new List<PriorityType>();

    // Add a new node to the stack and return the index
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

    // Removes the newest node with the lowest priority and return the removed node
    public DataType Unstack()
    {
        DataType unstackedData = stack[0];

        stack.RemoveAt(0);

        return unstackedData;
    }

    // Add a new node to the stack and return the index (identical to stack)
    public int Push(DataType data, PriorityType priority)
    {
        return Stack(data, priority);
    }

    // Removes the newest node with the lowest priority and return the removed node (identical to unstack)
    public DataType Pop()
    {
        return Unstack();
    }

    // Returns the data with the highest priority (without removing it from the stack)
    public DataType Peek()
    {
        return stack[0];
    }

    // Returns the data with the lowest priority (without removing it from the stack)
    public DataType PeekLast()
    {
        return stack[stack.Count - 1];
    }

    // Returns the data at the given index
    public DataType Get(int index)
    {
        return stack[index];
    }

    // Returns the data at the given index
    public DataType Get(int index, out PriorityType priority)
    {
        priority = this.priority[index];

        return stack[index];
    }

    // Sets the data at the given index
    public PriorityStack<DataType> Set(int index, DataType newData)
    {
        stack[index] = newData;

        return this;
    }

    // Sets the data at the given index
    public PriorityStack<DataType> Set(int index, DataType newData, PriorityType newPriority)
    {
        stack[index] = newData;

        priority[index] = newPriority;

        return this;
    }

    // Returns the highest priority value (the priority which is closest to being unstacked)
    public PriorityType HighestPriority()
    {
        return priority[0];
    }

    // Returns the lowest priority value (the priority which is furthest from being unstacked)
    public PriorityType LowestPriority()
    {
        return priority[priority.Count - 1];
    }

    // Returns the priority value of the given data in the stack
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

    // Returns the priority value at the given index in the stack
    public PriorityType GetPriorityAt(int index)
    {
        return priority[index];
    }

    // Sets the priority value of the given data
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

    // Sets the priority value at the given index
    public PriorityStack<DataType> SetPriorityAt(int index, PriorityType newPriority)
    {
        priority[index] = newPriority;

        return this;
    }

    // Clears the stack and returns the total number of cleared nodes
    public int Clear()
    {
        int total = stack.Count;

        stack.Clear();

        priority.Clear();

        return total;
    }

    // Returns the size of the stack
    public int Count()
    {
        return stack.Count;
    }

    // Returns if the stack is empty
    public bool IsEmpty()
    {
        return stack.Count == 0;
    }

    // Return the index of the given element, or -1 if it was not found
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

    // Return whether the stack contains the given element
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

    // Return the number of matching elements
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

    // Returns an array of the current stack data
    public DataType[] ToArray()
    {
        return stack.ToArray();
    }

    // Returns a list of the current stack data
    public List<DataType> ToList()
    {
        return stack;
    }

    // Returns an array of the current stack's priority values
    public PriorityType[] PriorityToArray()
    {
        return priority.ToArray();
    }

    // Returns a list of the current stack's priority values
    public List<PriorityType> PriorityToList()
    {
        return priority;
    }

    // Returns a dictionary of the current stack data and their priorities
    public Dictionary<DataType, PriorityType> ToDictionary()
    {
        Dictionary<DataType, PriorityType> dictionary = new Dictionary<DataType, PriorityType>(stack.Count);

        for (int i = 0; i < stack.Count; i++)
        {
            dictionary[stack[i]] = priority[i];
        }

        return dictionary;
    }

    // Default constructor
    public PriorityStack()
    {
        stack = new List<DataType>();

        priority = new List<PriorityType>();
    }

    // Array constructor
    public PriorityStack(DataType[] data, PriorityType[] priority)
    {
        stack = new List<DataType>(data.Length);

        this.priority = new List<PriorityType>(data.Length);

        for (int i = 0; i < data.Length; i++)
        {
            Stack(data[i], priority[i]);
        }
    }

    // List constructor
    public PriorityStack(List<DataType> data, List<PriorityType> priority)
    {
        stack = new List<DataType>(data.Count);

        this.priority = new List<PriorityType>(data.Count);

        for (int i = 0; i < data.Count; i++)
        {
            Stack(data[i], priority[i]);
        }
    }

    // Stack constructor
    public PriorityStack(PriorityStack<DataType> data)
    {
        stack = data.stack;

        priority = data.priority;
    }
}
