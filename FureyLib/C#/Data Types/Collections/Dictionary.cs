
// Dictionary Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/map/map/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.dictionary-2?view=net-8.0

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

/// <summary>
/// Class used for fast access to value objects based on unique corresponding key objects.
/// </summary>
/// <typeparam name="KeyType"></typeparam>
/// <typeparam name="ValueType"></typeparam>
public class Dictionary<KeyType, ValueType> : IEnumerable, IEnumerable<KeyValuePair<KeyType, ValueType>> // where KeyType : IComparable, IComparable<KeyType>
{
    // VARIABLES

    /// <summary>
    /// A binary tree storing each unique key object and its value object
    /// </summary>
    private HashSet<KeyValuePair<KeyType, ValueType>> dictionary = new HashSet<KeyValuePair<KeyType, ValueType>>();


    // PROPERTIES

    /// <summary>
    /// Readonly count variable
    /// </summary>
    public int Count
    {
        get
        {
            return dictionary.Count;
        }
    }

    /// <summary>
    /// Readonly keys variable
    /// </summary>
    public KeyType[] Keys
    {
        get
        {
            return KeysToArray();
        }
    }

    /// <summary>
    /// Readonly values variable
    /// </summary>
    public ValueType[] Values
    {
        get
        {
            return ValuesToArray();
        }
    }


    // TO ARRAY AND LIST

    /// <summary>
    /// Returns an array of the current dictionary
    /// </summary>
    /// <returns></returns>
    public KeyValuePair<KeyType, ValueType>[] ToArray()
    {
        KeyValuePair<KeyType, ValueType>[] newArray = new KeyValuePair<KeyType, ValueType>[dictionary.Count];

        int i = 0;

        foreach (KeyValuePair<KeyType, ValueType> pair in dictionary)
        {
            newArray[i] = pair;

            i++;
        }

        return newArray;
    }

    /// <summary>
    /// Returns a list of the current dictionary
    /// </summary>
    /// <returns></returns>
    public List<KeyValuePair<KeyType, ValueType>> ToList()
    {
        List<KeyValuePair<KeyType, ValueType>> newList = new List<KeyValuePair<KeyType, ValueType>>(dictionary.Count);

        foreach (KeyValuePair<KeyType, ValueType> pair in dictionary)
        {
            newList.Add(pair);
        }

        return newList;
    }

    /// <summary>
    /// Returns an array of the current dictionary's keys
    /// </summary>
    /// <returns></returns>
    public KeyType[] KeysToArray()
    {
        KeyType[] newArray = new KeyType[dictionary.Count];

        int i = 0;

        foreach (KeyValuePair<KeyType, ValueType> pair in dictionary)
        {
            newArray[i] = pair.key;

            i++;
        }

        return newArray;
    }

    /// <summary>
    /// Returns a list of the current dictionary's keys
    /// </summary>
    /// <returns></returns>
    public List<KeyType> KeysToList()
    {
        List<KeyType> newList = new List<KeyType>(dictionary.Count);

        foreach (KeyValuePair<KeyType, ValueType> pair in dictionary)
        {
            newList.Add(pair.key);
        }

        return newList;
    }

    /// <summary>
    /// Returns an array of the current dictionary's values
    /// </summary>
    /// <returns></returns>
    public ValueType[] ValuesToArray()
    {
        ValueType[] newArray = new ValueType[dictionary.Count];

        int i = 0;

        foreach (KeyValuePair<KeyType, ValueType> pair in dictionary)
        {
            newArray[i] = pair.value;

            i++;
        }

        return newArray;
    }

