
// Interactable VR Marker Object Script
// by Kyle Furey

// REQUIREMENTS: HandTrackerVR.cs, HandGrabbableVR.cs

using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

/// <summary>
/// Represents a marker-like object that can be picked up and used to draw on other objects.
/// </summary>
public class MarkerVR : MonoBehaviour, IHandInteractableVR
{
    [Header("Represents a marker-like object that can be picked up and used to draw on other objects.")]
    [Header("NOTE: This component must be placed on the marker tip object.")]
    [Header("It will only draw on qualifying objects with the \"Drawable\" tag.")]

    [Header("\nCONFIGURATION")]

    [Header("Configures the marker object's grab settings:")]
    [SerializeField] private HandGrabbableVR grabSettings = null;

    [Header("The direction to check for collision with the marker:")]
    [SerializeField] private Vector3 markerDirection = new Vector3(0, 1, -0.15f);

    [Header("The distance to check for collision with the marker:")]
    [SerializeField] private float markerDistance = 0.05f;

    [Header("The maximum distance the marker can move before ink is depleted, the texture is updated, and the last drawn position is reset:")]
    [SerializeField] private float markerUpdateDistance = 0;

    [Header("The name of the marker materials' color parameter:")]
    [SerializeField] private string markerColorParameter = "_BaseColor";

    [Header("The name of the drawn objects' materials' albedo texture parameters:")]
    [SerializeField] private bool useMainTexture = true;
    [SerializeField] private string textureParameter = "_BaseMap";

    /// <summary>
    /// Whether to use the main texture globally
    /// </summary>
    private static bool globalUseMainTexture = true;

    /// <summary>
    /// The global name for the texture parameter
    /// </summary>
    private static string globalTextureParameter = "_BaseMap";

    [Header("The name of the drawn objects' materials' roughness texture parameters:")]
    [SerializeField] private string roughnessParameter = "_MetallicGlossMap";

    /// <summary>
    /// The global name for the roughness parameter
    /// </summary>
    private static string globalRoughnessParameter = "_MetallicGlossMap";

    [Header("The roughness value of ink when drawn:")]
    [SerializeField] private float inkRoughness = 0;

    [Header("Renderers of separate parts of this marker object that match the color of this marker:")]
    [SerializeField] private List<Renderer> coloredMarkerBodyParts = new List<Renderer>();

    [Header("\nMARKER SETTINGS")]

    [Header("Whether this marker is an eraser and will instead remove color from a surface instead of applying it:")]
    [SerializeField] private bool isEraser = false;

    [Header("The color of this marker:")]
    [SerializeField] private Color drawColor = Color.black;

    [Header("The radius size in pixels this marker will draw:")]
    [SerializeField] private int drawSize = 10;

    [Header("The draw mode of this marker:")]
    [SerializeField] private DrawMode drawMode = DrawMode.Circle;

    [Header("Whether this marker has infinite ink:")]
    [SerializeField] private bool infiniteInk = true;

    [Header("The maximum ink before this marker dries out:")]
    [SerializeField] private float remainingInk = 100;

    [Header("\nEVENTS")]

    [Header("Event called when the user draws with the marker (update distance dependent):")]
    public UnityEvent onDraw = null;

    /// <summary>
    /// This marker's renderer
    /// </summary>
    private Renderer renderer = null;

    /// <summary>
    /// The last position to check for drawn movement
    /// </summary>
    private Vector3 lastDrawnPosition = Vector3.zero;

    /// <summary>
    /// The running list of game objects to materials (used for updating the original texture)
    /// </summary>
    private static Dictionary<GameObject, Material> materials = new Dictionary<GameObject, Material>();

    /// <summary>
    /// The running list of game objects to albedo textures (used for erasing and preserving the original texture)
    /// </summary>
    private static Dictionary<GameObject, Texture2D> textures = new Dictionary<GameObject, Texture2D>();

    /// <summary>
    /// The running list of game objects to roughness textures (used for erasing and preserving the original roughness values)
    /// </summary>
    private static Dictionary<GameObject, Texture2D> roughnessTextures = new Dictionary<GameObject, Texture2D>();

