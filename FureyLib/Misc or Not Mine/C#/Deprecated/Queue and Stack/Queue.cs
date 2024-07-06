
// Queue and Priority Queue Data Types Script
// by Kyle Furey

using System.Collections;
using System.Collections.Generic;

// Data type used for priority value
using PriorityType = System.Single;

/// <summary>
/// A first in first out list of a specified data type.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class Queue<DataType> : IEnumerable
{
    /// <summary>
    /// The list of nodes in queue in order of oldest to newest
    /// </summary>
    private List<DataType> queue = new List<DataType>();

    /// <summary>
    /// Add a new node to the queue and return the index
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int Enqueue(DataType data)
    {
        // Add the enqueued node to the end of the list
        queue.Add(data);

        return queue.Count - 1;
    }

    /// <summary>
    /// Removes and returns the oldest node
    /// </summary>
    /// <returns></returns>
    public DataType Dequeue()
    {
        // Check if the queue is empty
        if (queue.Count == 0)
        {
            return default(DataType);
        }

        // Store the oldest node
        DataType dequeuedNode = queue[0];

        // Remove the oldest node from the queue
        queue.RemoveAt(0);

        // Return our removed node
        return dequeuedNode;
    }

    /// <summary>
    /// Add a new node to the queue and return the index (identical to enqueue)
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int Push(DataType data)
    {
        return Enqueue(data);
    }

    /// <summary>
    /// Removes and returns the oldest node (identical to dequeue)
    /// </summary>
    /// <returns></returns>
    public DataType Pop()
    {
        return Dequeue();
    }

    /// <summary>
    /// Returns the oldest data (without removing it from the queue)
    /// </summary>
    /// <returns></returns>
    public DataType Peek()
    {
        return queue[0];
    }

    /// <summary>
    /// Returns the newest data (without removing it from the queue)
    /// </summary>
    /// <returns></returns>
    public DataType PeekLast()
    {
        return queue[queue.Count - 1];
    }

    /// <summary>
    /// Returns the data at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType Get(int index)
    {
        return queue[index];
    }

    /// <summary>
    /// Sets the data at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Queue<DataType> Set(int index, DataType newData)
    {
        queue[index] = newData;

        return this;
    }

    /// <summary>
    /// Clears the queue and returns the total number of cleared nodes
    /// </summary>
    /// <returns></returns>
    public int Clear()
    {
        int total = queue.Count;

        queue.Clear();

        return total;
    }

    /// <summary>
    /// Returns the size of the queue
    /// </summary>
    /// <returns></returns>
    public int Count()
    {
        return queue.Count;
    }

    /// <summary>
    /// Returns if the queue is empty
    /// </summary>
    /// <returns></returns>
    public bool IsEmpty()
    {
        return queue.Count == 0;
    }

    /// <summary>
    /// Return the index of the given element, or -1 if it was not found
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int Find(DataType data)
    {
        for (int i = 0; i < queue.Count; i++)
        {
            if (queue[i].Equals(data))
            {
                return i;
            }
        }

        return -1;
    }

    /// <summary>
    /// Return whether the queue contains the given element
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public bool Contains(DataType data)
    {
        for (int i = 0; i < queue.Count; i++)
        {
            if (queue[i].Equals(data))
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

        for (int i = 0; i < queue.Count; i++)
        {
            if (queue[i].Equals(data))
            {
                total++;
            }
        }

        return total;
    }

    /// <summary>
    /// Returns an array of the current queue data
    /// </summary>
    /// <returns></returns>
    public DataType[] ToArray()
    {
        return queue.ToArray();
    }

    /// <summary>
    /// Returns a list of the current queue data
    /// </summary>
    /// <returns></returns>
    public List<DataType> ToList()
    {
        return queue;
    }

    /// <summary>
    /// Default constructor
    /// </summary>
    public Queue()
    {
        queue = new List<DataType>();
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="data"></param>
    public Queue(params DataType[] data)
    {
        queue = new List<DataType>(data.Length);

        for (int i = 0; i < data.Length; i++)
        {
            queue.Add(data[i]);
        }
    }

    /// <summary>
    /// List constructor
    /// </summary>
    /// <param name="data"></param>
    public Queue(List<DataType> data)
    {
        queue = data;
    }

    /// <summary>
    /// Queue constructor
    /// </summary>
    /// <param name="data"></param>
    public Queue(Queue<DataType> data)
    {
        queue = data.queue;
    }

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return queue.GetEnumerator();
    }
}

/// <summary>
/// A first in first out list of a specified data type with an associated priority value assigned to each element used for adding and removing data in a specific order.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class PriorityQueue<DataType>
{
    /// <summary>
    /// The list of nodes in queue in order of oldest to newest and lowest priority to highest priority
    /// </summary>
    private List<DataType> queue = new List<DataType>();

    /// <summary>
    /// The list of priority corresponding with the list of nodes
    /// </summary>
    private List<PriorityType> priority = new List<PriorityType>();

    /// <summary>
    /// Add a new node to the queue and return the index
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public int Enqueue(DataType data, PriorityType priority)
    {
        for (int i = 0; i < queue.Count; i++)
        {
            if (priority > this.priority[i])
            {
                queue.Insert(i, data);

                this.priority.Insert(i, priority);

                return i;
            }
        }

        queue.Add(data);

        this.priority.Add(priority);

        return queue.Count - 1;
    }

    /// <summary>
    /// Removes the oldest node with the lowest priority and return the removed node
    /// </summary>
    /// <returns></returns>
    public DataType Dequeue()
    {
        DataType dequeuedData = queue[0];

        queue.RemoveAt(0);

        return dequeuedData;
    }

    /// <summary>
    /// Add a new node to the queue and return the index (identical to enqueue)
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    /// <returns></returns>
    public int Push(DataType data, PriorityType priority)
    {
        return Enqueue(data, priority);
    }

    /// <summary>
    /// Removes the oldest node with the lowest priority and return the removed node (identical to dequeue)
    /// </summary>
    /// <returns></returns>
    public DataType Pop()
    {
        return Dequeue();
    }

    /// <summary>
    /// Returns the data with the highest priority (without removing it from the queue)
    /// </summary>
    /// <returns></returns>
    public DataType Peek()
    {
        return queue[0];
    }

    /// <summary>
    /// Returns the data with the lowest priority (without removing it from the queue)
    /// </summary>
    /// <returns></returns>
    public DataType PeekLast()
    {
        return queue[queue.Count - 1];
    }

    /// <summary>
    /// Returns the data at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType Get(int index)
    {
        return queue[index];
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

        return queue[index];
    }

    /// <summary>
    /// Sets the data at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public PriorityQueue<DataType> Set(int index, DataType newData)
    {
        queue[index] = newData;

        return this;
    }

    /// <summary>
    /// Sets the data at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <param name="newPriority"></param>
    /// <returns></returns>
    public PriorityQueue<DataType> Set(int index, DataType newData, PriorityType newPriority)
    {
        queue[index] = newData;

        priority[index] = newPriority;

        return this;
    }

    /// <summary>
    /// Returns the highest priority value (the priority which is closest to being dequeued)
    /// </summary>
    /// <returns></returns>
    public PriorityType HighestPriority()
    {
        return priority[0];
    }

    /// <summary>
    /// Returns the lowest priority value (the priority which is furthest from being dequeued)
    /// </summary>
    /// <returns></returns>
    public PriorityType LowestPriority()
    {
        return priority[priority.Count - 1];
    }

    /// <summary>
    /// Returns the priority value of the given data in the queue
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public PriorityType GetPriority(DataType data)
    {
        PriorityType priority = 0;

        for (int i = 0; i < queue.Count; i++)
        {
            if (queue[i].Equals(data))
            {
                return this.priority[i];
            }
        }

        return priority;
    }

    /// <summary>
    /// Returns the priority value at the given index in the queue
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
    public PriorityQueue<DataType> SetPriority(DataType data, PriorityType newPriority)
    {
        for (int i = 0; i < queue.Count; i++)
        {
            if (queue[i].Equals(data))
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
    public PriorityQueue<DataType> SetPriorityAt(int index, PriorityType newPriority)
    {
        priority[index] = newPriority;

        return this;
    }

    /// <summary>
    /// Clears the queue and returns the total number of cleared nodes
    /// </summary>
    /// <returns></returns>
    public int Clear()
    {
        int total = queue.Count;

        queue.Clear();

        priority.Clear();

        return total;
    }

    /// <summary>
    /// Returns the size of the queue
    /// </summary>
    /// <returns></returns>
    public int Count()
    {
        return queue.Count;
    }

    /// <summary>
    /// Returns if the queue is empty
    /// </summary>
    /// <returns></returns>
    public bool IsEmpty()
    {
        return queue.Count == 0;
    }

    /// <summary>
    /// Return the index of the given element, or -1 if it was not found
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int Find(DataType data)
    {
        for (int i = 0; i < queue.Count; i++)
        {
            if (queue[i].Equals(data))
            {
                return i;
            }
        }

        return -1;
    }

    /// <summary>
    /// Return whether the queue contains the given element
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public bool Contains(DataType data)
    {
        for (int i = 0; i < queue.Count; i++)
        {
            if (queue[i].Equals(data))
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

        for (int i = 0; i < queue.Count; i++)
        {
            if (queue[i].Equals(data))
            {
                total++;
            }
        }

        return total;
    }

    /// <summary>
    /// Returns an array of the current queue data
    /// </summary>
    /// <returns></returns>
    public DataType[] ToArray()
    {
        return queue.ToArray();
    }

    /// <summary>
    /// Returns a list of the current queue data
    /// </summary>
    /// <returns></returns>
    public List<DataType> ToList()
    {
        return queue;
    }

    /// <summary>
    /// Returns an array of the current queue's priority values
    /// </summary>
    /// <returns></returns>
    public PriorityType[] PriorityToArray()
    {
        return priority.ToArray();
    }

    /// <summary>
    /// Returns a list of the current queue's priority values
    /// </summary>
    /// <returns></returns>
    public List<PriorityType> PriorityToList()
    {
        return priority;
    }

    /// <summary>
    /// Returns a dictionary of the current queue data and their priorities
    /// </summary>
    /// <returns></returns>
    public Dictionary<DataType, PriorityType> ToDictionary()
    {
        Dictionary<DataType, PriorityType> dictionary = new Dictionary<DataType, PriorityType>(queue.Count);

        for (int i = 0; i < queue.Count; i++)
        {
            dictionary[queue[i]] = priority[i];
        }

        return dictionary;
    }

    /// <summary>
    /// Default constructor
    /// </summary>
    public PriorityQueue()
    {
        queue = new List<DataType>();

        priority = new List<PriorityType>();
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityQueue(DataType[] data, PriorityType[] priority)
    {
        queue = new List<DataType>(data.Length);

        this.priority = new List<PriorityType>(data.Length);

        for (int i = 0; i < data.Length; i++)
        {
            Enqueue(data[i], priority[i]);
        }
    }

    /// <summary>
    /// List constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="priority"></param>
    public PriorityQueue(List<DataType> data, List<PriorityType> priority)
    {
        queue = new List<DataType>(data.Count);

        this.priority = new List<PriorityType>(data.Count);

        for (int i = 0; i < data.Count; i++)
        {
            Enqueue(data[i], priority[i]);
        }
    }

    /// <summary>
    /// Queue constructor
    /// </summary>
    /// <param name="data"></param>
    public PriorityQueue(PriorityQueue<DataType> data)
    {
        queue = data.queue;

        priority = data.priority;
    }
}
