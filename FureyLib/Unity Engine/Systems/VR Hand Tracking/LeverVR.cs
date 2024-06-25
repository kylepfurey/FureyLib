
// VR Movable Lever Script
// by Kyle Furey

// REQUIREMENTS: HandTrackerVR.cs, HandGrabbableVR.cs

using UnityEngine;
using UnityEngine.Events;

/// <summary>
/// Creates an interactable lever able to be moved by VR hands to call various events.
/// </summary>
public class LeverVR : MonoBehaviour, IHandInteractableVR
{
    [Header("Creates an interactable lever able to be moved by VR hands to call various events.")]

    [Header("\nCONFIGURATION")]

    [Header("The pivot object for the lever:")]
    [SerializeField] private GameObject pivot = null;

    [Header("The knob object and its HandGrabbableVR script for the lever:")]
    [SerializeField] private HandGrabbableVR knob = null;

    [Header("The directions the lever may move:")]
    [SerializeField] private LeverDirection direction = LeverDirection.ForwardBackward;

    [Header("The positive clamps (in degrees) of moving the lever backwards (X) and forwards (Y):")]
    [SerializeField] private Vector2 backwardForwardClamp = new Vector2(60, 60);

    [Header("The positive clamps (in degrees) of moving the lever left (X) and right (Y):")]
    [SerializeField] private Vector2 leftRightClamp = new Vector2(60, 60);

    [Header("Whether to automatically reset the lever when it is not grabbed:")]
    [SerializeField] private bool resetLever = true;

    [Header("Whether to use lerp instead of move towards to reset the lever when it is no longer grabbed:")]
    [SerializeField] private bool lerpReset = true;

    [Header("The speed to reset the lever when it is no longer grabbed:")]
    [SerializeField] private float resetSpeed = 1;

    [Header("\nEVENTS")]

    [Header("The minimum percentage the lever must be at of the clamps to be considered fully moved:")]
    [SerializeField] private float leverDownPercentage = 0.9f;

    [Header("Events for when the lever is fully moved in a direction:")]
    [SerializeField] private UnityEvent forwardEvents = null;
    [SerializeField] private UnityEvent backwardEvents = null;
    [SerializeField] private UnityEvent leftEvents = null;
    [SerializeField] private UnityEvent rightEvents = null;

    /// <summary>
    /// The parent object of the lever's knob (to keep it attached to the lever)
    /// </summary>
    private Transform knobParent = null;

    /// <summary>
    /// The local position of the lever's knob (to keep it attached to the lever)
    /// </summary>
    private Vector3 knobLocalPosition = Vector3.zero;

    /// <summary>
    /// The starting direction of the lever (to allow it to reset)
    /// </summary>
    private Quaternion startDirection = Quaternion.identity;

    /// <summary>
    /// Whether the lever has been updated this frame already (to prevent calling LateUpdate() multiple times in one frame when calling lever functions)
    /// </summary>
    private bool updated = false;

    /// <summary>
    /// Lever direction enum
    /// </summary>
    public enum LeverDirection
    {
        /// <summary>
        /// The lever will only be able to move forward and backward.
        /// </summary>
        ForwardBackward,

        /// <summary>
        /// The lever will only be able to move left and right.
        /// </summary>
        LeftRight,

        /// <summary>
        /// The lever will be able to move forward, backward, left, and right, but not in-between.
        /// </summary>
        Bidirectional,

        /// <summary>
        /// The lever will be able to move any direction; like a joystick. It is normalized, so the range of the lever is like a circle.
        /// </summary>
        OmnidirectionalNormalized,

        /// <summary>
        /// The lever will be able to move any direction; like a joystick. It is not normalized, so the range of the lever is like a square.
        /// </summary>
        Omnidirectional
    }

    /// <summary>
    /// 2D direction enum
    /// </summary>
    public enum Direction2D { Forward, Backward, Left, Right };

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

        knobParent = knob.transform.parent;

        knobLocalPosition = knob.transform.localPosition;

        startDirection = pivot.transform.localRotation;
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
    /// Marks the lever as not updated
    /// </summary>
    private void Update()
    {
        updated = false;
    }

    /// <summary>
    /// Ensures the lever is updated after HandGrabbableVR updates
    /// </summary>
    private void LateUpdate()
    {
        UpdateLever();
    }

