
// Static VR Hand Tracking Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

// Inherit from this interface to configure hand tracking functionality with a component.

/// <summary>
/// Indicates interaction with VR hands.
/// Inherit from this interface to configure hand tracking functionality with a component.
/// </summary>
public interface IHandInteractableVR
{
    /// <summary>
    /// A list of all objects that implement this interface. Each new implemented interface should be added to this.
    /// OnSetHands() is automatically called when hands are initialized.
    /// </summary>
    public static List<IHandInteractableVR> implementations = new List<IHandInteractableVR>();

    /// <summary>
    /// Whether the VR hands have been successfully configured.
    /// </summary>
    public static bool handsSet = false;

    /// <summary>
    /// Automatically called when the VR hands are successfully initialized on the implemented interface.
    /// </summary>
    public abstract void OnSetHands();
}

/// <summary>
/// Tracks a player's hands in VR through the hand's joints.
/// </summary>
public class HandTrackerVR : MonoBehaviour, IHandInteractableVR
{
    /// <summary>
    /// The instance of this class
    /// </summary>
    [HideInInspector] public static HandTrackerVR instance;

    /// <summary>
    /// The player's left hand
    /// </summary>
    [HideInInspector] public static HandVR leftHand = null;

    /// <summary>
    /// The player's right hand
    /// </summary>
    [HideInInspector] public static HandVR rightHand = null;

    /// <summary>
    /// The current gestures the left hand is making
    /// </summary>
    [HideInInspector] public static Dictionary<HandVR.Gesture, bool> leftGestures = new Dictionary<HandVR.Gesture, bool>();

    /// <summary>
    /// The current gestures the right hand is making
    /// </summary>
    [HideInInspector] public static Dictionary<HandVR.Gesture, bool> rightGestures = new Dictionary<HandVR.Gesture, bool>();

    [Header("Tracks a player's hands in VR through the hand's joints.")]

    [Header("\nCONFIGURATION")]

    [Header("Whether to set the player's hands on start:")]
    public bool setHandsOnStart = false;

    [Header("The name of the left hand to search for:")]
    public string leftHandName = "Left Hand Object Name";

    [Header("The name of the right hand to search for:")]
    public string rightHandName = "Right Hand Object Name";

    [Header("Whether to add collision to the hands:")]
    public bool addCollision = true;
    public bool collisionIsTrigger = false;

    [Header("Events to call when hands are set:")]
    public UnityEvent onHandsSet = null;

    private void Awake()
    {
        leftHand = null;

        rightHand = null;

        instance = this;

        for (int i = 0; i < System.Enum.GetNames(typeof(HandVR.Gesture)).Length; i++)
        {
            leftGestures[(HandVR.Gesture)i] = false;
            rightGestures[(HandVR.Gesture)i] = false;
        }

        if (setHandsOnStart)
        {
            OnSetHands();
        }
    }

    private void Update()
    {
        // Update the gestures both hands are making
        if (leftHand != null && rightHand != null)
        {
            for (int i = 0; i < System.Enum.GetNames(typeof(HandVR.Gesture)).Length; i++)
            {
                leftGestures[(HandVR.Gesture)i] = leftHand.GetGesture((HandVR.Gesture)i);

                rightGestures[(HandVR.Gesture)i] = rightHand.GetGesture((HandVR.Gesture)i);
            }
        }
    }

    /// <summary>
    /// IHandInteractableVR Interface - Configures and sets the VR hands of each object that has implemented the IHandInteractableVR interface.
    /// </summary>
    public void OnSetHands()
    {
        if (leftHand == null || rightHand == null)
        {
            leftHand = new HandVR(leftHandName, false, addCollision, collisionIsTrigger);

            rightHand = new HandVR(rightHandName, true, addCollision, collisionIsTrigger);

            if (leftHand.hand != null && rightHand.hand != null)
            {
                Debug.Log("Successfully found both hands!");

                IHandInteractableVR.handsSet = true;

                for (int i = 0; i < IHandInteractableVR.implementations.Count; i++)
                {
                    IHandInteractableVR.implementations[i].OnSetHands();
                }

                onHandsSet.Invoke();
            }
            else
            {
                Debug.LogError("Could not find both hands!");
            }
        }
    }