    /// <summary>
    /// Returns a list of the current dictionary's values
    /// </summary>
    /// <returns></returns>
    public List<ValueType> ValuesToList()
    {
        List<ValueType> newList = new List<ValueType>(dictionary.Count);

        foreach (KeyValuePair<KeyType, ValueType> pair in dictionary)
        {
            newList.Add(pair.value);
        }

        return newList;
    }


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Dictionary()
    {
        dictionary = new HashSet<KeyValuePair<KeyType, ValueType>>();
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copiedDictionary"></param>
    public Dictionary(Dictionary<KeyType, ValueType> copiedDictionary)
    {
        dictionary = new HashSet<KeyValuePair<KeyType, ValueType>>(copiedDictionary.dictionary);
    }

    /// <summary>
    /// Key value constructor
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
    public Dictionary(KeyType key, ValueType value)
    {
        dictionary = new HashSet<KeyValuePair<KeyType, ValueType>>();

        dictionary.Add(new KeyValuePair<KeyType, ValueType>(key, value));
    }


    // EQUALITY

    /// <summary>
    /// Check if another dictionary is equal to the dictionary
    /// </summary>
    /// <param name="comparedDictionary"></param>
    /// <returns></returns>
    public bool Equals(Dictionary<KeyType, ValueType> comparedDictionary)
    {
        return dictionary == comparedDictionary.dictionary;
    }

    /// <summary>
    /// Check if another dictionary is equal to the dictionary
    /// </summary>
    /// <param name="dictionary"></param>
    /// <param name="comparedDictionary"></param>
    /// <returns></returns>
    public static bool operator ==(Dictionary<KeyType, ValueType> dictionary, Dictionary<KeyType, ValueType> comparedDictionary)
    {
        return dictionary.Equals(comparedDictionary);
    }

    /// <summary>
    /// Check if another dictionary is not equal to the dictionary
    /// </summary>
    /// <param name="dictionary"></param>
    /// <param name="comparedDictionary"></param>
    /// <returns></returns>
    public static bool operator !=(Dictionary<KeyType, ValueType> dictionary, Dictionary<KeyType, ValueType> comparedDictionary)
    {
        return !dictionary.Equals(comparedDictionary);
    }


    // CAPACITY

    /// <summary>
    /// Returns whether the dictionary is empty
    /// </summary>
    /// <returns></returns>
    public bool Empty()
    {
        return dictionary.Count == 0;
    }

    /// <summary>
    /// Returns the current number of pairs in the dictionary
    /// </summary>
    /// <returns></returns>
    public int Size()
    {
        return dictionary.Count;
    }


    // ELEMENT ACCESS

    /// <summary>
    /// Gets or sets the value with the given key
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    public ValueType this[KeyType key]
    {
        get => Find(key);
        set => Add(key, value);
    }

    /// <summary>
    /// Returns the value with the given key
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    public ValueType Find(KeyType key)
    {
        KeyValuePair<KeyType, ValueType> result;

        if (dictionary.TryGetValue(new KeyValuePair<KeyType, ValueType>(key, default(ValueType)), out result))
        {
            return result.value;
        }
        else
        {
            throw new KeyNotFoundException();
        }
    }

    /// <summary>
    /// Returns the value with the given key if it exists
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
    /// <returns></returns>
    public bool TryGetValue(KeyType key, out ValueType value)
    {
        KeyValuePair<KeyType, ValueType> result;

        if (dictionary.TryGetValue(new KeyValuePair<KeyType, ValueType>(key, default(ValueType)), out result))
        {
            value = result.value;

            return true;
        }
        else
        {
            value = default(ValueType);

            return false;
        }
    }


    // LOCATING ELEMENTS

    /// <summary>
    /// Returns whether the dictionary contains the given key
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    public bool ContainsKey(KeyType key)
    {
        return dictionary.Contains(new KeyValuePair<KeyType, ValueType>(key, default(ValueType)));
    }

    /// <summary>
    /// Returns whether the dictionary contains at least one of the given value
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    public bool ContainsValue(ValueType value)
    {
        foreach (KeyValuePair<KeyType, ValueType> pair in dictionary)
        {
            if ((pair.value != null && pair.value.Equals(value)) || (pair.value == null && value == null))
            {
                return true;
            }
        }

        return false;
    }

    /// <summary>
    /// Returns the total number of the given value in the dictionary
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    public int Total(ValueType value)
    {
        int total = 0;

        foreach (KeyValuePair<KeyType, ValueType> pair in dictionary)
        {
            if ((pair.value != null && pair.value.Equals(value)) || (pair.value == null && value == null))
            {
                total++;
            }
        }

        return total;
    }


    // MODIFIERS

    /// <summary>
    /// Assigns the dictionary's data from another dictionary's data
    /// </summary>
    /// <param name="newData"></param>
    /// <returns></returns>
    public Dictionary<KeyType, ValueType> Assign(Dictionary<KeyType, ValueType> newData)
    {
        dictionary = new HashSet<KeyValuePair<KeyType, ValueType>>(newData.dictionary);

        return this;
    }

    /// <summary>
    /// Adds a new value or replaces an existing value in the dictionary at the given key
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
    /// <returns></returns>
    public Dictionary<KeyType, ValueType> Add(KeyType key, ValueType value)
    {
        KeyValuePair<KeyType, ValueType> pair = new KeyValuePair<KeyType, ValueType>(key, value);

        // Ensures the value is replaced
        dictionary.Remove(pair);

        dictionary.Add(pair);

        return this;
    }

    /// <summary>
    /// Attempts to add a new value to the dictionary at the given key but does not replace any existing values
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
    /// <returns></returns>
    public bool TryAdd(KeyType key, ValueType value)
    {
        if (ContainsKey(key))
        {
            return false;
        }

        Add(key, value);

        return true;
    }

    /// <summary>
    /// Removes a value from the dictionary at the given key
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    public ValueType Remove(KeyType key)
    {
        ValueType value;

        if (TryGetValue(key, out value))
        {
            dictionary.Remove(new KeyValuePair<KeyType, ValueType>(key, value));

            return value;
        }
        else
        {
            return default(ValueType);
        }
    }

    /// <summary>
    /// Swaps the dictionary's data with the data of another dictionary
    /// </summary>
    /// <param name="swappedData"></param>
    /// <returns></returns>
    public Dictionary<KeyType, ValueType> Swap(Dictionary<KeyType, ValueType> swappedData)
    {
        HashSet<KeyValuePair<KeyType, ValueType>> swappedDictionary = swappedData.dictionary;

        swappedData.dictionary = dictionary;

        dictionary = swappedDictionary;

        return this;
    }

    /// <summary>
    /// Clears the dictionary's data
    /// </summary>
    /// <returns></returns>
    public int Clear()
    {
        int count = dictionary.Count;

        dictionary.Clear();

        return count;
    }


    // TO STRING

    /// <summary>
    /// Converts the keys and values of the dictionary into a string
    /// </summary>
    /// <returns></returns>
    public string ToString()
    {
        if (dictionary.Count == 0)
        {
            return "{ }";
        }

        string log = "{ ";

        foreach (KeyValuePair<KeyType, ValueType> pair in dictionary)
        {
            log += (pair.key + " : " + pair.value + ", ");
        }

        log = log.Remove(log.Length - 2, 1);

        log += "}";

        return log;
    }


    // ENUMERATOR FUNCTIONS

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return dictionary.GetEnumerator();
    }

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    IEnumerator<KeyValuePair<KeyType, ValueType>> IEnumerable<KeyValuePair<KeyType, ValueType>>.GetEnumerator()
    {
        return dictionary.GetEnumerator();
    }
}

