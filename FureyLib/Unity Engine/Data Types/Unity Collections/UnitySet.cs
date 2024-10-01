
// Unity Editor Set Class Script
// by Kyle Furey

using System;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Allows a set to be constructed in the Unity editor.
/// </summary>
/// <typeparam name="KeyType"></typeparam>
[Serializable]
public class UnitySet<KeyType>
{
    /// <summary>
    /// Each of the serialized keys in the Unity editor.
    /// </summary>
    [SerializeField] private List<KeyType> Keys = new List<KeyType>();

    /// <summary>
    /// Creates a set from the serialized list of keys in the Unity editor.<br/>
    /// Discards the list after creation.
    /// </summary>
    /// <returns></returns>
    public HashSet<KeyType> Create()
    {
        HashSet<KeyType> Set = new HashSet<KeyType>();

        foreach (var Key in Keys)
        {
            Set.Add(Key);
        }

        Keys = null;

        return Set;
    }
}
