﻿
// Static Multithreading Functions Script
// by Kyle Furey

using System;
using System.Collections.Generic;
using System.Threading;

// Include this heading to use the library
using static Multithreading;

/// <summary>
/// Creates and manages multiple threads of code.
/// </summary>
public static class Multithreading
{
    // THREADS

    /// <summary>
    /// All of the program's currently active threads
    /// </summary>
    private static List<Thread> threads = new List<Thread>();

    /// <summary>
    /// The names of each active thread (KEY = NAME, VALUE = THREAD)
    /// </summary>
    private static Dictionary<string, Thread> threadNames = new Dictionary<string, Thread>();

    /// <summary>
    /// All of the program's currently running threads
    /// </summary>
    private static List<Thread> runningThreads = new List<Thread>();

    /// <summary>
    /// All of the running threads' cancellation tokens (KEY = THREAD, VALUE = CANCELLED)
    /// </summary>
    private static Dictionary<Thread, bool> cancellationTokens = new Dictionary<Thread, bool>();

    /// <summary>
    /// All of the running threads' locking threads (KEY = LOCKED THREAD, VALUE = THREAD LOCKING KEY)
    /// </summary>
    private static Dictionary<Thread, Thread> lockedThreads = new Dictionary<Thread, Thread>();

    /// <summary>
    /// The total number of active threads
    /// </summary>
    public static int totalActiveThreads
    {
        get
        {
            return threads.Count;
        }
    }

    /// <summary>
    /// The total number of running threads
    /// </summary>
    public static int totalRunningThreads
    {
        get
        {
            return runningThreads.Count;
        }
    }

    /// <summary>
    /// The name of the current running thread
    /// </summary>
    public static string name
    {
        get
        {
            return Thread.CurrentThread.Name;
        }
    }


    /// <summary>
    /// The program's main thread
    /// </summary>
    public static Thread main
    {
        get
        {
            return _main;
        }

        private set
        {
            _main = value;
        }
    }

    private static Thread _main = null;

    /// <summary>
    /// The current running thread
    /// </summary>
    public static Thread current
    {
        get
        {
            return Thread.CurrentThread;
        }
    }


    // STATIC CONSTRUCTOR

    /// <summary>
    /// Stores the main thread (automatically called)
    /// </summary>
    private static void SetMainThread()
    {
        _main = Thread.CurrentThread;

        Thread.CurrentThread.Name = "Main Thread";

        threads.Add(_main);

        threadNames["Main Thread"] = _main;

        runningThreads.Add(_main);

        cancellationTokens[_main] = false;
    }

    /// <summary>
    /// Marks and stores the main thread when the program starts
    /// </summary>
    static Multithreading()
    {
        SetMainThread();
    }


    // GETTERS

    /// <summary>
    /// Returns the first active thread of the given name (the thread must have been assigned a name on creation)
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    public static Thread Get(string name)
    {
        if (!threadNames.ContainsKey(name))
        {
            return null;
        }

        return threadNames[name];
    }

    /// <summary>
    /// Returns the active thread at the given index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public static Thread Get(int index)
    {
        if (index < 0 || index >= threads.Count)
        {
            return null;
        }

        return threads[index];
    }

    /// <summary>
    /// Returns a list of the active threads
    /// </summary>
    /// <returns></returns>
    public static List<Thread> GetThreads()
    {
        return threads;
    }

    /// <summary>
    /// Returns a dictionary of the active thread names to threads
    /// </summary>
    /// <returns></returns>
    public static Dictionary<string, Thread> GetThreadNames()
    {
        return threadNames;
    }

    /// <summary>
    /// Returns a list of the active and running threads in order
    /// </summary>
    public static List<Thread> GetRunningThreads()
    {
        return runningThreads;
    }

    /// <summary>
    /// Returns a dictionary of the currently locked threads to what thread is locking them
    /// </summary>
    public static Dictionary<Thread, Thread> GetLockedThreads()
    {
        return lockedThreads;
    }