/// <summary>
/// Structure that represents a pair of objects with one acting as the key to lookup the corresponding value object.
/// </summary>
/// <typeparam name="KeyType"></typeparam>
/// <typeparam name="ValueType"></typeparam>
public struct KeyValuePair<KeyType, ValueType> // where KeyType : IComparable, IComparable<KeyType>
{
    // VARIABLES

    /// <summary>
    /// The key object (used to find the value object)
    /// </summary>
    public readonly KeyType key;

    /// <summary>
    /// The value object (located using the key object)
    /// </summary>
    public ValueType value;


    // PROPERTIES

    /// <summary>
    /// Readonly key variable
    /// </summary>
    public KeyType Key
    {
        get
        {
            return key;
        }
    }

    /// <summary>
    /// Readonly value variable
    /// </summary>
    public ValueType Value
    {
        get
        {
            return value;
        }
    }


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public KeyValuePair()
    {
        key = default(KeyType);

        value = default(ValueType);
    }

    /// <summary>
    /// Key value constructor
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
    public KeyValuePair(KeyType key, ValueType value)
    {
        this.key = key;

        this.value = value;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copied"></param>
    public KeyValuePair(KeyValuePair<KeyType, ValueType> copied)
    {
        key = copied.key;

        value = copied.value;
    }


    // EQUALITY

    /// <summary>
    /// Returns the unique hash code of this pair's key
    /// </summary>
    /// <returns></returns>
    public override int GetHashCode()
    {
        return key.GetHashCode();
    }

    /// <summary>
    /// Check if the given pair's key matches this pair's key
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    public override bool Equals(object obj)
    {
        if (obj == null)
        {
            return false;
        }

        if (obj is KeyValuePair<KeyType, ValueType>)
        {
            KeyValuePair<KeyType, ValueType> pair = (KeyValuePair<KeyType, ValueType>)obj;

            return this == pair;
        }
        else
        {
            return false;
        }
    }

    /// <summary>
    /// Check if the given pair's key matches this pair's key
    /// </summary>
    /// <param name="pair"></param>
    /// <param name="comparedPair"></param>
    /// <returns></returns>
    public static bool operator ==(KeyValuePair<KeyType, ValueType> pair, KeyValuePair<KeyType, ValueType> comparedPair)
    {
        if (pair.key == null)
        {
            return comparedPair.key == null;
        }

        return pair.key.Equals(comparedPair.key);
    }

    /// <summary>
    /// Check if the given pair's key does not matches this pair's key
    /// </summary>
    /// <param name="pair"></param>
    /// <param name="comparedPair"></param>
    /// <returns></returns>
    public static bool operator !=(KeyValuePair<KeyType, ValueType> pair, KeyValuePair<KeyType, ValueType> comparedPair)
    {
        if (pair.key == null)
        {
            return comparedPair.key != null;
        }

        return !pair.key.Equals(comparedPair.key);
    }


    // TO STRING

    /// <summary>
    /// Returns a string representation of this key value pair
    /// </summary>
    /// <returns></returns>
    public string ToString()
    {
        return "{ " + key + " : " + value + " }";
    }
}
