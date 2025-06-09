// .cs
// Binary Serialization Functions
// by Kyle Furey

#nullable enable
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using UnityEngine;

/// <summary>
/// Serialization to and from binary.
/// </summary>
public class BinarySerializer : ISerializer
{
    // METHODS

    /// <summary>
    /// Converts an object into a serializable string.
    /// </summary>
    public string Serialize<Type>(Type data)
    {
        BinaryFormatter binary = new BinaryFormatter();
        using MemoryStream memory = new MemoryStream();
        binary.Serialize(memory, data);
        return Convert.ToBase64String(memory.ToArray());
    }

    /// <summary>
    /// Converts a serializable string into an object.
    /// </summary>
    public Type Deserialize<Type>(string data)
    {
        BinaryFormatter binary = new BinaryFormatter();
        using MemoryStream memory = new MemoryStream(Convert.FromBase64String(data));
        return (Type)binary.Deserialize(memory);
    }
}
