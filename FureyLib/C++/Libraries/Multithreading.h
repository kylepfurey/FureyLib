
// Static Multithreading Functions Script
// by Kyle Furey

#pragma once
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <functional>
#include <chrono>

// Include this heading to use the library
#include "Multithreading.h"

// Shorthand for std::find().
#define _FIND(vector, element) std::find(vector.begin(), vector.end(), element)

// Creates a lambda expression with the given captures and code.
#define LAMBDA(captures) [captures] () mutable -> void

// Thread state behaviour enum
enum thread_state { detach = 0, join = 1, follow = 2 };

// Creates and manages multiple threads of code.
class multithreading
{
private:

	// THREADS

	// All of the program's currently active threads
	static std::vector<std::thread*> threads;

	// All of the program's currently active threads' ids
	static std::vector<std::thread::id> thread_ids;

	// The names of each active thread (KEY = NAME, VALUE = THREAD)
	static std::map<std::string, std::thread*> thread_names;

	// The active threads of each thread id (KEY = THREAD ID, VALUE = THREAD)
	static std::map<std::thread::id, std::thread*> find_thread;

	// The thread ids of each active thread (KEY = THREAD, VALUE = THREAD ID)
	static std::map<std::thread*, std::thread::id> find_id;

	// All of the program's currently running threads
	static std::vector<std::thread*> running_threads;

	// All of the running thread's cancellation tokens (KEY = THREAD, VALUE = CANCELLED)
	static std::map<std::thread*, bool> cancellation_tokens;

	// All of the running thread's locking threads (KEY = LOCKED THREAD, VALUE = THREAD LOCKING KEY)
	static std::map<std::thread*, std::thread*> locked_threads;

	// Whether the main thread has been set
	static bool main_set;

	// The id of the main thread
	static std::thread::id main_thread_id;


	// MAIN THREAD

	// Stores the main thread's information (automatically called)
	static void set_main_thread()
	{
		if (!main_set)
		{
			main_set = true;

			main_thread_id = std::this_thread::get_id();

			threads.push_back(nullptr);

			thread_ids.push_back(main_thread_id);

			find_thread[main_thread_id] = nullptr;

			find_id[nullptr] = main_thread_id;

			thread_names["Main Thread"] = nullptr;

			running_threads.push_back(nullptr);

			cancellation_tokens[nullptr] = false;
		}
	}

public:

	// GETTERS

	// Returns the first active thread of the given name (the thread must have been assigned a name on creation)
	static std::thread& get(std::string name)
	{
		set_main_thread();

		return *thread_names[name];
	}

	// Returns the active thread at the given index
	static std::thread& get(int index)
	{
		set_main_thread();

		return *threads[index];
	}

	// Returns the active thread of the given id
	static std::thread& get(std::thread::id id)
	{
		set_main_thread();

		return *find_thread[id];
	}

	// Returns the first active thread's id of the given name (the thread must have been assigned a name on creation)
	static std::thread::id get_id(std::string name)
	{
		set_main_thread();

		return find_id[thread_names[name]];
	}

	// Returns the active thread's id at the given index
	static std::thread::id get_id(int index)
	{
		set_main_thread();

		return thread_ids[index];
	}

	// Returns the id of the given thread
	static std::thread::id get_id(std::thread& thread)
	{
		set_main_thread();

		return find_id[&thread];
	}

	// Returns a vector of pointers to all the active threads
	static std::vector<std::thread*> get_threads()
	{
		set_main_thread();

		return threads;
	}

	// Returns a vector of all the active threads' ids
	static std::vector<std::thread::id> get_thread_ids()
	{
		set_main_thread();

		return thread_ids;
	}

	// Returns a map of the active thread names to pointers to each active thread
	static std::map<std::string, std::thread*> get_thread_names()
	{
		set_main_thread();

		return thread_names;
	}

	// Returns a map of all the active threads' ids to pointers to their corresponding threads
	static std::map<std::thread::id, std::thread*> get_id_to_thread_map()
	{
		set_main_thread();

		return find_thread;
	}

	// Returns a map of pointers to all the active threads to their corresponding thread ids
	static std::map<std::thread*, std::thread::id> get_thread_to_id_map()
	{
		set_main_thread();

		return find_id;
	}

	// Returns a vector of the active and running threads in order
	static std::vector<std::thread*> get_running_threads()
	{
		set_main_thread();

		return running_threads;
	}