    /// <summary>
    /// Marker draw mode enum
    /// </summary>
    public enum DrawMode { Square, Diamond, Circle };

    /// <summary>
    /// IHandInteractableVR Interface - Adds this object's implementation to the interface.
    /// </summary>
    private void Awake()
    {
        IHandInteractableVR.implementations.Add(this);

        if (IHandInteractableVR.handsSet)
        {
            OnSetHands();
        }
    }

    /// <summary>
    /// IHandInteractableVR Interface - Called when VR hands are successfully set.
    /// </summary>
    public void OnSetHands() { }

    /// <summary>
    /// IHandInteractableVR Interface - Removes the object's implementation to the interface.
    /// </summary>
    private void OnDestroy()
    {
        IHandInteractableVR.implementations.Remove(this);
    }

    /// <summary>
    /// Called when the marker's settings are edited
    /// </summary>
    private void OnValidate()
    {
        if (Application.isPlaying)
        {
            UpdateMarker();
        }
    }

    /// <summary>
    /// Check for HandGrabbableVR and initialize the marker's material
    /// </summary>
    private void Start()
    {
        if (grabSettings == null)
        {
            Debug.LogError("ERROR: MarkerVR " + gameObject.name + " does not have HandGrabbableVR configured!");

            Destroy(this);
        }

        renderer = GetComponentInChildren<Renderer>();

        renderer.sharedMaterial = new Material(renderer.sharedMaterial);

        renderer.sharedMaterial.SetColor(markerColorParameter, drawColor);

        if (coloredMarkerBodyParts != null && coloredMarkerBodyParts.Count != 0)
        {
            coloredMarkerBodyParts[0].sharedMaterial = new Material(coloredMarkerBodyParts[0].sharedMaterial);

            coloredMarkerBodyParts[0].sharedMaterial.SetColor(markerColorParameter, drawColor);

            for (int i = 1; i < coloredMarkerBodyParts.Count; i++)
            {
                coloredMarkerBodyParts[i].sharedMaterial = coloredMarkerBodyParts[0].sharedMaterial;
            }
        }

        globalUseMainTexture = useMainTexture;

        globalTextureParameter = textureParameter;

        globalRoughnessParameter = roughnessParameter;

        grabSettings.onGrab.AddListener(ResetLastPosition);
    }

    /// <summary>
    /// Checks and draws with the marker
    /// </summary>
    private void Update()
    {
        CheckSurface();
    }


    // MARKER