    /// <summary>
    /// Whether the given hand is making the given gesture
    /// </summary>
    /// <param name="gesture"></param>
    /// <param name="isRight"></param>
    /// <returns></returns>
    public static bool GetGesture(HandVR.Gesture gesture, bool isRight)
    {
        if (!isRight)
        {
            return leftGestures[gesture];
        }
        else
        {
            return rightGestures[gesture];
        }
    }
}

/// <summary>
/// Data for an individual hand in VR.
/// </summary>
public class HandVR
{
    /// <summary>
    /// Default constructor
    /// </summary>
    public HandVR()
    {

    }

    /// <summary>
    /// Hand constructor
    /// </summary>
    /// <param name="name"></param>
    /// <param name="isRight"></param>
    /// <param name="addCollision"></param>
    /// <param name="collisionIsTrigger"></param>
    public HandVR(string name, bool isRight, bool addCollision = true, bool collisionIsTrigger = false)
    {
        SetHand(name, isRight, addCollision, collisionIsTrigger);
    }

    // Type of hand
    public bool isRight = false;

    // Hand
    public GameObject hand = null;

    // Wrist
    public GameObject wrist = null;

    // Palm
    public GameObject palm = null;

    // Thumb
    public GameObject thumb = null;
    public GameObject thumbTip = null;

    // Index
    public GameObject index = null;
    public GameObject indexMiddle = null;
    public GameObject indexTip = null;

    // Middle
    public GameObject middle = null;
    public GameObject middleMiddle = null;
    public GameObject middleTip = null;

    // Ring
    public GameObject ring = null;
    public GameObject ringMiddle = null;
    public GameObject ringTip = null;

    // Pinky
    public GameObject pinky = null;
    public GameObject pinkyMiddle = null;
    public GameObject pinkyTip = null;

    // Finger maximum and minimum values (using relative rotation)
    public const float thumbMin = 0; public const float thumbMax = 10;
    public const float fingerMin = 0; public const float fingerMax = 90;

    /// <summary>
    /// Collider dictionary where KEY = FINGER GAME OBJECT and VALUE = FINGER COLLIDER.
    /// Note: colliders[Palm] is a BoxCollider where all other colliders are SphereColliders.
    /// </summary>
    public Dictionary<GameObject, Collider> colliders = new Dictionary<GameObject, Collider>();

    /// <summary>
    /// Rigidbody dictionary where KEY = FINGER GAME OBJECT and VALUE = FINGER RIGIDBODY.
    /// </summary>
    public Dictionary<GameObject, Rigidbody> rigidbodies = new Dictionary<GameObject, Rigidbody>();

    /// <summary>
    /// Finger type enum
    /// </summary>
    public enum Finger { Thumb, Index, Middle, Ring, Pinky };

    /// <summary>
    /// Gesture type enum (add more if needed)
    /// </summary>
    public enum Gesture { Open, Fist, Point, Pinch, ThumbsUp, FingerGun, FlipOff };

