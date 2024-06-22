
// VR Jetpack Locomotion Script
// by Kyle Furey

// REQUIREMENTS: HandTrackerVR.cs, HandGrabbableVR.cs

using UnityEngine;

/// <summary>
/// Creates a grabbable device in front of the player that allows them to freely move in set directions in VR.
/// </summary>
public class JetpackVR : MonoBehaviour, IHandInteractableVR
{
    [Header("Creates a grabbable device in front of the player that allows them to freely move in set directions in VR.")]
    [Header("NOTE: This component requires the player to have a Rigidbody and Collider that does not collide with its other components.")]

    [Header("\nCONFIGURATION")]

    [Header("The camera owned by the player (to keep the control object in sight):")]
    [SerializeField] private Camera camera = null;

    [Header("The rigidbody used to move the player:")]
    [SerializeField] private Rigidbody rigidbody = null;

    [Header("The control object and its HandGrabbableVR script for the jetpack:")]
    [SerializeField] private HandGrabbableVR controlObject = null;

    [Header("\nJETPACK SETTINGS")]

    [Header("Whether the player has the jetpack:")]
    public bool hasJetpack = true;

    [Header("Whether the jetpack can be controlled with both hands:")]
    public bool canGrabLeft = true;
    public bool canGrabRight = true;

    [Header("The directions the player is allowed to move (in world space):")]
    [SerializeField] private bool canMoveX = true;
    [SerializeField] private bool canMoveY = false;
    [SerializeField] private bool canMoveZ = true;

    [Header("The max speed the player can move:")]
    [SerializeField] private float moveSpeed = 0.15f;

    [Header("The speed the control object lerps to the center:")]
    [SerializeField] private float controlObjectLerpSpeed = 5;

    [Header("The offset of the control object relative to the player's camera:")]
    [SerializeField] private Vector3 cameraOffset = new Vector3(0, -0.25f, 0.3f);

    [Header("Whether the control object follows the player's camera:")]
    [SerializeField] private bool followCameraX = true;
    [SerializeField] private bool followCameraY = true;

    [Header("The speed the control object lerps in view of the player:")]
    [SerializeField] private float cameraLerpSpeed = 5;

    [Header("The optional transparent material that this object owns:")]
    [SerializeField] private Material baseMaterial = null;

    [Header("The optional transparent material that the control object owns:")]
    [SerializeField] private Material controlObjectMaterial = null;

    [Header("The distance before fading the materials:")]
    [SerializeField] private float materialFadeDistance = 12.5f;

    /// <summary>
    /// The renderer of this object
    /// </summary>
    private Renderer renderer = null;

    /// <summary>
    /// The renderer of the control object object
    /// </summary>
    private Renderer controlObjectRenderer = null;

    /// <summary>
    /// The current offset of the camera (when grabbed)
    /// </summary>
    private Vector3 currentOffset = Vector3.zero;

    /// <summary>
    /// The starting color of the base material
    /// </summary>
    private Color baseColor = Color.black;

    /// <summary>
    /// The starting emissive color of the base material
    /// </summary>
    private Color baseEmissiveColor = Color.black;

    /// <summary>
    /// The starting color of the control object material
    /// </summary>
    private Color controlObjectColor = Color.black;

    /// <summary>
    /// The starting emissive color of the control object material
    /// </summary>
    private Color controlObjectEmissiveColor = Color.black;

    /// <summary>
    /// IHandInteractableVR Interface - Called when VR hands are successfully set.
    /// </summary>
    public void OnSetHands()
    {
        IHandInteractableVR.implementations.Add(this);
    }

    /// <summary>
    /// IHandInteractableVR Interface - Removes the object's implementation to the interface.
    /// </summary>
    private void OnDestroy()
    {
        IHandInteractableVR.implementations.Remove(this);

        baseMaterial.color = baseColor;

        baseMaterial.SetColor("_EmissionColor", baseEmissiveColor);

        controlObjectMaterial.color = controlObjectColor;

        controlObjectMaterial.SetColor("_EmissionColor", controlObjectEmissiveColor);
    }

    /// <summary>
    /// Sets components and their settings
    /// </summary>
    private void Awake()
    {
        if (IHandInteractableVR.handsSet)
        {
            OnSetHands();
        }

        if (camera == null)
        {
            camera = Camera.main;
        }

        if (rigidbody == null)
        {
            rigidbody = camera.gameObject.GetComponentInParent<Rigidbody>();
        }

        if (controlObject == null)
        {
            controlObject = transform.GetChild(0).GetComponent<HandGrabbableVR>();
        }

        renderer = GetComponent<Renderer>();

        controlObjectRenderer = controlObject.GetComponent<Renderer>();

        transform.parent = null;

        transform.position = TranslateRelative(camera.transform, cameraOffset);

        SetGravity(!canMoveY);

        if (baseMaterial != null)
        {
            baseColor = baseMaterial.color;

            baseEmissiveColor = baseMaterial.GetColor("_EmissionColor");
        }

        if (controlObjectMaterial != null)
        {
            controlObjectColor = controlObjectMaterial.color;

            controlObjectEmissiveColor = controlObjectMaterial.GetColor("_EmissionColor");
        }
    }

    /// <summary>
    /// Moves the rigidbody each physics tick
    /// </summary>
    private void FixedUpdate()
    {
        MovePlayer();
    }

    /// <summary>
    /// Ensures the control object is updated after HandGrabbableVR updates
    /// </summary>
    private void LateUpdate()
    {
        UpdateJetpack();
    }

