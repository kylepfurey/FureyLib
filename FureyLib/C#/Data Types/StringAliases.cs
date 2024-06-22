
// String Alias Replacement Script
// by Kyle Furey

using System.Collections;
using System.Collections.Generic;

// Include this heading to use the class
using static StringAliases;

/// <summary>
/// Provides simple storage for string replacements.
/// </summary>
public class StringAliases : IEnumerable
{
    // VARIABLES

    /// <summary>
    /// Collection of globally used aliases
    /// </summary>
    public static StringAliases globalAliases = new StringAliases();

    /// <summary>
    /// The strings to locate for replacement
    /// </summary>
    private List<string> identifiers = new List<string>();

    /// <summary>
    /// The strings to replace the identifier with
    /// </summary>
    private List<string> values = new List<string>();


    // FUNCTIONS

    /// <summary>
    /// Adds a new entry or replaces a entry in the list of aliases
    /// </summary>
    /// <param name="identifier"></param>
    /// <param name="value"></param>
    /// <returns></returns>
    public StringAliases Add(string identifier, string value)
    {
        identifier = RemoveWhitespace(identifier);

        value = RemoveWhitespace(value);

        if (identifier == "" || value == "" || identifier == value)
        {
            return this;
        }

        int index = identifiers.IndexOf(identifier);

        if (index == -1)
        {
            identifiers.Add(identifier);

            values.Add(value);
        }
        else
        {
            values[index] = value;
        }

        return this;
    }

    /// <summary>
    /// Removes the given identifier from the list of aliases and return the index
    /// </summary>
    /// <param name="identifier"></param>
    /// <returns></returns>
    public int Remove(string identifier)
    {
        identifier = RemoveWhitespace(identifier);

        int index = identifiers.IndexOf(identifier);

        if (index != -1)
        {
            identifiers.RemoveAt(index);

            values.RemoveAt(index);
        }

        return index;
    }

    /// <summary>
    /// Removes the given index from the list of aliases
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public StringAliases RemoveAt(int index)
    {
        if (index >= 0 && index < identifiers.Count)
        {
            identifiers.RemoveAt(index);

            values.RemoveAt(index);
        }

        return this;
    }

    /// <summary>
    /// Clears the list of aliases
    /// </summary>
    /// <returns></returns>
    public StringAliases Clear()
    {
        identifiers.Clear();

        values.Clear();

        return this;
    }

    /// <summary>
    /// Replaces all aliases in the given message with their corresponding values. Replaces once, in order of each alias.
    /// </summary>
    /// <param name="message"></param>
    /// <returns></returns>
    public string ReplaceAliases(string message)
    {
        for (int i = 0; i < identifiers.Count; i++)
        {
            if (message == identifiers[i])
            {
                message = values[i];

                i -= 1;

                continue;
            }

            int index = message.IndexOf(identifiers[i] + " ");

            if (index != -1)
            {
                message = message.Remove(index, identifiers[i].Length + 1);

                message = message.Insert(index, values[i] + " ");

                i -= 1;

                continue;
            }

            index = message.IndexOf(" " + identifiers[i]);

            if (index != -1)
            {
                message = message.Remove(index, identifiers[i].Length + 1);

                message = message.Insert(index, " " + values[i]);

                i -= 1;

                continue;
            }
        }

        return message;
    }

    /// <summary>
    /// Replaces all of the given aliases in the given message with their corresponding values. Replaces once, in order of each alias.
    /// </summary>
    /// <param name="message"></param>
    /// <param name="identifiers"></param>
    /// <returns></returns>
    public string ReplaceAliases(string message, params string[] identifiers)
    {
        for (int j = 0; j < identifiers.Length; j++)
        {
            int i = this.identifiers.IndexOf(identifiers[j]);

            if (i == -1)
            {
                continue;
            }

            if (message == this.identifiers[i])
            {
                message = values[i];

                j -= 1;

                continue;
            }

            int index = message.IndexOf(this.identifiers[i] + " ");

            if (index != -1)
            {
                message = message.Remove(index, this.identifiers[i].Length + 1);

                message = message.Insert(index, values[i] + " ");

                j -= 1;

                continue;
            }

            index = message.IndexOf(" " + this.identifiers[i]);

            if (index != -1)
            {
                message = message.Remove(index, this.identifiers[i].Length + 1);

                message = message.Insert(index, " " + values[i]);

                j -= 1;

                continue;
            }
        }

        return message;
    }

