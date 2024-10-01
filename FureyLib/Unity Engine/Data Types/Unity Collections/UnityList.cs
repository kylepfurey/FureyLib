
// Unity Editor Linked List Class Script
// by Kyle Furey

using System;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Allows a linked list to be constructed in the Unity editor.
/// </summary>
/// <typeparam name="DataType"></typeparam>
[Serializable]
public class UnityList<DataType>
{
    /// <summary>
    /// Each of the serialized nodes in the Unity editor.
    /// </summary>
    [SerializeField] private List<DataType> Nodes = new List<DataType>();

    /// <summary>
    /// Creates a linked list from the serialized list of nodes in the Unity editor.<br/>
    /// Discards the list after creation.
    /// </summary>
    /// <returns></returns>
    public LinkedList<DataType> Create()
    {
        LinkedList<DataType> List = new LinkedList<DataType>();

        foreach (var Node in Nodes)
        {
            List.AddLast(Node);
        }

        List = null;

        return List;
    }
}
