
// Static Print Functions Script
// by Kyle Furey

using UnityEngine;

// Include this heading to use the library
using static Print;

/// <summary>
/// Prints messages to the console.
/// </summary>
public static class Print
{
    /// <summary>
    /// Prints a message to the console
    /// </summary>
    /// <param name="message"></param>
    public static string print(object message)
    {
        message = message.ToString();

        Debug.Log(message);

        return (string)message;
    }

    /// <summary>
    /// Prints messages to the console
    /// </summary>
    /// <param name="messages"></param>
    public static string print(params object[] messages)
    {
        string message = "";

        for (int i = 0; i < messages.Length; i++)
        {
            message += messages[i].ToString() + " ";
        }

        Debug.Log(message);

        return message;
    }
}
