
// Static Json Serialization Functions Script
// by Kyle Furey

// REQUIREMENT: Json Serializer

using System;
using System.IO;
using System.Text.Json; // Serializer

// Include this heading to use the library.
using static Json;

/// <summary>
/// •  Serializes and deserializes data to and from Json files.<br/>
/// •  Serialized classes and structures should have the [System.Serializable] attribute above the class.<br/>
/// •  Public fields / properties are always serialized by default.<br/>
/// •  Note: Depending on the serializer, private and protected fields / properties may never be serialized.
/// </summary>
public static class Json
{
    // INLINE SPECIFIER

    /// <summary>
    /// Whether to read and write Json strings inline (true) or indented (false) by default.
    /// </summary>
    public static bool inline { get; set; } = false;


    // SERIALIZATION

    /// <summary>
    /// Converts the given data into a Json formatted string.
    /// </summary>
    /// <returns>The Json formatted string of the given data.</returns>
    public static string Serialize<DataType>(DataType data, bool inline)
    {
        JsonSerializerOptions options = new JsonSerializerOptions();

        options.IncludeFields = true;

        options.WriteIndented = !inline;

        return JsonSerializer.Serialize(data, options);
    }

    /// <summary>
    /// Converts the given data into a Json formatted string.
    /// </summary>
    /// <returns>The Json formatted string of the given data.</returns>
    public static string Serialize<DataType>(DataType data)
    {
        return Serialize(data, inline);
    }

    /// <summary>
    /// Reads the given Json formatted string as the given type.
    /// </summary>
    /// <returns>The deserialized Json string's corresponding values. Throws an exception if the string is not in a valid Json format.</returns>
    public static DataType Deserialize<DataType>(string json, bool inline)
    {
        JsonSerializerOptions options = new JsonSerializerOptions();

        options.IncludeFields = true;

        options.WriteIndented = !Json.inline;

        return JsonSerializer.Deserialize<DataType>(json, options);
    }

    /// <summary>
    /// Reads the given Json formatted string as the given type.
    /// </summary>
    /// <returns>The deserialized Json string's corresponding values. Throws an exception if the string is not in a valid Json format.</returns>
    public static DataType Deserialize<DataType>(string json)
    {
        return Deserialize<DataType>(json, inline);
    }


    // IMPORT AND EXPORT

    /// <summary>
    /// Reads a Json file at the given path and returns its data.
    /// </summary>
    /// <returns>The imported Json file's corresponding values. Throws an exception if the file is not a valid Json file.</returns>
    public static DataType Import<DataType>(string path)
    {
        if (!path.ToLower().Contains(".json"))
        {
            throw new JsonException("The given path \"" + path + "\" is not to a .json file.");
        }

        if (!File.Exists(path))
        {
            throw new JsonException("The given .json file does not exist at path \"" + path + "\".");
        }

        FileStream file = File.OpenRead(path);

        string json = "";

        int current = file.ReadByte();

        while (current != -1)
        {
            json += (char)current;

            current = file.ReadByte();
        }

        file.Close();

        return Deserialize<DataType>(json);
    }

    /// <summary>
    /// Creates or overwrites a Json file of the given data to the given path.
    /// </summary>
    /// <returns>Whether a Json file was overwritten (a file is always created unless an exception is thrown).</returns>
    public static bool Export<DataType>(DataType data, string path)
    {
        if (!path.ToLower().Contains(".json"))
        {
            throw new JsonException("The given path \"" + path + "\" does not end in .json. Make sure to write the file's name with .json at the end of it.");
        }

        bool overwrite = File.Exists(path);

        FileStream file = File.Create(path);

        string json = Serialize(data);

        foreach (char letter in json)
        {
            file.WriteByte((byte)letter);
        }

        file.Close();

        return overwrite;
    }

    /// <summary>
    /// Deletes the Json file at the given path.
    /// </summary>
    /// <returns>Whether the file's deletion was successful.</returns>
    public static bool Delete<DataType>(string path)
    {
        if (!path.ToLower().Contains(".json"))
        {
            throw new JsonException("The given path \"" + path + "\" does not end in .json. Make sure to write the file's name with .json at the end of it.");
        }

        if (!File.Exists(path))
        {
            return false;
        }
        else
        {
            File.Delete(path);

            return true;
        }
    }

    /// <summary>
    /// Returns whether the given path leads to a Json file.
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    public static bool Exists(string path)
    {
        if (!path.ToLower().Contains(".json"))
        {
            return false;
        }

        return File.Exists(path);
    }
}
