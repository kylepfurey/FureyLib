
// Static Delta Time Functions Script
// by Kyle FUrey

#pragma once
#include <chrono>

// Include this heading to use the library
#include "DeltaTime.h"

// Tracks the change in time between function calls.
class delta_time
{
private:

	// DELTA TIME VARIABLES

	// The current elapsed time in clock time (not in seconds)
	static std::clock_t clock_time;

	// The time in seconds since the last time the loop was called
	static double delta_time;

	// The number of loops that has occured since the program was started
	static int loop_count;

	// The elapsed time since the program started
	static double elapsed_time;

	// The current frame rate of the program
	static double frame_rate;

public:

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
};

// Static variable initialization
std::clock_t delta_time::clock_time = std::clock();
double delta_time::delta_time = 0;
int delta_time::loop_count = 0;
double delta_time::elapsed_time = 0;
double delta_time::frame_rate = 0;

// Tracks the change in time between function calls.
class DeltaTime
{
private:

	// DELTA TIME VARIABLES

	// The current elapsed time in clock time (not in seconds)
	static std::clock_t clockTime;

	// The time in seconds since the last time the loop was called
	static double deltaTime;

	// The number of loops that has occured since the program was started
	static int loopCount;

	// The elapsed time since the program started
	static double elapsedTime;

	// The current frame rate of the program
	static double frameRate;

public:

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
};

// Static variable initialization
std::clock_t DeltaTime::clock_time = std::clock();
double DeltaTime::delta_time = 0;
int DeltaTime::loop_count = 0;
double DeltaTime::elapsed_time = 0;
double DeltaTime::frame_rate = 0;
