
// Hairy Slice Visualizer Script
// by Kyle Furey for NASA VR Project

// REQUIREMENTS: Flow Files, HairySlice.cs, ClippingPlane.cs, RaygunVR.cs

using System.Collections.Generic;
using UnityEngine;
using TMPro;
using static IMEF;

/// <summary>
/// Allows easy visualization of hairy slice hairs based on input from a clipping plane.
/// </summary>
public class HairySliceVisualizer : MonoBehaviour, IRaygunShootable
{
    [Header("Allows easy visualization of hairy slice hairs based on input from a clipping plane.")]

    [Header("\nCONFIGURATION")]

    [Header("Reference to the hairy slice:")]
    [SerializeField] private HairySlice slice = null;

    [Header("Reference to the clipping plane:")]
    [SerializeField] private ClippingPlane plane = null;

    [Header("The prefab used to represent the hit point:")]
    [SerializeField] private GameObject prefab = null;

    [Header("\nCOLOR BAR")]

    [Header("The text (next to the color bar) used to display the information of the current hit point:")]
    [SerializeField] private TextMeshPro colorBarText = null;

    [Header("The height values used to calculate the position of the color bar to show the hit point's color value:")]
    [SerializeField] private float topPosition = 4;
    [SerializeField] private float bottomPosition = -5;

    /// <summary>
    /// The current active hairs.
    /// </summary>
    private List<GameObject> currentHairs = new List<GameObject>();

    /// <summary>
    /// The last recorded depth value of the visualization.
    /// </summary>
    private float lastDepthValue = 0;

    /// <summary>
    /// The last recorded axis of the visualization.
    /// </summary>
    private ParticleVisibility.Axis lastAxis = 0;

    /// <summary>
    /// The last recorded flow file of the visualization.
    /// </summary>
    private FlowFile lastFile = null;

    /// <summary>
    /// The game object representing the hit point.
    /// </summary>
    private GameObject hitPoint = null;

    /// <summary>
    /// Hides the clipping plane of the hairy slice.
    /// </summary>
    public void HideAxis()
    {
        foreach (GameObject currentHair in currentHairs)
        {
            currentHair.active = false;
        }

        currentHairs.Clear();
    }

    /// <summary>
    /// Unhides the clipping plane of the hairy slice.
    /// </summary>
    public void DisplayAxis()
    {
        if ((int)lastDepthValue == (int)plane.depth && lastAxis == plane.axis && lastFile == plane.particleVisibility.flowFile)
        {
            return;
        }

        lastDepthValue = plane.depth;

        lastAxis = plane.axis;

        lastFile = plane.particleVisibility.flowFile;

        HideAxis();

        int xCount = 0;

        int yCount = 0;

        int depth = 0;

        switch (plane.axis)
        {
            case ParticleVisibility.Axis.X:

                xCount = slice.hairCount.x;

                yCount = slice.hairCount.z;

                depth = (int)((plane.depth / ParticleVisibility.particleScale) * slice.hairCount.y);

                break;

            case ParticleVisibility.Axis.Y:

                xCount = slice.hairCount.x;

                yCount = slice.hairCount.y;

                depth = (int)((plane.depth / ParticleVisibility.particleScale) * slice.hairCount.z);

                break;

            case ParticleVisibility.Axis.Z:

                xCount = slice.hairCount.z;

                yCount = slice.hairCount.y;

                depth = (int)((plane.depth / ParticleVisibility.particleScale) * slice.hairCount.x);

                break;
        }

        for (int y = 0; y < yCount; y++)
        {
            for (int x = 0; x < xCount; x++)
            {
                Vector3Int vector = Vector3Int.zero;

                switch (plane.axis)
                {
                    case ParticleVisibility.Axis.X:

                        vector = new Vector3Int(x, depth, y);

                        break;

                    case ParticleVisibility.Axis.Y:

                        vector = new Vector3Int(x, y, depth);

                        break;

                    case ParticleVisibility.Axis.Z:

                        vector = new Vector3Int(depth, y, x);

                        break;
                }

                int index = slice.GetIndex(vector.x, vector.y, vector.z);

                if (index < slice.hairs.Length && index >= 0)
                {
                    slice.hairs[index].active = true;

                    currentHairs.Add(slice.hairs[index]);
                }
            }
        }

        RecalculateHit();
    }

