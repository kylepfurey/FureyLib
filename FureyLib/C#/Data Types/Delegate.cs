
// Delegate and Event Data Types Script
// by Kyle Furey

using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using System.Diagnostics;

// Define the function class
using Function = System.Delegate;

/// <summary>
/// Wrapper class for a collection of functions.
/// All stored functions must have no parameters.
/// </summary>
public class Event : IEnumerable
{
    // STATIC DELEGATE DATA

    /// <summary>
    /// Global list of all delegates
    /// </summary>
    private static List<Event> allDelegates = new List<Event>();

    /// <summary>
    /// Global delegate cancellation token
    /// </summary>
    private static bool cancelAll = false;

    /// <summary>
    /// Index of current invoked delegate
    /// </summary>
    private static int invokeIndex = 0;


    // DELEGATE DATA

    /// <summary>
    /// List of functions included in the delegate
    /// </summary>
    private List<Action> functions = new List<Action>();

    /// <summary>
    /// Whether the delegate is currently invoking functions
    /// </summary>
    private bool isInvoking = false;

    /// <summary>
    /// Delegate cancellation token
    /// </summary>
    private bool cancel = false;

    /// <summary>
    /// Index of current delegate
    /// </summary>
    private int index = 0;


    // DELEGATE CONSTRUCTORS AND DECONSTRUCTOR

