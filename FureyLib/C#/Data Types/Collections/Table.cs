// .cs
// Object Table Type
// by Kyle Furey

#nullable enable
using System;
using System.Collections;
using System.Collections.Generic;

/// <summary>
/// A collection of named objects of any type.
/// </summary>
public sealed class Table : IEnumerable, IEnumerable<KeyValuePair<string, object>>
{
    // DATA

    /// <summary>
    /// Each stored object by name.
    /// </summary>
    private Dictionary<string, object> objects;

    /// <summary>
    /// The current number of stored objects.
    /// </summary>
    public int Count => objects.Count;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor.
    /// </summary>
    public Table(int capacity = 16)
    {
        objects = new Dictionary<string, object>(capacity);
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    public Table(Table copied)
    {
        if (copied == null)
        {
            throw new ArgumentNullException(nameof(copied));
        }
        objects = new Dictionary<string, object>(copied.objects);
    }


    // INDEXER

    /// <summary>
    /// Returns the object of the given name or sets it to a new object.
    /// </summary>
    public object this[string name]
    {
        get
        {
            if (!objects.ContainsKey(name))
            {
                throw new KeyNotFoundException("ERROR: Object of name " + name + " was not found in the table!");
            }
            return objects[name];
        }
        set
        {
            if (objects.ContainsKey(name) && objects[name] != null)
            {
                if (value != null)
                {
                    if (objects[name].GetType() != value.GetType())
                    {
                        throw new InvalidOperationException("ERROR: Overwriting table object of name " + name + " and type " + objects[name].GetType().ToString() + " with a new object of type " + value.GetType().ToString() + "!");
                    }
                    objects[name] = value;
                }
                else
                {
                    if (!objects[name].GetType().IsClass)
                    {
                        throw new ArgumentNullException(nameof(value));
                    }
                    objects[name] = value;
                }
            }
            else
            {
                objects[name] = value;
            }
        }
    }


    // TABLE

    /// <summary>
    /// Returns an enumerator for this table.
    /// </summary>
    public IEnumerator GetEnumerator() => return objects.GetEnumerator();

    /// <summary>
    /// Returns an enumerator for this table.
    /// </summary>
    IEnumerator<KeyValuePair<string, object>> IEnumerable<KeyValuePair<string, object>>.GetEnumerator() => objects.GetEnumerator();

    /// <summary>
    /// Returns the object with the given name and type (or null).
    /// </summary>
    public T? Find<T>(string name)
    {
        return objects.TryGetValue(name, out var obj) && obj is T type ? type : default(T?);
    }

    /// <summary>
    /// Returns whether the table contains an object of the given name.
    /// </summary>
    public bool Contains(string name) => objects.ContainsKey(name);

    /// <summary>
    /// Returns whether the table contains an object of the given name and type.
    /// </summary>
    public bool Contains<T>(string name) => objects.ContainsKey(name) && objects[name] is T;

    /// <summary>
    /// Inserts a new object into the table with the given name and type.
    /// </summary>
    public T? Insert<T>(string name, T? obj)
    {
        if (objects.ContainsKey(name) && objects[name] != null && objects[name] is not T)
        {
            throw new InvalidOperationException("ERROR: Overwriting table object of name " + name + " and type " + objects[name].GetType().ToString() + " with a new object of type " + typeof(T).ToString() + "!");
        }
        objects[name] = obj;
        return (T?)objects[name];
    }

    /// <summary>
    /// Inserts a new object into the table with the given name and type.
    /// </summary>
    public T? Add<T>(string name, T? obj) => Insert(name, obj);

    /// <summary>
    /// Erases the object with the given name.
    /// </summary>
    public bool Erase(string name) => objects.Remove(name);

    /// <summary>
    /// Erases the object with the given name.
    /// </summary>
    public void Remove(string name) => Erase(name);

    /// <summary>
    /// Clears the table of all its objects.
    /// </summary>
    public void Clear() => objects.Clear();

    /// <summary>
    /// Converts this table into a string.
    /// </summary>
    public string ToString(bool prettyPrint)
    {
        if (objects.Count == 0)
        {
            return "{}";
        }
        string json = "{";
        if (prettyPrint)
        {
            foreach (var pair in objects)
            {
                json += "\n\t\"" + pair.Key + "\" : " + ((pair.Value != null) ? ((pair.Value is string) ? ('"' + pair.Value.ToString() + '"') : (pair.Value.ToString())) : ("null")) + ',';
            }
            json = json.Remove(json.Length - 1, 1);
            json += '\n';
        }
        else
        {
            foreach (var pair in objects)
            {
                json += " \"" + pair.Key + "\" : " + ((pair.Value != null) ? ((pair.Value is string) ? ('"' + pair.Value.ToString() + '"') : (pair.Value.ToString())) : ("null")) + ',';
            }
            json = json.Remove(json.Length - 1, 1);
            json += ' ';
        }
        return json + '}';
    }

    /// <summary>
    /// Converts this table into a string.
    /// </summary>
    public override string ToString() => ToString(true);
}
