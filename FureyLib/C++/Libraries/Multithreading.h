
// Static Multithreading Functions Script
// by Kyle Furey

#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <thread>
#include <chrono>

// Include this heading to use the library
#include "Multithreading.h"

// Shorthand for std::find().
#define FIND(vector, element) std::find(vector.begin(), vector.end(), element)

// Creates a lambda expression with the given captures and code.
#define LAMBDA(captures) [captures] () mutable -> void

// Thread starting behaviour enum.
enum thread_start
{
	// thread_state :: lock  =  Starts the thread in a locked state.
	lock = 0,

	// thread_state :: detach  =  Detaches and runs the thread asynchronously immediately.
	detach = 1,

	// thread_state :: join  =  Joins and runs the thread immediately before the current thread continues.
	join = 2
};

// Creates and manages multiple threads of code.
class multithreading
{
private:

	// THREADS

	// All of the program's currently active threads
	static std::vector<std::thread> threads;

	// The ids of each active thread with a pointer to the thread
	static std::vector<std::thread::id> thread_ids;

	// The names of each active thread
	static std::vector<std::string> thread_names;

	// All of the ids to the program's currently running threads
	static std::vector<std::thread::id> running_threads;

	// All of the ids to the running threads' cancellation tokens (KEY = THREAD ID, VALUE = CANCELLED)
	static std::map<std::thread::id, bool> cancellation_tokens;

	// All of the ids of the running threads' locking threads (KEY = LOCKED THREAD, VALUE = THREAD LOCKING KEY)
	static std::map<std::thread::id, std::thread::id> locked_threads;

	// A pointer to an empty thread that represents the presence of the main thread
	static std::thread* _main;

	// The id of the main thread
	static std::thread::id main_thread_id;


	// FIND FUNCTION

	// Finds the index of the given thread
	static int find(std::thread& thread)
	{
		for (int i = 0; i < threads.size(); i++)
		{
			if (&threads[i] == &thread)
			{
				return i;
			}
		}

		return -1;
	}

	// Finds the index of the given thread id
	static int find(std::thread::id id)
	{
		for (int i = 0; i < thread_ids.size(); i++)
		{
			if (thread_ids[i] == id)
			{
				return i;
			}
		}
	}

	// Finds the index of the given name
	static int find(std::string name)
	{
		for (int i = 0; i < thread_names.size(); i++)
		{
			if (thread_names[i] == name)
			{
				return i;
			}
		}

		return -1;
	}


	// MAIN THREAD

	// Stores the main thread (automatically called)
	static void set_main_thread()
	{
		main_thread_id = std::this_thread::get_id();

		threads.emplace_back(main_thread_id);

		_main = &threads[0];

		thread_ids.push_back(main_thread_id);

		thread_names.push_back("Main Thread");

		running_threads.push_back(main_thread_id);

		cancellation_tokens[main_thread_id] = false;
	}

public:

	// CONSTRUCTOR

	// Marks and stores the main thread when the program starts
	multithreading()
	{
		set_main_thread();
	}


	// GETTERS

	// Returns the first active thread of the given name (the thread must have been assigned a name on creation)
	static std::thread& get(std::string name)
	{
		return threads[find(name)];
	}

	// Returns the active thread at the given index
	static std::thread& get(int index)
	{
		return threads[index];
	}

	// Returns the active thread of the given id
	static std::thread& get(std::thread::id id)
	{
		return threads[find(id)];
	}

	// Returns the first active thread's id of the given name (the thread must have been assigned a name on creation)
	static std::thread::id get_id(std::string name)
	{
		return thread_ids[find(name)];
	}

	// Returns the active thread's id at the given index
	static std::thread::id get_id(int index)
	{
		return thread_ids[index];
	}

	// Returns the id of the given thread
	static std::thread::id get_id(std::thread& thread)
	{
		return thread_ids[find(thread)];
	}

	// Returns a vector of pointers to all the active threads
	static std::vector<std::thread*> get_threads()
	{
		std::vector<std::thread*> pointers = std::vector<std::thread*>();

		for (int i = 0; i < threads.size(); i++)
		{
			pointers.push_back(&threads[i]);
		}

		return pointers;
	}