    /// <summary>
    /// Default constructor
    /// </summary>
    public Event()
    {
        functions = new List<Action>();

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="functions"></param>
    public Event(params Action[] functions)
    {
        this.functions = new List<Action>(functions.Length);

        for (int i = 0; i < functions.Length; i++)
        {
            this.functions.Add(functions[i]);
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// List constructor
    /// </summary>
    /// <param name="functions"></param>
    public Event(List<Action> functions)
    {
        this.functions = functions;

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Delegate constructor
    /// </summary>
    /// <param name="newDelegate"></param>
    public Event(Event newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            functions.Add(newDelegate.functions[i]);
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Deconstructor
    /// </summary>
    ~Event()
    {
        for (int i = index + 1; i < allDelegates.Count; i++)
        {
            allDelegates[i].index--;
        }

        allDelegates.Remove(this);
    }


    // DELEGATE FUNCTIONS

    /// <summary>
    /// Call each function in the delegate and return if the invoke was successful
    /// </summary>
    /// <returns></returns>
    public bool Invoke()
    {
        cancel = false;

        cancelAll = false;

        invokeIndex = index;

        isInvoking = true;

        for (int i = 0; i < functions.Count; i++)
        {
            functions[i].Invoke();

            if (cancel || cancelAll)
            {
                isInvoking = false;

                return false;
            }
        }

        isInvoking = false;

        return true;
    }

    /// <summary>
    /// Invokes every delegate
    /// </summary>
    /// <returns></returns>
    public static bool InvokeAll()
    {
        for (int i = 0; i < allDelegates.Count; i++)
        {
            if (!allDelegates[i].Invoke())
            {
                return false;
            }
        }

        return true;
    }

    /// <summary>
    /// Reinvokes the current delegate
    /// </summary>
    /// <returns></returns>
    public static bool InvokeCurrent()
    {
        return allDelegates[invokeIndex].Invoke();
    }

    /// <summary>
    /// Cancel an invoke
    /// </summary>
    public void Cancel()
    {
        cancel = true;
    }

    /// <summary>
    /// Cancel all invokes
    /// </summary>
    public static void CancelAll()
    {
        cancelAll = true;
    }

    /// <summary>
    /// Cancel the current invoke
    /// </summary>
    public static void CancelCurrent()
    {
        allDelegates[invokeIndex].cancel = true;
    }

    /// <summary>
    /// Returns whether the delegate is currently being invoked
    /// </summary>
    /// <returns></returns>
    public bool IsInvoking()
    {
        return isInvoking;
    }


    // COLLECTION FUNCTIONS

    /// <summary>
    /// Gets a function in the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public Action Get(int index)
    {
        return functions[index];
    }

    /// <summary>
    /// Sets a function in the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public Event Set(int index, Action function)
    {
        functions[index] = function;

        return this;
    }

    /// <summary>
    /// Add a new function to the delegate
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public Event Add(Action function)
    {
        functions.Add(function);

        return this;
    }

    /// <summary>
    /// Adds new functions to the delegate
    /// </summary>
    /// <param name="functions"></param>
    /// <returns></returns>
    public Event Add(params Action[] functions)
    {
        for (int i = 0; i < functions.Length; i++)
        {
            this.functions.Add(functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Adds new functions to the delegate
    /// </summary>
    /// <param name="functions"></param>
    /// <returns></returns>
    public Event Add(List<Action> functions)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            this.functions.Add(functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Adds another delegate to the delegate
    /// </summary>
    /// <param name="newDelegate"></param>
    /// <returns></returns>
    public Event Add(Event newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            functions.Add(newDelegate.functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Remove a function from the delegate
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public Event Remove(Action function)
    {
        functions.Remove(function);

        return this;
    }

    /// <summary>
    /// Removes a delegate's functions from the delegate
    /// </summary>
    /// <param name="removedDelegate"></param>
    /// <returns></returns>
    public Event Remove(Event removedDelegate)
    {
        for (int i = 0; i < removedDelegate.functions.Count; i++)
        {
            functions.Remove(removedDelegate.functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Remove a function from the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public Event RemoveAt(int index)
    {
        functions.RemoveAt(index);

        return this;
    }

    /// <summary>
    /// Clear all functions from the delegate
    /// </summary>
    /// <returns></returns>
    public Event Clear()
    {
        functions.Clear();

        return this;
    }

    /// <summary>
    /// Return the number of functions in the delegate
    /// </summary>
    /// <returns></returns>
    public int Count()
    {
        return functions.Count;
    }

    /// <summary>
    /// Returns if the delegate contains a function
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public bool Contains(Action function)
    {
        return functions.Contains(function);
    }

    /// <summary>
    /// Returns the index of the function in the delegate, or -1 if it was not found
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public int Find(Action function)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            if (functions[i].Equals(function))
            {
                return i;
            }
        }

        return -1;
    }

    /// <summary>
    /// Returns an array of the functions
    /// </summary>
    /// <returns></returns>
    public Action[] ToArray()
    {
        return functions.ToArray();
    }

    /// <summary>
    /// Returns a list of the functions
    /// </summary>
    /// <returns></returns>
    public List<Action> ToList()
    {
        return functions;
    }


    // COLLECTION OPERATORS

    /// <summary>
    /// Adding a function
    /// </summary>
    /// <param name="Delegate"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public static Event operator +(Event Delegate, Action function)
    {
        return Delegate.Add(function);
    }

    /// <summary>
    /// Removing a function
    /// </summary>
    /// <param name="Delegate"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public static Event operator -(Event Delegate, Action function)
    {
        return Delegate.Remove(function);
    }


    // ENUMERATOR FUNCTION

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return functions.GetEnumerator();
    }
}

/// <summary>
/// Wrapper class for a collection of functions.
/// All stored functions must share the same return type.
/// All stored functions must have no parameters.
/// </summary>
public class Event<ReturnType> : IEnumerable
{
    // STATIC DELEGATE DATA

    /// <summary>
    /// Global list of all delegates
    /// </summary>
    private static List<Event<ReturnType>> allDelegates = new List<Event<ReturnType>>();

    /// <summary>
    /// Global delegate cancellation token
    /// </summary>
    private static bool cancelAll = false;

    /// <summary>
    /// Index of current invoked delegate
    /// </summary>
    private static int invokeIndex = 0;


    // DELEGATE DATA

    /// <summary>
    /// List of functions included in the delegate
    /// </summary>
    private List<Func<ReturnType>> functions = new List<Func<ReturnType>>();

    /// <summary>
    /// Whether the delegate is currently invoking functions
    /// </summary>
    private bool isInvoking = false;

    /// <summary>
    /// Delegate cancellation token
    /// </summary>
    private bool cancel = false;

    /// <summary>
    /// Index of current delegate
    /// </summary>
    private int index = 0;


    // DELEGATE CONSTRUCTORS AND DECONSTRUCTOR

    /// <summary>
    /// Default constructor
    /// </summary>
    public Event()
    {
        functions = new List<Func<ReturnType>>();

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="functions"></param>
    public Event(params Func<ReturnType>[] functions)
    {
        this.functions = new List<Func<ReturnType>>(functions.Length);

        for (int i = 0; i < functions.Length; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }

            this.functions.Add(functions[i]);
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// List constructor
    /// </summary>
    /// <param name="functions"></param>
    public Event(List<Func<ReturnType>> functions)
    {
        this.functions = functions;

        for (int i = 0; i < functions.Count; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Delegate constructor
    /// </summary>
    /// <param name="newDelegate"></param>
    public Event(Event<ReturnType> newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }

            functions.Add(newDelegate.functions[i]);
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Deconstructor
    /// </summary>
    ~Event()
    {
        for (int i = index + 1; i < allDelegates.Count; i++)
        {
            allDelegates[i].index--;
        }

        allDelegates.Remove(this);
    }


    // DELEGATE FUNCTIONS

    /// <summary>
    /// Returns a dictionary with each key representing the function and the value being the returned data
    /// </summary>
    /// <returns></returns>
    public Dictionary<Func<ReturnType>, ReturnType> Invoke()
    {
        cancel = false;

        cancelAll = false;

        invokeIndex = index;

        isInvoking = true;

        Dictionary<Func<ReturnType>, ReturnType> returns = new Dictionary<Func<ReturnType>, ReturnType>(functions.Count);

        for (int i = 0; i < functions.Count; i++)
        {
            try
            {
                returns[functions[i]] = (ReturnType)functions[i].DynamicInvoke();
            }
            catch
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not invoke the given delegate! Invoked parameters did not match the delegate type!");
            }

            if (cancel || cancelAll)
            {
                for (int j = i + 1; j < functions.Count; j++)
                {
                    returns[functions[i]] = default(ReturnType);
                }

                break;
            }
        }

        isInvoking = false;

        return returns;
    }

    /// <summary>
    /// Invokes every delegate
    /// </summary>
    /// <returns></returns>
    public static Dictionary<Event<ReturnType>, Dictionary<Func<ReturnType>, ReturnType>> InvokeAll()
    {
        Dictionary<Event<ReturnType>, Dictionary<Func<ReturnType>, ReturnType>> returns = new Dictionary<Event<ReturnType>, Dictionary<Func<ReturnType>, ReturnType>>(allDelegates.Count);

        for (int i = 0; i < allDelegates.Count; i++)
        {
            returns[allDelegates[i]] = allDelegates[i].Invoke();

            if (allDelegates[i].cancel || cancelAll)
            {
                break;
            }
        }

        return returns;
    }

    /// <summary>
    /// Reinvokes the current delegate
    /// </summary>
    /// <returns></returns>
    public static Dictionary<Func<ReturnType>, ReturnType> InvokeCurrent()
    {
        return allDelegates[invokeIndex].Invoke();
    }

    /// <summary>
    /// Cancel an invoke
    /// </summary>
    public void Cancel()
    {
        cancel = true;
    }

    /// <summary>
    /// Cancel all invokes
    /// </summary>
    public static void CancelAll()
    {
        cancelAll = true;
    }

    /// <summary>
    /// Cancel the current invoke
    /// </summary>
    public static void CancelCurrent()
    {
        allDelegates[invokeIndex].cancel = true;
    }

    /// <summary>
    /// Returns whether the delegate is currently being invoked
    /// </summary>
    /// <returns></returns>
    public bool IsInvoking()
    {
        return isInvoking;
    }


    // COLLECTION FUNCTIONS

    /// <summary>
    /// Gets a function in the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public Func<ReturnType> Get(int index)
    {
        return functions[index];
    }

    /// <summary>
    /// Sets a function in the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public Event<ReturnType> Set(int index, Func<ReturnType> function)
    {
        if (typeof(ReturnType) != function.Method.ReturnType)
        {
            Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
        }

        functions[index] = function;

        return this;
    }

    /// <summary>
    /// Add a new function to the delegate
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public Event<ReturnType> Add(Func<ReturnType> function)
    {
        if (typeof(ReturnType) != function.Method.ReturnType)
        {
            Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
        }

        functions.Add(function);

        return this;
    }

    /// <summary>
    /// Adds new functions to the delegate
    /// </summary>
    /// <param name="functions"></param>
    /// <returns></returns>
    public Event<ReturnType> Add(params Func<ReturnType>[] functions)
    {
        for (int i = 0; i < functions.Length; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }

            this.functions.Add(functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Adds new functions to the delegate
    /// </summary>
    /// <param name="functions"></param>
    /// <returns></returns>
    public Event<ReturnType> Add(List<Func<ReturnType>> functions)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }

            this.functions.Add(functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Adds another delegate to the delegate
    /// </summary>
    /// <param name="newDelegate"></param>
    /// <returns></returns>
    public Event<ReturnType> Add(Event<ReturnType> newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }

            functions.Add(newDelegate.functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Remove a function from the delegate
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public Event<ReturnType> Remove(Func<ReturnType> function)
    {
        functions.Remove(function);

        return this;
    }

    /// <summary>
    /// Removes a delegate's functions from the delegate
    /// </summary>
    /// <param name="removedDelegate"></param>
    /// <returns></returns>
    public Event<ReturnType> Remove(Event<ReturnType> removedDelegate)
    {
        for (int i = 0; i < removedDelegate.functions.Count; i++)
        {
            functions.Remove(removedDelegate.functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Remove a function from the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public Event<ReturnType> RemoveAt(int index)
    {
        functions.RemoveAt(index);

        return this;
    }

    /// <summary>
    /// Clear all functions from the delegate
    /// </summary>
    /// <returns></returns>
    public Event<ReturnType> Clear()
    {
        functions.Clear();

        return this;
    }

    /// <summary>
    /// Return the number of functions in the delegate
    /// </summary>
    /// <returns></returns>
    public int Count()
    {
        return functions.Count;
    }

    /// <summary>
    /// Returns if the delegate contains a function
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public bool Contains(Func<ReturnType> function)
    {
        return functions.Contains(function);
    }

    /// <summary>
    /// Returns the index of the function in the delegate, or -1 if it was not found
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public int Find(Func<ReturnType> function)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            if (functions[i].Equals(function))
            {
                return i;
            }
        }

        return -1;
    }

    /// <summary>
    /// Returns an array of the functions
    /// </summary>
    /// <returns></returns>
    public Func<ReturnType>[] ToArray()
    {
        return functions.ToArray();
    }

    /// <summary>
    /// Returns a list of the functions
    /// </summary>
    /// <returns></returns>
    public List<Func<ReturnType>> ToList()
    {
        return functions;
    }


    // COLLECTION OPERATORS

    /// <summary>
    /// Adding a function
    /// </summary>
    /// <param name="Delegate"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public static Event<ReturnType> operator +(Event<ReturnType> Delegate, Func<ReturnType> function)
    {
        return Delegate.Add(function);
    }

    /// <summary>
    /// Removing a function
    /// </summary>
    /// <param name="Delegate"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public static Event<ReturnType> operator -(Event<ReturnType> Delegate, Func<ReturnType> function)
    {
        return Delegate.Remove(function);
    }


    // ENUMERATOR FUNCTION

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return functions.GetEnumerator();
    }
}

/// <summary>
/// Wrapper class for a collection of functions.
/// Only stores functions that have no parameters regardless of return type.
/// </summary>
public class DynamicEvent : IEnumerable
{
    // STATIC DELEGATE DATA

    /// <summary>
    /// Global list of all delegates
    /// </summary>
    private static List<DynamicEvent> allDelegates = new List<DynamicEvent>();

    /// <summary>
    /// Global delegate cancellation token
    /// </summary>
    private static bool cancelAll = false;

    /// <summary>
    /// Index of current invoked delegate
    /// </summary>
    private static int invokeIndex = 0;


    // DELEGATE DATA

    /// <summary>
    /// List of functions included in the delegate
    /// </summary>
    private List<Function> functions = new List<Function>();

    /// <summary>
    /// Whether the delegate is currently invoking functions
    /// </summary>
    private bool isInvoking = false;

    /// <summary>
    /// Delegate cancellation token
    /// </summary>
    private bool cancel = false;

    /// <summary>
    /// Index of current delegate
    /// </summary>
    private int index = 0;


    // DELEGATE CONSTRUCTORS AND DECONSTRUCTOR

    /// <summary>
    /// Default constructor
    /// </summary>
    public DynamicEvent()
    {
        functions = new List<Function>();

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="functions"></param>
    public DynamicEvent(params Function[] functions)
    {
        this.functions = new List<Function>(functions.Length);

        for (int i = 0; i < functions.Length; i++)
        {
            if (functions[i].Method.GetParameters().Length == 0)
            {
                this.functions.Add(functions[i]);
            }
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// List constructor
    /// </summary>
    /// <param name="functions"></param>
    public DynamicEvent(List<Function> functions)
    {
        this.functions = new List<Function>(functions.Count);

        for (int i = 0; i < functions.Count; i++)
        {
            if (functions[i].Method.GetParameters().Length == 0)
            {
                this.functions.Add(functions[i]);
            }
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Delegate constructor
    /// </summary>
    /// <param name="newDelegate"></param>
    public DynamicEvent(DynamicEvent newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            if (newDelegate.functions[i].Method.GetParameters().Length == 0)
            {
                functions.Add(newDelegate.functions[i]);
            }
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Deconstructor
    /// </summary>
    ~DynamicEvent()
    {
        for (int i = index + 1; i < allDelegates.Count; i++)
        {
            allDelegates[i].index--;
        }

        allDelegates.Remove(this);
    }


    // DELEGATE FUNCTIONS

    /// <summary>
    /// Returns a dictionary with each key representing the function and the value being the returned data
    /// </summary>
    /// <returns></returns>
    public Dictionary<Function, object> Invoke()
    {
        cancel = false;

        cancelAll = false;

        invokeIndex = index;

        isInvoking = true;

        Dictionary<Function, object> returns = new Dictionary<Function, object>(functions.Count);

        for (int i = 0; i < functions.Count; i++)
        {
            returns[functions[i]] = functions[i].DynamicInvoke();

            if (cancel || cancelAll)
            {
                break;
            }
        }

        isInvoking = false;

        return returns;
    }

    /// <summary>
    /// Invokes every delegate
    /// </summary>
    /// <returns></returns>
    public static Dictionary<DynamicEvent, Dictionary<Function, object>> InvokeAll()
    {
        Dictionary<DynamicEvent, Dictionary<Function, object>> returns = new Dictionary<DynamicEvent, Dictionary<Function, object>>(allDelegates.Count);

        for (int i = 0; i < allDelegates.Count; i++)
        {
            returns[allDelegates[i]] = allDelegates[i].Invoke();

            if (allDelegates[i].cancel || cancelAll)
            {
                break;
            }
        }

        return returns;
    }

    /// <summary>
    /// Reinvokes the current delegate
    /// </summary>
    /// <returns></returns>
    public static Dictionary<Function, object> InvokeCurrent()
    {
        return allDelegates[invokeIndex].Invoke();
    }

    /// <summary>
    /// Cancel an invoke
    /// </summary>
    public void Cancel()
    {
        cancel = true;
    }

    /// <summary>
    /// Cancel all invokes
    /// </summary>
    public static void CancelAll()
    {
        cancelAll = true;
    }

    /// <summary>
    /// Cancel the current invoke
    /// </summary>
    public static void CancelCurrent()
    {
        allDelegates[invokeIndex].cancel = true;
    }

    /// <summary>
    /// Returns whether the delegate is currently being invoked
    /// </summary>
    /// <returns></returns>
    public bool IsInvoking()
    {
        return isInvoking;
    }


    // COLLECTION FUNCTIONS

    /// <summary>
    /// Gets a function in the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public Function Get(int index)
    {
        return functions[index];
    }

    /// <summary>
    /// Sets a function in the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public DynamicEvent Set(int index, Function function)
    {
        if (function.Method.GetParameters().Length == 0)
        {
            functions[index] = function;
        }

        return this;
    }

    /// <summary>
    /// Add a new function to the delegate
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public DynamicEvent Add(Function function)
    {
        if (function.Method.GetParameters().Length == 0)
        {
            functions.Add(function);
        }

        return this;
    }

    /// <summary>
    /// Adds new functions to the delegate
    /// </summary>
    /// <param name="functions"></param>
    /// <returns></returns>
    public DynamicEvent Add(params Function[] functions)
    {
        for (int i = 0; i < functions.Length; i++)
        {
            if (functions[i].Method.GetParameters().Length == 0)
            {
                this.functions.Add(functions[i]);
            }
        }

        return this;
    }

    /// <summary>
    /// Adds new functions to the delegate
    /// </summary>
    /// <param name="functions"></param>
    /// <returns></returns>
    public DynamicEvent Add(List<Function> functions)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            if (functions[i].Method.GetParameters().Length == 0)
            {
                this.functions.Add(functions[i]);
            }
        }

        return this;
    }

    /// <summary>
    /// Adds another delegate to the delegate
    /// </summary>
    /// <param name="newDelegate"></param>
    /// <returns></returns>
    public DynamicEvent Add(DynamicEvent newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            if (newDelegate.functions[i].Method.GetParameters().Length == 0)
            {
                functions.Add(newDelegate.functions[i]);
            }
        }

        return this;
    }

    /// <summary>
    /// Remove a function from the delegate
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public DynamicEvent Remove(Function function)
    {
        functions.Remove(function);

        return this;
    }

    /// <summary>
    /// Removes a delegate's functions from the delegate
    /// </summary>
    /// <param name="removedDelegate"></param>
    /// <returns></returns>
    public DynamicEvent Remove(DynamicEvent removedDelegate)
    {
        for (int i = 0; i < removedDelegate.functions.Count; i++)
        {
            functions.Remove(removedDelegate.functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Remove a function from the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DynamicEvent RemoveAt(int index)
    {
        functions.RemoveAt(index);

        return this;
    }

    /// <summary>
    /// Clear all functions from the delegate
    /// </summary>
    /// <returns></returns>
    public DynamicEvent Clear()
    {
        functions.Clear();

        return this;
    }

    /// <summary>
    /// Return the number of functions in the delegate
    /// </summary>
    /// <returns></returns>
    public int Count()
    {
        return functions.Count;
    }

    /// <summary>
    /// Returns if the delegate contains a function
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public bool Contains(Function function)
    {
        return functions.Contains(function);
    }

    /// <summary>
    /// Returns the index of the function in the delegate, or -1 if it was not found
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public int Find(Function function)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            if (functions[i].Equals(function))
            {
                return i;
            }
        }

        return -1;
    }

    /// <summary>
    /// Returns an array of the functions
    /// </summary>
    /// <returns></returns>
    public Function[] ToArray()
    {
        return functions.ToArray();
    }

    /// <summary>
    /// Returns a list of the functions
    /// </summary>
    /// <returns></returns>
    public List<Function> ToList()
    {
        return functions;
    }


    // PARAMETER FUNCTIONS

    /// <summary>
    /// Returns whether the given types match with the given parameters
    /// </summary>
    /// <param name="objects"></param>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public static bool CompareObjectParameters(object[] objects, ParameterInfo[] parameters)
    {
        if (objects.Length != parameters.Length)
        {
            return false;
        }

        for (int i = 0; i < parameters.Length; i++)
        {
            if (objects[i].GetType() != parameters[i].ParameterType)
            {
                return false;
            }
        }

        return true;
    }


    // COLLECTION OPERATORS

    /// <summary>
    /// Adding a function
    /// </summary>
    /// <param name="Delegate"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public static DynamicEvent operator +(DynamicEvent Delegate, Function function)
    {
        return Delegate.Add(function);
    }

    /// <summary>
    /// Removing a function
    /// </summary>
    /// <param name="Delegate"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public static DynamicEvent operator -(DynamicEvent Delegate, Function function)
    {
        return Delegate.Remove(function);
    }


    // ENUMERATOR FUNCTION

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return functions.GetEnumerator();
    }
}

/// <summary>
/// Wrapper class for a collection of functions.
/// All stored functions must share the same parameters.
/// </summary>
public class Delegate : IEnumerable
{
    // STATIC DELEGATE DATA

    /// <summary>
    /// Global list of all delegates
    /// </summary>
    private static List<Delegate> allDelegates = new List<Delegate>();

    /// <summary>
    /// Global delegate cancellation token
    /// </summary>
    private static bool cancelAll = false;

    /// <summary>
    /// Index of current invoked delegate
    /// </summary>
    private static int invokeIndex = 0;


    // DELEGATE DATA

    /// <summary>
    /// List of functions included in the delegate
    /// </summary>
    private List<Function> functions = new List<Function>();

    /// <summary>
    /// Whether the delegate is currently invoking functions
    /// </summary>
    private bool isInvoking = false;

    /// <summary>
    /// Delegate cancellation token
    /// </summary>
    private bool cancel = false;

    /// <summary>
    /// Index of current delegate
    /// </summary>
    private int index = 0;

    /// <summary>
    /// Delegate parameters
    /// </summary>
    private Type[] parameterTypes = null;


    // DELEGATE CONSTRUCTORS AND DECONSTRUCTOR

    /// <summary>
    /// Default constructor
    /// </summary>
    public Delegate()
    {
        functions = new List<Function>();

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="functions"></param>
    public Delegate(params Function[] functions)
    {
        this.functions = new List<Function>(functions.Length);

        for (int i = 0; i < functions.Length; i++)
        {
            if (parameterTypes != null && !CompareParameters(parameterTypes, functions[i].Method.GetParameters()))
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
            }
            else if (parameterTypes == null)
            {
                parameterTypes = GetParameterTypes(functions[i].Method.GetParameters());
            }

            this.functions.Add(functions[i]);
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// List constructor
    /// </summary>
    /// <param name="functions"></param>
    public Delegate(List<Function> functions)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            if (parameterTypes != null && !CompareParameters(parameterTypes, functions[i].Method.GetParameters()))
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
            }
            else if (parameterTypes == null)
            {
                parameterTypes = GetParameterTypes(functions[i].Method.GetParameters());
            }
        }

        this.functions = functions;

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Delegate constructor
    /// </summary>
    /// <param name="newDelegate"></param>
    public Delegate(Delegate newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            if (parameterTypes != null && !CompareParameters(parameterTypes, functions[i].Method.GetParameters()))
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
            }
            else if (parameterTypes == null)
            {
                parameterTypes = GetParameterTypes(functions[i].Method.GetParameters());
            }

            functions.Add(newDelegate.functions[i]);
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Deconstructor
    /// </summary>
    ~Delegate()
    {
        for (int i = index + 1; i < allDelegates.Count; i++)
        {
            allDelegates[i].index--;
        }

        allDelegates.Remove(this);
    }


    // DELEGATE FUNCTIONS

    /// <summary>
    /// Call each function in the delegate and return if the invoke was successful
    /// </summary>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public bool Invoke(params object[] parameters)
    {
        cancel = false;

        cancelAll = false;

        invokeIndex = index;

        isInvoking = true;

        for (int i = 0; i < functions.Count; i++)
        {
            try
            {
                functions[i].DynamicInvoke(parameters);
            }
            catch
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not invoke the given delegate! Invoked parameters did not match the delegate type!");
            }

            if (cancel || cancelAll)
            {
                isInvoking = false;

                return false;
            }
        }

        isInvoking = false;

        return true;
    }

    /// <summary>
    /// Invokes every delegate
    /// </summary>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public static bool InvokeAll(params object[] parameters)
    {
        for (int i = 0; i < allDelegates.Count; i++)
        {
            if (!allDelegates[i].Invoke(parameters))
            {
                return false;
            }
        }

        return true;
    }

    /// <summary>
    /// Reinvokes the current delegate
    /// </summary>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public static bool InvokeCurrent(params object[] parameters)
    {
        return allDelegates[invokeIndex].Invoke(parameters);
    }

    /// <summary>
    /// Cancel an invoke
    /// </summary>
    public void Cancel()
    {
        cancel = true;
    }

    /// <summary>
    /// Cancel all invokes
    /// </summary>
    public static void CancelAll()
    {
        cancelAll = true;
    }

    /// <summary>
    /// Cancel the current invoke
    /// </summary>
    public static void CancelCurrent()
    {
        allDelegates[invokeIndex].cancel = true;
    }

    /// <summary>
    /// Returns whether the delegate is currently being invoked
    /// </summary>
    /// <returns></returns>
    public bool IsInvoking()
    {
        return isInvoking;
    }


    // COLLECTION FUNCTIONS

    /// <summary>
    /// Gets a function in the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public Function Get(int index)
    {
        return functions[index];
    }

    /// <summary>
    /// Sets a function in the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public Delegate Set(int index, Function function)
    {
        if (parameterTypes != null && !CompareParameters(parameterTypes, function.Method.GetParameters()))
        {
            Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
        }
        else if (parameterTypes == null)
        {
            parameterTypes = GetParameterTypes(function.Method.GetParameters());
        }

        functions[index] = function;

        return this;
    }

    /// <summary>
    /// Add a new function to the delegate
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public Delegate Add(Function function)
    {
        if (parameterTypes != null && !CompareParameters(parameterTypes, function.Method.GetParameters()))
        {
            Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
        }
        else if (parameterTypes == null)
        {
            parameterTypes = GetParameterTypes(function.Method.GetParameters());
        }

        functions.Add(function);

        return this;
    }

    /// <summary>
    /// Adds new functions to the delegate
    /// </summary>
    /// <param name="functions"></param>
    /// <returns></returns>
    public Delegate Add(params Function[] functions)
    {
        for (int i = 0; i < functions.Length; i++)
        {
            if (parameterTypes != null && !CompareParameters(parameterTypes, functions[i].Method.GetParameters()))
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
            }
            else if (parameterTypes == null)
            {
                parameterTypes = GetParameterTypes(functions[i].Method.GetParameters());
            }

            this.functions.Add(functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Adds new functions to the delegate
    /// </summary>
    /// <param name="functions"></param>
    /// <returns></returns>
    public Delegate Add(List<Function> functions)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            if (parameterTypes != null && !CompareParameters(parameterTypes, functions[i].Method.GetParameters()))
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
            }
            else if (parameterTypes == null)
            {
                parameterTypes = GetParameterTypes(functions[i].Method.GetParameters());
            }

            this.functions.Add(functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Adds another delegate to the delegate
    /// </summary>
    /// <param name="newDelegate"></param>
    /// <returns></returns>
    public Delegate Add(Delegate newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            if (parameterTypes != null && !CompareParameters(parameterTypes, functions[i].Method.GetParameters()))
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
            }
            else if (parameterTypes == null)
            {
                parameterTypes = GetParameterTypes(functions[i].Method.GetParameters());
            }

            functions.Add(newDelegate.functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Remove a function from the delegate
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public Delegate Remove(Function function)
    {
        functions.Remove(function);

        return this;
    }

    /// <summary>
    /// Removes a delegate's functions from the delegate
    /// </summary>
    /// <param name="removedDelegate"></param>
    /// <returns></returns>
    public Delegate Remove(Delegate removedDelegate)
    {
        for (int i = 0; i < removedDelegate.functions.Count; i++)
        {
            functions.Remove(removedDelegate.functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Remove a function from the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public Delegate RemoveAt(int index)
    {
        functions.RemoveAt(index);

        return this;
    }

    /// <summary>
    /// Clear all functions from the delegate
    /// </summary>
    /// <returns></returns>
    public Delegate Clear()
    {
        functions.Clear();

        parameterTypes = null;

        return this;
    }

    /// <summary>
    /// Return the number of functions in the delegate
    /// </summary>
    /// <returns></returns>
    public int Count()
    {
        return functions.Count;
    }

    /// <summary>
    /// Returns if the delegate contains a function
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public bool Contains(Function function)
    {
        return functions.Contains(function);
    }

    /// <summary>
    /// Returns the index of the function in the delegate, or -1 if it was not found
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public int Find(Function function)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            if (functions[i].Equals(function))
            {
                return i;
            }
        }

        return -1;
    }

    /// <summary>
    /// Returns an array of the functions
    /// </summary>
    /// <returns></returns>
    public Function[] ToArray()
    {
        return functions.ToArray();
    }

    /// <summary>
    /// Returns a list of the functions
    /// </summary>
    /// <returns></returns>
    public List<Function> ToList()
    {
        return functions;
    }


    // PARAMETER FUNCTIONS

    /// <summary>
    /// Get the assigned parameters of this delegate
    /// </summary>
    /// <returns></returns>
    public Type[] GetParameters()
    {
        return parameterTypes;
    }

    /// <summary>
    /// Set the parameters of this delegate if they have not been assigned yet
    /// </summary>
    /// <param name="newParameters"></param>
    /// <returns></returns>
    public bool SetParameters(Type[] newParameters)
    {
        if (parameterTypes == null || functions.Count == 0)
        {
            parameterTypes = newParameters;

            return true;
        }

        return false;
    }

    /// <summary>
    /// Set the parameters of this delegate if they have not been assigned yet
    /// </summary>
    /// <param name="newParameters"></param>
    /// <returns></returns>
    public bool SetParameters(ParameterInfo[] newParameters)
    {
        if (parameterTypes == null || functions.Count == 0)
        {
            parameterTypes = new Type[newParameters.Length];

            for (int i = 0; i < newParameters.Length; i++)
            {
                parameterTypes[i] = newParameters[i].ParameterType;
            }

            return true;
        }

        return false;
    }

    /// <summary>
    /// Reset the parameters of this delegate and clear all functions
    /// </summary>
    /// <param name="newParameters"></param>
    /// <returns></returns>
    public Delegate Reset(Type[] newParameters = null)
    {
        functions.Clear();

        parameterTypes = newParameters;

        return this;
    }

    /// <summary>
    /// Reset the parameters of this delegate and clear all functions
    /// </summary>
    /// <param name="newParameters"></param>
    /// <returns></returns>
    public Delegate Reset(ParameterInfo[] newParameters)
    {
        functions.Clear();

        parameterTypes = new Type[newParameters.Length];

        for (int i = 0; i < newParameters.Length; i++)
        {
            parameterTypes[i] = newParameters[i].ParameterType;
        }

        return this;
    }

    /// <summary>
    /// Returns whether the given types match with the given parameters
    /// </summary>
    /// <param name="types"></param>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public static bool CompareParameters(Type[] types, ParameterInfo[] parameters)
    {
        if (types.Length != parameters.Length)
        {
            return false;
        }

        for (int i = 0; i < parameters.Length; i++)
        {
            if (types[i] != parameters[i].ParameterType)
            {
                return false;
            }
        }

        return true;
    }

    /// <summary>
    /// Returns an array of parameter types from the given parameter info
    /// </summary>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public static Type[] GetParameterTypes(ParameterInfo[] parameters)
    {
        Type[] types = new Type[parameters.Length];

        for (int i = 0; i < parameters.Length; i++)
        {
            types[i] = parameters[i].ParameterType;
        }

        return types;
    }


    // COLLECTION OPERATORS

    /// <summary>
    /// Adding a function
    /// </summary>
    /// <param name="Delegate"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public static Delegate operator +(Delegate Delegate, Function function)
    {
        return Delegate.Add(function);
    }

    /// <summary>
    /// Removing a function
    /// </summary>
    /// <param name="Delegate"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public static Delegate operator -(Delegate Delegate, Function function)
    {
        return Delegate.Remove(function);
    }


    // ENUMERATOR FUNCTION

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return functions.GetEnumerator();
    }
}

/// <summary>
/// Wrapper class for a collection of functions.
/// All stored functions must share the same return type.
/// All stored functions must share the same parameters.
/// </summary>
public class Delegate<ReturnType> : IEnumerable
{
    // STATIC DELEGATE DATA

    /// <summary>
    /// Global list of all delegates
    /// </summary>
    private static List<Delegate<ReturnType>> allDelegates = new List<Delegate<ReturnType>>();

    /// <summary>
    /// Global delegate cancellation token
    /// </summary>
    private static bool cancelAll = false;

    /// <summary>
    /// Index of current invoked delegate
    /// </summary>
    private static int invokeIndex = 0;


    // DELEGATE DATA

    /// <summary>
    /// List of functions included in the delegate
    /// </summary>
    private List<Function> functions = new List<Function>();

    /// <summary>
    /// Whether the delegate is currently invoking functions
    /// </summary>
    private bool isInvoking = false;

    /// <summary>
    /// Delegate cancellation token
    /// </summary>
    private bool cancel = false;

    /// <summary>
    /// Index of current delegate
    /// </summary>
    private int index = 0;

    /// <summary>
    /// Delegate parameters
    /// </summary>
    private Type[] parameterTypes = null;


    // DELEGATE CONSTRUCTORS AND DECONSTRUCTOR

    /// <summary>
    /// Default constructor
    /// </summary>
    public Delegate()
    {
        functions = new List<Function>();

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="functions"></param>
    public Delegate(params Function[] functions)
    {
        this.functions = new List<Function>(functions.Length);

        for (int i = 0; i < functions.Length; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }
            else if (parameterTypes != null && !CompareParameters(parameterTypes, functions[i].Method.GetParameters()))
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
            }
            else if (parameterTypes == null)
            {
                parameterTypes = GetParameterTypes(functions[i].Method.GetParameters());
            }

            this.functions.Add(functions[i]);
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// List constructor
    /// </summary>
    /// <param name="functions"></param>
    public Delegate(List<Function> functions)
    {
        this.functions = functions;

        for (int i = 0; i < functions.Count; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }
            else if (parameterTypes != null && !CompareParameters(parameterTypes, functions[i].Method.GetParameters()))
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
            }
            else if (parameterTypes == null)
            {
                parameterTypes = GetParameterTypes(functions[i].Method.GetParameters());
            }
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Delegate constructor
    /// </summary>
    /// <param name="newDelegate"></param>
    public Delegate(Delegate<ReturnType> newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }
            else if (parameterTypes != null && !CompareParameters(parameterTypes, functions[i].Method.GetParameters()))
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
            }
            else if (parameterTypes == null)
            {
                parameterTypes = GetParameterTypes(functions[i].Method.GetParameters());
            }

            functions.Add(newDelegate.functions[i]);
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Deconstructor
    /// </summary>
    ~Delegate()
    {
        for (int i = index + 1; i < allDelegates.Count; i++)
        {
            allDelegates[i].index--;
        }

        allDelegates.Remove(this);
    }


    // DELEGATE FUNCTIONS

    /// <summary>
    /// Returns a dictionary with each key representing the function and the value being the returned data
    /// </summary>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public Dictionary<Function, ReturnType> Invoke(params object[] parameters)
    {
        cancel = false;

        cancelAll = false;

        invokeIndex = index;

        isInvoking = true;

        Dictionary<Function, ReturnType> returns = new Dictionary<Function, ReturnType>(functions.Count);

        for (int i = 0; i < functions.Count; i++)
        {
            try
            {
                returns[functions[i]] = (ReturnType)functions[i].DynamicInvoke(parameters);
            }
            catch
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not invoke the given delegate! Invoked parameters did not match the delegate type!");
            }

            if (cancel || cancelAll)
            {
                for (int j = i + 1; j < functions.Count; j++)
                {
                    returns[functions[i]] = default(ReturnType);
                }

                break;
            }
        }

        isInvoking = false;

        return returns;
    }

    /// <summary>
    /// Invokes every delegate
    /// </summary>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public static Dictionary<Delegate<ReturnType>, Dictionary<Function, ReturnType>> InvokeAll(params object[] parameters)
    {
        Dictionary<Delegate<ReturnType>, Dictionary<Function, ReturnType>> returns = new Dictionary<Delegate<ReturnType>, Dictionary<Function, ReturnType>>(allDelegates.Count);

        for (int i = 0; i < allDelegates.Count; i++)
        {
            returns[allDelegates[i]] = allDelegates[i].Invoke(parameters);

            if (allDelegates[i].cancel || cancelAll)
            {
                break;
            }
        }

        return returns;
    }

    /// <summary>
    /// Reinvokes the current delegate
    /// </summary>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public static Dictionary<Function, ReturnType> InvokeCurrent(params object[] parameters)
    {
        return allDelegates[invokeIndex].Invoke(parameters);
    }

    /// <summary>
    /// Cancel an invoke
    /// </summary>
    public void Cancel()
    {
        cancel = true;
    }

    /// <summary>
    /// Cancel all invokes
    /// </summary>
    public static void CancelAll()
    {
        cancelAll = true;
    }

    /// <summary>
    /// Cancel the current invoke
    /// </summary>
    public static void CancelCurrent()
    {
        allDelegates[invokeIndex].cancel = true;
    }

    /// <summary>
    /// Returns whether the delegate is currently being invoked
    /// </summary>
    /// <returns></returns>
    public bool IsInvoking()
    {
        return isInvoking;
    }


    // COLLECTION FUNCTIONS

    /// <summary>
    /// Gets a function in the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public Function Get(int index)
    {
        return functions[index];
    }

    /// <summary>
    /// Sets a function in the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public Delegate<ReturnType> Set(int index, Function function)
    {
        if (typeof(ReturnType) != function.Method.ReturnType)
        {
            Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
        }
        else if (parameterTypes != null && !CompareParameters(parameterTypes, function.Method.GetParameters()))
        {
            Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
        }
        else if (parameterTypes == null)
        {
            parameterTypes = GetParameterTypes(function.Method.GetParameters());
        }

        functions[index] = function;

        return this;
    }

    /// <summary>
    /// Add a new function to the delegate
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public Delegate<ReturnType> Add(Function function)
    {
        if (typeof(ReturnType) != function.Method.ReturnType)
        {
            Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
        }
        else if (parameterTypes != null && !CompareParameters(parameterTypes, function.Method.GetParameters()))
        {
            Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
        }
        else if (parameterTypes == null)
        {
            parameterTypes = GetParameterTypes(function.Method.GetParameters());
        }

        functions.Add(function);

        return this;
    }

    /// <summary>
    /// Adds new functions to the delegate
    /// </summary>
    /// <param name="functions"></param>
    /// <returns></returns>
    public Delegate<ReturnType> Add(params Function[] functions)
    {
        for (int i = 0; i < functions.Length; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }
            else if (parameterTypes != null && !CompareParameters(parameterTypes, functions[i].Method.GetParameters()))
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
            }
            else if (parameterTypes == null)
            {
                parameterTypes = GetParameterTypes(functions[i].Method.GetParameters());
            }

            this.functions.Add(functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Adds new functions to the delegate
    /// </summary>
    /// <param name="functions"></param>
    /// <returns></returns>
    public Delegate<ReturnType> Add(List<Function> functions)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }
            else if (parameterTypes != null && !CompareParameters(parameterTypes, functions[i].Method.GetParameters()))
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
            }
            else if (parameterTypes == null)
            {
                parameterTypes = GetParameterTypes(functions[i].Method.GetParameters());
            }

            this.functions.Add(functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Adds another delegate to the delegate
    /// </summary>
    /// <param name="newDelegate"></param>
    /// <returns></returns>
    public Delegate<ReturnType> Add(Delegate<ReturnType> newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }
            else if (parameterTypes != null && !CompareParameters(parameterTypes, functions[i].Method.GetParameters()))
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's parameters do not match the delegate's parameters!");
            }
            else if (parameterTypes == null)
            {
                parameterTypes = GetParameterTypes(functions[i].Method.GetParameters());
            }

            functions.Add(newDelegate.functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Remove a function from the delegate
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public Delegate<ReturnType> Remove(Function function)
    {
        functions.Remove(function);

        return this;
    }

    /// <summary>
    /// Removes a delegate's functions from the delegate
    /// </summary>
    /// <param name="removedDelegate"></param>
    /// <returns></returns>
    public Delegate<ReturnType> Remove(Delegate<ReturnType> removedDelegate)
    {
        for (int i = 0; i < removedDelegate.functions.Count; i++)
        {
            functions.Remove(removedDelegate.functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Remove a function from the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public Delegate<ReturnType> RemoveAt(int index)
    {
        functions.RemoveAt(index);

        return this;
    }

    /// <summary>
    /// Clear all functions from the delegate
    /// </summary>
    /// <returns></returns>
    public Delegate<ReturnType> Clear()
    {
        functions.Clear();

        parameterTypes = null;

        return this;
    }

    /// <summary>
    /// Return the number of functions in the delegate
    /// </summary>
    /// <returns></returns>
    public int Count()
    {
        return functions.Count;
    }

    /// <summary>
    /// Returns if the delegate contains a function
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public bool Contains(Function function)
    {
        return functions.Contains(function);
    }

    /// <summary>
    /// Returns the index of the function in the delegate, or -1 if it was not found
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public int Find(Function function)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            if (functions[i].Equals(function))
            {
                return i;
            }
        }

        return -1;
    }

    /// <summary>
    /// Returns an array of the functions
    /// </summary>
    /// <returns></returns>
    public Function[] ToArray()
    {
        return functions.ToArray();
    }

    /// <summary>
    /// Returns a list of the functions
    /// </summary>
    /// <returns></returns>
    public List<Function> ToList()
    {
        return functions;
    }


    // PARAMETER FUNCTIONS

    /// <summary>
    /// Get the assigned parameters of this delegate
    /// </summary>
    /// <returns></returns>
    public Type[] GetParameters()
    {
        return parameterTypes;
    }

    /// <summary>
    /// Set the parameters of this delegate if they have not been assigned yet
    /// </summary>
    /// <param name="newParameters"></param>
    /// <returns></returns>
    public bool SetParameters(Type[] newParameters)
    {
        if (parameterTypes == null || functions.Count == 0)
        {
            parameterTypes = newParameters;

            return true;
        }

        return false;
    }

    /// <summary>
    /// Set the parameters of this delegate if they have not been assigned yet
    /// </summary>
    /// <param name="newParameters"></param>
    /// <returns></returns>
    public bool SetParameters(ParameterInfo[] newParameters)
    {
        if (parameterTypes == null || functions.Count == 0)
        {
            parameterTypes = new Type[newParameters.Length];

            for (int i = 0; i < newParameters.Length; i++)
            {
                parameterTypes[i] = newParameters[i].ParameterType;
            }

            return true;
        }

        return false;
    }

    /// <summary>
    /// Reset the parameters of this delegate and clear all functions
    /// </summary>
    /// <param name="newParameters"></param>
    /// <returns></returns>
    public Delegate<ReturnType> Reset(Type[] newParameters = null)
    {
        functions.Clear();

        parameterTypes = newParameters;

        return this;
    }

    /// <summary>
    /// Reset the parameters of this delegate and clear all functions
    /// </summary>
    /// <param name="newParameters"></param>
    /// <returns></returns>
    public Delegate<ReturnType> Reset(ParameterInfo[] newParameters)
    {
        functions.Clear();

        parameterTypes = new Type[newParameters.Length];

        for (int i = 0; i < newParameters.Length; i++)
        {
            parameterTypes[i] = newParameters[i].ParameterType;
        }

        return this;
    }

    /// <summary>
    /// Returns whether the given types match with the given parameters
    /// </summary>
    /// <param name="types"></param>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public static bool CompareParameters(Type[] types, ParameterInfo[] parameters)
    {
        if (types.Length != parameters.Length)
        {
            return false;
        }

        for (int i = 0; i < parameters.Length; i++)
        {
            if (types[i] != parameters[i].ParameterType)
            {
                return false;
            }
        }

        return true;
    }

    /// <summary>
    /// Returns an array of parameter types from the given parameter info
    /// </summary>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public static Type[] GetParameterTypes(ParameterInfo[] parameters)
    {
        Type[] types = new Type[parameters.Length];

        for (int i = 0; i < parameters.Length; i++)
        {
            types[i] = parameters[i].ParameterType;
        }

        return types;
    }


    // COLLECTION OPERATORS

    /// <summary>
    /// Adding a function
    /// </summary>
    /// <param name="Delegate"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public static Delegate<ReturnType> operator +(Delegate<ReturnType> Delegate, Function function)
    {
        return Delegate.Add(function);
    }

    /// <summary>
    /// Removing a function
    /// </summary>
    /// <param name="Delegate"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public static Delegate<ReturnType> operator -(Delegate<ReturnType> Delegate, Function function)
    {
        return Delegate.Remove(function);
    }


    // ENUMERATOR FUNCTION

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return functions.GetEnumerator();
    }
}

/// <summary>
/// Wrapper class for a collection of functions.
/// Any function can be stored in this delegate.
/// Invoke will only call delegates with matching parameters.
/// </summary>
public class DynamicDelegate : IEnumerable
{
    // STATIC DELEGATE DATA

    /// <summary>
    /// Global list of all delegates
    /// </summary>
    private static List<DynamicDelegate> allDelegates = new List<DynamicDelegate>();

    /// <summary>
    /// Global delegate cancellation token
    /// </summary>
    private static bool cancelAll = false;

    /// <summary>
    /// Index of current invoked delegate
    /// </summary>
    private static int invokeIndex = 0;


    // DELEGATE DATA

    /// <summary>
    /// List of functions included in the delegate
    /// </summary>
    private List<Function> functions = new List<Function>();

    /// <summary>
    /// Whether the delegate is currently invoking functions
    /// </summary>
    private bool isInvoking = false;

    /// <summary>
    /// Delegate cancellation token
    /// </summary>
    private bool cancel = false;

    /// <summary>
    /// Index of current delegate
    /// </summary>
    private int index = 0;


    // DELEGATE CONSTRUCTORS AND DECONSTRUCTOR

    /// <summary>
    /// Default constructor
    /// </summary>
    public DynamicDelegate()
    {
        functions = new List<Function>();

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Array constructor
    /// </summary>
    /// <param name="functions"></param>
    public DynamicDelegate(params Function[] functions)
    {
        this.functions = new List<Function>(functions.Length);

        for (int i = 0; i < functions.Length; i++)
        {
            this.functions.Add(functions[i]);
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// List constructor
    /// </summary>
    /// <param name="functions"></param>
    public DynamicDelegate(List<Function> functions)
    {
        this.functions = functions;

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Delegate constructor
    /// </summary>
    /// <param name="newDelegate"></param>
    public DynamicDelegate(DynamicDelegate newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            functions.Add(newDelegate.functions[i]);
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    /// <summary>
    /// Deconstructor
    /// </summary>
    ~DynamicDelegate()
    {
        for (int i = index + 1; i < allDelegates.Count; i++)
        {
            allDelegates[i].index--;
        }

        allDelegates.Remove(this);
    }


    // DELEGATE FUNCTIONS

    /// <summary>
    /// Returns a dictionary with each key representing the function and the value being the returned data
    /// </summary>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public Dictionary<Function, object> Invoke(params object[] parameters)
    {
        cancel = false;

        cancelAll = false;

        invokeIndex = index;

        isInvoking = true;

        Dictionary<Function, object> returns = new Dictionary<Function, object>(functions.Count);

        for (int i = 0; i < functions.Count; i++)
        {
            if (CompareObjectParameters(parameters, functions[i].Method.GetParameters()))
            {
                returns[functions[i]] = functions[i].DynamicInvoke(parameters);
            }
            else
            {
                returns[functions[i]] = functions[i].Method.ReturnType.IsValueType ? Activator.CreateInstance(functions[i].Method.ReturnType) : null;
            }

            if (cancel || cancelAll)
            {
                break;
            }
        }

        isInvoking = false;

        return returns;
    }

    /// <summary>
    /// Invokes every delegate
    /// </summary>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public static Dictionary<DynamicDelegate, Dictionary<Function, object>> InvokeAll(params object[] parameters)
    {
        Dictionary<DynamicDelegate, Dictionary<Function, object>> returns = new Dictionary<DynamicDelegate, Dictionary<Function, object>>(allDelegates.Count);

        for (int i = 0; i < allDelegates.Count; i++)
        {
            returns[allDelegates[i]] = allDelegates[i].Invoke(parameters);

            if (allDelegates[i].cancel || cancelAll)
            {
                break;
            }
        }

        return returns;
    }

    /// <summary>
    /// Reinvokes the current delegate
    /// </summary>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public static Dictionary<Function, object> InvokeCurrent(params object[] parameters)
    {
        return allDelegates[invokeIndex].Invoke(parameters);
    }

    /// <summary>
    /// Cancel an invoke
    /// </summary>
    public void Cancel()
    {
        cancel = true;
    }

    /// <summary>
    /// Cancel all invokes
    /// </summary>
    public static void CancelAll()
    {
        cancelAll = true;
    }

    /// <summary>
    /// Cancel the current invoke
    /// </summary>
    public static void CancelCurrent()
    {
        allDelegates[invokeIndex].cancel = true;
    }

    /// <summary>
    /// Returns whether the delegate is currently being invoked
    /// </summary>
    /// <returns></returns>
    public bool IsInvoking()
    {
        return isInvoking;
    }


    // COLLECTION FUNCTIONS

    /// <summary>
    /// Gets a function in the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public Function Get(int index)
    {
        return functions[index];
    }

    /// <summary>
    /// Sets a function in the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public DynamicDelegate Set(int index, Function function)
    {
        functions[index] = function;

        return this;
    }

    /// <summary>
    /// Add a new function to the delegate
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public DynamicDelegate Add(Function function)
    {
        functions.Add(function);

        return this;
    }

    /// <summary>
    /// Adds new functions to the delegate
    /// </summary>
    /// <param name="functions"></param>
    /// <returns></returns>
    public DynamicDelegate Add(params Function[] functions)
    {
        for (int i = 0; i < functions.Length; i++)
        {
            this.functions.Add(functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Adds new functions to the delegate
    /// </summary>
    /// <param name="functions"></param>
    /// <returns></returns>
    public DynamicDelegate Add(List<Function> functions)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            this.functions.Add(functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Adds another delegate to the delegate
    /// </summary>
    /// <param name="newDelegate"></param>
    /// <returns></returns>
    public DynamicDelegate Add(DynamicDelegate newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            functions.Add(newDelegate.functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Remove a function from the delegate
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public DynamicDelegate Remove(Function function)
    {
        functions.Remove(function);

        return this;
    }

    /// <summary>
    /// Removes a delegate's functions from the delegate
    /// </summary>
    /// <param name="removedDelegate"></param>
    /// <returns></returns>
    public DynamicDelegate Remove(DynamicDelegate removedDelegate)
    {
        for (int i = 0; i < removedDelegate.functions.Count; i++)
        {
            functions.Remove(removedDelegate.functions[i]);
        }

        return this;
    }

    /// <summary>
    /// Remove a function from the delegate
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public DynamicDelegate RemoveAt(int index)
    {
        functions.RemoveAt(index);

        return this;
    }

    /// <summary>
    /// Clear all functions from the delegate
    /// </summary>
    /// <returns></returns>
    public DynamicDelegate Clear()
    {
        functions.Clear();

        return this;
    }

    /// <summary>
    /// Return the number of functions in the delegate
    /// </summary>
    /// <returns></returns>
    public int Count()
    {
        return functions.Count;
    }

    /// <summary>
    /// Returns if the delegate contains a function
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public bool Contains(Function function)
    {
        return functions.Contains(function);
    }

    /// <summary>
    /// Returns the index of the function in the delegate, or -1 if it was not found
    /// </summary>
    /// <param name="function"></param>
    /// <returns></returns>
    public int Find(Function function)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            if (functions[i].Equals(function))
            {
                return i;
            }
        }

        return -1;
    }

    /// <summary>
    /// Returns an array of the functions
    /// </summary>
    /// <returns></returns>
    public Function[] ToArray()
    {
        return functions.ToArray();
    }

    /// <summary>
    /// Returns a list of the functions
    /// </summary>
    /// <returns></returns>
    public List<Function> ToList()
    {
        return functions;
    }


    // PARAMETER FUNCTIONS

    /// <summary>
    /// Returns whether the given types match with the given parameters
    /// </summary>
    /// <param name="objects"></param>
    /// <param name="parameters"></param>
    /// <returns></returns>
    public static bool CompareObjectParameters(object[] objects, ParameterInfo[] parameters)
    {
        if (objects.Length != parameters.Length)
        {
            return false;
        }

        for (int i = 0; i < parameters.Length; i++)
        {
            if (objects[i].GetType() != parameters[i].ParameterType)
            {
                return false;
            }
        }

        return true;
    }


    // COLLECTION OPERATORS

    /// <summary>
    /// Adding a function
    /// </summary>
    /// <param name="Delegate"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public static DynamicDelegate operator +(DynamicDelegate Delegate, Function function)
    {
        return Delegate.Add(function);
    }

    /// <summary>
    /// Removing a function
    /// </summary>
    /// <param name="Delegate"></param>
    /// <param name="function"></param>
    /// <returns></returns>
    public static DynamicDelegate operator -(DynamicDelegate Delegate, Function function)
    {
        return Delegate.Remove(function);
    }


    // ENUMERATOR FUNCTION

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return functions.GetEnumerator();
    }
}