	// Returns a map of the currently locked threads to what thread is locking them
	static std::map<std::thread*, std::thread*> get_locked_threads()
	{
		set_main_thread();

		return locked_threads;
	}

	// Returns the total number of active threads 
	static int active_count()
	{
		set_main_thread();

		return threads.size();
	}

	// Returns the total number of running threads 
	static int running_count()
	{
		set_main_thread();

		return threads.size();
	}

	// Get the name of the current running thread
	static std::string get_name()
	{
		set_main_thread();

		if (main_thread_id == std::this_thread::get_id())
		{
			return "Main Thread";
		}

		for (auto iterator = thread_names.begin(); iterator != thread_names.end(); ++iterator)
		{
			if (current_id() == get_id(*iterator->second))
			{
				return iterator->first;
			}
		}

		return "";
	}

	// Get the name of the given thread
	static std::string get_name(std::thread& thread)
	{
		set_main_thread();

		for (auto iterator = thread_names.begin(); iterator != thread_names.end(); ++iterator)
		{
			if (get_id(thread) == get_id(*iterator->second))
			{
				return iterator->first;
			}
		}

		return "";
	}

	// Get the name of the given thread by id
	static std::string get_name(std::thread::id id)
	{
		if (main_thread_id == id)
		{
			return "Main Thread";
		}

		return get_name(*find_thread[id]);
	}

	// Get the program's main thread's id
	static std::thread::id main_id()
	{
		set_main_thread();

		return main_thread_id;
	}

	// Get the current running thread
	static std::thread& current()
	{
		set_main_thread();

		return *find_thread[std::this_thread::get_id()];
	}

	// Get the current running thread's id
	static std::thread::id current_id()
	{
		set_main_thread();

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
		set_main_thread();

		for (int i = 0; i < threads.size(); i++)
		{
			if (get_id(thread) == get_id(*threads[i]))
			{
				return true;
			}
		}

		return false;
	}

	// Returns whether the given thread by id is currently active
	static bool is_active(std::thread::id id)
	{
		return is_active(*find_thread[id]);
	}

	// Returns whether the given thread is currently running
	static bool is_running(std::thread& thread)
	{
		set_main_thread();

		return !thread.joinable();
	}

	// Returns whether the given thread by id is currently running
	static bool is_running(std::thread::id id)
	{
		return is_running(*find_thread[id]);
	}

	// Returns whether the given thread is active and not currently running (and therefore can be started)
	static bool is_ready(std::thread& thread)
	{
		set_main_thread();

		return is_active(thread) && !is_running(thread);
	}

	// Returns whether the given thread by id is active and not currently running (and therefore can be started)
	static bool is_ready(std::thread::id id)
	{
		return is_ready(*find_thread[id]);
	}


	// LOCKING THREAD

	// Delays the current thread until the given condition is met
	static void block(bool& condition)
	{
		set_main_thread();

		while (!condition) { std::this_thread::yield(); }
	}

	// Delays the current thread until it is is unlocked
	static void lock()
	{
		set_main_thread();

		locked_threads[&current()] = nullptr;

		while (locked_threads.count(&current())) { std::this_thread::yield(); }

		locked_threads.erase(&current());
	}

	// Delays the current thread until the given thread completes or this thread is unlocked
	static void lock(std::thread& thread)
	{
		set_main_thread();

		locked_threads[&current()] = &thread;

		while (locked_threads.count(&current()) && is_active(*locked_threads[&current()])) { std::this_thread::yield(); }

		locked_threads.erase(&current());
	}

	// Delays the current thread until the given thread by id completes or this thread is unlocked
	static void lock(std::thread::id id)
	{
		return lock(*find_thread[id]);
	}

	// Relocks the given locked thread to the current thread and return whether it was successful
	static bool relock(std::thread& locked_thread)
	{
		set_main_thread();

		if (locked_threads.count(&locked_thread))
		{
			locked_threads[&locked_thread] = &current();

			return true;
		}

		return false;
	}

	// Relocks the given locked thread by id to the current thread and return whether it was successful
	static bool relock(std::thread::id locked_id)
	{
		return relock(*find_thread[locked_id]);
	}

