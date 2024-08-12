
// Static Time Functions Script
// by Kyle Furey

using System;

// Include this heading to use the library
using static Time;

/// <summary>
/// Tracks the change in time between function calls.
/// </summary>
public static class Time
{
    // TIME VARIABLES

    /// <summary>
    /// The date and time of when the program started.
    /// </summary>
    public static DateTime startTime { get; private set; }

    /// <summary>
    /// The current date and time.
    /// </summary>
    public static DateTime currentTime { get => DateTime.Now; }

    /// <summary>
    /// The date and time of the last time update.
    /// </summary>
    public static DateTime clockTime { get; private set; }

    /// <summary>
    /// The time in seconds since the last time update.
    /// </summary>
    public static double deltaTime { get; private set; }

    /// <summary>
    /// The number of time updates that has occurred since the program was started.
    /// </summary>
    public static long updateCount { get; private set; }

    /// <summary>
    /// The elapsed time since the program started.
    /// </summary>
    public static double elapsedTime { get; private set; }

    /// <summary>
    /// The current frame rate of the program.
    /// </summary>
    public static double frameRate { get; private set; }


    // STATIC CONSTRUCTOR

    /// <summary>
    /// Sets the start time.
    /// </summary>
    static Time()
    {
        startTime = DateTime.Now;
    }


    // TIME FUNCTIONS

    /// <summary>
    /// •  Initializes the time variables.<br/>
    /// •  Call this at the start of your program or to restart the time tracking.<br/>
    /// •  Call Update() to update the time variables.
    /// </summary>
    /// <returns>The current date and time.</returns>
    public static DateTime Start()
    {
        clockTime = DateTime.Now;

        deltaTime = 0;

        updateCount = 0;

        elapsedTime = 0;

        frameRate = 0;

        return clockTime;
    }

    /// <summary>
    /// •  Updates the time variables.<br/>
    /// •  Call this function at the start of each tick of your program.
    /// </summary>
    /// <returns>The time in seconds since the last time update.</returns>
    public static double Update()
    {
        deltaTime = (DateTime.Now - clockTime).TotalSeconds;

        clockTime = DateTime.Now;

        updateCount++;

        elapsedTime = (clockTime - DateTime.Now).TotalSeconds;

        frameRate = (updateCount / elapsedTime);

        return deltaTime;
    }
}