    /// <summary>
    /// Checks for a surface to draw on with the marker
    /// </summary>
    private void CheckSurface()
    {
        if (grabSettings.IsGrabbed() && (infiniteInk || remainingInk > 0 || isEraser))
        {
            RaycastHit hit;

            if (Physics.Raycast(transform.position, transform.rotation * markerDirection.normalized, out hit, markerDistance, ~(1 << 2), QueryTriggerInteraction.Ignore))
            {
                if (hit.transform.tag == "Drawable" && hit.collider is MeshCollider && !(hit.collider as MeshCollider).convex)
                {
                    Renderer hitRenderer = hit.transform.gameObject.GetComponent<Renderer>();

                    if (hitRenderer != null)
                    {
                        Mesh mesh = hit.transform.gameObject.GetComponent<MeshFilter>().sharedMesh;

                        if (mesh != null && mesh.isReadable)
                        {
                            Texture2D texture = (useMainTexture ? hitRenderer.sharedMaterial.mainTexture : hitRenderer.sharedMaterial.GetTexture(textureParameter)) as Texture2D;

                            Texture2D roughness = hitRenderer.sharedMaterial.GetTexture(roughnessParameter) as Texture2D;

                            if (texture != null && texture.isReadable)
                            {
                                if (!textures.ContainsKey(hit.transform.gameObject))
                                {
                                    materials[hit.transform.gameObject] = hitRenderer.sharedMaterial;

                                    hitRenderer.sharedMaterial = new Material(hitRenderer.sharedMaterial);

                                    textures[hit.transform.gameObject] = texture;

                                    if (useMainTexture)
                                    {
                                        hitRenderer.sharedMaterial.mainTexture = new Texture2D(texture.width, texture.height, texture.format, true);

                                        hitRenderer.sharedMaterial.mainTexture.wrapMode = TextureWrapMode.Repeat;
                                    }
                                    else
                                    {
                                        hitRenderer.sharedMaterial.SetTexture(textureParameter, new Texture2D(texture.width, texture.height, texture.format, true));

                                        hitRenderer.sharedMaterial.GetTexture(textureParameter).wrapMode = TextureWrapMode.Repeat;
                                    }

                                    Graphics.CopyTexture(textures[hit.transform.gameObject], useMainTexture ? hitRenderer.sharedMaterial.mainTexture : hitRenderer.sharedMaterial.GetTexture(textureParameter));

                                    if (roughness != null && roughness.isReadable)
                                    {
                                        roughnessTextures[hit.transform.gameObject] = roughness;

                                        hitRenderer.sharedMaterial.SetTexture(roughnessParameter, new Texture2D(roughness.width, roughness.height, roughness.format, true));

                                        hitRenderer.sharedMaterial.GetTexture(roughnessParameter).wrapMode = TextureWrapMode.Repeat;

                                        Graphics.CopyTexture(roughnessTextures[hit.transform.gameObject], hitRenderer.sharedMaterial.GetTexture(roughnessParameter));
                                    }
                                }

                                float distance = DistanceSquared(transform.position, lastDrawnPosition);

                                if (distance > markerUpdateDistance * markerUpdateDistance)
                                {
                                    lastDrawnPosition = transform.position;

                                    Draw(hitRenderer, hit.textureCoord);

                                    texture.Apply();

                                    if (roughness != null && roughness.isReadable)
                                    {
                                        roughness.Apply();
                                    }

                                    if (!isEraser && !infiniteInk)
                                    {
                                        remainingInk -= markerUpdateDistance <= 0 ? 0.25f : markerUpdateDistance * 10;
                                    }

                                    onDraw.Invoke();
                                }
                            }
                            else
                            {
                                Debug.LogError("ERROR: Drawn texture is not set to Read / Write or is missing!");
                            }
                        }
                        else
                        {
                            Debug.LogError("ERROR: Drawn-on mesh is not set to Read / Write or is missing!");
                        }
                    }
                }
                else
                {
                    Debug.LogWarning("NOTE: To draw on an object with a marker, the object must: have a mesh with Read / Write enabled and a Generated Collider, have a concave mesh collider attached, have a material with a Read / Write texture imported in an editable format, and have the \"Drawable\" tag.");
                }
            }
        }
    }

