
// Static Print Functions Script
// by Kyle Furey

using System;

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
    public static void print(object message)
    {
        Console.WriteLine(message.ToString());
    }

    /// <summary>
    /// Prints messages to the console
    /// </summary>
    /// <param name="messages"></param>
    public static void print(params object[] messages)
    {
        for (int i = 0; i < messages.Length; i++)
        {
            Console.Write(messages[i].ToString() + " ");
        }

        Console.WriteLine();
    }
}
