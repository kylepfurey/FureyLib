
// Axis Orbiter Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Emulates an orbit on an axis.
/// </summary>
public class Orbiter : MonoBehaviour
{
    [Header("Emulates an orbit on an axis.")]

    [Header("The axis and local speed to orbit around:")]
    public OrbitAxis axis = OrbitAxis.Y;
    public float localSpeed = 1;

    [Header("The parent object to represent the center object:")]
    public GameObject centerObject = null;

    [Header("The child objects to represent the orbiting object:")]
    public List<GameObject> orbitingObjects = new List<GameObject>();

    [Header("The base speed to spin this object (the closer it is, the faster it will spin):")]
    public float orbitSpeed = 5000;
    public Vector2 orbitDistance = new Vector2(0.1f, 0.5f);

    [Header("The speed and height of the orbiting object's levitation:")]
    public float levitateSpeed = 1;
    public float levitateHeight = 0.9f;

    [Header("Whether to orbit closer or further from the center based on levitate height:")]
    public bool useDistance = true;

    /// <summary>
    /// The timer used for the levitating sin wave.
    /// </summary>
    private float timer = 0;

    /// <summary>
    /// Orbit axis enum
    /// </summary>
    public enum OrbitAxis { X, Y, Z, };

    /// <summary>
    /// Sets the center and orbiting objects.
    /// </summary>
    private void Awake()
    {
        if (centerObject == null)
        {
            centerObject = gameObject;
        }

        if (orbitingObjects == null || orbitingObjects.Count == 0)
        {
            orbitingObjects = new List<GameObject>(centerObject.transform.childCount);

            for (int i = 0; i < centerObject.transform.childCount; i++)
            {
                orbitingObjects.Add(transform.GetChild(i).gameObject);
            }
        }
    }

    /// <summary>
    /// Spins and orbits the object.
    /// </summary>
    private void Update()
    {
        float delta = Time.deltaTime * localSpeed;

        switch (axis)
        {
            case OrbitAxis.Y:

                foreach (GameObject orbitingObject in orbitingObjects)
                {
                    // Rotates the parent object based on its distance to the center
                    centerObject.transform.Rotate(0, (orbitDistance.y - Mathf.Abs(orbitingObject.transform.localPosition.z)) * orbitSpeed * delta, 0);

                    // Moves the child object up and down
                    orbitingObject.transform.localPosition = new Vector3(orbitingObject.transform.localPosition.x, Mathf.Sin(levitateSpeed * timer) * levitateHeight, orbitingObject.transform.localPosition.z);

                    // Moves the child object forward based on the height
                    if (useDistance)
                    {
                        orbitingObject.transform.localPosition = new Vector3(orbitingObject.transform.localPosition.x, orbitingObject.transform.localPosition.y, Mathf.Max((levitateHeight - Mathf.Abs(orbitingObject.transform.localPosition.y)) * orbitDistance.y, orbitDistance.x));
                    }
                }

                break;

            case OrbitAxis.Z:

                foreach (GameObject orbitingObject in orbitingObjects)
                {
                    // Rotates the parent object based on its distance to the center
                    centerObject.transform.Rotate(0, 0, (orbitDistance.y - Mathf.Abs(orbitingObject.transform.localPosition.y)) * orbitSpeed * delta);

                    // Moves the child object up and down
                    orbitingObject.transform.localPosition = new Vector3(orbitingObject.transform.localPosition.x, orbitingObject.transform.localPosition.y, Mathf.Sin(levitateSpeed * timer) * levitateHeight);

                    // Moves the child object forward based on the height
                    if (useDistance)
                    {
                        orbitingObject.transform.localPosition = new Vector3(Mathf.Max((levitateHeight - Mathf.Abs(orbitingObject.transform.localPosition.z)) * orbitDistance.y, orbitDistance.x), orbitingObject.transform.localPosition.y, orbitingObject.transform.localPosition.z);
                    }
                }

                break;

            case OrbitAxis.X:

                foreach (GameObject orbitingObject in orbitingObjects)
                {
                    // Rotates the parent object based on its distance to the center
                    centerObject.transform.Rotate((orbitDistance.y - Mathf.Abs(orbitingObject.transform.localPosition.x)) * orbitSpeed * delta, 0, 0);

                    // Moves the child object up and down
                    orbitingObject.transform.localPosition = new Vector3(Mathf.Sin(levitateSpeed * timer) * levitateHeight, orbitingObject.transform.localPosition.y, orbitingObject.transform.localPosition.z);

                    // Moves the child object forward based on the height
                    if (useDistance)
                    {
                        orbitingObject.transform.localPosition = new Vector3(orbitingObject.transform.localPosition.x, Mathf.Max((levitateHeight - Mathf.Abs(orbitingObject.transform.localPosition.x)) * orbitDistance.y, orbitDistance.x), orbitingObject.transform.localPosition.z);
                    }
                }

                break;
        }

        // Increments the timer
        timer += delta;
    }
}