	// Relocks the given locked thread to the given thread and return whether it was successful
	static bool relock(std::thread& locked_thread, std::thread& thread)
	{
		set_main_thread();

		if (locked_threads.count(&locked_thread))
		{
			locked_threads[&locked_thread] = &thread;

			return true;
		}

		return false;
	}

	// Relocks the given locked thread by id to the given thread by id and return whether it was successful
	static bool relock(std::thread::id locked_id, std::thread::id id)
	{
		return relock(*find_thread[locked_id], *find_thread[id]);
	}

	// Unlocks the given thread and returns whether it was successful
	static bool unlock(std::thread& unlocked_thread)
	{
		set_main_thread();

		return locked_threads.erase(&unlocked_thread);
	}

	// Unlocks the given thread by id and returns whether it was successful
	static bool unlock(std::thread::id unlocked_id)
	{
		return unlock(*find_thread[unlocked_id]);
	}

	// Returns whether the given thread is locked
	static bool is_locked(std::thread& thread)
	{
		set_main_thread();

		return locked_threads.erase(&thread);
	}

	// Returns whether the given thread by id is locked
	static bool is_locked(std::thread::id id)
	{
		return is_locked(*find_thread[id]);
	}

	// Returns the thread that is locking the given thread or null if it is unlocked
	static std::thread& locked_by(std::thread& thread)
	{
		set_main_thread();

		return *locked_threads[&thread];
	}

	// Returns the thread that is locking the given thread or null if it is unlocked
	static std::thread& locked_by(std::thread::id id)
	{
		return locked_by(*find_thread[id]);
	}


	// NEW THREADS

	// Creates a pointer to a new thread that can run code independently of other threads.
	// •  method = The code this thread will execute.
	// •  Use a lambda expression "[] () -> void { }" or the LAMBDA macro to add code.
	// Returns: A pointer to the newly created thread.
	static std::thread* new_thread(std::function<void()> method)
	{
		set_main_thread();

		std::thread new_thread;

		std::thread temp_thread
		(
			LAMBDA(&)
			{
				if (locked_threads.count(&new_thread))
				{
					lock(*locked_threads[&new_thread]);
				}

				running_threads.push_back(&new_thread);

				method();

				threads.erase(_FIND(threads, &new_thread));

				thread_ids.erase(_FIND(thread_ids, get_id(new_thread)));

				find_thread.erase(find_id[&new_thread]);

				find_id.erase(&new_thread);

				running_threads.erase(_FIND(running_threads, &new_thread));

				cancellation_tokens.erase(&new_thread);
			}
		);

		threads.push_back(&new_thread);

		thread_ids.push_back(temp_thread.get_id());

		find_thread[temp_thread.get_id()] = &new_thread;

		find_id[&new_thread] = temp_thread.get_id();

		cancellation_tokens[&new_thread] = false;

		temp_thread.detach();

		new_thread = std::move(temp_thread);

		return &new_thread;
	}

	// Creates a pointer to a new thread that can run code independently of other threads.
	// •  start_behaviour = Whether to not start, start immediately, or complete this new thread before the current thread resumes.
	// •  method = The code this thread will execute.
	// •  Use a lambda expression "[] () -> void { }" or the LAMBDA macro to add code.
	// Returns: A pointer to the newly created thread.
	static std::thread* new_thread(thread_state start_behaviour, std::function<void()> method)
	{
		set_main_thread();

		std::thread new_thread;

		std::thread temp_thread
		(
			LAMBDA(&)
			{
				if (locked_threads.count(&new_thread))
				{
					lock(*locked_threads[&new_thread]);
				}

				running_threads.push_back(&new_thread);

				method();

				threads.erase(_FIND(threads, &new_thread));

				thread_ids.erase(_FIND(thread_ids, get_id(new_thread)));

				find_thread.erase(find_id[&new_thread]);

				find_id.erase(&new_thread);

				running_threads.erase(_FIND(running_threads, &new_thread));

				cancellation_tokens.erase(&new_thread);
			}
		);

		threads.push_back(&new_thread);

		thread_ids.push_back(temp_thread.get_id());

		find_thread[temp_thread.get_id()] = &new_thread;

		find_id[&new_thread] = temp_thread.get_id();

		cancellation_tokens[&new_thread] = false;

		switch (start_behaviour)
		{
		case thread_state::detach:

			temp_thread.detach();

			break;

		case thread_state::join:

			temp_thread.join();

			break;

		case thread_state::follow:

			follow(new_thread, current());

			break;
		}

		new_thread = std::move(temp_thread);

		return &new_thread;
	}

