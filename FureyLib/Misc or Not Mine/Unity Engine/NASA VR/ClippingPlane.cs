
// Flow Data Clipping Plane Script
// by Kyle Furey for NASA VR Project

using UnityEngine;
using UnityEngine.Rendering;

/// <summary>
/// Clips and displays a plane of flow data.
/// </summary>
public class ClippingPlane : MonoBehaviour
{
    [Header("Clips and displays a plane of flow data.")]

    [Header("\nCONFIGURATION")]

    [Header("Reference to the flow file data and planes of visibility:")]
    [SerializeField] private ParticleVisibility particleVisibility = null;

    [Header("The contour lines material used to represent the slice:")]
    [SerializeField] private Material material = null;

    [Header("The axis of the flow data to clip:")]
    public ParticleVisibility.Axis axis = ParticleVisibility.Axis.X;

    [Header("The size of the slice of flow data to clip:")]
    public int resolution = 100;

    [Header("The depth of the slice of flow data to clip:")]
    public float depth = 50;

    [Header("\nHEIGHT MAP SETTINGS")]

    [Header("Whether to display the clipping plane's grid:")]
    public bool showPlane = true;

    [Header("Whether to use the density or magnetic field map as the height map's texture:")]
    public MapType calculation = MapType.Velocity;

    [Header("Whether to make the map black and white:")]
    public bool blackAndWhite = false;

    [Header("The number of planes generated to display the flow data with:")]
    public int planeCount = 500;

    [Header("The maximum height to generate planes for when displaying the flow data:")]
    public float planeHeight = 10;

    [Header("The direction to render the height map in:")]
    public PlaneDirection direction = PlaneDirection.AxisDirection;

    [Header("Whether to render the height map's direction in the opposite direction:")]
    [SerializeField] private bool negativeX = false;
    [SerializeField] private bool negativeY = false;
    [SerializeField] private bool negativeZ = false;

    [Header("\nSHADER SETTINGS")]

    [Header("The color mode to assign the flow data:")]
    public ColorMode colorMode = ColorMode.Default;

    [Header("The color assigned to the flow data based on the color mode:")]
    public Color color = Color.white;

    [Header("The color assigned to the flow data based on the color mode:")]
    public float padding = 0.001f;

    /// <summary>
    /// Automatically generated height map generator
    /// </summary>
    private HeightMapGenerator heightMap = null;

    /// <summary>
    /// The clipped plane of the flow file's data
    /// </summary>
    private Vector3[,] slice = null;

    /// <summary>
    /// All of the points of data from the flow sample
    /// </summary>
    public Vector3[,,] sample = null;

    /// <summary>
    /// The stored texture that represents the clipped plane's density values
    /// </summary>
    private Texture2D map = null;

    /// <summary>
    /// The starting position of the height map generator
    /// </summary>
    private Vector3 startPosition = Vector3.zero;

    /// <summary>
    /// The starting rotation of the height map generator
    /// </summary>
    private Vector3 startRotation = Vector3.zero;

    /// <summary>
    /// Map type enum
    /// </summary>
    public enum MapType { Velocity, Density, MagneticField };

    /// <summary>
    /// Color mode enum
    /// </summary>
    public enum ColorMode { Default, Normal, Overlay, Multiply, Fill, BlackAndWhite };

    /// <summary>
    /// Direction enum
    /// </summary>
    public enum PlaneDirection { AxisDirection, X, Y, Z };

    /// <summary>
    /// Whether the game has started
    /// </summary>
    private bool awake = false;

    /// <summary>
    /// mu0 mathematical constant
    /// </summary>
    public const double mu0 = 1.25663706 * 10e-6;


    // FUNCTIONS

    /// <summary>
    /// Clamps the depth and tests the clipping plane
    /// </summary>
    private void OnValidate()
    {
        depth = Mathf.Clamp(depth, 0, ParticleVisibility.particleScale);

        if (awake && particleVisibility.flowFile != null && material != null)
        {
            RenderSlice(false);
        }
    }

    /// <summary>
    /// Allows the clipping plane to be tested
    /// </summary>
    private void Awake()
    {
        awake = true;

        heightMap = gameObject.GetComponent<HeightMapGenerator>();

        if (heightMap == null)
        {
            heightMap = gameObject.AddComponent<HeightMapGenerator>();
        }

        heightMap.material = material;

        heightMap.liveTesting = false;

        heightMap.Generate();

        particleVisibility.boundsAreStatic = true;

        startPosition = transform.position;

        startRotation = transform.eulerAngles;
    }

