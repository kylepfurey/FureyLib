
// Template Static Function Library Script
// by Kyle Furey

using System;
using System.Collections;
using System.Collections.Generic;

// Include this heading to use the class
using static Function;

/// <summary>
/// Static function library.
/// </summary>
public static class Function
{
    /// <summary>
    /// Example function
    /// </summary>
    public static void Function()
    {
        Console.WriteLine("Function called!");
    }

    /// <summary>
    /// Prints a message to the console
    /// </summary>
    /// <param name="message"></param>
    public static string print(object message)
    {
        message = message.ToString();

        Console.WriteLine(message);

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

        Console.WriteLine(message);

        return message;
    }
}
