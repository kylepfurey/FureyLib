// .cs
// JSON Save Data
// by Kyle Furey

using System;
using System.Collections.Generic;
using Newtonsoft.Json;

/// <summary>
/// Contains serialized save data.
/// </summary>
[Serializable]
public sealed class SaveData
{
    // FIELDS

    /// <summary>
    /// The name of this save data.
    /// </summary>
    string name;

    /// <summary>
    /// Each save file property.
    /// </summary>
    Dictionary<string, string> properties;


    // PROPERTIES

    /// <summary>
    /// The name of this save data.
    /// </summary>
    public string Name => name;

    /// <summary>
    /// Each save file property.
    /// </summary>
    public IReadOnlyDictionary<string, string> All => properties;


    // CONSTRUCTOR

    /// <summary>
    /// Deserializes a JSON object into save data.
    /// </summary>
    public SaveData(string name, string json = "{}")
    {
        this.name = name;
        try
        {
            properties = JsonConvert.DeserializeObject<Dictionary<string, string>>(json);
            if (properties == null)
                properties = new Dictionary<string, string>();
        }
        catch
        {
            properties = new Dictionary<string, string>();
        }
    }


    // METHODS

    /// <summary>
    /// Reasd properties from a save file.
    /// </summary>
    public bool Read<T>(string property, out T value, T defaultValue = default(T))
    {
        string json;
        if (properties.TryGetValue(property, out json))
        {
            try
            {
                value = JsonConvert.DeserializeObject<T>(json);
                return true;
            }
            catch { }
        }

        value = defaultValue;
        return false;
    }

    /// <summary>
    /// Writes properties into a save file.
    /// </summary>
    public bool Write<T>(string property, T value)
    {
        string json;
        try
        {
            json = JsonConvert.SerializeObject(value);
            if (json == null)
                return false;
        }
        catch
        {
            return false;
        }

        properties[property] = json;
        return true;
    }

    /// <summary>
    /// Clears all properties from a save file.
    /// </summary>
    public void Clear() => properties.Clear();

    /// <summary>
    /// Converts save data into a JSON object.
    /// </summary>
    public override string ToString() => JsonConvert.SerializeObject(properties);
}