    /// <summary>
    /// Start() is called before the first frame update
    /// </summary>
    private void Start()
    {
        MakeSample();

        RenderSlice();
    }


    // RENDERING SLICE

    /// <summary>
    /// Updates a slice of data and renders it to a texture to display the clipped plane's contour lines
    /// </summary>
    public void RenderSlice()
    {
        GetSlice();

        if (map != null)
        {
            map.Reinitialize(resolution, resolution);
        }
        else
        {
            map = new Texture2D(resolution, resolution);
        }

        for (int y = 0; y < resolution; y++)
        {
            for (int x = 0; x < resolution; x++)
            {
                Vector3 J = new Vector3();

                float average;

                switch (calculation)
                {
                    case MapType.Velocity:

                        J = slice[x, y].normalized;

                        break;

                    case MapType.Density:

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
                              (1e-6 / mu0 * (GetSample(x + 1, y + 1, (int)(depth + 1)).z - GetSample(x - 1, y - 1, (int)(depth - 1)).z)
                              /
                              ((OrientPoint(x + 1, y + 1, (int)(depth + 1)).y - OrientPoint(x - 1, y - 1, (int)(depth - 1)).y))
                              -
                              (GetSample(x + 1, y + 1, (int)(depth + 1)).y - GetSample(x - 1, y - 1, (int)(depth - 1)).y)
                              /
                              ((OrientPoint(x + 1, y + 1, (int)(depth + 1)).z - OrientPoint(x - 1, y - 1, (int)(depth - 1)).z)));

                        J.y = (float)
                              (1e-6 / mu0 * (GetSample(x + 1, y + 1, (int)(depth + 1)).x - GetSample(x - 1, y - 1, (int)(depth - 1)).x)
                              /
                              ((OrientPoint(x + 1, y + 1, (int)(depth + 1)).z - OrientPoint(x - 1, y - 1, (int)(depth - 1)).z))
                              -
                              (GetSample(x + 1, y + 1, (int)(depth + 1)).z - GetSample(x - 1, y - 1, (int)(depth - 1)).z)
                              /
                              ((OrientPoint(x + 1, y + 1, (int)(depth + 1)).x - OrientPoint(x - 1, y - 1, (int)(depth - 1)).x)));

                        J.z = (float)
                              (1e-6 / mu0 * (GetSample(x + 1, y + 1, (int)(depth + 1)).y - GetSample(x - 1, y - 1, (int)(depth - 1)).y)
                              /
                              ((OrientPoint(x + 1, y + 1, (int)(depth + 1)).x - OrientPoint(x - 1, y - 1, (int)(depth - 1)).x))
                              -
                              (GetSample(x + 1, y + 1, (int)(depth + 1)).x - GetSample(x - 1, y - 1, (int)(depth - 1)).x)
                              /
                              ((OrientPoint(x + 1, y + 1, (int)(depth + 1)).y - OrientPoint(x - 1, y - 1, (int)(depth - 1)).y)));

                        J = J.normalized;

                        average = (J.x + J.y + J.z) / 3;

                        J = new Vector3(average * J.x, average * J.y, average * J.z);

                        break;

                    case MapType.MagneticField:

                        J = IMEF.BDipole(GetSample(x, y, (int)depth)).normalized;

                        break;
                }

                if (blackAndWhite)
                {
                    average = (J.x + J.y + J.z) / 3;

                    J = new Vector3(average, average, average);
                }

                map.SetPixel(x, y, new Color(J.x, J.y, J.z, 1));
            }
        }

        map.Apply();

        material.SetTexture("_Map", map);

        UpdateColor();

        UpdateDirection();

        material.SetFloat("_Projection_Height", planeHeight);

        material.SetFloat("_Projection_Padding", padding);

        UpdatePlanes();
    }