    /// <summary>
    /// Returns the total number of active threads 
    /// </summary>
    /// <returns></returns>
    public static int ActiveCount()
    {
        return threads.Count;
    }

    /// <summary>
    /// Returns the total number of running threads 
    /// </summary>
    /// <returns></returns>
    public static int RunningCount()
    {
        return threads.Count;
    }

    /// <summary>
    /// Get the name of the current running thread
    /// </summary>
    /// <returns></returns>
    public static string GetName()
    {
        return current.Name;
    }

    /// <summary>
    /// Get the name of the given thread
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static string GetName(Thread thread)
    {
        return thread.Name;
    }

    /// <summary>
    /// Get the name of the given thread's index
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public static string GetName(int index)
    {
        return threads[index].Name;
    }

    /// <summary>
    /// Get the program's main thread
    /// </summary>
    /// <returns></returns>
    public static Thread Main()
    {
        return main;
    }

    /// <summary>
    /// Get the current running thread
    /// </summary>
    /// <returns></returns>
    public static Thread Current()
    {
        return current;
    }

    /// <summary>
    /// Get the total number of logical processors on this device
    /// </summary>
    /// <returns></returns>
    public static int NumberOfProcessors()
    {
        return Environment.ProcessorCount;
    }


    // ACTIVE AND RUNNING

    /// <summary>
    /// Returns whether the given thread is currently active
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool IsActive(Thread thread)
    {
        return threads.Contains(thread);
    }

    /// <summary>
    /// Returns whether the given thread is currently running
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool IsRunning(Thread thread)
    {
        return thread.IsAlive;
    }

    /// <summary>
    /// Returns whether the given thread is active and not currently running (and therefore can be started)
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool IsReady(Thread thread)
    {
        return threads.Contains(thread) && !thread.IsAlive;
    }


    // LOCKING THREAD

    /// <summary>
    /// Delays the current thread until the given condition is met
    /// </summary>
    /// <param name="condition"></param>
    public static void Block(ref bool condition)
    {
        while (!condition) { }
    }

    /// <summary>
    /// Delays the current thread until it is is unlocked
    /// </summary>
    public static void Lock()
    {
        lockedThreads[current] = null;

        while (lockedThreads.ContainsKey(current)) { }

        lockedThreads.Remove(current);
    }

    /// <summary>
    /// Delays the current thread until the given thread completes or this thread is unlocked
    /// </summary>
    /// <param name="thread"></param>
    public static void Lock(Thread thread)
    {
        if (!threads.Contains(thread))
        {
            return;
        }

        lockedThreads[current] = thread;

        while (lockedThreads.ContainsKey(current) && threads.Contains(lockedThreads[current])) { }

        lockedThreads.Remove(current);
    }

    /// <summary>
    /// Relocks the given locked thread to the current thread and return whether it was successful
    /// </summary>
    /// <param name="lockedThread"></param>
    public static bool Relock(Thread lockedThread)
    {
        if (lockedThreads.ContainsKey(lockedThread))
        {
            lockedThreads[lockedThread] = current;

            return true;
        }

        return false;
    }

    /// <summary>
    /// Relocks the given locked thread to the given thread and return whether it was successful
    /// </summary>
    /// <param name="lockedThread"></param>
    /// <param name="thread"></param>
    public static bool Relock(Thread lockedThread, Thread thread)
    {
        if (lockedThreads.ContainsKey(lockedThread))
        {
            lockedThreads[lockedThread] = thread;

            return true;
        }

        return false;
    }

    /// <summary>
    /// Unlocks the given thread and returns whether it was successful
    /// </summary>
    /// <param name="unlockedThread"></param>
    /// <returns></returns>
    public static bool Unlock(Thread unlockedThread)
    {
        return lockedThreads.Remove(unlockedThread);
    }

    /// <summary>
    /// Returns whether the given thread is locked
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool IsLocked(Thread thread)
    {
        return lockedThreads.ContainsKey(thread);
    }

    /// <summary>
    /// Returns the thread that is locking the given thread or null if it is unlocked
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static Thread LockedBy(Thread thread)
    {
        if (lockedThreads.ContainsKey(thread))
        {
            return lockedThreads[thread];
        }
        else
        {
            return null;
        }
    }