    /// <summary>
    /// IRaygunShootable - Shows the hairy slice based on the current hit point. Hit point is calculated based on a plane primitive.
    /// </summary>
    /// <param name="hit"></param>
    public void OnRaygunHit(RaycastHit hit)
    {
        HideAxis();

        if (hitPoint != null)
        {
            Destroy(hitPoint);
        }

        hitPoint = Instantiate(prefab);

        hitPoint.transform.position = hit.point;

        hitPoint.transform.parent = hit.transform;

        Vector2 coordinate = new Vector2
        (
            plane.axis != ParticleVisibility.Axis.Z ? 1 - (hitPoint.transform.localPosition.x + 0.5f) : hitPoint.transform.localPosition.x + 0.5f,
            plane.axis == ParticleVisibility.Axis.X ? 1 - (hitPoint.transform.localPosition.z + 0.5f) : hitPoint.transform.localPosition.z + 0.5f
        );

        Vector3Int vector = plane.GetNearestCoordinate(coordinate, slice.hairCount);

        coordinate = new Vector2
        (
            hitPoint.transform.localPosition.x + 0.5f,
            1 - (hitPoint.transform.localPosition.z + 0.5f)
        );

        Vector3 sample = plane.GetNearestCoordinate(coordinate);

        Material material = hitPoint.GetComponent<Renderer>().material;

        if (colorBarText != null)
        {
            switch (plane.calculation)
            {
                case ClippingPlane.MapType.Velocity:

                    sample = plane.particleVisibility.flowFile.Sample(sample);

                    break;

                case ClippingPlane.MapType.Density:

                    sample = GetDensity(plane.particleVisibility.flowFile.Sample(sample));

                    break;

                case ClippingPlane.MapType.MagneticField:

                    sample = BDipole(plane.particleVisibility.flowFile.Sample(sample)).normalized;

                    break;
            }

            colorBarText.text = "{ " + sample.x.ToString("F1") + ", " + sample.y.ToString("F1") + ", " + sample.z.ToString("F1") + " }";

            sample = sample.normalized;

            sample.x = Mathf.Abs(sample.x);

            sample.y = Mathf.Abs(sample.y);

            sample.z = Mathf.Abs(sample.z);

            colorBarText.outlineColor = new Color(sample.x, sample.y, sample.z, 1);

            Color newColor = new Color(sample.x, sample.y, sample.z, 1);

            float percentage;

            float empty;

            Color.RGBToHSV(newColor, out percentage, out empty, out empty);

            colorBarText.transform.position = new Vector3(
            colorBarText.transform.position.x,
            colorBarText.transform.parent.transform.position.y + (bottomPosition + (topPosition - bottomPosition) * (1 - percentage)),
            colorBarText.transform.position.z);

            material.SetColor("_BaseColor", newColor);

            material.SetColor("_EmissionColor", newColor);
        }

        int index = slice.GetIndex(vector.x, vector.y, vector.z);

        if (index < slice.hairs.Length && index >= 0)
        {
            slice.hairs[index].active = true;

            currentHairs.Add(slice.hairs[index]);
        }
    }

    /// <summary>
    /// Recalculates the current hit point.
    /// </summary>
    public void RecalculateHit()
    {
        if (hitPoint == null)
        {
            return;
        }

        Vector2 coordinate = new Vector2
        (
            plane.axis != ParticleVisibility.Axis.Z ? 1 - (hitPoint.transform.localPosition.x + 0.5f) : hitPoint.transform.localPosition.x + 0.5f,
            plane.axis == ParticleVisibility.Axis.X ? 1 - (hitPoint.transform.localPosition.z + 0.5f) : hitPoint.transform.localPosition.z + 0.5f
        );

        Vector3Int vector = plane.GetNearestCoordinate(coordinate, slice.hairCount);

        coordinate = new Vector2
        (
            hitPoint.transform.localPosition.x + 0.5f,
            1 - (hitPoint.transform.localPosition.z + 0.5f)
        );

        Vector3 sample = plane.GetNearestCoordinate(coordinate);

        Material material = hitPoint.GetComponent<Renderer>().material;

        if (colorBarText != null)
        {
            switch (plane.calculation)
            {
                case ClippingPlane.MapType.Velocity:

                    sample = plane.particleVisibility.flowFile.Sample(sample);

                    break;

                case ClippingPlane.MapType.Density:

                    sample = GetDensity(plane.particleVisibility.flowFile.Sample(sample));

                    break;

                case ClippingPlane.MapType.MagneticField:

                    sample = BDipole(plane.particleVisibility.flowFile.Sample(sample)).normalized;

                    break;
            }

            colorBarText.text = "{ " + sample.x.ToString("F1") + ", " + sample.y.ToString("F1") + ", " + sample.z.ToString("F1") + " }";

            sample = sample.normalized;

            sample.x = Mathf.Abs(sample.x);

            sample.y = Mathf.Abs(sample.y);

            sample.z = Mathf.Abs(sample.z);

            colorBarText.outlineColor = new Color(sample.x, sample.y, sample.z, 1);

            Color newColor = new Color(sample.x, sample.y, sample.z, 1);

            float percentage;

            float empty;

            Color.RGBToHSV(newColor, out percentage, out empty, out empty);

            colorBarText.transform.position = new Vector3(
            colorBarText.transform.position.x,
            colorBarText.transform.parent.transform.position.y + (bottomPosition + (topPosition - bottomPosition) * (1 - percentage)),
            colorBarText.transform.position.z);

            material.SetColor("_BaseColor", newColor);

            material.SetColor("_EmissionColor", newColor);
        }

        int index = slice.GetIndex(vector.x, vector.y, vector.z);

        if (index < slice.hairs.Length && index >= 0)
        {
            slice.hairs[index].active = true;

            currentHairs.Add(slice.hairs[index]);
        }
    }

