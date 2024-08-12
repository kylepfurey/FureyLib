
// Static Time Functions Script
// by Kyle Furey

#pragma once
#include <chrono>
#include <ctime>

// Include this heading to use the library
#include "time.h"

// Tracks the change in time between function calls.
class time
{
private:

	// TIME VARIABLES

	// The date and time of when the program started.
	static std::clock_t begin;

	// The date and time of the last time update.
	static std::clock_t clock;

	// The time in seconds since the last time update.
	static double delta;

	// The number of time updates that has occurred since the program was started.
	static long updates;

	// The elapsed time since the program started.
	static double elapsed;

	// The current frame rate of the program.
	static double frames;

public:

	// TIME FUNCTIONS

	// •  Initializes the time variables.
	// •  Call this at the start of your program or to restart the time tracking.
	// •  Call update() to update the time variables.
	// •  Returns the current date and time.
	static auto start()
	{
		clock = std::clock();

		delta = 0;

		updates = 0;

		elapsed = 0;

		frames = 0;

		return clock;
	}

	// •  Updates the time variables.
	// •  Call this function at the start of each tick of your program.
	// •  Returns the time in seconds since the last time update.
	static double update()
	{
		delta = (std::clock() - clock) / (double)CLOCKS_PER_SEC;

		clock = std::clock();

		updates++;

		elapsed = (clock / (double)CLOCKS_PER_SEC);

		frames = (updates / elapsed);

		return delta;
	}


	// GETTERS

	// The date and time of when the program started.
	static auto start_time()
	{
		return begin;
	}

	// The current date and time.
	static auto current_time()
	{
		return std::chrono::system_clock::now();
	}

	// The date and time of the last time update.
	static auto clock_time()
	{
		return clock;
	}

	// The time in seconds since the last time update.
	static double delta_time()
	{
		return delta;
	}

	// The number of time updates that has occurred since the program was started.
	static long update_count()
	{
		return updates;
	}

	// The elapsed time since the program started.
	static double elapsed_time()
	{
		return elapsed;
	}

	// The current frame rate of the program.
	static double frame_rate()
	{
		return frames;
	}
};

// Static variable initialization.
std::clock_t time::begin = std::clock();
std::clock_t time::clock = std::clock();
double time::delta = 0;
long time::updates = 0;
double time::elapsed = 0;
double time::frames = 0;