    /// <summary>
    /// Draws on the given renderer at the given hit point based on the draw mode
    /// </summary>
    /// <param name="renderer"></param>
    /// <param name="textureCoord"></param>
    private void Draw(Renderer renderer, Vector2 textureCoord)
    {
        int drawSize = Mathf.Abs(this.drawSize) - 1;

        if (useMainTexture)
        {
            if (drawSize < 0)
            {
                return;
            }

            if (drawSize == 0)
            {
                if (isEraser)
                {
                    EraseMainTexture(renderer, textureCoord);
                }
                else
                {
                    PaintMainTexture(renderer, textureCoord);
                }

                return;
            }

            switch (drawMode)
            {
                case DrawMode.Square:

                    if (isEraser)
                    {
                        for (int y = -drawSize; y < drawSize; y++)
                        {
                            for (int x = -drawSize; x < drawSize; x++)
                            {
                                EraseMainTexture(renderer, textureCoord, new Vector2Int(x, y));
                            }
                        }

                    }
                    else
                    {
                        for (int y = -drawSize; y < drawSize; y++)
                        {
                            for (int x = -drawSize; x < drawSize; x++)
                            {
                                PaintMainTexture(renderer, textureCoord, new Vector2Int(x, y));
                            }
                        }
                    }

                    break;

                case DrawMode.Diamond:

                    if (isEraser)
                    {
                        for (int y = -drawSize; y < drawSize; y++)
                        {
                            int width = drawSize - Mathf.Abs(y);

                            for (int x = -width; x < width; x++)
                            {
                                EraseMainTexture(renderer, textureCoord, new Vector2Int(x, y));
                            }
                        }

                    }
                    else
                    {
                        for (int y = -drawSize; y < drawSize; y++)
                        {
                            int width = drawSize - Mathf.Abs(y);

                            for (int x = -width; x < width; x++)
                            {
                                PaintMainTexture(renderer, textureCoord, new Vector2Int(x, y));
                            }
                        }
                    }

                    break;

                case DrawMode.Circle:

                    if (isEraser)
                    {
                        for (int y = -drawSize; y < drawSize; y++)
                        {
                            int width = Mathf.CeilToInt(Mathf.Sqrt(drawSize * drawSize - Mathf.Abs(y) * Mathf.Abs(y)));

                            for (int x = -width; x < width; x++)
                            {
                                EraseMainTexture(renderer, textureCoord, new Vector2Int(x, y));
                            }
                        }

                    }
                    else
                    {
                        for (int y = -drawSize; y < drawSize; y++)
                        {
                            int width = Mathf.CeilToInt(Mathf.Sqrt(drawSize * drawSize - Mathf.Abs(y) * Mathf.Abs(y)));

                            for (int x = -width; x < width; x++)
                            {
                                PaintMainTexture(renderer, textureCoord, new Vector2Int(x, y));
                            }
                        }
                    }

                    break;
            }
        }
        else
        {
            if (drawSize < 0)
            {
                return;
            }

            if (drawSize == 0)
            {
                if (isEraser)
                {
                    EraseTexture(renderer, textureCoord);
                }
                else
                {
                    PaintTexture(renderer, textureCoord);
                }

                return;
            }

            switch (drawMode)
            {
                case DrawMode.Square:

                    if (isEraser)
                    {
                        for (int y = -drawSize; y < drawSize; y++)
                        {
                            for (int x = -drawSize; x < drawSize; x++)
                            {
                                EraseTexture(renderer, textureCoord, new Vector2Int(x, y));
                            }
                        }
                    }
                    else
                    {
                        for (int y = -drawSize; y < drawSize; y++)
                        {
                            for (int x = -drawSize; x < drawSize; x++)
                            {
                                PaintTexture(renderer, textureCoord, new Vector2Int(x, y));
                            }
                        }
                    }

                    break;

                case DrawMode.Diamond:

                    if (isEraser)
                    {
                        for (int y = -drawSize; y < drawSize; y++)
                        {
                            int width = drawSize - Mathf.Abs(y);

                            for (int x = -width; x < width; x++)
                            {
                                EraseTexture(renderer, textureCoord, new Vector2Int(x, y));
                            }
                        }

                    }
                    else
                    {
                        for (int y = -drawSize; y < drawSize; y++)
                        {
                            int width = drawSize - Mathf.Abs(y);

                            for (int x = -width; x < width; x++)
                            {
                                PaintTexture(renderer, textureCoord, new Vector2Int(x, y));
                            }
                        }
                    }

                    break;

                case DrawMode.Circle:

                    if (isEraser)
                    {
                        for (int y = -drawSize; y < drawSize; y++)
                        {
                            int width = Mathf.CeilToInt(Mathf.Sqrt(drawSize * drawSize - Mathf.Abs(y) * Mathf.Abs(y)));

                            for (int x = -width; x < width; x++)
                            {
                                EraseTexture(renderer, textureCoord, new Vector2Int(x, y));
                            }
                        }

                    }
                    else
                    {
                        for (int y = -drawSize; y < drawSize; y++)
                        {
                            int width = Mathf.CeilToInt(Mathf.Sqrt(drawSize * drawSize - Mathf.Abs(y) * Mathf.Abs(y)));

                            for (int x = -width; x < width; x++)
                            {
                                PaintTexture(renderer, textureCoord, new Vector2Int(x, y));
                            }
                        }
                    }

                    break;
            }
        }
    }

