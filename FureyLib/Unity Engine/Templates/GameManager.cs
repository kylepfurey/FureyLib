
// Game Manager Template Script
// by Kyle Furey

using UnityEngine;

/// <summary>
/// A singleton component that allows easy access to other components.
/// </summary>
public class GameManager : MonoBehaviour
{
    [Header("A singleton component that allows easy access to other components.")]


    // SETTINGS

    [Header("\nCONFIGURATION")]

    [Header("Whether to always keep the game manager loaded between scenes:")]
    [SerializeField] private bool dontDestroyOnLoad = true;

    // New variables here


    // INSTANCE

    /// <summary>
    /// The current instance of the game manager game object
    /// </summary>
    [HideInInspector] public static GameManager instance;


    // PROPERTIES

    /// <summary>
    /// Reference to the player
    /// </summary>
    public static PlayerClass player
    {
        get
        {
            if (player == null)
            {
                player = FindObjectOfType<PlayerClass>();
            }

            return player;
        }

        set
        {
            player = value;
        }
    }

    // New properties here


    // FUNCTIONS

    /// <summary>
    /// Called before Start when the object is created
    /// </summary>
    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
        }
        else
        {
            DestroyImmediate(this);
        }

        if (dontDestroyOnLoad)
        {
            DontDestroyOnLoad(gameObject);
        }
    }

    // New functions here
}