    // Sets this hand to a found hand object based on the given name. Make sure the name exactly matches the parent of the intended hand.
    // Note: The hierarchy of joints may also need to be changed depending on your hand prefab.
    public bool SetHand(string name, bool isRight, bool addCollision = true, bool collisionIsTrigger = false)
    {
        GameObject handParent = GameObject.Find(name);

        if (handParent != null)
        {
            this.isRight = isRight;
            Debug.Log((isRight ? "Right" : "Left") + " hand of name " + name + " was found.");

            hand = handParent;
            Debug.Log((isRight ? "Right" : "Left") + " Hand: " + hand.name);

            wrist = handParent.transform.GetChild(0).gameObject;
            Debug.Log((isRight ? "Right" : "Left") + " Wrist: " + wrist.name);

            palm = handParent.transform.GetChild(0).GetChild(3).gameObject;
            Debug.Log((isRight ? "Right" : "Left") + " Palm: " + palm.name);

            thumb = wrist.transform.GetChild(5).transform.GetChild(0).gameObject;
            thumbTip = thumb.transform.GetChild(0).GetChild(0).gameObject;
            Debug.Log((isRight ? "Right" : "Left") + " Thumb: " + thumb.name);

            index = wrist.transform.GetChild(0).transform.GetChild(0).gameObject;
            indexMiddle = index.transform.GetChild(0).gameObject;
            indexTip = indexMiddle.transform.GetChild(0).GetChild(0).gameObject;
            Debug.Log((isRight ? "Right" : "Left") + " Index Finger: " + index.name);

            middle = wrist.transform.GetChild(2).transform.GetChild(0).gameObject;
            middleMiddle = middle.transform.GetChild(0).gameObject;
            middleTip = middleMiddle.transform.GetChild(0).GetChild(0).gameObject;
            Debug.Log((isRight ? "Right" : "Left") + " Middle Finger: " + middle.name);

            ring = wrist.transform.GetChild(4).transform.GetChild(0).gameObject;
            ringMiddle = ring.transform.GetChild(0).gameObject;
            ringTip = ringMiddle.transform.GetChild(0).GetChild(0).gameObject;
            Debug.Log((isRight ? "Right" : "Left") + " Ring Finger: " + ring.name);

            pinky = wrist.transform.GetChild(1).transform.GetChild(0).gameObject;
            pinkyMiddle = pinky.transform.GetChild(0).gameObject;
            pinkyTip = pinkyMiddle.transform.GetChild(0).GetChild(0).gameObject;
            Debug.Log((isRight ? "Right" : "Left") + " Pinky Finger: " + pinky.name);

            if (addCollision)
            {
                GenerateHandCollision(collisionIsTrigger);
            }

            return true;
        }
        else
        {
            Debug.LogError("No hand of name " + name + " was found.");

            return false;
        }
    }