    /// <summary>
    /// Updates and generates a slice of data and renders it to a texture to display the clipped plane's contour lines
    /// </summary>
    public void RenderSlice(bool regenerate)
    {
        GetSlice();

        if (map != null)
        {
            map.Reinitialize(resolution, resolution);
        }
        else
        {
            map = new Texture2D(resolution, resolution);
        }

        for (int y = 0; y < resolution; y++)
        {
            for (int x = 0; x < resolution; x++)
            {
                Vector3 J = new Vector3();

                float average = 0;

                switch (calculation)
                {
                    case MapType.Velocity:

                        J = slice[x, y].normalized;

                        break;

                    case MapType.Density:

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
                              (1e-6 / mu0 * (GetSample(x + 1, y + 1, (int)(depth + 1)).z - GetSample(x - 1, y - 1, (int)(depth - 1)).z)
                              /
                              ((OrientPoint(x + 1, y + 1, (int)(depth + 1)).y - OrientPoint(x - 1, y - 1, (int)(depth - 1)).y))
                              -
                              (GetSample(x + 1, y + 1, (int)(depth + 1)).y - GetSample(x - 1, y - 1, (int)(depth - 1)).y)
                              /
                              ((OrientPoint(x + 1, y + 1, (int)(depth + 1)).z - OrientPoint(x - 1, y - 1, (int)(depth - 1)).z)));

                        J.y = (float)
                              (1e-6 / mu0 * (GetSample(x + 1, y + 1, (int)(depth + 1)).x - GetSample(x - 1, y - 1, (int)(depth - 1)).x)
                              /
                              ((OrientPoint(x + 1, y + 1, (int)(depth + 1)).z - OrientPoint(x - 1, y - 1, (int)(depth - 1)).z))
                              -
                              (GetSample(x + 1, y + 1, (int)(depth + 1)).z - GetSample(x - 1, y - 1, (int)(depth - 1)).z)
                              /
                              ((OrientPoint(x + 1, y + 1, (int)(depth + 1)).x - OrientPoint(x - 1, y - 1, (int)(depth - 1)).x)));

                        J.z = (float)
                              (1e-6 / mu0 * (GetSample(x + 1, y + 1, (int)(depth + 1)).y - GetSample(x - 1, y - 1, (int)(depth - 1)).y)
                              /
                              ((OrientPoint(x + 1, y + 1, (int)(depth + 1)).x - OrientPoint(x - 1, y - 1, (int)(depth - 1)).x))
                              -
                              (GetSample(x + 1, y + 1, (int)(depth + 1)).x - GetSample(x - 1, y - 1, (int)(depth - 1)).x)
                              /
                              ((OrientPoint(x + 1, y + 1, (int)(depth + 1)).y - OrientPoint(x - 1, y - 1, (int)(depth - 1)).y)));

                        J = J.normalized;

                        average = (J.x + J.y + J.z) / 3;

                        J = new Vector3(average * J.x, average * J.y, average * J.z);

                        break;

                    case MapType.MagneticField:

                        J = IMEF.BDipole(GetSample(x, y, (int)depth)).normalized;

                        break;
                }

                if (blackAndWhite)
                {
                    average = (J.x + J.y + J.z) / 3;

                    J = new Vector3(average, average, average);
                }

                map.SetPixel(x, y, new Color(J.x, J.y, J.z, 1));
            }
        }

        map.Apply();

        material.SetTexture("_Map", map);

        UpdateColor();

        UpdateDirection();

        material.SetFloat("_Projection_Height", planeHeight);

        material.SetFloat("_Projection_Padding", padding);

        UpdatePlanes(regenerate);
    }

    /// <summary>
    /// Updates the color mode of the shader
    /// </summary>
    private void UpdateColor()
    {
        material.DisableKeyword(new LocalKeyword(material.shader, "_COLOR_MODE_DEFAULT"));
        material.DisableKeyword(new LocalKeyword(material.shader, "_COLOR_MODE_NORMAL"));
        material.DisableKeyword(new LocalKeyword(material.shader, "_COLOR_MODE_OVERLAY"));
        material.DisableKeyword(new LocalKeyword(material.shader, "_COLOR_MODE_MULTIPLY"));
        material.DisableKeyword(new LocalKeyword(material.shader, "_COLOR_MODE_FILL"));
        material.DisableKeyword(new LocalKeyword(material.shader, "_COLOR_MODE_BLACK_AND_WHITE"));

        switch (colorMode)
        {
            case ColorMode.Default:

                material.SetKeyword(new LocalKeyword(material.shader, "_COLOR_MODE_DEFAULT"), true);

                return;

            case ColorMode.Normal:

                material.SetKeyword(new LocalKeyword(material.shader, "_COLOR_MODE_NORMAL"), true);

                return;

            case ColorMode.Overlay:

                material.SetKeyword(new LocalKeyword(material.shader, "_COLOR_MODE_OVERLAY"), true);

                return;

            case ColorMode.Multiply:

                material.SetKeyword(new LocalKeyword(material.shader, "_COLOR_MODE_MULTIPLY"), true);

                return;

            case ColorMode.Fill:

                material.SetKeyword(new LocalKeyword(material.shader, "_COLOR_MODE_FILL"), true);

                return;

            case ColorMode.BlackAndWhite:

                material.SetKeyword(new LocalKeyword(material.shader, "_COLOR_MODE_BLACK_AND_WHITE"), true);

                return;
        }

        material.SetColor("_Color", color);
    }