    /// <summary>
    /// Updates the lever if it has not been updated already
    /// </summary>
    private void UpdateLever()
    {
        if (!updated && IHandInteractableVR.handsSet)
        {
            updated = true;

            if (knob.IsGrabbedRight())
            {
                knob.transform.parent = knobParent;

                knob.transform.localPosition = knobLocalPosition;

                PointLeverTowards(HandTrackerVR.rightHand.palm.transform.position);

                MoveLever();
            }
            else if (knob.IsGrabbedLeft())
            {
                knob.transform.parent = knobParent;

                knob.transform.localPosition = knobLocalPosition;

                PointLeverTowards(HandTrackerVR.leftHand.palm.transform.position);

                MoveLever();
            }
            else if (resetLever)
            {
                pivot.transform.localRotation = lerpReset ? Quaternion.Lerp(pivot.transform.localRotation, startDirection, Time.deltaTime * resetSpeed) : Quaternion.RotateTowards(pivot.transform.localRotation, startDirection, Time.deltaTime * resetSpeed);
            }
        }
    }

    /// <summary>
    /// Rotates the lever based on the clamps
    /// </summary>
    private void MoveLever()
    {
        float xRotation = 0;

        float zRotation = 0;

        switch (direction)
        {
            case LeverDirection.ForwardBackward:

                pivot.transform.localEulerAngles = new Vector3(Mathf.Clamp(RotationOnAxis(pivot.transform.localRotation, Axis.X), startDirection.x - backwardForwardClamp.x, startDirection.x + backwardForwardClamp.y), startDirection.eulerAngles.y, startDirection.eulerAngles.z);

                break;

            case LeverDirection.LeftRight:

                pivot.transform.localEulerAngles = new Vector3(startDirection.eulerAngles.x, startDirection.eulerAngles.y, Mathf.Clamp(RotationOnAxis(pivot.transform.localRotation, Axis.Z), startDirection.z - leftRightClamp.x, startDirection.y + leftRightClamp.y));

                break;

            case LeverDirection.Bidirectional:

                xRotation = Mathf.Clamp(RotationOnAxis(pivot.transform.localRotation, Axis.X), startDirection.x - backwardForwardClamp.x, startDirection.x + backwardForwardClamp.y);

                zRotation = Mathf.Clamp(RotationOnAxis(pivot.transform.localRotation, Axis.Z), startDirection.z - leftRightClamp.x, startDirection.y + leftRightClamp.y);

                if (Mathf.Abs(zRotation - startDirection.z) <= 10)
                {
                    pivot.transform.localEulerAngles = new Vector3(xRotation, startDirection.eulerAngles.y, startDirection.eulerAngles.z);
                }
                else if (Mathf.Abs(xRotation - startDirection.x) <= 10)
                {
                    pivot.transform.localEulerAngles = new Vector3(startDirection.eulerAngles.x, startDirection.eulerAngles.y, zRotation);
                }
                else if (Mathf.Abs(zRotation) < Mathf.Abs(xRotation))
                {
                    pivot.transform.localEulerAngles = new Vector3(xRotation, startDirection.eulerAngles.y, startDirection.eulerAngles.z);
                }
                else
                {
                    pivot.transform.localEulerAngles = new Vector3(startDirection.eulerAngles.x, startDirection.eulerAngles.y, zRotation);
                }

                // ALTERNATIVE METHOD
                /*
                xRotation = Mathf.Clamp(RotationOnAxis(pivot.transform.localRotation, Axis.X), startDirection.x - forwardBackwardClamp.x, startDirection.x + forwardBackwardClamp.y);

                zRotation = Mathf.Clamp(RotationOnAxis(pivot.transform.localRotation, Axis.Z), startDirection.z - leftRightClamp.x, startDirection.y + leftRightClamp.y);

                Vector2 rotation = new Vector2(Mathf.Abs(xRotation), Mathf.Abs(zRotation)).normalized;

                pivot.transform.localEulerAngles = new Vector3(startDirection.x + rotation.x * xRotation, startDirection.eulerAngles.y, startDirection.z + rotation.y * zRotation);
                */

                break;

            case LeverDirection.OmnidirectionalNormalized:

                pivot.transform.localEulerAngles = new Vector3(Mathf.Clamp(RotationOnAxis(pivot.transform.localRotation, Axis.X), startDirection.x - backwardForwardClamp.x, startDirection.x + backwardForwardClamp.y), startDirection.eulerAngles.y, Mathf.Clamp(RotationOnAxis(pivot.transform.localRotation, Axis.Z), startDirection.z - leftRightClamp.x, startDirection.y + leftRightClamp.y));

                break;

            case LeverDirection.Omnidirectional:

                pivot.transform.localEulerAngles = new Vector3(Mathf.Clamp(RotationOnAxis(pivot.transform.localRotation, Axis.X), startDirection.x - backwardForwardClamp.x, startDirection.x + backwardForwardClamp.y), startDirection.eulerAngles.y, Mathf.Clamp(RotationOnAxis(pivot.transform.localRotation, Axis.Z), startDirection.z - leftRightClamp.x, startDirection.y + leftRightClamp.y));

                break;
        }

        if (IsLeverDown(Direction2D.Forward))
        {
            forwardEvents.Invoke();
        }
        else if (IsLeverDown(Direction2D.Backward))
        {
            backwardEvents.Invoke();
        }

        if (IsLeverDown(Direction2D.Right))
        {
            rightEvents.Invoke();
        }
        else if (IsLeverDown(Direction2D.Left))
        {
            leftEvents.Invoke();
        }
    }

