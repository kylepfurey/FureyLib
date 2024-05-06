
// Queue and Priority Queue Data Types Script
// by Kyle Furey

using System.Collections;
using System.Collections.Generic;

// Data type used for priority value
using PriorityType = System.Single;

// A first in first out list of a specified data type.
public class Queue<DataType> : IEnumerable
{
    // The list of nodes in queue in order of oldest to newest
    private List<DataType> queue = new List<DataType>();

    // Add a new node to the queue and return the index
    public int Enqueue(DataType data)
    {
        // Add the enqueued node to the end of the list
        queue.Add(data);

        return queue.Count - 1;
    }

    // Removes and returns the oldest node
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

    // Add a new node to the queue and return the index (identical to enqueue)
    public int Push(DataType data)
    {
        return Enqueue(data);
    }

    // Removes and returns the oldest node (identical to dequeue)
    public DataType Pop()
    {
        return Dequeue();
    }

    // Returns the oldest data (without removing it from the queue)
    public DataType Peek()
    {
        return queue[0];
    }

    // Returns the newest data (without removing it from the queue)
    public DataType PeekLast()
    {
        return queue[queue.Count - 1];
    }

    // Returns the data at the given index
    public DataType Get(int index)
    {
        return queue[index];
    }

    // Sets the data at the given index
    public Queue<DataType> Set(int index, DataType newData)
    {
        queue[index] = newData;

        return this;
    }

    // Clears the queue and returns the total number of cleared nodes
    public int Clear()
    {
        int total = queue.Count;

        queue.Clear();

        return total;
    }

    // Returns the size of the queue
    public int Count()
    {
        return queue.Count;
    }

    // Returns if the queue is empty
    public bool IsEmpty()
    {
        return queue.Count == 0;
    }

    // Return the index of the given element, or -1 if it was not found
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

    // Return whether the queue contains the given element
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

    // Return the number of matching elements
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

    // Returns an array of the current queue data
    public DataType[] ToArray()
    {
        return queue.ToArray();
    }

    // Returns a list of the current queue data
    public List<DataType> ToList()
    {
        return queue;
    }

    // Default constructor
    public Queue()
    {
        queue = new List<DataType>();
    }

    // Array constructor
    public Queue(params DataType[] data)
    {
        queue = new List<DataType>(data.Length);

        for (int i = 0; i < data.Length; i++)
        {
            queue.Add(data[i]);
        }
    }

    // List constructor
    public Queue(List<DataType> data)
    {
        queue = data;
    }

    // Queue constructor
    public Queue(Queue<DataType> data)
    {
        queue = data.queue;
    }

    // Enumerator implementation
    public IEnumerator GetEnumerator()
    {
        return queue.GetEnumerator();
    }
}

// A first in first out list of a specified data type with an associated priority value assigned to each element used for adding and removing data in a specific order.
public class PriorityQueue<DataType>
{
    // The list of nodes in queue in order of oldest to newest and lowest priority to highest priority
    private List<DataType> queue = new List<DataType>();

    // The list of priority corresponding with the list of nodes
    private List<PriorityType> priority = new List<PriorityType>();

    // Add a new node to the queue and return the index
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

    // Removes the oldest node with the lowest priority and return the removed node
    public DataType Dequeue()
    {
        DataType dequeuedData = queue[0];

        queue.RemoveAt(0);

        return dequeuedData;
    }

    // Add a new node to the queue and return the index (identical to enqueue)
    public int Push(DataType data, PriorityType priority)
    {
        return Enqueue(data, priority);
    }

    // Removes the oldest node with the lowest priority and return the removed node (identical to dequeue)
    public DataType Pop()
    {
        return Dequeue();
    }

    // Returns the data with the highest priority (without removing it from the queue)
    public DataType Peek()
    {
        return queue[0];
    }

    // Returns the data with the lowest priority (without removing it from the queue)
    public DataType PeekLast()
    {
        return queue[queue.Count - 1];
    }

    // Returns the data at the given index
    public DataType Get(int index)
    {
        return queue[index];
    }

    // Returns the data at the given index
    public DataType Get(int index, out PriorityType priority)
    {
        priority = this.priority[index];

        return queue[index];
    }

    // Sets the data at the given index
    public PriorityQueue<DataType> Set(int index, DataType newData)
    {
        queue[index] = newData;

        return this;
    }

    // Sets the data at the given index
    public PriorityQueue<DataType> Set(int index, DataType newData, PriorityType newPriority)
    {
        queue[index] = newData;

        priority[index] = newPriority;

        return this;
    }

    // Returns the highest priority value (the priority which is closest to being dequeued)
    public PriorityType HighestPriority()
    {
        return priority[0];
    }

    // Returns the lowest priority value (the priority which is furthest from being dequeued)
    public PriorityType LowestPriority()
    {
        return priority[priority.Count - 1];
    }

    // Returns the priority value of the given data in the queue
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

    // Returns the priority value at the given index in the queue
    public PriorityType GetPriorityAt(int index)
    {
        return priority[index];
    }

    // Sets the priority value of the given data
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

    // Sets the priority value at the given index
    public PriorityQueue<DataType> SetPriorityAt(int index, PriorityType newPriority)
    {
        priority[index] = newPriority;

        return this;
    }

    // Clears the queue and returns the total number of cleared nodes
    public int Clear()
    {
        int total = queue.Count;

        queue.Clear();

        priority.Clear();

        return total;
    }

    // Returns the size of the queue
    public int Count()
    {
        return queue.Count;
    }

    // Returns if the queue is empty
    public bool IsEmpty()
    {
        return queue.Count == 0;
    }

    // Return the index of the given element, or -1 if it was not found
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

    // Return whether the queue contains the given element
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

    // Return the number of matching elements
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

    // Returns an array of the current queue data
    public DataType[] ToArray()
    {
        return queue.ToArray();
    }

    // Returns a list of the current queue data
    public List<DataType> ToList()
    {
        return queue;
    }

    // Returns an array of the current queue's priority values
    public PriorityType[] PriorityToArray()
    {
        return priority.ToArray();
    }

    // Returns a list of the current queue's priority values
    public List<PriorityType> PriorityToList()
    {
        return priority;
    }

    // Returns a dictionary of the current queue data and their priorities
    public Dictionary<DataType, PriorityType> ToDictionary()
    {
        Dictionary<DataType, PriorityType> dictionary = new Dictionary<DataType, PriorityType>(queue.Count);

        for (int i = 0; i < queue.Count; i++)
        {
            dictionary[queue[i]] = priority[i];
        }

        return dictionary;
    }

    // Default constructor
    public PriorityQueue()
    {
        queue = new List<DataType>();

        priority = new List<PriorityType>();
    }

    // Array constructor
    public PriorityQueue(DataType[] data, PriorityType[] priority)
    {
        queue = new List<DataType>(data.Length);

        this.priority = new List<PriorityType>(data.Length);

        for (int i = 0; i < data.Length; i++)
        {
            Enqueue(data[i], priority[i]);
        }
    }

    // List constructor
    public PriorityQueue(List<DataType> data, List<PriorityType> priority)
    {
        queue = new List<DataType>(data.Count);

        this.priority = new List<PriorityType>(data.Count);

        for (int i = 0; i < data.Count; i++)
        {
            Enqueue(data[i], priority[i]);
        }
    }

    // Queue constructor
    public PriorityQueue(PriorityQueue<DataType> data)
    {
        queue = data.queue;

        priority = data.priority;
    }
}
