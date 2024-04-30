
// Simple VR Slingshot Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

// Creates a simple slingshot for use in VR.
public class SlingshotVR : MonoBehaviour
{
    [Header("Creates a simple slingshot for use in VR.")]

    [Header("SLINGSHOT SETTINGS")]

    [Header("Whether the player has the slingshot:")]
    [SerializeField] private bool hasSlingshot = true;

    // The hand game objects
    [HideInInspector] public GameObject leftHand = null;
    [HideInInspector] public GameObject rightHand = null;

    [Header("The pivots of the player's tracked hands:")]
    public GameObject leftHandPivot = null;
    public GameObject rightHandPivot = null;

    [Header("The offset position and rotation to add to the hand's position and rotation:")]
    [SerializeField] private Vector3 offsetPosition = new Vector3(0, -0.05f, 0.1f);
    [SerializeField] private Vector3 offsetRotation = new Vector3(-10, 0, -90);

    // Whether the player's hands are currently in a pinching state
    private bool isPinchingRight = false;
    private bool onPinchRight = false;
    private bool isPinchingLeft = false;
    private bool onPinchLeft = false;

    [Header("The object being slung from the slingshot:")]
    [SerializeField] private GameObject slungPrefab = null;
    private Rigidbody slungRigidbody = null;
    [SerializeField] private Vector3 shootOffset = new Vector3(0, 0.15f, 0.1f);

    // The current state of the slingshot
    private SlingshotState slingshotState = SlingshotState.Unloaded;

    [Header("Settings for pinching:")]
    [SerializeField] private bool pinchWithLeftHand = true;
    [SerializeField] private bool pinchWithRightHand = true;
    [SerializeField] private bool mustPinchWithOneHand = true;
    [SerializeField] private float pinchGrabDistance = 0.1f;
    [SerializeField] private float pinchReleaseDistance = 0.65f;

    [Header("Velocity settings:")]
    [SerializeField] private float slingshotMultiplier = 20;
    [SerializeField] private bool slingByCharge = false;
    [SerializeField] private bool lerpCharge = false;
    [SerializeField] private float chargeSpeed = 2.5f;
    private bool slideUp = true;

    [Header("The number of objects to spawn before replacing the oldest object:")]
    [SerializeField] private bool capSlungObjects = true;
    [SerializeField] private int maxNumberOfSlungObjects = 10;
    private Queue<GameObject> slungObjects = new Queue<GameObject>();

    [Header("SLINGSHOT UI")]

    [Header("Slingshot and crosshair object settings:")]
    [SerializeField] private GameObject slingshot = null;
    [SerializeField] private GameObject crosshair = null;
    [SerializeField] private bool fixedCrosshair = false;
    [SerializeField] private float crosshairScale = 2;

    [Header("The slider and its components indicating when the player is using the slingshot:")]
    [SerializeField] private Slider slider = null;
    [SerializeField] private List<Image> sliderImages = new List<Image>();
    [SerializeField] private float sliderFadeSpeed = 1500;
    [SerializeField] private Vector3 sliderOffset = new Vector3(0, -0.1f, -0.15f);

    // The current slingshot state
    public enum SlingshotState { Unloaded, LoadedRight, LoadedLeft };

    // Set this object's hands
    public void SetHands()
    {
        leftHand = HandTrackerVR.leftHand.wrist;

        leftHandPivot.transform.parent = leftHand.transform;

        rightHand = HandTrackerVR.rightHand.wrist;

        rightHandPivot.transform.parent = rightHand.transform;
    }

    private void Start()
    {
        leftHand = null;

        rightHand = null;

        // Disable slingshot and crosshair
        slingshot.active = false;

        crosshair.active = false;
    }

