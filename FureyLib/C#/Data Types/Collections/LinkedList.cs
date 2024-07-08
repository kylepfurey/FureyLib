
// Linked List Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/list/list/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.linkedlist-1?view=net-8.0

using System;
using System.Collections;
using System.Collections.Generic;

// Data type used for sorting
using SortType = System.Single;

/// <summary>
/// Class used to store a series of nodes with data in a circular doubly linked list.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class LinkedList<DataType> : IEnumerable
{
    // LINKED LIST VARIABLES

    /// <summary>
    /// The head (starting) node of the linked list
    /// </summary>
    private LinkedListNode<DataType> head = null;

    /// <summary>
    /// The current number of nodes in the linked list
    /// </summary>
    private int nodeCount = 0;

    /// <summary>
    /// Readonly count variable
    /// </summary>
    public int Count
    {
        get
        {
            return nodeCount;
        }
    }

    /// <summary>
    /// Readonly first node variable
    /// </summary>
    public LinkedListNode<DataType> First
    {
        get
        {
            return head;
        }
    }

    /// <summary>
    /// Readonly last node variable
    /// </summary>
    public LinkedListNode<DataType> Last
    {
        get
        {
            return nodeCount == 0 ? null : head.previous;
        }
    }


    // TO ARRAY AND LIST

    /// <summary>
    /// Returns an array of the current linked list
    /// </summary>
    /// <returns></returns>
    public DataType[] ToArray()
    {
        if (nodeCount == 0)
        {
            return new DataType[0];
        }

        // Copy the linked list into an array
        DataType[] newArray = new DataType[nodeCount];

        // Set the current nodes
        LinkedListNode<DataType> node = head;

        // Loop through each node and add it to the array
        for (int i = 0; i < nodeCount; i++)
        {
            newArray[i] = node.data;

            node = node.next;
        }

        return newArray;
    }

    /// <summary>
    /// Returns a list of the current linked list
    /// </summary>
    /// <returns></returns>
    public List<DataType> ToList()
    {
        if (nodeCount == 0)
        {
            return null;
        }

        // Copy the linked list into an list
        List<DataType> newList = new List<DataType>(nodeCount);

        // Set the current nodes
        LinkedListNode<DataType> node = head;

        // Loop through each node and add it to the array
        for (int i = 0; i < nodeCount; i++)
        {
            newList.Add(node.data);

            node = node.next;
        }

        return newList;
    }


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public LinkedList()
    {
        head = null;

        nodeCount = 0;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copiedList"></param>
    public LinkedList(LinkedList<DataType> copiedList)
    {
        if (copiedList.nodeCount == 0)
        {
            head = null;

            nodeCount = 0;

            return;
        }

        head = new LinkedListNode<DataType>(copiedList.head.data);

        nodeCount = copiedList.nodeCount;

        if (nodeCount == 1)
        {
            head.previous = head;

            head.next = head;
        }
        else
        {
            DataType[] array = copiedList.ToArray();

            LinkedListNode<DataType> node = head;

            for (int i = 1; i < nodeCount; i++)
            {
                LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(array[i]);

                node.next = newNode;

                newNode.previous = node;

                node = newNode;
            }

            node.next = head;

            head.previous = node;
        }
    }

    /// <summary>
    /// Data constructor
    /// </summary>
    /// <param name="data"></param>
    public LinkedList(DataType data)
    {
        head = new LinkedListNode<DataType>(data);

        head.previous = head;

        head.next = head;

        nodeCount = 1;
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="array"></param>
    public LinkedList(params DataType[] array)
    {
        if (array.Length == 0)
        {
            head = null;

            nodeCount = 0;

            return;
        }

        head = new LinkedListNode<DataType>(array[0]);

        nodeCount = array.Length;

        if (nodeCount == 1)
        {
            head.previous = head;

            head.next = head;
        }
        else
        {
            LinkedListNode<DataType> node = head;

            for (int i = 1; i < array.Length; i++)
            {
                LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(array[i]);

                node.next = newNode;

                newNode.previous = node;

                node = newNode;
            }

            node.next = head;

            head.previous = node;
        }
    }

    /// <summary>
    /// List constructor
    /// </summary>
    /// <param name="list"></param>
    public LinkedList(List<DataType> list)
    {
        if (list.Count == 0)
        {
            head = null;

            nodeCount = 0;

            return;
        }

        head = new LinkedListNode<DataType>(list[0]);

        nodeCount = list.Count;

        if (nodeCount == 1)
        {
            head.previous = head;

            head.next = head;
        }
        else
        {
            LinkedListNode<DataType> node = head;

            for (int i = 1; i < list.Count; i++)
            {
                LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(list[i]);

                node.next = newNode;

                newNode.previous = node;

                node = newNode;
            }

            node.next = head;

            head.previous = node;
        }
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="node"></param>
    public LinkedList(LinkedListNode<DataType> node)
    {
        head = node;

        head.previous = head;

        head.next = head;

        nodeCount = 1;
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="array"></param>
    public LinkedList(params LinkedListNode<DataType>[] array)
    {
        if (array.Length == 0)
        {
            head = null;

            nodeCount = 0;

            return;
        }

        head = array[0];

        nodeCount = array.Length;

        if (nodeCount == 1)
        {
            head.previous = head;

            head.next = head;
        }
        else
        {
            LinkedListNode<DataType> node = head;

            for (int i = 1; i < array.Length; i++)
            {
                node.next = array[i];

                array[i].previous = node;

                node = array[i];
            }

            node.next = head;

            head.previous = node;
        }
    }

    /// <summary>
    /// List constructor
    /// </summary>
    /// <param name="list"></param>
    public LinkedList(List<LinkedListNode<DataType>> list)
    {
        if (list.Count == 0)
        {
            head = null;

            nodeCount = 0;

            return;
        }

        head = list[0];

        nodeCount = list.Count;

        if (nodeCount == 1)
        {
            head.previous = head;

            head.next = head;
        }
        else
        {
            LinkedListNode<DataType> node = head;

            for (int i = 1; i < list.Count; i++)
            {
                node.next = list[i];

                list[i].previous = node;

                node = list[i];
            }

            node.next = head;

            head.previous = node;
        }
    }


    // LINKED LIST EQUALITY

    /// <summary>
    /// Check if another linked list is equal to the linked list
    /// </summary>
    /// <param name="comparedList"></param>
    /// <returns></returns>
    public bool Equals(LinkedList<DataType> comparedList)
    {
        if (nodeCount == 0 || comparedList.nodeCount == 0)
        {
            return false;
        }

        // Check if the sizes are equal
        if (nodeCount != comparedList.nodeCount)
        {
            return false;
        }

        // Set the current nodes
        LinkedListNode<DataType> node = head;

        LinkedListNode<DataType> comparedNode = comparedList.head;

        // Loop through each node to check if they are not equal
        for (int i = 0; i < nodeCount; i++)
        {
            // Are they not equal
            if (!node.data.Equals(comparedNode.data))
            {
                return false;
            }

            node = node.next;

            comparedNode = comparedNode.next;
        }

        // The lists are equal
        return true;
    }

    /// <summary>
    /// Check if another linked list is equal to the linked list
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedList"></param>
    /// <returns></returns>
    public static bool operator ==(LinkedList<DataType> list, LinkedList<DataType> comparedList)
    {
        return list.Equals(comparedList);
    }

    /// <summary>
    /// Check if another linked list is not equal to the linked list
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedList"></param>
    /// <returns></returns>
    public static bool operator !=(LinkedList<DataType> list, LinkedList<DataType> comparedList)
    {
        return !list.Equals(comparedList);
    }


    // SIZE

    /// <summary>
    /// Return the current number of nodes of the linked list
    /// </summary>
    /// <returns></returns>
    public int Size()
    {
        return nodeCount;
    }

    /// <summary>
    /// Return whether the linked list is empty
    /// </summary>
    /// <returns></returns>
    public bool Empty()
    {
        return nodeCount == 0;
    }


    // NODE AND DATA ACCESS

    /// <summary>
    /// Returns the node at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> Get(int index)
    {
        if (index < 0)
        {
            index = nodeCount + index;
        }

        index %= nodeCount;

        LinkedListNode<DataType> node = head;

        int count = nodeCount / 2 - 1;

        if (index <= count)
        {
            for (int i = 0; i < index; i++)
            {
                node = node.next;
            }
        }
        else
        {
            count = nodeCount - index;

            for (int i = 0; i < count; i++)
            {
                node = node.previous;
            }
        }

        return node;
    }

    /// <summary>
    /// Returns the node's data at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType Data(int index)
    {
        return Get(index).data;
    }

    /// <summary>
    /// Returns the first node in the linked list
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> Begin()
    {
        return head;
    }

    /// <summary>
    /// Returns the last node in the linked list
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> End()
    {
        if (nodeCount == 0)
        {
            return null;
        }

        return head.previous;
    }

    /// <summary>
    /// Returns the node's data in the linked list
    /// </summary>
    /// <returns></returns>
    public DataType Front()
    {
        return head.data;
    }

    /// <summary>
    /// Returns the last node's data in the linked list
    /// </summary>
    /// <returns></returns>
    public DataType Back()
    {
        return head.previous.data;
    }


    // LOCATING NODES

    /// <summary>
    /// Finds the first matching node of the given data
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> Find(DataType data)
    {
        if (nodeCount == 0)
        {
            return null;
        }

        LinkedListNode<DataType> node = head;

        for (int i = 0; i < nodeCount; i++)
        {
            if (node.data.Equals(data))
            {
                return node;
            }

            node = node.next;
        }

        return null;
    }

    /// <summary>
    /// Finds the last matching node of the given data
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> FindLast(DataType data)
    {
        if (nodeCount == 0)
        {
            return null;
        }

        LinkedListNode<DataType> node = head.previous;

        for (int i = nodeCount - 1; i >= 0; i++)
        {
            if (node.data.Equals(data))
            {
                return node;
            }

            node = node.previous;
        }

        return null;
    }

    /// <summary>
    /// Returns the index of the given node, or -1 if nothing matched
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int IndexOf(DataType data)
    {
        if (nodeCount == 0)
        {
            return -1;
        }

        LinkedListNode<DataType> node = head;

        for (int i = 0; i < nodeCount; i++)
        {
            if (node.data.Equals(data))
            {
                return i;
            }

            node = node.next;
        }

        return -1;
    }

    /// <summary>
    /// Returns the index of the given node starting from the back, or -1 if nothing matched
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int LastIndexOf(DataType data)
    {
        if (nodeCount == 0)
        {
            return -1;
        }

        LinkedListNode<DataType> node = head.previous;

        for (int i = nodeCount - 1; i >= 0; i++)
        {
            if (node.data.Equals(data))
            {
                return i;
            }

            node = node.previous;
        }

        return -1;
    }

    /// <summary>
    /// Returns whether the linked list contains at least one of the elements 
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool Contains(DataType containedData)
    {
        return Find(containedData) != null;
    }

    /// <summary>
    /// Returns whether the linked list contains at least one of the elements, starting from the back
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool ContainsLast(DataType containedData)
    {
        return FindLast(containedData) != null;
    }

    /// <summary>
    /// Returns the index of the given node, or -1 if nothing matched
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int IndexOf(LinkedListNode<DataType> data)
    {
        if (nodeCount == 0)
        {
            return -1;
        }

        LinkedListNode<DataType> node = head;

        for (int i = 0; i < nodeCount; i++)
        {
            if (node == data)
            {
                return i;
            }

            node = node.next;
        }

        return -1;
    }

    /// <summary>
    /// Returns the index of the given node starting from the back, or -1 if nothing matched
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int LastIndexOf(LinkedListNode<DataType> data)
    {
        if (nodeCount == 0)
        {
            return -1;
        }

        LinkedListNode<DataType> node = head.previous;

        for (int i = nodeCount - 1; i >= 0; i++)
        {
            if (node == data)
            {
                return i;
            }

            node = node.previous;
        }

        return -1;
    }

    /// <summary>
    /// Returns whether the linked list contains the given node
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public bool Contains(LinkedListNode<DataType> node)
    {
        return IndexOf(node) != -1;
    }

    /// <summary>
    /// Returns whether the linked list contains the given node, starting from the back
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public bool ContainsLast(LinkedListNode<DataType> node)
    {
        return LastIndexOf(node) != -1;
    }

    /// <summary>
    /// Returns the total number of instances of the given data in the linked list
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int Total(DataType foundData)
    {
        if (nodeCount == 0)
        {
            return 0;
        }

        int count = 0;

        LinkedListNode<DataType> node = head;

        for (int i = 0; i < nodeCount; i++)
        {
            if (node.data.Equals(foundData))
            {
                count++;
            }

            node = node.next;
        }

        return count;
    }


    // ADDING NODES

    /// <summary>
    /// Inserts a new node of the given data at the end of the linked list
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public LinkedList<DataType> Add(DataType data)
    {
        LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(data);

        if (nodeCount == 0)
        {
            head = newNode;

            head.next = head;

            head.previous = head;

            nodeCount++;

            return this;
        }

        newNode.previous = head.previous;

        newNode.next = head;

        head.previous.next = newNode;

        head.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Inserts a range of new nodes of the given data at the end of the linked list
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddRange(params DataType[] data)
    {
        for (int i = 0; i < data.Length; i++)
        {
            Add(data[i]);
        }

        return this;
    }

    /// <summary>
    /// Inserts a new node of the given data at the front of the linked list
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddFirst(DataType data)
    {
        LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(data);

        if (nodeCount == 0)
        {
            head = newNode;

            head.next = head;

            head.previous = head;

            nodeCount++;

            return this;
        }

        newNode.previous = head.previous;

        newNode.next = head;

        head.previous.next = newNode;

        head.previous = newNode;

        head = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Inserts a range of new nodes of the given data at the front of the linked list
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddFirstRange(params DataType[] data)
    {
        for (int i = 0; i < data.Length; i++)
        {
            AddFirst(data[i]);
        }

        return this;
    }

    /// <summary>
    /// Inserts a new node of the given data before the given node
    /// </summary>
    /// <param name="data"></param>
    /// <param name="node"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddBefore(LinkedListNode<DataType> node, DataType data)
    {
        LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(data);

        if (nodeCount == 0)
        {
            head = newNode;

            head.next = head;

            head.previous = head;

            nodeCount++;

            return this;
        }

        newNode.previous = node.previous;

        newNode.next = node;

        node.previous.next = newNode;

        node.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Inserts a new node of the given data after the given node
    /// </summary>
    /// <param name="data"></param>
    /// <param name="node"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddAfter(LinkedListNode<DataType> node, DataType data)
    {
        LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(data);

        if (nodeCount == 0)
        {
            head = newNode;

            head.next = head;

            head.previous = head;

            nodeCount++;

            return this;
        }

        newNode.previous = node;

        newNode.next = node.next;

        node.next.previous = newNode;

        node.next = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Adds a new node in the linked list at a given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Insert(int index, DataType newData)
    {
        return AddBefore(Get(index), newData);
    }

    /// <summary>
    /// Inserts a new node of the given data at the end of the linked list
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Add(LinkedListNode<DataType> newNode)
    {
        if (nodeCount == 0)
        {
            head = newNode;

            head.next = head;

            head.previous = head;

            nodeCount++;

            return this;
        }

        newNode.previous = head.previous;

        newNode.next = head;

        head.previous.next = newNode;

        head.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Inserts a range of new nodes of the given data at the end of the linked list
    /// </summary>
    /// <param name="nodes"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddRange(params LinkedListNode<DataType>[] nodes)
    {
        for (int i = 0; i < nodes.Length; i++)
        {
            Add(nodes[i]);
        }

        return this;
    }

    /// <summary>
    /// Inserts a new node of the given data at the front of the linked list
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddFirst(LinkedListNode<DataType> newNode)
    {
        if (nodeCount == 0)
        {
            head = newNode;

            head.next = head;

            head.previous = head;

            nodeCount++;

            return this;
        }

        newNode.previous = head.previous;

        newNode.next = head;

        head.previous.next = newNode;

        head.previous = newNode;

        head = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Inserts a range of new nodes of the given data at the front of the linked list
    /// </summary>
    /// <param name="nodes"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddFirstRange(params LinkedListNode<DataType>[] nodes)
    {
        for (int i = 0; i < nodes.Length; i++)
        {
            AddFirst(nodes[i]);
        }

        return this;
    }

    /// <summary>
    /// Inserts a new node of the given data before the given node
    /// </summary>
    /// <param name="node"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddBefore(LinkedListNode<DataType> node, LinkedListNode<DataType> newNode)
    {
        if (nodeCount == 0)
        {
            head = newNode;

            head.next = head;

            head.previous = head;

            nodeCount++;

            return this;
        }

        newNode.previous = node.previous;

        newNode.next = node;

        node.previous.next = newNode;

        node.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Inserts a new node of the given data after the given node
    /// </summary>
    /// <param name="node"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddAfter(LinkedListNode<DataType> node, LinkedListNode<DataType> newNode)
    {
        if (nodeCount == 0)
        {
            head = newNode;

            head.next = head;

            head.previous = head;

            nodeCount++;

            return this;
        }

        newNode.previous = node;

        newNode.next = node.next;

        node.next.previous = newNode;

        node.next = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Adds a new node in the linked list at a given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Insert(int index, LinkedListNode<DataType> newNode)
    {
        return AddBefore(Get(index), newNode);
    }


    // REMOVING NODES

    /// <summary>
    /// Removes a node from its connected nodes
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public LinkedList<DataType> Remove(LinkedListNode<DataType> node)
    {
        nodeCount--;

        if (nodeCount <= 0)
        {
            nodeCount = 0;

            head = null;

            return this;
        }

        node.previous.next = node.next;

        node.next.previous = node.previous;

        if (node == head)
        {
            head = head.next;
        }

        return this;
    }

    /// <summary>
    /// Remove and return the first node of the given data
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> Remove(DataType data)
    {
        LinkedListNode<DataType> node = Find(data);

        if (node == null)
        {
            return null;
        }

        Remove(node);

        return node;
    }

    /// <summary>
    /// Remove and return the last node of the given data
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> RemoveLast(DataType data)
    {
        LinkedListNode<DataType> node = FindLast(data);

        if (node == null)
        {
            return null;
        }

        Remove(node);

        return node;
    }

    /// <summary>
    /// Remove and return the first node from its connected nodes in the linked list
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> RemoveFirst()
    {
        if (head == null)
        {
            return null;
        }

        LinkedListNode<DataType> node = head;

        nodeCount--;

        if (nodeCount <= 0)
        {
            nodeCount = 0;

            head = null;

            return node;
        }

        head.previous.next = head.next;

        head.next.previous = head.previous;

        head = head.next;

        return node;
    }

    /// <summary>
    /// Remove and return the last node from its connected nodes in the linked list
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> RemoveLast()
    {
        if (head == null)
        {
            return null;
        }

        LinkedListNode<DataType> node = head.previous;

        nodeCount--;

        if (nodeCount <= 0)
        {
            nodeCount = 0;

            head = null;

            return node;
        }

        head.previous.previous.next = head;

        head.previous = head.previous.previous;

        return node;
    }

    /// <summary>
    /// Remove and return a node at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> RemoveAt(int index)
    {
        LinkedListNode<DataType> node = Get(index);

        if (node == null)
        {
            return null;
        }

        Remove(node);

        return node;
    }

    /// <summary>
    /// Removes all of the given nodes that match with the data and return the total number of nodes removed
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public int RemoveAll(DataType data)
    {
        int total = 0;

        LinkedListNode<DataType> current = head;

        for (int i = 0; i < nodeCount; i++)
        {
            if (current == null)
            {
                break;
            }

            if (current.data.Equals(data))
            {
                Remove(current);

                total++;

                i--;
            }

            current = current.next;
        }

        return total;
    }

    /// <summary>
    /// Clears the linked list's data
    /// </summary>
    /// <returns></returns>
    public int Clear()
    {
        int total = nodeCount;

        head = null;

        nodeCount = 0;

        return total;
    }


    // NODE OPERATIONS

    /// <summary>
    /// Replaces the first of the found data with the given data and return the index
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public int Replace(DataType replacedData, DataType newData)
    {
        // Find the index of the found data
        int index = IndexOf(replacedData);

        // Check if the data was not found
        if (index == -1)
        {
            return index;
        }

        LinkedListNode<DataType> node = Get(index);

        // Replace the data at the index
        node.data = newData;

        return index;
    }

    /// <summary>
    /// Replaces the last of the found data with the given data and return the index
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public int ReplaceLast(DataType replacedData, DataType newData)
    {
        // Find the index of the found data
        int index = LastIndexOf(replacedData);

        LinkedListNode<DataType> node = Get(index);

        // Check if the data was not found
        if (index == -1)
        {
            return index;
        }

        // Replace the data at the index
        node.data = newData;

        return index;
    }

    /// <summary>
    /// Replaces all of the found data with the given data and returns the total number of replacements
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public int ReplaceAll(DataType replacedData, DataType newData)
    {
        int total = 0;

        LinkedListNode<DataType> current = head;

        for (int i = 0; i < nodeCount; i++)
        {
            if (current == null)
            {
                break;
            }

            if (current.data.Equals(replacedData))
            {
                current.data = newData;

                total++;
            }

            current = current.next;
        }

        return total;
    }

    /// <summary>
    /// Replaces the node with the given node
    /// </summary>
    /// <param name="replacedNode"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Replace(LinkedListNode<DataType> replacedNode, LinkedListNode<DataType> newNode)
    {
        replacedNode.previous.next = newNode;

        replacedNode.next.previous = newNode;

        newNode.previous = replacedNode.previous;

        newNode.next = replacedNode.next;

        if (replacedNode == head)
        {
            head = newNode;
        }

        return this;
    }

    /// <summary>
    /// Replaces the node's data at the given index with the given data, returns the replaced data
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> Set(int index, DataType newData)
    {
        // Replace the data at the index
        LinkedListNode<DataType> node = Get(index);

        node.data = newData;

        return node;
    }

    /// <summary>
    /// Replaces the node's data at the given index with the given data, returns the replaced data
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> Set(int index, LinkedListNode<DataType> newNode)
    {
        // Replace the data at the index
        LinkedListNode<DataType> node = Get(index);

        Replace(node, newNode);

        return node;
    }

    /// <summary>
    /// Swaps two nodes' values
    /// </summary>
    /// <param name="node1"></param>
    /// <param name="node2"></param>
    /// <returns></returns>
    public LinkedList<DataType> Swap(LinkedListNode<DataType> node1, LinkedListNode<DataType> node2)
    {
        if (node1 == node2)
        {
            return this;
        }

        DataType data = node1.data;

        node1.data = node2.data;

        node2.data = data;

        return this;
    }

    /// <summary>
    /// Swaps two nodes' values at two given indicies
    /// </summary>
    /// <param name="index1"></param>
    /// <param name="index2"></param>
    /// <returns></returns>
    public LinkedList<DataType> Swap(int index1, int index2)
    {
        // Check if the indicies are the same
        if (index1 == index2)
        {
            return this;
        }

        return Swap(Get(index1), Get(index2));
    }

    /// <summary>
    /// Gets or sets the node at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> this[int index]
    {
        get => Get(index);
        set => Set(index, value);
    }


    // LINKED LIST OPERATIONS

    /// <summary>
    /// Assigns the list's nodes from another list's nodes
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Assign(LinkedList<DataType> newData)
    {
        if (newData.nodeCount == 0)
        {
            head = null;

            nodeCount = 0;

            return this;
        }

        head = new LinkedListNode<DataType>(newData.head.data);

        nodeCount = newData.nodeCount;

        if (nodeCount == 1)
        {
            head.previous = head;

            head.next = head;
        }
        else
        {
            DataType[] array = newData.ToArray();

            LinkedListNode<DataType> node = head;

            for (int i = 1; i < nodeCount; i++)
            {
                LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(array[i]);

                node.next = newNode;

                newNode.previous = node;

                node = newNode;
            }

            node.next = head;

            head.previous = node;
        }

        return this;
    }

    /// <summary>
    /// Returns a copy of the list's data
    /// </summary>
    /// <returns></returns>
    public LinkedList<DataType> Copy()
    {
        LinkedList<DataType> newList = new LinkedList<DataType>(this);

        return newList;
    }

    /// <summary>
    /// Reverse the nodes
    /// </summary>
    /// <returns></returns>
    public LinkedList<DataType> Reverse()
    {
        // Check length
        if (nodeCount <= 1)
        {
            return this;
        }

        // Loop through each element and swap it with the element across the end
        for (int i = 0; i < nodeCount / 2; i++)
        {
            Swap(i, nodeCount - i - 1);
        }

        return this;
    }

    /// <summary>
    /// Shifts the nodes right
    /// </summary>
    /// <param name="numberOfShifts"></param>
    /// <returns></returns>
    public LinkedList<DataType> ShiftRight(int numberOfShifts)
    {
        if (numberOfShifts < 0)
        {
            return ShiftLeft(-numberOfShifts);
        }

        numberOfShifts %= nodeCount;

        for (int i = 0; i < numberOfShifts; i++)
        {
            head = head.previous;
        }

        return this;
    }

    /// <summary>
    /// Shifts the nodes left
    /// </summary>
    /// <param name="numberOfShifts"></param>
    /// <returns></returns>
    public LinkedList<DataType> ShiftLeft(int numberOfShifts)
    {
        if (numberOfShifts < 0)
        {
            return ShiftRight(-numberOfShifts);
        }

        numberOfShifts %= nodeCount;

        for (int i = 0; i < numberOfShifts; i++)
        {
            head = head.next;
        }

        return this;
    }

    /// <summary>
    /// Bubble sorts the nodes of the linked list relative to the given sort order
    /// </summary>
    /// <param name="sortOrder"></param>
    /// <returns></returns>
    public LinkedList<DataType> Sort(params SortType[] sortOrder)
    {
        // Check length
        if (nodeCount <= 1)
        {
            return this;
        }

        // Place the list elements in the sorted order
        for (int i = 0; i < nodeCount - 1; i++)
        {
            for (int j = 0; j < nodeCount - i - 1; j++)
            {
                if (sortOrder[j] > sortOrder[j + 1])
                {
                    // Swap the two list elements
                    Swap(j, j + 1);

                    // Swap the two sorting elements
                    SortType tempData = sortOrder[j];

                    sortOrder[j] = sortOrder[j + 1];
                    sortOrder[j + 1] = tempData;
                }
            }
        }

        return this;
    }

    /// <summary>
    /// Bubble sorts the nodes of the linked list relative to the given sort order
    /// </summary>
    /// <param name="sortOrder"></param>
    /// <returns></returns>
    public LinkedList<DataType> Sort(List<SortType> sortOrder)
    {
        return Sort(sortOrder.ToArray());
    }


    // TO STRING

    /// <summary>
    /// Converts the nodes of the linked list into a string
    /// </summary>
    /// <returns></returns>
    public string ToString()
    {
        if (nodeCount == 0)
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
}

/// <summary>
/// Class that stores data and connections to the previous and next nodes in a doubly linked list.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class LinkedListNode<DataType>
{
    // LINKED LIST NODE VARIABLES

    /// <summary>
    /// A link to the previous node
    /// </summary>
    public LinkedListNode<DataType> previous = null;

    /// <summary>
    /// This node's data
    /// </summary>
    public DataType data = default(DataType);

    /// <summary>
    /// A link to the next node
    /// </summary>
    public LinkedListNode<DataType> next = null;


    // LINKED LIST NODE CONSTRUCTOR

    /// <summary>
    /// Default constructor
    /// </summary>
    /// <param name="previous"></param>
    /// <param name="data"></param>
    /// <param name="next"></param>
    public LinkedListNode(LinkedListNode<DataType> previous = null, DataType data = default(DataType), LinkedListNode<DataType> next = null)
    {
        this.previous = previous;

        this.data = data;

        this.next = next;
    }

    /// <summary>
    /// Default constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="previous"></param>
    /// <param name="next"></param>
    public LinkedListNode(DataType data, LinkedListNode<DataType> previous = null, LinkedListNode<DataType> next = null)
    {
        this.data = data;

        this.previous = previous;

        this.next = next;
    }
}
