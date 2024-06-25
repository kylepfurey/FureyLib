
// String Alias Replacement Script
// by Kyle Furey

using System.Collections;
using System.Collections.Generic;

// Include this heading to use the class
using static StringAlias;

/// <summary>
/// Provides simple storage for string replacements.
/// </summary>
public class StringAlias : IEnumerable
{
    // VARIABLES

    /// <summary>
    /// Collection of globally used aliases
    /// </summary>
    public static StringAlias globalAliases = new StringAlias();

    /// <summary>
    /// The strings to locate for replacement
    /// </summary>
    private List<string> identifiers = new List<string>();

    /// <summary>
    /// The strings to replace the identifier with
    /// </summary>
    private List<string> values = new List<string>();

    /// <summary>
    /// Whitespace characters to ignore when parsing messages
    /// </summary>
    public List<char> whitespaceCharacters = new List<char>
    { '.', '?', '!', '+', '-', '*', '/', '=', '\n', '`', '~', '@', '#', '$', '%', '^', '&', '(', ')', '[', ']', '{', '}', '\\', ';', ':', '\'', ',', '<', '>', '"', '|' };


    // FUNCTIONS

    /// <summary>
    /// Adds a new entry or replaces a entry in the list of aliases
    /// </summary>
    /// <param name="identifier"></param>
    /// <param name="value"></param>
    /// <returns></returns>
    public int Add(string identifier, string value)
    {
        identifier = RemoveWhitespace(identifier);

        value = RemoveWhitespace(value);

        if (identifier == value || identifier == "" || value == "")
        {
            return -1;
        }

        int index = identifiers.IndexOf(identifier);

        if (index == -1)
        {
            identifiers.Add(identifier);

            values.Add(value);

            return identifiers.Count - 1;
        }
        else
        {
            values[index] = value;

            return index;
        }
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
    public bool RemoveAt(int index)
    {
        if (index >= 0 && index < identifiers.Count)
        {
            identifiers.RemoveAt(index);

            values.RemoveAt(index);

            return true;
        }
        else
        {
            return false;
        }
    }

    /// <summary>
    /// Clears the list of aliases
    /// </summary>
    /// <returns></returns>
    public int Clear()
    {
        int count = identifiers.Count;

        identifiers.Clear();

        values.Clear();

        return count;
    }

    /// <summary>
    /// Replaces all aliases in the given message with their corresponding values in order of each alias.
    /// </summary>
    /// <param name="message"></param>
    /// <returns></returns>
    public string ReplaceAliases(string message)
    {
        string tempMessage = message;

        for (int i = 0; i < whitespaceCharacters.Count; i++)
        {
            tempMessage = tempMessage.Replace(whitespaceCharacters[i], ' ');
        }

        for (int i = 0; i < identifiers.Count; i++)
        {
            if (message == identifiers[i])
            {
                message = values[i];

                continue;
            }

            string gap = "";

            for (int j = 0; j < values[i].Length; j++)
            {
                gap += " ";
            }

            int index = tempMessage.IndexOf(" " + identifiers[i] + " ");

            if (index != -1)
            {
                message = message.Remove(index + 1, identifiers[i].Length);

                message = message.Insert(index + 1, values[i]);

                tempMessage = tempMessage.Remove(index + 1, identifiers[i].Length);

                tempMessage = tempMessage.Insert(index + 1, gap);

                i--;

                continue;
            }

            index = tempMessage.IndexOf(identifiers[i] + " ");

            if (index == 0)
            {
                message = message.Remove(index, identifiers[i].Length);

                message = message.Insert(index, values[i]);

                tempMessage = tempMessage.Remove(index, identifiers[i].Length);

                tempMessage = tempMessage.Insert(index, gap);

                i--;

                continue;
            }

            index = tempMessage.IndexOf(" " + identifiers[i]);

            if (index == message.Length - identifiers[i].Length - 1)
            {
                message = message.Remove(index + 1, identifiers[i].Length);

                message = message.Insert(index + 1, values[i]);

                tempMessage = tempMessage.Remove(index + 1, identifiers[i].Length);

                tempMessage = tempMessage.Insert(index + 1, gap);

                i--;

                continue;
            }
        }

        return message;
    }

    /// <summary>
    /// Replaces all of the given aliases in the given message with their corresponding values in order of each alias.
    /// </summary>
    /// <param name="message"></param>
    /// <param name="identifiers"></param>
    /// <returns></returns>
    public string ReplaceAliases(string message, params string[] identifiers)
    {
        for (int i = 0; i < identifiers.Length; i++)
        {
            identifiers[i] = RemoveWhitespace(identifiers[i]);
        }

        string tempMessage = message;

        for (int i = 0; i < whitespaceCharacters.Count; i++)
        {
            tempMessage = tempMessage.Replace(whitespaceCharacters[i], ' ');
        }

        for (int j = 0; j < identifiers.Length; j++)
        {
            int i = this.identifiers.IndexOf(identifiers[j]);

            if (message == this.identifiers[i])
            {
                message = values[i];

                continue;
            }

            string gap = "";

            for (int k = 0; k < values[i].Length; k++)
            {
                gap += " ";
            }

            int index = tempMessage.IndexOf(" " + this.identifiers[i] + " ");

            if (index != -1)
            {
                message = message.Remove(index + 1, this.identifiers[i].Length);

                message = message.Insert(index + 1, values[i]);

                tempMessage = tempMessage.Remove(index + 1, this.identifiers[i].Length);

                tempMessage = tempMessage.Insert(index + 1, gap);

                j--;

                continue;
            }

            index = tempMessage.IndexOf(this.identifiers[i] + " ");

            if (index == 0)
            {
                message = message.Remove(index, this.identifiers[i].Length);

                message = message.Insert(index, values[i]);

                tempMessage = tempMessage.Remove(index, this.identifiers[i].Length);

                tempMessage = tempMessage.Insert(index, gap);

                j--;

                continue;
            }

            index = tempMessage.IndexOf(" " + this.identifiers[i]);

            if (index == message.Length - this.identifiers[i].Length - 1)
            {
                message = message.Remove(index + 1, this.identifiers[i].Length);

                message = message.Insert(index + 1, values[i]);

                tempMessage = tempMessage.Remove(index + 1, this.identifiers[i].Length);

                tempMessage = tempMessage.Insert(index + 1, gap);

                j--;

                continue;
            }
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

        int index = values.IndexOf(identifier);

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

        int index = identifiers.IndexOf(value);

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
    public string RemoveWhitespace(string value)
    {
        if (value == " ")
        {
            return "";
        }

        for (int i = 0; i < whitespaceCharacters.Count; i++)
        {
            value = value.Replace(whitespaceCharacters[i], ' ');
        }

        while (value[0] == ' ')
        {
            value = value.Remove(0, 1);
        }

        while (value[value.Length - 1] == ' ')
        {
            value = value.Remove(value.Length - 1, 1);
        }

        return value;
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
