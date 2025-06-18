// .cs
// Game Manager Component Script
// by Kyle Furey

using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// A singleton component that allows easy access to other components.
/// </summary>
public class GameManager : MonoBehaviour
{
	// VARIABLES

    /// <summary>
    /// Whether this component's game object should persist through scene changes.
    /// </summary>
    [SerializeField]
    private bool dontDestroyOnLoad = true;


    // PROPERTIES

    /// <summary>
    /// A singleton reference to the game manager.
    /// </summary>
    public static GameManager instance { get; private set; } = null;


    // EVENTS

    /// <summary>
    /// Sets this object as the current game manager.
    /// </summary>
    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
        }
        else
        {
            Destroy(this);
        }

        if (dontDestroyOnLoad)
        {
            DontDestroyOnLoad(gameObject);
        }
    }

    /// <summary>
    /// Removes this object as the current game manager.
    /// </summary>
    private void OnDestroy()
    {
        if (instance == this)
        {
            instance = null;
        }
    }
}