    /// <summary>
    /// Generates collision for the hands
    /// </summary>
    public void GenerateHandCollision(bool isTrigger)
    {
        colliders.Clear();
        rigidbodies.Clear();


        // PALM

        // Palm collider
        BoxCollider boxCollider = palm.AddComponent<BoxCollider>();
        boxCollider.isTrigger = isTrigger;
        boxCollider.providesContacts = false;
        boxCollider.material = null;
        boxCollider.center = new Vector3(0, -0.01f, -0.05f);
        boxCollider.size = new Vector3(0.1f, 0.05f, 0.3f);
        colliders[palm] = boxCollider;

        // Palm rigidbody
        Rigidbody rigidbody = palm.AddComponent<Rigidbody>();
        rigidbody.mass = 1;
        rigidbody.drag = 0;
        rigidbody.angularDrag = 0.05f;
        rigidbody.automaticCenterOfMass = true;
        rigidbody.automaticInertiaTensor = true;
        rigidbody.useGravity = false;
        rigidbody.isKinematic = true;
        rigidbody.interpolation = RigidbodyInterpolation.Interpolate;
        rigidbody.collisionDetectionMode = CollisionDetectionMode.Continuous;
        rigidbodies[palm] = rigidbody;
        palm.layer = 2;


        // THUMB

        // Thumb collider
        SphereCollider sphereCollider = thumbTip.AddComponent<SphereCollider>();
        sphereCollider.isTrigger = isTrigger;
        sphereCollider.providesContacts = false;
        sphereCollider.material = null;
        sphereCollider.center = Vector3.zero;
        sphereCollider.radius = 0.01f;
        colliders[thumb] = sphereCollider;
        thumbTip.layer = 2;

        // Thumb rigidbody
        rigidbody = thumbTip.AddComponent<Rigidbody>();
        rigidbody.mass = 1;
        rigidbody.drag = 0;
        rigidbody.angularDrag = 0.05f;
        rigidbody.automaticCenterOfMass = true;
        rigidbody.automaticInertiaTensor = true;
        rigidbody.useGravity = false;
        rigidbody.isKinematic = true;
        rigidbody.interpolation = RigidbodyInterpolation.Interpolate;
        rigidbody.collisionDetectionMode = CollisionDetectionMode.Continuous;
        rigidbodies[thumb] = rigidbody;
        thumbTip.layer = 2;


        // INDEX

        // Index collider
        sphereCollider = indexTip.AddComponent<SphereCollider>();
        sphereCollider.isTrigger = isTrigger;
        sphereCollider.providesContacts = false;
        sphereCollider.material = null;
        sphereCollider.center = Vector3.zero;
        sphereCollider.radius = 0.01f;
        colliders[index] = sphereCollider;
        indexTip.layer = 2;

        // Index rigidbody
        rigidbody = indexTip.AddComponent<Rigidbody>();
        rigidbody.mass = 1;
        rigidbody.drag = 0;
        rigidbody.angularDrag = 0.05f;
        rigidbody.automaticCenterOfMass = true;
        rigidbody.automaticInertiaTensor = true;
        rigidbody.useGravity = false;
        rigidbody.isKinematic = true;
        rigidbody.interpolation = RigidbodyInterpolation.Interpolate;
        rigidbody.collisionDetectionMode = CollisionDetectionMode.Continuous;
        rigidbodies[index] = rigidbody;
        indexTip.layer = 2;


        // MIDDLE

        // Middle collider
        sphereCollider = middleTip.AddComponent<SphereCollider>();
        sphereCollider.isTrigger = isTrigger;
        sphereCollider.providesContacts = false;
        sphereCollider.material = null;
        sphereCollider.center = Vector3.zero;
        sphereCollider.radius = 0.01f;
        colliders[middle] = sphereCollider;
        middleTip.layer = 2;

        // Middle rigidbody
        rigidbody = middleTip.AddComponent<Rigidbody>();
        rigidbody.mass = 1;
        rigidbody.drag = 0;
        rigidbody.angularDrag = 0.05f;
        rigidbody.automaticCenterOfMass = true;
        rigidbody.automaticInertiaTensor = true;
        rigidbody.useGravity = false;
        rigidbody.isKinematic = true;
        rigidbody.interpolation = RigidbodyInterpolation.Interpolate;
        rigidbody.collisionDetectionMode = CollisionDetectionMode.Continuous;
        rigidbodies[middle] = rigidbody;
        middleTip.layer = 2;


        // RING

        // Ring collider
        sphereCollider = ringTip.AddComponent<SphereCollider>();
        sphereCollider.isTrigger = isTrigger;
        sphereCollider.providesContacts = false;
        sphereCollider.material = null;
        sphereCollider.center = Vector3.zero;
        sphereCollider.radius = 0.01f;
        colliders[ring] = sphereCollider;
        ringTip.layer = 2;

        // Ring rigidbody
        rigidbody = ringTip.AddComponent<Rigidbody>();
        rigidbody.mass = 1;
        rigidbody.drag = 0;
        rigidbody.angularDrag = 0.05f;
        rigidbody.automaticCenterOfMass = true;
        rigidbody.automaticInertiaTensor = true;
        rigidbody.useGravity = false;
        rigidbody.isKinematic = true;
        rigidbody.interpolation = RigidbodyInterpolation.Interpolate;
        rigidbody.collisionDetectionMode = CollisionDetectionMode.Continuous;
        rigidbodies[ring] = rigidbody;
        ringTip.layer = 2;


        // PINKY

        // Pinky collider
        sphereCollider = pinkyTip.AddComponent<SphereCollider>();
        sphereCollider.isTrigger = isTrigger;
        sphereCollider.providesContacts = false;
        sphereCollider.material = null;
        sphereCollider.center = Vector3.zero;
        sphereCollider.radius = 0.01f;
        colliders[pinky] = sphereCollider;
        pinkyTip.layer = 2;

        // Pinky rigidbody
        rigidbody = pinkyTip.AddComponent<Rigidbody>();
        rigidbody.mass = 1;
        rigidbody.drag = 0;
        rigidbody.angularDrag = 0.05f;
        rigidbody.automaticCenterOfMass = true;
        rigidbody.automaticInertiaTensor = true;
        rigidbody.useGravity = false;
        rigidbody.isKinematic = true;
        rigidbody.interpolation = RigidbodyInterpolation.Interpolate;
        rigidbody.collisionDetectionMode = CollisionDetectionMode.Continuous;
        rigidbodies[pinky] = rigidbody;
        pinkyTip.layer = 2;
    }