    /// <summary>
    /// Updates the direction of the shader
    /// </summary>
    private void UpdateDirection()
    {
        transform.position = startPosition;

        transform.eulerAngles = startRotation;

        material.DisableKeyword(new LocalKeyword(material.shader, "_DIRECTION_X"));
        material.DisableKeyword(new LocalKeyword(material.shader, "_DIRECTION_Y"));
        material.DisableKeyword(new LocalKeyword(material.shader, "_DIRECTION_Z"));
        material.DisableKeyword(new LocalKeyword(material.shader, "_DIRECTION_NEGATIVE_X"));
        material.DisableKeyword(new LocalKeyword(material.shader, "_DIRECTION_NEGATIVE_Y"));
        material.DisableKeyword(new LocalKeyword(material.shader, "_DIRECTION_NEGATIVE_Z"));

        switch (direction)
        {
            case PlaneDirection.AxisDirection:

                switch (axis)
                {
                    case ParticleVisibility.Axis.X:

                        if (negativeX)
                        {
                            material.SetKeyword(new LocalKeyword(material.shader, "_DIRECTION_NEGATIVE_Y"), true);

                            transform.Translate(0, 10, 0, Space.World);

                            transform.Rotate(0, 0, 180);

                            material.SetFloat("_Projection_Offset", transform.position.y);
                        }
                        else
                        {
                            material.SetKeyword(new LocalKeyword(material.shader, "_DIRECTION_Y"), true);

                            material.SetFloat("_Projection_Offset", -transform.position.y);
                        }

                        return;

                    case ParticleVisibility.Axis.Y:

                        if (negativeY)
                        {
                            material.SetKeyword(new LocalKeyword(material.shader, "_DIRECTION_NEGATIVE_Z"), true);

                            transform.Translate(0, 5, 5, Space.World);

                            transform.Rotate(-90, 0, 0);

                            material.SetFloat("_Projection_Offset", transform.position.z);
                        }
                        else
                        {
                            material.SetKeyword(new LocalKeyword(material.shader, "_DIRECTION_Z"), true);

                            transform.Translate(0, 5, -5, Space.World);

                            transform.Rotate(90, 0, 0);

                            material.SetFloat("_Projection_Offset", -transform.position.z);
                        }

                        return;

                    case ParticleVisibility.Axis.Z:

                        if (negativeZ)
                        {
                            material.SetKeyword(new LocalKeyword(material.shader, "_DIRECTION_NEGATIVE_X"), true);

                            transform.Translate(5, 5, 0, Space.World);

                            transform.Rotate(0, 0, 90);

                            material.SetFloat("_Projection_Offset", transform.position.x);
                        }
                        else
                        {
                            material.SetKeyword(new LocalKeyword(material.shader, "_DIRECTION_X"), true);

                            transform.Translate(-5, 5, 0, Space.World);

                            transform.Rotate(0, 0, -90);

                            material.SetFloat("_Projection_Offset", -transform.position.x);
                        }

                        return;
                }

                return;

            case PlaneDirection.X:

                if (negativeX)
                {
                    material.SetKeyword(new LocalKeyword(material.shader, "_DIRECTION_NEGATIVE_Y"), true);

                    transform.Translate(0, 10, 0, Space.World);

                    transform.Rotate(0, 0, 180);

                    material.SetFloat("_Projection_Offset", transform.position.y);
                }
                else
                {
                    material.SetKeyword(new LocalKeyword(material.shader, "_DIRECTION_Y"), true);

                    material.SetFloat("_Projection_Offset", -transform.position.y);
                }

                return;

            case PlaneDirection.Y:

                if (negativeY)
                {
                    material.SetKeyword(new LocalKeyword(material.shader, "_DIRECTION_NEGATIVE_Z"), true);

                    transform.Translate(0, 5, 5, Space.World);

                    transform.Rotate(-90, 0, 0);

                    material.SetFloat("_Projection_Offset", transform.position.z);
                }
                else
                {
                    material.SetKeyword(new LocalKeyword(material.shader, "_DIRECTION_Z"), true);

                    transform.Translate(0, 5, -5, Space.World);

                    transform.Rotate(90, 0, 0);

                    material.SetFloat("_Projection_Offset", -transform.position.z);
                }

                return;

            case PlaneDirection.Z:

                if (negativeZ)
                {
                    material.SetKeyword(new LocalKeyword(material.shader, "_DIRECTION_NEGATIVE_X"), true);

                    transform.Translate(5, 5, 0, Space.World);

                    transform.Rotate(0, 0, 90);

                    material.SetFloat("_Projection_Offset", transform.position.x);
                }
                else
                {
                    material.SetKeyword(new LocalKeyword(material.shader, "_DIRECTION_X"), true);

                    transform.Translate(-5, 5, 0, Space.World);

                    transform.Rotate(0, 0, -90);

                    material.SetFloat("_Projection_Offset", -transform.position.x);
                }

                return;
        }

        material.SetColor("_Color", color);
    }

