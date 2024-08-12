
// IFunctional Interface Script
// by Kyle Furey

// Inherit from this interface to implement it

/// <summary>
/// Since function pointers do not exist in C#, this interface provides a generic function that can be used to store objects that implement it to imitate functional programming.
/// </summary>
public interface IFunctional
{
    /// <summary>
    /// •  The custom function this object implements to imitate functional programming.<br/>
    /// •  Parameters and return types are objects by default as they can be downcasted into any other type.
    /// </summary>
    /// <param name="arguments">An array of objects representing the parameters of this function.</param>
    /// <returns>An object representing the return of this function.</returns>
    public abstract object Invoke(params object[] arguments);
}
