
// Binary Search Tree Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/set/set/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.hashset-1?view=net-8.0

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

/// <summary>
/// Class used to store a binary search tree for fast storage and retrieval of nodes with unique data.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class BinaryTree<DataType> : IEnumerable, IEnumerable<DataType> // where DataType : IComparable, IComparable<DataType>
{
    // VARIABLES

    /// <summary>
    /// The root (starting) node of the binary tree
    /// </summary>
    private BinaryNode<DataType> root = null;

    /// <summary>
    /// The current number of nodes in the binary tree
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
    /// Readonly root node variable
    /// </summary>
    public BinaryNode<DataType> Root
    {
        get
        {
            return root;
        }
    }

    /// <summary>
    /// Readonly minimum node variable
    /// </summary>
    public DataType Min
    {
        get
        {
            return Left();
        }
    }

    /// <summary>
    /// Readonly maximum node variable
    /// </summary>
    public DataType Max
    {
        get
        {
            return Right();
        }
    }


    // TO ARRAY AND LIST

    /// <summary>
    /// Fills an array with this node and all of its children recursively in an array of nodes
    /// </summary>
    /// <param name="index"></param>
    /// <param name="currentArray"></param>
    /// <param name="currentNode"></param>
    /// <returns></returns>
    private static void FillArrayRecursively(ref int index, ref DataType[] currentArray, ref BinaryNode<DataType> currentNode)
    {
        if (currentNode.left != null)
        {
            FillArrayRecursively(ref index, ref currentArray, ref currentNode.left);
        }

        currentArray[index] = currentNode.data;

        index++;

        if (currentNode.right != null)
        {
            FillArrayRecursively(ref index, ref currentArray, ref currentNode.right);
        }
    }

    /// <summary>
    /// Returns a array of the current binary tree
    /// </summary>
    /// <returns></returns>
    public DataType[] ToArray()
    {
        if (nodeCount == 0)
        {
            return new DataType[0];
        }

        DataType[] newArray = new DataType[nodeCount];

        int index = 0;

        FillArrayRecursively(ref index, ref newArray, ref root);

        return newArray;
    }

    /// <summary>
    /// Adds this node and all of its children recursively to a list of nodes
    /// </summary>
    /// <param name="currentList"></param>
    /// <param name="currentNode"></param>
    /// <returns></returns>
    private static void AddListRecursively(ref List<DataType> currentList, ref BinaryNode<DataType> currentNode)
    {
        if (currentNode.left != null)
        {
            AddListRecursively(ref currentList, ref currentNode.left);
        }

        currentList.Add(currentNode.data);

        if (currentNode.right != null)
        {
            AddListRecursively(ref currentList, ref currentNode.right);
        }
    }

    /// <summary>
    /// Returns a list of the current binary tree
    /// </summary>
    /// <returns></returns>
    public List<DataType> ToList()
    {
        if (nodeCount == 0)
        {
            return null;
        }

        List<DataType> newList = new List<DataType>(nodeCount);

        AddListRecursively(ref newList, ref root);

        return newList;
    }


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public BinaryTree()
    {
        root = null;

        nodeCount = 0;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copiedTree"></param>
    public BinaryTree(BinaryTree<DataType> copiedTree)
    {
        if (copiedTree.root == null)
        {
            root = null;

            nodeCount = 0;

            return;
        }

        DataType[] array = copiedTree.ToArray();

        for (int i = 0; i < array.Length; i++)
        {
            Add(array[i]);
        }
    }

    /// <summary>
    /// Data constructor
    /// </summary>
    /// <param name="data"></param>
    public BinaryTree(DataType data)
    {
        root = new BinaryNode<DataType>(data);

        nodeCount = 1;
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="array"></param>
    public BinaryTree(params DataType[] array)
    {
        if (array.Length == 0)
        {
            root = null;

            nodeCount = 0;

            return;
        }

        for (int i = 0; i < array.Length; i++)
        {
            Add(array[i]);
        }
    }

    /// <summary>
    /// Enumerable constructor
    /// </summary>
    /// <param name="list"></param>
    public BinaryTree(IEnumerable<DataType> list)
    {
        if (list.Count() == 0)
        {
            root = null;

            nodeCount = 0;

            return;
        }

        foreach (DataType data in list)
        {
            Add(data);
        }
    }


    // EQUALITY

    /// <summary>
    /// Check if another binary tree is equal to the binary tree
    /// </summary>
    /// <param name="comparedTree"></param>
    /// <returns></returns>
    public bool Equals(BinaryTree<DataType> comparedTree)
    {
        if (nodeCount == 0 || comparedTree.nodeCount == 0)
        {
            return false;
        }

        if (nodeCount != comparedTree.nodeCount)
        {
            return false;
        }

        DataType[] array1 = ToArray();

        DataType[] array2 = comparedTree.ToArray();

        for (int i = 0; i < nodeCount; i++)
        {
            if (!GenericEquals(array1[i], array2[i]))
            {
                return false;
            }
        }

        return true;
    }

    /// <summary>
    /// Check if another binary tree is equal to the binary tree
    /// </summary>
    /// <param name="tree"></param>
    /// <param name="comparedTree"></param>
    /// <returns></returns>
    public static bool operator ==(BinaryTree<DataType> tree, BinaryTree<DataType> comparedTree)
    {
        return tree.Equals(comparedTree);
    }

    /// <summary>
    /// Check if another binary tree is not equal to the binary tree
    /// </summary>
    /// <param name="tree"></param>
    /// <param name="comparedTree"></param>
    /// <returns></returns>
    public static bool operator !=(BinaryTree<DataType> tree, BinaryTree<DataType> comparedTree)
    {
        return !tree.Equals(comparedTree);
    }


    // ITERATORS

    /// <summary>
    /// Returns the leftmost node in the binary tree
    /// </summary>
    /// <returns></returns>
    public BinaryNode<DataType> Begin()
    {
        BinaryNode<DataType> node = root;

        while (node.left != null)
        {
            node = node.left;
        }

        return node;
    }

    /// <summary>
    /// Returns the root node in the binary tree
    /// </summary>
    /// <returns></returns>
    public BinaryNode<DataType> Middle()
    {
        return root;
    }

    /// <summary>
    /// Returns the rightmost node in the binary tree
    /// </summary>
    /// <returns></returns>
    public BinaryNode<DataType> End()
    {
        BinaryNode<DataType> node = root;

        while (node.right != null)
        {
            node = node.right;
        }

        return node;
    }


    // CAPACITY

    /// <summary>
    /// Returns whether the binary tree is empty
    /// </summary>
    /// <returns></returns>
    public bool Empty()
    {
        return nodeCount == 0;
    }

    /// <summary>
    /// Returns the current number of nodes of the binary tree
    /// </summary>
    /// <returns></returns>
    public int Size()
    {
        return nodeCount;
    }


    // ELEMENT ACCESS

    /// <summary>
    /// Returns the leftmost node's data in the binary tree
    /// </summary>
    /// <returns></returns>
    public DataType Left()
    {
        return Begin().data;
    }

    /// <summary>
    /// Returns the root node's data in the binary tree
    /// </summary>
    /// <returns></returns>
    public DataType Top()
    {
        return root.data;
    }

    /// <summary>
    /// Returns the rightmost node's data in the binary tree
    /// </summary>
    /// <returns></returns>
    public DataType Right()
    {
        return End().data;
    }

    /// <summary>
    /// Attempts to retrieve the given matching value from this binary tree
    /// </summary>
    /// <param name="value"></param>
    /// <param name="result"></param>
    /// <returns></returns>
    public bool TryGetValue(DataType value, out DataType result)
    {
        if (!Contains(value))
        {
            result = default(DataType);

            return false;
        }

        result = Find(value).data;

        return true;
    }


    // MODIFIERS

    /// <summary>
    /// Assigns the binary tree's nodes from another binary tree's nodes
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public BinaryTree<DataType> Assign(BinaryTree<DataType> newData)
    {
        if (newData.root == null)
        {
            root = null;

            nodeCount = 0;

            return this;
        }

        Clear();

        DataType[] array = newData.ToArray();

        for (int i = 0; i < array.Length; i++)
        {
            Add(array[i]);
        }

        return this;
    }

    /// <summary>
    /// Inserts a new node of the given data into the binary tree 
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public BinaryNode<DataType> Add(DataType data)
    {
        BinaryNode<DataType> newNode = new BinaryNode<DataType>(data);

        Add(newNode);

        return newNode;
    }

    /// <summary>
    /// Inserts a new node of the given data into the binary tree 
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public BinaryTree<DataType> Add(BinaryNode<DataType> newNode)
    {
        if (nodeCount == 0)
        {
            root = newNode;

            nodeCount = 1;

            return this;
        }

        BinaryNode<DataType> node = root;

        while (!node.IsLeaf())
        {
            if (GenericEquals(node.data, newNode.data))
            {
                node.data = newNode.data;

                return this;
            }

            if (GenericGreaterThan(node.data, newNode.data))
            {
                if (node.left == null)
                {
                    node.left = newNode;

                    newNode.parent = node;

                    nodeCount++;

                    return this;
                }
                else
                {
                    node = node.left;
                }
            }
            else
            {
                if (node.right == null)
                {
                    node.right = newNode;

                    newNode.parent = node;

                    nodeCount++;

                    return this;
                }
                else
                {
                    node = node.right;
                }
            }
        }

        if (GenericEquals(node.data, newNode.data))
        {
            node.data = newNode.data;

            return this;
        }

        if (GenericGreaterThan(node.data, newNode.data))
        {
            node.left = newNode;
        }
        else
        {
            node.right = newNode;
        }

        newNode.parent = node;

        nodeCount++;

        return this;
    }

    /// <summary>
    /// Remove and return a node of the given data if it is present
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public BinaryNode<DataType> Remove(DataType data)
    {
        BinaryNode<DataType> node = Find(data);

        Remove(node);

        return node;
    }

    /// <summary>
    /// Removes a node from the binary tree
    /// </summary>
    /// <param name="removedNode"></param>
    /// <returns></returns>
    public BinaryTree<DataType> Remove(BinaryNode<DataType> removedNode)
    {
        if (!Contains(removedNode))
        {
            return this;
        }

        nodeCount--;

        if (nodeCount <= 0)
        {
            root = null;

            nodeCount = 0;

            return this;
        }

        if (removedNode.IsLeaf())
        {
            if (removedNode.parent.left == removedNode)
            {
                removedNode.parent.left = null;
            }
            else
            {
                removedNode.parent.right = null;
            }
        }
        else if (removedNode.right == null)
        {
            removedNode.left.parent = removedNode.parent;

            if (removedNode != root)
            {
                if (removedNode.parent.left == removedNode)
                {
                    removedNode.parent.left = removedNode.left;
                }
                else
                {
                    removedNode.parent.right = removedNode.left;
                }
            }
            else
            {
                root = removedNode.left;
            }
        }
        else if (removedNode.left == null)
        {
            removedNode.right.parent = removedNode.parent;

            if (removedNode != root)
            {
                if (removedNode.parent.left == removedNode)
                {
                    removedNode.parent.left = removedNode.right;
                }
                else
                {
                    removedNode.parent.right = removedNode.right;
                }
            }
            else
            {
                root = removedNode.right;
            }
        }
        else
        {
            BinaryNode<DataType> node = removedNode.right;

            while (node.left != null)
            {
                node = node.left;
            }

            if (removedNode != root)
            {
                if (removedNode.parent.right == removedNode)
                {
                    removedNode.parent.right = node;
                }
                else
                {
                    removedNode.parent.left = node;
                }
            }
            else
            {
                root = node;
            }

            if (removedNode.right != node)
            {
                node.parent.left = node.right;

                if (node.right != null)
                {
                    node.right.parent = node.parent;
                }

                node.right = removedNode.right;

                removedNode.right.parent = node;
            }

            node.left = removedNode.left;

            removedNode.left.parent = node;

            node.parent = removedNode.parent;
        }

        return this;
    }

    /// <summary>
    /// Remove and return the leftmost node from its connected nodes in the binary tree
    /// </summary>
    /// <returns></returns>
    public BinaryNode<DataType> RemoveLeft()
    {
        return Remove(Left());
    }

    /// <summary>
    /// Remove and return the root node from its connected nodes in the binary tree
    /// </summary>
    /// <returns></returns>
    public BinaryNode<DataType> RemoveRoot()
    {
        return Remove(root.data);
    }

    /// <summary>
    /// Remove and return the rightmost node from its connected nodes in the binary tree
    /// </summary>
    /// <returns></returns>
    public BinaryNode<DataType> RemoveRight()
    {
        return Remove(Right());
    }

    /// <summary>
    /// Swaps the binary tree's nodes with another binary tree's nodes
    /// </summary>
    /// <param name="swappedData"></param>
    /// <returns></returns>
    public BinaryTree<DataType> Swap(BinaryTree<DataType> swappedData)
    {
        BinaryNode<DataType> data = root;

        int count = nodeCount;

        root = swappedData.root;

        nodeCount = swappedData.nodeCount;

        swappedData.root = data;

        swappedData.nodeCount = count;

        return this;
    }

    /// <summary>
    /// Clears the binary tree's data
    /// </summary>
    /// <returns></returns>
    public int Clear()
    {
        int total = nodeCount;

        root = null;

        nodeCount = 0;

        return total;
    }


    // ELEMENT OPERATIONS

    /// <summary>
    /// Finds and an existing node and if successful, removes it and inserts a new node
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public BinaryNode<DataType> Replace(DataType replacedData, DataType newData)
    {
        BinaryNode<DataType> node = Find(replacedData);

        if (node == null)
        {
            return null;
        }

        Remove(node);

        Add(newData);

        return node;
    }

    /// <summary>
    /// Removes the replaced node and inserts the new one
    /// </summary>
    /// <param name="replacedNode"></param>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public BinaryTree<DataType> Replace(BinaryNode<DataType> replacedNode, BinaryNode<DataType> newNode)
    {
        Remove(replacedNode);

        Add(newNode);

        return this;
    }


    // OPERATIONS

    /// <summary>
    /// Finds the matching node of the given data if it is present
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public BinaryNode<DataType> Find(DataType data)
    {
        if (nodeCount == 0)
        {
            return null;
        }

        BinaryNode<DataType> node = root;

        while (node != null)
        {
            if (GenericEquals(node.data, data))
            {
                return node;
            }
            else
            {
                if (GenericGreaterThan(node.data, data))
                {
                    node = node.left;
                }
                else
                {
                    node = node.right;
                }
            }
        }

        return null;
    }

    /// <summary>
    /// Returns whether the binary tree contains the given data
    /// </summary>
    /// <param name="containedData"></param>
    /// <returns></returns>
    public bool Contains(DataType containedData)
    {
        return Find(containedData) != null;
    }

    /// <summary>
    /// Returns whether the binary tree contains the given node
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public bool Contains(BinaryNode<DataType> newNode)
    {
        if (nodeCount == 0 || newNode == null)
        {
            return false;
        }

        return root == newNode.Root();
    }

    /// <summary>
    /// Inserts the given node and all of the its children recursively to the given tree
    /// </summary>
    /// <param name="currentTree"></param>
    /// <param name="currentNode"></param>
    private static void AddChildrenRecursively(ref BinaryTree<DataType> currentTree, ref BinaryNode<DataType> currentNode)
    {
        currentTree.Add(currentNode);

        if (currentNode.left != null)
        {
            AddChildrenRecursively(ref currentTree, ref currentNode.left);
        }

        if (currentNode.right != null)
        {
            AddChildrenRecursively(ref currentTree, ref currentNode.right);
        }
    }

    /// <summary>
    /// Returns a new tree whose root is of the given node
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public static BinaryTree<DataType> Subset(BinaryNode<DataType> node)
    {
        BinaryTree<DataType> tree = new BinaryTree<DataType>();

        AddChildrenRecursively(ref tree, ref node);

        return tree;
    }

    /// <summary>
    /// Merges the given binary tree into this binary tree
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public BinaryTree<DataType> Merge(BinaryTree<DataType> newData)
    {
        DataType[] array = newData.ToArray();

        for (int i = 0; i < array.Length; i++)
        {
            Add(array[i]);
        }

        newData.Clear();

        return this;
    }

    /// <summary>
    /// Returns a copy of the binary tree's data
    /// </summary>
    /// <returns></returns>
    public BinaryTree<DataType> Copy()
    {
        return new BinaryTree<DataType>(this);
    }


    // TO STRING

    /// <summary>
    /// Converts the nodes of the binary tree into a string
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


    // GENERIC FUNCTIONS

    /// <summary>
    /// Compares a generic type with null accounted for
    /// </summary>
    /// <returns></returns>
    private static bool GenericEquals(DataType left, DataType right)
    {
        if (left == null)
        {
            return right == null;
        }

        return left.Equals(right);
    }

    /// <summary>
    /// Compares a generic type with null accounted for
    /// </summary>
    /// <returns></returns>
    private static bool GenericGreaterThan(DataType left, DataType right)
    {
        if (left == null)
        {
            return false;
        }

        if (right == null)
        {
            return true;
        }

        // Uncomment for IComparable
        // return left.CompareTo(right) > 0;

        return left.GetHashCode() > right.GetHashCode();
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
}

/// <summary>
/// Class that stores unique data and connections to the left and right nodes in a binary search tree.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class BinaryNode<DataType> // where DataType : IComparable, IComparable<DataType>
{
    // VARIABLES

    /// <summary>
    /// This node's data
    /// </summary>
    public DataType data = default(DataType);

    /// <summary>
    /// A link to the parent (above) node
    /// </summary>
    public BinaryNode<DataType> parent = null;

    /// <summary>
    /// A link to the left (lesser) node
    /// </summary>
    public BinaryNode<DataType> left = null;

    /// <summary>
    /// A link to the right (greater) node
    /// </summary>
    public BinaryNode<DataType> right = null;


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
    /// Readonly parent node variable
    /// </summary>
    public BinaryNode<DataType> Parent
    {
        get
        {
            return parent;
        }
    }

    /// <summary>
    /// Readonly left node variable
    /// </summary>
    public BinaryNode<DataType> Left
    {
        get
        {
            return left;
        }
    }

    /// <summary>
    /// Readonly right node variable
    /// </summary>
    public BinaryNode<DataType> Right
    {
        get
        {
            return right;
        }
    }


    // CONSTRUCTOR

    /// <summary>
    /// Default constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="left"></param>
    /// <param name="right"></param>
    /// <param name="parent"></param>
    public BinaryNode(DataType data = default(DataType), BinaryNode<DataType> left = null, BinaryNode<DataType> right = null, BinaryNode<DataType> parent = null)
    {
        this.data = data;

        this.left = left;

        this.right = right;

        this.parent = parent;
    }


    // FUNCTIONS

    /// <summary>
    /// Searches for the given data by traversing this node's connected nodes and returns the node that matches (or null)
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public BinaryNode<DataType> BinarySearch(DataType data)
    {
        BinaryNode<DataType> current = this;

        while (current != null)
        {
            if (GenericEquals(current.data, data))
            {
                return current;
            }
            else
            {
                if (GenericGreaterThan(current.data, data))
                {
                    current = current.left;
                }
                else
                {
                    current = current.right;
                }
            }
        }

        return current;
    }

    /// <summary>
    /// Returns the leftmost node of this node
    /// </summary>
    /// <returns></returns>
    public BinaryNode<DataType> LowerBound()
    {
        BinaryNode<DataType> node = this;

        while (node.left != null)
        {
            node = node.left;
        }

        return node;
    }

    /// <summary>
    /// Returns the root node of this node
    /// </summary>
    /// <returns></returns>
    public BinaryNode<DataType> Root()
    {
        BinaryNode<DataType> node = this;

        while (node.parent != null)
        {
            node = node.parent;
        }

        return node;
    }

    /// <summary>
    /// Returns the rightmost node of this node
    /// </summary>
    /// <returns></returns>
    public BinaryNode<DataType> UpperBound()
    {
        BinaryNode<DataType> node = this;

        while (node.right != null)
        {
            node = node.right;
        }

        return node;
    }

    /// <summary>
    /// Returns whether this node has no children
    /// </summary>
    /// <returns></returns>
    public bool IsLeaf()
    {
        return left == null && right == null;
    }


    // GENERIC FUNCTIONS

    /// <summary>
    /// Compares a generic type with null accounted for
    /// </summary>
    /// <returns></returns>
    private static bool GenericEquals(DataType left, DataType right)
    {
        if (left == null)
        {
            return right == null;
        }

        return left.Equals(right);
    }

    /// <summary>
    /// Compares a generic type with null accounted for
    /// </summary>
    /// <returns></returns>
    private static bool GenericGreaterThan(DataType left, DataType right)
    {
        if (left == null)
        {
            return false;
        }

        if (right == null)
        {
            return true;
        }

        // Uncomment for IComparable
        // return left.CompareTo(right) > 0;

        return left.GetHashCode() > right.GetHashCode();
    }
}

/// <summary>
/// Class that stores unique elements for fast insertion, access, and removal.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class HashSet<DataType> : BinaryTree<DataType> /* where DataType : IComparable, IComparable<DataType> */ { }
