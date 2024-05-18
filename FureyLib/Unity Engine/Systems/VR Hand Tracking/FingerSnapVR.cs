
// VR Finger Snap Event Script
// by Kyle Furey

using UnityEngine;
using UnityEngine.Events;

/// <summary>
/// Detects and invokes events when the player snaps their fingers in VR.
/// </summary>
public class FingerSnapVR : MonoBehaviour, IHandInteractableVR
{
    [Header("Detects and invokes events when the player snaps their fingers in VR.")]

    [Header("\nEVENTS")]

    [Header("Events for when the player snaps their fingers:")]
    [SerializeField] private UnityEvent snapEvents = null;
    [SerializeField] private UnityEvent leftSnapEvents = null;
    [SerializeField] private UnityEvent rightSnapEvents = null;

    [Header("The optional sound to play when the player snaps:")]
    [SerializeField] private AudioClip snapSound = null;

    /// <summary>
    /// This object's current instance in the scene
    /// </summary>
    [HideInInspector] public FingerSnapVR instance = null;

    /// <summary>
    /// Whether the player is readying a snap with their left hand
    /// </summary>
    private bool leftSnapReady = false;

    /// <summary>
    /// Whether the player is readying a snap with their right hand
    /// </summary>
    private bool rightSnapReady = false;

    /// <summary>
    /// Timer used to give frame leeway for snapping (left hand)
    /// </summary>
    private float leftBuffer = 0;

    /// <summary>
    /// Timer used to give frame leeway for snapping (right hand)
    /// </summary>
    private float rightBuffer = 0;

    /// <summary>
    /// IHandInteractableVR Interface - Adds the object as an implementation to the interface.
    /// </summary>
    public FingerSnapVR()
    {
        IHandInteractableVR.implementations.Add(this);
    }

    /// <summary>
    /// IHandInteractableVR Interface - Removes the object's implementation to the interface.
    /// </summary>
    ~FingerSnapVR()
    {
        IHandInteractableVR.implementations.Remove(this);
    }

    /// <summary>
    /// IHandInteractableVR Interface - Called when VR hands are successfully set.
    /// </summary>
    public void OnSetHands()
    {

    }

    /// <summary>
    /// Removes duplicate FingerSnapVR components
    /// </summary>
    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
        }
        else
        {
            DestroyImmediate(this);
        }
    }

    /// <summary>
    /// Checks for finger snapping
    /// </summary>
    private void Update()
    {
        if (IHandInteractableVR.handsSet)
        {
            if (HandTrackerVR.GetGesture(HandVR.Gesture.PinchMiddle, false))
            {
                leftSnapReady = true;
            }
            else if (leftSnapReady && (HandTrackerVR.GetGesture(HandVR.Gesture.Point, false) || HandTrackerVR.GetGesture(HandVR.Gesture.FingerGun, false)))
            {
                leftSnapReady = false;

                leftBuffer = 0;

                leftSnapEvents.Invoke();

                snapEvents.Invoke();
            }
            else if (leftSnapReady)
            {
                if (leftBuffer > 0.25f)
                {
                    leftSnapReady = false;

                    leftBuffer = 0;
                }

                leftBuffer += Time.deltaTime;
            }

            if (HandTrackerVR.GetGesture(HandVR.Gesture.PinchMiddle, true))
            {
                rightSnapReady = true;
            }
            else if (rightSnapReady && (HandTrackerVR.GetGesture(HandVR.Gesture.Point, true) || HandTrackerVR.GetGesture(HandVR.Gesture.FingerGun, true)))
            {
                rightSnapReady = false;

                rightBuffer = 0;

                rightSnapEvents.Invoke();

                snapEvents.Invoke();
            }
            else if (rightSnapReady)
            {
                if (rightBuffer > 0.25f)
                {
                    rightSnapReady = false;

                    rightBuffer = 0;
                }

                rightBuffer += Time.deltaTime;
            }
        }
    }

    /// <summary>
    /// Logs "SNAP!" to the console
    /// </summary>
    public void Print()
    {
        if (IHandInteractableVR.handsSet)
        {
            Debug.Log("SNAP!");
        }
    }

    /// <summary>
    /// Plays the snapping sound
    /// </summary>
    public void PlaySound()
    {
        if (IHandInteractableVR.handsSet && snapSound != null)
        {
            AudioSource.PlayClipAtPoint(snapSound, HandTrackerVR.rightHand.palm.transform.root.position);
        }
    }
}