    /// <summary>
    /// Updates the shader and clipping plane objects
    /// </summary>
    private void UpdatePlanes()
    {
        if (particleVisibility != null)
        {
            particleVisibility.ShowPlanes(false);

            particleVisibility.ShowPlane(axis, showPlane);

            particleVisibility.xPlane.transform.localPosition = new Vector3(0.5f, depth / ParticleVisibility.particleScale, 0.5f) * ParticleVisibility.particleScale;
            particleVisibility.yPlane.transform.localPosition = new Vector3(0.5f, 0.5f, depth / ParticleVisibility.particleScale) * ParticleVisibility.particleScale;
            particleVisibility.zPlane.transform.localPosition = new Vector3(depth / ParticleVisibility.particleScale, 0.5f, 0.5f) * ParticleVisibility.particleScale;
        }

        heightMap.count = planeCount;

        heightMap.height = planeHeight;

        heightMap.Generate();
    }

    /// <summary>
    /// Updates the shader and regenerates clipping plane objects
    /// </summary>
    private void UpdatePlanes(bool regenerate)
    {
        if (particleVisibility != null)
        {
            particleVisibility.ShowPlanes(false);

            particleVisibility.ShowPlane(axis, showPlane);

            particleVisibility.xPlane.transform.localPosition = new Vector3(0.5f, depth / ParticleVisibility.particleScale, 0.5f) * ParticleVisibility.particleScale;
            particleVisibility.yPlane.transform.localPosition = new Vector3(0.5f, 0.5f, depth / ParticleVisibility.particleScale) * ParticleVisibility.particleScale;
            particleVisibility.zPlane.transform.localPosition = new Vector3(depth / ParticleVisibility.particleScale, 0.5f, 0.5f) * ParticleVisibility.particleScale;
        }

        heightMap.count = planeCount;

        heightMap.height = planeHeight;

        if (regenerate)
        {
            heightMap.Generate();
        }
    }


    // GETTERS

    /// <summary>
    /// Returns a 2D array of a plane of this component's flow data and settings
    /// </summary>
    public Vector3[,] GetSlice()
    {
        return slice = GetSlice(particleVisibility.flowFile, resolution, resolution, axis, depth);
    }

    /// <summary>
    /// Returns a 3D array of all this component's flow data points
    /// </summary>
    /// <returns></returns>
    public Vector3[,,] MakeSample()
    {
        return sample = MakeSample(particleVisibility.flowFile, 100, 100, 100);
    }

    /// <summary>
    /// Returns a point of the sample relative to the axis
    /// </summary>
    /// <param name="pointX"></param>
    /// <param name="pointY"></param>
    /// <param name="pointZ"></param>
    /// <returns></returns>
    public Vector3 GetSample(int pointX, int pointY, int pointZ)
    {
        return GetSample(pointX, pointY, pointZ, sample, axis);
    }

