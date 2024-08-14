
// Game Object Spawning Selector Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

/// <summary>
/// Provides easy instantiation of objects of different types based on index.
/// </summary>
public class SpawnSelector : MonoBehaviour
{
    [Header("Provides easy instantiation of objects of different types based on index.")]

    [Header("\nCONFIGURATION")]

    [Header("The current / default spawned game object:")]
    [SerializeField] private GameObject current = null;

    [Header("The list of possible objects to spawn:")]
    public List<GameObject> prefabs = new List<GameObject>();

    [Header("The current spawning index:")]
    public int index = 0;

    [Header("Whether to delete the current object when a new one is spawned:")]
    public bool exclusiveSpawn = true;

    [Header("Whether to copy the transform values of the previous spawned object to the new one:")]
    public bool replacePreviousTransform = true;

    [Header("Events for this selector:")]
    public UnityEvent onSpawn = null;
    public UnityEvent onDestroy = null;
    public UnityEvent onShift = null;
    public UnityEvent onShiftLeft = null;
    public UnityEvent onShiftRight = null;

    /// <summary>
    /// The current number of prefabs.
    /// </summary>
    public int Count => prefabs.Count;

    /// <summary>
    /// The current object.
    /// </summary>
    public GameObject Current { get => current; }


    // INDEX FUNCTIONS

    /// <summary>
    /// Sets the index to the given number.
    /// </summary>
    public int SetIndex(int index)
    {
        onShift.Invoke();

        this.index = index;

        return index;
    }

    /// <summary>
    /// Sets the index to the given number.
    /// </summary>
    public GameObject SetIndexAndSpawn(int index)
    {
        SetIndex(index);

        return Spawn();
    }


    // SPAWNING FUNCTIONS

    /// <summary>
    /// Spawns the object at the current index.
    /// </summary>
    /// <returns></returns>
    public GameObject Spawn()
    {
        Vector3 position = transform.position;

        Quaternion rotation = transform.rotation;

        Transform parent = transform.parent;

        if (replacePreviousTransform && current != null)
        {
            position = current.transform.position;

            rotation = current.transform.rotation;

            parent = current.transform.parent;
        }

        if (exclusiveSpawn && current != null)
        {
            onDestroy.Invoke();

            Destroy(current);
        }

        onSpawn.Invoke();

        current = Instantiate(prefabs[index]);

        current.transform.position = position;

        current.transform.rotation = rotation;

        current.transform.parent = parent;

        return current;
    }

    /// <summary>
    /// Spawns the object at the given index (does not shift the index).
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public GameObject Spawn(int index)
    {
        Vector3 position = transform.position;

        Quaternion rotation = transform.rotation;

        Transform parent = transform.parent;

        if (replacePreviousTransform && current != null)
        {
            position = current.transform.position;

            rotation = current.transform.rotation;

            parent = current.transform.parent;
        }

        if (exclusiveSpawn && current != null)
        {
            onDestroy.Invoke();

            Destroy(current);
        }

        onSpawn.Invoke();

        current = Instantiate(prefabs[index]);

        current.transform.position = position;

        current.transform.rotation = rotation;

        current.transform.parent = parent;

        return current;
    }


    // SHIFT FUNCTIONS

    /// <summary>
    /// Shifts the index left by the given number.
    /// </summary>
    /// <param name="shifts"></param>
    /// <returns></returns>
    public int ShiftLeft(int shifts = 1)
    {
        for (int i = 0; i < shifts; i++)
        {
            onShiftLeft.Invoke();

            onShift.Invoke();
        }

        index -= shifts;

        while (index < 0)
        {
            index = prefabs.Count - index;
        }

        return index;
    }

    /// <summary>
    /// Shifts the index right by the given number.
    /// </summary>
    /// <param name="shifts"></param>
    /// <returns></returns>
    public int ShiftRight(int shifts = 1)
    {
        for (int i = 0; i < shifts; i++)
        {
            onShiftRight.Invoke();

            onShift.Invoke();
        }

        index += shifts;

        while (index >= prefabs.Count)
        {
            index -= prefabs.Count;
        }

        return index;
    }