    /// <summary>
    /// Paints the given texture at the given hit point
    /// </summary>
    /// <param name="renderer"></param>
    /// /// <param name="textureCoord"></param>
    private void PaintMainTexture(Renderer renderer, Vector2 textureCoord)
    {
        Texture2D texture = renderer.sharedMaterial.mainTexture as Texture2D;

        Texture2D roughness = renderer.sharedMaterial.GetTexture(roughnessParameter) as Texture2D;

        int x = Mathf.FloorToInt((textureCoord.x + renderer.sharedMaterial.mainTextureOffset.x) * texture.width * renderer.sharedMaterial.mainTextureScale.x);

        int y = Mathf.FloorToInt((textureCoord.y + renderer.sharedMaterial.mainTextureOffset.y) * texture.height * renderer.sharedMaterial.mainTextureScale.y);

        texture.SetPixel(x, y, drawColor);

        if (roughness != null && roughness.isReadable)
        {
            roughness.SetPixel(x, y, new Color(inkRoughness, inkRoughness, inkRoughness, drawColor.a));
        }
    }

    /// <summary>
    /// Paints the given texture at the given hit point offset
    /// </summary>
    /// <param name="renderer"></param>
    /// /// <param name="textureCoord"></param>
    /// /// <param name="offset"></param>
    private void PaintMainTexture(Renderer renderer, Vector2 textureCoord, Vector2Int offset)
    {
        Texture2D texture = renderer.sharedMaterial.mainTexture as Texture2D;

        Texture2D roughness = renderer.sharedMaterial.GetTexture(roughnessParameter) as Texture2D;

        int x = Mathf.FloorToInt((textureCoord.x + renderer.sharedMaterial.mainTextureOffset.x) * texture.width * renderer.sharedMaterial.mainTextureScale.x) + offset.x;

        int y = Mathf.FloorToInt((textureCoord.y + renderer.sharedMaterial.mainTextureOffset.y) * texture.height * renderer.sharedMaterial.mainTextureScale.y) + offset.y;

        texture.SetPixel(x, y, drawColor);

        if (roughness != null && roughness.isReadable)
        {
            roughness.SetPixel(x, y, new Color(inkRoughness, inkRoughness, inkRoughness, drawColor.a));
        }
    }

    /// <summary>
    /// Paints the given texture at the given hit point
    /// </summary>
    /// <param name="renderer"></param>
    /// /// <param name="textureCoord"></param>
    private void PaintTexture(Renderer renderer, Vector2 textureCoord)
    {
        Texture2D texture = renderer.sharedMaterial.GetTexture(textureParameter) as Texture2D;

        Texture2D roughness = renderer.sharedMaterial.GetTexture(roughnessParameter) as Texture2D;

        int x = Mathf.FloorToInt((textureCoord.x + renderer.sharedMaterial.GetTextureOffset(textureParameter).x) * texture.width * renderer.sharedMaterial.GetTextureScale(textureParameter).x);

        int y = Mathf.FloorToInt((textureCoord.y + renderer.sharedMaterial.GetTextureOffset(textureParameter).y) * texture.height * renderer.sharedMaterial.GetTextureScale(textureParameter).y);

        texture.SetPixel(x, y, drawColor);

        if (roughness != null && roughness.isReadable)
        {
            roughness.SetPixel(x, y, new Color(inkRoughness, inkRoughness, inkRoughness, drawColor.a));
        }
    }

    /// <summary>
    /// Paints the given texture at the given hit point offset
    /// </summary>
    /// <param name="renderer"></param>
    /// /// <param name="textureCoord"></param>
    /// /// <param name="offset"></param>
    private void PaintTexture(Renderer renderer, Vector2 textureCoord, Vector2Int offset)
    {
        Texture2D texture = renderer.sharedMaterial.GetTexture(textureParameter) as Texture2D;

        Texture2D roughness = renderer.sharedMaterial.GetTexture(roughnessParameter) as Texture2D;

        int x = Mathf.FloorToInt((textureCoord.x + renderer.sharedMaterial.GetTextureOffset(textureParameter).x) * texture.width * renderer.sharedMaterial.GetTextureScale(textureParameter).x) + offset.x;

        int y = Mathf.FloorToInt((textureCoord.y + renderer.sharedMaterial.GetTextureOffset(textureParameter).y) * texture.height * renderer.sharedMaterial.GetTextureScale(textureParameter).y) + offset.y;

        texture.SetPixel(x, y, drawColor);

        if (roughness != null && roughness.isReadable)
        {
            roughness.SetPixel(x, y, new Color(inkRoughness, inkRoughness, inkRoughness, drawColor.a));
        }
    }