    // Returns the percentage of a finger's value based on their maximums and minimums. 1 = finger pointing outward, 0 = finger pointing inward.
    // Note: You may need to adjust the minimum and maximum constants Depending on your hand prefab.
    public float GetFinger(Finger finger)
    {
        switch (finger)
        {
            default:

                return 0;

            case Finger.Thumb:

                if (thumb.transform.localRotation.eulerAngles.x > 350)
                {
                    return 1;
                }

                return 1 - Percentage(thumb.transform.localRotation.eulerAngles.x, thumbMin, thumbMax);

            case Finger.Index:

                if (indexMiddle.transform.localRotation.eulerAngles.x > 350)
                {
                    return 1;
                }

                return 1 - Percentage(indexMiddle.transform.localRotation.eulerAngles.x, fingerMin, fingerMax);

            case Finger.Middle:

                if (middleMiddle.transform.localRotation.eulerAngles.x > 350)
                {
                    return 1;
                }

                return 1 - Percentage(middleMiddle.transform.localRotation.eulerAngles.x, fingerMin, fingerMax);

            case Finger.Ring:

                if (ringMiddle.transform.localRotation.eulerAngles.x > 350)
                {
                    return 1;
                }

                return 1 - Percentage(ringMiddle.transform.localRotation.eulerAngles.x, fingerMin, fingerMax);

            case Finger.Pinky:

                if (pinkyMiddle.transform.localRotation.eulerAngles.x > 350)
                {
                    return 1;
                }

                return 1 - Percentage(pinkyMiddle.transform.localRotation.eulerAngles.x, fingerMin, fingerMax);
        }
    }

    // Returns if the hand matches the selected gesture. Add more gestures if needed.
    // Note: You may need to adjust the values that check the gesture for accuracy and leniency.
    public bool GetGesture(Gesture gesture)
    {
        float thumb = GetFinger(Finger.Thumb);
        float index = GetFinger(Finger.Index);
        float middle = GetFinger(Finger.Middle);
        float ring = GetFinger(Finger.Ring);
        float pinky = GetFinger(Finger.Pinky);

        switch (gesture)
        {
            default:

                Debug.LogError("Gesture " + System.Enum.GetName(typeof(Gesture), gesture) + " is not defined.");

                return false;

            case Gesture.Open:

                return (thumb >= 0.7f) && (index >= 0.7f) && (middle >= 0.7f) && (ring >= 0.7f) && (pinky >= 0.7f);

            case Gesture.Fist:

                return (thumb < 0.4f) && (index < 0.4f) && (middle < 0.4f) && (ring < 0.4f) && (pinky < 0.4f);

            case Gesture.Point:

                return (index >= 0.7f) && (middle < 0.4f) && (ring < 0.4f) && (pinky < 0.4f);

            case Gesture.Pinch:

                return DistanceSquared(TranslateRelative(indexTip.transform, new Vector3(0, -0.005f, 0.017f)), TranslateRelative(thumbTip.transform, new Vector3(0, -0.0045f, 0.008f))) < 0.0005f;

            case Gesture.ThumbsUp:

                return (thumb >= 0.7f) && (index < 0.4f) && (middle < 0.4f) && (ring < 0.4f) && (pinky < 0.4f);

            case Gesture.FingerGun:

                return (thumb >= 0.7f) && (index >= 0.7f) && (middle < 0.4f) && (ring < 0.4f) && (pinky < 0.4f);

            case Gesture.FlipOff:

                return (index < 0.4f) && (middle >= 0.7f) && (ring < 0.4f) && (pinky < 0.4f);
        }
    }

    /// <summary>
    /// Returns a percentage relative to a value of a minimum and maximum
    /// </summary>
    /// <param name="value"></param>
    /// <param name="min"></param>
    /// <param name="max"></param>
    /// <returns></returns>
    private static float Percentage(float value, float min, float max)
    {
        return (value - min) / (max - min);
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

    /// <summary>
    /// Returns an offset vector3 based on the relative transform and given offset values
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
}
