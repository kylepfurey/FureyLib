
// Priority Queue Data Type Script
// by Kyle Furey

using System.Collections.Generic;

// A first in first out list of a specified data type with an associated priority value assigned to each element used for adding and removing data in a specific order.
public class PriorityQueue<DataType>
{
    // The list of nodes in queue in order of oldest to newest and lowest priority to highest priority
    public LinkedList<PriorityQueueElement<DataType>> Queue = new LinkedList<PriorityQueueElement<DataType>>();

    // Add a new node to the queue
    public void Enqueue(PriorityQueueElement<DataType> enqueuedNode)
    {
        // Find the first node with a greater priority
        foreach (PriorityQueueElement<DataType> Node in Queue)
        {
            if (enqueuedNode.priority < Node.priority)
            {
                // Add the node to the queue right before the next node
                Queue.AddBefore(Queue.Find(Node), enqueuedNode);

                return;
            }
        }

        // Add the enqueued node to the end of the list
        Queue.AddLast(enqueuedNode);
    }

    // Add a new node to the queue
    public void Enqueue(DataType data, float priority)
    {
        // Make an element from the data and priority
        PriorityQueueElement<DataType> enqueuedNode = new PriorityQueueElement<DataType>();
        enqueuedNode.data = data; enqueuedNode.priority = priority;

        // Enqueue node
        Enqueue(enqueuedNode);
    }

    // Removes the oldest node with the lowest priority and return the removed node
    public DataType Dequeue()
    {
        // Check if the queue is empty
        if (Queue.Count == 0)
        {
            return default;
        }

        // Store the oldest node with the lowest priority
        PriorityQueueElement<DataType> dequeuedNode = Queue.First.Value;

        // Remove the oldest node with the lowest priority from the queue
        Queue.Remove(dequeuedNode);

        // Return our removed node
        return dequeuedNode.data;
    }

    // Add a new node to the queue (identical to enqueue)
    public void Push(PriorityQueueElement<DataType> enqueuedNode)
    {
        // Find the first node with a greater priority
        foreach (PriorityQueueElement<DataType> Node in Queue)
        {
            if (enqueuedNode.priority < Node.priority)
            {
                // Add the node to the queue right before the next node
                Queue.AddBefore(Queue.Find(Node), enqueuedNode);

                return;
            }
        }

        // Add the enqueued node to the end of the list
        Queue.AddLast(enqueuedNode);
    }

    // Add a new node to the queue (identical to enqueue)
    public void Push(DataType data, float priority)
    {
        // Make an element from the data and priority
        PriorityQueueElement<DataType> enqueuedNode = new PriorityQueueElement<DataType>();
        enqueuedNode.data = data; enqueuedNode.priority = priority;

        // Enqueue node
        Enqueue(enqueuedNode);
    }

    // Removes the oldest node with the lowest priority and return the removed node (identical to dequeue)
    public DataType Pop()
    {
        // Check if the queue is empty
        if (Queue.Count == 0)
        {
            return default;
        }

        // Store the oldest node with the lowest priority
        PriorityQueueElement<DataType> dequeuedNode = Queue.First.Value;

        // Remove the oldest node with the lowest priority from the queue
        Queue.Remove(dequeuedNode);

        // Return our removed node
        return dequeuedNode.data;
    }
}

// A member of the priority queue consisting of a data type value and its priority.
public class PriorityQueueElement<DataType>
{
    // The node in the queue
    public DataType data;

    // The priority of the corresponding node
    public float priority = 0;
}
