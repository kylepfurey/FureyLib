
// Queue and Priority Queue Data Types Script
// by Kyle Furey

using System.Collections.Generic;

// A first in first out list of a specified data type.
public class Queue<DataType>
{
    // The list of nodes in queue in order of oldest to newest
    private LinkedList<DataType> queue = new LinkedList<DataType>();

    // Add a new node to the queue and return the index
    public int Enqueue(DataType data)
    {
        // Add the enqueued node to the end of the list
        queue.AddLast(data);

        return queue.Count() - 1;
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
        DataType dequeuedNode = queue.First.Value;

        // Remove the oldest node from the queue
        queue.Remove(dequeuedNode);

        // Return our removed node
        return dequeuedNode;
    }

    // Add a new node to the queue and return the index (identical to enqueue)
    public int Push(DataType data)
    {
        // Add the enqueued node to the end of the list
        queue.AddLast(data);

        return queue.Count() - 1;
    }

    // Removes and returns the oldest node (identical to dequeue)
    public DataType Pop()
    {
        // Check if the queue is empty
        if (queue.Count == 0)
        {
            return default(DataType);
        }

        // Store the oldest node
        DataType dequeuedNode = queue.First.Value;

        // Remove the oldest node from the queue
        queue.Remove(dequeuedNode);

        // Return our removed node
        return dequeuedNode;
    }

    // Returns the oldest data (without removing it from the queue)
    public DataType Peek()
    {
        return queue.First.Value;
    }

    // Returns the newest data (without removing it from the queue)
    public DataType PeekLast()
    {
        return queue.Last.Value;
    }

    // Clears the queue and returns the total number of cleared nodes
    public int Clear()
    {
        int total = queue.Count();

        queue.Clear();

        return total;
    }

    // Returns the size of the queue
    public int Size()
    {
        return queue.Count();
    }

    // Returns if the queue is empty
    public bool IsEmpty()
    {
        return queue.Count() == 0;
    }
}

// A first in first out list of a specified data type with an associated priority value assigned to each element used for adding and removing data in a specific order.
public class PriorityQueue<DataType>
{
    // The list of nodes in queue in order of oldest to newest and lowest priority to highest priority
    private LinkedList<PriorityQueueElement<DataType>> queue = new LinkedList<PriorityQueueElement<DataType>>();

    // Add a new node to the queue and return the index
    public int Enqueue(PriorityQueueElement<DataType> enqueuedNode)
    {
        // Find the first node with a greater priority
        int index = 0;

        foreach (PriorityQueueElement<DataType> Node in queue)
        {
            if (enqueuedNode.priority < Node.priority)
            {
                // Add the node to the queue right before the next node
                queue.AddBefore(queue.Find(Node), enqueuedNode);

                return index;
            }

            index++;
        }

        // Add the enqueued node to the end of the list
        queue.AddLast(enqueuedNode);

        return queue.Count - 1;
    }

    // Add a new node to the queue and return the index
    public int Enqueue(DataType data, float priority)
    {
        // Make an element from the data and priority
        PriorityQueueElement<DataType> enqueuedNode = new PriorityQueueElement<DataType>();
        enqueuedNode.data = data; enqueuedNode.priority = priority;

        // Enqueue node
        return Enqueue(enqueuedNode);
    }

    // Removes the oldest node with the lowest priority and return the removed node
    public DataType Dequeue()
    {
        // Check if the queue is empty
        if (queue.Count == 0)
        {
            return default(DataType);
        }

        // Store the oldest node with the lowest priority
        PriorityQueueElement<DataType> dequeuedNode = queue.First.Value;

        // Remove the oldest node with the lowest priority from the queue
        queue.Remove(dequeuedNode);

        // Return our removed node
        return dequeuedNode.data;
    }

    // Add a new node to the queue and return the index (identical to enqueue)
    public int Push(PriorityQueueElement<DataType> enqueuedNode)
    {
        // Find the first node with a greater priority
        int index = 0;

        foreach (PriorityQueueElement<DataType> Node in queue)
        {
            if (enqueuedNode.priority < Node.priority)
            {
                // Add the node to the queue right before the next node
                queue.AddBefore(queue.Find(Node), enqueuedNode);

                return index;
            }

            index++;
        }

        // Add the enqueued node to the end of the list
        queue.AddLast(enqueuedNode);

        return queue.Count - 1;
    }

    // Add a new node to the queue and return the index (identical to enqueue)
    public int Push(DataType data, float priority)
    {
        // Make an element from the data and priority
        PriorityQueueElement<DataType> enqueuedNode = new PriorityQueueElement<DataType>();
        enqueuedNode.data = data; enqueuedNode.priority = priority;

        // Enqueue node
        return Push(enqueuedNode);
    }

    // Removes the oldest node with the lowest priority and return the removed node (identical to dequeue)
    public DataType Pop()
    {
        // Check if the queue is empty
        if (queue.Count == 0)
        {
            return default(DataType);
        }

        // Store the oldest node with the lowest priority
        PriorityQueueElement<DataType> dequeuedNode = queue.First.Value;

        // Remove the oldest node with the lowest priority from the queue
        queue.Remove(dequeuedNode);

        // Return our removed node
        return dequeuedNode.data;
    }

    // Returns the data with the highest priority (without removing it from the queue)
    public DataType Peek()
    {
        return queue.First.Value.data;
    }

    // Returns the data with the lowest priority (without removing it from the queue)
    public DataType PeekLast()
    {
        return queue.Last.Value.data;
    }

    // Returns the highest priority value (the priority which is closest to being dequeued)
    public float HighestPriority()
    {
        return queue.First.Value.priority;
    }

    // Returns the lowest priority value (the priority which is furthest from being dequeued)
    public float LowestPriority()
    {
        return queue.Last.Value.priority;
    }

    // Clears the queue and returns the total number of cleared nodes
    public int Clear()
    {
        int total = queue.Count();

        queue.Clear();

        return total;
    }

    // Returns the size of the queue
    public int Size()
    {
        return queue.Count();
    }

    // Returns if the queue is empty
    public bool IsEmpty()
    {
        return queue.Count() == 0;
    }
}

// A member of the priority queue consisting of a data type value and its priority.
public class PriorityQueueElement<DataType>
{
    // The node in the queue
    public DataType data = default(DataType);

    // The priority of the corresponding node
    public float priority = 1;
}
