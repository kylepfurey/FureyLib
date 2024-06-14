
// Static Asynchronous Functions Script
// by Kyle Furey

#pragma once
#include <thread>
#include <future>
#include <chrono>

// Include this heading to use the library
#include "Async.h"

// Define the lambda expression
#define _LAMBDA(captures) [captures] () mutable -> void

// Define the method data type
#define _METHOD(variable) void (*variable) (ParameterTypes...)

// Define the function data type
#define _FUNCTION(variable) ReturnType (*variable) (ParameterTypes...)

// Creates and runs asynchronous tasks.
class async
{
public:

	// RUN FUNCTION

	// Runs the given function asynchronously
	template <typename ... ParameterTypes> static void run(_METHOD(function), ParameterTypes... parameters)
	{
		std::thread async
		(
			_LAMBDA(=)
			{
				function(parameters...);
			}
		);

		async.detach();
	}

	// Runs the given function asynchronously and returns a future with its result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> run(_FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread async
		(
			_LAMBDA(=)
			{
				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		async.detach();

		return promise->get_future();
	}


	// CONVERT TO SECONDS

	// Converts the given number of seconds to a count of milliseconds
	static int to_milliseconds(float seconds)
	{
		return (int)(1000 * seconds);
	}

	// Converts the given number of milliseconds to a count of seconds
	static float to_seconds(int milliseconds)
	{
		return milliseconds / 1000;
	}


	// DELAY FOR ONE TICK

	// Delays the current thread by one tick
	static void delay_for_tick()
	{
		std::this_thread::yield();
	}

	// Invokes the given void function after one tick
	template <typename ... ParameterTypes> static void invoke_after_tick(_METHOD(function), ParameterTypes... parameters)
	{
		std::thread delay
		(
			_LAMBDA(=)
			{
				delay_for_tick();

				function(parameters...);
			}
		);

		delay.detach();
	}

	// Invokes the given function after one tick and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> invoke_after_tick(_FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			_LAMBDA(=)
			{
				delay_for_tick();

				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

		return promise->get_future();
	}


	// DELAY FOR TICKS

	// Delays the current thread by the given number of ticks
	static void delay_for_ticks(int number_of_ticks)
	{
		for (int i = 0; i < number_of_ticks; i++)
		{
			std::this_thread::yield();
		}
	}

	// Invokes the given void function after the given number of ticks
	template <typename ... ParameterTypes> static void invoke_after_ticks(int number_of_ticks, _METHOD(function), ParameterTypes... parameters)
	{
		std::thread delay
		(
			_LAMBDA(=)
			{
				delay_for_ticks(number_of_ticks);

				function(parameters...);
			}
		);

		delay.detach();
	}

	// Invokes the given function after the given number of ticks and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> invoke_after_ticks(int number_of_ticks, _FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			_LAMBDA(=)
			{
				delay_for_ticks(number_of_ticks);

				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

		return promise->get_future();
	}


	// DELAY FOR MILLISECONDS

	// Delays the current thread by the given number of milliseconds
	static void delay_for_milliseconds(int milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

	// Invokes the given void function after the given number of milliseconds
	template <typename ... ParameterTypes> static void invoke_after_milliseconds(int milliseconds, _METHOD(function), ParameterTypes... parameters)
	{
		std::thread delay
		(
			_LAMBDA(=)
			{
				delay_for_milliseconds(milliseconds);

				function(parameters...);
			}
		);

		delay.detach();
	}

	// Invokes the given function after the given number of milliseconds and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> invoke_after_milliseconds(int milliseconds, _FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			_LAMBDA(=)
			{
				delay_for_milliseconds(milliseconds);

				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

		return promise->get_future();
	}


	// DELAY FOR SECONDS

	// Delays the current thread by the given number of seconds
	static void delay_for_seconds(float seconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(to_milliseconds(seconds)));
	}

	// Invokes the given void function after the given number of seconds
	template <typename ... ParameterTypes> static void invoke_after_seconds(float seconds, _METHOD(function), ParameterTypes... parameters)
	{
		std::thread delay
		(
			_LAMBDA(=)
			{
				delay_for_seconds(seconds);

				function(parameters...);
			}
		);

		delay.detach();
	}

	// Invokes the given function after the given number of seconds and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> invoke_after_seconds(float seconds, _FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			_LAMBDA(=)
			{
				delay_for_seconds(seconds);

				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

		return promise->get_future();
	}


	// AWAIT

	// Delays the current thread until the given condition is met
	static void await(bool& condition)
	{
		while (!condition) { std::this_thread::yield(); }
	}

	// Delays the current thread until the given future is ready and returns the future's result
	template <typename ReturnType> static ReturnType await(std::future<ReturnType> future)
	{
		return future.get();
	}

	// Delays the current thread until the given future is ready and returns the future's result
	template <typename ReturnType> static ReturnType awaitref(std::future<ReturnType>& future)
	{
		return future.get();
	}
};

// Creates and runs asynchronous tasks.
class Async
{
public:

	// RUN FUNCTION

	// Runs the given function asynchronously
	template <typename ... ParameterTypes> static void Run(_METHOD(function), ParameterTypes... parameters)
	{
		std::thread async
		(
			_LAMBDA(=)
			{
				function(parameters...);
			}
		);

		async.detach();
	}

	// Runs the given function asynchronously and returns a future with its result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> Run(_FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread async
		(
			_LAMBDA(=)
			{
				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		async.detach();

		return promise->get_future();
	}


	// CONVERT TO SECONDS

	// Converts the given number of seconds to a count of milliseconds
	static int ToMilliseconds(float seconds)
	{
		return (int)(1000 * seconds);
	}

	// Converts the given number of milliseconds to a count of seconds
	static float ToSeconds(int milliseconds)
	{
		return milliseconds / 1000;
	}


	// DELAY FOR ONE TICK

	// Delays the current thread by one tick
	static void DelayForTick()
	{
		std::this_thread::yield();
	}

	// Invokes the given void function after one tick
	template <typename ... ParameterTypes> static void InvokeAfterTick(_METHOD(function), ParameterTypes... parameters)
	{
		std::thread delay
		(
			_LAMBDA(=)
			{
				DelayForTick();

				function(parameters...);
			}
		);

		delay.detach();
	}

	// Invokes the given function after one tick and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> InvokeAfterTick(_FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			_LAMBDA(=)
			{
				DelayForTick();

				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

		return promise->get_future();
	}


	// DELAY FOR TICKS

	// Delays the current thread by the given number of ticks
	static void DelayForTicks(int number_of_ticks)
	{
		for (int i = 0; i < number_of_ticks; i++)
		{
			std::this_thread::yield();
		}
	}

	// Invokes the given void function after the given number of ticks
	template <typename ... ParameterTypes> static void InvokeAfterTicks(int number_of_ticks, _METHOD(function), ParameterTypes... parameters)
	{
		std::thread delay
		(
			_LAMBDA(=)
			{
				DelayForTicks(number_of_ticks);

				function(parameters...);
			}
		);

		delay.detach();
	}

	// Invokes the given function after the given number of ticks and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> InvokeAfterTicks(int number_of_ticks, _FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			_LAMBDA(=)
			{
				DelayForTicks(number_of_ticks);

				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

		return promise->get_future();
	}


	// DELAY FOR MILLISECONDS

	// Delays the current thread by the given number of milliseconds
	static void DelayForMilliseconds(int milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

	// Invokes the given void function after the given number of milliseconds
	template <typename ... ParameterTypes> static void InvokeAfterMilliseconds(int milliseconds, _METHOD(function), ParameterTypes... parameters)
	{
		std::thread delay
		(
			_LAMBDA(=)
			{
				DelayForMilliseconds(milliseconds);

				function(parameters...);
			}
		);

		delay.detach();
	}

	// Invokes the given function after the given number of milliseconds and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> InvokeAfterMilliseconds(int milliseconds, _FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			_LAMBDA(=)
			{
				DelayForMilliseconds(milliseconds);

				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

		return promise->get_future();
	}


	// DELAY FOR SECONDS

	// Delays the current thread by the given number of seconds
	static void DelayForSeconds(float seconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(ToMilliseconds(seconds)));
	}

	// Invokes the given void function after the given number of seconds
	template <typename ... ParameterTypes> static void InvokeAfterSeconds(float seconds, _METHOD(function), ParameterTypes... parameters)
	{
		std::thread delay
		(
			_LAMBDA(=)
			{
				DelayForSeconds(seconds);

				function(parameters...);
			}
		);

		delay.detach();
	}

	// Invokes the given function after the given number of seconds and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> InvokeAfterSeconds(float seconds, _FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			_LAMBDA(=)
			{
				DelayForSeconds(seconds);

				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

		return promise->get_future();
	}


	// AWAIT

	// Delays the current thread until the given condition is met
	static void Await(bool& condition)
	{
		while (!condition) { std::this_thread::yield(); }
	}

	// Delays the current thread until the given future is ready and returns the future's result
	template <typename ReturnType> static ReturnType Await(std::future<ReturnType> future)
	{
		return future.get();
	}

	// Delays the current thread until the given future is ready and returns the future's result
	template <typename ReturnType> static ReturnType AwaitReference(std::future<ReturnType>& future)
	{
		return future.get();
	}
};