    /// <summary>
    /// Properly points the lever towards the given world position
    /// </summary>
    /// <param name="pointAtPosition"></param>
    public void PointLeverTowards(Vector3 pointAtPosition)
    {
        GameObject rotator = new GameObject();

        Vector3 direction = (pointAtPosition - pivot.transform.position).normalized;

        rotator.transform.LookAt(new Vector3(0, direction.y, Mathf.Abs(direction.z)));

        rotator.transform.Rotate(90, 0, 0);

        float xRotation = RotationOnAxis(rotator.transform.rotation, Axis.X);

        if (direction.z < 0)
        {
            xRotation *= -1;
        }

        rotator.transform.eulerAngles = Vector3.zero;

        rotator.transform.LookAt(new Vector3(0, direction.y, Mathf.Abs(direction.x)));

        rotator.transform.Rotate(90, 0, 0);

        float zRotation = RotationOnAxis(rotator.transform.rotation, Axis.X);

        if (direction.x > 0)
        {
            zRotation *= -1;
        }

        DestroyImmediate(rotator);

        switch (this.direction)
        {
            case LeverDirection.ForwardBackward:

                pivot.transform.eulerAngles = new Vector3(xRotation, pivot.transform.eulerAngles.y, pivot.transform.eulerAngles.z);

                break;

            case LeverDirection.LeftRight:

                pivot.transform.eulerAngles = new Vector3(pivot.transform.eulerAngles.x, pivot.transform.eulerAngles.y, zRotation);

                break;

            case LeverDirection.Bidirectional:

                pivot.transform.eulerAngles = new Vector3(xRotation, pivot.transform.eulerAngles.y, zRotation);

                break;

            case LeverDirection.OmnidirectionalNormalized:

                Vector2 newDirection = new Vector2(xRotation, zRotation).normalized;

                pivot.transform.eulerAngles = new Vector3(newDirection.x * xRotation * (newDirection.x < 0 ? -1 : 1), pivot.transform.eulerAngles.y, newDirection.y * zRotation * (newDirection.y < 0 ? -1 : 1));

                break;

            case LeverDirection.Omnidirectional:

                pivot.transform.eulerAngles = new Vector3(xRotation, pivot.transform.eulerAngles.y, zRotation);

                break;
        }
    }

    /// <summary>
    /// Sets whether the lever is active (modifies the ability to grab the lever's knob)
    /// </summary>
    /// <param name="active"></param>
    public void SetLeverActive(bool active)
    {
        knob.grabbableLeft = active;

        knob.grabbableRight = active;
    }

    /// <summary>
    /// Updates the lever and returns the lever's current percentage in the given direction
    /// </summary>
    /// <param name="direction"></param>
    /// <returns>The percentage the lever is at of the given direction</returns>
    public float GetLeverAxis(Direction2D direction)
    {
        UpdateLever();

        float percent = 0;

        switch (direction)
        {
            case Direction2D.Forward:

                percent = Percentage(RotationOnAxis(pivot.transform.localRotation, Axis.X), startDirection.eulerAngles.x, startDirection.eulerAngles.x + backwardForwardClamp.y);

                break;

            case Direction2D.Backward:

                percent = Percentage(RotationOnAxis(pivot.transform.localRotation, Axis.X), startDirection.eulerAngles.x - backwardForwardClamp.x, startDirection.eulerAngles.x);

                break;

            case Direction2D.Right:

                percent = Percentage(RotationOnAxis(pivot.transform.localRotation, Axis.Z), startDirection.eulerAngles.z, startDirection.eulerAngles.z + backwardForwardClamp.y);

                break;

            case Direction2D.Left:

                percent = Percentage(RotationOnAxis(pivot.transform.localRotation, Axis.Z), startDirection.eulerAngles.z - backwardForwardClamp.x, startDirection.eulerAngles.z);

                break;
        }

        return percent;
    }