	// Returns a vector of all the active threads' ids
	static std::vector<std::thread::id> get_thread_ids()
	{
		return thread_ids;
	}

	// Returns a vector of all the active threads' names
	static std::vector<std::string> get_thread_names()
	{
		return thread_names;
	}

	// Returns a vector of the ids of the active and running threads in order
	static std::vector<std::thread::id> get_running_threads()
	{
		return running_threads;
	}

	// Returns a map of the ids of the currently locked threads to what thread is locking them
	static std::map<std::thread::id, std::thread::id> get_locked_threads()
	{
		return locked_threads;
	}

	// Returns the total number of active threads 
	static int active_count()
	{
		return threads.size();
	}

	// Returns the total number of running threads 
	static int running_count()
	{
		return threads.size();
	}

	// Get the name of the current running thread
	static std::string get_name()
	{
		return thread_names[find(std::this_thread::get_id())];
	}

	// Get the name of the given thread
	static std::string get_name(std::thread& thread)
	{
		return thread_names[find(thread)];
	}

	// Get the name of the given thread by id
	static std::string get_name(std::thread::id id)
	{
		return thread_names[find(id)];
	}

	// Get the name of the given thread by index
	static std::string get_name(int index)
	{
		return thread_names[index];
	}

	// Get the program's main thread's id
	static std::thread::id main_id()
	{
		return main_thread_id;
	}

	// Get the current running thread
	static std::thread& current()
	{
		return threads[find(std::this_thread::get_id())];
	}

	// Get the current running thread's id
	static std::thread::id current_id()
	{
		return std::this_thread::get_id();
	}

	// Get the total number of logical processors on this device
	static int number_of_processors()
	{
		return std::thread::hardware_concurrency();
	}


	// ACTIVE AND RUNNING

	// Returns whether the given thread is currently active
	static bool is_active(std::thread& thread)
	{
		return find(thread) != -1;
	}

	// Returns whether the given thread by id is currently active
	static bool is_active(std::thread::id id)
	{
		return find(id) != -1;
	}

	// Returns whether the given thread is currently running
	static bool is_running(std::thread& thread)
	{
		return !thread.joinable();
	}

	// Returns whether the given thread by id is currently running
	static bool is_running(std::thread::id id)
	{
		return !threads[find(id)].joinable();
	}

	// Returns whether the given thread is active and not currently running (and therefore can be started)
	static bool is_ready(std::thread& thread)
	{
		return is_active(thread) && !is_running(thread);
	}

	// Returns whether the given thread by id is active and not currently running (and therefore can be started)
	static bool is_ready(std::thread::id id)
	{
		return is_active(id) && !is_running(id);
	}


	// LOCKING THREAD

	// Delays the current thread until the given condition is met
	static void block(bool& condition)
	{
		while (!condition) { std::this_thread::yield(); }
	}

	// Delays the current thread until it is is unlocked
	static void lock()
	{
		locked_threads[std::this_thread::get_id()] = std::thread::id();

		while (locked_threads.count(std::this_thread::get_id())) { std::this_thread::yield(); }

		locked_threads.erase(std::this_thread::get_id());
	}

	// Delays the current thread until the given thread completes or this thread is unlocked
	static void lock(std::thread& thread)
	{
		locked_threads[std::this_thread::get_id()] = thread_ids[find(thread)];

		while (locked_threads.count(std::this_thread::get_id()) && is_active(locked_threads[std::this_thread::get_id()])) { std::this_thread::yield(); }

		locked_threads.erase(std::this_thread::get_id());
	}

	// Delays the current thread until the given thread by id completes or this thread is unlocked
	static void lock(std::thread::id id)
	{
		locked_threads[std::this_thread::get_id()] = id;

		while (locked_threads.count(std::this_thread::get_id()) && is_active(locked_threads[std::this_thread::get_id()])) { std::this_thread::yield(); }

		locked_threads.erase(std::this_thread::get_id());
	}

