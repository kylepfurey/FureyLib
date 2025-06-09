// .cs
// Json Serialization Functions
// by Kyle Furey

#nullable enable
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;

/// <summary>
/// Serialization to and from the .json format.
/// </summary>
public class JsonSerializer : ISerializer
{
    // METHODS
    
    /// <summary>
    /// Converts an object into a serializable string.
    /// </summary>
    public string Serialize<Type>(Type data)
    {
        JsonSerializerSettings settings = new JsonSerializerSettings();
        settings.Formatting = Formatting.Indented;
        return JsonConvert.SerializeObject(data, settings);
    }

    /// <summary>
    /// Converts a serializable string into an object.
    /// </summary>
    public Type Deserialize<Type>(string data)
    {
        JsonSerializerSettings settings = new JsonSerializerSettings();
        settings.Formatting = Formatting.Indented;
        return JsonConvert.DeserializeObject<Type>(data, settings)!;
    }
}
