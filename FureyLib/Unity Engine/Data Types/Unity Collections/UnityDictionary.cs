
// Unity Editor Dictionary Class Script
// by Kyle Furey

using System;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Allows a dictionary to be constructed in the Unity editor.
/// </summary>
/// <typeparam name="KeyType"></typeparam>
/// <typeparam name="ValueType"></typeparam>
[Serializable]
public class UnityDictionary<KeyType, ValueType>
{
    /// <summary>
    /// A serialized key value pair in the Unity editor.
    /// </summary>
    [Serializable]
    public struct KeyValuePair
    {
        /// <summary>
        /// This pair's key.
        /// </summary>
        public KeyType Key;

        /// <summary>
        /// This pair's value.
        /// </summary>
        public ValueType Value;
    }

    /// <summary>
    /// Each of the serialized key value pairs in the Unity editor.
    /// </summary>
    [SerializeField] private List<KeyValuePair> Pairs = new List<KeyValuePair>();

    /// <summary>
    /// Creates a dictionary from the serialized list of key value pairs in the Unity editor.<br/>
    /// Discards the list after creation.
    /// </summary>
    /// <returns></returns>
    public Dictionary<KeyType, ValueType> Create()
    {
        Dictionary<KeyType, ValueType> Dictionary = new Dictionary<KeyType, ValueType>();

        foreach (var Pair in Pairs)
        {
            Dictionary[Pair.Key] = Pair.Value;
        }

        Pairs = null;

        return Dictionary;
    }
}