    /// <summary>
    /// Orients a point based on the axis
    /// </summary>
    /// <param name="pointX"></param>
    /// <param name="pointY"></param>
    /// <param name="pointZ"></param>
    /// <returns></returns>
    public Vector3Int OrientPoint(int pointX, int pointY, int pointZ)
    {
        return OrientPoint(pointX, pointY, pointZ, axis);
    }


    // STATIC GETTERS

    /// <summary>
    /// Returns a 2D array of a plane of the given flow data and settings
    /// </summary>
    /// <param name="flowFile"></param>
    /// <param name="sizeX"></param>
    /// <param name="sizeY"></param>
    /// <param name="axis"></param>
    /// <param name="depth"></param>
    /// <returns></returns>
    public static Vector3[,] GetSlice(FlowFile flowFile, int sizeX, int sizeY, ParticleVisibility.Axis axis, float depth)
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
                    case ParticleVisibility.Axis.X:

                        slice[x, y] = flowFile.Sample(new Vector3(x * (sizeX > 1 ? (100 / (sizeX - 1)) : 100), depth, y * (sizeY > 1 ? (100 / (sizeY - 1)) : 100)));

                        break;

                    case ParticleVisibility.Axis.Y:

                        slice[x, y] = flowFile.Sample(new Vector3(x * (sizeX > 1 ? (100 / (sizeX - 1)) : 100), y * (sizeY > 1 ? (100 / (sizeY - 1)) : 100), depth));

                        break;

                    case ParticleVisibility.Axis.Z:

                        slice[x, y] = flowFile.Sample(new Vector3(depth, y * (sizeY > 1 ? (100 / (sizeY - 1)) : 100), x * (sizeX > 1 ? (100 / (sizeX - 1)) : 100)));

