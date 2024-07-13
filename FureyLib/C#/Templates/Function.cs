
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
