
// Game Manager Template Script
// by Kyle Furey

using UnityEngine;

/// <summary>
/// A singleton component that allows easy access to other components.
/// </summary>
public class GameManager : MonoBehaviour
{
    [Header("A singleton component that allows easy access to other components.\n")]

    [Header("Whether to always keep the game manager loaded between scenes:")]
    [SerializeField] private bool dontDestroyOnLoad = true;

    // New variables here


    // PROPERTIES

    /// <summary>
    /// A singleton reference to the game manager.
    /// </summary>
    public static GameManager instance { get; private set; } = null;

    // New properties here


    // FUNCTIONS

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
            Destroy(gameObject);
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
        instance = null;
    }

    // New functions here
}
