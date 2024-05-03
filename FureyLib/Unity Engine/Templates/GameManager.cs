
// Game Manager Template Script
// by Kyle Furey

using UnityEngine;

/// <summary>
/// A component that allows easy access to other components through the singleton design pattern.
/// </summary>
public class GameManager : MonoBehaviour
{
    /// <summary>
    /// The current instance of the game manager game object
    /// </summary>
    [HideInInspector] public static GameManager instance;

    /// <summary>
    /// A reference to the player
    /// </summary>
    [HideInInspector]
    public static Player Player
    {
        get
        {
            if (!player)
            {
                player = FindObjectOfType<Player>();
            }

            return player;
        }
        set
        {
            Player = value;
        }
    }

    /// <summary>
    /// Static reference to the player
    /// </summary>
    private static Player player;

    /// <summary>
    /// Called before Start when the object is created
    /// </summary>
    private void Awake()
    {
        instance = this;
    }
}