    // NEW THREADS

    /// <summary>
    /// Creates a new thread that can run code independently of other threads.
    /// </summary>
    /// <param name="method">The code this thread will execute. Use a lambda expression "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(Action method)
    {
        Thread newThread = null;

        newThread = new Thread(() =>
        {
            if (lockedThreads.ContainsKey(newThread))
            {
                Lock(lockedThreads[newThread]);
            }

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);
        });

        threads.Add(newThread);

        newThread.Name = "New Thread";

        newThread.IsBackground = true;

        newThread.Priority = ThreadPriority.Normal;

        cancellationTokens[newThread] = false;

        newThread.Start();

        return newThread;
    }

    /// <summary>
    /// Creates a new thread that can run code independently of other threads.
    /// </summary>
    /// <param name="start">Whether to run this thread immediately.</param>
    /// <param name="method">The code this thread will execute. Use a lambda expression "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(bool start, Action method)
    {
        Thread newThread = null;

        newThread = new Thread(() =>
        {
            if (lockedThreads.ContainsKey(newThread))
            {
                Lock(lockedThreads[newThread]);
            }

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);
        });

        threads.Add(newThread);

        newThread.Name = "New Thread";

        newThread.IsBackground = true;

        newThread.Priority = ThreadPriority.Normal;

        cancellationTokens[newThread] = false;

        if (start)
        {
            newThread.Start();
        }

        return newThread;
    }

    /// <summary>
    /// Creates a new thread that can run code independently of other threads.
    /// </summary>
    /// <param name="start">Whether to start this thread immediately.</param>
    /// <param name="name">The name of this thread.</param>
    /// <param name="method">The code this thread will execute. Use a lambda expression "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(bool start, bool join, Action method)
    {
        Thread newThread = null;

        newThread = new Thread(() =>
        {
            if (lockedThreads.ContainsKey(newThread))
            {
                Lock(lockedThreads[newThread]);
            }

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);
        });

        threads.Add(newThread);

        newThread.Name = "New Thread";

        newThread.IsBackground = true;

        newThread.Priority = ThreadPriority.Normal;

        cancellationTokens[newThread] = false;

        if (start)
        {
            newThread.Start();

            if (join)
            {
                newThread.Join();
            }
        }

        return newThread;
    }

    /// <summary>
    /// Creates a new thread that can run code independently of other threads.
    /// </summary>
    /// <param name="start">Whether to start this thread immediately.</param>
    /// <param name="join">Whether to complete this new thread before the current thread resumes.</param>
    /// <param name="name">The name of this thread.</param>
    /// <param name="method">The code this thread will execute. Use a lambda expression "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(bool start, bool join, string name, Action method)
    {
        Thread newThread = null;

        newThread = new Thread(() =>
        {
            if (lockedThreads.ContainsKey(newThread))
            {
                Lock(lockedThreads[newThread]);
            }

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            threadNames.Remove(name);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);
        });

        threads.Add(newThread);

        newThread.Name = name;

        threadNames[newThread.Name] = newThread;

        newThread.IsBackground = true;

        newThread.Priority = ThreadPriority.Normal;

        cancellationTokens[newThread] = false;

        if (start)
        {
            newThread.Start();

            if (join)
            {
                newThread.Join();
            }
        }

        return newThread;
    }

    /// <summary>
    /// Creates a new thread that can run code independently of other threads.
    /// </summary>
    /// <param name="start">Whether to run this thread immediately.</param>
    /// <param name="join">Whether to complete this new thread before the current thread resumes.</param>
    /// <param name="name">The name of this thread.</param>
    /// <param name="isBackground">Whether this thread will terminate when the main thread ends.</param>
    /// <param name="method">The code this thread will execute. Use a lambda expression "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(bool start, bool join, string name, bool isBackground, Action method)
    {
        Thread newThread = null;

        newThread = new Thread(() =>
        {
            if (lockedThreads.ContainsKey(newThread))
            {
                Lock(lockedThreads[newThread]);
            }

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            threadNames.Remove(name);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);
        });

        threads.Add(newThread);

        newThread.Name = name;

        threadNames[newThread.Name] = newThread;

        newThread.IsBackground = isBackground;

        newThread.Priority = ThreadPriority.Normal;

        cancellationTokens[newThread] = false;

        if (start)
        {
            newThread.Start();

            if (join)
            {
                newThread.Join();
            }
        }

        return newThread;
    }

    /// <summary>
    /// Creates a new thread that can run code independently of other threads.
    /// </summary>
    /// <param name="start">Whether to run this thread immediately.</param>
    /// <param name="join">Whether to complete this new thread before the current thread resumes.</param>
    /// <param name="name">The name of this thread.</param>
    /// <param name="isBackground">Whether this thread will terminate when the main thread ends.</param>
    /// <param name="priority">The priority of this thread.</param>
    /// <param name="method">The code this thread will execute. Use a lambda expression "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(bool start, bool join, string name, bool isBackground, ThreadPriority priority, Action method)
    {
        Thread newThread = null;

        newThread = new Thread(() =>
        {
            if (lockedThreads.ContainsKey(newThread))
            {
                Lock(lockedThreads[newThread]);
            }

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            threadNames.Remove(name);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);
        });

        threads.Add(newThread);

        newThread.Name = name;

        threadNames[newThread.Name] = newThread;

        newThread.IsBackground = isBackground;

        newThread.Priority = priority;

        cancellationTokens[newThread] = false;

        if (start)
        {
            newThread.Start();

            if (join)
            {
                newThread.Join();
            }
        }

        return newThread;
    }

    /// <summary>
    /// Creates a new thread that can run code independently of other threads.
    /// </summary>
    /// <param name="followedThread">The thread to follow this new thread after.</param>
    /// <param name="method">The code this thread will execute. Use a lambda expression "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(Thread followedThread, Action method)
    {
        Thread newThread = null;

        newThread = new Thread(() =>
        {
            Lock(followedThread);

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);
        });

        threads.Add(newThread);

        newThread.Name = "New Thread";

        newThread.IsBackground = true;

        newThread.Priority = ThreadPriority.Normal;

        cancellationTokens[newThread] = false;

        newThread.Start();

        return newThread;
    }

    /// <summary>
    /// Creates a new thread that can run code independently of other threads.
    /// </summary>
    /// <param name="followedThread">The thread to follow this new thread after.</param>
    /// <param name="name">The name of this thread.</param>
    /// <param name="method">The code this thread will execute. Use a lambda expression "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(Thread followedThread, string name, Action method)
    {
        Thread newThread = null;

        newThread = new Thread(() =>
        {
            Lock(followedThread);

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);
        });

        threads.Add(newThread);

        newThread.Name = name;

        threadNames[newThread.Name] = newThread;

        newThread.IsBackground = true;

        newThread.Priority = ThreadPriority.Normal;

        cancellationTokens[newThread] = false;

        newThread.Start();

        return newThread;
    }

    /// <summary>
    /// Creates a new thread that can run code independently of other threads.
    /// </summary>
    /// <param name="followedThread">The thread to follow this new thread after.</param>
    /// <param name="name">The name of this thread.</param>
    /// <param name="isBackground">Whether this thread will terminate when the main thread ends.</param>
    /// <param name="method">The code this thread will execute. Use a lambda expression "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(Thread followedThread, string name, bool isBackground, Action method)
    {
        Thread newThread = null;

        newThread = new Thread(() =>
        {
            Lock(followedThread);

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);
        });

        threads.Add(newThread);

        newThread.Name = name;

        threadNames[newThread.Name] = newThread;

        newThread.IsBackground = isBackground;

        newThread.Priority = ThreadPriority.Normal;

        cancellationTokens[newThread] = false;

        newThread.Start();

        return newThread;
    }

    /// <summary>
    /// Creates a new thread that can run code independently of other threads.
    /// </summary>
    /// <param name="followedThread">The thread to follow this new thread after.</param>
    /// <param name="name">The name of this thread.</param>
    /// <param name="isBackground">Whether this thread will terminate when the main thread ends.</param>
    /// <param name="priority">The priority of this thread.</param>
    /// <param name="followedThread">The thread to have this new thread start after.</param>
    /// <param name="method">The code this thread will execute. Use a lambda expression "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(Thread followedThread, string name, bool isBackground, ThreadPriority priority, Action method)
    {
        Thread newThread = null;

        newThread = new Thread(() =>
        {
            Lock(followedThread);

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);
        });

        threads.Add(newThread);

        newThread.Name = name;

        threadNames[newThread.Name] = newThread;

        newThread.IsBackground = isBackground;

        newThread.Priority = priority;

        cancellationTokens[newThread] = false;

        newThread.Start();

        return newThread;
    }


    // JOINING THREADS

    /// <summary>
    /// Starts a non-running thread asynchronously and returns whether it was successful
    /// </summary>
    /// <param name="thread"></param>
    /// <param name="join"></param>
    /// <returns></returns>
    public static bool Start(Thread thread, bool join = false)
    {
        if (threads.Contains(thread) && !thread.IsAlive)
        {
            thread.Start();

            if (join)
            {
                thread.Join();
            }
        }
        else
        {
            return false;
        }

        return true;
    }

    /// <summary>
    /// Joins and completes the given non-running thread before the current thread resumes and returns whether it was successful
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool Join(Thread thread)
    {
        if (threads.Contains(thread) && !thread.IsAlive)
        {
            thread.Start();

            thread.Join();
        }
        else
        {
            return false;
        }

        return true;
    }

    /// <summary>
    /// Joins and locks the given non-running thread until after the current thread finishes and returns whether it was successful
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool Follow(Thread thread)
    {
        if (lockedThreads.ContainsKey(thread))
        {
            if (current == main)
            {
                thread.IsBackground = false;
            }

            lockedThreads[thread] = current;
        }
        else if (threads.Contains(thread) && !thread.IsAlive)
        {
            if (current == main)
            {
                thread.IsBackground = false;
            }

            lockedThreads[thread] = current;

            thread.Start();
        }
        else
        {
            return false;
        }

        return true;
    }

    /// <summary>
    /// Joins and locks the given non-running thread after after the given following thread finishes and returns whether it was successful
    /// </summary>
    /// <param name="thread"></param>
    /// <param name="followedThread"></param>
    /// <returns></returns>
    public static bool Follow(Thread thread, Thread followedThread)
    {
        if (lockedThreads.ContainsKey(thread))
        {
            if (followedThread == main)
            {
                thread.IsBackground = false;
            }

            lockedThreads[thread] = followedThread;
        }
        else if (threads.Contains(thread) && !thread.IsAlive)
        {
            if (followedThread == main)
            {
                thread.IsBackground = false;
            }

            lockedThreads[thread] = followedThread;

            thread.Start();
        }
        else
        {
            return false;
        }

        return true;
    }


    // CANCELLING THREADS

    /// <summary>
    /// Gets the current thread's cancellation token (set to true on when Cancel() is called)
    /// </summary>
    /// <returns></returns>
    public static bool GetCancellationToken()
    {
        return cancellationTokens[current];
    }

    /// <summary>
    /// Gets the given thread's cancellation token (set to true on when Cancel() is called)
    /// </summary>
    /// <returns></returns>
    public static bool GetCancellationToken(Thread thread)
    {
        return cancellationTokens[thread];
    }

    /// <summary>
    /// Cancels the current thread and returns whether it was successful. You need to program cancellation logic in the thread using GetCancellationToken() for it to cancel.
    /// </summary>
    /// <returns></returns>
    public static bool Cancel()
    {
        if (current.IsAlive)
        {
            cancellationTokens[current] = true;

            if (current == main)
            {
                EndMainThread();
            }
        }
        else
        {
            return false;
        }

        return true;
    }

    /// <summary>
    /// Cancels the given thread and returns whether it was successful. You need to program cancellation logic in the thread using GetCancellationToken() for it to cancel.
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool Cancel(Thread thread)
    {
        if (thread.IsAlive)
        {
            cancellationTokens[thread] = true;

            if (thread == main)
            {
                EndMainThread();
            }
        }
        else
        {
            return false;
        }

        return true;
    }

    /// <summary>
    /// Cancels all of the given threads except the main thread. You need to program cancellation logic in the thread using GetCancellationToken() for it to cancel.
    /// </summary>
    /// <returns></returns>
    public static int CancelAll()
    {
        int count = 0;

        for (int i = 0; i < threads.Count; i++)
        {
            if (main != threads[i])
            {
                if (Cancel(threads[i]))
                {
                    count++;
                }
            }
        }

        return count;
    }

    /// <summary>
    /// Cancels all of the given threads except the current thread. You need to program cancellation logic in the thread using GetCancellationToken() for it to cancel.
    /// </summary>
    /// <returns></returns>
    public static int CancelOthers()
    {
        int count = 0;

        for (int i = 0; i < threads.Count; i++)
        {
            if (current != threads[i])
            {
                if (Cancel(threads[i]))
                {
                    count++;
                }
            }
        }

        return count;
    }


    // DELAYING THREAD

    /// <summary>
    /// Converts the given number of seconds to a count of milliseconds
    /// </summary>
    /// <param name="seconds"></param>
    /// <returns></returns>
    public static int ToMilliseconds(float seconds)
    {
        return (int)(1000 * seconds);
    }

    /// <summary>
    /// Converts the given number of milliseconds to a count of seconds
    /// </summary>
    /// <param name="milliseconds"></param>
    /// <returns></returns>
    public static float ToSeconds(int milliseconds)
    {
        return milliseconds / 1000;
    }

    /// <summary>
    /// Delay the current thread for one tick
    /// </summary>
    public static void Yield()
    {
        Thread.Yield();
    }

    /// <summary>
    /// Delay the current thread for the given number of ticks
    /// <param name="numberOfTicks"></param>
    /// </summary>
    public static void Yield(int numberOfTicks)
    {
        for (int i = 0; i < numberOfTicks; i++)
        {
            Thread.Yield();
        }
    }

    /// <summary>
    /// Delay the current thread for the given number of milliseconds
    /// <param name="milliseconds"></param>
    /// </summary>
    public static void SleepForMilliseconds(int milliseconds)
    {
        Thread.Sleep(milliseconds);
    }

    /// <summary>
    /// Delay the current for the given number of seconds
    /// <param name="seconds"></param>
    /// </summary>
    public static void SleepForSeconds(float seconds)
    {
        Thread.Sleep(ToMilliseconds(seconds));
    }


    // MAIN THREAD

    /// <summary>
    /// Returns whether the main thread is still running
    /// </summary>
    /// <returns></returns>
    public static bool IsMainThreadActive()
    {
        return threads.Contains(main);
    }

    /// <summary>
    /// Retrieves the cancellation token of the main thread
    /// </summary>
    public static bool GetMainThreadCancellationToken()
    {
        return cancellationTokens[main];
    }

    /// <summary>
    /// Joins and locks the given non-running thread until after the main thread finishes and returns whether it was successful
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool FollowMainThread(Thread thread)
    {
        return Follow(thread, main);
    }

    /// <summary>
    /// Locks the main thread until it is cancelled (current thread must be main thread)
    /// </summary>
    public static void LockMainThread()
    {
        if (current == main)
        {
            while (!cancellationTokens[main]) { }
        }
    }

    /// <summary>
    /// Call this function to properly end the main thread (non-background threads will continue until they complete).
    /// </summary>
    /// <param name="cancelAllThreads"></param>
    public static void EndMainThread(bool cancelAllThreads = false)
    {
        threads.RemoveAt(0);

        threadNames.Remove(main.Name);

        runningThreads.RemoveAt(0);

        cancellationTokens.Remove(main);

        if (cancelAllThreads)
        {
            CancelAll();
        }
    }
}