    private void Update()
    {
        // Check the player's hands
        if (leftHand != null && rightHand != null)
        {
            // PINCHING INPUT

            onPinchLeft = !isPinchingLeft;

            isPinchingLeft = HandTrackerVR.GetGesture(HandVR.Gesture.Pinch, false);

            onPinchRight = !isPinchingRight;

            isPinchingRight = HandTrackerVR.GetGesture(HandVR.Gesture.Pinch, true);


            // OFFSET HANDS

            leftHandPivot.transform.localPosition = offsetPosition;

            leftHandPivot.transform.localEulerAngles = offsetRotation;

            rightHandPivot.transform.localPosition = offsetPosition;

            rightHandPivot.transform.localEulerAngles = -offsetRotation;


            // SLINGSHOT

            // Slingshot logic based on slingshot state
            if (hasSlingshot)
            {
                if (slingshotState == SlingshotState.Unloaded)
                {
                    // Loading slingshot by pinching
                    if (pinchWithRightHand && isPinchingRight && onPinchRight)
                    {
                        if (!mustPinchWithOneHand || !isPinchingLeft)
                        {
                            // Pinching with right hand
                            if (PinchCheck(rightHandPivot, leftHandPivot))
                            {
                                // Loading the slingshot
                                LoadSlingshot(rightHandPivot, true);

                                AimSlingshot(rightHandPivot, leftHandPivot);
                            }
                        }
                    }
                    else if (pinchWithLeftHand && isPinchingLeft && onPinchLeft)
                    {
                        if (!mustPinchWithOneHand || !isPinchingRight)
                        {
                            // Pinching with left hand
                            if (PinchCheck(leftHandPivot, rightHandPivot))
                            {
                                // Loading the slingshot
                                LoadSlingshot(leftHandPivot, false);

                                AimSlingshot(leftHandPivot, rightHandPivot);
                            }
                        }
                    }

                    // Fade the slider out
                    for (int i = 0; i < sliderImages.Count; i++)
                    {
                        sliderImages[i].color = new Vector4(sliderImages[i].color.r, sliderImages[i].color.g, sliderImages[i].color.b, Mathf.Min(sliderImages[i].color.a - (sliderFadeSpeed * Time.deltaTime / 255), 1));
                    }
                }
                else if (slingshotState == SlingshotState.LoadedRight)
                {
                    if (isPinchingRight)
                    {
                        // Aiming slingshot (right moving towards left)
                        AimSlingshot(rightHandPivot, leftHandPivot);
                    }
                    else
                    {
                        // Shooting slingshot (right moving towards left)
                        ShootSlingshot(rightHandPivot, leftHandPivot);
                    }

                    UpdateSlider(leftHandPivot);
                }
                else
                {
                    if (isPinchingLeft)
                    {
                        // Aiming slingshot (left moving towards right)
                        AimSlingshot(leftHandPivot, rightHandPivot);
                    }
                    else
                    {
                        // Shooting slingshot (left moving towards right)
                        ShootSlingshot(leftHandPivot, rightHandPivot);
                    }

                    UpdateSlider(rightHandPivot);
                }
            }
            else if (slungRigidbody != null)
            {
                slingshotState = SlingshotState.Unloaded;

                slingshot.active = false;

                crosshair.active = false;

                Destroy(slungRigidbody.gameObject);

                for (int i = 0; i < sliderImages.Count; i++)
                {
                    sliderImages[i].color = new Vector4(sliderImages[i].color.r, sliderImages[i].color.g, sliderImages[i].color.b, 0);
                }
            }
        }
    }

    // Returns an offset vector3 based on the relative transform and given offset values
    private static Vector3 TranslateRelative(Transform transform, Vector3 offset)
    {
        Vector3 directionX = transform.right * offset.x;
        Vector3 directionY = transform.up * offset.y;
        Vector3 directionZ = transform.forward * offset.z;

        return transform.position + directionX + directionY + directionZ;
    }

    // Returns the squared distance between two vector 3s
    public static float DistanceSquared(Vector3 pointA, Vector3 pointB)
    {
        float xDistance = pointA.x - pointB.x;
        float yDistance = pointA.y - pointB.y;
        float zDistance = pointA.z - pointB.z;

        return xDistance * xDistance + yDistance * yDistance + zDistance * zDistance;
    }

    // Whether the player pinching is within range of using the slingshot
    private bool PinchCheck(GameObject pinchHand, GameObject aimHand)
    {
        return DistanceSquared(pinchHand.transform.position, aimHand.transform.position) <= pinchGrabDistance * pinchGrabDistance;
    }

    // Creating the slingshot object
    private void LoadSlingshot(GameObject pinchHand, bool loadRight)
    {
        GameObject slungObject = Instantiate(slungPrefab);

        slungObject.transform.position = pinchHand.transform.position;

        slungRigidbody = slungObject.GetComponent<Rigidbody>();

        slungRigidbody.useGravity = false;

        slingshot.active = true;

        crosshair.active = true;

        if (loadRight)
        {
            slingshotState = SlingshotState.LoadedRight;
        }
        else
        {
            slingshotState = SlingshotState.LoadedLeft;
        }
    }

    // Updating slider value and color
    private void UpdateSlider(GameObject aimHand)
    {
        // Slider color
        ColorBlock sliderColor = new ColorBlock();

        if (slider.value >= 0.66f)
        {
            sliderColor.normalColor = Color.red;
            sliderColor.highlightedColor = Color.red;
            sliderColor.pressedColor = Color.red;
            sliderColor.selectedColor = Color.red;
            sliderColor.disabledColor = Color.red;
        }
        else if (slider.value >= 0.33f)
        {
            sliderColor.normalColor = Color.yellow;
            sliderColor.highlightedColor = Color.yellow;
            sliderColor.pressedColor = Color.yellow;
            sliderColor.selectedColor = Color.yellow;
            sliderColor.disabledColor = Color.yellow;
        }
        else
        {
            sliderColor.normalColor = Color.green;
            sliderColor.highlightedColor = Color.green;
            sliderColor.pressedColor = Color.green;
            sliderColor.selectedColor = Color.green;
            sliderColor.disabledColor = Color.green;
        }

        sliderColor.colorMultiplier = 1;

        slider.colors = sliderColor;

        // Fade the slider in
        for (int i = 0; i < sliderImages.Count; i++)
        {
            sliderImages[i].color = new Vector4(sliderImages[i].color.r, sliderImages[i].color.g, sliderImages[i].color.b, Mathf.Max(sliderImages[i].color.a + (sliderFadeSpeed * Time.deltaTime / 255), 0));
        }

        // Move the slider UI to the slingshot
        slider.transform.position = TranslateRelative(aimHand.transform, shootOffset);

        slider.transform.eulerAngles = aimHand.transform.eulerAngles;

        slider.transform.position = TranslateRelative(slider.transform, sliderOffset);
    }