    /// <summary>
    /// Updates the lever and returns the lever's current percentage in either the forward or right direction unless they are negative where it will return the negative percentage of the opposite direction
    /// </summary>
    /// <param name="isHorizontalDirection">Whether we are checking the left and right directions instead of forward and backward directions.</param>
    /// <param name="useOppositeDirection">Whether we are checking either the backward or left directions instead of forward or right directions.</param>
    /// <returns>The percentage the lever is at of the given directions</returns>
    public float GetLeverAxis(bool isHorizontalDirection, bool useOppositeDirection = false)
    {
        if (isHorizontalDirection)
        {
            if (useOppositeDirection)
            {
                float percent = GetLeverAxis(Direction2D.Left);

                if (percent < 0)
                {
                    percent = -(1 - GetLeverAxis(Direction2D.Right));
                }

                return percent;
            }
            else
            {
                float percent = GetLeverAxis(Direction2D.Right);

                if (percent < 0)
                {
                    percent = -(1 - GetLeverAxis(Direction2D.Left));
                }

                return percent;
            }
        }
        else
        {
            if (useOppositeDirection)
            {
                float percent = GetLeverAxis(Direction2D.Backward);

                if (percent < 0)
                {
                    percent = -(1 - GetLeverAxis(Direction2D.Forward));
                }

                return percent;
            }
            else
            {
                float percent = GetLeverAxis(Direction2D.Forward);

                if (percent < 0)
                {
                    percent = -(1 - GetLeverAxis(Direction2D.Backward));
                }

                return percent;
            }
        }
    }

    /// <summary>
    /// Updates the lever and returns whether the lever is currently considered down in the given direction
    /// </summary>
    /// <param name="direction"></param>
    /// <returns>Whether the lever is considered down in the given direction</returns>
    public bool IsLeverDown(Direction2D direction)
    {
        return GetLeverAxis(direction) >= leverDownPercentage;
    }

    /// <summary>
    /// Updates the lever and returns whether the lever is currently considered down in the given directions
    /// </summary>
    /// <param name="isHorizontalDirection">Whether we are checking the left and right directions instead of forward and backward directions.</param>
    /// <returns>Whether the lever is considered down in either of the two given directions</returns>
    public bool IsLeverDown(bool isHorizontalDirection)
    {
        return Mathf.Abs(GetLeverAxis(isHorizontalDirection)) >= leverDownPercentage;
    }

    /// <summary>
    /// Updates the lever and returns the normalized world direction the lever is currently facing
    /// </summary>
    /// <returns></returns>
    public Vector3 GetLeverDirection()
    {
        UpdateLever();

        return (knob.transform.position - pivot.transform.position).normalized;
    }

    /// <summary>
    /// Resets the lever to its starting direction
    /// </summary>
    /// <returns></returns>
    public void ResetLever()
    {
        knob.transform.localRotation = startDirection;
    }

    /// <summary>
    /// Sets the lever's starting direction to its current rotation
    /// </summary>
    /// <returns></returns>
    public void SetLeverOrigin()
    {
        startDirection = knob.transform.localRotation;
    }

    /// <summary>
    /// Sets the lever's starting direction to the given rotation
    /// </summary>
    /// <param name="rotation"></param>
    public void SetLeverOrigin(Quaternion rotation)
    {
        startDirection = rotation;
    }

    /// <summary>
    /// Sets the lever's starting direction to the given rotation
    /// </summary>
    /// <param name="eulerRotation"></param>
    public void SetLeverOrigin(Vector3 eulerRotation)
    {
        startDirection = Quaternion.Euler(eulerRotation);
    }

    /// <summary>
    /// Rotation axis enum
    /// </summary>
    private enum Axis { X, Y, Z, W, x = X, y = Y, z = Z, w = W };

    /// <summary>
    /// Returns the 0 - 360 degree rotation of an axis based on the given rotation
    /// SOURCE: https://discussions.unity.com/t/read-rotations-around-local-axis/227816/4 by WarmedxMints
    /// </summary>
    /// <param name="rotation"></param>
    /// <param name="axis"></param>
    /// <returns></returns>
    private static float RotationOnAxis(Quaternion rotation, Axis axis)
    {
        rotation.x /= rotation.w;
        rotation.y /= rotation.w;
        rotation.z /= rotation.w;
        rotation.w = 1;

        float angle = Mathf.Atan(rotation[(int)axis]) * Mathf.Rad2Deg * 2;

        return angle;
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
}
