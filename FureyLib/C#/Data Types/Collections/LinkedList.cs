
// Linked List Data Type Class
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/list/list/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.linkedlist-1?view=net-8.0

using System;
using System.Collections;
using System.Collections.Generic;

// Data type used for sorting
using SortType = System.Single;

/// <summary>
/// Doubly linked list circular container class.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class LinkedList<DataType> : IEnumerable
{
    // LINKED LIST VARIABLES

    /// <summary>
    /// The head node (starting point) of this linked list
    /// </summary>
    private LinkedListNode<DataType> head;

    /// <summary>
    /// The current number of nodes in the list
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
            return head.previous;
        }
    }


    // TO ARRAY AND LIST

    /// <summary>
    /// Returns an array of the current linked list
    /// </summary>
    /// <returns></returns>
    public DataType[] ToArray()
    {
        if (head == null)
        {
            return null;
        }

        // Copy the list into an array
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
    /// Returns an list of the current linked list
    /// </summary>
    /// <returns></returns>
    public List<DataType> ToList()
    {
        if (head == null)
        {
            return null;
        }

        // Copy the list into an array
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


    // LIST EQUALITY

    /// <summary>
    /// Check if another linked list is equal to this linked list
    /// </summary>
    /// <param name="comparedList"></param>
    /// <returns></returns>
    public bool Equals(LinkedList<DataType> comparedList)
    {
        if (head == null || comparedList.head == null)
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
    /// Check if another linked list is equal to this linked list
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedList"></param>
    /// <returns></returns>
    public static bool operator ==(LinkedList<DataType> list, LinkedList<DataType> comparedList)
    {
        return list.Equals(comparedList);
    }

    /// <summary>
    /// Check if another linked list is not equal to this linked list
    /// </summary>
    /// <param name="list"></param>
    /// <param name="comparedList"></param>
    /// <returns></returns>
    public static bool operator !=(LinkedList<DataType> list, LinkedList<DataType> comparedList)
    {
        return !list.Equals(comparedList);
    }


    // COUNT

    /// <summary>
    /// Return the current size of the linked list
    /// </summary>
    /// <returns></returns>
    public int Size()
    {
        return nodeCount;
    }

    /// <summary>
    /// Return the current size of the linked list
    /// </summary>
    /// <returns></returns>
    public int Length()
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

    /// <summary>
    /// Return whether the linked list is empty
    /// </summary>
    /// <returns></returns>
    public bool IsEmpty()
    {
        return Empty();
    }


    // NODE ACCESS

    /// <summary>
    /// Return the beginning node
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> Begin()
    {
        return head;
    }

    /// <summary>
    /// Return the beginning node
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> Head()
    {
        return head;
    }

    /// <summary>
    /// Returns the first node in the list
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> FrontNode()
    {
        return head;
    }

    /// <summary>
    /// Return the end node
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> End()
    {
        return head.previous;
    }

    /// <summary>
    /// Return the end node
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> Tail()
    {
        return head.previous;
    }

    /// <summary>
    /// Returns the first node in the list
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> BackNode()
    {
        return head.previous;
    }

    /// <summary>
    /// Returns the node at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> NodeAt(int index)
    {
        LinkedListNode<DataType> element = head;

        int count = nodeCount / 2 - 1;

        if (index <= count)
        {
            for (int i = 0; i < index; i++)
            {
                element = element.next;
            }
        }
        else
        {
            count = nodeCount - index;

            for (int i = 0; i < count; i++)
            {
                element = element.previous;
            }
        }

        return element;
    }

    /// <summary>
    /// Returns the node at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> GetNode(int index)
    {
        return NodeAt(index);
    }

    /// <summary>
    /// Returns the node at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> Node(int index)
    {
        return NodeAt(index);
    }

    /// <summary>
    /// Returns the node at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public LinkedListNode<DataType> this[int index]
    {
        get => GetNode(index);
        set => Set(index, value);
    }


    // ELEMENT ACCESS

    /// <summary>
    /// Returns the element at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType At(int index)
    {
        return NodeAt(index).data;
    }

    /// <summary>
    /// Returns the element at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType Get(int index)
    {
        return At(index);
    }

    /// <summary>
    /// Returns the element at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DataType Data(int index)
    {
        return At(index);
    }

    /// <summary>
    /// Returns the first element in the list
    /// </summary>
    /// <returns></returns>
    public DataType Front()
    {
        return head.data;
    }

    /// <summary>
    /// Returns the first element in the list
    /// </summary>
    /// <returns></returns>
    public DataType Back()
    {
        return head.previous.data;
    }


    // MODIFIERS

    /// <summary>
    /// Assigns this linked list's nodes to the nodes of another linked list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Assign(LinkedList<DataType> newData)
    {
        if (newData.head == null)
        {
            head = null;

            return this;
        }

        nodeCount = newData.nodeCount;

        DataType[] array = newData.ToArray();

        head = new LinkedListNode<DataType>(array[0]);

        LinkedListNode<DataType> node = head;

        for (int i = 1; i < array.Length; i++)
        {
            node.next = new LinkedListNode<DataType>(array[i]);

            node = node.next;
        }

        node.next = head;

        head.previous = node;

        return this;
    }

    /// <summary>
    /// Adds a new node at the front of the linked list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Push(DataType newData)
    {
        nodeCount++;

        if (head == null)
        {
            head = new LinkedListNode<DataType>(newData);

            head.next = head;

            head.previous = head;

            return this;
        }

        LinkedListNode<DataType> node = head;

        head = new LinkedListNode<DataType>(newData);

        head.next = node;

        head.previous = node.previous;

        node.previous.next = head;

        node.previous = head;

        return this;
    }

    /// <summary>
    /// Adds a new node at the front of the linked list
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Push(LinkedListNode<DataType> newNode)
    {
        nodeCount++;

        if (head == null)
        {
            head = newNode;

            head.next = head;

            head.previous = head;

            return this;
        }

        LinkedListNode<DataType> node = head;

        head = newNode;

        head.next = node;

        head.previous = node.previous;

        node.previous.next = head;

        node.previous = head;

        return this;
    }

    /// <summary>
    /// Adds a new node at the front of the linked list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> PushFront(DataType newData)
    {
        return Push(newData);
    }

    /// <summary>
    /// Adds a new node at the front of the linked list
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> PushFront(LinkedListNode<DataType> newNode)
    {
        return Push(newNode);
    }

    /// <summary>
    /// Adds a new node at the front of the linked list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Enqueue(DataType newData)
    {
        return Push(newData);
    }

    /// <summary>
    /// Adds a new node at the front of the linked list
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Enqueue(LinkedListNode<DataType> newNode)
    {
        return Push(newNode);
    }

    /// <summary>
    /// Adds a new node at the front of the linked list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddFront(DataType newData)
    {
        return Push(newData);
    }

    /// <summary>
    /// Adds a new node at the front of the linked list
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddFront(LinkedListNode<DataType> newNode)
    {
        return Push(newNode);
    }

    /// <summary>
    /// Adds a new node at the end of the linked list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddFirst(DataType newData)
    {
        return Push(newData);
    }

    /// <summary>
    /// Adds a new node at the end of the linked list
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddFirst(LinkedListNode<DataType> newNode)
    {
        return Push(newNode);
    }

    /// <summary>
    /// Adds a new node at the end of the linked list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> PushBack(DataType newData)
    {
        nodeCount++;

        if (head == null)
        {
            head = new LinkedListNode<DataType>(newData);

            head.next = head;

            head.previous = head;

            return this;
        }

        LinkedListNode<DataType> node = head.previous;

        head.previous = new LinkedListNode<DataType>(newData);

        head.previous.next = head;

        head.previous.previous = node;

        node.next = head.previous;

        return this;
    }

    /// <summary>
    /// Adds a new node at the end of the linked list
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> PushBack(LinkedListNode<DataType> newNode)
    {
        nodeCount++;

        if (head == null)
        {
            head = newNode;

            head.next = head;

            head.previous = head;

            return this;
        }

        LinkedListNode<DataType> node = head.previous;

        head.previous = newNode;

        head.previous.next = head;

        head.previous.previous = node;

        node.next = head.previous;

        return this;
    }

    /// <summary>
    /// Adds a new node at the end of the linked list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Add(DataType newData)
    {
        return PushBack(newData);
    }

    /// <summary>
    /// Adds a new node at the end of the linked list
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Add(LinkedListNode<DataType> newNode)
    {
        return PushBack(newNode);
    }

    /// <summary>
    /// Adds a new node at the end of the linked list
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddLast(LinkedListNode<DataType> newNode)
    {
        return PushBack(newNode);
    }

    /// <summary>
    /// Adds a new node at the end of the linked list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddLast(DataType newData)
    {
        return PushBack(newData);
    }

    /// <summary>
    /// Remove and return the first node of the linked list
    /// </summary>
    /// <returns></returns>
    public DataType Pop()
    {
        nodeCount--;

        if (nodeCount == 0)
        {
            DataType data = head.data;

            head = null;

            return data;
        }

        DataType newData = head.data;

        head.previous.next = head.next;

        head.next.previous = head.previous;

        head = head.next;

        return newData;
    }

    /// <summary>
    /// Remove and return the first node of the linked list
    /// </summary>
    /// <returns></returns>
    public DataType PopFront()
    {
        return Pop();
    }

    /// <summary>
    /// Remove and return the first node of the linked list
    /// </summary>
    /// <returns></returns>
    public DataType RemoveFront()
    {
        return Pop();
    }

    /// <summary>
    /// Remove and return the last node of the linked list
    /// </summary>
    /// <returns></returns>
    public DataType RemoveFirst()
    {
        return Pop();
    }

    /// <summary>
    /// Remove and return the first node of the linked list
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> PopNode()
    {
        nodeCount--;

        if (nodeCount == 0)
        {
            LinkedListNode<DataType> node = head;

            head = null;

            return node;
        }

        LinkedListNode<DataType> newNode = head;

        head.previous.next = head.next;

        head.next.previous = head.previous;

        head = head.next;

        return newNode;
    }

    /// <summary>
    /// Remove and return the first node of the linked list
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> PopFrontNode()
    {
        return PopNode();
    }

    /// <summary>
    /// Remove and return the first node of the linked list
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> RemoveFrontNode()
    {
        return PopNode();
    }

    /// <summary>
    /// Remove and return the first node of the linked list
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> RemoveFirstNode()
    {
        return PopNode();
    }

    /// <summary>
    /// Remove and return the last node of the linked list
    /// </summary>
    /// <returns></returns>
    public DataType PopBack()
    {
        nodeCount--;

        if (nodeCount == 0)
        {
            DataType data = head.data;

            head = null;

            return data;
        }

        DataType newData = head.previous.data;

        head.next.previous = head.previous;

        head.previous.next = head.next;

        return newData;
    }

    /// <summary>
    /// Remove and return the last node of the linked list
    /// </summary>
    /// <returns></returns>
    public DataType Dequeue()
    {
        return PopBack();
    }

    /// <summary>
    /// Remove and return the last node of the linked list
    /// </summary>
    /// <returns></returns>
    public DataType RemoveBack()
    {
        return PopBack();
    }

    /// <summary>
    /// Remove and return the last node of the linked list
    /// </summary>
    /// <returns></returns>
    public DataType RemoveLast()
    {
        return PopBack();
    }

    /// <summary>
    /// Remove and return the last node of the linked list
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> PopBackNode()
    {
        nodeCount--;

        if (nodeCount == 0)
        {
            LinkedListNode<DataType> node = head;

            head = null;

            return node;
        }

        LinkedListNode<DataType> newNode = head.previous;

        head.next.previous = head.previous;

        head.previous.next = head.next;

        return newNode;
    }

    /// <summary>
    /// Remove and return the last node of the linked list
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> DequeueNode()
    {
        return PopBackNode();
    }

    /// <summary>
    /// Remove and return the last node of the linked list
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> RemoveBackNode()
    {
        return PopBackNode();
    }

    /// <summary>
    /// Remove and return the last node of the linked list
    /// </summary>
    /// <returns></returns>
    public LinkedListNode<DataType> RemoveLastNode()
    {
        return PopBackNode();
    }

    /// <summary>
    /// Adds a new node in the linked list at a given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Insert(int index, DataType newData)
    {
        // Check for out of bounds
        if (index < 0 || index >= nodeCount)
        {
            return this;
        }

        LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(newData);

        LinkedListNode<DataType> oldNode = NodeAt(index);

        newNode.next = oldNode;

        newNode.previous = oldNode.previous;

        oldNode.previous.next = newNode;

        oldNode.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Adds a new node in the linked list at a given node
    /// </summary>
    /// <param name="oldNode"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Insert(LinkedListNode<DataType> oldNode, DataType newData)
    {
        LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(newData);

        newNode.next = oldNode;

        newNode.previous = oldNode.previous;

        oldNode.previous.next = newNode;

        oldNode.previous = newNode;

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
        LinkedListNode<DataType> oldNode = NodeAt(index);

        newNode.next = oldNode;

        newNode.previous = oldNode.previous;

        oldNode.previous.next = newNode;

        oldNode.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Adds a new node in the linked list at a given node
    /// </summary>
    /// <param name="oldNode"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Insert(LinkedListNode<DataType> oldNode, LinkedListNode<DataType> newNode)
    {
        newNode.next = oldNode;

        newNode.previous = oldNode.previous;

        oldNode.previous.next = newNode;

        oldNode.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Adds a new node in the linked list at a given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddBefore(int index, DataType newData)
    {
        return Insert(index, newData);
    }

    /// <summary>
    /// Adds a new node in the linked list at a given node
    /// </summary>
    /// <param name="oldNode"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddBefore(LinkedListNode<DataType> oldNode, DataType newData)
    {
        return Insert(oldNode, newData);
    }

    /// <summary>
    /// Adds a new node in the linked list at a given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddBefore(int index, LinkedListNode<DataType> newNode)
    {
        return Insert(index, newNode);
    }

    /// <summary>
    /// Adds a new node in the linked list at a given node
    /// </summary>
    /// <param name="oldNode"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddBefore(LinkedListNode<DataType> oldNode, LinkedListNode<DataType> newNode)
    {
        return Insert(oldNode, newNode);
    }

    /// <summary>
    /// Adds a new node in the linked list after a given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> InsertAfter(int index, DataType newData)
    {
        // Check for out of bounds
        if (index < 0 || index >= nodeCount)
        {
            return this;
        }

        if (index == nodeCount - 1)
        {
            return PushBack(newData);
        }

        LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(newData);

        LinkedListNode<DataType> oldNode = NodeAt(index + 1);

        newNode.next = oldNode;

        newNode.previous = oldNode.previous;

        oldNode.previous.next = newNode;

        oldNode.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Adds a new node in the linked list after a given node
    /// </summary>
    /// <param name="oldNode"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> InsertAfter(LinkedListNode<DataType> oldNode, DataType newData)
    {
        LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(newData);

        oldNode = oldNode.next;

        newNode.next = oldNode;

        newNode.previous = oldNode.previous;

        oldNode.previous.next = newNode;

        oldNode.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Adds a new node in the linked list after a given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> InsertAfter(int index, LinkedListNode<DataType> newNode)
    {

        if (index == nodeCount - 1)
        {
            return PushBack(newNode);
        }

        LinkedListNode<DataType> oldNode = NodeAt(index + 1);

        newNode.next = oldNode;

        newNode.previous = oldNode.previous;

        oldNode.previous.next = newNode;

        oldNode.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Adds a new node in the linked list after a given node
    /// </summary>
    /// <param name="oldNode"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> InsertAfter(LinkedListNode<DataType> oldNode, LinkedListNode<DataType> newNode)
    {
        oldNode = oldNode.next;

        newNode.next = oldNode;

        newNode.previous = oldNode.previous;

        oldNode.previous.next = newNode;

        oldNode.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Adds a new node in the linked list after a given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddAfter(int index, DataType newData)
    {
        return InsertAfter(index, newData);
    }

    /// <summary>
    /// Adds a new node in the linked list after a given node
    /// </summary>
    /// <param name="oldNode"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddAfter(LinkedListNode<DataType> oldNode, DataType newData)
    {
        return InsertAfter(oldNode, newData);
    }

    /// <summary>
    /// Adds a new node in the linked list after a given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddAfter(int index, LinkedListNode<DataType> newNode)
    {
        return InsertAfter(index, newNode);
    }

    /// <summary>
    /// Adds a new node in the linked list after a given node
    /// </summary>
    /// <param name="oldNode"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> AddAfter(LinkedListNode<DataType> oldNode, LinkedListNode<DataType> newNode)
    {
        return InsertAfter(oldNode, newNode);
    }

    /// <summary>
    /// Removes a node in the linked list at a given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public LinkedList<DataType> Erase(int index)
    {
        if (index == 0 && nodeCount == 1)
        {
            head = null;

            nodeCount--;

            return this;
        }

        // Check for out of bounds
        if (index < 0 || index >= nodeCount)
        {
            return this;
        }

        LinkedListNode<DataType> removedNode = NodeAt(index);

        removedNode.next.previous = removedNode.previous;

        removedNode.previous.next = removedNode.next;

        nodeCount--;

        return this;
    }

    /// <summary>
    /// Removes a node in the linked list
    /// </summary>
    /// <param name="removedNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Erase(LinkedListNode<DataType> removedNode)
    {
        if (removedNode == head && nodeCount == 1)
        {
            head = null;

            nodeCount--;

            return this;
        }

        removedNode.next.previous = removedNode.previous;

        removedNode.previous.next = removedNode.next;

        nodeCount--;

        return this;
    }

    /// <summary>
    /// Removes a node in the linked list at a given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public LinkedList<DataType> RemoveAt(int index)
    {
        return Erase(index);
    }

    /// <summary>
    /// Removes a node in the linked list at a given node
    /// </summary>
    /// <param name="removedNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> RemoveAt(LinkedListNode<DataType> removedNode)
    {
        return Erase(removedNode);
    }

    /// <summary>
    /// Swaps two nodes at two given indicies
    /// </summary>
    /// <param name="index1"></param>
    /// <param name="index2"></param>
    /// <returns></returns>
    public LinkedList<DataType> Swap(int index1, int index2)
    {
        // Check for out of bounds
        if (index1 < 0 || index1 >= nodeCount || index2 < 0 || index2 >= nodeCount)
        {
            return this;
        }

        LinkedListNode<DataType> node1 = NodeAt(index1);

        LinkedListNode<DataType> node2 = NodeAt(index2);

        DataType movedData = node1.data;

        node1.data = node2.data;

        node2.data = movedData;

        return this;
    }

    /// <summary>
    /// Swaps two nodes
    /// </summary>
    /// <param name="node1"></param>
    /// <param name="node2"></param>
    /// <returns></returns>
    public LinkedList<DataType> Swap(LinkedListNode<DataType> node1, LinkedListNode<DataType> node2)
    {
        DataType movedData = node1.data;

        node1.data = node2.data;

        node2.data = movedData;

        return this;
    }

    /// <summary>
    /// Clears the linked list's data
    /// </summary>
    /// <returns></returns>
    public LinkedList<DataType> Clear()
    {
        nodeCount = 0;

        head = null;

        return this;
    }

    /// <summary>
    /// Adds an existing variable to a given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Emplace(int index, ref DataType newData)
    {
        // Check for out of bounds
        if (index < 0 || index >= nodeCount)
        {
            return this;
        }

        LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(newData);

        LinkedListNode<DataType> oldNode = NodeAt(index);

        newNode.next = oldNode;

        newNode.previous = oldNode.previous;

        oldNode.previous.next = newNode;

        oldNode.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Adds an existing variable to a given index
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Emplace(int index, ref LinkedListNode<DataType> newNode)
    {
        // Check for out of bounds
        if (index < 0 || index >= nodeCount)
        {
            return this;
        }

        LinkedListNode<DataType> oldNode = NodeAt(index);

        newNode.next = oldNode;

        newNode.previous = oldNode.previous;

        oldNode.previous.next = newNode;

        oldNode.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Adds an existing variable to a given node
    /// </summary>
    /// <param name="oldNode"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Emplace(LinkedListNode<DataType> oldNode, ref DataType newData)
    {
        LinkedListNode<DataType> newNode = new LinkedListNode<DataType>(newData);

        newNode.next = oldNode;

        newNode.previous = oldNode.previous;

        oldNode.previous.next = newNode;

        oldNode.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Adds an existing variable to a given node
    /// </summary>
    /// <param name="oldNode"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Emplace(LinkedListNode<DataType> oldNode, ref LinkedListNode<DataType> newNode)
    {
        newNode.next = oldNode;

        newNode.previous = oldNode.previous;

        oldNode.previous.next = newNode;

        oldNode.previous = newNode;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Adds an existing variable to the front of the linked list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Emplace(ref DataType newData)
    {
        nodeCount++;

        if (head == null)
        {
            head = new LinkedListNode<DataType>(newData);

            head.next = head;

            head.previous = head;

            return this;
        }

        LinkedListNode<DataType> node = head;

        head = new LinkedListNode<DataType>(newData);

        head.next = node;

        head.previous = node.previous;

        node.previous.next = head;

        node.previous = head;

        return this;
    }

    /// <summary>
    /// Adds an existing variable to the front of the linked list
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Emplace(ref LinkedListNode<DataType> newNode)
    {
        nodeCount++;

        if (head == null)
        {
            head = newNode;

            head.next = head;

            head.previous = head;

            return this;
        }

        LinkedListNode<DataType> node = head;

        head = newNode;

        head.next = node;

        head.previous = node.previous;

        node.previous.next = head;

        node.previous = head;

        return this;
    }

    /// <summary>
    /// Adds an existing variable to the front of the linked list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> EmplaceFront(ref DataType newData)
    {
        return Emplace(ref newData);
    }

    /// <summary>
    /// Adds an existing variable to the front of the linked list
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> EmplaceFront(ref LinkedListNode<DataType> newNode)
    {
        return Emplace(ref newNode);
    }

    /// <summary>
    /// Adds an existing variable to the end of the linked list
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> EmplaceBack(ref DataType newData)
    {
        nodeCount++;

        if (head == null)
        {
            head = new LinkedListNode<DataType>(newData);

            head.next = head;

            head.previous = head;

            return this;
        }

        LinkedListNode<DataType> node = head.previous;

        head.previous = new LinkedListNode<DataType>(newData);

        head.previous.next = head;

        head.previous.previous = node;

        node.next = head.previous;

        return this;
    }

    /// <summary>
    /// Adds an existing variable to the end of the linked list
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> EmplaceBack(ref LinkedListNode<DataType> newNode)
    {
        nodeCount++;

        if (head == null)
        {
            head = newNode;

            head.next = head;

            head.previous = head;

            return this;
        }

        LinkedListNode<DataType> node = head.previous;

        head.previous = newNode;

        head.previous.next = head;

        head.previous.previous = node;

        node.next = head.previous;

        return this;
    }

    /// <summary>
    /// Returns a copy of the linked list's data
    /// </summary>
    /// <returns></returns>
    public LinkedList<DataType> Copy()
    {
        LinkedList<DataType> newLinkedList = new LinkedList<DataType>(this);

        return newLinkedList;
    }

    /// <summary>
    /// Returns the first index of the given data in the linked list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int Find(DataType foundData)
    {
        LinkedListNode<DataType> current = head;

        // Loop through the linked list for the matching node
        for (int i = 0; i < nodeCount; i++)
        {
            if (current.data.Equals(foundData))
            {
                return i;
            }

            current = current.next;
        }

        return -1;
    }

    /// <summary>
    /// Returns the first index of the given data in the linked list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundNode"></param>
    /// <returns></returns>
    public int Find(LinkedListNode<DataType> foundNode)
    {
        LinkedListNode<DataType> current = head;

        // Loop through the linked list for the matching node
        for (int i = 0; i < nodeCount; i++)
        {
            if (current.Equals(foundNode))
            {
                return i;
            }

            current = current.next;
        }

        return -1;
    }

    /// <summary>
    /// Returns the first index of the given data in the linked list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int IndexOf(DataType foundData)
    {
        return Find(foundData);
    }

    /// <summary>
    /// Returns the first index of the given data in the linked list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundNode"></param>
    /// <returns></returns>
    public int IndexOf(LinkedListNode<DataType> foundNode)
    {
        return Find(foundNode);
    }

    /// <summary>
    /// Returns the last index of the given data in the linked list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int FindLast(DataType foundData)
    {
        LinkedListNode<DataType> current = head.previous;

        // Loop through the linked list for the matching node
        for (int i = nodeCount - 1; i >= 0; i--)
        {
            if (current.data.Equals(foundData))
            {
                return i;
            }

            current = current.previous;
        }

        return -1;
    }

    /// <summary>
    /// Returns the last index of the given data in the linked list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundNode"></param>
    /// <returns></returns>
    public int FindLast(LinkedListNode<DataType> foundNode)
    {
        LinkedListNode<DataType> current = head.previous;

        // Loop through the linked list for the matching node
        for (int i = nodeCount - 1; i >= 0; i--)
        {
            if (current.Equals(foundNode))
            {
                return i;
            }

            current = current.previous;
        }

        return -1;
    }

    /// <summary>
    /// Returns the last index of the given data in the linked list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int LastIndexOf(DataType foundData)
    {
        return FindLast(foundData);
    }

    /// <summary>
    /// Returns the last index of the given data in the linked list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundNode"></param>
    /// <returns></returns>
    public int LastIndexOf(LinkedListNode<DataType> foundNode)
    {
        return FindLast(foundNode);
    }

    /// <summary>
    /// Returns the total number of instances of the given data in the linked list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundData"></param>
    /// <returns></returns>
    public int Total(DataType foundData)
    {
        // Store the current count
        int count = 0;

        LinkedListNode<DataType> current = head;

        // Loop through the linked list for matching nodes
        for (int i = 0; i < nodeCount; i++)
        {
            if (current.data.Equals(foundData))
            {
                count++;
            }

            current = current.next;
        }

        return count;
    }

    /// <summary>
    /// Returns the total number of instances of the given data in the linked list, returns -1 if nothing matched
    /// </summary>
    /// <param name="foundNode"></param>
    /// <returns></returns>
    public int Total(LinkedListNode<DataType> foundNode)
    {
        // Store the current count
        int count = 0;

        LinkedListNode<DataType> current = head;

        // Loop through the linked list for matching nodes
        for (int i = 0; i < nodeCount; i++)
        {
            if (current.data.Equals(foundNode.data))
            {
                count++;
            }

            current = current.next;
        }

        return count;
    }

    /// <summary>
    /// Returns whether the linked list contains at least one of the nodes 
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool Contains(DataType containedData)
    {
        return Find(containedData) != -1;
    }

    /// <summary>
    /// Returns whether the linked list contains at least one of the nodes 
    /// </summary>
    /// <param name="containedNode"></param>
    /// <returns></returns>
    public bool Contains(LinkedListNode<DataType> containedNode)
    {
        return Find(containedNode) != -1;
    }

    /// <summary>
    /// Returns whether the linked list contains at least one of the nodes 
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool Exists(DataType containedData)
    {
        return Contains(containedData);
    }

    /// <summary>
    /// Returns whether the linked list contains at least one of the nodes 
    /// </summary>
    /// <param name="containedNode"></param>
    /// <returns></returns>
    public bool Exists(LinkedListNode<DataType> containedNode)
    {
        return Contains(containedNode);
    }

    /// <summary>
    /// Removes the first of a given node in the linked list
    /// </summary>
    /// <param name="removedData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Remove(DataType removedData)
    {
        return Erase(Find(removedData));
    }

    /// <summary>
    /// Removes the first of a given node in the linked list
    /// </summary>
    /// <param name="removedNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Remove(LinkedListNode<DataType> removedNode)
    {
        return Erase(removedNode);
    }

    /// <summary>
    /// Removes the last of a given node in the linked list
    /// </summary>
    /// <param name="removedData"></param>
    /// <returns></returns>
    public LinkedList<DataType> RemoveLast(DataType removedData)
    {
        return Erase(FindLast(removedData));
    }

    /// <summary>
    /// Removes the last of a given node in the linked list
    /// </summary>
    /// <param name="removedNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> RemoveLast(LinkedListNode<DataType> removedNode)
    {
        return Erase(FindLast(removedNode));
    }

    /// <summary>
    /// Removes all of the given node in the linked list
    /// </summary>
    /// <param name="removedData"></param>
    /// <returns></returns>
    public LinkedList<DataType> RemoveAll(DataType removedData)
    {
        // Get the total number of nodes
        int amount = Total(removedData);

        // Remove those nodes
        for (int i = 0; i < amount; i++)
        {
            Remove(removedData);
        }

        return this;
    }

    /// <summary>
    /// Removes all of the given node in the linked list
    /// </summary>
    /// <param name="removedNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> RemoveAll(LinkedListNode<DataType> removedNode)
    {
        // Get the total number of nodes
        int amount = Total(removedNode);

        // Remove those nodes
        for (int i = 0; i < amount; i++)
        {
            Remove(removedNode);
        }

        return this;
    }

    /// <summary>
    /// Replaces the data at the given index with the given data
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Set(int index, DataType newData)
    {
        // Check for out of bounds
        if (index < 0 || index >= nodeCount)
        {
            return this;
        }

        // Replace the data at the index
        this[index].data = newData;

        return this;
    }

    /// <summary>
    /// Replaces the data at the given index with the given data
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Set(int index, LinkedListNode<DataType> newNode)
    {
        // Check for out of bounds
        if (index < 0 || index >= nodeCount)
        {
            return this;
        }

        // Replace the data at the index
        this[index].data = newNode.data;

        return this;
    }

    /// <summary>
    /// Replaces the data at the given index with the given data
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Overwrite(int index, DataType newData)
    {
        return Set(index, newData);
    }

    /// <summary>
    /// Replaces the data at the given index with the given data
    /// </summary>
    /// <param name="index"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Overwrite(int index, LinkedListNode<DataType> newNode)
    {
        return Set(index, newNode);
    }

    /// <summary>
    /// Replaces the first of the found data with the given data
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> Replace(DataType replacedData, DataType newData)
    {
        // Find the index of the found data
        int index = Find(replacedData);

        // Check if the data was not found
        if (index == -1)
        {
            return this;
        }

        // Replace the data at the index
        this[index].data = newData;

        return this;
    }

    /// <summary>
    /// Replaces the first of the found data with the given data
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> Replace(DataType replacedData, LinkedListNode<DataType> newNode)
    {
        // Find the index of the found data
        int index = Find(replacedData);

        // Check if the data was not found
        if (index == -1)
        {
            return this;
        }

        // Replace the data at the index
        this[index].data = newNode.data;

        return this;
    }

    /// <summary>
    /// Replaces the last of the found data with the given data
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> ReplaceLast(DataType replacedData, DataType newData)
    {
        // Find the index of the found data
        int index = FindLast(replacedData);

        // Check if the data was not found
        if (index == -1)
        {
            return this;
        }

        // Replace the data at the index
        this[index].data = newData;

        return this;
    }

    /// <summary>
    /// Replaces the last of the found data with the given data
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> ReplaceLast(DataType replacedData, LinkedListNode<DataType> newNode)
    {
        // Find the index of the found data
        int index = FindLast(replacedData);

        // Check if the data was not found
        if (index == -1)
        {
            return this;
        }

        // Replace the data at the index
        this[index].data = newNode.data;

        return this;
    }

    /// <summary>
    /// Replaces all of the found data with the given data
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public LinkedList<DataType> ReplaceAll(DataType replacedData, DataType newData)
    {
        // Get the total number of nodes
        int amount = Total(replacedData);

        // Replace those nodes
        for (int i = 0; i < amount; i++)
        {
            Replace(replacedData, newData);
        }

        return this;
    }

    /// <summary>
    /// Replaces all of the found data with the given data
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public LinkedList<DataType> ReplaceAll(DataType replacedData, LinkedListNode<DataType> newNode)
    {
        // Get the total number of nodes
        int amount = Total(replacedData);

        // Replace those nodes
        for (int i = 0; i < amount; i++)
        {
            Replace(replacedData, newNode.data);
        }

        return this;
    }

    /// <summary>
    /// Reverse the linked list nodes
    /// </summary>
    /// <returns></returns>
    public LinkedList<DataType> Reverse()
    {
        // Check length
        if (nodeCount <= 1)
        {
            return this;
        }

        // Loop through each node and swap it with the node across the end
        for (int i = 0; i < nodeCount / 2; i++)
        {
            Swap(i, nodeCount - i - 1);
        }

        return this;
    }

    /// <summary>
    /// Shifts the linked list nodes right
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
    /// Shifts the linked list nodes right
    /// </summary>
    /// <param name="numberOfShifts"></param>
    /// <returns></returns>
    public LinkedList<DataType> Shift(int numberOfShifts)
    {
        return ShiftRight(numberOfShifts);
    }

    /// <summary>
    /// Shifts the linked list nodes left
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

        // Place the linked list nodes in the sorted order
        for (int i = 0; i < nodeCount - 1; i++)
        {
            for (int j = 0; j < nodeCount - i - 1; j++)
            {
                if (sortOrder[j] > sortOrder[j + 1])
                {
                    // Swap the two linked list nodes
                    Swap(j, j + 1);

                    // Swap the two sorting nodes
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
        // Check length
        if (nodeCount <= 1)
        {
            return this;
        }

        // Place the linked list nodes in the sorted order
        for (int i = 0; i < nodeCount - 1; i++)
        {
            for (int j = 0; j < nodeCount - i - 1; j++)
            {
                if (sortOrder[j] > sortOrder[j + 1])
                {
                    // Swap the two linked list nodes
                    Swap(j, j + 1);

                    // Swap the two sorting nodes
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
    public LinkedList<DataType> Sort(LinkedList<SortType> sortOrder)
    {
        SortType[] newSortOrder = sortOrder.ToArray();

        Sort(newSortOrder);

        return this;
    }

    /// <summary>
    /// Prints the nodes of the linked list
    /// </summary>
    public void Print()
    {
        for (int i = 0; i < nodeCount; i++)
        {
            Console.WriteLine(i + ". " + this[i].data);
        }
    }

    /// <summary>
    /// Converts the nodes of the linked list into a string
    /// </summary>
    /// <returns></returns>
    public string ToString()
    {
        string log = "";

        for (int i = 0; i < nodeCount; i++)
        {
            log += (i + ". " + this[i].data + "\n");
        }

        return log;
    }


    // LINKED LIST CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public LinkedList()
    {
        head = null;

        nodeCount = 0;
    }

    /// <summary>
    /// Data constructor
    /// </summary>
    /// <param name="data"></param>
    public LinkedList(DataType data)
    {
        head = new LinkedListNode<DataType>(data);

        head.next = head;

        head.previous = head;

        nodeCount = 1;
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="node"></param>
    public LinkedList(LinkedListNode<DataType> node)
    {
        head = new LinkedListNode<DataType>(node.data);

        head.next = head;

        head.previous = head;

        nodeCount = 1;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="node"></param>
    public LinkedList(LinkedList<DataType> list)
    {
        Assign(list);
    }


    // ENUMERATOR FUNCTION

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
/// Stores data and connections to the previous and next nodes in a doubly linked list.
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

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="node"></param>
    public LinkedListNode(LinkedListNode<DataType> node)
    {
        data = node.data;

        previous = node.previous;

        next = node.next;
    }
}
