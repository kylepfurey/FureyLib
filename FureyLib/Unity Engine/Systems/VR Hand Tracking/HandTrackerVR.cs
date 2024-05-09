
// Static VR Hand Tracking Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine.Events;
using UnityEngine;

/// <summary>
/// Tracks a player's hands in VR through the hand's joints.
/// </summary>
public class HandTrackerVR : MonoBehaviour
{
    [Header("Tracks a player's hands in VR through the hand's joints.")]

    // The instance of this class
    [HideInInspector] public static HandTrackerVR Instance;

    // The player's left hand
    [HideInInspector] public static HandVR leftHand = null;

    // The player's right hand
    [HideInInspector] public static HandVR rightHand = null;

    // The current gestures the left hand is making
    [HideInInspector] public static Dictionary<HandVR.Gesture, bool> leftGestures = new Dictionary<HandVR.Gesture, bool>();

    // The current gestures the right hand is making
    [HideInInspector] public static Dictionary<HandVR.Gesture, bool> rightGestures = new Dictionary<HandVR.Gesture, bool>();

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
    public UnityEvent onHandSet = null;

    private void Awake()
    {
        leftHand = null;

        rightHand = null;

        Instance = this;

        for (int i = 0; i < System.Enum.GetNames(typeof(HandVR.Gesture)).Length; i++)
        {
            leftGestures[(HandVR.Gesture)i] = false;
            rightGestures[(HandVR.Gesture)i] = false;
        }

        if (setHandsOnStart)
        {
            SetHands();
        }
    }

    // Sets the left and right hand
    public void SetHands()
    {
        if (leftHand == null || rightHand == null)
        {
            leftHand = new HandVR(leftHandName, false, addCollision, collisionIsTrigger);

            rightHand = new HandVR(rightHandName, true, addCollision, collisionIsTrigger);

            if (leftHand.hand != null && rightHand.hand != null)
            {
                Debug.Log("Successfully found both hands!");

                onHandSet.Invoke();
            }
            else
            {
                Debug.LogError("Could not find both hands!");
            }
        }
    }

    // Whether the given hand is making the given gesture
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
}

/// <summary>
/// Data for an individual hand in VR.
/// </summary>
public class HandVR
{
    // Constructor
    public HandVR()
    {

    }

    // Constructor
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

    // Collision
    public CapsuleCollider collider = null;
    public Rigidbody rigidbody = null;

    // Finger maximum and minimum values (using relative rotation)
    public const float thumbMin = 0; public const float thumbMax = 10;
    public const float fingerMin = 0; public const float fingerMax = 90;

    // Finger type enum
    public enum Finger { Thumb, Index, Middle, Ring, Pinky };

    // Gesture type enum (add more if needed)
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
            thumbTip = thumb.transform.GetChild(0).gameObject;
            Debug.Log((isRight ? "Right" : "Left") + " Thumb: " + thumb.name);

            index = wrist.transform.GetChild(0).transform.GetChild(0).gameObject;
            indexMiddle = index.transform.GetChild(0).gameObject;
            indexTip = indexMiddle.transform.GetChild(0).gameObject;
            Debug.Log((isRight ? "Right" : "Left") + " Index Finger: " + index.name);

            middle = wrist.transform.GetChild(2).transform.GetChild(0).gameObject;
            middleMiddle = middle.transform.GetChild(0).gameObject;
            middleTip = middleMiddle.transform.GetChild(0).gameObject;
            Debug.Log((isRight ? "Right" : "Left") + " Middle Finger: " + middle.name);

            ring = wrist.transform.GetChild(4).transform.GetChild(0).gameObject;
            ringMiddle = ring.transform.GetChild(0).gameObject;
            ringTip = ringMiddle.transform.GetChild(0).gameObject;
            Debug.Log((isRight ? "Right" : "Left") + " Ring Finger: " + ring.name);

            pinky = wrist.transform.GetChild(1).transform.GetChild(0).gameObject;
            pinkyMiddle = pinky.transform.GetChild(0).gameObject;
            pinkyTip = pinkyMiddle.transform.GetChild(0).gameObject;
            Debug.Log((isRight ? "Right" : "Left") + " Pinky Finger: " + pinky.name);

            collider = palm.AddComponent<CapsuleCollider>();
            collider.isTrigger = collisionIsTrigger;
            collider.providesContacts = false;
            collider.sharedMaterial = null;
            collider.center = new Vector3(0, 0, -0.1f);
            collider.radius = 0.05f;
            collider.height = 0.4f;
            collider.direction = 2;

            rigidbody = palm.AddComponent<Rigidbody>();
            rigidbody.mass = 1;
            rigidbody.drag = 0;
            rigidbody.angularDrag = 0.05f;
            rigidbody.automaticCenterOfMass = true;
            rigidbody.automaticInertiaTensor = true;
            rigidbody.useGravity = false;
            rigidbody.isKinematic = true;
            rigidbody.interpolation = RigidbodyInterpolation.Interpolate;
            rigidbody.collisionDetectionMode = CollisionDetectionMode.Continuous;

            if (!addCollision)
            {
                collider.enabled = false;

                rigidbody.detectCollisions = false;
            }

            return true;
        }
        else
        {
            Debug.LogError("No hand of name " + name + " was found.");

            return false;
        }
    }

    // Returns a percentage relative to a value of a minimum and maximum
    private static float Percentage(float value, float min, float max)
    {
        return (value - min) / (max - min);
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

    // Returns the squared distance between two vector 3s
    private static float DistanceSquared(Vector3 pointA, Vector3 pointB)
    {
        float xDistance = pointA.x - pointB.x;
        float yDistance = pointA.y - pointB.y;
        float zDistance = pointA.z - pointB.z;

        return xDistance * xDistance + yDistance * yDistance + zDistance * zDistance;
    }

    // Returns an offset vector3 based on the relative transform and given offset values
    private static Vector3 TranslateRelative(Transform transform, Vector3 offset)
    {
        Vector3 directionX = transform.right * offset.x;
        Vector3 directionY = transform.up * offset.y;
        Vector3 directionZ = transform.forward * offset.z;

        return transform.position + directionX + directionY + directionZ;
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
}
