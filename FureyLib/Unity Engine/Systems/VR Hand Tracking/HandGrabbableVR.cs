
// VR Grabbable Object Script
// by Kyle Furey

// REQUIREMENTS: HandTrackerVR.cs

using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

/// <summary>
/// Allows this game object to be picked up and thrown when in range of a VR hand.
/// </summary>
public class HandGrabbableVR : MonoBehaviour, IHandInteractableVR
{
    [Header("Allows this game object to be picked up and possibly thrown when in range.")]

    [Header("\nGRABBING")]

    [Header("Whether this object is grabbable:")]
    public bool grabbableLeft = true;
    public bool grabbableRight = true;

    [Header("The maximum distance to this object where it can be grabbed:")]
    [SerializeField] private float grabDistance = 0.25f;

    [Header("The offset for grabbed objects:")]
    [SerializeField] private Vector3 grabPositionOffset = new Vector3(0, -0.07f, 0.07f);
    [SerializeField] private bool rotationOffset = false;
    [SerializeField] private Vector3 leftRotationOffset = new Vector3(0, 0, 0);
    [SerializeField] private Vector3 rightRotationOffset = new Vector3(0, 0, 0);

    [Header("The maximum time the player can be grabbing to grab this item:")]
    [SerializeField] private float grabBuffer = 0.5f;

    [Header("The gestures allowed to be used to grab this item:")]
    [SerializeField] private List<HandVR.Gesture> allowedGestures = new List<HandVR.Gesture>() { HandVR.Gesture.Fist };

    [Header("Whether to apply rigidbody physics while the object is held:")]
    [SerializeField] private bool grabPhysics = true;

    [Header("Whether to assign a rigidbody when this object is let go of:")]
    [SerializeField] private bool assignRigidbody = true;

    [Header("Whether to keep the old gravity setting when this object is let go of:")]
    [SerializeField] private bool keepGravitySetting = true;

    [Header("The new gravity setting for this object if it is not keeping its old gravity setting:")]
    [SerializeField] private bool newGravity = true;

    [Header("Whether the held object is locked in one of the player's hands when grabbed:")]
    [SerializeField] private bool isLocked = false;

    [Header("\nTHROWING")]

    [Header("Whether this object can be thrown by the player:")]
    public bool throwable = true;

    [Header("The scale applied to thrown object's velocity:")]
    [SerializeField] private float thrownScale = 10;
    [SerializeField] private VelocityScaleType velocityScalingType = VelocityScaleType.Direction;

    [Header("The buffer time before updating the object's previous position:")]
    [SerializeField] private float previousPositionDelay = 0.5f;

    [Header("The offset applied to this thrown object's direction:")]
    [SerializeField] private Vector3 thrownOffset = new Vector3(0, 0, 20);

    [Header("The delay before reenabling collision for the player's hands (to prevent the hands bumping the object):")]
    [SerializeField] private float collisionDelay = 0.5f;

    [Header(":")]

    [Header("\nEVENTS")]

    [Header("Events for when this object is grabbed, dropped, or thrown:")]
    public UnityEvent onGrab = null;
    public UnityEvent onDrop = null;
    public UnityEvent onThrow = null;

    /// <summary>
    /// Velocity scaling enum
    /// </summary>
    public enum VelocityScaleType { Direction, Distance, DistanceSquared };

    // Whether the player's hands are currently occupied
    private static GameObject heldLeftObject = null;
    private static GameObject heldRightObject = null;

    /// <summary>
    /// The current object held in the left hand
    /// </summary>
    public static GameObject heldLeft
    {
        get { return heldLeftObject; }
    }

    /// <summary>
    /// The current object held in the right hand
    /// </summary>
    public static GameObject heldRight
    {
        get { return heldRightObject; }
    }

    // The time the player has been grabbing with each hand
    private bool grabbingLeft = false;
    private float leftGrabTime = 0;
    private bool grabbingRight = false;
    private float rightGrabTime = 0;