    // Aiming the slingshot
    private void AimSlingshot(GameObject pinchHand, GameObject aimHand)
    {
        float distance = Vector3.Distance(pinchHand.transform.position, TranslateRelative(aimHand.transform, shootOffset));

        slungRigidbody.transform.position = TranslateRelative(aimHand.transform, shootOffset);

        slungRigidbody.transform.LookAt(pinchHand.transform.position);

        slungRigidbody.transform.position = TranslateRelative(slungRigidbody.transform, new Vector3(0, 0, Mathf.Min(distance, pinchReleaseDistance)));

        slungRigidbody.transform.LookAt(TranslateRelative(aimHand.transform, shootOffset));

        crosshair.transform.position = TranslateRelative(aimHand.transform, shootOffset);

        crosshair.transform.LookAt(pinchHand.transform.position);

        slungRigidbody.velocity = Vector3.zero;

        slungRigidbody.angularVelocity = Vector3.zero;

        slingshot.transform.position = aimHand.transform.position;

        slingshot.transform.eulerAngles = aimHand.transform.eulerAngles;

        if (!slingByCharge)
        {
            // Calculate the power of the shot based on the distance from the slingshot
            slider.value = Mathf.Min(distance / pinchReleaseDistance, 1);

            if (!fixedCrosshair)
            {
                crosshair.transform.position = TranslateRelative(crosshair.transform, new Vector3(0, 0, -Mathf.Min(distance, pinchReleaseDistance) * crosshairScale));
            }
            else
            {
                crosshair.transform.position = TranslateRelative(crosshair.transform, new Vector3(0, 0, -pinchReleaseDistance * crosshairScale));
            }
        }
        else
        {
            // Calculate the power of the shot based on time
            if (slideUp)
            {
                if (lerpCharge)
                {
                    slider.value = Mathf.Lerp(slider.value, 1, chargeSpeed * Time.deltaTime);
                }
                else
                {
                    slider.value = Mathf.MoveTowards(slider.value, 1, chargeSpeed * Time.deltaTime);
                }

                if (slider.value + 0.05f >= 1)
                {
                    slideUp = false;
                }
            }
            else
            {
                if (lerpCharge)
                {
                    slider.value = Mathf.Lerp(slider.value, 0, chargeSpeed * Time.deltaTime);
                }
                else
                {
                    slider.value = Mathf.MoveTowards(slider.value, 0, chargeSpeed * Time.deltaTime);
                }

                if (slider.value - 0.05f <= 0)
                {
                    slideUp = true;
                }
            }

            if (!fixedCrosshair)
            {
                crosshair.transform.position = TranslateRelative(crosshair.transform, new Vector3(0, 0, -pinchReleaseDistance * crosshairScale * slider.value));
            }
            else
            {
                crosshair.transform.position = TranslateRelative(crosshair.transform, new Vector3(0, 0, -pinchReleaseDistance * crosshairScale));
            }
        }
    }

    // Returns the direction between two vector 3s
    private static Vector3 Direction(Vector3 pointA, Vector3 pointB)
    {
        return pointB - pointA;
    }

    // Shooting the slingshot
    private void ShootSlingshot(GameObject pinchHand, GameObject aimHand)
    {
        AimSlingshot(pinchHand, aimHand);

        if (!slingByCharge)
        {
            // Shoot the slingshot based on the distance to the slingshot
            slungRigidbody.velocity = Direction(slungRigidbody.transform.position, TranslateRelative(aimHand.transform, shootOffset)) * slingshotMultiplier;
        }
        else
        {
            // Shoot the slingshot based on when the slingshot was charged
            slungRigidbody.velocity = Direction(slungRigidbody.transform.position, TranslateRelative(aimHand.transform, shootOffset)).normalized * pinchReleaseDistance * slingshotMultiplier * slider.value;
        }

        slungRigidbody.useGravity = true;

        slungRigidbody.collisionDetectionMode = CollisionDetectionMode.Continuous;

        slungObjects.Enqueue(slungRigidbody.gameObject);

        while (slungObjects.Count > maxNumberOfSlungObjects)
        {
            Destroy(slungObjects.Dequeue());
        }

        slungRigidbody = null;

        slingshot.active = false;

        crosshair.active = false;

        slingshotState = SlingshotState.Unloaded;
    }
}
