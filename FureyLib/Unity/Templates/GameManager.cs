
// Game Manager Template Script
// by Kyle Furey

using UnityEngine;

// A component that allows easy access to other components through the singleton design pattern.
public class GameManager : MonoBehaviour
{
    [HideInInspector] public static GameManager Instance;

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

    private static Player player;

    private void Awake()
    {
        Instance = this;
    }
}