    /// <summary>
    /// Moves the player by the control object's distance and direction
    /// </summary>
    private void MovePlayer()
    {
        Vector3 speed = (controlObject.transform.position - transform.position) * moveSpeed;

        speed = speed.normalized * speed.magnitude;

        speed.x *= canMoveX ? 1 : 0;
        speed.y *= canMoveY ? 1 : 0;
        speed.z *= canMoveZ ? 1 : 0;

        rigidbody.MovePosition(rigidbody.transform.position + speed);

        if (controlObject.IsGrabbed())
        {
            transform.position = TranslateRelative(rigidbody.transform, currentOffset);
        }
    }

    /// <summary>
    /// Updates the jetpack's control object
    /// </summary>
    private void UpdateJetpack()
    {
        controlObject.grabbableLeft = hasJetpack && canGrabLeft;

        controlObject.grabbableRight = hasJetpack && canGrabRight;

        float distance = Vector3.Distance(controlObject.transform.position, transform.position);

        if (IHandInteractableVR.handsSet)
        {
            if (!controlObject.IsGrabbed())
            {
                ResetControl(distance);

                if (hasJetpack)
                {
                    UpdateMaterialColors();
                }
            }
        }
        else
        {
            ResetControl(distance);
        }
    }

    /// <summary>
    /// Resets the control object to the starting point
    /// </summary>
    private void ResetControl(float distance)
    {
        if (followCameraX || followCameraY)
        {
            Vector3 cameraEulerAngles = camera.transform.eulerAngles;

            if (!followCameraY)
            {
                camera.transform.eulerAngles = new Vector3(0, camera.transform.eulerAngles.y, 0);
            }
            else if (!followCameraX)
            {
                camera.transform.eulerAngles = new Vector3(camera.transform.eulerAngles.x, 0, 0);
            }

            transform.position = Vector3.Lerp(transform.position, TranslateRelative(camera.transform, cameraOffset), Time.deltaTime * cameraLerpSpeed);

            camera.transform.eulerAngles = cameraEulerAngles;
        }
        else
        {
            transform.position = camera.transform.position + cameraOffset;
        }

        transform.LookAt(camera.transform.position);

        transform.Rotate(0, 180, 0);

        currentOffset = transform.position - rigidbody.transform.position;

        controlObject.transform.parent = transform;

        controlObject.transform.localEulerAngles = Vector3.zero;

        controlObject.transform.position = Vector3.Lerp(controlObject.transform.position, transform.position, Time.deltaTime * controlObjectLerpSpeed);

        if (distance <= 0.005f)
        {
            controlObject.transform.localPosition = Vector3.zero;

            if (renderer != null) { renderer.enabled = hasJetpack && IHandInteractableVR.handsSet; }

            if (controlObjectRenderer != null) { controlObjectRenderer.enabled = hasJetpack && IHandInteractableVR.handsSet; }
        }
    }

    /// <summary>
    /// Updates the material colors based on the distance of the hands to here
    /// </summary>
    private void UpdateMaterialColors()
    {
        float leftDistance = DistanceSquared(controlObject.transform.position, HandTrackerVR.leftHand.palm.transform.position) * materialFadeDistance;

        float rightDistance = DistanceSquared(controlObject.transform.position, HandTrackerVR.rightHand.palm.transform.position) * materialFadeDistance;

        float distance = rightDistance < leftDistance ? rightDistance : leftDistance;

        if (baseMaterial != null)
        {
            baseMaterial.color = new Color(Mathf.Max(baseColor.r - distance, 0), Mathf.Max(baseColor.g - distance, 0), Mathf.Max(baseColor.b - distance, 0), Mathf.Max(baseColor.a - distance, 0));

            baseMaterial.SetColor("_EmissionColor", new Color(Mathf.Max(baseEmissiveColor.r - distance, 0), Mathf.Max(baseEmissiveColor.g - distance, 0), Mathf.Max(baseEmissiveColor.b - distance, 0), Mathf.Max(baseEmissiveColor.a - distance, 0)));
        }

        if (controlObjectMaterial != null)
        {
            controlObjectMaterial.color = new Color(Mathf.Max(controlObjectColor.r - distance, 0), Mathf.Max(controlObjectColor.g - distance, 0), Mathf.Max(controlObjectColor.b - distance, 0), Mathf.Max(controlObjectColor.a - distance, 0));

            controlObjectMaterial.SetColor("_EmissionColor", new Color(Mathf.Max(controlObjectEmissiveColor.r - distance, 0), Mathf.Max(controlObjectEmissiveColor.g - distance, 0), Mathf.Max(controlObjectEmissiveColor.b - distance, 0), Mathf.Max(controlObjectEmissiveColor.a - distance, 0)));
        }

        if (renderer != null) { renderer.UpdateGIMaterials(); }

        if (controlObjectRenderer != null) { controlObjectRenderer.UpdateGIMaterials(); }
    }

    /// <summary>
    /// Adjusts the jetpack settings to change Y axis movement (with or without gravity)
    /// </summary>
    /// <param name="useGravity"></param>
    public void SetGravity(bool useGravity)
    {
        canMoveY = !useGravity;

        rigidbody.useGravity = useGravity;
    }

    /// <summary>
    /// Returns an offset vector3 based on the relative transform and given offset vector 3
    /// </summary>
    /// <param name="transform"></param>
    /// <param name="offset"></param>
    /// <returns></returns>
    private static Vector3 TranslateRelative(Transform transform, Vector3 offset)
    {
        Vector3 directionX = transform.right * offset.x;
        Vector3 directionY = transform.up * offset.y;
        Vector3 directionZ = transform.forward * offset.z;

        return transform.position + directionX + directionY + directionZ;
    }

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
}
