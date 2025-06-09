// .cs
// Serialization Interface
// by Kyle Furey

#nullable enable
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Enables a class to support generic serialization.
/// </summary>
public interface ISerializer
{
    // VARIABLES

    /// <summary>
    /// The default serializer object.
    /// </summary>
    public static ISerializer instance = new JsonSerializer();


    // INTERFACE

    /// <summary>
    /// Converts an object into a serializable string.
    /// </summary>
    public string Serialize<Type>(Type data);

    /// <summary>
    /// Converts a serializable string into an object.
    /// </summary>
    public Type Deserialize<Type>(string data);
}

/// <summary>
/// Extension methods for serialization.
/// </summary>
public static class SerializationExtensions
{
    // METHODS
    
    /// <summary>
    /// Serializes this object into a string using the default serializer.
    /// </summary>
    public static string Serialize<Type>(this Type self)
    {
        return ISerializer.instance.Serialize(self);
    }

    /// <summary>
    /// Deserializes the given string into an object using the default serializer.
    /// </summary>
    public static Type Deserialize<Type>(this string self)
    {
        return ISerializer.instance.Deserialize<Type>(self);
    }
}