	// Relocks the given locked thread to the current thread and return whether it was successful
	static bool relock(std::thread& locked_thread)
	{
		int index = find(locked_thread);

		if (locked_threads.count(thread_ids[index]))
		{
			locked_threads[thread_ids[index]] = std::this_thread::get_id();

			return true;
		}

		return false;
	}

	// Relocks the given locked thread by id to the current thread and return whether it was successful
	static bool relock(std::thread::id locked_id)
	{
		if (locked_threads.count(locked_id))
		{
			locked_threads[locked_id] = std::this_thread::get_id();

			return true;
		}

		return false;
	}

	// Relocks the given locked thread to the given thread and return whether it was successful
	static bool relock(std::thread& locked_thread, std::thread& thread)
	{
		int index = find(locked_thread);

		if (locked_threads.count(thread_ids[index]))
		{
			locked_threads[thread_ids[index]] = thread_ids[find(thread)];

			return true;
		}

		return false;
	}

	// Relocks the given locked thread by id to the given thread by id and return whether it was successful
	static bool relock(std::thread::id locked_id, std::thread::id id)
	{
		if (locked_threads.count(locked_id))
		{
			locked_threads[locked_id] = id;

			return true;
		}

		return false;
	}

	// Unlocks the given thread and returns whether it was successful
	static bool unlock(std::thread& unlocked_thread)
	{
		return locked_threads.erase(thread_ids[find(unlocked_thread)]);
	}

	// Unlocks the given thread by id and returns whether it was successful
	static bool unlock(std::thread::id unlocked_id)
	{
		return locked_threads.erase(unlocked_id);
	}

	// Returns whether the given thread is locked
	static bool is_locked(std::thread& thread)
	{
		return locked_threads.count(thread_ids[find(thread)]);
	}

	// Returns whether the given thread by id is locked
	static bool is_locked(std::thread::id id)
	{
		return locked_threads.count(id);
	}

	// Returns the thread that is locking the given thread
	static std::thread::id locked_by(std::thread& thread)
	{
		return locked_threads[thread_ids[find(thread)]];
	}

	// Returns the thread that is locking the given thread
	static std::thread::id locked_by(std::thread::id id)
	{
		return locked_threads[id];
	}


	// NEW THREADS

	// •  Creates a new thread that can run code independently of other threads.
	// •  method = The code this thread will execute.
	// •  Use a lambda expression "[] () . void { }" or the LAMBDA() { } macro to add code.
	// •  Returns a pointer to the newly created thread.
	static std::thread* new_thread(std::function<void()> method)
	{
		std::thread* new_thread;

		threads.emplace_back
		(
			LAMBDA(&)
			{
				std::this_thread::yield();

				int index = find(*new_thread);

				std::thread::id id = thread_ids[index];

				if (locked_threads.count(id))
				{
					lock(id);
				}

				running_threads.push_back(id);

				method();

				threads.erase(threads.begin() + index);

				thread_ids.erase(FIND(thread_ids, id));

				thread_names.erase(FIND(thread_names, thread_names[index]));

				running_threads.erase(FIND(running_threads, id));

				cancellation_tokens.erase(id);
			}
		);

		new_thread = &threads[threads.size()];

		thread_ids.push_back(new_thread->get_id());

		thread_names.push_back("New Thread");

		cancellation_tokens[new_thread->get_id()] = false;

		new_thread->detach();

		return new_thread;
	}

