// .cs
// Prefab Spawner Component
// by Kyle Furey

using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

/// <summary>
/// Spawns and destroys prefabs over a set amount of time.
/// </summary>
public class PrefabSpawner : MonoBehaviour
{
    // VARIABLES

    [Header("Each potential prefab to spawn:")]
    public List<GameObject> prefabs = new List<GameObject>();

    [Header("UnityEngine.Randomization:")]
    public float minSpawnTime = 1.0f;
    public float maxSpawnTime = 3.0f;
    public float minDestroyTime = 3.0f;
    public float maxDestroyTime = 5.0f;

    [Header("Called when a prefab is spawned:")]
    public UnityEvent onSpawn = new UnityEvent();


    // EVENTS

    /// <summary>
    /// Begins spawning prefabs.
    /// </summary>
    private IEnumerator Start()
    {
        if (prefabs.Count == 0)
        {
            Debug.LogError("PREFAB ERROR: No prefabs were set on the PrefabSpawner on " +
                gameObject.name +
                " to be randomly spawned!");
            Destroy(this);
            yield break;
        }

        while (true)
        {
            yield return this != null && enabled ? new WaitForSeconds(UnityEngine.Random.Range(minSpawnTime, maxSpawnTime)) : null;
            if (this != null)
            {
                ForceSpawn();
            }
            else
            {
                yield break;
            }
        }
    }

    /// <summary>
    /// Spawns a random prefab.
    /// </summary>
    public GameObject ForceSpawn()
    {
        if (prefabs.Count == 0)
        {
            Debug.LogError("PREFAB ERROR: No prefabs were set on the PrefabSpawner on " +
                gameObject.name +
                " to be randomly spawned!");
            return null;
        }

        GameObject prefab = prefabs[UnityEngine.Random.Range(0, prefabs.Count)];
        if (prefab == null)
        {
            Debug.LogError("PREFAB ERROR: A set prefab on the PrefabSpawner on " +
                gameObject.name +
                " was null!");
            return null;
        }

        GameObject spawned = Instantiate(prefab);
        onSpawn.Invoke();
        float time = UnityEngine.Random.Range(minDestroyTime, maxDestroyTime);
        if (time > 0.0)
        {
            Destroy(spawned, time);
        }
        return spawned;
    }
}
