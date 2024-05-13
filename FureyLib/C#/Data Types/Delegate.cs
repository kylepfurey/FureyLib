
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

    // Global list of all delegates
    private static List<Event> allDelegates = new List<Event>();

    // Global delegate cancellation token
    private static bool cancelAll = false;

    // Index of current invoked delegate
    private static int invokeIndex = 0;


    // DELEGATE DATA

    // List of functions included in the delegate
    private List<Action> functions = new List<Action>();

    // Delegate cancellation token
    private bool cancel = false;

    // Index of current delegate
    private int index = 0;


    // DELEGATE CONSTRUCTOR AND DECONSTRUCTOR

    // Default constructor
    public Event()
    {
        functions = new List<Action>();

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    // Array constructor
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

    // List constructor
    public Event(List<Action> functions)
    {
        this.functions = functions;

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    // Delegate constructor
    public Event(Event newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            functions.Add(newDelegate.functions[i]);
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    // Deconstructor
    ~Event()
    {
        for (int i = index + 1; i < allDelegates.Count; i++)
        {
            allDelegates[i].index--;
        }

        allDelegates.Remove(this);
    }


    // DELEGATE FUNCTIONS

    /// <summary> Call each function in the delegate and return if the invoke was successful. </summary>
    public bool Invoke()
    {
        cancel = false;

        cancelAll = false;

        invokeIndex = index;

        for (int i = 0; i < functions.Count; i++)
        {
            functions[i].Invoke();

            if (cancel || cancelAll)
            {
                return false;
            }
        }

        return true;
    }

    // Invokes every delegate
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

    // Reinvokes the current delegate
    public static bool InvokeCurrent()
    {
        return allDelegates[invokeIndex].Invoke();
    }

    // Cancel an invoke
    public void Cancel()
    {
        cancel = true;
    }

    // Cancel all invokes
    public static void CancelAll()
    {
        cancelAll = true;
    }

    // Cancel the current invoke
    public static void CancelCurrent()
    {
        allDelegates[invokeIndex].cancel = true;
    }


    // COLLECTION FUNCTIONS

    // Gets a function in the delegate
    public Action Get(int index)
    {
        return functions[index];
    }

    // Sets a function in the delegate
    public Event Set(int index, Action function)
    {
        functions[index] = function;

        return this;
    }

    // Add a new function to the delegate
    public Event Add(Action function)
    {
        functions.Add(function);

        return this;
    }

    // Adds new functions to the delegate
    public Event Add(params Action[] functions)
    {
        for (int i = 0; i < functions.Length; i++)
        {
            this.functions.Add(functions[i]);
        }

        return this;
    }

    // Adds new functions to the delegate
    public Event Add(List<Action> functions)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            this.functions.Add(functions[i]);
        }

        return this;
    }

    // Adds another delegate to the delegate
    public Event Add(Event newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            functions.Add(newDelegate.functions[i]);
        }

        return this;
    }

    // Remove a function from the delegate
    public Event Remove(Action function)
    {
        functions.Remove(function);

        return this;
    }

    // Remove a function from the delegate
    public Event RemoveAt(int index)
    {
        functions.RemoveAt(index);

        return this;
    }

    // Removes a delegate's functions from the delegate
    public Event Remove(Event removedDelegate)
    {
        for (int i = 0; i < removedDelegate.functions.Count; i++)
        {
            functions.Remove(removedDelegate.functions[i]);
        }

        return this;
    }

    // Clear all functions from the delegate
    public Event Clear()
    {
        functions.Clear();

        return this;
    }

    // Return the number of functions in the delegate
    public int Count()
    {
        return functions.Count;
    }

    // Returns if the delegate contains a function
    public bool Contains(Action function)
    {
        return functions.Contains(function);
    }

    // Returns the index of the function in the delegate, or -1 if it was not found
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

    // Returns an array of the functions
    public Action[] ToArray()
    {
        return functions.ToArray();
    }

    // Returns a list of the functions
    public List<Action> ToList()
    {
        return functions;
    }


    // COLLECTION OPERATORS

    // Adding a function
    public static Event operator +(Event Delegate, Action function)
    {
        return Delegate.Add(function);
    }

    // Removing a function
    public static Event operator -(Event Delegate, Action function)
    {
        return Delegate.Remove(function);
    }


    // ENUMERATOR FUNCTION

    // Enumerator implementation
    public IEnumerator GetEnumerator()
    {
        return functions.GetEnumerator();
    }
}

