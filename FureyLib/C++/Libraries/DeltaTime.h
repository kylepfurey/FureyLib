
// Delta Time Script
// by Kyle FUrey

#pragma once
#include <chrono>

// Include this heading to use the class
#include "DeltaTime.h"


// DELTA TIME VARIABLES

// The current elapsed time in clock time (not in seconds)
static std::clock_t clock_time = std::clock();

// The time in seconds since the last time the loop was called
static double delta_time = 0;

// The number of loops that has occured since the program was started
static int loop_count = 0;

// The elapsed time since the program started
static double elapsed_time = 0;

// The current frame rate of the program
static double frame_rate = 0;


// DELTA TIME FUNCTIONS

// Updates the current delta time and returns it (call once at the start of each main tick)
static double update_delta_time()
{
    delta_time = (std::clock() - clock_time) / (double)CLOCKS_PER_SEC;

    clock_time = std::clock();

    loop_count++;

    elapsed_time = (clock_time / (double)CLOCKS_PER_SEC);

    frame_rate = (loop_count / elapsed_time);

    return delta_time;
}

// Get the time in seconds since delta time was last updated
static double get_delta_time()
{
    return delta_time;
}

// Get the number of loops since the program started
static int get_loop_count()
{
    return loop_count;
}

// Get the time in seconds since the program started
static double get_elapsed_time()
{
    return elapsed_time;
}

// Get the current frames per second of the program
static double get_frame_rate()
{
    return frame_rate;
}


// DELTA TIME VARIABLES

// The current elapsed time in clock time (not in seconds)
static std::clock_t clockTime = std::clock();

// The time in seconds since the last time the loop was called
static double deltaTime = 0;

// The number of loops that has occured since the program was started
static int loopCount = 0;

// The elapsed time since the program started
static double elapsedTime = 0;

// The current frame rate of the program
static double frameRate = 0;


// DELTA TIME FUNCTIONS

// Updates the current delta time and returns it (call at the start of each main tick)
static double UpdateDeltaTime()
{
    deltaTime = (std::clock() - clockTime) / (double)CLOCKS_PER_SEC;

    clockTime = std::clock();

    loopCount++;

    elapsedTime = (clockTime / (double)CLOCKS_PER_SEC);

    frameRate = (loopCount / elapsedTime);

    return deltaTime;
}

// Get the time in seconds since delta time was last updated
static double GetDeltaTime()
{
    return deltaTime;
}

// Get the number of loops since the program started
static int GetLoopCount()
{
    return loopCount;
}

// Get the time in seconds since the program started
static double GetElapsedTime()
{
    return elapsedTime;
}

// Get the current frames per second of the program
static double GetFrameRate()
{
    return frameRate;
}
