
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

    [Header("Reference to the flow file:")]
    [SerializeField] private FlowFile flowFile = null;

    [Header("The contour lines material used to represent the slice:")]
    [SerializeField] private Material material = null;

    [Header("The axis of the flow data to clip:")]
    public ParticleVisibility.Axis axis = ParticleVisibility.Axis.X;

    [Header("The size of the slice of flow data to clip:")]
    public int resolution = 100;

    [Header("The depth of the slice of flow data to clip:")]
    public float depth = 50;

    [Header("\nGRID SETTINGS")]

    [Header("Optional reference to the planes of visibility:")]
    [SerializeField] private ParticleVisibility particleVisibility = null;

    [Header("Whether to display the clipping plane's grid:")]
    public bool showPlane = true;

    [Header("\nHEIGHT MAP SETTINGS")]

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
    /// The stored texture that represents the clipped plane
    /// </summary>
    private Texture2D texture = null;

    /// <summary>
    /// The starting position of the height map generator
    /// </summary>
    private Vector3 startPosition = Vector3.zero;

    /// <summary>
    /// The starting rotation of the height map generator
    /// </summary>
    private Vector3 startRotation = Vector3.zero;

    /// <summary>
    /// Color mode enum
    /// </summary>
    public enum ColorMode { Default, Normal, Overlay, Multiply, Fill, BlackAndWhite, Density };

    /// <summary>
    /// Direction enum
    /// </summary>
    public enum PlaneDirection { AxisDirection, X, Y, Z };

    /// <summary>
    /// Whether the game has started
    /// </summary>
    private bool awake = false;


    // FUNCTIONS

    /// <summary>
    /// Clamps the depth and tests the clipping plane
    /// </summary>
    private void OnValidate()
    {
        depth = Mathf.Clamp(depth, 0, ParticleVisibility.particleScale);

        if (awake && flowFile != null && material != null)
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
        RenderSlice();
    }


    // RENDERING SLICE

    /// <summary>
    /// Updates a slice of data and renders it to a texture to display the clipped plane's contour lines
    /// </summary>
    public void RenderSlice()
    {
        GetSlice();

        if (texture != null)
        {
            texture.Reinitialize(resolution, resolution);
        }
        else
        {
            texture = new Texture2D(resolution, resolution);
        }

        for (int y = 0; y < resolution; y++)
        {
            for (int x = 0; x < resolution; x++)
            {
                texture.SetPixel(x, y, new Color(slice[x, y].normalized.x, slice[x, y].normalized.y, slice[x, y].normalized.z, 1));
            }
        }

        texture.Apply();

        material.SetTexture("_Texture", texture);

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

        if (texture != null)
        {
            texture.Reinitialize(resolution, resolution);
        }
        else
        {
            texture = new Texture2D(resolution, resolution);
        }

        for (int y = 0; y < resolution; y++)
        {
            for (int x = 0; x < resolution; x++)
            {
                texture.SetPixel(x, y, new Color(slice[x, y].normalized.x, slice[x, y].normalized.y, slice[x, y].normalized.z, 1));
            }
        }

        texture.Apply();

        material.SetTexture("_Texture", texture);

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
        material.DisableKeyword(new LocalKeyword(material.shader, "_COLOR_MODE_DENSITY"));

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

            case ColorMode.Density:

                material.SetKeyword(new LocalKeyword(material.shader, "_COLOR_MODE_DENSITY"), true);

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
        return slice = GetSlice(flowFile, resolution, resolution, axis, depth);
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
}