	// •  Creates a new thread that can run code independently of other threads.
	// •  start_behaviour = When to start the new thread.
	// •  method = The code this thread will execute.
	// •  Use a lambda expression "[] () . void { }" or the LAMBDA() { } macro to add code.
	// •  Returns a pointer to the newly created thread.
	static std::thread* new_thread(thread_start start_behaviour, std::function<void()> method)
	{
		std::thread* new_thread;

		threads.emplace_back
		(
			LAMBDA(&)
			{
				std::this_thread::yield();

				int index = find(*new_thread);

				std::thread::id id = thread_ids[index];

				if (locked_threads.count(id))
				{
					lock(id);
				}

				running_threads.push_back(id);

				method();

				threads.erase(threads.begin() + index);

				thread_ids.erase(FIND(thread_ids, id));

				thread_names.erase(FIND(thread_names, thread_names[index]));

				running_threads.erase(FIND(running_threads, id));

				cancellation_tokens.erase(id);
			}
		);

		new_thread = &threads[threads.size()];

		thread_ids.push_back(new_thread->get_id());

		thread_names.push_back("New Thread");

		cancellation_tokens[new_thread->get_id()] = false;

		switch (start_behaviour)
		{
		case thread_start::lock:

			locked_threads[new_thread->get_id()] = std::this_thread::get_id();

			new_thread->detach();

			break;

		case thread_start::detach:

			new_thread->detach();

			break;

		case thread_start::join:

			new_thread->join();

			break;
		}

		return new_thread;
	}

	// •  Creates a new thread that can run code independently of other threads.
	// •  start_behaviour = When to start the new thread.
	// •  name = The name of this thread.
	// •  method = The code this thread will execute.
	// •  Use a lambda expression "[] () . void { }" or the LAMBDA() { } macro to add code.
	// •  Returns a pointer to the newly created thread.
	static std::thread* new_thread(thread_start start_behaviour, std::string name, std::function<void()> method)
	{
		std::thread* new_thread;

		threads.emplace_back
		(
			LAMBDA(&)
			{
				std::this_thread::yield();

				int index = find(*new_thread);

				std::thread::id id = thread_ids[index];

				if (locked_threads.count(id))
				{
					lock(id);
				}

				running_threads.push_back(id);

				method();

				threads.erase(threads.begin() + index);

				thread_ids.erase(FIND(thread_ids, id));

				thread_names.erase(FIND(thread_names, thread_names[index]));

				running_threads.erase(FIND(running_threads, id));

				cancellation_tokens.erase(id);
			}
		);

		new_thread = &threads[threads.size()];

		thread_ids.push_back(new_thread->get_id());

		thread_names.push_back(name);

		cancellation_tokens[new_thread->get_id()] = false;

		switch (start_behaviour)
		{
		case thread_start::lock:

			locked_threads[new_thread->get_id()] = std::this_thread::get_id();

			new_thread->detach();

			break;

		case thread_start::detach:

			new_thread->detach();

			break;

		case thread_start::join:

			new_thread->join();

			break;
		}

		return new_thread;
	}

	// •  Creates a new thread that can run code independently of other threads.
	// •  followed_thread = The thread to follow this new thread after.
	// •  method = The code this thread will execute.
	// •  Use a lambda expression "[] () . void { }" or the LAMBDA() { } macro to add code.
	// •  Returns a pointer to the newly created thread.
	static std::thread* new_thread(std::thread& followed_thread, std::function<void()> method)
	{
		std::thread* new_thread;

		threads.emplace_back
		(
			LAMBDA(&)
			{
				std::this_thread::yield();

				int index = find(*new_thread);

				std::thread::id id = thread_ids[index];

				lock(followed_thread);

				running_threads.push_back(id);

				method();

				threads.erase(threads.begin() + index);

				thread_ids.erase(FIND(thread_ids, id));

				thread_names.erase(FIND(thread_names, thread_names[index]));

				running_threads.erase(FIND(running_threads, id));

				cancellation_tokens.erase(id);
			}
		);

		new_thread = &threads[threads.size()];

		thread_ids.push_back(new_thread->get_id());

		thread_names.push_back("New Thread");

		cancellation_tokens[new_thread->get_id()] = false;

		new_thread->detach();

		return new_thread;
	}

