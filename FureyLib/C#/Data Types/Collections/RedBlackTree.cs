
// Red-Black Binary Search Tree Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/set/set/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.sortedset-1?view=net-8.0,
// https://www.geeksforgeeks.org/introduction-to-red-black-tree/

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

/// <summary>
/// Class used to store a sorted red-black binary search tree for fast retrieval of nodes with unique data.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class RedBlackTree<DataType> : IEnumerable, IEnumerable<DataType> // where DataType : IComparable, IComparable<DataType>
{
    // VARIABLES

    /// <summary>
    /// The root (starting) node of the binary tree
    /// </summary>
    private RedBlackNode<DataType> root = null;

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
    public RedBlackNode<DataType> Root
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
    private static void FillArrayRecursively(ref int index, ref DataType[] currentArray, ref RedBlackNode<DataType> currentNode)
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
    private static void AddListRecursively(ref List<DataType> currentList, ref RedBlackNode<DataType> currentNode)
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


    // REBALANCING TREE

    /// <summary>
    /// Rotates the given node left relative to its connected nodes
    /// </summary>
    /// <param name="node"></param>
    private void RotateLeft(RedBlackNode<DataType> node)
    {
        if (node == null || node.right == null)
        {
            return;
        }

        RedBlackNode<DataType> right = node.right;

        node.right = right.left;

        if (right.left != null)
        {
            right.left.parent = node;
        }

        right.parent = node.parent;

        if (node.parent == null)
        {
            root = right;
        }
        else if (node == node.parent.left)
        {
            node.parent.left = right;
        }
        else
        {
            node.parent.right = right;
        }

        right.left = node;

        node.parent = right;
    }

    /// <summary>
    /// Rotates the given node right relative to its connected nodes
    /// </summary>
    /// <param name="node"></param>
    private void RotateRight(RedBlackNode<DataType> node)
    {
        if (node == null || node.left == null)
        {
            return;
        }

        RedBlackNode<DataType> left = node.left;

        node.left = left.right;

        if (left.right != null)
        {
            left.right.parent = node;
        }

        left.parent = node.parent;

        if (node.parent == null)
        {
            root = left;
        }
        else if (node == node.parent.right)
        {
            node.parent.right = left;
        }
        else
        {
            node.parent.left = left;
        }

        left.right = node;

        node.parent = left;
    }

    /// <summary>
    /// Rebalances the tree's colors based on the given incoming node's relatives
    /// </summary>
    /// <param name="node"></param>
    private void RebalanceInsertion(RedBlackNode<DataType> node)
    {
        if (node.parent.color == RedBlackColor.Red)
        {
            RedBlackNode<DataType> uncle = null;

            bool parentIsRight = false;

            if (node.parent.parent.left == node.parent)
            {
                uncle = node.parent.parent.right;

                parentIsRight = false;
            }
            else
            {
                uncle = node.parent.parent.left;

                parentIsRight = true;
            }

            if (uncle != null && uncle.color == RedBlackColor.Red)
            {
                node.parent.color = RedBlackColor.Black;

                uncle.color = RedBlackColor.Black;

                node.parent.parent.color = RedBlackColor.Red;

                if (node.parent.parent != root)
                {
                    RebalanceInsertion(node.parent.parent);
                }
            }
            else
            {
                RedBlackNode<DataType> grandparent = node.parent.parent;

                RedBlackColor swapped = grandparent.color;

                if (!parentIsRight)
                {
                    // LEFT LEFT
                    if (node.parent.left == node)
                    {
                        grandparent.color = node.parent.color;

                        node.parent.color = swapped;

                        RotateRight(grandparent);
                    }
                    // LEFT RIGHT
                    else
                    {
                        grandparent.color = node.color;

                        node.color = swapped;

                        swapped = grandparent.color;

                        grandparent.color = node.parent.color;

                        node.parent.color = swapped;

                        RotateLeft(node.parent);

                        RotateRight(grandparent);
                    }
                }
                else
                {
                    // RIGHT RIGHT
                    if (node.parent.right == node)
                    {
                        grandparent.color = node.parent.color;

                        node.parent.color = swapped;

                        RotateLeft(grandparent);
                    }
                    // RIGHT LEFT
                    else
                    {
                        grandparent.color = node.color;

                        node.color = swapped;

                        swapped = grandparent.color;

                        grandparent.color = node.parent.color;

                        node.parent.color = swapped;

                        RotateRight(node.parent);

                        RotateLeft(grandparent);
                    }
                }
            }
        }

        root.color = RedBlackColor.Black;
    }

    /// <summary>
    /// Rebalances the tree's colors based on the given removed node's relatives
    /// </summary>
    /// <param name="node"></param>
    private void RebalanceRemoval(RedBlackNode<DataType> node, RedBlackColor removedColor)
    {
        if (node.color == RedBlackColor.Red || removedColor == RedBlackColor.Red)
        {
            node.color = RedBlackColor.Black;

            return;
        }

        while (node.parent != null && node.color == RedBlackColor.Black)
        {
            RedBlackNode<DataType> sibling = null;

            if (node == node.parent.left)
            {
                sibling = node.parent.right;

                if (sibling != null)
                {
                    if (sibling.color == RedBlackColor.Red)
                    {
                        sibling.color = RedBlackColor.Black;

                        node.parent.color = RedBlackColor.Red;

                        RotateLeft(node.parent);

                        sibling = node.parent.right;

                        if (sibling == null)
                        {
                            node = node.parent;

                            continue;
                        }
                    }

                    if ((sibling.left == null || sibling.left.color == RedBlackColor.Black) && (sibling.right == null || sibling.right.color == RedBlackColor.Black))
                    {
                        sibling.color = RedBlackColor.Red;

                        node = node.parent;
                    }
                    else
                    {
                        if (sibling.right == null || sibling.right.color == RedBlackColor.Black)
                        {
                            if (sibling.left != null)
                            {
                                sibling.left.color = RedBlackColor.Black;
                            }

                            sibling.color = RedBlackColor.Red;

                            RotateRight(sibling);

                            sibling = node.parent.right;
                        }

                        sibling.color = node.parent.color;

                        node.parent.color = RedBlackColor.Black;

                        if (sibling.right != null)
                        {
                            sibling.right.color = RedBlackColor.Black;
                        }

                        RotateLeft(node.parent);

                        break;
                    }
                }
                else
                {
                    node = node.parent;
                }
            }
            else
            {
                sibling = node.parent.left;

                if (sibling != null)
                {
                    if (sibling.color == RedBlackColor.Red)
                    {
                        sibling.color = RedBlackColor.Black;

                        node.parent.color = RedBlackColor.Red;

                        RotateRight(node.parent);

                        sibling = node.parent.left;

                        if (sibling == null)
                        {
                            node = node.parent;

                            continue;
                        }
                    }

                    if ((sibling.right == null || sibling.right.color == RedBlackColor.Black) && (sibling.left == null || sibling.left.color == RedBlackColor.Black))
                    {
                        sibling.color = RedBlackColor.Red;

                        node = node.parent;
                    }
                    else
                    {
                        if (sibling.left == null || sibling.left.color == RedBlackColor.Black)
                        {
                            if (sibling.right != null)
                            {
                                sibling.right.color = RedBlackColor.Black;
                            }

                            sibling.color = RedBlackColor.Red;

                            RotateLeft(sibling);

                            sibling = node.parent.left;
                        }

                        sibling.color = node.parent.color;

                        node.parent.color = RedBlackColor.Black;

                        if (sibling.left != null)
                        {
                            sibling.left.color = RedBlackColor.Black;
                        }

                        RotateRight(node.parent);

                        break;
                    }
                }
                else
                {
                    node = node.parent;
                }
            }
        }

        root.color = RedBlackColor.Black;
    }


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public RedBlackTree()
    {
        root = null;

        nodeCount = 0;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copiedTree"></param>
    public RedBlackTree(RedBlackTree<DataType> copiedTree)
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
    public RedBlackTree(DataType data)
    {
        root = new RedBlackNode<DataType>(data);

        nodeCount = 1;
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="array"></param>
    public RedBlackTree(params DataType[] array)
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
    public RedBlackTree(IEnumerable<DataType> list)
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
    public bool Equals(RedBlackTree<DataType> comparedTree)
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
    public static bool operator ==(RedBlackTree<DataType> tree, RedBlackTree<DataType> comparedTree)
    {
        return tree.Equals(comparedTree);
    }

    /// <summary>
    /// Check if another binary tree is not equal to the binary tree
    /// </summary>
    /// <param name="tree"></param>
    /// <param name="comparedTree"></param>
    /// <returns></returns>
    public static bool operator !=(RedBlackTree<DataType> tree, RedBlackTree<DataType> comparedTree)
    {
        return !tree.Equals(comparedTree);
    }


    // ITERATORS

    /// <summary>
    /// Returns the leftmost node in the binary tree
    /// </summary>
    /// <returns></returns>
    public RedBlackNode<DataType> Begin()
    {
        RedBlackNode<DataType> node = root;

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
    public RedBlackNode<DataType> Middle()
    {
        return root;
    }

    /// <summary>
    /// Returns the rightmost node in the binary tree
    /// </summary>
    /// <returns></returns>
    public RedBlackNode<DataType> End()
    {
        RedBlackNode<DataType> node = root;

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
    public RedBlackTree<DataType> Assign(RedBlackTree<DataType> newData)
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
    public RedBlackNode<DataType> Add(DataType data)
    {
        RedBlackNode<DataType> newNode = new RedBlackNode<DataType>(data);

        Add(newNode);

        return newNode;
    }

    /// <summary>
    /// Inserts a new node of the given data into the binary tree 
    /// </summary>
    /// <param name="newNode"></param>
    /// <returns></returns>
    public RedBlackTree<DataType> Add(RedBlackNode<DataType> newNode)
    {
        if (nodeCount == 0)
        {
            newNode.color = RedBlackColor.Black;

            root = newNode;

            nodeCount = 1;

            return this;
        }

        newNode.color = RedBlackColor.Red;

        RedBlackNode<DataType> node = root;

        while (!node.IsLeaf())
        {
            if (GenericEquals(node.data, newNode.data))
            {
                return this;
            }

            if (GenericGreaterThan(node.data, newNode.data))
            {
                if (node.left == null)
                {
                    node.left = newNode;

                    newNode.parent = node;

                    nodeCount++;

                    RebalanceInsertion(newNode);

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

                    RebalanceInsertion(newNode);

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

        RebalanceInsertion(newNode);

        return this;
    }

    /// <summary>
    /// Remove and return a node of the given data if it is present
    /// </summary>
    /// <param name="data"></param>
    /// <returns></returns>
    public RedBlackNode<DataType> Remove(DataType data)
    {
        RedBlackNode<DataType> node = Find(data);

        Remove(node);

        return node;
    }

    /// <summary>
    /// Removes a node from the binary tree
    /// </summary>
    /// <param name="removedNode"></param>
    /// <returns></returns>
    public RedBlackTree<DataType> Remove(RedBlackNode<DataType> removedNode)
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

        RedBlackNode<DataType> replacingNode = null;

        if (removedNode.IsLeaf())
        {
            // NIL NODE
            replacingNode = new RedBlackNode<DataType>();

            replacingNode.color = RedBlackColor.Black;

            replacingNode.parent = removedNode.parent;

            if (removedNode.parent.left == removedNode)
            {
                removedNode.parent.left = replacingNode;
            }
            else
            {
                removedNode.parent.right = replacingNode;
            }

            RebalanceRemoval(replacingNode, removedNode.color);

            if (replacingNode.parent.left == replacingNode)
            {
                replacingNode.parent.left = null;
            }
            else
            {
                replacingNode.parent.right = null;
            }

            return this;
        }
        else if (removedNode.right == null)
        {
            replacingNode = removedNode.left;

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

            removedNode.left.color = removedNode.color;
        }
        else if (removedNode.left == null)
        {
            replacingNode = removedNode.right;

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

            removedNode.right.color = removedNode.color;
        }
        else
        {
            RedBlackNode<DataType> node = removedNode.right;

            while (node.left != null)
            {
                node = node.left;
            }

            replacingNode = node;

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

            node.color = removedNode.color;
        }

        RebalanceRemoval(replacingNode, removedNode.color);

        return this;
    }

    /// <summary>
    /// Remove and return the leftmost node from its connected nodes in the binary tree
    /// </summary>
    /// <returns></returns>
    public RedBlackNode<DataType> RemoveLeft()
    {
        return Remove(Left());
    }

    /// <summary>
    /// Remove and return the root node from its connected nodes in the binary tree
    /// </summary>
    /// <returns></returns>
    public RedBlackNode<DataType> RemoveRoot()
    {
        return Remove(root.data);
    }

    /// <summary>
    /// Remove and return the rightmost node from its connected nodes in the binary tree
    /// </summary>
    /// <returns></returns>
    public RedBlackNode<DataType> RemoveRight()
    {
        return Remove(Right());
    }

    /// <summary>
    /// Swaps the binary tree's nodes with another binary tree's nodes
    /// </summary>
    /// <param name="swappedData"></param>
    /// <returns></returns>
    public RedBlackTree<DataType> Swap(RedBlackTree<DataType> swappedData)
    {
        RedBlackNode<DataType> data = root;

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
    public RedBlackNode<DataType> Emplace(ref DataType data)
    {
        RedBlackNode<DataType> newNode = new RedBlackNode<DataType>(data);

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
    public RedBlackNode<DataType> Replace(DataType replacedData, DataType newData)
    {
        RedBlackNode<DataType> node = Find(replacedData);

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
    public RedBlackTree<DataType> Replace(RedBlackNode<DataType> replacedNode, RedBlackNode<DataType> newNode)
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
    public RedBlackNode<DataType> Find(DataType data)
    {
        if (nodeCount == 0)
        {
            return null;
        }

        RedBlackNode<DataType> node = root;

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
    public bool Contains(RedBlackNode<DataType> newNode)
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
    private static void AddChildrenRecursively(ref RedBlackTree<DataType> currentTree, ref RedBlackNode<DataType> currentNode)
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
    public static RedBlackTree<DataType> Subset(RedBlackNode<DataType> node)
    {
        RedBlackTree<DataType> tree = new RedBlackTree<DataType>();

        AddChildrenRecursively(ref tree, ref node);

        return tree;
    }

    /// <summary>
    /// Merges the given binary tree into this binary tree
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public RedBlackTree<DataType> Merge(RedBlackTree<DataType> newData)
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
    public RedBlackTree<DataType> Copy()
    {
        return new RedBlackTree<DataType>(this);
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
/// The color of a node in a red-black binary search tree.
/// </summary>
public enum RedBlackColor { Black = 0, Red = 1 };

/// <summary>
/// Class that stores unique data, a red or black value, and connections to the left and right nodes in a red-black binary search tree.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class RedBlackNode<DataType> // where DataType : IComparable, IComparable<DataType>
{
    // VARIABLES

    /// <summary>
    /// This node's data
    /// </summary>
    public DataType data = default(DataType);

    /// <summary>
    /// A link to the parent (above) node
    /// </summary>
    public RedBlackNode<DataType> parent = null;

    /// <summary>
    /// A link to the left (lesser) node
    /// </summary>
    public RedBlackNode<DataType> left = null;

    /// <summary>
    /// A link to the right (greater) node
    /// </summary>
    public RedBlackNode<DataType> right = null;

    /// <summary>
    /// Whether this node is red or black
    /// </summary>
    public RedBlackColor color = RedBlackColor.Red;


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
    public RedBlackNode<DataType> Parent
    {
        get
        {
            return parent;
        }
    }

    /// <summary>
    /// Readonly left node variable
    /// </summary>
    public RedBlackNode<DataType> Left
    {
        get
        {
            return left;
        }
    }

    /// <summary>
    /// Readonly right node variable
    /// </summary>
    public RedBlackNode<DataType> Right
    {
        get
        {
            return right;
        }
    }

    /// <summary>
    /// Readonly color variable
    /// </summary>
    public RedBlackColor Color
    {
        get
        {
            return color;
        }
    }


    // CONSTRUCTOR

    /// <summary>
    /// Default constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="color"></param>
    /// <param name="left"></param>
    /// <param name="right"></param>
    /// <param name="parent"></param>
    public RedBlackNode(DataType data = default(DataType), RedBlackColor color = RedBlackColor.Red, RedBlackNode<DataType> left = null, RedBlackNode<DataType> right = null, RedBlackNode<DataType> parent = null)
    {
        this.data = data;

        this.color = color;

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
    public RedBlackNode<DataType> BinarySearch(DataType data)
    {
        RedBlackNode<DataType> current = this;

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
    public RedBlackNode<DataType> LowerBound()
    {
        RedBlackNode<DataType> node = this;

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
    public RedBlackNode<DataType> Root()
    {
        RedBlackNode<DataType> node = this;

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
    public RedBlackNode<DataType> UpperBound()
    {
        RedBlackNode<DataType> node = this;

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

    /// <summary>
    /// Returns whether this node is red
    /// </summary>
    /// <returns></returns>
    public bool IsRed()
    {
        return color == RedBlackColor.Red;
    }

    /// <summary>
    /// Returns whether this node is black
    /// </summary>
    /// <returns></returns>
    public bool IsBlack()
    {
        return color == RedBlackColor.Black;
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