/// <summary>
/// Wrapper class for a collection of functions.
/// All stored functions must have no parameters.
/// All stored functions must share the same return type.
/// </summary>
public class Event<ReturnType> : IEnumerable
{
    // STATIC DELEGATE DATA

    // Global list of all delegates
    private static List<Event<ReturnType>> allDelegates = new List<Event<ReturnType>>();

    // Global delegate cancellation token
    private static bool cancelAll = false;

    // Index of current invoked delegate
    private static int invokeIndex = 0;


    // DELEGATE DATA

    // List of functions included in the delegate
    private List<Func<ReturnType>> functions = new List<Func<ReturnType>>();

    // Delegate cancellation token
    private bool cancel = false;

    // Index of current delegate
    private int index = 0;


    // DELEGATE CONSTRUCTOR AND DECONSTRUCTOR

    // Default constructor
    public Event()
    {
        functions = new List<Func<ReturnType>>();

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    // Array constructor
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

    // List constructor
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

    // Delegate constructor
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

    // Deconstructor
    ~Event()
    {
        for (int i = index + 1; i < allDelegates.Count; i++)
        {
            allDelegates[i].index--;
        }

        allDelegates.Remove(this);
    }


    // DELEGATE FUNCTIONS

    /// <summary> Returns a dictionary with each key representing the function and the value being the returned data. </summary>
    public Dictionary<Func<ReturnType>, ReturnType> Invoke()
    {
        cancel = false;

        cancelAll = false;

        invokeIndex = index;

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

        return returns;
    }

    // Invokes every delegate
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

    // Reinvokes the current delegate
    public static Dictionary<Func<ReturnType>, ReturnType> InvokeCurrent()
    {
        return allDelegates[invokeIndex].Invoke();
    }

    // Cancel an invoke
    public void Cancel()
    {
        cancel = true;
    }

    // Cancel all invokes
    public static void CancelAll()
    {
        cancelAll = true;
    }

    // Cancel the current invoke
    public static void CancelCurrent()
    {
        allDelegates[invokeIndex].cancel = true;
    }


    // COLLECTION FUNCTIONS

    // Gets a function in the delegate
    public Func<ReturnType> Get(int index)
    {
        return functions[index];
    }

    // Sets a function in the delegate
    public Event<ReturnType> Set(int index, Func<ReturnType> function)
    {
        if (typeof(ReturnType) != function.Method.ReturnType)
        {
            Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
        }

        functions[index] = function;

        return this;
    }

    // Add a new function to the delegate
    public Event<ReturnType> Add(Func<ReturnType> function)
    {
        if (typeof(ReturnType) != function.Method.ReturnType)
        {
            Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
        }

        functions.Add(function);

        return this;
    }

    // Adds new functions to the delegate
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

    // Adds new functions to the delegate
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

    // Adds another delegate to the delegate
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

    // Remove a function from the delegate
    public Event<ReturnType> Remove(Func<ReturnType> function)
    {
        functions.Remove(function);

        return this;
    }

    // Remove a function from the delegate
    public Event<ReturnType> RemoveAt(int index)
    {
        functions.RemoveAt(index);

        return this;
    }

    // Removes a delegate's functions from the delegate
    public Event<ReturnType> Remove(Event<ReturnType> removedDelegate)
    {
        for (int i = 0; i < removedDelegate.functions.Count; i++)
        {
            functions.Remove(removedDelegate.functions[i]);
        }

        return this;
    }

    // Clear all functions from the delegate
    public Event<ReturnType> Clear()
    {
        functions.Clear();

        return this;
    }

    // Return the number of functions in the delegate
    public int Count()
    {
        return functions.Count;
    }

    // Returns if the delegate contains a function
    public bool Contains(Func<ReturnType> function)
    {
        return functions.Contains(function);
    }

    // Returns the index of the function in the delegate, or -1 if it was not found
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

    // Returns an array of the functions
    public Func<ReturnType>[] ToArray()
    {
        return functions.ToArray();
    }

    // Returns a list of the functions
    public List<Func<ReturnType>> ToList()
    {
        return functions;
    }


    // COLLECTION OPERATORS

    // Adding a function
    public static Event<ReturnType> operator +(Event<ReturnType> Delegate, Func<ReturnType> function)
    {
        return Delegate.Add(function);
    }

    // Removing a function
    public static Event<ReturnType> operator -(Event<ReturnType> Delegate, Func<ReturnType> function)
    {
        return Delegate.Remove(function);
    }


    // ENUMERATOR FUNCTION

    // Enumerator implementation
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

    // Global list of all delegates
    private static List<DynamicEvent> allDelegates = new List<DynamicEvent>();

    // Global delegate cancellation token
    private static bool cancelAll = false;

    // Index of current invoked delegate
    private static int invokeIndex = 0;


    // DELEGATE DATA

    // List of functions included in the delegate
    private List<Function> functions = new List<Function>();

    // Delegate cancellation token
    private bool cancel = false;

    // Index of current delegate
    private int index = 0;


    // DELEGATE CONSTRUCTOR AND DECONSTRUCTOR

    // Default constructor
    public DynamicEvent()
    {
        functions = new List<Function>();

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    // Array constructor
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

    // List constructor
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

    // Delegate constructor
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

    // Deconstructor
    ~DynamicEvent()
    {
        for (int i = index + 1; i < allDelegates.Count; i++)
        {
            allDelegates[i].index--;
        }

        allDelegates.Remove(this);
    }


    // DELEGATE FUNCTIONS

    /// <summary> Returns a dictionary with each key representing the function and the value being the returned data. </summary>
    public Dictionary<Function, object> Invoke()
    {
        cancel = false;

        cancelAll = false;

        invokeIndex = index;

        Dictionary<Function, object> returns = new Dictionary<Function, object>(functions.Count);

        for (int i = 0; i < functions.Count; i++)
        {
            returns[functions[i]] = functions[i].DynamicInvoke();

            if (cancel || cancelAll)
            {
                break;
            }
        }

        return returns;
    }

    // Invokes every delegate
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

    // Reinvokes the current delegate
    public static Dictionary<Function, object> InvokeCurrent()
    {
        return allDelegates[invokeIndex].Invoke();
    }

    // Cancel an invoke
    public void Cancel()
    {
        cancel = true;
    }

    // Cancel all invokes
    public static void CancelAll()
    {
        cancelAll = true;
    }

    // Cancel the current invoke
    public static void CancelCurrent()
    {
        allDelegates[invokeIndex].cancel = true;
    }


    // COLLECTION FUNCTIONS

    // Gets a function in the delegate
    public Function Get(int index)
    {
        return functions[index];
    }

    // Sets a function in the delegate
    public DynamicEvent Set(int index, Function function)
    {
        if (function.Method.GetParameters().Length == 0)
        {
            functions[index] = function;
        }

        return this;
    }

    // Add a new function to the delegate
    public DynamicEvent Add(Function function)
    {
        if (function.Method.GetParameters().Length == 0)
        {
            functions.Add(function);
        }

        return this;
    }

    // Adds new functions to the delegate
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

    // Adds new functions to the delegate
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

    // Adds another delegate to the delegate
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

    // Remove a function from the delegate
    public DynamicEvent Remove(Function function)
    {
        functions.Remove(function);

        return this;
    }

    // Remove a function from the delegate
    public DynamicEvent RemoveAt(int index)
    {
        functions.RemoveAt(index);

        return this;
    }

    // Removes a delegate's functions from the delegate
    public DynamicEvent Remove(DynamicEvent removedDelegate)
    {
        for (int i = 0; i < removedDelegate.functions.Count; i++)
        {
            functions.Remove(removedDelegate.functions[i]);
        }

        return this;
    }

    // Clear all functions from the delegate
    public DynamicEvent Clear()
    {
        functions.Clear();

        return this;
    }

    // Return the number of functions in the delegate
    public int Count()
    {
        return functions.Count;
    }

    // Returns if the delegate contains a function
    public bool Contains(Function function)
    {
        return functions.Contains(function);
    }

    // Returns the index of the function in the delegate, or -1 if it was not found
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

    // Returns an array of the functions
    public Function[] ToArray()
    {
        return functions.ToArray();
    }

    // Returns a list of the functions
    public List<Function> ToList()
    {
        return functions;
    }


    // PARAMETER FUNCTIONS

    // Returns whether the given types match with the given parameters
    public static bool CheckObjectParameters(object[] objects, ParameterInfo[] parameters)
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

    // Adding a function
    public static DynamicEvent operator +(DynamicEvent Delegate, Function function)
    {
        return Delegate.Add(function);
    }

    // Removing a function
    public static DynamicEvent operator -(DynamicEvent Delegate, Function function)
    {
        return Delegate.Remove(function);
    }


    // ENUMERATOR FUNCTION

    // Enumerator implementation
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

    // Global list of all delegates
    private static List<Delegate> allDelegates = new List<Delegate>();

    // Global delegate cancellation token
    private static bool cancelAll = false;

    // Index of current invoked delegate
    private static int invokeIndex = 0;


    // DELEGATE DATA

    // List of functions included in the delegate
    private List<Function> functions = new List<Function>();

    // Delegate cancellation token
    private bool cancel = false;

    // Index of current delegate
    private int index = 0;

    // Delegate parameters
    private Type[] parameterTypes = null;


    // DELEGATE CONSTRUCTOR AND DECONSTRUCTOR

    // Default constructor
    public Delegate()
    {
        functions = new List<Function>();

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    // Array constructor
    public Delegate(params Function[] functions)
    {
        this.functions = new List<Function>(functions.Length);

        for (int i = 0; i < functions.Length; i++)
        {
            if (parameterTypes != null && !CheckParameters(parameterTypes, functions[i].Method.GetParameters()))
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

    // List constructor
    public Delegate(List<Function> functions)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            if (parameterTypes != null && !CheckParameters(parameterTypes, functions[i].Method.GetParameters()))
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

    // Delegate constructor
    public Delegate(Delegate newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            if (parameterTypes != null && !CheckParameters(parameterTypes, functions[i].Method.GetParameters()))
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

    // Deconstructor
    ~Delegate()
    {
        for (int i = index + 1; i < allDelegates.Count; i++)
        {
            allDelegates[i].index--;
        }

        allDelegates.Remove(this);
    }


    // DELEGATE FUNCTIONS

    /// <summary> Call each function in the delegate and return if the invoke was successful. </summary>
    public bool Invoke(params object[] parameters)
    {
        cancel = false;

        cancelAll = false;

        invokeIndex = index;

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
                return false;
            }
        }

        return true;
    }

    // Invokes every delegate
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

    // Reinvokes the current delegate
    public static bool InvokeCurrent(params object[] parameters)
    {
        return allDelegates[invokeIndex].Invoke(parameters);
    }

    // Cancel an invoke
    public void Cancel()
    {
        cancel = true;
    }

    // Cancel all invokes
    public static void CancelAll()
    {
        cancelAll = true;
    }

    // Cancel the current invoke
    public static void CancelCurrent()
    {
        allDelegates[invokeIndex].cancel = true;
    }


    // COLLECTION FUNCTIONS

    // Gets a function in the delegate
    public Function Get(int index)
    {
        return functions[index];
    }

    // Sets a function in the delegate
    public Delegate Set(int index, Function function)
    {
        if (parameterTypes != null && !CheckParameters(parameterTypes, function.Method.GetParameters()))
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

    // Add a new function to the delegate
    public Delegate Add(Function function)
    {
        if (parameterTypes != null && !CheckParameters(parameterTypes, function.Method.GetParameters()))
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

    // Adds new functions to the delegate
    public Delegate Add(params Function[] functions)
    {
        for (int i = 0; i < functions.Length; i++)
        {
            if (parameterTypes != null && !CheckParameters(parameterTypes, functions[i].Method.GetParameters()))
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

    // Adds new functions to the delegate
    public Delegate Add(List<Function> functions)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            if (parameterTypes != null && !CheckParameters(parameterTypes, functions[i].Method.GetParameters()))
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

    // Adds another delegate to the delegate
    public Delegate Add(Delegate newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            if (parameterTypes != null && !CheckParameters(parameterTypes, functions[i].Method.GetParameters()))
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

    // Remove a function from the delegate
    public Delegate Remove(Function function)
    {
        functions.Remove(function);

        return this;
    }

    // Remove a function from the delegate
    public Delegate RemoveAt(int index)
    {
        functions.RemoveAt(index);

        return this;
    }

    // Removes a delegate's functions from the delegate
    public Delegate Remove(Delegate removedDelegate)
    {
        for (int i = 0; i < removedDelegate.functions.Count; i++)
        {
            functions.Remove(removedDelegate.functions[i]);
        }

        return this;
    }

    // Clear all functions from the delegate
    public Delegate Clear()
    {
        functions.Clear();

        parameterTypes = null;

        return this;
    }

    // Return the number of functions in the delegate
    public int Count()
    {
        return functions.Count;
    }

    // Returns if the delegate contains a function
    public bool Contains(Function function)
    {
        return functions.Contains(function);
    }

    // Returns the index of the function in the delegate, or -1 if it was not found
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

    // Returns an array of the functions
    public Function[] ToArray()
    {
        return functions.ToArray();
    }

    // Returns a list of the functions
    public List<Function> ToList()
    {
        return functions;
    }


    // PARAMETER FUNCTIONS

    // Get the assigned parameters of this delegate
    public Type[] GetParameters()
    {
        return parameterTypes;
    }

    // Set the parameters of this delegate if they have not been assigned yet
    public bool SetParameters(Type[] newParameters)
    {
        if (parameterTypes == null || functions.Count == 0)
        {
            parameterTypes = newParameters;

            return true;
        }

        return false;
    }

    // Set the parameters of this delegate if they have not been assigned yet
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

    // Reset the parameters of this delegate and clear all functions
    public Delegate Reset(Type[] newParameters = null)
    {
        functions.Clear();

        parameterTypes = newParameters;

        return this;
    }

    // Reset the parameters of this delegate and clear all functions
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

    // Returns whether the given types match with the given parameters
    public static bool CheckParameters(Type[] types, ParameterInfo[] parameters)
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

    // Returns an array of parameter types from the given parameter info
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

    // Adding a function
    public static Delegate operator +(Delegate Delegate, Function function)
    {
        return Delegate.Add(function);
    }

    // Removing a function
    public static Delegate operator -(Delegate Delegate, Function function)
    {
        return Delegate.Remove(function);
    }


    // ENUMERATOR FUNCTION

    // Enumerator implementation
    public IEnumerator GetEnumerator()
    {
        return functions.GetEnumerator();
    }
}

/// <summary>
/// Wrapper class for a collection of functions.
/// All stored functions must share the same parameters.
/// All stored functions must share the same return type.
/// </summary>
public class Delegate<ReturnType> : IEnumerable
{
    // STATIC DELEGATE DATA

    // Global list of all delegates
    private static List<Delegate<ReturnType>> allDelegates = new List<Delegate<ReturnType>>();

    // Global delegate cancellation token
    private static bool cancelAll = false;

    // Index of current invoked delegate
    private static int invokeIndex = 0;


    // DELEGATE DATA

    // List of functions included in the delegate
    private List<Function> functions = new List<Function>();

    // Delegate cancellation token
    private bool cancel = false;

    // Index of current delegate
    private int index = 0;

    // Delegate parameters
    private Type[] parameterTypes = null;


    // DELEGATE CONSTRUCTOR AND DECONSTRUCTOR

    // Default constructor
    public Delegate()
    {
        functions = new List<Function>();

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    // Array constructor
    public Delegate(params Function[] functions)
    {
        this.functions = new List<Function>(functions.Length);

        for (int i = 0; i < functions.Length; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }
            else if (parameterTypes != null && !CheckParameters(parameterTypes, functions[i].Method.GetParameters()))
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

    // List constructor
    public Delegate(List<Function> functions)
    {
        this.functions = functions;

        for (int i = 0; i < functions.Count; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }
            else if (parameterTypes != null && !CheckParameters(parameterTypes, functions[i].Method.GetParameters()))
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

    // Delegate constructor
    public Delegate(Delegate<ReturnType> newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }
            else if (parameterTypes != null && !CheckParameters(parameterTypes, functions[i].Method.GetParameters()))
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

    // Deconstructor
    ~Delegate()
    {
        for (int i = index + 1; i < allDelegates.Count; i++)
        {
            allDelegates[i].index--;
        }

        allDelegates.Remove(this);
    }


    // DELEGATE FUNCTIONS

    /// <summary> Returns a dictionary with each key representing the function and the value being the returned data. </summary>
    public Dictionary<Function, ReturnType> Invoke(params object[] parameters)
    {
        cancel = false;

        cancelAll = false;

        invokeIndex = index;

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

        return returns;
    }

    // Invokes every delegate
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

    // Reinvokes the current delegate
    public static Dictionary<Function, ReturnType> InvokeCurrent(params object[] parameters)
    {
        return allDelegates[invokeIndex].Invoke(parameters);
    }

    // Cancel an invoke
    public void Cancel()
    {
        cancel = true;
    }

    // Cancel all invokes
    public static void CancelAll()
    {
        cancelAll = true;
    }

    // Cancel the current invoke
    public static void CancelCurrent()
    {
        allDelegates[invokeIndex].cancel = true;
    }


    // COLLECTION FUNCTIONS

    // Gets a function in the delegate
    public Function Get(int index)
    {
        return functions[index];
    }

    // Sets a function in the delegate
    public Delegate<ReturnType> Set(int index, Function function)
    {
        if (typeof(ReturnType) != function.Method.ReturnType)
        {
            Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
        }
        else if (parameterTypes != null && !CheckParameters(parameterTypes, function.Method.GetParameters()))
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

    // Add a new function to the delegate
    public Delegate<ReturnType> Add(Function function)
    {
        if (typeof(ReturnType) != function.Method.ReturnType)
        {
            Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
        }
        else if (parameterTypes != null && !CheckParameters(parameterTypes, function.Method.GetParameters()))
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

    // Adds new functions to the delegate
    public Delegate<ReturnType> Add(params Function[] functions)
    {
        for (int i = 0; i < functions.Length; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }
            else if (parameterTypes != null && !CheckParameters(parameterTypes, functions[i].Method.GetParameters()))
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

    // Adds new functions to the delegate
    public Delegate<ReturnType> Add(List<Function> functions)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }
            else if (parameterTypes != null && !CheckParameters(parameterTypes, functions[i].Method.GetParameters()))
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

    // Adds another delegate to the delegate
    public Delegate<ReturnType> Add(Delegate<ReturnType> newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            if (typeof(ReturnType) != functions[i].Method.ReturnType)
            {
                Debug.Assert(false, "DELEGATE ERROR: Could not add the function to the delegate! The function's return type does not match the delegate's return type!");
            }
            else if (parameterTypes != null && !CheckParameters(parameterTypes, functions[i].Method.GetParameters()))
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

    // Remove a function from the delegate
    public Delegate<ReturnType> Remove(Function function)
    {
        functions.Remove(function);

        return this;
    }

    // Remove a function from the delegate
    public Delegate<ReturnType> RemoveAt(int index)
    {
        functions.RemoveAt(index);

        return this;
    }

    // Removes a delegate's functions from the delegate
    public Delegate<ReturnType> Remove(Delegate<ReturnType> removedDelegate)
    {
        for (int i = 0; i < removedDelegate.functions.Count; i++)
        {
            functions.Remove(removedDelegate.functions[i]);
        }

        return this;
    }

    // Clear all functions from the delegate
    public Delegate<ReturnType> Clear()
    {
        functions.Clear();

        parameterTypes = null;

        return this;
    }

    // Return the number of functions in the delegate
    public int Count()
    {
        return functions.Count;
    }

    // Returns if the delegate contains a function
    public bool Contains(Function function)
    {
        return functions.Contains(function);
    }

    // Returns the index of the function in the delegate, or -1 if it was not found
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

    // Returns an array of the functions
    public Function[] ToArray()
    {
        return functions.ToArray();
    }

    // Returns a list of the functions
    public List<Function> ToList()
    {
        return functions;
    }


    // PARAMETER FUNCTIONS

    // Get the assigned parameters of this delegate
    public Type[] GetParameters()
    {
        return parameterTypes;
    }

    // Set the parameters of this delegate if they have not been assigned yet
    public bool SetParameters(Type[] newParameters)
    {
        if (parameterTypes == null || functions.Count == 0)
        {
            parameterTypes = newParameters;

            return true;
        }

        return false;
    }

    // Set the parameters of this delegate if they have not been assigned yet
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

    // Reset the parameters of this delegate and clear all functions
    public Delegate<ReturnType> Reset(Type[] newParameters = null)
    {
        functions.Clear();

        parameterTypes = newParameters;

        return this;
    }

    // Reset the parameters of this delegate and clear all functions
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

    // Returns whether the given types match with the given parameters
    public static bool CheckParameters(Type[] types, ParameterInfo[] parameters)
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

    // Returns an array of parameter types from the given parameter info
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

    // Adding a function
    public static Delegate<ReturnType> operator +(Delegate<ReturnType> Delegate, Function function)
    {
        return Delegate.Add(function);
    }

    // Removing a function
    public static Delegate<ReturnType> operator -(Delegate<ReturnType> Delegate, Function function)
    {
        return Delegate.Remove(function);
    }


    // ENUMERATOR FUNCTION

    // Enumerator implementation
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

    // Global list of all delegates
    private static List<DynamicDelegate> allDelegates = new List<DynamicDelegate>();

    // Global delegate cancellation token
    private static bool cancelAll = false;

    // Index of current invoked delegate
    private static int invokeIndex = 0;


    // DELEGATE DATA

    // List of functions included in the delegate
    private List<Function> functions = new List<Function>();

    // Delegate cancellation token
    private bool cancel = false;

    // Index of current delegate
    private int index = 0;


    // DELEGATE CONSTRUCTOR AND DECONSTRUCTOR

    // Default constructor
    public DynamicDelegate()
    {
        functions = new List<Function>();

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    // Array constructor
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

    // List constructor
    public DynamicDelegate(List<Function> functions)
    {
        this.functions = functions;

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    // Delegate constructor
    public DynamicDelegate(DynamicDelegate newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            functions.Add(newDelegate.functions[i]);
        }

        allDelegates.Add(this);

        index = allDelegates.Count - 1;
    }

    // Deconstructor
    ~DynamicDelegate()
    {
        for (int i = index + 1; i < allDelegates.Count; i++)
        {
            allDelegates[i].index--;
        }

        allDelegates.Remove(this);
    }


    // DELEGATE FUNCTIONS

    /// <summary> Returns a dictionary with each key representing the function and the value being the returned data. </summary>
    public Dictionary<Function, object> Invoke(params object[] parameters)
    {
        cancel = false;

        cancelAll = false;

        invokeIndex = index;

        Dictionary<Function, object> returns = new Dictionary<Function, object>(functions.Count);

        for (int i = 0; i < functions.Count; i++)
        {
            if (CheckObjectParameters(parameters, functions[i].Method.GetParameters()))
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

        return returns;
    }

    // Invokes every delegate
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

    // Reinvokes the current delegate
    public static Dictionary<Function, object> InvokeCurrent(params object[] parameters)
    {
        return allDelegates[invokeIndex].Invoke(parameters);
    }

    // Cancel an invoke
    public void Cancel()
    {
        cancel = true;
    }

    // Cancel all invokes
    public static void CancelAll()
    {
        cancelAll = true;
    }

    // Cancel the current invoke
    public static void CancelCurrent()
    {
        allDelegates[invokeIndex].cancel = true;
    }


    // COLLECTION FUNCTIONS

    // Gets a function in the delegate
    public Function Get(int index)
    {
        return functions[index];
    }

    // Sets a function in the delegate
    public DynamicDelegate Set(int index, Function function)
    {
        functions[index] = function;

        return this;
    }

    // Add a new function to the delegate
    public DynamicDelegate Add(Function function)
    {
        functions.Add(function);

        return this;
    }

    // Adds new functions to the delegate
    public DynamicDelegate Add(params Function[] functions)
    {
        for (int i = 0; i < functions.Length; i++)
        {
            this.functions.Add(functions[i]);
        }

        return this;
    }

    // Adds new functions to the delegate
    public DynamicDelegate Add(List<Function> functions)
    {
        for (int i = 0; i < functions.Count; i++)
        {
            this.functions.Add(functions[i]);
        }

        return this;
    }

    // Adds another delegate to the delegate
    public DynamicDelegate Add(DynamicDelegate newDelegate)
    {
        for (int i = 0; i < newDelegate.functions.Count; i++)
        {
            functions.Add(newDelegate.functions[i]);
        }

        return this;
    }

    // Remove a function from the delegate
    public DynamicDelegate Remove(Function function)
    {
        functions.Remove(function);

        return this;
    }

    // Remove a function from the delegate
    public DynamicDelegate RemoveAt(int index)
    {
        functions.RemoveAt(index);

        return this;
    }

    // Removes a delegate's functions from the delegate
    public DynamicDelegate Remove(DynamicDelegate removedDelegate)
    {
        for (int i = 0; i < removedDelegate.functions.Count; i++)
        {
            functions.Remove(removedDelegate.functions[i]);
        }

        return this;
    }

    // Clear all functions from the delegate
    public DynamicDelegate Clear()
    {
        functions.Clear();

        return this;
    }

    // Return the number of functions in the delegate
    public int Count()
    {
        return functions.Count;
    }

    // Returns if the delegate contains a function
    public bool Contains(Function function)
    {
        return functions.Contains(function);
    }

    // Returns the index of the function in the delegate, or -1 if it was not found
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

    // Returns an array of the functions
    public Function[] ToArray()
    {
        return functions.ToArray();
    }

    // Returns a list of the functions
    public List<Function> ToList()
    {
        return functions;
    }


    // PARAMETER FUNCTIONS

    // Returns whether the given types match with the given parameters
    public static bool CheckObjectParameters(object[] objects, ParameterInfo[] parameters)
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

    // Adding a function
    public static DynamicDelegate operator +(DynamicDelegate Delegate, Function function)
    {
        return Delegate.Add(function);
    }

    // Removing a function
    public static DynamicDelegate operator -(DynamicDelegate Delegate, Function function)
    {
        return Delegate.Remove(function);
    }


    // ENUMERATOR FUNCTION

    // Enumerator implementation
    public IEnumerator GetEnumerator()
    {
        return functions.GetEnumerator();
    }
}