    /// <summary>
    /// The rigidbody of the grabbed object
    /// </summary>
    private Rigidbody rigidbody = null;

    /// <summary>
    /// The setting for gravity of this object
    /// </summary>
    private bool gravitySetting = true;

    /// <summary>
    /// The time since last updating the previous position
    /// </summary>
    private float previousPositionUpdateTime = 0;

    /// <summary>
    /// The current previous position of this object
    /// </summary>
    private Vector3 previousPosition = Vector3.zero;


    // FUNCTIONS

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

        // Get rigidbody
        rigidbody = GetComponent<Rigidbody>();

        // Update our previous position
        previousPosition = transform.position;
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

        if (heldLeft == gameObject)
        {
            heldLeftObject = null;
        }

        if (heldRight == gameObject)
        {
            heldRightObject = null;
        }
    }

    /// <summary>
    /// Drops the object on disable
    /// </summary>
    private void OnDisable()
    {
        if (heldLeft == gameObject)
        {
            heldLeftObject = null;
        }

        if (heldRight == gameObject)
        {
            heldRightObject = null;
        }
    }

    /// <summary>
    /// Call the hand grabbing functions
    /// </summary>
    private void Update()
    {
        // Check the player's hands
        if (IHandInteractableVR.handsSet)
        {
            // Grabbing with left hand
            Grab(false);

            // Grabbing with right hand
            Grab(true);

            // Increment grab time for left hand
            GrabTime(false);

            // Increment grab time for right hand
            GrabTime(true);

            // Update our previous position
            previousPositionUpdateTime += Time.deltaTime;

            if (previousPositionUpdateTime >= previousPositionDelay)
            {
                previousPosition = transform.position;
                previousPositionUpdateTime -= previousPositionDelay;
            }
        }
    }

    /// <summary>
    /// Increment or reset grab time
    /// </summary>
    /// <param name="isRight"></param>
    private void GrabTime(bool isRight)
    {
        // Loop through all the allowed gestures
        foreach (HandVR.Gesture gesture in allowedGestures)
        {
            // Check if that gesture is currently active
            if (selectref(isRight, ref HandTrackerVR.rightGestures, ref HandTrackerVR.leftGestures)[gesture])
            {
                // Add to the grab time
                selectref(isRight, ref rightGrabTime, ref leftGrabTime) += Time.deltaTime;

                selectref(isRight, ref grabbingRight, ref grabbingLeft) = true;

                return;
            }
        }

        // Reset the grab time
        selectref(isRight, ref rightGrabTime, ref leftGrabTime) = 0;

        selectref(isRight, ref grabbingRight, ref grabbingLeft) = false;
    }

    /// <summary>
    /// Grabbing the object
    /// </summary>
    /// <param name="isRight"></param>
    private void Grab(bool isRight)
    {
        // Check if the player is grabbing something
        if (selectref(isRight, ref heldRightObject, ref heldLeftObject) == null && selectref(isRight, ref heldLeftObject, ref heldRightObject) != gameObject)
        {
            // Check if the object is grabbable, if the hand is within grab distance of this object, if the grab time is within the grab buffer, and that the player is currently gesturing
            if (selectref(isRight, ref grabbableRight, ref grabbableLeft) && DistanceSquared(transform.position, selectref(isRight, ref HandTrackerVR.rightHand.palm, ref HandTrackerVR.leftHand.palm).transform.position) <= grabDistance * grabDistance && selectref(isRight, ref rightGrabTime, ref leftGrabTime) <= grabBuffer && selectref(isRight, ref grabbingRight, ref grabbingLeft))
            {
                // Set this hand's grabbed object to this
                selectref(isRight, ref heldRightObject, ref heldLeftObject) = gameObject;

                // Check if the rigidbody exists 
                if (rigidbody != null)
                {
                    gravitySetting = rigidbody.useGravity;

                    rigidbody.useGravity = false;
                }

                // Invoke the grab event
                onGrab.Invoke();
            }
        }
        else if (selectref(isRight, ref heldRightObject, ref heldLeftObject) == gameObject)
        {
            // Check if the player is no longer grabbing the object, if they can no longer grab, or if the object is out of reach
            if (!isLocked && (!selectref(isRight, ref grabbingRight, ref grabbingLeft) || !selectref(isRight, ref grabbableRight, ref grabbableLeft)))
            {
                Drop(isRight);
            }
            else
            {
                // Hold the item in the player's hand
                if (rigidbody != null && grabPhysics)
                {
                    rigidbody.MovePosition(TranslateRelative(selectref(isRight, ref HandTrackerVR.rightHand.wrist, ref HandTrackerVR.leftHand.wrist).transform, new Vector3(isRight ? grabPositionOffset.x : -grabPositionOffset.x, grabPositionOffset.y, grabPositionOffset.z)));
                }
                else
                {
                    transform.position = TranslateRelative(selectref(isRight, ref HandTrackerVR.rightHand.wrist, ref HandTrackerVR.leftHand.wrist).transform, new Vector3(isRight ? grabPositionOffset.x : -grabPositionOffset.x, grabPositionOffset.y, grabPositionOffset.z));
                }

                if (rotationOffset)
                {
                    transform.eulerAngles = selectref(isRight, ref HandTrackerVR.rightHand.wrist, ref HandTrackerVR.leftHand.wrist).transform.eulerAngles;

                    transform.Rotate(isRight ? rightRotationOffset : leftRotationOffset);
                }

                // Check if the rigidbody exists
                if (rigidbody != null)
                {
                    // Ignore the rigidbody's velocities
                    rigidbody.velocity = Vector3.zero;

                    rigidbody.angularVelocity = Vector3.zero;
                }
            }
        }
    }

    /// <summary>
    /// Dropping the object
    /// </summary>
    /// <param name="isRight"></param>
    private void Drop(bool isRight)
    {
        // Set this hand's grabbed object to null
        selectref(isRight, ref heldRightObject, ref heldLeftObject) = null;

        // Check if the rigidbody exists 
        if (rigidbody == null)
        {
            // Add a rigidbody component
            if (assignRigidbody)
            {
                rigidbody = gameObject.AddComponent<Rigidbody>();
            }

            // Check if rigidbody exists
            if (rigidbody != null)
            {
                // Set the gravity of the object
                if (keepGravitySetting)
                {
                    rigidbody.useGravity = gravitySetting;
                }
                else
                {
                    rigidbody.useGravity = newGravity;
                }

                // Check if this object is throwable
                if (throwable)
                {
                    Throw();

                    LoseCollision(isRight);
                }
            }
        }
        else
        {
            // Set the gravity of the object
            if (keepGravitySetting)
            {
                rigidbody.useGravity = gravitySetting;
            }
            else
            {
                rigidbody.useGravity = newGravity;
            }

            // Check if this object is throwable
            if (throwable)
            {
                Throw();

                LoseCollision(isRight);
            }
        }

        // Invoke the drop event
        onDrop.Invoke();
    }

    /// <summary>
    /// Throwing the object
    /// </summary>
    private void Throw()
    {
        // Calculate the direction of the throw in world space
        Vector3 direction = transform.position - previousPosition;

        // Check the type of velocity scaling
        if (velocityScalingType == VelocityScaleType.DistanceSquared)
        {
            // Scale the direction based on distance squared
            direction = direction.normalized * DistanceSquared(previousPosition, transform.position);
        }
        else if (velocityScalingType == VelocityScaleType.Distance)
        {
            // Scale the direction based on distance
            direction = direction.normalized * Vector3.Distance(previousPosition, transform.position);
        }

        // Offset the thrown rotation
        direction = Rotate(direction, thrownOffset);

        // Scale the throw force
        direction *= thrownScale;

        // Set the velocity of the object to the thrown direction
        rigidbody.velocity = direction;

        // Invoke the throw event
        onThrow.Invoke();
    }

    /// <summary>
    /// Losing hand collision after throwing
    /// </summary>
    /// <param name="isRight"></param>
    private void LoseCollision(bool isRight)
    {
        if (isRight)
        {
            foreach (GameObject finger in HandTrackerVR.rightHand.colliders.Keys)
            {
                HandTrackerVR.rightHand.colliders[finger].enabled = false;
            }

            Invoke("RegainRightCollision", collisionDelay);
        }
        else
        {
            foreach (GameObject finger in HandTrackerVR.leftHand.colliders.Keys)
            {
                HandTrackerVR.leftHand.colliders[finger].enabled = false;
            }

            Invoke("RegainLeftCollision", collisionDelay);
        }
    }

    /// <summary>
    /// Regaining left hand collision after throwing
    /// </summary>
    private void RegainLeftCollision()
    {
        foreach (GameObject finger in HandTrackerVR.leftHand.colliders.Keys)
        {
            HandTrackerVR.leftHand.colliders[finger].enabled = true;
        }
    }

    /// <summary>
    /// Regaining right hand collision after throwing
    /// </summary>
    private void RegainRightCollision()
    {
        foreach (GameObject finger in HandTrackerVR.rightHand.colliders.Keys)
        {
            HandTrackerVR.rightHand.colliders[finger].enabled = true;
        }
    }


    // GETTERS

    /// <summary>
    /// Returns if the object is currently being grabbed
    /// </summary>
    /// <returns></returns>
    public bool IsGrabbed()
    {
        return heldLeftObject == gameObject || heldRightObject == gameObject;
    }

    /// <summary>
    /// Returns if the object is currently grabbed with the player's left hand
    /// </summary>
    /// <returns></returns>
    public bool IsGrabbedLeft()
    {
        return heldLeftObject == gameObject;
    }

    /// <summary>
    /// Returns if the object is currently grabbed with the player's right hand
    /// </summary>
    /// <returns></returns>
    public bool IsGrabbedRight()
    {
        return heldRightObject == gameObject;
    }

    /// <summary>
    /// Returns if the object is currently being grabbed by the given hand
    /// </summary>
    /// <returns></returns>
    public bool IsGrabbed(bool isRight)
    {
        return isRight ? heldRightObject == gameObject : heldLeftObject == gameObject;
    }


    // LOCKING ITEM

    /// <summary>
    /// Returns whether the object is currently locked
    /// </summary>
    /// <returns></returns>
    public bool IsLocked()
    {
        return isLocked;
    }

    /// <summary>
    /// Locks the player's item to their hands when grabbed
    /// </summary>
    /// <returns></returns>
    public bool Lock(bool isLocked = true)
    {
        this.isLocked = isLocked;

        return isLocked;
    }

    /// <summary>
    /// Unlocks this item so it may be dropped
    /// </summary>
    /// <returns></returns>
    public bool Unlock(bool isUnlocked = false)
    {
        this.isLocked = isUnlocked;

        return isLocked;
    }

    /// <summary>
    /// Locks or unlocks the player's item from their hands
    /// </summary>
    /// <returns></returns>
    public bool ToggleLock()
    {
        isLocked = !isLocked;

        return isLocked;
    }


    // HELPER FUNCTIONS

    /// <summary>
    /// Select from a boolean and return the chosen data
    /// </summary>
    /// <typeparam name="DataType"></typeparam>
    /// <param name="condition"></param>
    /// <param name="trueData"></param>
    /// <param name="falseData"></param>
    /// <returns></returns>
    private static ref DataType selectref<DataType>(bool condition, ref DataType trueData, ref DataType falseData)
    {
        if (condition)
        {
            return ref trueData;
        }
        else
        {
            return ref falseData;
        }
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
    /// Rotate a vector 3 by a euler rotation
    /// </summary>
    /// <param name="direction"></param>
    /// <param name="rotation"></param>
    /// <returns></returns>
    private static Vector3 Rotate(Vector3 direction, Vector3 rotation)
    {
        return Quaternion.Euler(rotation) * direction;
    }
}
