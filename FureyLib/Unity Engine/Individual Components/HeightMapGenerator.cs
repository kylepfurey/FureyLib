
// Height Map Generator Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Generates a simple height map using planes and a material.
/// </summary>
public class HeightMapGenerator : MonoBehaviour
{
    [Header("Generates a simple height map using planes and a material.")]

    [Header("\nHEIGHT MAP SETTINGS")]

    [Header("The material to assign to the planes:")]
    [SerializeField] private Material material = null;

    [Header("The number of planes to generate:")]
    [SerializeField] private float count = 10;

    [Header("The maximum height to generate planes from:")]
    [SerializeField] private float height = 10;

    [Header("\nTESTING")]

    [Header("Whether to generate the planes on start:")]
    [SerializeField] private bool generateOnStart = true;

    [Header("Whether to generate the planes live:")]
    [SerializeField] private bool liveTesting = true;

    [Header("Test generation button:")]
    [SerializeField] private bool test = false;

    [Header("Clear generation button:")]
    [SerializeField] private bool clear = false;

    // A list of the generated objects
    private List<GameObject> planes = new List<GameObject>();

    /// <summary>
    /// Allows testing in the editor
    /// </summary>
    private void OnValidate()
    {
        if (liveTesting)
        {
            Invoke("Generate", 0);
        }
        else
        {
            if (test)
            {
                test = false;

                Invoke("Generate", 0);
            }

            if (clear)
            {
                clear = false;

                Invoke("Clear", 0);
            }
        }
    }

    /// <summary>
    /// Generates the planes when the game starts
    /// </summary>
    private void Start()
    {
        if (generateOnStart)
        {
            Generate();
        }
    }

    /// <summary>
    /// Generates and returns the planes representing the height map
    /// </summary>
    /// <returns></returns>
    public List<GameObject> Generate()
    {
        Clear();

        for (int i = 0; i < count; i++)
        {
            GameObject plane = GameObject.CreatePrimitive(PrimitiveType.Plane);

            plane.name = "Generated Plane " + i + 1;

            plane.transform.parent = transform;

            plane.transform.localPosition = transform.localPosition + new Vector3(0, i * (height / count), 0);

            plane.transform.localEulerAngles = Vector3.zero;

            plane.transform.localScale = Vector3.one;

            if (material != null)
            {
                plane.GetComponent<Renderer>().material = material;
            }

            planes.Add(plane);
        }

        return planes;
    }

    /// <summary>
    /// Clears all generated planes and returns the total cleared planes
    /// </summary>
    /// <returns></returns>
    public int Clear()
    {
        int count = planes.Count;

        for (int i = 0; i < planes.Count; i++)
        {
            DestroyImmediate(planes[i]);
        }

        planes.Clear();

        return count;
    }
}
