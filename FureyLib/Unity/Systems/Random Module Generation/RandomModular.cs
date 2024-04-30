
// Randomly Generated Modules Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;

// Generates different sets of random modules based on set criteria.
public class RandomModular : MonoBehaviour
{
    [Header("Generates a set of random modules based on set criteria.")]

    [Header("All possible modules to be used in sets for spawning:")]
    [SerializeField] private List<Module> allModules = new List<Module>();

    [Header("All sets and their spawned modules:")]
    [SerializeField] private List<SetOfModules> sets = new List<SetOfModules>();

    [Header("Click the checkbox to reroll the spawned modules:")]
    [SerializeField] private bool testSpawns = false;

    // All currently spawned modules
    private Dictionary<SetOfModules, List<GameObject>> allSpawnedModules = new Dictionary<SetOfModules, List<GameObject>>();

    // Spawns modules for a specific set
    public void SpawnSet(string setName)
    {
        // Despawn the modules of the current set (if applicable)
        DespawnSet(setName);

        // Find the set from the given name
        foreach (SetOfModules set in sets)
        {
            if (set.name == setName)
            {
                // Spawn that set's modules
                Spawn(set);
                break;
            }
        }
    }

    // Spawns modules for all sets
    public void SpawnAll()
    {
        // Despawn all modules of each set (if applicable)
        DespawnAll();

        // Find each set and delete its modules
        foreach (SetOfModules set in sets)
        {
            Spawn(set);
        }
    }

    // Destroys all spawned modules of a given set
    public void DespawnSet(string setName)
    {
        // Find the set from the given name
        foreach (SetOfModules set in sets)
        {
            if (set.name == setName)
            {
                // Delete each module
                for (int i = 0; i < allSpawnedModules[set].Count; i++)
                {
                    Destroy(allSpawnedModules[set][i]);
                }

                // Remove the modules from the list of spawned modules
                allSpawnedModules.Remove(set);

                break;
            }
        }
    }

    // Destroys all spawned modules of each set
    public void DespawnAll()
    {
        // Find each set and delete its modules
        foreach (SetOfModules set in sets)
        {
            if (allSpawnedModules.ContainsKey(set))
            {
                for (int i = 0; i < allSpawnedModules[set].Count; i++)
                {
                    Destroy(allSpawnedModules[set][i]);
                }
            }
        }

        // Clear the list of spawned modules
        allSpawnedModules.Clear();
    }

    // Spawns modules at random depending on their spawn rates from a given set
    private void Spawn(SetOfModules set)
    {
        // Initalize our spawned modules list
        allSpawnedModules[set] = new List<GameObject>();

        // All possible modules that may be spawned and their spawn rates
        List<Module> spawnTable = new List<Module>();
        Dictionary<Module, float> spawnRates = new Dictionary<Module, float>();

        // All spawn points that may spawn a module
        Queue<GameObject> spawnPoints = new Queue<GameObject>();

        // All modules that have been spawned
        List<Module> spawnedModules = new List<Module>();

        // Initalize the spawn table
        if (!set.useAllModules)
        {
            // Add the set's modules to the spawn table
            foreach (Module module in allModules)
            {
                if (set.setModules.Contains(module.name))
                {
                    spawnTable.Add(module);
                    spawnRates[module] = module.spawnRate;
                }
            }
        }
        else
        {
            // Copy all modules to the spawn table
            foreach (Module module in allModules)
            {
                spawnTable.Add(module);
                spawnRates[module] = module.spawnRate;
            }
        }

        // Store spawn points
        foreach (GameObject spawnPoint in set.spawnPoints)
        {
            spawnPoints.Enqueue(spawnPoint);
        }

        // Spawn modules until no spawn points or modules remain
        while (spawnTable.Count > 0 && spawnPoints.Count > 0)
        {
            // Track the spawn rate of each current module
            float spawnPercent = 0;
            Dictionary<Module, float> spawnPercents = new Dictionary<Module, float>();

            // Set the spawn rate of each module
            for (int i = 0; i < spawnTable.Count; i++)
            {
                // Remove modules that cannot spawn
                if (spawnRates[spawnTable[i]] <= 0 || spawnTable[i].numberOfSpawns <= FindAll(spawnedModules, spawnTable[i]))
                {
                    spawnTable.Remove(spawnTable[i]);
                    continue;
                }

                // Increase the total spawn rate to gauge a percentage of each of the modules relative to each other
                spawnPercent += spawnTable[i].spawnRate;
                spawnPercents[spawnTable[i]] = spawnPercent;
            }

            // Pick a module to spawn
            spawnPercent = Random.Range(0, spawnPercent);

            // Find the spawned module
            foreach (Module module in spawnPercents.Keys)
            {
                if (spawnPercent < spawnPercents[module])
                {
                    // Dequeue our next spawn point
                    GameObject spawnPoint = spawnPoints.Dequeue();

                    // Spawn the module and sets its transform values
                    GameObject spawnedModule = Instantiate(module.prefab);
                    spawnedModule.name = module.name;
                    spawnedModule.transform.position = spawnPoint.transform.position + module.spawnPositionOffset;
                    spawnedModule.transform.eulerAngles = spawnPoint.transform.eulerAngles + module.spawnRotationOffset;
                    spawnedModule.transform.localScale = module.spawnScale;

                    // Randomize transform values if applicable
                    if (module.randomizeTransform)
                    {
                        spawnedModule.transform.position += new Vector3(Random.Range(module.spawnPositionOffsetMinimum.x, module.spawnPositionOffsetMaximum.x), Random.Range(module.spawnPositionOffsetMinimum.y, module.spawnPositionOffsetMaximum.y), Random.Range(module.spawnPositionOffsetMinimum.z, module.spawnPositionOffsetMaximum.z));
                        spawnedModule.transform.eulerAngles += new Vector3(Random.Range(module.spawnRotationOffsetMinimum.x, module.spawnRotationOffsetMaximum.x), Random.Range(module.spawnRotationOffsetMinimum.y, module.spawnRotationOffsetMaximum.y), Random.Range(module.spawnRotationOffsetMinimum.z, module.spawnRotationOffsetMaximum.z));
                        spawnedModule.transform.localScale += new Vector3(Random.Range(module.spawnScaleMinimum.x, module.spawnScaleMaximum.x), Random.Range(module.spawnScaleMinimum.y, module.spawnScaleMaximum.y), Random.Range(module.spawnScaleMinimum.z, module.spawnScaleMaximum.z));
                    }

                    // Add our spawned module to our list of spawned modules
                    spawnedModules.Add(module);
                    allSpawnedModules[set].Add(spawnedModule);

                    // Update the spawn rates of the spawn table
                    for (int i = 0; i < spawnTable.Count; i++)
                    {
                        // Check if this spawned module is in each other module's exclusive modules
                        foreach (ExclusiveModule exclusiveModule in spawnTable[i].exclusiveModules)
                        {
                            if (exclusiveModule.exclusiveModuleName == module.name)
                            {
                                // Update the spawn rate for that module
                                spawnRates[spawnTable[i]] += exclusiveModule.spawnModifier;
                            }

                            break;
                        }
                    }

                    // Hide the spawn point's game object
                    MeshRenderer[] meshRenderers = spawnPoint.GetComponentsInChildren<MeshRenderer>(true);

                    for (int i = 0; i < meshRenderers.Length; i++)
                    {
                        meshRenderers[i].enabled = false;
                    }

                    break;
                }
            }
        }
    }