    /// <summary>
    /// Erases the given texture at the given hit point
    /// </summary>
    /// <param name="renderer"></param>
    /// /// <param name="textureCoord"></param>
    private void EraseMainTexture(Renderer renderer, Vector2 textureCoord)
    {
        Texture2D texture = renderer.sharedMaterial.mainTexture as Texture2D;

        Texture2D roughness = renderer.sharedMaterial.GetTexture(roughnessParameter) as Texture2D;

        int x = Mathf.FloorToInt((textureCoord.x + renderer.sharedMaterial.mainTextureOffset.x) * texture.width * renderer.sharedMaterial.mainTextureScale.x);

        int y = Mathf.FloorToInt((textureCoord.y + renderer.sharedMaterial.mainTextureOffset.y) * texture.height * renderer.sharedMaterial.mainTextureScale.y);

        texture.SetPixel(x, y, textures[renderer.gameObject].GetPixel(x, y));

        if (roughness != null && roughness.isReadable)
        {
            roughness.SetPixel(x, y, roughnessTextures[renderer.gameObject].GetPixel(x, y));
        }
    }

    /// <summary>
    /// Erases the given texture at the given hit point offset
    /// </summary>
    /// <param name="renderer"></param>
    /// /// <param name="textureCoord"></param>
    /// /// <param name="offset"></param>
    private void EraseMainTexture(Renderer renderer, Vector2 textureCoord, Vector2Int offset)
    {
        Texture2D texture = renderer.sharedMaterial.mainTexture as Texture2D;

        Texture2D roughness = renderer.sharedMaterial.GetTexture(roughnessParameter) as Texture2D;

        int x = Mathf.FloorToInt((textureCoord.x + renderer.sharedMaterial.mainTextureOffset.x) * texture.width * renderer.sharedMaterial.mainTextureScale.x) + offset.x;

        int y = Mathf.FloorToInt((textureCoord.y + renderer.sharedMaterial.mainTextureOffset.y) * texture.height * renderer.sharedMaterial.mainTextureScale.y) + offset.y;

        texture.SetPixel(x, y, textures[renderer.gameObject].GetPixel(x, y));

        if (roughness != null && roughness.isReadable)
        {
            roughness.SetPixel(x, y, roughnessTextures[renderer.gameObject].GetPixel(x, y));
        }
    }

    /// <summary>
    /// Erases the given texture at the given hit point
    /// </summary>
    /// <param name="renderer"></param>
    /// /// <param name="textureCoord"></param>
    private void EraseTexture(Renderer renderer, Vector2 textureCoord)
    {
        Texture2D texture = renderer.sharedMaterial.GetTexture(textureParameter) as Texture2D;

        Texture2D roughness = renderer.sharedMaterial.GetTexture(roughnessParameter) as Texture2D;

        int x = Mathf.FloorToInt((textureCoord.x + renderer.sharedMaterial.GetTextureOffset(textureParameter).x) * texture.width * renderer.sharedMaterial.GetTextureScale(textureParameter).x);

        int y = Mathf.FloorToInt((textureCoord.y + renderer.sharedMaterial.GetTextureOffset(textureParameter).y) * texture.height * renderer.sharedMaterial.GetTextureScale(textureParameter).y);

        texture.SetPixel(x, y, textures[renderer.gameObject].GetPixel(x, y));

        if (roughness != null && roughness.isReadable)
        {
            roughness.SetPixel(x, y, roughnessTextures[renderer.gameObject].GetPixel(x, y));
        }
    }

