
// Static Delta Time Functions Script
// by Kyle Furey

using System;

// Include this heading to use the library
using static DeltaTime;

// Tracks the change in time between function calls.
public static class DeltaTime
{
    // DELTA TIME VARIABLES

    /// <summary>
    /// The current real time
    /// </summary>
    public static DateTime clockTime = DateTime.Now;

    /// <summary>
    /// The time in seconds since the last time the loop was called
    /// </summary>
    public static double deltaTime = 0;

    /// <summary>
    /// The number of loops that has occured since the program was started
    /// </summary>
    public static int loopCount = 0;

    /// <summary>
    /// The date and time from when the program started
    /// </summary>
    public static DateTime startDateAndTime = DateTime.Now;

    /// <summary>
    /// The elapsed time since the program started
    /// </summary>
    public static double elapsedTime = 0;

    /// <summary>
    /// The current frame rate of the program
    /// </summary>
    public static double frameRate = 0;


    // DELTA TIME FUNCTIONS

    /// <summary>
    /// Updates the current delta time and returns it (call once at the start of each main tick)
    /// </summary>
    /// <returns></returns>
    public static double UpdateDeltaTime()
    {
        deltaTime = (DateTime.Now - clockTime).TotalSeconds;

        clockTime = DateTime.Now;

        loopCount++;

        elapsedTime = (clockTime - startDateAndTime).TotalSeconds;

        frameRate = (loopCount / elapsedTime);

        return deltaTime;
    }

    /// <summary>
    /// Get the time in seconds since delta time was last updated
    /// </summary>
    /// <returns></returns>
    public static double GetDeltaTime()
    {
        return deltaTime;
    }

    /// <summary>
    /// Get the number of loops since the program started
    /// </summary>
    /// <returns></returns>
    public static int GetLoopCount()
    {
        return loopCount;
    }

    /// <summary>
    /// Get the time in seconds since the program started
    /// </summary>
    /// <returns></returns>
    public static double GetElapsedTime()
    {
        return elapsedTime;
    }

    /// <summary>
    /// Get the current frames per second of the program
    /// </summary>
    /// <returns></returns>
    public static double GetFrameRate()
    {
        return frameRate;
    }

    /// <summary>
    /// Get the date and time from when the program started
    /// </summary>
    /// <returns></returns>
    public static DateTime GetStartDateAndTime()
    {
        return startDateAndTime;
    }
}