    // Returns a count of specific elements in a list
    private static int FindAll<DataType>(List<DataType> list, DataType element)
    {
        int count = 0;

        foreach (DataType listElement in list)
        {
            if (listElement.Equals(element))
            {
                count++;
            }
        }

        return count;
    }

    // Test spawning
    private void OnValidate()
    {
        // Generate spawns 
        if (testSpawns)
        {
            // Disable button
            testSpawns = false;

            // No spawning unless in play mode!
            if (Application.isPlaying)
            {
                SpawnAll();
            }
            else
            {
                Debug.LogWarning("No spawning unless in play mode!");
            }
        }
    }
}

// A module that may be spawned by the random modular class.
[System.Serializable]
public class Module
{
    [Header("NAME AND PREFAB")]

    [Header("The referenced name of this module:")]
    public string name = "New Module";
    // NOTE FROM DEVELOPER: You cannot serialize a class both by value and by reference in Unity without custom editor code, so I had to use a naming system to reference each module

    [Header("The prefab to be generated:")]
    public GameObject prefab;


    [Header("\nSPAWN CRITERIA")]

    [Header("The likeliness that this module will spawn relative to other modules:")]
    public float spawnRate = 1;

    [Header("Modules that will affect this module's spawn rate when present in a set:")]
    public List<ExclusiveModule> exclusiveModules = new List<ExclusiveModule>();

    [Header("The total number of spawns of this module that can be present in a set:")]
    public int numberOfSpawns = 1;


    [Header("\nTRANSFORM SETTINGS")]

    [Header("Adds the given position and rotation to the prefab after it spawns at the spawn point:")]
    public Vector3 spawnPositionOffset = Vector3.zero;
    public Vector3 spawnRotationOffset = Vector3.zero;

    [Header("Sets the given scale of the prefab after it spawns:")]
    public Vector3 spawnScale = Vector3.one;


    [Header("\nRANDOMIZATION SETTINGS")]

    [Header("Randomize transform values between the minimum and maximum values to be added after the offset:")]
    public bool randomizeTransform = false;
    public Vector3 spawnPositionOffsetMinimum = Vector3.zero;
    public Vector3 spawnPositionOffsetMaximum = Vector3.zero;
    public Vector3 spawnRotationOffsetMinimum = Vector3.zero;
    public Vector3 spawnRotationOffsetMaximum = Vector3.zero;
    public Vector3 spawnScaleMinimum = Vector3.one;
    public Vector3 spawnScaleMaximum = Vector3.one;
}

// A module that will affect another module's chances of spawning.
[System.Serializable]
public class ExclusiveModule
{
    [Header("The referenced name of the module that will affect the parent module's spawn rate:")]
    public string exclusiveModuleName;
    // NOTE FROM DEVELOPER: You cannot serialize a class both by value and by reference in Unity without custom editor code, so I had to use a naming system to reference each module

    [Header("The spawn rate value that will be added to the parent module's spawn rate if the above module is present in the set:")]
    public float spawnModifier = 0;

    [Header("A brief explanation about why the above module is affecting the parent module's spawn rate:")]
    [SerializeField] private string description = "New Module Behavior";
}

// A set of modules that can be spawned to specific spawn points depending on each module's spawn rate.
[System.Serializable]
public class SetOfModules
{
    [Header("The referenced name of this set:")]
    public string name = "New Set";

    [Header("Locations to spawn modules:")]
    public List<GameObject> spawnPoints = new List<GameObject>();

    [Header("Whether to use all possible modules for spawning in this set:")]
    public bool useAllModules = true;

    [Header("The referenced name of the modules that can be spawned in this set:")]
    public List<string> setModules = new List<string>();
    // NOTE FROM DEVELOPER: You cannot serialize a class both by value and by reference in Unity without custom editor code, so I had to use a naming system to reference each module
}