    /// <summary>
    /// Replaces all aliases in the given message with their corresponding values. Repeats until all aliases are filled in.
    /// </summary>
    /// <param name="message"></param>
    /// <returns></returns>
    public string ReplaceAliasesRecursively(string message)
    {
        message = ReplaceAliases(message);

        string newMessage = ReplaceAliases(message);

        while (message != newMessage)
        {
            message = newMessage;

            newMessage = ReplaceAliases(message);
        }

        return message;
    }

    /// <summary>
    /// Replaces all of the given aliases in the given message with their corresponding values. Repeats until all aliases are filled in.
    /// </summary>
    /// <param name="message"></param>
    /// <param name="identifiers"></param>
    /// <returns></returns>
    public string ReplaceAliasesRecursively(string message, params string[] identifiers)
    {
        message = ReplaceAliases(message, identifiers);

        string newMessage = ReplaceAliases(message, identifiers);

        while (message != newMessage)
        {
            message = newMessage;

            newMessage = ReplaceAliases(message, identifiers);
        }

        return message;
    }

    /// <summary>
    /// Returns whether the list of aliases contains the given identifier
    /// </summary>
    /// <param name="identifier"></param>
    /// <returns></returns>
    public bool Contains(string identifier)
    {
        identifier = RemoveWhitespace(identifier);

        return identifiers.Contains(identifier);
    }

    /// <summary>
    /// Returns the index of the given identifier
    /// </summary>
    /// <param name="identifier"></param>
    /// <returns></returns>
    public int Find(string identifier)
    {
        identifier = RemoveWhitespace(identifier);

        return identifiers.IndexOf(identifier);
    }

    /// <summary>
    /// Returns the total number of aliases
    /// </summary>
    /// <returns></returns>
    public int Count()
    {
        return identifiers.Count;
    }

    /// <summary>
    /// Returns the corresponding value of the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public string GetValue(int index)
    {
        if (index >= 0 && index < values.Count)
        {
            return values[index];
        }
        else
        {
            return "";
        }
    }

    /// <summary>
    /// Returns the corresponding identifier of the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public string GetIdentifier(int index)
    {
        if (index >= 0 && index < identifiers.Count)
        {
            return identifiers[index];
        }
        else
        {
            return "";
        }
    }

    /// <summary>
    /// Returns the corresponding value of the given identifier
    /// </summary>
    /// <param name="identifier"></param>
    /// <returns></returns>
    public string GetValue(string identifier)
    {
        identifier = RemoveWhitespace(identifier);

        int index = identifiers.IndexOf(identifier);

        if (index != -1)
        {
            return values[index];
        }
        else
        {
            return "";
        }
    }

    /// <summary>
    /// Returns the corresponding identifier of the given value
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    public string GetIdentifier(string value)
    {
        value = RemoveWhitespace(value);

        int index = values.IndexOf(value);

        if (index != -1)
        {
            return identifiers[index];
        }
        else
        {
            return "";
        }
    }

    /// <summary>
    /// Returns a list of the identifiers
    /// </summary>
    /// <returns></returns>
    public List<string> GetIdentifiers()
    {
        return identifiers;
    }

    /// <summary>
    /// Returns a list of the values
    /// </summary>
    /// <returns></returns>
    public List<string> GetValues()
    {
        return values;
    }

    /// <summary>
    /// Returns a dictionary of the identifiers to values
    /// </summary>
    /// <returns></returns>
    public Dictionary<string, string> GetDictionary()
    {
        Dictionary<string, string> dictionary = new Dictionary<string, string>();

        for (int i = 0; i < identifiers.Count; i++)
        {
            dictionary[identifiers[i]] = values[i];
        }

        return dictionary;
    }

    /// <summary>
    /// Removes whitespace characters from the beginning and end of a string
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    public static string RemoveWhitespace(string value, bool lower = false)
    {
        if (value == " ")
        {
            return "";
        }

        value = value.Replace("\n", "");

        while (value[0] == ' ')
        {
            value = value.Remove(0);
        }

        while (value[value.Length - 1] == ' ')
        {
            value = value.Remove(value.Length - 1);
        }

        return lower ? value.ToLower() : value;
    }


    // IENUMERATOR

    /// <summary>
    /// IEnumerator implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return identifiers.GetEnumerator();
    }
}
