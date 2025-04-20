// .cs
// Memory Manager Type
// by Kyle Furey

using System;
using System.Collections;
using System.Collections.Generic;


// MEMORY MANAGER

/// <summary>
/// A class used to manually instantiate and delete managed objects of a given type.
/// </summary>
public sealed class Manager<Type> : IEnumerable, IEnumerable<Type> where Type : class
{
    // DATA

    /// <summary>
    /// Each managed object this memory manager currently stores.<br/>
    /// Objects can be manually created via Manager.New().<br/>
    /// Objects can be manually deleted via Manager.Delete().
    /// </summary>
    public List<Type> ManagedObjects { get; private set; }

    /// <summary>
    /// The current number of managed objects.
    /// </summary>
    public int Count => ManagedObjects.Count;

    /// <summary>
    /// The maximum number of managed objects before automatically expanding.
    /// </summary>
    public int Capacity => ManagedObjects.Capacity;


    // DELEGATES

    /// <summary>
    /// A delegate for newly created managed objects.<br/>
    /// NOTE: Storing ManagedObject will prolong the lifetime of weak references to it!
    /// </summary>
    public delegate void NewObjectDelegate(Type ManagedObject);

    /// <summary>
    /// A delegate for deleted managed objects.<br/>
    /// NOTE: Storing ManagedObject will prolong the lifetime of weak references to it!
    /// </summary>
    public delegate void ObjectDeletedDelegate(Type ManagedObject);

    /// <summary>
    /// Events for when a new managed object is created.
    /// </summary>
    public event NewObjectDelegate OnNewObject;

    /// <summary>
    /// Events for when a managed object is deleted.
    /// </summary>
    public event ObjectDeletedDelegate OnObjectDeleted;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor.
    /// </summary>
    public Manager(int Capacity = 16)
    {
        ManagedObjects = new List<Type>(Capacity);
    }


    // OPERATORS

    /// <summary>
    /// Returns the managed object at the given index.
    /// </summary>
    public WeakReference<Type> this[int Index]
    {
        get => new WeakReference<Type>(ManagedObjects[Index]);
    }


    // NEW

    /// <summary>
    /// Creates a new managed object and returns a weak reference to it.
    /// </summary>
    public WeakReference<DerivedType> New<DerivedType>() where DerivedType : class, Type, new()
    {
        ManagedObjects.Add((Type)(new DerivedType()));

        OnNewObject?.Invoke(ManagedObjects[ManagedObjects.Count - 1]);

        return new WeakReference<DerivedType>((DerivedType)ManagedObjects[ManagedObjects.Count - 1]);
    }

    /// <summary>
    /// Creates a new managed object from the given arguments and returns a weak reference to it.
    /// </summary>
    public WeakReference<DerivedType> New<DerivedType>(params object[] Arguments) where DerivedType : class, Type
    {
        DerivedType Instance = (DerivedType)Activator.CreateInstance(typeof(DerivedType), Arguments);

        ManagedObjects.Add(Instance);

        OnNewObject?.Invoke(ManagedObjects[ManagedObjects.Count - 1]);

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

        ManagedObjects.Add((Type)(Cloned.Clone()));

        OnNewObject?.Invoke(ManagedObjects[ManagedObjects.Count - 1]);

        return new WeakReference<DerivedType>((DerivedType)ManagedObjects[ManagedObjects.Count - 1]);
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
    public bool Delete(Type ManagedObject, bool ForceGC = false)
    {
        if (ManagedObjects.Remove(ManagedObject))
        {
            OnObjectDeleted?.Invoke(ManagedObject);

            if (ManagedObject is IDisposable Disposed)
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
    public bool Delete<DerivedType>(WeakReference<DerivedType> ManagedObject, bool ForceGC = false) where DerivedType : class, Type
    {
        if (ManagedObject != null && ManagedObject.TryGetTarget(out DerivedType Target))
        {
            if (ManagedObjects.Remove(Target))
            {
                OnObjectDeleted?.Invoke(Target);

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
    public bool Remove(Type ManagedObject, bool ForceGC = false)
    {
        return Delete(ManagedObject, ForceGC);
    }

    /// <summary>
    /// Forcefully deletes a managed object and returns whether it was successful.
    /// </summary>
    public bool Remove<DerivedType>(WeakReference<DerivedType> ManagedObject, bool ForceGC = false) where DerivedType : class, Type
    {
        return Delete<DerivedType>(ManagedObject, ForceGC);
    }


    // CLEAR

    /// <summary>
    /// Forcefully deletes all managed objects within the memory manager.
    /// </summary>
    public int Clear(bool ForceGC = false)
    {
        int Count = ManagedObjects.Count;

        foreach (Type Deleted in ManagedObjects)
        {
            if (Deleted is IDisposable Disposed)
            {
                Disposed.Dispose();
            }
        }

        ManagedObjects.Clear();

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
    public bool Contains(Type ManagedObject)
    {
        return ManagedObjects.Contains(ManagedObject);
    }

    /// <summary>
    /// Returns whether the given managed object is within this memory manager.
    /// </summary>
    public bool Contains(WeakReference<Type> ManagedObject)
    {
        if (ManagedObject != null && ManagedObject.TryGetTarget(out Type Target))
        {
            return ManagedObjects.Contains(Target);
        }

        return false;
    }


    // ENUMERATORS

    /// <summary>
    /// Returns an enumerator for each managed object.
    /// </summary>
    public IEnumerator<Type> GetEnumerator()
    {
        return ManagedObjects.GetEnumerator();
    }

    /// <summary>
    /// Returns an enumerator for each managed object.
    /// </summary>
    IEnumerator IEnumerable.GetEnumerator()
    {
        return ManagedObjects.GetEnumerator();
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
