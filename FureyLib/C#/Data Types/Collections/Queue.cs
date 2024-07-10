
// Queue and Priority Queue Containers Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/queue/queue/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.queue-1?view=net-8.0, https://en.cppreference.com/w/cpp/container/priority_queue, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.priorityqueue-2?view=net-8.0

using System;
using System.Collections;
using System.Collections.Generic;

// The priority type used for sorting
using PriorityType = System.Single;

/// <summary>
/// Wrapper class of a linked list allowing first in first out access of its elements.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class Queue<DataType> : IEnumerable
{
    // VARIABLES

    /// <summary>
    /// The linked list holding the data of the queue
    /// </summary>
    private LinkedList<DataType> queue = new LinkedList<DataType>();


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

        foreach (DataType node in queue)
        {
            array[i] = node;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a list of the current queue
    /// </summary>
    /// <returns></returns>
    public List<DataType> ToList()
    {
        List<DataType> array = new List<DataType>(queue.Count);

        int i = 0;

        foreach (DataType node in queue)
        {
            array[i] = node;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a linked list of the current queue
    /// </summary>
    /// <returns></returns>
    public LinkedList<DataType> ToLinkedList()
    {
        return new LinkedList<DataType>(queue);
    }


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Queue()
    {
        queue = new LinkedList<DataType>();
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copiedQueue"></param>
    public Queue(Queue<DataType> copiedQueue)
    {
        queue = new LinkedList<DataType>(copiedQueue.queue);
    }

    /// <summary>
    /// Data constructor
    /// </summary>
    /// <param name="data"></param>
    public Queue(DataType data)
    {
        queue = new LinkedList<DataType>();

        queue.AddLast(data);
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="array"></param>
    public Queue(params DataType[] array)
    {
        queue = new LinkedList<DataType>(array);
    }

    /// <summary>
    /// List constructor
    /// </summary>
    /// <param name="list"></param>
    public Queue(List<DataType> list)
    {
        queue = new LinkedList<DataType>(list);
    }

    /// <summary>
    /// Linked list constructor
    /// </summary>
    /// <param name="linkedList"></param>
    public Queue(LinkedList<DataType> linkedList)
    {
        queue = new LinkedList<DataType>(linkedList);
    }


    // EQUALITY

    /// <summary>
    /// Check if another queue is equal to the queue
    /// </summary>
    /// <param name="comparedQueue"></param>
    /// <returns></returns>
    public bool Equals(Queue<DataType> comparedQueue)
    {
        return queue == comparedQueue.queue;
    }

    /// <summary>
    /// Check if another queue is equal to the queue
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedQueue"></param>
    /// <returns></returns>
    public static bool operator ==(Queue<DataType> list, Queue<DataType> comparedQueue)
    {
        return list.Equals(comparedQueue);
    }

    /// <summary>
    /// Check if another queue is not equal to the queue
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedQueue"></param>
    /// <returns></returns>
    public static bool operator !=(Queue<DataType> list, Queue<DataType> comparedQueue)
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
    /// Returns the oldest element without dequeuing it
    /// </summary>
    /// <returns></returns>
    public DataType Peek()
    {
        return queue.First.Value;
    }

    /// <summary>
    /// Returns the oldest element without dequeuing it safely
    /// </summary>
    /// <returns></returns>
    public DataType TryPeek()
    {
        if (queue.Count == 0)
        {
            return default(DataType);
        }

        return queue.First.Value;
    }

    /// <summary>
    /// Returns the most recent element
    /// </summary>
    /// <returns></returns>
    public DataType PeekLast()
    {
        return queue.Last.Value;
    }

    /// <summary>
    /// Returns the most recent element safely
    /// </summary>
    /// <returns></returns>
    public DataType TryPeekLast()
    {
        if (queue.Count == 0)
        {
            return default(DataType);
        }

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
        return queue.Contains(containedData);
    }


    // MODIFIERS

    /// <summary>
    /// Assigns the queue's elements from another queue's elements
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Queue<DataType> Assign(Queue<DataType> newData)
    {
        queue = new LinkedList<DataType>(newData.queue);

        return this;
    }

    /// <summary>
    /// Inserts a new element of the given data at the end of the queue
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public Queue<DataType> Enqueue(DataType data)
    {
        queue.AddLast(data);

        return this;
    }

    /// <summary>
    /// Inserts an existing element of the given data at the end of the queue
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public Queue<DataType> Emplace(ref DataType data)
    {
        queue.AddLast(data);

        return this;
    }

    /// <summary>
    /// Remove and return the last element from the queue
    /// </summary>
    /// <returns></returns>
    public DataType Dequeue()
    {
        DataType element = queue.First.Value;

        queue.RemoveFirst();

        return element;
    }

    /// <summary>
    /// Remove and return the last element from the queue safely
    /// </summary>
    /// <returns></returns>
    public DataType TryDequeue()
    {
        if (queue.Count == 0)
        {
            return default(DataType);
        }

        DataType element = queue.First.Value;

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
    public Queue<DataType> Swap(Queue<DataType> swappedData)
    {
        LinkedList<DataType> data = queue;

        queue = swappedData.queue;

        swappedData.queue = data;

        return this;
    }

    /// <summary>
    /// Reverse the queue
    /// </summary>
    /// <returns></returns>
    public Queue<DataType> Reverse()
    {
        queue.Reverse();

        return this;
    }

    /// <summary>
    /// Returns a copy of the queue's data
    /// </summary>
    /// <returns></returns>
    public Queue<DataType> Copy()
    {
        return new Queue<DataType>(this);
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
    /// Inserts a new element of the given data at the end of the queue
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public Queue<DataType> Add(DataType data)
    {
        return Enqueue(data);
    }
}

/// <summary>
/// •  Wrapper class of a linked list allowing first in first out access of its elements.<br/>
/// •  Each element has its own associated priority value used for automatic sorting on insertion.<br/>
/// •  Elements with higher priority are dequeued first.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class PriorityQueue<DataType> : IEnumerable
{
    // VARIABLES

    /// <summary>
    /// The linked list holding the data of the queue
    /// </summary>
    private LinkedList<DataType> queue = new LinkedList<DataType>();

    /// <summary>
    /// The linked list holding the priority values of the queue
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

        foreach (DataType node in queue)
        {
            array[i] = node;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a list of the current queue
    /// </summary>
    /// <returns></returns>
    public List<DataType> ToList()
    {
        List<DataType> array = new List<DataType>(queue.Count);

        int i = 0;

        foreach (DataType node in queue)
        {
            array[i] = node;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a linked list of the current queue
    /// </summary>
    /// <returns></returns>
    public LinkedList<DataType> ToLinkedList()
    {
        return new LinkedList<DataType>(queue);
    }

    /// <summary>
    /// Returns an array of the current queue's priority
    /// </summary>
    /// <returns></returns>
    public PriorityType[] PriorityToArray()
    {
        PriorityType[] array = new PriorityType[queue.Count];

        int i = 0;

        foreach (PriorityType node in priority)
        {
            array[i] = node;

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

        foreach (PriorityType node in priority)
        {
            array[i] = node;

            i++;
        }

        return array;
    }

    /// <summary>
    /// Returns a linked list of the current queue's priority
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
    public PriorityQueue()
    {
        queue = new LinkedList<DataType>();

        priority = new LinkedList<PriorityType>();
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copiedQueue"></param>
    public PriorityQueue(PriorityQueue<DataType> copiedQueue)
    {
        queue = new LinkedList<DataType>(copiedQueue.queue);

        priority = new LinkedList<PriorityType>(copiedQueue.priority);
    }

    /// <summary>
    /// Data constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityQueue(DataType data, float priority)
    {
        queue = new LinkedList<DataType>();

        queue.AddLast(data);

        this.priority = new LinkedList<PriorityType>();

        this.priority.AddLast(priority);
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
        return queue.First.Value;
    }

    /// <summary>
    /// Returns the highest priority element without dequeuing it safely
    /// </summary>
    /// <returns></returns>
    public DataType TryPeek()
    {
        if (queue.Count == 0)
        {
            return default(DataType);
        }

        return queue.First.Value;
    }

    /// <summary>
    /// Returns the lowest priority element
    /// </summary>
    /// <returns></returns>
    public DataType PeekLast()
    {
        return queue.Last.Value;
    }

    /// <summary>
    /// Returns the lowest priority element safely
    /// </summary>
    /// <returns></returns>
    public DataType TryPeekLast()
    {
        if (queue.Count == 0)
        {
            return default(DataType);
        }

        return queue.Last.Value;
    }

    /// <summary>
    /// Returns the highest priority element and its priority without dequeuing it
    /// </summary>
    /// <returns></returns>
    public (DataType data, PriorityType priority) PeekWithPriority()
    {
        return (queue.First.Value, priority.First.Value);
    }

    /// <summary>
    /// Returns the highest priority element and its priority without dequeuing it safely
    /// </summary>
    /// <returns></returns>
    public (DataType data, PriorityType priority) TryPeekWithPriority()
    {
        if (queue.Count == 0)
        {
            return (default(DataType), 0);
        }

        return (queue.First.Value, priority.First.Value);
    }

    /// <summary>
    /// Returns the lowest priority element and its priority
    /// </summary>
    /// <returns></returns>
    public (DataType data, PriorityType priority) PeekLastWithPriority()
    {
        return (queue.Last.Value, priority.Last.Value);
    }

    /// <summary>
    /// Returns the lowest priority element and its priority safely
    /// </summary>
    /// <returns></returns>
    public (DataType data, PriorityType priority) TryPeekLastWithPriority()
    {
        if (queue.Count == 0)
        {
            return (default(DataType), 0);
        }

        return (queue.Last.Value, priority.Last.Value);
    }


    // LOCATING ELEMENTS

    /// <summary>
    /// Returns whether the queue contains at least one of the elements 
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool Contains(DataType containedData)
    {
        return queue.Contains(containedData);
    }


    // MODIFIERS

    /// <summary>
    /// Assigns the queue's elements from another queue's elements
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public PriorityQueue<DataType> Assign(PriorityQueue<DataType> newData)
    {
        queue = new LinkedList<DataType>(newData.queue);

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
            queue.AddLast(data);

            this.priority.AddLast(priority);

            return this;
        }

        LinkedListNode<DataType> dataNode = queue.First;

        LinkedListNode<PriorityType> priorityNode = this.priority.First;

        for (int i = 0; i < queue.Count; i++)
        {
            if (priority > priorityNode.Value)
            {
                queue.AddBefore(dataNode, data);

                this.priority.AddBefore(priorityNode, priority);

                return this;
            }

            dataNode = dataNode.Next;

            priorityNode = priorityNode.Next;
        }

        queue.AddLast(data);

        this.priority.AddLast(priority);

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
            queue.AddLast(data);

            this.priority.AddLast(priority);

            return this;
        }

        LinkedListNode<DataType> dataNode = queue.First;

        LinkedListNode<PriorityType> priorityNode = this.priority.First;

        for (int i = 0; i < queue.Count; i++)
        {
            if (priority > priorityNode.Value)
            {
                queue.AddBefore(dataNode, data);

                this.priority.AddBefore(priorityNode, priority);

                return this;
            }

            dataNode = dataNode.Next;

            priorityNode = priorityNode.Next;
        }

        queue.AddLast(data);

        this.priority.AddLast(priority);

        return this;
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the queue
    /// </summary>
    /// <returns></returns>
    public DataType Dequeue()
    {
        DataType element = queue.First.Value;

        queue.RemoveFirst();

        priority.RemoveFirst();

        return element;
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the queue with its priority
    /// </summary>
    /// <returns></returns>
    public (DataType data, PriorityType priority) DequeueWithPriority()
    {
        DataType element = queue.First.Value;

        PriorityType priority = this.priority.First.Value;

        queue.RemoveFirst();

        this.priority.RemoveFirst();

        return (element, priority);
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the queue safely
    /// </summary>
    /// <returns></returns>
    public DataType TryDequeue()
    {
        if (queue.Count == 0)
        {
            return default(DataType);
        }

        DataType element = queue.First.Value;

        queue.RemoveFirst();

        priority.RemoveFirst();

        return element;
    }

    /// <summary>
    /// Remove and return the element with the greatest priority from the queue safely with its priority
    /// </summary>
    /// <returns></returns>
    public (DataType data, PriorityType priority) TryDequeueWithPriority()
    {
        if (queue.Count == 0)
        {
            return (default(DataType), 0);
        }

        DataType element = queue.First.Value;

        PriorityType priority = this.priority.First.Value;

        queue.RemoveFirst();

        this.priority.RemoveFirst();

        return (element, priority);
    }

    /// <summary>
    /// Clears the queue
    /// </summary>
    /// <returns></returns>
    public int Clear()
    {
        int total = queue.Count;

        queue.Clear();

        priority.Clear();

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
        LinkedList<DataType> data = queue;

        LinkedList<PriorityType> priority = this.priority;

        queue = swappedData.queue;

        this.priority = swappedData.priority;

        swappedData.queue = data;

        swappedData.priority = priority;

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
        return queue.GetEnumerator();
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
