// .cs
// Awaitable Unity Async Functions
// by Kyle Furey

#nullable enable
using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading.Tasks;
using UnityEngine;

/// <summary>
/// A component that tracks Unity ticks for async code.
/// </summary>
public class UnityAsync : MonoBehaviour
{
    // VARIABLES

    /// <summary>
    /// The number of Update() calls since this component was created.
    /// </summary>
    private ulong updateCount = 0;

    /// <summary>
    /// The number of FixedUpdate() calls since this component was created.
    /// </summary>
    private ulong fixedUpdateCount = 0;

    /// <summary>
    /// The number of LateUpdate() calls since this component was created.
    /// </summary>
    private ulong lateUpdateCount = 0;


    // PROPERTIES

    /// <summary>
    /// Singleton reference to the UnityAsync component.
    /// </summary>
    public static UnityAsync instance { get; private set; } = null!;


    // EVENTS

    /// <summary>
    /// Initializes the singleton component.
    /// </summary>
    private void Awake()
    {
        if (!instance)
        {
            instance = this;
        }
        else
        {
            Debug.LogError("SINGLETON ERROR: A UnityAsync component already exists on " +
                instance.gameObject.name +
                "!");
            Destroy(this);
            return;
        }
    }

    /// <summary>
    /// Tracks each Unity Update() call.
    /// </summary>
    private void Update()
    {
        ++updateCount;
    }

    /// <summary>
    /// Tracks each Unity FixedUpdate() call.
    /// </summary>
    private void FixedUpdate()
    {
        ++fixedUpdateCount;
    }

    /// <summary>
    /// Tracks each Unity LateUpdate() call.
    /// </summary>
    private void LateUpdate()
    {
        ++lateUpdateCount;
    }

    /// <summary>
    /// Cleans up the singleton component.
    /// </summary>
    private void OnDestroy()
    {
        if (instance == this)
            instance = null!;
    }


    // METHODS

    /// <summary>
    /// Awaits the next Unity Update() call.
    /// </summary>
    public static async Task NextUpdate(uint numberOfFrames = 1)
    {
        if (!instance)
            return;

        ulong next = instance.updateCount + numberOfFrames;
        while (instance && instance.updateCount < next)
            await Task.Yield();
    }

    /// <summary>
    /// Awaits the next Unity FixedUpdate() call.
    /// </summary>
    public static async Task NextFixedUpdate(uint numberOfFrames = 1)
    {
        if (!instance)
        {
            Debug.LogError("ASYNC ERROR: UnityAsync was null!");
            return;
        }

        ulong next = instance.fixedUpdateCount + numberOfFrames;
        while (instance && instance.fixedUpdateCount < next)
            await Task.Yield();
    }

    /// <summary>
    /// Awaits the next Unity LateUpdate() call.
    /// </summary>
    public static async Task NextLateUpdate(uint numberOfFrames = 1)
    {
        if (!instance)
        {
            Debug.LogError("ASYNC ERROR: UnityAsync was null!");
            return;
        }

        ulong next = instance.lateUpdateCount + numberOfFrames;
        while (instance && instance.lateUpdateCount < next)
            await Task.Yield();
    }
}