	// Creates a pointer to a new thread that can run code independently of other threads.
	// •  start_behaviour = Whether to not start, start immediately, or complete this new thread before the current thread resumes.
	// •  name = The name of this thread.
	// •  method = The code this thread will execute.
	// •  Use a lambda expression "[] () -> void { }" or the LAMBDA(){ } macro to add code.
	// Returns: A pointer to the newly created thread.
	static std::thread* new_thread(thread_state start_behaviour, std::string name, std::function<void()> method)
	{
		set_main_thread();

		std::thread new_thread;

		std::thread temp_thread
		(
			LAMBDA(&)
			{
				if (locked_threads.count(&new_thread))
				{
					lock(*locked_threads[&new_thread]);
				}

				running_threads.push_back(&new_thread);

				method();

				threads.erase(_FIND(threads, &new_thread));

				thread_ids.erase(_FIND(thread_ids, get_id(new_thread)));

				find_thread.erase(find_id[&new_thread]);

				find_id.erase(&new_thread);

				thread_names.erase(get_name(new_thread));

				running_threads.erase(_FIND(running_threads, &new_thread));

				cancellation_tokens.erase(&new_thread);
			}
		);

		threads.push_back(&new_thread);

		thread_ids.push_back(temp_thread.get_id());

		find_thread[temp_thread.get_id()] = &new_thread;

		find_id[&new_thread] = temp_thread.get_id();

		thread_names[name] = &new_thread;

		cancellation_tokens[&new_thread] = false;

		switch (start_behaviour)
		{
		case thread_state::detach:

			temp_thread.detach();

			break;

		case thread_state::join:

			temp_thread.join();

			break;

		case thread_state::follow:

			follow(new_thread, current());

			break;
		}

		new_thread = std::move(temp_thread);

		return &new_thread;
	}

	// Creates a pointer to a new thread that can run code independently of other threads.
	// •  followed_thread = The thread to follow this new thread after.
	// •  method = The code this thread will execute.
	// •  Use a lambda expression "[] () -> void { }" or the LAMBDA(){ } macro to add code.
	// Returns: A pointer to the newly created thread.
	static std::thread* new_thread(std::thread& followed_thread, std::function<void()> method)
	{
		set_main_thread();

		std::thread new_thread;

		std::thread temp_thread
		(
			LAMBDA(&)
			{
				lock(followed_thread);

				running_threads.push_back(&new_thread);

				method();

				threads.erase(_FIND(threads, &new_thread));

				thread_ids.erase(_FIND(thread_ids, get_id(new_thread)));

				find_thread.erase(find_id[&new_thread]);

				find_id.erase(&new_thread);

				running_threads.erase(_FIND(running_threads, &new_thread));

				cancellation_tokens.erase(&new_thread);
			}
		);

		threads.push_back(&new_thread);

		thread_ids.push_back(temp_thread.get_id());

		find_thread[temp_thread.get_id()] = &new_thread;

		find_id[&new_thread] = temp_thread.get_id();

		cancellation_tokens[&new_thread] = false;

		temp_thread.detach();

		new_thread = std::move(temp_thread);

		return &new_thread;
	}

	// Creates a pointer to a new thread that can run code independently of other threads.
	// •  followed_thread = The thread to follow this new thread after.
	// •  name = The name of this thread.
	// •  method = The code this thread will execute.
	// •  Use a lambda expression "[] () -> void { }" or the LAMBDA(){ } macro to add code.
	// Returns: A pointer to the newly created thread.
	static std::thread* new_thread(std::thread& followed_thread, std::string name, std::function<void()> method)
	{
		set_main_thread();

		std::thread new_thread;

		std::thread temp_thread
		(
			LAMBDA(&)
			{
				lock(followed_thread);

				running_threads.push_back(&new_thread);

				method();

				threads.erase(_FIND(threads, &new_thread));

				thread_ids.erase(_FIND(thread_ids, get_id(new_thread)));

				find_thread.erase(find_id[&new_thread]);

				find_id.erase(&new_thread);

				thread_names.erase(get_name(new_thread));

				running_threads.erase(_FIND(running_threads, &new_thread));

				cancellation_tokens.erase(&new_thread);
			}
		);

		threads.push_back(&new_thread);

		thread_ids.push_back(temp_thread.get_id());

		find_thread[temp_thread.get_id()] = &new_thread;

		find_id[&new_thread] = temp_thread.get_id();

		thread_names[name] = &new_thread;

		cancellation_tokens[&new_thread] = false;

		temp_thread.detach();

		new_thread = std::move(temp_thread);

		return &new_thread;
	}

