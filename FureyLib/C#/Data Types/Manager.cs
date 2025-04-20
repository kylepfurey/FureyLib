// .cs
// Memory Manager Type
// by Kyle Furey

using System;
using System.Collections;
using System.Collections.Generic;

// MANAGER

/// <summary>
/// A class used to manually instantiate and delete managed objects of a given type.
/// </summary>
public sealed class Manager<Type> : IEnumerable, IEnumerable<Type>, IDisposable where Type : class
{
    // DATA

    /// <summary>
    /// Each managed object this memory manager currently stores.<br/>
    /// Objects can be manually created via Manager.New().<br/>
    /// Objects can be manually deleted via Manager.Delete().
    /// </summary>
    private readonly List<Type> managedObjects;

    /// <summary>
    /// The current number of managed objects.
    /// </summary>
    public int Count => managedObjects.Count;

    /// <summary>
    /// The maximum number of managed objects before automatically expanding.
    /// </summary>
    public int Capacity => managedObjects.Capacity;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor.
    /// </summary>
    public Manager(int Capacity = 16)
    {
        managedObjects = new List<Type>(Capacity);
    }

    /// <summary>
    /// Destructor.
    /// </summary>
    ~Manager()
    {
        Clear();
    }


    // OPERATORS

    /// <summary>
    /// Returns the managed object at the given index.
    /// </summary>
    public WeakReference<Type> this[int Index]
    {
        get => new WeakReference<Type>(managedObjects[Index]);
    }


    // NEW

    /// <summary>
    /// Creates a new managed object and returns a weak reference to it.
    /// </summary>
    public WeakReference<DerivedType> New<DerivedType>() where DerivedType : class, Type, new()
    {
        managedObjects.Add((Type)(new DerivedType()));

        return new WeakReference<DerivedType>((DerivedType)managedObjects[managedObjects.Count - 1]);
    }

    /// <summary>
    /// Creates a new managed object from the given arguments and returns a weak reference to it.
    /// </summary>
    public WeakReference<DerivedType> New<DerivedType>(params object[] Arguments) where DerivedType : class, Type
    {
        DerivedType Instance = (DerivedType)Activator.CreateInstance(typeof(DerivedType), Arguments);

        managedObjects.Add(Instance);

        return new WeakReference<DerivedType>(Instance);
    }

    /// <summary>
    /// Creates a new managed object from a clone of the given object and returns a weak reference to it.
    /// </summary>
    public WeakReference<DerivedType> New<DerivedType>(DerivedType Cloned) where DerivedType : class, Type, ICloneable
    {
        if (Cloned == null)
        {
            return null;
        }

        managedObjects.Add((Type)(Cloned.Clone()));

        return new WeakReference<DerivedType>((DerivedType)managedObjects[managedObjects.Count - 1]);
    }

    /// <summary>
    /// Creates a new managed object and returns a weak reference to it.
    /// </summary>
    public WeakReference<DerivedType> Add<DerivedType>() where DerivedType : class, Type, new()
    {
        return New<DerivedType>();
    }

    /// <summary>
    /// Creates a new managed object from the given arguments and returns a weak reference to it.
    /// </summary>
    public WeakReference<DerivedType> Add<DerivedType>(params object[] Arguments) where DerivedType : class, Type
    {
        return New<DerivedType>(Arguments);
    }


    /// <summary>
    /// Creates a new managed object from a clone of the given object and returns a weak reference to it.
    /// </summary>
    public WeakReference<DerivedType> Add<DerivedType>(DerivedType Cloned) where DerivedType : class, Type, ICloneable
    {
        return New<DerivedType>(Cloned);
    }


    // DELETE

    /// <summary>
    /// Forcefully deletes a managed object and returns whether it was successful.
    /// </summary>
    public bool Delete(Type Deleted, bool ForceGC = false)
    {
        if (managedObjects.Remove(Deleted))
        {
            if (Deleted is IDisposable Disposed)
            {
                Disposed.Dispose();
            }

            if (ForceGC)
            {
                GC.Collect();

                GC.WaitForPendingFinalizers();
            }

            return true;
        }

        return false;
    }

