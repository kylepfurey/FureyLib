
// Binary Search Tree Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/set/set/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.sortedset-1?view=net-8.0,

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

/// <summary>
/// Class used to store a sorted binary search tree for fast retrieval of nodes with unique data.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class BinaryTree<DataType> : IEnumerable, IEnumerable<DataType> where DataType : IComparable
{
    // VARIABLES

    /// <summary>
    /// The root (starting) node of the binary tree
    /// </summary>
    private BinaryTreeNode<DataType> root = null;

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
    public BinaryTreeNode<DataType> Root
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
    private void FillArrayRecursively(ref int index, ref DataType[] currentArray, ref BinaryTreeNode<DataType> currentNode)
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
    /// Returns a sorted array of the current binary tree
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
    private void AddListRecursively(ref List<DataType> currentList, ref BinaryTreeNode<DataType> currentNode)
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
    /// Returns a sorted list of the current binary tree
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
        root = new BinaryTreeNode<DataType>(data);

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
            if (!array1[i].Equals(array2[i]))
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
    public BinaryTreeNode<DataType> Begin()
    {
        BinaryTreeNode<DataType> node = root;

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
    public BinaryTreeNode<DataType> Middle()
    {
        return root;
    }

    /// <summary>
    /// Returns the rightmost node in the binary tree
    /// </summary>
    /// <returns></returns>
    public BinaryTreeNode<DataType> End()
    {
        BinaryTreeNode<DataType> node = root;

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
    public BinaryTreeNode<DataType> Add(DataType data)
    {
        BinaryTreeNode<DataType> newNode = new BinaryTreeNode<DataType>(data);

        Add(newNode);

        return newNode;
    }

    /// <summary>
    /// Inserts a new node of the given data into the binary tree 
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public BinaryTree<DataType> Add(BinaryTreeNode<DataType> newNode)
    {
        if (nodeCount == 0)
        {
            root = newNode;

            nodeCount = 1;

            return this;
        }

        BinaryTreeNode<DataType> node = root;

        while (!node.IsLeaf())
        {
            if (node.data.Equals(newNode.data))
            {
                return this;
            }

            if (node.data.CompareTo(newNode.data) > 0)
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

        if (node.data.Equals(newNode.data))
        {
            return this;
        }

        if (node.data.CompareTo(newNode.data) > 0)
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
    public BinaryTreeNode<DataType> Remove(DataType data)
    {
        BinaryTreeNode<DataType> node = Find(data);

        Remove(node);

        return node;
    }

    /// <summary>
    /// Removes a node from the binary tree
    /// </summary>
    /// <param name="removedNode"></param>
    /// <returns></returns>
    public BinaryTree<DataType> Remove(BinaryTreeNode<DataType> removedNode)
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
            BinaryTreeNode<DataType> node = removedNode.left;

            while (node.right != null)
            {
                node = node.right;
            }

            if (removedNode != root)
            {
                if (removedNode.parent.left == removedNode)
                {
                    removedNode.parent.left = node;
                }
                else
                {
                    removedNode.parent.right = node;
                }
            }
            else
            {
                root = node;
            }

            if (removedNode.left != node)
            {
                node.parent.right = node.left;

                if (node.left != null)
                {
                    node.left.parent = node.parent;
                }

                node.left = removedNode.left;

                removedNode.left.parent = node;
            }

            node.right = removedNode.right;

            removedNode.right.parent = node;

            node.parent = removedNode.parent;
        }

        return this;
    }

    /// <summary>
    /// Remove and return the leftmost node from its connected nodes in the binary tree
    /// </summary>
    /// <returns></returns>
    public BinaryTreeNode<DataType> RemoveLeft()
    {
        return Remove(Left());
    }

    /// <summary>
    /// Remove and return the root node from its connected nodes in the binary tree
    /// </summary>
    /// <returns></returns>
    public BinaryTreeNode<DataType> RemoveRoot()
    {
        return Remove(root.data);
    }

    /// <summary>
    /// Remove and return the rightmost node from its connected nodes in the binary tree
    /// </summary>
    /// <returns></returns>
    public BinaryTreeNode<DataType> RemoveRight()
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
        BinaryTreeNode<DataType> data = root;

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

    /// <summary>
    /// Inserts an existing node of the given data into the binary tree 
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public BinaryTreeNode<DataType> Emplace(ref DataType data)
    {
        BinaryTreeNode<DataType> newNode = new BinaryTreeNode<DataType>(data);

        Add(newNode);

        return newNode;
    }


    // ELEMENT OPERATIONS

    /// <summary>
    /// Finds and an existing node and if successful, removes it and inserts a new node
    /// </summary>
    /// <param name="replacedData"></param>
    /// <param name="newData"></param>
    /// <returns></returns>
    public BinaryTreeNode<DataType> Replace(DataType replacedData, DataType newData)
    {
        BinaryTreeNode<DataType> node = Find(replacedData);

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
    public BinaryTree<DataType> Replace(BinaryTreeNode<DataType> replacedNode, BinaryTreeNode<DataType> newNode)
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
    public BinaryTreeNode<DataType> Find(DataType data)
    {
        if (nodeCount == 0)
        {
            return null;
        }

        BinaryTreeNode<DataType> node = root;

        while (node != null)
        {
            if (node.data.Equals(data))
            {
                return node;
            }
            else
            {
                int comparison = node.data.CompareTo(data);

                if (comparison > 0)
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
    public bool Contains(BinaryTreeNode<DataType> newNode)
    {
        if (nodeCount == 0 || newNode == null)
        {
            return false;
        }

        BinaryTreeNode<DataType> node = root;

        while (node != null)
        {
            if (node == newNode)
            {
                return true;
            }
            else
            {
                int comparison = node.data.CompareTo(newNode.data);

                if (comparison > 0)
                {
                    node = node.left;
                }
                else
                {
                    node = node.right;
                }
            }
        }

        return false;
    }

    /// <summary>
    /// Returns a new tree whose root is of the given node
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public BinaryTree<DataType> Subset(BinaryTreeNode<DataType> node)
    {
        return new BinaryTree<DataType>(node);
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
public class BinaryTreeNode<DataType> where DataType : IComparable
{
    // VARIABLES

    /// <summary>
    /// This node's data
    /// </summary>
    public DataType data = default(DataType);

    /// <summary>
    /// A link to the parent (above) node
    /// </summary>
    public BinaryTreeNode<DataType> parent = null;

    /// <summary>
    /// A link to the left (lesser) node
    /// </summary>
    public BinaryTreeNode<DataType> left = null;

    /// <summary>
    /// A link to the right (greater) node
    /// </summary>
    public BinaryTreeNode<DataType> right = null;


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
    public BinaryTreeNode<DataType> Parent
    {
        get
        {
            return parent;
        }
    }

    /// <summary>
    /// Readonly left node variable
    /// </summary>
    public BinaryTreeNode<DataType> Left
    {
        get
        {
            return left;
        }
    }

    /// <summary>
    /// Readonly right node variable
    /// </summary>
    public BinaryTreeNode<DataType> Right
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
    public BinaryTreeNode(DataType data = default(DataType), BinaryTreeNode<DataType> left = null, BinaryTreeNode<DataType> right = null, BinaryTreeNode<DataType> parent = null)
    {
        this.data = data;

        this.left = left;

        this.right = right;

        this.parent = parent;
    }


    // FUNCTIONS

    /// <summary>
    /// Returns the leftmost node of this node
    /// </summary>
    /// <returns></returns>
    public BinaryTreeNode<DataType> LowerBound()
    {
        BinaryTreeNode<DataType> node = this;

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
    public BinaryTreeNode<DataType> Root()
    {
        BinaryTreeNode<DataType> node = this;

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
    public BinaryTreeNode<DataType> UpperBound()
    {
        BinaryTreeNode<DataType> node = this;

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
}
