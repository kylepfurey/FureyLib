
// Flow Data Clipping Plane Script
// by Kyle Furey for NASA VR Project

using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Clips and displays a plane of flow data.
/// </summary>
public class ClippingPlane : MonoBehaviour
{
    [Header("Clips and displays a plane of flow data.")]

    [Header("\nCONFIGURATION")]

    [Header("Reference to the flow file:")]
    [SerializeField] private FlowFile flowFile = null;

    [Header("The shader used to represent the slice:")]
    [SerializeField] private Material shader = null;

    [Header("The size of the slice of flow data to clip:")]
    [SerializeField] private Vector2Int size = new Vector2Int(100, 100);

    [Header("The axis of the flow data to clip:")]
    [SerializeField] private PlaneAxis axis = PlaneAxis.XY;

    [Header("The depth of the slice of flow data to clip:")]
    [SerializeField] private float depth = 50;

    /// <summary>
    /// The clipped plane of the flow file's data
    /// </summary>
    private Vector3[,] slice = null;

    /// <summary>
    /// The stored texture that represents the clipped plane
    /// </summary>
    private Texture2D texture = null;

    /// <summary>
    /// Whether the game has started
    /// </summary>
    private bool awake = false;

    /// <summary>
    /// Plane axis enum
    /// </summary>
    public enum PlaneAxis { XZ, XY, ZY };

    /// <summary>
    /// Clamps the depth and tests the clipping plane
    /// </summary>
    private void OnValidate()
    {
        depth = Mathf.Clamp(depth, 0, 100);

        if (awake && flowFile != null && shader != null)
        {
            UpdateSlice();
        }
    }

    /// <summary>
    /// Allows the clipping plane to be tested
    /// </summary>
    private void Awake()
    {
        awake = true;
    }

    /// <summary>
    /// Start() is called before the first frame update
    /// </summary>
    private void Start()
    {
        UpdateSlice();
    }

    /// <summary>
    /// Returns a 2D array of a plane of this component's flow data and settings
    /// </summary>
    private Vector3[,] GetSlice()
    {
        return slice = GetSlice(flowFile, size.x, size.y, axis, depth);
    }

    /// <summary>
    /// Generates a slice of data and renders it to a texture to display the clipped plane's contour lines
    /// </summary>
    public void UpdateSlice()
    {
        GetSlice();

        if (texture != null)
        {
            texture.Reinitialize(size.x, size.y);
        }
        else
        {
            texture = new Texture2D(size.x, size.y);
        }

        for (int y = 0; y < size.y; y++)
        {
            for (int x = 0; x < size.x; x++)
            {
                texture.SetPixel(x, y, new Color(slice[x, y].normalized.x, slice[x, y].normalized.y, slice[x, y].normalized.z, 1));
            }
        }

        texture.Apply();

        shader.SetTexture("_Texture", texture);
    }

    /// <summary>
    /// Returns a 2D array of a plane of the given flow data and settings
    /// </summary>
    /// <param name="flowFile"></param>
    /// <param name="sizeX"></param>
    /// <param name="sizeY"></param>
    /// <param name="axis"></param>
    /// <param name="depth"></param>
    /// <returns></returns>
    public static Vector3[,] GetSlice(FlowFile flowFile, int sizeX, int sizeY, PlaneAxis axis, float depth)
    {
        if (flowFile == null)
        {
            return null;
        }

        Vector3[,] slice = new Vector3[sizeX, sizeY];

        depth = Mathf.Clamp(depth, 0, 100);

        for (int y = 0; y < sizeY; y++)
        {
            for (int x = 0; x < sizeX; x++)
            {
                switch (axis)
                {
                    case PlaneAxis.XZ:

                        slice[x, y] = flowFile.Sample(new Vector3(x * (sizeX > 1 ? (100 / (sizeX - 1)) : 100), depth, y * (sizeY > 1 ? (100 / (sizeY - 1)) : 100)));

                        break;

                    case PlaneAxis.XY:

                        slice[x, y] = flowFile.Sample(new Vector3(x * (sizeX > 1 ? (100 / (sizeX - 1)) : 100), y * (sizeY > 1 ? (100 / (sizeY - 1)) : 100), depth));

                        break;

                    case PlaneAxis.ZY:

                        slice[x, y] = flowFile.Sample(new Vector3(depth, y * (sizeY > 1 ? (100 / (sizeY - 1)) : 100), x * (sizeX > 1 ? (100 / (sizeX - 1)) : 100)));

                        break;
                }
            }
        }

        return slice;
    }
}
