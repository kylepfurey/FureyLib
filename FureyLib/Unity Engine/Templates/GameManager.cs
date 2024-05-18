
// Game Manager Template Script
// by Kyle Furey

using UnityEngine;

/// <summary>
/// A singleton component that allows easy access to other components.
/// </summary>
public class GameManager : MonoBehaviour
{
    [Header("A singleton component that allows easy access to other components.")]

    [Header("\nCONFIGURATION")]

    [Header("Whether to always keep the game manager loaded between scenes:")]
    [SerializeField] private bool dontDestroyOnLoad = true;

    /// <summary>
    /// Reference to the game manager in the scene
    /// </summary>
    [HideInInspector] public static GameManager instance;

    // New variables here


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
    /// Awake is called when the script is loaded
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
