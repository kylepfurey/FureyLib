
// Prefab Spawner Script
// by Kyle Furey

using UnityEngine;

// Spawns an object after a set number of time at this object's position and rotation.
public class Spawner : MonoBehaviour
{
    [Header("Spawns an object after a set number of time at this object's position and rotation.")]

    [Header("The spawned prefab:")]
    [SerializeField] private GameObject spawnedPrefab = null;

    [Header("The delayed time in seconds before spawning the prefab:")]
    [SerializeField] private float spawnTime = 0;

    [Header("The spawned prefab's offset position:")]
    [SerializeField] private Vector3 offsetPosition = new Vector3(0, 0, 0);

    [Header("The spawned prefab's offset rotation:")]
    [SerializeField] private Vector3 offsetRotation = new Vector3(0, 0, 0);

    [Header("The spawned prefab's scale:")]
    [SerializeField] private Vector3 scale = new Vector3(1, 1, 1);

    private void Start()
    {
        Invoke("Spawn", spawnTime);
    }

    private void Spawn()
    {
        GameObject spawn = Instantiate(spawnedPrefab);
        
        spawn.transform.position = transform.position + offsetPosition;

        spawn.transform.eulerAngles = transform.eulerAngles + offsetRotation;

        spawn.transform.localScale = scale;

        Destroy(gameObject);
    }
}