    /// <summary>
    /// Erases the given texture at the given hit point offset
    /// </summary>
    /// <param name="renderer"></param>
    /// /// <param name="textureCoord"></param>
    /// /// <param name="offset"></param>
    private void EraseTexture(Renderer renderer, Vector2 textureCoord, Vector2Int offset)
    {
        Texture2D texture = renderer.sharedMaterial.GetTexture(textureParameter) as Texture2D;

        Texture2D roughness = renderer.sharedMaterial.GetTexture(roughnessParameter) as Texture2D;

        int x = Mathf.FloorToInt((textureCoord.x + renderer.sharedMaterial.GetTextureOffset(textureParameter).x) * texture.width * renderer.sharedMaterial.GetTextureScale(textureParameter).x) + offset.x;

        int y = Mathf.FloorToInt((textureCoord.y + renderer.sharedMaterial.GetTextureOffset(textureParameter).y) * texture.height * renderer.sharedMaterial.GetTextureScale(textureParameter).y) + offset.y;

        texture.SetPixel(x, y, textures[renderer.gameObject].GetPixel(x, y));

        if (roughness != null && roughness.isReadable)
        {
            roughness.SetPixel(x, y, roughnessTextures[renderer.gameObject].GetPixel(x, y));
        }
    }

    /// <summary>
    /// Updates the marker based on the current settings
    /// </summary>
    private void UpdateMarker()
    {
        if (renderer == null)
        {
            renderer = GetComponentInChildren<Renderer>();
        }

        renderer.sharedMaterial.SetColor(markerColorParameter, drawColor);

        if (coloredMarkerBodyParts != null && coloredMarkerBodyParts.Count != 0)
        {
            coloredMarkerBodyParts[0].sharedMaterial.SetColor(markerColorParameter, drawColor);
        }

        globalUseMainTexture = useMainTexture;

        globalTextureParameter = textureParameter;

        globalRoughnessParameter = roughnessParameter;
    }

    /// <summary>
    /// Resets the last position of the marker (called on grab)
    /// </summary>
    private void ResetLastPosition()
    {
        lastDrawnPosition = transform.position;
    }


    // GETTERS

    /// <summary>
    /// Gets whether the marker is an eraser
    /// </summary>
    /// <returns></returns>
    public bool IsEraser()
    {
        return isEraser;
    }

    /// <summary>
    /// Gets the marker's draw color
    /// </summary>
    /// <returns></returns>
    public Color GetDrawColor()
    {
        return drawColor;
    }

    /// <summary>
    /// Gets the marker's draw size
    /// </summary>
    /// <returns></returns>
    public int GetDrawSize()
    {
        return drawSize;
    }

    /// <summary>
    /// Gets the marker's draw mode
    /// </summary>
    /// <returns></returns>
    public DrawMode GetDrawMode()
    {
        return drawMode;
    }

    /// <summary>
    /// Returns whether the marker has infinite ink
    /// </summary>
    /// <returns></returns>
    public bool IsInfinite()
    {
        return infiniteInk;
    }

    /// <summary>
    /// Gets the remaining ink of this marker
    /// </summary>
    /// <returns></returns>
    public float GetInk()
    {
        return remainingInk;
    }

    /// <summary>
    /// Gets whether the marker is currently grabbed
    /// </summary>
    /// <returns></returns>
    public bool IsGrabbed()
    {
        return grabSettings.IsGrabbed();
    }

    /// <summary>
    /// Gets whether the marker is currently grabbed in the left hand
    /// </summary>
    /// <returns></returns>
    public bool IsGrabbedLeft()
    {
        return grabSettings.IsGrabbedLeft();
    }

    /// <summary>
    /// Gets whether the marker is currently grabbed in the right hand
    /// </summary>
    /// <returns></returns>
    public bool IsGrabbedRight()
    {
        return grabSettings.IsGrabbedRight();
    }

    /// <summary>
    /// Gets whether the marker is currently being grabbed by the given hand
    /// </summary>
    /// <returns></returns>
    public bool IsGrabbed(bool isRight)
    {
        return isRight ? grabSettings.IsGrabbedRight() : grabSettings.IsGrabbedLeft();
    }


    // SETTERS