                        break;
                }
            }
        }

        return slice;
    }

    /// <summary>
    /// Returns a 3D array of all the given flow data points
    /// </summary>
    /// <param name="flowFile"></param>
    /// <param name="resolution"></param>
    /// <returns></returns>
    public static Vector3[,,] MakeSample(FlowFile flowFile, int sizeX, int sizeY, int sizeZ)
    {
        if (flowFile == null)
        {
            return null;
        }

        Vector3[,,] sample = new Vector3[sizeX, sizeY, sizeZ];

        for (int z = 0; z < sizeZ; z++)
        {
            for (int y = 0; y < sizeY; y++)
            {
                for (int x = 0; x < sizeX; x++)
                {
                    sample[x, y, z] = flowFile.Sample(new Vector3(x * (sizeX > 1 ? (100 / (sizeX - 1)) : 100), y * (sizeY > 1 ? (100 / (sizeY - 1)) : 100), z * (sizeZ > 1 ? (100 / (sizeZ - 1)) : 100)));
                }
            }
        }

        return sample;
    }

    /// <summary>
    /// Returns a point of the given sample relative to an axis
    /// </summary>
    /// <param name="pointX"></param>
    /// <param name="pointY"></param>
    /// <param name="pointZ"></param>
    /// <param name="sample"></param>
    /// <param name="axis"></param>
    /// <returns></returns>
    public static Vector3 GetSample(int pointX, int pointY, int pointZ, Vector3[,,] sample, ParticleVisibility.Axis axis)
    {
        if (pointX < 0)
        {
            pointX = 0;
        }
        else if (pointX >= sample.GetLength(0))
        {
            pointX = sample.GetLength(0) - 1;
        }

        if (pointY < 0)
        {
            pointY = 0;
        }
        else if (pointY >= sample.GetLength(1))
        {
            pointY = sample.GetLength(1) - 1;
        }

        if (pointZ < 0)
        {
            pointZ = 0;
        }
        else if (pointZ >= sample.GetLength(2))
        {
            pointZ = sample.GetLength(2) - 1;
        }

        Vector3 point = Vector3.zero;

        switch (axis)
        {
            case ParticleVisibility.Axis.X:

                point = sample[pointX, pointZ, pointY];

                break;

            case ParticleVisibility.Axis.Y:

                point = sample[pointX, pointY, pointZ];

                break;

            case ParticleVisibility.Axis.Z:

                point = sample[pointZ, pointY, pointX];

                break;
        }

        return point;
    }

    /// <summary>
    /// Orients a point based on the given axis
    /// </summary>
    /// <param name="pointX"></param>
    /// <param name="pointY"></param>
    /// <param name="pointZ"></param>
    /// <param name="axis"></param>
    /// <returns></returns>
    public static Vector3Int OrientPoint(int pointX, int pointY, int pointZ, ParticleVisibility.Axis axis)
    {
        Vector3Int point = Vector3Int.zero;

        switch (axis)
        {
            case ParticleVisibility.Axis.X:

                point = new Vector3Int(pointX, pointZ, pointY);

                break;

            case ParticleVisibility.Axis.Y:

                point = new Vector3Int(pointX, pointY, pointZ);

                break;

            case ParticleVisibility.Axis.Z:

                point = new Vector3Int(pointZ, pointY, pointX);

                break;
        }

        return point;
    }


    // SETTERS

    /// <summary>
    /// Updates the axis and direction of the clipping plane
    /// </summary>
    public void SetAxis(ParticleVisibility.Axis axis, PlaneDirection direction = PlaneDirection.AxisDirection)
    {
        this.axis = axis;

        this.direction = direction;
    }

    /// <summary>
    /// Updates the resolution of the clipping plane
    /// </summary>
    public void SetResolution(int resolution)
    {
        this.resolution = resolution;
    }

    /// <summary>
    /// Updates the depth of the clipping plane
    /// </summary>
    public void SetDepth(float depth)
    {
        this.depth = depth;

        this.depth = Mathf.Clamp(this.depth, 0, ParticleVisibility.particleScale);
    }

    /// <summary>
    /// Shows or hides the clipping plane
    /// </summary>
    public void ShowPlane(bool show)
    {
        showPlane = show;
    }

    /// <summary>
    /// Updates the plane count and height of the planes
    /// </summary>
    public void SetPlaneCount(int count, float height = 10)
    {
        planeCount = count;

        planeHeight = height;
    }

    /// <summary>
    /// Updates the color mode of the shader
    /// </summary>
    public void SetColorMode(ColorMode colorMode)
    {
        this.colorMode = colorMode;
    }

    /// <summary>
    /// Updates the color mode and color of the shader
    /// </summary>
    public void SetColorMode(ColorMode colorMode, Color color)
    {
        this.colorMode = colorMode;

        this.color = color;
    }

    /// <summary>
    /// Updates the padding of the shader
    /// </summary>
    public void SetPadding(float padding)
    {
        this.padding = padding;
    }

    /// <summary>
    /// Updates the padding of the shader
    /// </summary>
    public void SetMap(MapType calculation)
    {
        this.calculation = calculation;
    }


    // UX FUNCTIONS

    [Header("The lever that provides control over the clipping plane:")]
    [SerializeField] private LeverVR controlLever = null;

    /// <summary>
    /// Increments depth by the given speed and lever's percentage
    /// </summary>
    /// <param name="speed"></param>
    public void MoveDepthForward(float speed = 20)
    {
        SetDepth(depth + speed * Time.deltaTime * controlLever.GetLeverAxis(LeverVR.Direction2D.Backward));

        RenderSlice(false);
    }

    /// <summary>
    /// Decrements depth by the given speed and lever's percentage
    /// </summary>
    /// <param name="speed"></param>
    public void MoveDepthBackward(float speed = 20)
    {
        SetDepth(depth - speed * Time.deltaTime * controlLever.GetLeverAxis(LeverVR.Direction2D.Backward));

        RenderSlice(false);
    }

    /// <summary>
    /// Cycles the current axis direction
    /// </summary>
    public void CycleAxis()
    {
        SetAxis((ParticleVisibility.Axis)(((int)axis + 1) % 3), direction);

        RenderSlice(false);
    }

    /// <summary>
    /// Toggles the clipping plane
    /// </summary>
    public void TogglePlane()
    {
        ShowPlane(!showPlane);

        RenderSlice(false);
    }

    /// <summary>
    /// Cycles which map to show
    /// </summary>
    public void CycleMap()
    {
        SetMap((MapType)(((int)calculation + 1) % 3));

        RenderSlice(false);
    }

    /// <summary>
    /// Cycles which data field to show
    /// </summary>
    public void CycleFlowFile()
    {
        particleVisibility.CycleFlowFiles();

        RenderSlice(false);
    }
}
