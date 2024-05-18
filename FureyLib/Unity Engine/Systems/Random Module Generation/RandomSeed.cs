
// Random Seed Generator Script
// by Kyle Furey

using UnityEngine;
using UnityEngine.Events;

/// <summary>
/// Generates a random seed used for random generation.
/// </summary>
public class RandomSeed : MonoBehaviour
{
    [Header("Generates a random seed used for random generation.")]

    [Header("The deterministic seed used to generate random numbers:")]
    [SerializeField] private int seed = 0;

    [Header("Whether to randomize the seed on game start:")]
    [SerializeField] private bool randomizeSeed = true;
    [SerializeField] private int seedMinimum = -2147483647;
    [SerializeField] private int seedMaximum = 2147483647;

    [Header("Start functions called after the random seed is generated:")]
    [SerializeField] private UnityEvent StartFunctions;

    /// <summary>
    /// Awake is called when the script is loaded
    /// </summary>
    private void Awake()
    {
        // Set random seed at the start of the game
        if (randomizeSeed)
        {
            Random.InitState(System.Environment.TickCount);
            seed = Random.Range(seedMinimum, seedMaximum);
        }

        // Start the seed's randomization
        Random.InitState(seed);
        print("New Seed: " + seed);

        // Calls each start function after the seed is generated
        StartFunctions.Invoke();
    }
}
