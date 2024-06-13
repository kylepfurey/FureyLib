
// Static Asynchronous Function Library Script
// by Kyle Furey

using System;
using System.Threading;
using System.Threading.Tasks;

// Include this heading to use the class
using static Async;

/// <summary>
/// Creates and runs asynchronous tasks.
/// </summary>
public static class Async
{
    // RUN FUNCTION

    /// <summary>
    /// Runs the given function asynchronously
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public static async Task Run(Action function)
    {
        await Task.Run(function);
    }

    /// <summary>
    /// Runs the given function asynchronously and returns the result
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <param name="function"></param>
    /// <returns></returns>
    public static async Task<ReturnType> Run<ReturnType>(Func<ReturnType> function)
    {
        ReturnType returns = await Task.Run(function);

        return returns;
    }

    /// <summary>
    /// Runs the given function asynchronously and returns the result
    /// </summary>
    /// <param name="function"></param>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public static async Task Run(Delegate function, params object[] parameters)
    {
        await Task.Run(() => { function.DynamicInvoke(parameters); });
    }

    /// <summary>
    /// Runs the given function asynchronously and returns the result
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <param name="function"></param>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public static async Task<ReturnType> Run<ReturnType>(Delegate function, params object[] parameters)
    {
        ReturnType returns = await Task.Run(ReturnType () => { return (ReturnType)function.DynamicInvoke(parameters); });

        return returns;
    }


    // CONVERT TO SECONDS

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


    // DELAY FOR ONE TICK

    /// <summary>
    /// Delays the current thread by one tick when awaited
    /// </summary>
    /// <returns></returns>
    public static async Task DelayForTick()
    {
        await Task.Yield();
    }

    /// <summary>
    /// Invokes the given parameterless void function after one tick
    /// </summary>
    /// <param name="function"></param>
    public static async Task InvokeAfterTick(Action function)
    {
        await DelayForTick();

        function.Invoke();
    }

    /// <summary>
    /// Invokes the given parameterless function after one tick and returns the result
    /// </summary>
    /// <typeparam></typeparam>
    /// <param name="function"></param>
    public static async Task<ReturnType> InvokeAfterTick<ReturnType>(Func<ReturnType> function)
    {
        await DelayForTick();

        return function.Invoke();
    }

    /// <summary>
    /// Invokes the given void function after one tick
    /// </summary>
    /// <param name="function"></param>
    /// <param name="parameters"></param>
    public static async Task InvokeAfterTick(Delegate function, params object[] parameters)
    {
        await DelayForTick();

        function.DynamicInvoke(parameters);
    }

    /// <summary>
    /// Invokes the given function after one tick and returns the result
    /// </summary>
    /// <typeparam></typeparam>
    /// <param name="function"></param>
    /// <param name="parameters"></param>
    public static async Task<ReturnType> InvokeAfterTick<ReturnType>(Delegate function, params object[] parameters)
    {
        await DelayForTick();

        return (ReturnType)function.DynamicInvoke(parameters);
    }


    // DELAY FOR TICKS

    /// <summary>
    /// Delays the current thread by the given number of ticks when awaited
    /// </summary>
    /// <returns></returns>
    public static async Task DelayForTicks(int numberOfTicks)
    {
        for (int i = 0; i < numberOfTicks; i++)
        {
            await Task.Yield();
        }
    }

    /// <summary>
    /// Invokes the given parameterless void function after the given number of ticks
    /// </summary>
    /// <param name="function"></param>
    public static async Task InvokeAfterTicks(int numberOfTicks, Action function)
    {
        await DelayForTicks(numberOfTicks);

        function.Invoke();
    }

    /// <summary>
    /// Invokes the given parameterless function after the given number of ticks and returns the result
    /// </summary>
    /// <typeparam></typeparam>
    /// <param name="function"></param>
    public static async Task<ReturnType> InvokeAfterTicks<ReturnType>(int numberOfTicks, Func<ReturnType> function)
    {
        await DelayForTicks(numberOfTicks);

        return function.Invoke();
    }

    /// <summary>
    /// Invokes the given void function after the given number of ticks
    /// </summary>
    /// <param name="function"></param>
    /// <param name="parameters"></param>
    public static async Task InvokeAfterTicks(int numberOfTicks, Delegate function, params object[] parameters)
    {
        await DelayForTicks(numberOfTicks);

        function.DynamicInvoke(parameters);
    }

    /// <summary>
    /// Invokes the given function after the given number of ticks and returns the result
    /// </summary>
    /// <typeparam></typeparam>
    /// <param name="function"></param>
    /// <param name="parameters"></param>
    public static async Task<ReturnType> InvokeAfterTicks<ReturnType>(int numberOfTicks, Delegate function, params object[] parameters)
    {
        await DelayForTicks(numberOfTicks);

        return (ReturnType)function.DynamicInvoke(parameters);
    }


