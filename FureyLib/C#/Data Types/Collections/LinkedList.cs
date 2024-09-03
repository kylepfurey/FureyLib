
// Linked List Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/list/list/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.linkedlist-1?view=net-8.0

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

/// <summary>
/// Class used to store a series of nodes with data in a circular doubly linked list.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class LinkedList<DataType> : IEnumerable, IEnumerable<DataType>
{
    // VARIABLES

    /// <summary>
    /// The head (starting) node of the linked list
    /// </summary>
    private LinkedListNode<DataType> head = null;

    /// <summary>
    /// The current number of nodes in the linked list
    /// </summary>
    private int nodeCount = 0;


    // PROPERTIES

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

        DataType[] newArray = new DataType[nodeCount];

        LinkedListNode<DataType> node = head;

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

        List<DataType> newList = new List<DataType>(nodeCount);

        LinkedListNode<DataType> node = head;

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
    /// Enumerable constructor
    /// </summary>
    /// <param name="list"></param>
    public LinkedList(IEnumerable<DataType> list)
    {
        nodeCount = list.Count();

        if (nodeCount == 0)
        {
            head = null;

            nodeCount = 0;

            return;
        }

        foreach (DataType data in list)
        {
            head = new LinkedListNode<DataType>(data);

            break;
        }

        if (nodeCount == 1)
        {
            head.previous = head;

            head.next = head;
        }
        else
        {
            LinkedListNode<DataType> node = head;

            foreach (DataType data in list)
            {
                LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(data);

                node.next = newNode;

                newNode.previous = node;

                node = newNode;
            }

            node.next = head;

            head.previous = node;
        }
    }


    // EQUALITY

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

        if (nodeCount != comparedList.nodeCount)
        {
            return false;
        }

        LinkedListNode<DataType> node = head;

        LinkedListNode<DataType> comparedNode = comparedList.head;

        for (int i = 0; i < nodeCount; i++)
        {
            if (!node.data.Equals(comparedNode.data))
            {
                return false;
            }

            node = node.next;

            comparedNode = comparedNode.next;
        }

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


    // ITERATORS

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


    // CAPACITY

    /// <summary>
    /// Returns whether the linked list is empty
    /// </summary>
    /// <returns></returns>
    public bool Empty()
    {
        return nodeCount == 0;
    }

    /// <summary>
    /// Returns the current number of nodes of the linked list
    /// </summary>
    /// <returns></returns>
    public int Size()
    {
        return nodeCount;
    }


    // ELEMENT ACCESS

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


    // LOCATING ELEMENTS

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
    /// Returns whether the linked list contains at least one of the elements 
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool Contains(DataType containedData)
    {
        return Find(containedData) != null;
    }

    /// <summary>
    /// Returns whether the linked list contains the given node
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public bool Contains(LinkedListNode<DataType> node)
    {
        LinkedListNode<DataType> current = head;

        for (int i = 0; i < nodeCount; i++)
        {
            if (current == node)
            {
                return true;
            }
            else
            {
                current = current.next;
            }
        }

        return false;
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

    /// <summary>
    /// Returns the total number of instances of the given data in the linked list
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public int Total(LinkedListNode<DataType> node)
    {
        return Total(node.data);
    }


    // MODIFIERS

    /// <summary>
    /// Assigns the linked list's nodes from another linked list's nodes
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
    /// Inserts a new node of the given data at the front of the linked list
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> AddFirst(DataType data)
    {
        LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(data);

        if (nodeCount == 0)
        {
            head = newNode;

            head.next = head;

            head.previous = head;

            nodeCount++;

            return newNode;
        }

        newNode.previous = head.previous;

        newNode.next = head;

        head.previous.next = newNode;

        head.previous = newNode;

        head = newNode;

        nodeCount++;

        return newNode;
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
    /// Inserts a new node of the given data at the end of the linked list
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> AddLast(DataType data)
    {
        LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(data);

        if (nodeCount == 0)
        {
            head = newNode;

            head.next = head;

            head.previous = head;

            nodeCount++;

            return newNode;
        }

        newNode.previous = head.previous;

        newNode.next = head;

        head.previous.next = newNode;

        head.previous = newNode;

        nodeCount++;

        return newNode;
    }

    /// <summary>
    /// Inserts a new node of the given data at the end of the linked list
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddLast(LinkedListNode<DataType> newNode)
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

        if (node == head)
        {
            head = newNode;
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

        if (node == head)
        {
            head = newNode;
        }

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
    /// Removes a node from its connected nodes
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public LinkedList<DataType> Remove(LinkedListNode<DataType> node)
    {
        if (!Contains(node))
        {
            return this;
        }

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


    // ELEMENT OPERATIONS

    /// <summary>
    /// Replaces the first of the found data with the given data 
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> Replace(DataType replacedData, DataType newData)
    {
        LinkedListNode<DataType> node = Find(replacedData);

        if (node != null)
        {
            node.data = newData;
        }

        return node;
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
    /// Replaces the last of the found data with the given data 
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> ReplaceLast(DataType replacedData, DataType newData)
    {
        LinkedListNode<DataType> node = FindLast(replacedData);

        if (node != null)
        {
            node.data = newData;
        }

        return node;
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


    // OPERATIONS

    /// <summary>
    /// Transfers another linked list's nodes to this linked list
    /// </summary>
    /// <param name="startNode"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Splice(LinkedListNode<DataType> startNode, LinkedList<DataType> newData)
    {
        for (int i = 0; i < newData.nodeCount; i++)
        {
            AddBefore(startNode, newData.head);

            newData.RemoveFirst();

            startNode = startNode.next;
        }

        return this;
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
    /// Removes duplicate values from this linked list and return the total number of removals
    /// </summary>
    /// <returns></returns>
    public int RemoveDuplicates()
    {
        int count = 0;

        LinkedListNode<DataType> node = head;

        do
        {
            int total = Total(node.data) - 1;

            count += total;

            for (int i = 0; i < total; i++)
            {
                RemoveLast(node.data);
            }

            node = node.next;
        } while (node != head);

        return count;
    }

    /// <summary>
    /// Merges the given linked list into this linked list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Merge(LinkedList<DataType> newData)
    {
        for (int i = 0; i < newData.nodeCount; i++)
        {
            AddLast(newData.head);

            newData.RemoveFirst();
        }

        return this;
    }

    /// <summary>
    /// Bubble sorts the nodes of the linked list relative to the given sort order
    /// </summary>
    /// <param name="sortOrder"></param>
    /// <returns></returns>
    public LinkedList<DataType> Sort<SortType>(params SortType[] sortOrder) where SortType : IComparable
    {
        if (nodeCount <= 1)
        {
            return this;
        }

        for (int i = 0; i < nodeCount - 1; i++)
        {
            for (int j = 0; j < nodeCount - i - 1; j++)
            {
                LinkedListNode<DataType> node = head;

                if (sortOrder[j].CompareTo(sortOrder[j + 1]) > 0)
                {
                    Swap(node, node.next);

                    SortType tempData = sortOrder[j];

                    sortOrder[j] = sortOrder[j + 1];

                    sortOrder[j + 1] = tempData;
                }

                node = node.next;
            }
        }

        return this;
    }

    /// <summary>
    /// Bubble sorts the nodes of the linked list relative to the given sort order
    /// </summary>
    /// <param name="sortOrder"></param>
    /// <returns></returns>
    public LinkedList<DataType> Sort<SortType>(List<SortType> sortOrder) where SortType : IComparable
    {
        return Sort(sortOrder.ToArray());
    }

    /// <summary>
    /// Bubble sorts the nodes of the linked list relative to the given sort order
    /// </summary>
    /// <param name="sortOrder"></param>
    /// <returns></returns>
    public LinkedList<DataType> Sort<SortType>(LinkedList<SortType> sortOrder) where SortType : IComparable
    {
        return Sort(sortOrder.ToArray());
    }

    /// <summary>
    /// Reverse the nodes
    /// </summary>
    /// <returns></returns>
    public LinkedList<DataType> Reverse()
    {
        if (nodeCount <= 1)
        {
            return this;
        }

        LinkedListNode<DataType> node = head;

        LinkedListNode<DataType> endNode = head.previous;

        for (int i = 0; i < nodeCount / 2; i++)
        {
            Swap(node, endNode);

            node = node.next;

            endNode = endNode.previous;
        }

        return this;
    }

    /// <summary>
    /// Swaps the linked list's nodes with another linked list's nodes
    /// </summary>
    /// <param name="swappedData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Swap(LinkedList<DataType> swappedData)
    {
        LinkedListNode<DataType> data = head;

        int count = nodeCount;

        head = swappedData.head;

        nodeCount = swappedData.nodeCount;

        swappedData.head = data;

        swappedData.nodeCount = count;

        return this;
    }

    /// <summary>
    /// Returns a copy of the list's data
    /// </summary>
    /// <returns></returns>
    public LinkedList<DataType> Copy()
    {
        return new LinkedList<DataType>(this);
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

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    IEnumerator<DataType> IEnumerable<DataType>.GetEnumerator()
    {
        return (IEnumerator<DataType>)ToArray().GetEnumerator();
    }

    /// <summary>
    /// Inserts a new node of the given data at the end of the linked list
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> Add(DataType data)
    {
        return AddLast(data);
    }

    /// <summary>
    /// Inserts a new node of the given data at the end of the linked list
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public LinkedList<DataType> Add(LinkedListNode<DataType> data)
    {
        return AddLast(data);
    }
}

/// <summary>
/// Class that stores data and connections to the previous and next nodes in a doubly linked list.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class LinkedListNode<DataType>
{
    // VARIABLES

    /// <summary>
    /// This node's data
    /// </summary>
    public DataType data = default(DataType);

    /// <summary>
    /// A link to the previous node
    /// </summary>
    public LinkedListNode<DataType> previous = null;

    /// <summary>
    /// A link to the next node
    /// </summary>
    public LinkedListNode<DataType> next = null;


    // PROPERTIES

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
    /// Readonly data reference variable
    /// </summary>
    public ref DataType ValueRef
    {
        get
        {
            return ref data;
        }
    }

    /// <summary>
    /// Readonly previous node variable
    /// </summary>
    public LinkedListNode<DataType> Previous
    {
        get
        {
            return previous;
        }
    }

    /// <summary>
    /// Readonly next node variable
    /// </summary>
    public LinkedListNode<DataType> Next
    {
        get
        {
            return next;
        }
    }


    // CONSTRUCTOR

    /// <summary>
    /// Default constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="previous"></param>
    /// <param name="next"></param>
    public LinkedListNode(DataType data = default(DataType), LinkedListNode<DataType> previous = null, LinkedListNode<DataType> next = null)
    {
        this.data = data;

        this.previous = previous;

        this.next = next;
    }
}
