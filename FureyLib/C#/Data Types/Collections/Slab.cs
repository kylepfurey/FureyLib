// .cs
// Slab Type
// by Kyle Furey

#nullable enable
using System;
using System.Collections;
using System.Collections.Generic;


// SLAB

/// <summary>
/// A unique ID used to lookup an object in a slab.
/// </summary>
using ID = System.Int32;

/// <summary>
/// A collection that manages the memory of each object it contains by providing handles to access the objects.
/// </summary>
public sealed class Slab<T> : IEnumerable, IEnumerable<(ID ID, T Object)> where T : notnull
{
    // VARIABLES

    /// <summary>
    /// The underlying array of objects in the slab.
    /// </summary>
    private List<T?> objects = null!;

    /// <summary>
    /// Each ID that can be reused in the slab.
    /// </summary>
    private Queue<ID> nextIDs = new Queue<ID>();

    /// <summary>
    /// The current number of objects in the slab.
    /// </summary>
    private int count = 0;


    // PROPERTIES

    /// <summary>
    /// The number of objects currently in the slab.
    /// </summary>
    public int Count => count;

    /// <summary>
    /// The maximum number of objects that can be stored before resizing the slab.
    /// </summary>
    public int Capacity => objects.Capacity;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor.
    /// </summary>
    public Slab(int capacity = 16)
    {
        objects = new List<T?>(capacity);
        for (int i = 0; i < capacity; ++i)
        {
            nextIDs.Enqueue(i);
            objects.Add(default(T?));
        }
    }

    /// <summary>
    /// Copy constructor,
    /// </summary>
    public Slab(Slab<T> copied)
    {
        if (copied == null)
        {
            throw new ArgumentNullException(nameof(copied));
        }
        objects = new List<T?>(copied.objects);
        nextIDs = new Queue<ID>(copied.nextIDs);
        count = copied.count;
    }


    // INDEXER

    /// <summary>
    /// Finds the object with the specified ID if it is valid.
    /// </summary>
    public T? this[ID id]
    {
        get => Find(id);
    }


    // IENUMERATOR

    /// <summary>
    /// Returns an enumerator that iterates through all the slab's objects.
    /// </summary>
    public IEnumerator GetEnumerator()
    {
        ID id = 0;
        foreach (T? obj in objects)
        {
            if (obj != null)
            {
                yield return (ID: id, Object: (T)obj);
            }
            ++id;
        }
    }

    /// <summary>
    /// Returns an enumerator that iterates through all the slab's objects.
    /// </summary>
    IEnumerator<(ID ID, T Object)> IEnumerable<(ID ID, T Object)>.GetEnumerator()
    {
        ID id = 0;
        foreach (T? obj in objects)
        {
            if (obj != null)
            {
                yield return (ID: id, Object: (T)obj);
            }
            ++id;
        }
    }


    // METHODS

    /// <summary>
    /// Adds the object to the slab and returns its unique ID.
    /// </summary>
    public ID Add(T obj)
    {
        if (obj == null)
        {
            throw new ArgumentNullException(nameof(obj), "ERROR: Cannot add a null object to the slab!");
        }
        if (nextIDs.Count == 0)
        {
            int capacity = objects.Capacity == 0 ? 16 : objects.Capacity * 2;
            for (int i = objects.Count; i < capacity; ++i)
            {
                nextIDs.Enqueue(i);
                objects.Add(default(T?));
            }
        }
        ID id = nextIDs.Dequeue();
        objects[id] = obj;
        ++count;
        return id;
    }

    /// <summary>
    /// Removes the object that matches the given ID from the slab, and returns whether it was successful.
    /// </summary>
    public bool Remove(ID id)
    {
        if ((id < 0) || (id >= objects.Count) || (objects[id] == null))
        {
            return false;
        }
        objects[id] = default(T?);
        nextIDs.Enqueue(id);
        --count;
        return true;
    }

    /// <summary>
    /// Returns whether the slab contains an object with the given ID.
    /// </summary>
    public bool Contains(ID id)
    {
        return (id >= 0) && (id < objects.Count) && (objects[id] != null);
    }

    /// <summary>
    /// Returns the object with the given ID if it exists, or null if it does not.
    /// </summary>
    public T? Find(ID id)
    {
        return (id >= 0 && id < objects.Count) ? (objects[id]) : (default(T?));
    }

    /// <summary>
    /// Clears the slab of all its objects.
    /// </summary>
    public void Clear(int capacity = 16)
    {
        objects.Clear();
        nextIDs.Clear();
        count = 0;
        for (int i = 0; i < capacity; ++i)
        {
            nextIDs.Enqueue(i);
            objects.Add(default(T?));
        }
    }
}