	// Creates a pointer to a new thread that can run code independently of other threads.
	// •  followed_thread = The thread to follow this new thread after.
	// •  method = The code this thread will execute.
	// •  Use a lambda expression "[] () -> void { }" or the LAMBDA(){ } macro to add code.
	// Returns: A pointer to the newly created thread.
	static std::thread* new_thread(std::thread::id followed_id, std::function<void()> method)
	{
		set_main_thread();

		std::thread new_thread;

		std::thread temp_thread
		(
			LAMBDA(&)
			{
				lock(*find_thread[followed_id]);

				running_threads.push_back(&new_thread);

				method();

				threads.erase(_FIND(threads, &new_thread));

				thread_ids.erase(_FIND(thread_ids, get_id(new_thread)));

				find_thread.erase(find_id[&new_thread]);

				find_id.erase(&new_thread);

				running_threads.erase(_FIND(running_threads, &new_thread));

				cancellation_tokens.erase(&new_thread);
			}
		);

		threads.push_back(&new_thread);

		thread_ids.push_back(temp_thread.get_id());

		find_thread[temp_thread.get_id()] = &new_thread;

		find_id[&new_thread] = temp_thread.get_id();

		cancellation_tokens[&new_thread] = false;

		temp_thread.detach();

		new_thread = std::move(temp_thread);

		return &new_thread;
	}

	// Creates a pointer to a new thread that can run code independently of other threads.
	// •  followed_thread = The thread to follow this new thread after.
	// •  name = The name of this thread.
	// •  method = The code this thread will execute.
	// •  Use a lambda expression "[] () -> void { }" or the LAMBDA(){ } macro to add code.
	// Returns: A pointer to the newly created thread.
	static std::thread* new_thread(std::thread::id followed_id, std::string name, std::function<void()> method)
	{
		set_main_thread();

		std::thread new_thread;

		std::thread temp_thread
		(
			LAMBDA(&)
			{
				lock(*find_thread[followed_id]);

				running_threads.push_back(&new_thread);

				method();

				threads.erase(_FIND(threads, &new_thread));

				thread_ids.erase(_FIND(thread_ids, get_id(new_thread)));

				find_thread.erase(find_id[&new_thread]);

				find_id.erase(&new_thread);

				thread_names.erase(get_name(new_thread));

				running_threads.erase(_FIND(running_threads, &new_thread));

				cancellation_tokens.erase(&new_thread);
			}
		);

		threads.push_back(&new_thread);

		thread_ids.push_back(temp_thread.get_id());

		find_thread[temp_thread.get_id()] = &new_thread;

		find_id[&new_thread] = temp_thread.get_id();

		thread_names[name] = &new_thread;

		cancellation_tokens[&new_thread] = false;

		temp_thread.detach();

		new_thread = std::move(temp_thread);

		return &new_thread;
	}


	// JOINING THREADS

	// Starts a non-running thread asynchronously and returns whether it was successful
	static bool start(std::thread& thread, bool join = false)
	{
		set_main_thread();

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
		return start(*find_thread[id], join);
	}

	// Joins and completes the given non-running thread before the current thread resumes and returns whether it was successful
	static bool join(std::thread& thread)
	{
		set_main_thread();

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
		return join(*find_thread[id]);
	}