    /// <summary>
    /// Sets whether this marker is an eraser
    /// </summary>
    /// <param name="isEraser"></param>
    /// <returns></returns>
    public bool SetEraser(bool isEraser)
    {
        this.isEraser = isEraser;

        UpdateMarker();

        return this.isEraser;
    }

    /// <summary>
    /// Sets the marker's color
    /// </summary>
    /// <param name="newColor"></param>
    /// <returns></returns>
    public Color SetDrawColor(Color newColor)
    {
        drawColor = newColor;

        UpdateMarker();

        return drawColor;
    }

    /// <summary>
    /// Sets the marker's draw size
    /// </summary>
    /// <param name="newSize"></param>
    /// <returns></returns>
    public int SetDrawSize(int newSize)
    {
        drawSize = newSize;

        UpdateMarker();

        return drawSize;
    }

    /// <summary>
    /// Sets the marker's draw mode
    /// </summary>
    /// <param name="newMode"></param>
    /// <returns></returns>
    public DrawMode SetDrawMode(DrawMode newMode)
    {
        drawMode = newMode;

        UpdateMarker();

        return drawMode;
    }

    /// <summary>
    /// Sets whether this marker has infinite ink
    /// </summary>
    /// <param name="isInfinite"></param>
    /// <returns></returns>
    public bool SetInfinite(bool isInfinite)
    {
        infiniteInk = isInfinite;

        return infiniteInk;
    }

    /// <summary>
    /// Sets the remaining ink of this marker
    /// </summary>
    /// <param name="newInk"></param>
    /// <returns></returns>
    public float SetInk(int newInk)
    {
        remainingInk = newInk;

        return remainingInk;
    }


    // HELPER FUNCTIONS

    /// <summary>
    /// Returns the squared distance between two vector 3s
    /// </summary>
    /// <param name="pointA"></param>
    /// <param name="pointB"></param>
    /// <returns></returns>
    private static float DistanceSquared(Vector3 pointA, Vector3 pointB)
    {
        float xDistance = pointA.x - pointB.x;
        float yDistance = pointA.y - pointB.y;
        float zDistance = pointA.z - pointB.z;

        return xDistance * xDistance + yDistance * yDistance + zDistance * zDistance;
    }

    /// <summary>
    /// Resets the given object's texture to before it was drawn on and returns whether it was successful
    /// </summary>
    /// <param name="resetObject"></param>
    /// <returns></returns>
    public static bool ResetTexture(GameObject resetObject)
    {
        if (textures.ContainsKey(resetObject))
        {
            Material material = resetObject.GetComponent<Renderer>().sharedMaterial;

            Graphics.CopyTexture(textures[resetObject], globalUseMainTexture ? material.mainTexture : material.GetTexture(globalTextureParameter));

            textures.Remove(resetObject);

            if (roughnessTextures.ContainsKey(resetObject))
            {
                Graphics.CopyTexture(roughnessTextures[resetObject], material.GetTexture(globalRoughnessParameter));

                roughnessTextures.Remove(resetObject);
            }

            return true;
        }

        return false;
    }

    /// <summary>
    /// Saves the given object's current texture as is (WARNING: THIS IS A PERMANENT CHANGE)
    /// </summary>
    /// <param name="savedObject"></param>
    /// <returns></returns>
    public static bool SaveTexture(GameObject savedObject)
    {
        if (materials.ContainsKey(savedObject))
        {
            Renderer renderer = savedObject.GetComponentInChildren<Renderer>();

            if (globalUseMainTexture)
            {
                Graphics.CopyTexture(renderer.material.mainTexture, materials[savedObject].mainTexture);
            }
            else
            {
                Graphics.CopyTexture(renderer.material.GetTexture(globalTextureParameter), materials[savedObject].GetTexture(globalTextureParameter));
            }

            textures.Remove(savedObject);

            if (roughnessTextures.ContainsKey(savedObject))
            {
                Graphics.CopyTexture(renderer.material.GetTexture(globalRoughnessParameter), materials[savedObject].GetTexture(globalRoughnessParameter));

                roughnessTextures.Remove(savedObject);
            }

            renderer.material = materials[savedObject];

            materials.Remove(savedObject);

            return true;
        }

        return false;
    }
}
