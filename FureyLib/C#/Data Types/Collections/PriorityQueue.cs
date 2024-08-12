
// Priority Queue Container Script
// by Kyle Furey

// REFERENCES: https://en.cppreference.com/w/cpp/container/priority_queue, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.priorityqueue-2?view=net-8.0

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

// The default priority type used for sorting
using PriorityType = System.Single;

/// <summary>
/// •  Wrapper class of a linked list allowing first in first out access of its elements.<br/>
/// •  Each element has its own associated priority value used for automatic sorting on insertion.<br/>
/// •  Elements with higher priority are dequeued first.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class PriorityQueue<DataType> : IEnumerable, IEnumerable<DataType>
{
    // VARIABLES

    /// <summary>
    /// The linked list holding the data and priority values of the queue
    /// </summary>
    private LinkedList<PriorityQueueNode<DataType>> queue = new LinkedList<PriorityQueueNode<DataType>>();


    // PROPERTIES

    /// <summary>
    /// Readonly count variable
    /// </summary>
    public int Count
    {
        get
        {
            return queue.Count;
        }
    }


    // TO ARRAY AND LIST

    /// <summary>
    /// Returns an array of the current queue
    /// </summary>
    /// <returns></returns>
    public DataType[] ToArray()
    {
        DataType[] array = new DataType[queue.Count];

        int i = 0;

        foreach (PriorityQueueNode<DataType> node in queue)
        {
            array[i] = node.data;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns an array of the current queue's priority
    /// </summary>
    /// <returns></returns>
    public PriorityType[] PriorityToArray()
    {
        PriorityType[] array = new PriorityType[queue.Count];

        int i = 0;

        foreach (PriorityQueueNode<DataType> node in queue)
        {
            array[i] = node.priority;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a list of the current queue's data
    /// </summary>
    /// <returns></returns>
    public List<DataType> ToList()
    {
        List<DataType> list = new List<DataType>(queue.Count);

        int i = 0;

        foreach (PriorityQueueNode<DataType> node in queue)
        {
            list.Add(node.data);

            i++;
        }

        return list;
    }

    /// <summary>
    /// Returns a list of the current queue's priority
    /// </summary>
    /// <returns></returns>
    public List<PriorityType> PriorityToList()
    {
        List<PriorityType> list = new List<PriorityType>(queue.Count);

        int i = 0;

        foreach (PriorityQueueNode<DataType> node in queue)
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
    public PriorityQueue()
    {
        queue = new LinkedList<PriorityQueueNode<DataType>>();
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copiedQueue"></param>
    public PriorityQueue(PriorityQueue<DataType> copiedQueue)
    {
        queue = new LinkedList<PriorityQueueNode<DataType>>(copiedQueue.queue);
    }

    /// <summary>
    /// Data constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityQueue(DataType data, PriorityType priority)
    {
        queue = new LinkedList<PriorityQueueNode<DataType>>();

        queue.AddLast(new PriorityQueueNode<DataType>(this, data, priority));
    }


    // EQUALITY

    /// <summary>
    /// Check if another queue is equal to the queue
    /// </summary>
    /// <param name="comparedQueue"></param>
    /// <returns></returns>
    public bool Equals(PriorityQueue<DataType> comparedQueue)
    {
        return queue == comparedQueue.queue;
    }

    /// <summary>
    /// Check if another queue is equal to the queue
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedQueue"></param>
    /// <returns></returns>
    public static bool operator ==(PriorityQueue<DataType> list, PriorityQueue<DataType> comparedQueue)
    {
        return list.Equals(comparedQueue);
    }

    /// <summary>
    /// Check if another queue is not equal to the queue
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedQueue"></param>
    /// <returns></returns>
    public static bool operator !=(PriorityQueue<DataType> list, PriorityQueue<DataType> comparedQueue)
    {
        return !list.Equals(comparedQueue);
    }


    // CAPACITY

    /// <summary>
    /// Returns whether the queue is empty
    /// </summary>
    /// <returns></returns>
    public bool Empty()
    {
        return queue.Count == 0;
    }

    /// <summary>
    /// Returns the current number of elements of the queue
    /// </summary>
    /// <returns></returns>
    public int Size()
    {
        return queue.Count;
    }


    // ELEMENT ACCESS

    /// <summary>
    /// Returns the highest priority element without dequeuing it
    /// </summary>
    /// <returns></returns>
    public DataType Peek()
    {
        return queue.First.Value.data;
    }

    /// <summary>
    /// Returns the lowest priority element
    /// </summary>
    /// <returns></returns>
    public DataType PeekLast()
    {
        return queue.Last.Value.data;
    }

    /// <summary>
    /// Returns the highest priority element and its priority without dequeuing it
    /// </summary>
    /// <returns></returns>
    public PriorityQueueNode<DataType> PeekNode()
    {
        return queue.First.Value;
    }

    /// <summary>
    /// Returns the lowest priority element and its priority
    /// </summary>
    /// <returns></returns>
    public PriorityQueueNode<DataType> PeekLastNode()
    {
        return queue.Last.Value;
    }


    // LOCATING ELEMENTS

    /// <summary>
    /// Returns whether the queue contains at least one of the elements 
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool Contains(DataType containedData)
    {
        foreach (PriorityQueueNode<DataType> node in queue)
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
        return queue.First.Value.priority;
    }

    /// <summary>
    /// Returns the lowest priority value
    /// </summary>
    /// <returns></returns>
    public PriorityType LowestPriority()
    {
        return queue.Last.Value.priority;
    }


    // MODIFIERS

    /// <summary>
    /// Assigns the queue's elements from another queue's elements
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public PriorityQueue<DataType> Assign(PriorityQueue<DataType> newData)
    {
        queue = new LinkedList<PriorityQueueNode<DataType>>(newData.queue);

        return this;
    }

    /// <summary>
    /// Inserts a new element of the given data into the queue based on its priority value
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public PriorityQueue<DataType> Enqueue(DataType data, PriorityType priority)
    {
        if (queue.Count == 0)
        {
            queue.AddLast(new PriorityQueueNode<DataType>(this, data, priority));

            return this;
        }

        LinkedListNode<PriorityQueueNode<DataType>> node = queue.First;

        for (int i = 0; i < queue.Count; i++)
        {
            if (priority > node.Value.priority)
            {
                queue.AddBefore(node, new PriorityQueueNode<DataType>(this, data, priority));

                return this;
            }

            node = node.Next;
        }

        queue.AddLast(new PriorityQueueNode<DataType>(this, data, priority));

        return this;
    }

    /// <summary>
    /// Inserts a priority queue node into the queue based on its priority value
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public PriorityQueue<DataType> Enqueue(PriorityQueueNode<DataType> newNode)
    {
        if (queue.Count == 0)
        {
            newNode.queue = this;

            queue.AddLast(newNode);

            return this;
        }

        LinkedListNode<PriorityQueueNode<DataType>> node = queue.First;

        for (int i = 0; i < queue.Count; i++)
        {
            if (newNode.priority > node.Value.priority)
            {
                newNode.queue = this;

                queue.AddBefore(node, newNode);

                return this;
            }

            node = node.Next;
        }

        newNode.queue = this;

        queue.AddLast(newNode);

        return this;
    }

    /// <summary>
    /// Inserts an existing element of the given data into the queue based on its priority value
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public PriorityQueue<DataType> Emplace(ref DataType data, PriorityType priority)
    {
        if (queue.Count == 0)
        {
            queue.AddLast(new PriorityQueueNode<DataType>(this, data, priority));

            return this;
        }

        LinkedListNode<PriorityQueueNode<DataType>> node = queue.First;

        for (int i = 0; i < queue.Count; i++)
        {
            if (priority > node.Value.priority)
            {
                queue.AddBefore(node, new PriorityQueueNode<DataType>(this, data, priority));

                return this;
            }

            node = node.Next;
        }

        queue.AddLast(new PriorityQueueNode<DataType>(this, data, priority));

        return this;
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the queue
    /// </summary>
    /// <returns></returns>
    public DataType Dequeue()
    {
        DataType element = queue.First.Value.data;

        queue.RemoveFirst();

        return element;
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the queue with its priority
    /// </summary>
    /// <returns></returns>
    public PriorityQueueNode<DataType> DequeueNode()
    {
        PriorityQueueNode<DataType> element = queue.First.Value;

        queue.RemoveFirst();

        return element;
    }

    /// <summary>
    /// Clears the queue
    /// </summary>
    /// <returns></returns>
    public int Clear()
    {
        int total = queue.Count;

        queue.Clear();

        return total;
    }


    // OPERATIONS

    /// <summary>
    /// Swaps the queue with another queue
    /// </summary>
    /// <param name="swappedData"></param>
    /// <returns></returns>
    public PriorityQueue<DataType> Swap(PriorityQueue<DataType> swappedData)
    {
        LinkedList<PriorityQueueNode<DataType>> data = queue;

        queue = swappedData.queue;

        swappedData.queue = data;

        return this;
    }

    /// <summary>
    /// Returns a copy of the queue's data
    /// </summary>
    /// <returns></returns>
    public PriorityQueue<DataType> Copy()
    {
        return new PriorityQueue<DataType>(this);
    }


    // TO STRING

    /// <summary>
    /// Converts the elements of the queue into a string
    /// </summary>
    /// <returns></returns>
    public string ToString()
    {
        if (queue.Count == 0)
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
    /// Inserts a new element of the given data into the queue based on its priority value
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public PriorityQueue<DataType> Add(DataType data, PriorityType priority)
    {
        return Enqueue(data, priority);
    }
}

/// <summary>
/// Class that stores data and its priority value for insertion in a priority queue.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class PriorityQueueNode<DataType>
{
    // VARIABLES

    /// <summary>
    /// This node's priority queue
    /// </summary>
    public PriorityQueue<DataType> queue = null;

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
    /// Readonly queue variable
    /// </summary>
    public PriorityQueue<DataType> Queue
    {
        get
        {
            return queue;
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
    /// <param name="queue"></param>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityQueueNode(PriorityQueue<DataType> queue = null, DataType data = default(DataType), PriorityType priority = default(PriorityType))
    {
        this.queue = queue;

        this.data = data;

        this.priority = priority;
    }
}

/// <summary>
/// •  Wrapper class of a linked list allowing first in first out access of its elements.<br/>
/// •  Each element has its own associated priority value used for automatic sorting on insertion.<br/>
/// •  Elements with higher priority are dequeued first.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class PriorityQueue<DataType, PriorityType> : IEnumerable, IEnumerable<DataType> where PriorityType : IComparable, IComparable<DataType>
{
    // VARIABLES

    /// <summary>
    /// The linked list holding the data and priority values of the queue
    /// </summary>
    private LinkedList<PriorityQueueNode<DataType, PriorityType>> queue = new LinkedList<PriorityQueueNode<DataType, PriorityType>>();


    // PROPERTIES

    /// <summary>
    /// Readonly count variable
    /// </summary>
    public int Count
    {
        get
        {
            return queue.Count;
        }
    }


    // TO ARRAY AND LIST

    /// <summary>
    /// Returns an array of the current queue
    /// </summary>
    /// <returns></returns>
    public DataType[] ToArray()
    {
        DataType[] array = new DataType[queue.Count];

        int i = 0;

        foreach (PriorityQueueNode<DataType, PriorityType> node in queue)
        {
            array[i] = node.data;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns an array of the current queue's priority
    /// </summary>
    /// <returns></returns>
    public PriorityType[] PriorityToArray()
    {
        PriorityType[] array = new PriorityType[queue.Count];

        int i = 0;

        foreach (PriorityQueueNode<DataType, PriorityType> node in queue)
        {
            array[i] = node.priority;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a list of the current queue's data
    /// </summary>
    /// <returns></returns>
    public List<DataType> ToList()
    {
        List<DataType> array = new List<DataType>(queue.Count);

        int i = 0;

        foreach (PriorityQueueNode<DataType, PriorityType> node in queue)
        {
            array[i] = node.data;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a list of the current queue's priority
    /// </summary>
    /// <returns></returns>
    public List<PriorityType> PriorityToList()
    {
        List<PriorityType> array = new List<PriorityType>(queue.Count);

        int i = 0;

        foreach (PriorityQueueNode<DataType, PriorityType> node in queue)
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
    public PriorityQueue()
    {
        queue = new LinkedList<PriorityQueueNode<DataType, PriorityType>>();
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copiedQueue"></param>
    public PriorityQueue(PriorityQueue<DataType, PriorityType> copiedQueue)
    {
        queue = new LinkedList<PriorityQueueNode<DataType, PriorityType>>(copiedQueue.queue);
    }

    /// <summary>
    /// Data constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityQueue(DataType data, PriorityType priority)
    {
        queue = new LinkedList<PriorityQueueNode<DataType, PriorityType>>();

        queue.AddLast(new PriorityQueueNode<DataType, PriorityType>(this, data, priority));
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="node"></param>
    public PriorityQueue(PriorityQueueNode<DataType, PriorityType> node)
    {
        queue = new LinkedList<PriorityQueueNode<DataType, PriorityType>>();

        node.queue = this;

        queue.AddLast(node);
    }

    /// <summary>
    /// <summary>
    /// Node array constructor
    /// </summary>
    /// <param name="nodes"></param>
    public PriorityQueue(params PriorityQueueNode<DataType, PriorityType>[] nodes)
    {
        queue = new LinkedList<PriorityQueueNode<DataType, PriorityType>>();

        for (int i = 0; i < nodes.Length; i++)
        {
            Enqueue(nodes[i]);
        }
    }

    /// <summary>
    /// Enumerable constructor
    /// </summary>
    /// <param name="nodes"></param>
    public PriorityQueue(IEnumerable<PriorityQueueNode<DataType, PriorityType>> nodes)
    {
        queue = new LinkedList<PriorityQueueNode<DataType, PriorityType>>();

        foreach (PriorityQueueNode<DataType, PriorityType> node in nodes)
        {
            Enqueue(node);
        }
    }


    // EQUALITY

    /// <summary>
    /// Check if another queue is equal to the queue
    /// </summary>
    /// <param name="comparedQueue"></param>
    /// <returns></returns>
    public bool Equals(PriorityQueue<DataType, PriorityType> comparedQueue)
    {
        return queue == comparedQueue.queue;
    }

    /// <summary>
    /// Check if another queue is equal to the queue
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedQueue"></param>
    /// <returns></returns>
    public static bool operator ==(PriorityQueue<DataType, PriorityType> list, PriorityQueue<DataType, PriorityType> comparedQueue)
    {
        return list.Equals(comparedQueue);
    }

    /// <summary>
    /// Check if another queue is not equal to the queue
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedQueue"></param>
    /// <returns></returns>
    public static bool operator !=(PriorityQueue<DataType, PriorityType> list, PriorityQueue<DataType, PriorityType> comparedQueue)
    {
        return !list.Equals(comparedQueue);
    }


    // CAPACITY

    /// <summary>
    /// Returns whether the queue is empty
    /// </summary>
    /// <returns></returns>
    public bool Empty()
    {
        return queue.Count == 0;
    }

    /// <summary>
    /// Returns the current number of elements of the queue
    /// </summary>
    /// <returns></returns>
    public int Size()
    {
        return queue.Count;
    }


    // ELEMENT ACCESS

    /// <summary>
    /// Returns the highest priority element without dequeuing it
    /// </summary>
    /// <returns></returns>
    public DataType Peek()
    {
        return queue.First.Value.data;
    }

    /// <summary>
    /// Returns the lowest priority element
    /// </summary>
    /// <returns></returns>
    public DataType PeekLast()
    {
        return queue.Last.Value.data;
    }

    /// <summary>
    /// Returns the highest priority element and its priority without dequeuing it
    /// </summary>
    /// <returns></returns>
    public PriorityQueueNode<DataType, PriorityType> PeekNode()
    {
        return queue.First.Value;
    }

    /// <summary>
    /// Returns the lowest priority element and its priority
    /// </summary>
    /// <returns></returns>
    public PriorityQueueNode<DataType, PriorityType> PeekLastNode()
    {
        return queue.Last.Value;
    }


    // LOCATING ELEMENTS

    /// <summary>
    /// Returns whether the queue contains at least one of the elements 
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool Contains(DataType containedData)
    {
        foreach (PriorityQueueNode<DataType, PriorityType> node in queue)
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
        return queue.First.Value.priority;
    }

    /// <summary>
    /// Returns the lowest priority value
    /// </summary>
    /// <returns></returns>
    public PriorityType LowestPriority()
    {
        return queue.Last.Value.priority;
    }


    // MODIFIERS

    /// <summary>
    /// Assigns the queue's elements from another queue's elements
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public PriorityQueue<DataType, PriorityType> Assign(PriorityQueue<DataType, PriorityType> newData)
    {
        queue = new LinkedList<PriorityQueueNode<DataType, PriorityType>>(newData.queue);

        return this;
    }

    /// <summary>
    /// Inserts a new element of the given data into the queue based on its priority value
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public PriorityQueue<DataType, PriorityType> Enqueue(DataType data, PriorityType priority)
    {
        if (queue.Count == 0)
        {
            queue.AddLast(new PriorityQueueNode<DataType, PriorityType>(this, data, priority));

            return this;
        }

        LinkedListNode<PriorityQueueNode<DataType, PriorityType>> node = queue.First;

        for (int i = 0; i < queue.Count; i++)
        {
            if (priority.CompareTo(node.Value.priority) > 0)
            {
                queue.AddBefore(node, new PriorityQueueNode<DataType, PriorityType>(this, data, priority));

                return this;
            }

            node = node.Next;
        }

        queue.AddLast(new PriorityQueueNode<DataType, PriorityType>(this, data, priority));

        return this;
    }

    /// <summary>
    /// Inserts a priority queue node into the queue based on its priority value
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public PriorityQueue<DataType, PriorityType> Enqueue(PriorityQueueNode<DataType, PriorityType> newNode)
    {
        if (queue.Count == 0)
        {
            newNode.queue = this;

            queue.AddLast(newNode);

            return this;
        }

        LinkedListNode<PriorityQueueNode<DataType, PriorityType>> node = queue.First;

        for (int i = 0; i < queue.Count; i++)
        {
            if (newNode.priority.CompareTo(node.Value.priority) > 0)
            {
                newNode.queue = this;

                queue.AddBefore(node, newNode);

                return this;
            }

            node = node.Next;
        }

        newNode.queue = this;

        queue.AddLast(newNode);

        return this;
    }

    /// <summary>
    /// Inserts an existing element of the given data into the queue based on its priority value
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public PriorityQueue<DataType, PriorityType> Emplace(ref DataType data, PriorityType priority)
    {
        if (queue.Count == 0)
        {
            queue.AddLast(new PriorityQueueNode<DataType, PriorityType>(this, data, priority));

            return this;
        }

        LinkedListNode<PriorityQueueNode<DataType, PriorityType>> node = queue.First;

        for (int i = 0; i < queue.Count; i++)
        {
            if (priority.CompareTo(node.Value.priority) > 0)
            {
                queue.AddBefore(node, new PriorityQueueNode<DataType, PriorityType>(this, data, priority));

                return this;
            }

            node = node.Next;
        }

        queue.AddLast(new PriorityQueueNode<DataType, PriorityType>(this, data, priority));

        return this;
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the queue
    /// </summary>
    /// <returns></returns>
    public DataType Dequeue()
    {
        DataType element = queue.First.Value.data;

        queue.RemoveFirst();

        return element;
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the queue with its priority
    /// </summary>
    /// <returns></returns>
    public PriorityQueueNode<DataType, PriorityType> DequeueNode()
    {
        PriorityQueueNode<DataType, PriorityType> element = queue.First.Value;

        queue.RemoveFirst();

        return element;
    }

    /// <summary>
    /// Clears the queue
    /// </summary>
    /// <returns></returns>
    public int Clear()
    {
        int total = queue.Count;

        queue.Clear();

        return total;
    }


    // OPERATIONS

    /// <summary>
    /// Swaps the queue with another queue
    /// </summary>
    /// <param name="swappedData"></param>
    /// <returns></returns>
    public PriorityQueue<DataType, PriorityType> Swap(PriorityQueue<DataType, PriorityType> swappedData)
    {
        LinkedList<PriorityQueueNode<DataType, PriorityType>> data = queue;

        queue = swappedData.queue;

        swappedData.queue = data;

        return this;
    }

    /// <summary>
    /// Returns a copy of the queue's data
    /// </summary>
    /// <returns></returns>
    public PriorityQueue<DataType, PriorityType> Copy()
    {
        return new PriorityQueue<DataType, PriorityType>(this);
    }


    // TO STRING

    /// <summary>
    /// Converts the elements of the queue into a string
    /// </summary>
    /// <returns></returns>
    public string ToString()
    {
        if (queue.Count == 0)
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
    /// Inserts a new element of the given data into the queue based on its priority value
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public PriorityQueue<DataType, PriorityType> Add(DataType data, PriorityType priority)
    {
        return Enqueue(data, priority);
    }
}

/// <summary>
/// Class that stores data and its priority value for insertion in a priority queue.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class PriorityQueueNode<DataType, PriorityType> where PriorityType : IComparable, IComparable<DataType>
{
    // VARIABLES

    /// <summary>
    /// This node's priority queue
    /// </summary>
    public PriorityQueue<DataType, PriorityType> queue = null;

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
    /// Readonly queue variable
    /// </summary>
    public PriorityQueue<DataType, PriorityType> Queue
    {
        get
        {
            return queue;
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
    /// <param name="queue"></param>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityQueueNode(PriorityQueue<DataType, PriorityType> queue = null, DataType data = default(DataType), PriorityType priority = default(PriorityType))
    {
        this.queue = queue;

        this.data = data;

        this.priority = priority;
    }
}