	// Joins and locks the given non-running thread until after the current thread finishes and returns whether it was successful
	static bool follow(std::thread& thread)
	{
		set_main_thread();

		if (locked_threads.count(&thread))
		{
			locked_threads[&thread] = &current();
		}
		else if (is_active(thread) && !is_running(thread))
		{
			locked_threads[&thread] = &current();

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
		return follow(*find_thread[id]);
	}

	// Joins and locks the given non-running thread after after the given following thread finishes and returns whether it was successful
	static bool follow(std::thread& thread, std::thread& followed_thread)
	{
		set_main_thread();

		if (locked_threads.count(&thread))
		{
			locked_threads[&thread] = &followed_thread;
		}
		else if (is_active(thread) && !is_running(thread))
		{
			locked_threads[&thread] = &followed_thread;

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
		return follow(*find_thread[id], *find_thread[followed_id]);
	}


	// CANCELLING THREADS

	// Gets the current thread's cancellation token (set to true on when cancel() is called)
	static bool get_cancellation_token()
	{
		set_main_thread();

		return cancellation_tokens[&current()];
	}

	// Gets the given thread's cancellation token (set to true on when cancel() is called)
	static bool get_cancellation_token(std::thread& thread)
	{
		set_main_thread();

		return cancellation_tokens[&thread];
	}

	// Gets the given thread's cancellation token by id (set to true on when cancel() is called)
	static bool get_cancellation_token(std::thread::id id)
	{
		return get_cancellation_token(*find_thread[id]);
	}

	// Cancels the current thread and returns whether it was successful. You need to program cancellation logic in the thread using get_cancellation_token() for it to cancel.
	static bool cancel()
	{
		set_main_thread();

		if (is_active(current()) && is_running(current()))
		{
			cancellation_tokens[&current()] = true;

			if (current_id() == main_thread_id)
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
		set_main_thread();

		if (is_active(thread) && is_running(thread))
		{
			cancellation_tokens[&thread] = true;

			if (get_id(thread) == main_thread_id)
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
		return cancel(*find_thread[id]);
	}

	// Cancels all of the given threads except the main thread. You need to program cancellation logic in the thread using get_cancellation_token() for it to cancel.
	static int cancel_all()
	{
		set_main_thread();

		int count = running_threads.size() - 1;

		while (running_threads.size() > 1)
		{
			cancel(*running_threads[1]);
		}

		return count;
	}

	// Cancels all of the given threads except the current thread. You need to program cancellation logic in the thread using get_cancellation_token() for it to cancel.
	static int cancel_others()
	{
		set_main_thread();

		int count = running_threads.size() - 1;

		while (get_id(*running_threads[0]) != current_id())
		{
			cancel(*running_threads[0]);
		}

		while (running_threads.size() > 1)
		{
			cancel(*running_threads[1]);
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
		set_main_thread();

		return is_active(main_thread_id);
	}

	// Retrieves the cancellation token of the main thread
	static bool get_main_thread_cancellation_token()
	{
		set_main_thread();

		return cancellation_tokens[nullptr];
	}

	// Locks the main thread until it is cancelled (current thread must be main thread)
	static void lock_main_thread()
	{
		set_main_thread();

		if (current_id() == main_thread_id)
		{
			while (!cancellation_tokens[nullptr]) { std::this_thread::yield(); }
		}
	}

	// Call this function to end the main thread
	static void cancel_main_thread(bool cancel_all_threads = false)
	{
		set_main_thread();

		cancellation_tokens[nullptr] = true;

		if (current_id() == main_thread_id)
		{
			std::this_thread::yield();
		}

		threads.erase(_FIND(threads, nullptr));

		thread_ids.erase(_FIND(thread_ids, main_thread_id));

		find_thread.erase(find_id[nullptr]);

		find_id.erase(nullptr);

		thread_names.erase("Main Thread");

		running_threads.erase(_FIND(running_threads, nullptr));

		cancellation_tokens.erase(nullptr);

		if (cancel_all_threads)
		{
			cancel_all();
		}
	}
};

// Static variable initialization
std::vector<std::thread*> multithreading::threads = std::vector<std::thread*>();
std::vector<std::thread::id> multithreading::thread_ids = std::vector<std::thread::id>();
std::map<std::string, std::thread*> multithreading::thread_names = std::map<std::string, std::thread*>();
std::map<std::thread::id, std::thread*> multithreading::find_thread = std::map<std::thread::id, std::thread*>();
std::map<std::thread*, std::thread::id> multithreading::find_id = std::map<std::thread*, std::thread::id>();
std::vector<std::thread*> multithreading::running_threads = std::vector<std::thread*>();
std::map<std::thread*, bool> multithreading::cancellation_tokens = std::map<std::thread*, bool>();
std::map<std::thread*, std::thread*> multithreading::locked_threads = std::map<std::thread*, std::thread*>();
bool multithreading::main_set = false;
std::thread::id multithreading::main_thread_id = std::thread::id();
