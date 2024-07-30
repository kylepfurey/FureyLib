
// Object Factory Class Script
// by Kyle Furey

using System.Collections;
using System.Collections.Generic;

/// <summary>
/// Provides easy instantiation of new derived objects.
/// </summary>
public class Factory : IEnumerable, IEnumerable<object>
{
    // OBJECTS

    /// <summary>
    /// All of this factory's objects.
    /// </summary>
    public LinkedList<object> objects = new LinkedList<object>();


    // COUNT

    /// <summary>
    /// Returns the current size of the factory.
    /// </summary>
    public int Count { get => objects.Count; }


    // INSTANTIATE

    /// <summary>
    /// Instantiates a new derived object of the given type.
    /// </summary>
    /// <typeparam name="DerivedType"></typeparam>
    /// <returns></returns>
    public DerivedType Instantiate<DerivedType>() where DerivedType : new()
    {
        DerivedType instantiated = new DerivedType();

        objects.AddLast(instantiated);

        return instantiated;
    }

    /// <summary>
    /// Instantiates a new derived object of the given type.
    /// </summary>
    /// <typeparam name="DerivedType"></typeparam>
    /// <returns></returns>
    public DerivedType Instantiate<DerivedType>(DerivedType argument = default(DerivedType))
    {
        DerivedType instantiated = argument;

        objects.AddLast(instantiated);

        return instantiated;
    }


    // REMOVAL

    /// <summary>
    /// Manually removes the given factory object.
    /// </summary>
    /// <typeparam name="DerivedType"></typeparam>
    /// <param name="removed"></param>
    public void Remove<DerivedType>(DerivedType removed)
    {
        if (removed == null)
        {
            return;
        }

        objects.Remove(removed);
    }

    /// <summary>
    /// Removes all of the objects in the factory and return its previous size.
    /// </summary>
    /// <returns></returns>
    int Clear()
    {
        int size = objects.Count;

        objects.Clear();

        return size;
    }


    // CONTAINS

    /// <summary>
    /// Returns whether the given factory object is present in this factory.
    /// </summary>
    /// <typeparam name="DerivedType"></typeparam>
    /// <param name="found"></param>
    /// <returns></returns>
    public bool Contains<DerivedType>(DerivedType found)
    {
        if (found == null)
        {
            return false;
        }

        return objects.Contains(found);
    }


    // IENUMERABLE

    /// <summary>
    /// IEnumerator implementation.
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return objects.GetEnumerator();
    }

    /// <summary>
    /// IEnumerator implementation.
    /// </summary>
    /// <returns></returns>
    IEnumerator<object> IEnumerable<object>.GetEnumerator()
    {
        return objects.GetEnumerator();
    }
}

/// <summary>
/// Provides easy instantiation of new derived objects from a base type.
/// </summary>
/// <typeparam name="BaseType"></typeparam>
public class Factory<BaseType> : IEnumerable, IEnumerable<BaseType>
{
    // OBJECTS

    /// <summary>
    /// All of this factory's objects.
    /// </summary>
    public LinkedList<BaseType> objects = new LinkedList<BaseType>();


    // COUNT

    /// <summary>
    /// Returns the current size of the factory.
    /// </summary>
    public int Count { get => objects.Count; }


    // INSTANTIATE

    /// <summary>
    /// Instantiates a new derived object of the given type.
    /// </summary>
    /// <typeparam name="DerivedType"></typeparam>
    /// <returns></returns>
    public DerivedType Instantiate<DerivedType>() where DerivedType : BaseType, new()
    {
        DerivedType instantiated = new DerivedType();

        objects.AddLast(instantiated);

        return instantiated;
    }


    // REMOVAL

    /// <summary>
    /// Manually removes the given factory object.
    /// </summary>
    /// <typeparam name="DerivedType"></typeparam>
    /// <param name="removed"></param>
    public void Remove<DerivedType>(DerivedType removed) where DerivedType : BaseType
    {
        if (removed == null)
        {
            return;
        }

        objects.Remove(removed);
    }

    /// <summary>
    /// Removes all of the objects in the factory and return its previous size.
    /// </summary>
    /// <returns></returns>
    int Clear()
    {
        int size = objects.Count;

        objects.Clear();

        return size;
    }


    // CONTAINS

    /// <summary>
    /// Returns whether the given factory object is present in this factory.
    /// </summary>
    /// <typeparam name="DerivedType"></typeparam>
    /// <param name="found"></param>
    /// <returns></returns>
    public bool Contains<DerivedType>(DerivedType found) where DerivedType : BaseType
    {
        if (found == null)
        {
            return false;
        }

        return objects.Contains(found);
    }


    // IENUMERABLE

    /// <summary>
    /// IEnumerator implementation.
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return objects.GetEnumerator();
    }

    /// <summary>
    /// IEnumerator implementation.
    /// </summary>
    /// <returns></returns>
    IEnumerator<BaseType> IEnumerable<BaseType>.GetEnumerator()
    {
        return objects.GetEnumerator();
    }
}