	// •  Creates a new thread that can run code independently of other threads.
	// •  followed_thread = The thread to follow this new thread after.
	// •  name = The name of this thread.
	// •  method = The code this thread will execute.
	// •  Use a lambda expression "[] () . void { }" or the LAMBDA() { } macro to add code.
	// •  Returns a pointer to the newly created thread.
	static std::thread* new_thread(std::thread& followed_thread, std::string name, std::function<void()> method)
	{
		std::thread* new_thread;

		threads.emplace_back
		(
			LAMBDA(&)
			{
				std::this_thread::yield();

				int index = find(*new_thread);

				std::thread::id id = thread_ids[index];

				lock(followed_thread);

				running_threads.push_back(id);

				method();

				threads.erase(threads.begin() + index);

				thread_ids.erase(FIND(thread_ids, id));

				thread_names.erase(FIND(thread_names, thread_names[index]));

				running_threads.erase(FIND(running_threads, id));

				cancellation_tokens.erase(id);
			}
		);

		new_thread = &threads[threads.size()];

		thread_ids.push_back(new_thread->get_id());

		thread_names.push_back(name);

		cancellation_tokens[new_thread->get_id()] = false;

		new_thread->detach();

		return new_thread;
	}

	// •  Creates a new thread that can run code independently of other threads.
	// •  followed_thread = The thread to follow this new thread after.
	// •  method = The code this thread will execute.
	// •  Use a lambda expression "[] () . void { }" or the LAMBDA() { } macro to add code.
	// •  Returns a pointer to the newly created thread.
	static std::thread* new_thread(std::thread::id followed_id, std::function<void()> method)
	{
		std::thread* new_thread;

		threads.emplace_back
		(
			LAMBDA(&)
			{
				std::this_thread::yield();

				int index = find(*new_thread);

				std::thread::id id = thread_ids[index];

				lock(followed_id);

				running_threads.push_back(id);

				method();

				threads.erase(threads.begin() + index);

				thread_ids.erase(FIND(thread_ids, id));

				thread_names.erase(FIND(thread_names, thread_names[index]));

				running_threads.erase(FIND(running_threads, id));

				cancellation_tokens.erase(id);
			}
		);

		new_thread = &threads[threads.size()];

		thread_ids.push_back(new_thread->get_id());

		thread_names.push_back("New Thread");

		cancellation_tokens[new_thread->get_id()] = false;

		new_thread->detach();

		return new_thread;
	}

	// •  Creates a new thread that can run code independently of other threads.
	// •  followed_thread = The thread to follow this new thread after.
	// •  name = The name of this thread.
	// •  method = The code this thread will execute.
	// •  Use a lambda expression "[] () . void { }" or the LAMBDA() { } macro to add code.
	// •  Returns a pointer to the newly created thread.
	static std::thread* new_thread(std::thread::id followed_id, std::string name, std::function<void()> method)
	{
		std::thread* new_thread;

		threads.emplace_back
		(
			LAMBDA(&)
			{
				std::this_thread::yield();

				int index = find(*new_thread);

				std::thread::id id = thread_ids[index];

				lock(followed_id);

				running_threads.push_back(id);

				method();

				threads.erase(threads.begin() + index);

				thread_ids.erase(FIND(thread_ids, id));

				thread_names.erase(FIND(thread_names, thread_names[index]));

				running_threads.erase(FIND(running_threads, id));

				cancellation_tokens.erase(id);
			}
		);

		new_thread = &threads[threads.size()];

		thread_ids.push_back(new_thread->get_id());

		thread_names.push_back(name);

		cancellation_tokens[new_thread->get_id()] = false;

		new_thread->detach();

		return new_thread;
	}


	// JOINING THREADS

