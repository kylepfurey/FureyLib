
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
    public Material material = null;

    [Header("The number of planes to generate:")]
    public int count = 10;

    [Header("The maximum height to generate planes from:")]
    public float height = 5;

    [Header("\nTESTING")]

    [Header("Whether to generate the planes on start:")]
    [SerializeField] private bool generateOnStart = true;

    [Header("Whether to generate the planes live:")]
    public bool liveTesting = true;

    [Header("Test generation button:")]
    [SerializeField] private bool test = false;

    [Header("Clear generation button:")]
    [SerializeField] private bool clear = false;

    /// <summary>
    /// A list of the generated objects
    /// </summary>
    private List<GameObject> planes = new List<GameObject>();


    // FUNCTIONS

    /// <summary>
    /// Allows testing in the editor
    /// </summary>
    private void OnValidate()
    {
        if (test)
        {
            test = false;

            Invoke("Generate", 0);

            return;
        }

        if (clear)
        {
            clear = false;

            Invoke("Clear", 0);

            return;
        }

        if (liveTesting)
        {
            Invoke("Generate", 0);
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


    // GENERATE AND CLEAR

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

            plane.GetComponent<Collider>().enabled = false;

            plane.name = "Generated Plane " + (i + 1);

            plane.transform.parent = transform;

            if (count > 1)
            {
                plane.transform.localPosition = new Vector3(0, i * (height / (count - 1)), 0);
            }
            else
            {
                plane.transform.localPosition = Vector3.zero;
            }

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
            Destroy(planes[i]);
        }

        planes.Clear();

        return count;
    }


    // SETTERS

    /// <summary>
    /// Sets the material of the height map
    /// </summary>
    public void SetMaterial(Material material)
    {
        this.material = material;
    }

    /// <summary>
    /// Sets the count of the height map
    /// </summary>
    public void SetCount(int count)
    {
        this.count = count;
    }

    /// <summary>
    /// Sets the height of the height map
    /// </summary>
    public void SetHeight(float height)
    {
        this.height = height;
    }
}