    // SPAWN AND SHIFT FUNCTIONS

    /// <summary>
    /// Shifts the index left by the given number and spawns the current prefab.
    /// </summary>
    /// <param name="shifts"></param>
    /// <returns></returns>
    public GameObject ShiftLeftAndSpawn(int shifts = 1)
    {
        ShiftLeft(shifts);

        return Spawn();
    }

    /// <summary>
    /// Shifts the index right by the given number and spawns the current prefab.
    /// </summary>
    /// <param name="shifts"></param>
    /// <returns></returns>
    public GameObject ShiftRightAndSpawn(int shifts = 1)
    {
        ShiftRight(shifts);

        return Spawn();
    }


    // RANDOM FUNCTIONS

    /// <summary>
    /// Spawns a random prefab.
    /// </summary>
    /// <returns></returns>
    public GameObject SpawnRandom()
    {
        Vector3 position = transform.position;

        Quaternion rotation = transform.rotation;

        Transform parent = transform.parent;

        if (replacePreviousTransform && current != null)
        {
            position = current.transform.position;

            rotation = current.transform.rotation;

            parent = current.transform.parent;
        }

        if (exclusiveSpawn && current != null)
        {
            onDestroy.Invoke();

            Destroy(current);
        }

        onSpawn.Invoke();

        current = Instantiate(prefabs[Random.Range(0, prefabs.Count - 1)]);

        current.transform.position = position;

        current.transform.rotation = rotation;

        current.transform.parent = parent;

        return current;
    }

    /// <summary>
    /// Shifts the index a random amount.
    /// </summary>
    /// <returns></returns>
    public int ShiftRandom()
    {
        onShift.Invoke();

        index = Random.Range(0, prefabs.Count - 1);

        return index;
    }

    /// <summary>
    /// Shifts the index a random and spawns.
    /// </summary>
    /// <returns></returns>
    public GameObject ShiftRandomAndSpawn()
    {
        ShiftRandom();

        return Spawn();
    }


    // MISC FUNCTIONS

    /// <summary>
    /// Removes the prefab at the given index.
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    public GameObject RemovePrefab(int index = 0)
    {
        if (this.index >= index)
        {
            this.index--;
        }

        GameObject prefab = prefabs[index];

        prefabs.RemoveAt(index);

        return prefab;
    }

    /// <summary>
    /// Sets whether one object can spawn at a time.
    /// </summary>
    /// <param name="oneAtATime"></param>
    /// <returns></returns>
    public bool SetExclusiveSpawn(bool oneAtATime)
    {
        this.exclusiveSpawn = oneAtATime;

        return oneAtATime;
    }

    /// <summary>
    /// Toggles whether one object can spawn at a time.
    /// </summary>
    /// <param name="oneAtATime"></param>
    /// <returns></returns>
    public bool ToggleExclusiveSpawn()
    {
        exclusiveSpawn = !exclusiveSpawn;

        return exclusiveSpawn;
    }

    /// <summary>
    /// Spawns all of the prefabs at once (does not delete any).
    /// </summary>
    /// <returns></returns>
    public List<GameObject> SpawnAll()
    {
        List<GameObject> list = new List<GameObject>();

        foreach (GameObject current in prefabs)
        {
            onSpawn.Invoke();

            GameObject spawned = Instantiate(current);

            spawned.transform.position = transform.position;

            spawned.transform.rotation = transform.rotation;

            spawned.transform.parent = transform.parent;

            list.Add(spawned);
        }

        return list;
    }

    /// <summary>
    /// Destroys the current object.
    /// </summary>
    /// <returns></returns>
    public void DestroyCurrent()
    {
        onDestroy.Invoke();

        Destroy(current);
    }
}