    // DELAY FOR MILLISECONDS

    /// <summary>
    /// Delays the current thread by the given number of milliseconds when awaited
    /// </summary>
    /// <param name="milliseconds"></param>
    /// <returns></returns>
    public static async Task DelayForMilliseconds(int milliseconds)
    {
        await Task.Delay(milliseconds);
    }

    /// <summary>
    /// Invokes the given parameterless void function after the given number of milliseconds
    /// </summary>
    /// <param name="function"></param>
    /// <param name="milliseconds"></param>
    public static async Task InvokeAfterMilliseconds(int milliseconds, Action function)
    {
        await DelayForMilliseconds(milliseconds);

        function.Invoke();
    }

    /// <summary>
    /// Invokes the given parameterless function after the given number of milliseconds and returns the result
    /// </summary>
    /// <typeparam></typeparam>
    /// <param name="function"></param>
    /// <param name="milliseconds"></param>
    public static async Task<ReturnType> InvokeAfterMilliseconds<ReturnType>(int milliseconds, Func<ReturnType> function)
    {
        await DelayForSeconds(milliseconds);

        return function.Invoke();
    }

    /// <summary>
    /// Invokes the given void function after the given number of milliseconds
    /// </summary>
    /// <param name="function"></param>
    /// <param name="parameters"></param>
    public static async Task InvokeAfterMilliseconds(int milliseconds, Delegate function, params object[] parameters)
    {
        await DelayForMilliseconds(milliseconds);

        function.DynamicInvoke(parameters);
    }

    /// <summary>
    /// Invokes the given function after the given number of milliseconds and returns the result
    /// </summary>
    /// <typeparam></typeparam>
    /// <param name="function"></param>
    /// <param name="parameters"></param>
    public static async Task<ReturnType> InvokeAfterMilliseconds<ReturnType>(int milliseconds, Delegate function, params object[] parameters)
    {
        await DelayForMilliseconds(milliseconds);

        return (ReturnType)function.DynamicInvoke(parameters);
    }


    // DELAY FOR SECONDS

    /// <summary>
    /// Delays the current thread by the given number of seconds when awaited
    /// </summary>
    /// <param name="seconds"></param>
    /// <returns></returns>
    public static async Task DelayForSeconds(float seconds)
    {
        await Task.Delay(ToMilliseconds(seconds));
    }

    /// <summary>
    /// Invokes the given parameterless void function after the given number of seconds
    /// </summary>
    /// <param name="function"></param>
    /// <param name="seconds"></param>
    public static async Task InvokeAfterSeconds(float seconds, Action function)
    {
        await DelayForSeconds(seconds);

        function.Invoke();
    }

    /// <summary>
    /// Invokes the given parameterless function after the given number of seconds and returns the result
    /// </summary>
    /// <typeparam></typeparam>
    /// <param name="function"></param>
    /// <param name="seconds"></param>
    public static async Task<ReturnType> InvokeAfterSeconds<ReturnType>(float seconds, Func<ReturnType> function)
    {
        await DelayForSeconds(seconds);

        return function.Invoke();
    }

    /// <summary>
    /// Invokes the given void function after the given number of seconds
    /// </summary>
    /// <param name="function"></param>
    /// <param name="parameters"></param>
    public static async Task InvokeAfterSeconds(float seconds, Delegate function, params object[] parameters)
    {
        await DelayForSeconds(seconds);

        function.DynamicInvoke(parameters);
    }

    /// <summary>
    /// Invokes the given function after the given number of seconds and returns the result
    /// </summary>
    /// <typeparam></typeparam>
    /// <param name="function"></param>
    /// <param name="parameters"></param>
    public static async Task<ReturnType> InvokeAfterSeconds<ReturnType>(float seconds, Delegate function, params object[] parameters)
    {
        await DelayForSeconds(seconds);

        return (ReturnType)function.DynamicInvoke(parameters);
    }


    // AWAIT

    /// <summary>
    /// Delays the current thread until the given condition is met
    /// </summary>
    /// <param name="condition"></param>
    public static void Await(ref bool condition)
    {
        while (!condition) { Thread.Yield(); }
    }

    /// <summary>
    /// Delays the current thread until the given task is complete
    /// </summary>
    /// <param name="task"></param>
    public static void Await(Task task)
    {
        while (!task.IsCompleted) { Thread.Yield(); }
    }

    /// <summary>
    /// Delays the current thread until the given task is complete
    /// </summary>
    /// <param name="task"></param>
    public static ReturnType Await<ReturnType>(Task<ReturnType> task)
    {
        while (!task.IsCompleted) { Thread.Yield(); }

        return task.Result;
    }
}
