
// Static Asynchronous Functions Script
// by Kyle Furey

#pragma once
#include <thread>
#include <future>
#include <chrono>

// Include this heading to use the library
#include "Async.h"

// Represents a referenced bool that can be used to indicate when an asynchronous function has completed.
#define TASK std::future<bool> 

// Await keyword used to await a task, result, or condition.
#define AWAIT(task) async::await(task);

// Creates a lambda expression with the given captures and code.
#define LAMBDA(...) [__VA_ARGS__] () mutable -> void

// Represents a void function pointer either with or without parameters.
#define METHOD(variable) void (*variable) (ParameterTypes...)

// Represents a function pointer with a return type either with or without parameters.
#define FUNCTION(variable) ReturnType (*variable) (ParameterTypes...)

// Creates and runs asynchronous tasks.
class async
{
public:

	// RUN FUNCTION

	// Runs the given function asynchronously
	template <typename ... ParameterTypes> static std::future<bool> run(METHOD(function), ParameterTypes... parameters)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				function(parameters...);

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Runs the given function asynchronously and returns a future with its result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> run(FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			LAMBDA(=, &promise)
			{
				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

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

	// Delays the current thread by one tick when awaited
	static std::future<bool> delay_for_tick()
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				std::this_thread::yield();

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given void function after one tick
	template <typename ... ParameterTypes> static std::future<bool> invoke_after_tick(METHOD(function), ParameterTypes... parameters)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				std::this_thread::yield();

				function(parameters...);

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given function after one tick and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> invoke_after_tick(FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			LAMBDA(=, &promise)
			{
				std::this_thread::yield();

				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

		return promise->get_future();
	}


	// DELAY FOR TICKS

	// Delays the current thread by the given number of ticks when awaited
	static std::future<bool> delay_for_ticks(int number_of_ticks)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				for (int i = 0; i < number_of_ticks; i++)
				{
					std::this_thread::yield();
				}

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given void function after the given number of ticks
	template <typename ... ParameterTypes> static std::future<bool> invoke_after_ticks(int number_of_ticks, METHOD(function), ParameterTypes... parameters)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				for (int i = 0; i < number_of_ticks; i++)
				{
					std::this_thread::yield();
				}

				function(parameters...);

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given function after the given number of ticks and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> invoke_after_ticks(int number_of_ticks, FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			LAMBDA(=, &promise)
			{
				for (int i = 0; i < number_of_ticks; i++)
				{
					std::this_thread::yield();
				}

				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

		return promise->get_future();
	}


	// DELAY FOR MILLISECONDS

	// Delays the current thread by the given number of milliseconds when awaited
	static std::future<bool> delay_for_milliseconds(int milliseconds)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given void function after the given number of milliseconds
	template <typename ... ParameterTypes> static std::future<bool> invoke_after_milliseconds(int milliseconds, METHOD(function), ParameterTypes... parameters)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

				function(parameters...);

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given function after the given number of milliseconds and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> invoke_after_milliseconds(int milliseconds, FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			LAMBDA(=, &promise)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

		return promise->get_future();
	}


	// DELAY FOR SECONDS

	// Delays the current thread by the given number of seconds when awaited
	static std::future<bool> delay_for_seconds(float seconds)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(to_milliseconds(seconds)));

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given void function after the given number of seconds
	template <typename ... ParameterTypes> static std::future<bool> invoke_after_seconds(float seconds, METHOD(function), ParameterTypes... parameters)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(to_milliseconds(seconds)));

				function(parameters...);

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given function after the given number of seconds and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> invoke_after_seconds(float seconds, FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			LAMBDA(=, &promise)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(to_milliseconds(seconds)));;

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
		while (!condition) { }
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
	template <typename ... ParameterTypes> static std::future<bool> Run(METHOD(function), ParameterTypes... parameters)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				function(parameters...);

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Runs the given function asynchronously and returns a future with its result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> Run(FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			LAMBDA(=, &promise)
			{
				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

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

	// Delays the current thread by one tick when awaited
	static std::future<bool> DelayForTick()
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				std::this_thread::yield();

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given void function after one tick
	template <typename ... ParameterTypes> static std::future<bool> InvokeAfterTick(METHOD(function), ParameterTypes... parameters)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				std::this_thread::yield();

				function(parameters...);

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given function after one tick and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> InvokeAfterTick(FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			LAMBDA(=, &promise)
			{
				std::this_thread::yield();

				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

		return promise->get_future();
	}


	// DELAY FOR TICKS

	// Delays the current thread by the given number of ticks when awaited
	static std::future<bool> DelayForTicks(int number_of_ticks)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				for (int i = 0; i < number_of_ticks; i++)
				{
					std::this_thread::yield();
				}

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given void function after the given number of ticks
	template <typename ... ParameterTypes> static std::future<bool> InvokeAfterTicks(int number_of_ticks, METHOD(function), ParameterTypes... parameters)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				for (int i = 0; i < number_of_ticks; i++)
				{
					std::this_thread::yield();
				}

				function(parameters...);

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given function after the given number of ticks and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> InvokeAfterTicks(int number_of_ticks, FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			LAMBDA(=, &promise)
			{
				for (int i = 0; i < number_of_ticks; i++)
				{
					std::this_thread::yield();
				}

				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

		return promise->get_future();
	}


	// DELAY FOR MILLISECONDS

	// Delays the current thread by the given number of milliseconds when awaited
	static std::future<bool> DelayForMilliseconds(int milliseconds)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given void function after the given number of milliseconds
	template <typename ... ParameterTypes> static std::future<bool> InvokeAfterMilliseconds(int milliseconds, METHOD(function), ParameterTypes... parameters)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

				function(parameters...);

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given function after the given number of milliseconds and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> InvokeAfterMilliseconds(int milliseconds, FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			LAMBDA(=, &promise)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

				promise->set_value(function(parameters...));

				delete promise;

				promise = nullptr;
			}
		);

		delay.detach();

		return promise->get_future();
	}


	// DELAY FOR SECONDS

	// Delays the current thread by the given number of seconds when awaited
	static std::future<bool> DelayForSeconds(float seconds)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(ToMilliseconds(seconds)));

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given void function after the given number of seconds
	template <typename ... ParameterTypes> static std::future<bool> InvokeAfterSeconds(float seconds, METHOD(function), ParameterTypes... parameters)
	{
		std::promise<bool>* complete = new std::promise<bool>();

		std::thread delay
		(
			LAMBDA(=, &complete)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(ToMilliseconds(seconds)));

				function(parameters...);

				complete->set_value(true);

				delete complete;

				complete = nullptr;
			}
		);

		delay.detach();

		return complete->get_future();
	}

	// Invokes the given function after the given number of seconds and returns the result
	template <typename ReturnType, typename ... ParameterTypes> static std::future<ReturnType> InvokeAfterSeconds(float seconds, FUNCTION(function), ParameterTypes... parameters)
	{
		std::promise<ReturnType>* promise = new std::promise<ReturnType>();

		std::thread delay
		(
			LAMBDA(=, &promise)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(ToMilliseconds(seconds)));

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
		while (!condition) { }
	}

	// Delays the current thread until the given future is ready and returns the future's result
	template <typename ReturnType> static ReturnType Await(std::future<ReturnType> future)
	{
		return future.get();
	}

	// Delays the current thread until the given future is ready and returns the future's result
	template <typename ReturnType> static ReturnType Awaitref(std::future<ReturnType>& future)
	{
		return future.get();
	}
};
