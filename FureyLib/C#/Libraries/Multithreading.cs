
// Static Multithreading Function Library Script
// by Kyle Furey

using System;
using System.Collections.Generic;
using System.Reflection;
using System.Threading;

// Include this heading to use the class
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
    /// All of the running thread's cancellation tokens (KEY = THREAD, VALUE = CANCELLED)
    /// </summary>
    private static Dictionary<Thread, bool> cancellationTokens = new Dictionary<Thread, bool>();

    /// <summary>
    /// All of the running thread's locking threads (KEY = LOCKED THREAD, VALUE = THREAD LOCKING KEY)
    /// </summary>
    private static Dictionary<Thread, Thread> lockedThreads = new Dictionary<Thread, Thread>();

    /// <summary>
    /// The total number of active threads
    /// </summary>
    public static int totalActiveThreads
    {
        get
        {
            SetMainThread();

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
            SetMainThread();

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
            SetMainThread();

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
            SetMainThread();

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
            SetMainThread();

            return Thread.CurrentThread;
        }
    }


    // MAIN THREAD

    /// <summary>
    /// Stores the main thread (automatically called)
    /// </summary>
    private static void SetMainThread()
    {
        if (_main == null)
        {
            _main = Thread.CurrentThread;

            Thread.CurrentThread.Name = "Main Thread";

            threads.Add(_main);

            threadNames["Main Thread"] = _main;

            runningThreads.Add(_main);

            cancellationTokens[Thread.CurrentThread] = false;
        }
    }

    /// <summary>
    /// Returns whether the main thread is still running
    /// </summary>
    /// <returns></returns>
    public static bool IsMainThreadActive()
    {
        SetMainThread();

        return main.IsAlive;
    }

    /// <summary>
    /// Retrieves the cancellation token of the main thread
    /// </summary>
    public static bool GetMainThreadCancellationToken()
    {
        SetMainThread();

        return cancellationTokens[main];
    }

    /// <summary>
    /// Joins and completes the given non-running thread before the main thread resumes and returns whether it was successful
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool JoinMainThread(Thread thread)
    {
        return Join(thread);
    }

    /// <summary>
    /// Joins and locks the given non-running thread until after the main thread finishes and returns whether it was successful    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool FollowMainThread(Thread thread)
    {
        return Follow(thread);
    }

    /// <summary>
    /// Call this function when the main thread ends
    /// </summary>
    public static void TerminateMainThread(bool cancelAll = false)
    {
        SetMainThread();

        threads.Remove(main);

        threadNames.Remove(main.Name);

        runningThreads.Remove(main);

        cancellationTokens.Remove(main);

        lockedThreads.Remove(main);

        if (cancelAll)
        {
            CancelAll();
        }
    }

    /// <summary>
    /// Call this function when the main thread ends
    /// </summary>
    public static void CancelMainThread(bool cancelAll = false)
    {
        TerminateMainThread(cancelAll);
    }

    /// <summary>
    /// Call this function when the main thread ends
    /// </summary>
    public static void EndMainThread(bool cancelAll = false)
    {
        TerminateMainThread(cancelAll);
    }


    // GETTERS

    /// <summary>
    /// Returns the first active thread of the given name (the thread must have been assigned a name on creation)
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    public static Thread Get(string name)
    {
        SetMainThread();

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
        SetMainThread();

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
        SetMainThread();

        return threads;
    }

    /// <summary>
    /// Returns a dictionary of the active thread names to threads
    /// </summary>
    /// <returns></returns>
    public static Dictionary<string, Thread> GetThreadNames()
    {
        SetMainThread();

        return threadNames;
    }

    /// <summary>
    /// Returns a list of the active and running threads in order
    /// </summary>
    public static List<Thread> GetRunningThreads()
    {
        SetMainThread();

        return runningThreads;
    }

    /// <summary>
    /// Returns a dictionary of the currently locked threads to what thread is locking them
    /// </summary>
    public static Dictionary<Thread, Thread> GetLockedThreads()
    {
        SetMainThread();

        return lockedThreads;
    }

    /// <summary>
    /// Returns the total number of active threads 
    /// </summary>
    /// <returns></returns>
    public static int ActiveCount()
    {
        SetMainThread();

        return threads.Count;
    }

    /// <summary>
    /// Returns the total number of running threads 
    /// </summary>
    /// <returns></returns>
    public static int RunningCount()
    {
        SetMainThread();

        return threads.Count;
    }

    /// <summary>
    /// Get the name of the current running thread
    /// </summary>
    /// <returns></returns>
    public static string GetName()
    {
        SetMainThread();

        return current.Name;
    }

    /// <summary>
    /// Get the program's main thread
    /// </summary>
    /// <returns></returns>
    public static Thread Main()
    {
        SetMainThread();

        return main;
    }

    /// <summary>
    /// Get the current running thread
    /// </summary>
    /// <returns></returns>
    public static Thread Current()
    {
        SetMainThread();

        return current;
    }


    // ACTIVE AND RUNNING

    /// <summary>
    /// Returns whether the given thread is currently active
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool IsActive(Thread thread)
    {
        SetMainThread();

        return threads.Contains(thread);
    }

    /// <summary>
    /// Returns whether the given thread is currently running
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool IsRunning(Thread thread)
    {
        SetMainThread();

        return thread.IsAlive;
    }

    /// <summary>
    /// Returns whether the given thread is not active and not currently running (and therefore can be started)
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool IsReady(Thread thread)
    {
        SetMainThread();

        return threads.Contains(thread) && !thread.IsAlive;
    }


    // LOCKING THREAD

    /// <summary>
    /// Delays the current thread until the given condition is met
    /// </summary>
    /// <param name="condition"></param>
    public static void Lock(ref bool condition)
    {
        SetMainThread();

        while (!condition) { Thread.Yield(); }
    }

    /// <summary>
    /// Delays the current thread until the given thread completes
    /// </summary>
    /// <param name="condition"></param>
    public static void Lock(Thread thread)
    {
        SetMainThread();

        while (threads.Contains(thread) && thread.IsAlive) { Thread.Yield(); }
    }


    // NEW THREADS

    /// <summary>
    /// Creates a new thread that can run code independently of other threads.
    /// </summary>
    /// <param name="method">The code this thread will execute. Use a lambda function "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(Action method)
    {
        SetMainThread();

        Thread newThread = null;

        newThread = new Thread(() =>
        {
            if (lockedThreads.ContainsKey(newThread))
            {
                Lock(lockedThreads[newThread]);

                lockedThreads.Remove(newThread);
            }

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);

            lockedThreads.Remove(newThread);
        });

        threads.Add(newThread);

        cancellationTokens[newThread] = false;

        newThread.Name = "New Thread";

        newThread.IsBackground = true;

        newThread.Priority = ThreadPriority.Normal;

        newThread.Start();

        return newThread;
    }

    /// <summary>
    /// Creates a new thread that can run code independently of other threads.
    /// </summary>
    /// <param name="start">Whether to run this thread immediately.</param>
    /// <param name="method">The code this thread will execute. Use a lambda function "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(bool start, Action method)
    {
        SetMainThread();

        Thread newThread = null;

        newThread = new Thread(() =>
        {
            if (lockedThreads.ContainsKey(newThread))
            {
                Lock(lockedThreads[newThread]);

                lockedThreads.Remove(newThread);
            }

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);

            lockedThreads.Remove(newThread);
        });

        threads.Add(newThread);

        cancellationTokens[newThread] = false;

        newThread.Name = "New Thread";

        newThread.IsBackground = true;

        newThread.Priority = ThreadPriority.Normal;

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
    /// <param name="method">The code this thread will execute. Use a lambda function "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(bool start, bool join, Action method)
    {
        SetMainThread();

        Thread newThread = null;

        newThread = new Thread(() =>
        {
            if (lockedThreads.ContainsKey(newThread))
            {
                Lock(lockedThreads[newThread]);

                lockedThreads.Remove(newThread);
            }

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);

            lockedThreads.Remove(newThread);
        });

        threads.Add(newThread);

        cancellationTokens[newThread] = false;

        newThread.Name = "New Thread";

        newThread.IsBackground = true;

        newThread.Priority = ThreadPriority.Normal;

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
    /// <param name="method">The code this thread will execute. Use a lambda function "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(bool start, bool join, string name, Action method)
    {
        SetMainThread();

        Thread newThread = null;

        newThread = new Thread(() =>
        {
            if (lockedThreads.ContainsKey(newThread))
            {
                Lock(lockedThreads[newThread]);

                lockedThreads.Remove(newThread);
            }

            method.Invoke();

            threads.Remove(newThread);

            threadNames.Remove(name);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);

            lockedThreads.Remove(newThread);
        });

        threads.Add(newThread);

        cancellationTokens[newThread] = false;

        newThread.Name = name;

        threadNames[newThread.Name] = newThread;

        newThread.IsBackground = true;

        newThread.Priority = ThreadPriority.Normal;

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
    /// <param name="method">The code this thread will execute. Use a lambda function "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(bool start, bool join, string name, bool isBackground, Action method)
    {
        SetMainThread();

        Thread newThread = null;

        newThread = new Thread(() =>
        {
            if (lockedThreads.ContainsKey(newThread))
            {
                Lock(lockedThreads[newThread]);

                lockedThreads.Remove(newThread);
            }

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            threadNames.Remove(name);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);

            lockedThreads.Remove(newThread);
        });

        threads.Add(newThread);

        cancellationTokens[newThread] = false;

        newThread.Name = name;

        threadNames[newThread.Name] = newThread;

        newThread.IsBackground = isBackground;

        newThread.Priority = ThreadPriority.Normal;

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
    /// <param name="method">The code this thread will execute. Use a lambda function "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(bool start, bool join, string name, bool isBackground, ThreadPriority priority, Action method)
    {
        SetMainThread();

        Thread newThread = null;

        newThread = new Thread(() =>
        {
            if (lockedThreads.ContainsKey(newThread))
            {
                Lock(lockedThreads[newThread]);

                lockedThreads.Remove(newThread);
            }

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            threadNames.Remove(name);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);

            lockedThreads.Remove(newThread);
        });

        threads.Add(newThread);

        cancellationTokens[newThread] = false;

        newThread.Name = name;

        threadNames[newThread.Name] = newThread;

        newThread.IsBackground = isBackground;

        newThread.Priority = priority;

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
    /// <param name="method">The code this thread will execute. Use a lambda function "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(Thread followedThread, Action method)
    {
        SetMainThread();

        Thread newThread = null;

        newThread = new Thread(() =>
        {
            Lock(followedThread);

            lockedThreads.Remove(newThread);

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);

            lockedThreads.Remove(newThread);
        });

        threads.Add(newThread);

        cancellationTokens[newThread] = false;

        newThread.Name = "New Thread";

        newThread.IsBackground = true;

        newThread.Priority = ThreadPriority.Normal;

        newThread.Start();

        return newThread;
    }

    /// <summary>
    /// Creates a new thread that can run code independently of other threads.
    /// </summary>
    /// <param name="followedThread">The thread to follow this new thread after.</param>
    /// <param name="name">The name of this thread.</param>
    /// <param name="method">The code this thread will execute. Use a lambda function "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(Thread followedThread, string name, Action method)
    {
        SetMainThread();

        Thread newThread = null;

        newThread = new Thread(() =>
        {
            Lock(followedThread);

            lockedThreads.Remove(newThread);

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);

            lockedThreads.Remove(newThread);
        });

        threads.Add(newThread);

        cancellationTokens[newThread] = false;

        newThread.Name = name;

        threadNames[newThread.Name] = newThread;

        newThread.IsBackground = true;

        newThread.Priority = ThreadPriority.Normal;

        newThread.Start();

        return newThread;
    }

    /// <summary>
    /// Creates a new thread that can run code independently of other threads.
    /// </summary>
    /// <param name="followedThread">The thread to follow this new thread after.</param>
    /// <param name="name">The name of this thread.</param>
    /// <param name="isBackground">Whether this thread will terminate when the main thread ends.</param>
    /// <param name="method">The code this thread will execute. Use a lambda function "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(Thread followedThread, string name, bool isBackground, Action method)
    {
        SetMainThread();

        Thread newThread = null;

        newThread = new Thread(() =>
        {
            Lock(followedThread);

            lockedThreads.Remove(newThread);

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);

            lockedThreads.Remove(newThread);
        });

        threads.Add(newThread);

        cancellationTokens[newThread] = false;

        newThread.Name = name;

        threadNames[newThread.Name] = newThread;

        newThread.IsBackground = isBackground;

        newThread.Priority = ThreadPriority.Normal;

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
    /// <param name="method">The code this thread will execute. Use a lambda function "() => { }" to add code.</param>
    /// <returns>The newly created thread.</returns>
    public static Thread NewThread(Thread followedThread, string name, bool isBackground, ThreadPriority priority, Action method)
    {
        SetMainThread();

        Thread newThread = null;

        newThread = new Thread(() =>
        {
            Lock(followedThread);

            lockedThreads.Remove(newThread);

            runningThreads.Add(newThread);

            method.Invoke();

            threads.Remove(newThread);

            runningThreads.Remove(newThread);

            cancellationTokens.Remove(newThread);

            lockedThreads.Remove(newThread);
        });

        threads.Add(newThread);

        cancellationTokens[newThread] = false;

        newThread.Name = name;

        threadNames[newThread.Name] = newThread;

        newThread.IsBackground = isBackground;

        newThread.Priority = priority;

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
    public static bool Start(Thread thread, bool join)
    {
        SetMainThread();

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
        SetMainThread();

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
        SetMainThread();

        if (lockedThreads.ContainsKey(thread))
        {
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
    /// <param name="followingThread"></param>
    /// <returns></returns>
    public static bool Follow(Thread thread, Thread followingThread)
    {
        SetMainThread();

        if (lockedThreads.ContainsKey(thread))
        {
            lockedThreads[thread] = followingThread;
        }
        else if (threads.Contains(thread) && !thread.IsAlive)
        {
            if (current == main)
            {
                thread.IsBackground = false;
            }

            lockedThreads[thread] = followingThread;

            thread.Start();
        }
        else
        {
            return false;
        }

        return true;
    }


    // TERMINATING THREADS

    /// <summary>
    /// Gets the current thread's cancellation token (set to true on when Terminate() is called)
    /// </summary>
    /// <returns></returns>
    public static bool GetCancellationToken()
    {
        SetMainThread();

        return cancellationTokens[current];
    }

    /// <summary>
    /// Gets the given thread's cancellation token (set to true on when Terminate() is called)
    /// </summary>
    /// <returns></returns>
    public static bool GetCancellationToken(Thread thread)
    {
        SetMainThread();

        return cancellationTokens[thread];
    }

    /// <summary>
    /// Cancels the current thread and returns whether it was successful. You need to program cancellation logic in the thread using GetCancellationToken() for it to cancel.
    /// </summary>
    /// <returns></returns>
    public static bool Terminate()
    {
        SetMainThread();

        if (runningThreads.Contains(current) && current.IsAlive)
        {
            cancellationTokens[current] = true;

            if (current == main)
            {
                TerminateMainThread();
            }
        }
        else
        {
            return false;
        }

        return true;
    }

    /// <summary>
    /// Cancels the given thread and returns whether it was successful. You need to program cancellation logic in the thread using GetToken() for it to cancel.
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool Terminate(Thread thread)
    {
        SetMainThread();

        if (runningThreads.Contains(thread) && thread.IsAlive)
        {
            cancellationTokens[thread] = true;

            if (thread == main)
            {
                TerminateMainThread();
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
    public static int TerminateAll()
    {
        SetMainThread();

        int count = runningThreads.Count - 1;

        while (runningThreads.Count > 1)
        {
            Terminate(runningThreads[1]);
        }

        return count;
    }

    /// <summary>
    /// Cancels all of the given threads except the current thread. You need to program cancellation logic in the thread using GetCancellationToken() for it to cancel.
    /// </summary>
    /// <returns></returns>
    public static int TerminateOthers()
    {
        SetMainThread();

        int count = runningThreads.Count - 1;

        while (runningThreads[0] != current)
        {
            Terminate(runningThreads[0]);
        }

        while (runningThreads.Count > 1)
        {
            Terminate(runningThreads[1]);
        }

        return count;
    }

    /// <summary>
    /// Cancels the current thread and returns whether it was successful. You need to program cancellation logic in the thread using GetCancellationToken() for it to cancel.
    /// </summary>
    /// <returns></returns>
    public static bool Cancel()
    {
        return Cancel();
    }

    /// <summary>
    /// Cancels the given thread and returns whether it was successful. You need to program cancellation logic in the thread using GetCancellationToken() for it to cancel.
    /// </summary>
    /// <param name="thread"></param>
    /// <returns></returns>
    public static bool Cancel(Thread thread)
    {
        return Cancel(thread);
    }

    /// <summary>
    /// Cancels all of the given threads except the main thread. You need to program cancellation logic in the thread using GetCancellationToken() for it to cancel.
    /// </summary>
    /// <returns></returns>
    public static int CancelAll()
    {
        return TerminateAll();
    }

    /// <summary>
    /// Cancels all of the given threads except the current thread. You need to program cancellation logic in the thread using GetCancellationToken() for it to cancel.
    /// </summary>
    /// <returns></returns>
    public static int CancelOthers()
    {
        return TerminateOthers();
    }


    // DELAYING THREAD
    // CONVERT TO SECONDS

    /// <summary>
    /// Converts the given number of seconds to a count of milliseconds
    /// </summary>
    /// <param name="seconds"></param>
    /// <returns></returns>
    public static int ToMilliseconds(float seconds)
    {
        SetMainThread();

        return (int)(1000 * seconds);
    }

    /// <summary>
    /// Converts the given number of milliseconds to a count of seconds
    /// </summary>
    /// <param name="milliseconds"></param>
    /// <returns></returns>
    public static float ToSeconds(int milliseconds)
    {
        SetMainThread();

        return milliseconds / 1000;
    }

    /// <summary>
    /// Delay the current thread for one tick
    /// </summary>
    public static void Yield()
    {
        SetMainThread();

        Thread.Yield();
    }

    /// <summary>
    /// Delay the current thread for the given number of ticks
    /// <param name="numberOfTicks"></param>
    /// </summary>
    public static void Yield(int numberOfTicks)
    {
        SetMainThread();

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
        SetMainThread();

        Thread.Sleep(milliseconds);
    }

    /// <summary>
    /// Delay the current for the given number of seconds
    /// <param name="seconds"></param>
    /// </summary>
    public static void SleepForSeconds(float seconds)
    {
        SetMainThread();

        Thread.Sleep(ToMilliseconds(seconds));
    }

    /// <summary>
    /// Delay the current thread for one tick
    /// </summary>
    public static void DelayForTick()
    {
        Yield();
    }

    /// <summary>
    /// Delay the current thread for the given number of ticks
    /// <param name="numberOfTicks"></param>
    /// </summary>
    public static void DelayForTicks(int numberOfTicks)
    {
        Yield(numberOfTicks);
    }

    /// <summary>
    /// Delay the current thread for the given number of milliseconds
    /// <param name="milliseconds"></param>
    /// </summary>
    public static void DelayForMilliseconds(int milliseconds)
    {
        SleepForMilliseconds(milliseconds);
    }

    /// <summary>
    /// Delay the current for the given number of seconds
    /// <param name="seconds"></param>
    /// </summary>
    public static void DelayForSeconds(float seconds)
    {
        SleepForSeconds(seconds);
    }
}