	// Starts a non-running thread asynchronously and returns whether it was successful
	static bool start(std::thread& thread, bool join = false)
	{
		if (is_active(thread) && !is_running(thread))
		{
			if (join)
			{
				thread.join();
			}
			else
			{
				thread.detach();
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	// Starts a non-running thread asynchronously by id and returns whether it was successful
	static bool start(std::thread::id id, bool join = false)
	{
		if (is_active(id) && !is_running(id))
		{
			if (join)
			{
				threads[find(id)].join();
			}
			else
			{
				threads[find(id)].detach();
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	// Joins and completes the given non-running thread before the current thread resumes and returns whether it was successful
	static bool join(std::thread& thread)
	{
		if (is_active(thread) && !is_running(thread))
		{
			thread.join();
		}
		else
		{
			return false;
		}

		return true;
	}

	// Joins and completes the given non-running thread by id before the current thread resumes and returns whether it was successful
	static bool join(std::thread::id id)
	{
		if (is_active(id) && !is_running(id))
		{
			threads[find(id)].join();
		}
		else
		{
			return false;
		}

		return true;
	}

	// Joins and locks the given non-running thread until after the current thread finishes and returns whether it was successful
	static bool follow(std::thread& thread)
	{
		int index = find(thread);

		if (locked_threads.count(thread_ids[index]))
		{
			locked_threads[thread_ids[index]] = std::this_thread::get_id();
		}
		else if (is_active(thread) && !is_running(thread))
		{
			locked_threads[thread_ids[index]] = std::this_thread::get_id();

			thread.detach();
		}
		else
		{
			return false;
		}

		return true;
	}

	// Joins and locks the given non-running thread by id until after the current thread finishes and returns whether it was successful
	static bool follow(std::thread::id id)
	{
		if (locked_threads.count(id))
		{
			locked_threads[id] = std::this_thread::get_id();
		}
		else if (is_active(id) && !is_running(id))
		{
			locked_threads[id] = std::this_thread::get_id();

			threads[find(id)].detach();
		}
		else
		{
			return false;
		}

		return true;
	}

	// Joins and locks the given non-running thread after after the given following thread finishes and returns whether it was successful
	static bool follow(std::thread& thread, std::thread& followed_thread)
	{
		int index = find(thread);

		if (locked_threads.count(thread_ids[index]))
		{
			locked_threads[thread_ids[index]] = thread_ids[find(followed_thread)];
		}
		else if (is_active(thread) && !is_running(thread))
		{
			locked_threads[thread_ids[index]] = thread_ids[find(followed_thread)];

			thread.detach();
		}
		else
		{
			return false;
		}

		return true;
	}

	// Joins and locks the given non-running thread by id after after the given following thread by id finishes and returns whether it was successful
	static bool follow(std::thread::id id, std::thread::id followed_id)
	{
		if (locked_threads.count(id))
		{
			locked_threads[id] = followed_id;
		}
		else if (is_active(id) && !is_running(id))
		{
			locked_threads[id] = followed_id;

			threads[find(id)].detach();
		}
		else
		{
			return false;
		}

		return true;
	}


	// CANCELLING THREADS

	// Gets the current thread's cancellation token (set to true on when cancel() is called)
	static bool get_cancellation_token()
	{
		return cancellation_tokens[std::this_thread::get_id()];
	}

	// Gets the given thread's cancellation token (set to true on when cancel() is called)
	static bool get_cancellation_token(std::thread& thread)
	{
		return cancellation_tokens[thread_ids[find(thread)]];
	}

	// Gets the given thread's cancellation token by id (set to true on when cancel() is called)
	static bool get_cancellation_token(std::thread::id id)
	{
		return cancellation_tokens[id];
	}

	// Cancels the current thread and returns whether it was successful. You need to program cancellation logic in the thread using get_cancellation_token() for it to cancel.
	static bool cancel()
	{
		if (is_active(std::this_thread::get_id()) && is_running(std::this_thread::get_id()))
		{
			cancellation_tokens[std::this_thread::get_id()] = true;

			if (std::this_thread::get_id() == main_thread_id)
			{
				cancel_main_thread();
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	// Cancels the given thread and returns whether it was successful. You need to program cancellation logic in the thread using get_cancellation_token() for it to cancel.
	static bool cancel(std::thread& thread)
	{
		int index = find(thread);

		if (is_active(thread_ids[index]) && is_running(thread_ids[index]))
		{
			cancellation_tokens[thread_ids[index]] = true;

			if (thread_ids[index] == main_thread_id)
			{
				cancel_main_thread();
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	// Cancels the given thread by id and returns whether it was successful. You need to program cancellation logic in the thread using get_cancellation_token() for it to cancel.
	static bool cancel(std::thread::id id)
	{
		if (is_active(id) && is_running(id))
		{
			cancellation_tokens[id] = true;

			if (id == main_thread_id)
			{
				cancel_main_thread();
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	// Cancels all of the given threads except the main thread. You need to program cancellation logic in the thread using get_cancellation_token() for it to cancel.
	static int cancel_all()
	{
		int count = running_threads.size() - 1;

		while (running_threads.size() > 1)
		{
			cancel(running_threads[1]);
		}

		return count;
	}

	// Cancels all of the given threads except the current thread. You need to program cancellation logic in the thread using get_cancellation_token() for it to cancel.
	static int cancel_others()
	{
		int count = running_threads.size() - 1;

		while (running_threads[0] != std::this_thread::get_id())
		{
			cancel(running_threads[0]);
		}

		while (running_threads.size() > 1)
		{
			cancel(running_threads[1]);
		}

		return count;
	}


	// DELAYING THREAD

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

	// Delay the current thread for one tick
	static void yield()
	{
		std::this_thread::yield();
	}

	// Delay the current thread for the given number of ticks
	static void yield(int number_of_ticks)
	{
		for (int i = 0; i < number_of_ticks; i++)
		{
			std::this_thread::yield();
		}
	}

	// Delay the current thread for the given number of milliseconds
	static void sleep_for_milliseconds(int milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

	// Delay the current for the given number of seconds
	static void sleep_for_seconds(float seconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(to_milliseconds(seconds)));
	}


	// MAIN THREAD

	// Returns whether the main thread is still running
	static bool is_main_thread_active()
	{
		return is_active(main_thread_id);
	}

	// Retrieves the cancellation token of the main thread
	static bool get_main_thread_cancellation_token()
	{
		return cancellation_tokens[main_thread_id];
	}

	// Joins and locks the given non-running thread until after the main thread finishes and returns whether it was successful
	static bool follow_main_thread(std::thread& thread)
	{
		return follow(thread_ids[find(thread)], main_thread_id);
	}

	// Joins and locks the given non-running thread until after the main thread finishes and returns whether it was successful
	static bool follow_main_thread(std::thread::id id)
	{
		return follow(id, main_thread_id);
	}

	// Locks the main thread until it is cancelled (current thread must be main thread)
	static void lock_main_thread()
	{
		if (std::this_thread::get_id() == main_thread_id)
		{
			while (!cancellation_tokens[main_thread_id]) { std::this_thread::yield(); }
		}
	}

	// Call this function to end the main thread and preserve other threads until they complete
	static void cancel_main_thread(bool cancel_all_threads = false)
	{
		cancellation_tokens[main_thread_id] = true;

		if (std::this_thread::get_id() == main_thread_id)
		{
			std::this_thread::yield();
		}

		threads.erase(threads.begin());

		thread_ids.erase(FIND(thread_ids, main_thread_id));

		thread_names.erase(FIND(thread_names, "Main Thread"));

		running_threads.erase(FIND(running_threads, main_thread_id));

		cancellation_tokens.erase(main_thread_id);

		if (cancel_all_threads)
		{
			cancel_all();

			std::this_thread::yield();
		}
		else
		{
			while (threads.size() > 0)
			{ 
				// Prevent deadlocks
				if (threads.size() == locked_threads.size()) 
				{ 
					cancel_all();

					std::this_thread::yield();

					break; 
				}
			}
		}
	}
};

// Static variable initialization	
std::vector<std::thread> threads;
std::vector<std::thread::id> thread_ids = std::vector<std::thread::id>();
std::vector<std::string> thread_names = std::vector<std::string>();
std::vector<std::thread::id> multithreading::running_threads = std::vector<std::thread::id>();
std::map<std::thread::id, bool> multithreading::cancellation_tokens = std::map<std::thread::id, bool>();
std::map<std::thread::id, std::thread::id> multithreading::locked_threads = std::map<std::thread::id, std::thread::id>();
std::thread* multithreading::_main;
std::thread::id multithreading::main_thread_id;

// •  The program's global instance of the thread pool used to initialize the main thread.
// •  Do not access this instance directly, use the multithreading class's static functions.
multithreading thread_pool = multithreading();