    /// <summary>
    /// Forcefully deletes a managed object and returns whether it was successful.
    /// </summary>
    public bool Delete(WeakReference<Type> Deleted, bool ForceGC = false)
    {
        if (Deleted != null && Deleted.TryGetTarget(out Type Target))
        {
            if (managedObjects.Remove(Target))
            {
                if (Target is IDisposable Disposed)
                {
                    Disposed.Dispose();
                }

                if (ForceGC)
                {
                    GC.Collect();

                    GC.WaitForPendingFinalizers();
                }

                return true;
            }
        }

        return false;
    }

    /// <summary>
    /// Forcefully deletes a managed object and returns whether it was successful.
    /// </summary>
    public bool Remove(Type Deleted, bool ForceGC = false)
    {
        return Delete(Deleted, ForceGC);
    }

    /// <summary>
    /// Forcefully deletes a managed object and returns whether it was successful.
    /// </summary>
    public bool Remove(WeakReference<Type> Deleted, bool ForceGC = false)
    {
        return Delete(Deleted, ForceGC);
    }


    // CLEAR

    /// <summary>
    /// Forcefully deletes all managed objects within the memory manager.
    /// </summary>
    public int Clear(bool ForceGC = false)
    {
        int Count = managedObjects.Count;

        foreach (Type Deleted in managedObjects)
        {
            if (Deleted is IDisposable Disposed)
            {
                Disposed.Dispose();
            }
        }

        managedObjects.Clear();

        if (ForceGC)
        {
            GC.Collect();

            GC.WaitForPendingFinalizers();
        }

        return Count;
    }


    // CONTAINS

    /// <summary>
    /// Returns whether the given managed object is within this memory manager.
    /// </summary>
    public bool Contains(Type Deleted)
    {
        return managedObjects.Contains(Deleted);
    }

    /// <summary>
    /// Returns whether the given managed object is within this memory manager.
    /// </summary>
    public bool Contains(WeakReference<Type> Deleted)
    {
        if (Deleted != null && Deleted.TryGetTarget(out Type Target))
        {
            return managedObjects.Contains(Target);
        }

        return false;
    }


    // ENUMERATORS

    /// <summary>
    /// Returns an enumerator for each managed object.
    /// </summary>
    public IEnumerator<Type> GetEnumerator()
    {
        return managedObjects.GetEnumerator();
    }

    /// <summary>
    /// Returns an enumerator for each managed object.
    /// </summary>
    IEnumerator IEnumerable.GetEnumerator()
    {
        return managedObjects.GetEnumerator();
    }


    // DISPOSE

    /// <summary>
    /// Forcefully deletes all managed objects within the memory manager.
    /// </summary>
    public void Dispose()
    {
        Clear();
    }
}


// WEAK REFERENCE EXTENSIONS

/// <summary>
/// Extension methods for WeakReference<T>.
/// </summary>
public static class WeakReferenceExtensions
{
    // WEAK REFERENCE EXTENSIONS

    /// <summary>
    /// Returns whether this weak reference is still valid.
    /// </summary>
    public static bool IsValid<Type>(this WeakReference<Type> Self) where Type : class
    {
        return Self != null && Self.TryGetTarget(out Type Value);
    }

    /// <summary>
    /// Returns the underlying value of this weak reference or null if it is not valid.
    /// </summary>
    public static Type Get<Type>(this WeakReference<Type> Self) where Type : class
    {
        if (Self != null && Self.TryGetTarget(out Type Value))
        {
            return Value;
        }

        return null;
    }
}


// REFERENCE

/// <summary>
/// A wrapper for value types that enable reference counting.
/// </summary>
public sealed class Reference<Type> where Type : struct
{
    // DATA

    /// <summary>
    /// The underlying value of this reference.
    /// </summary>
    public Type Value { get; set; }


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor.
    /// </summary>
    public Reference()
    {
        Value = default(Type);
    }

    /// <summary>
    /// Data constructor.
    /// </summary>
    public Reference(Type Data)
    {
        Value = Data;
    }
}