    /// <summary>
    /// mu0 mathematical constant
    /// </summary>
    public const double mu0 = 1.25663706 * 10e-6;

    /// <summary>
    /// Calculates the magnetic density
    /// </summary>
    /// <param name="position"></param>
    /// <returns></returns>
    public Vector3 GetDensity(Vector3 position)
    {
        Vector3 J;

        float x = position.x;
        float y = position.y;
        float z = position.z;

        /*
        DENSITY EQUATION

        The current density, J, can be calculated from the magnetic field, B.

        •	We know Bi = (Bxi, Byi, Bzi) at point xi = (xi, yi, zi), where i is a grid cell.

        •	The current density Ji = (Jxi, Jyi, Jzi) at cell i can be calculated as:

        •	mu0 = 1.25663706 × 10-6

        •	Jxi = 1e-6 * mu0 * { [Bz(i+1) - Bz(i-1)] / [y(i+1) - y(i-1)] - [By(i+1) - By(i-1)] / [z(i+1) - z(i-1)] }

        •	Jyi = 1e-6 * mu0 * { [Bx(i+1) - Bx(i-1)] / [z(i+1) - z(i-1)] - [Bz(i+1) - Bz(i-1)] / [x(i+1) - x(i-1)] }

        •	Jzi = 1e-6 * mu0 * { [By(i+1) - By(i-1)] / [x(i+1) - x(i-1)] - [Bx(i+1) - Bx(i-1)] / [y(i+1) - y(i-1)] }
        */

        J.x = (float)
              (1e-6 / mu0 * (plane.particleVisibility.flowFile.Sample(new Vector3(x + 1, y + 1, z + 1)).z - plane.particleVisibility.flowFile.Sample(new Vector3(x - 1, y - 1, z - 1)).z)
              /
              ((new Vector3(x + 1, y + 1, z + 1).y - new Vector3(x - 1, y - 1, z - 1).y))
              -
              (plane.particleVisibility.flowFile.Sample(new Vector3(x + 1, y + 1, z + 1)).y - plane.particleVisibility.flowFile.Sample(new Vector3(x - 1, y - 1, z - 1)).y)
              /
              ((new Vector3(x + 1, y + 1, z + 1).z - new Vector3(x - 1, y - 1, z - 1).z)));

        J.y = (float)
              (1e-6 / mu0 * (plane.particleVisibility.flowFile.Sample(new Vector3(x + 1, y + 1, z + 1)).x - plane.particleVisibility.flowFile.Sample(new Vector3(x - 1, y - 1, z - 1)).x)
              /
              ((new Vector3(x + 1, y + 1, z + 1).z - new Vector3(x - 1, y - 1, z - 1).z))
              -
              (plane.particleVisibility.flowFile.Sample(new Vector3(x + 1, y + 1, z + 1)).z - plane.particleVisibility.flowFile.Sample(new Vector3(x - 1, y - 1, z - 1)).z)
              /
              ((new Vector3(x + 1, y + 1, z + 1).x - new Vector3(x - 1, y - 1, z - 1).x)));

        J.z = (float)
              (1e-6 / mu0 * (plane.particleVisibility.flowFile.Sample(new Vector3(x + 1, y + 1, z + 1)).y - plane.particleVisibility.flowFile.Sample(new Vector3(x - 1, y - 1, z - 1)).y)
              /
              ((new Vector3(x + 1, y + 1, z + 1).x - new Vector3(x - 1, y - 1, z - 1).x))
              -
              (plane.particleVisibility.flowFile.Sample(new Vector3(x + 1, y + 1, z + 1)).x - plane.particleVisibility.flowFile.Sample(new Vector3(x - 1, y - 1, z - 1)).x)
              /
              ((new Vector3(x + 1, y + 1, z + 1).y - new Vector3(x - 1, y - 1, z - 1).y)));

        return J;
    }
}
