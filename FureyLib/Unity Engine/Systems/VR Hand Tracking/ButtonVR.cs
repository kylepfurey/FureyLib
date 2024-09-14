
// VR Pressable Button Script
// by Kyle Furey

// REQUIREMENT: HandTrackerVR.cs

using UnityEngine;
using UnityEngine.Events;

/// <summary>
/// Creates an interactable button able to be clicked by VR hands to call various events.
/// </summary>
public class ButtonVR : MonoBehaviour, IHandInteractableVR
{
    [Header("Creates an interactable button able to be clicked by VR hands to call various events.")]
    [Header("NOTE: This component's object must be parented to a base object.")]

    [Header("\nCONFIGURATION")]

    [Header("The local height of the button when it is up:")]
    [SerializeField] private float startHeight = 0.6f;

    [Header("The minimum local height the button can be pressed down to:")]
    [SerializeField] private float pressedHeight = 0.45f;

    [Header("The local height for this button to be considered clicked:")]
    [SerializeField] private float clickedHeight = 0.5f;

    [Header("The speed the button will move to its target height when released:")]
    [SerializeField] private float releaseSpeed = 1;

    [Header("Whether the button's release movement will use lerp or move towards:")]
    [SerializeField] private bool lerpRelease = true;

    [Header("Multiplier applied to the button's scale height to ensure it moves properly when it is touched:")]
    [SerializeField] private float startingWorldScaleY = 1;

    [Header("Whether the button will automatically be clicked on start:")]
    [SerializeField] private bool startClicked = false;

    [Header("\nBUTTON SETTINGS")]

    [Header("Whether the button is currently active:")]
    public bool isActive = true;

    [Header("Whether the button will stay clicked when pushed down and unclick when pushed again:")]
    [SerializeField] private bool isSticky = true;

    [Header("The delay in seconds before considering the button held down:")]
    [SerializeField] private float heldDelay = 0.5f;

    [Header("The optional material for when the button is currently unclicked:")]
    [SerializeField] private Material unclickedMaterial = null;

    [Header("The optional material for when the button is currently clicked down:")]
    [SerializeField] private Material clickedMaterial = null;

    [Header("The optional sound to play for when the button is clicked:")]
    [SerializeField] private AudioClip clickedSound = null;

    [Header("The optional sound to play for when the button is unclicked:")]
    [SerializeField] private AudioClip unclickedSound = null;

    [Header("\nEVENTS")]

    [Header("Events for when the button is clicked down:")]
    public UnityEvent onClick = null;

    [Header("Events for when the button is pressed down:")]
    public UnityEvent onHold = null;

    [Header("Events for when the button is no longer held down:")]
    public UnityEvent onRelease = null;

    [Header("Events for when the button is clicked down:")]
    public UnityEvent duringClick = null;

    [Header("Events for when the button is clicked back up:")]
    public UnityEvent onUnclick = null;

    /// <summary>
    /// The current state of the button
    /// </summary>
    private ButtonState state = ButtonState.Unclicked;

    /// <summary>
    /// The current elapsed time of pressing a button
    /// </summary>
    private float elapsedTime = 0;

    /// <summary>
    /// Whether the button is currently being pressed
    /// </summary>
    private bool isTouched = false;

    /// <summary>
    /// Whether the button is currently clicked down
    /// </summary>
    private bool isClicked = false;

    /// <summary>
    /// The current collider to check for trigger interactions
    /// </summary>
    private Collider currentCollider = null;

    /// <summary>
    /// Button state enum
    /// </summary>
    public enum ButtonState
    {
        /// <summary>
        /// When the button is untouched or moving to its starting height.
        /// </summary>
        Unclicked,

        /// <summary>
        /// When the button is continually pressed after being clicked for at least the number of seconds equal to the heldDelay variable.
        /// </summary>
        HeldDown,

        /// <summary>
        /// When the button is first pressed down or when the button is untouched and in a clicked state.
        /// </summary>
        ClickedDown
    };

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
    /// Presses the button if it is to start clicked
    /// </summary>
    private void Start()
    {
        if (startClicked)
        {
            isClicked = true;

            state = ButtonState.ClickedDown;

            transform.localPosition = new Vector3(transform.localPosition.x, clickedHeight, transform.localPosition.z);

            GetComponent<Renderer>().material = clickedMaterial == null ? GetComponent<Renderer>().material : clickedMaterial;
        }
    }

    /// <summary>
    /// Resets the button's height
    /// </summary>
    private void Update()
    {
        if (isClicked)
        {
            transform.localPosition = lerpRelease ? Vector3.Lerp(transform.localPosition, new Vector3(transform.localPosition.x, clickedHeight, transform.localPosition.z), Time.deltaTime * releaseSpeed) : Vector3.MoveTowards(transform.localPosition, new Vector3(transform.localPosition.x, clickedHeight, transform.localPosition.z), Time.deltaTime * releaseSpeed);

            duringClick.Invoke();
        }
        else
        {
            transform.localPosition = lerpRelease ? Vector3.Lerp(transform.localPosition, new Vector3(transform.localPosition.x, startHeight, transform.localPosition.z), Time.deltaTime * releaseSpeed) : Vector3.MoveTowards(transform.localPosition, new Vector3(transform.localPosition.x, startHeight, transform.localPosition.z), Time.deltaTime * releaseSpeed);
        }
    }

    /// <summary>
    /// Called when entering a 3D trigger collision
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerEnter(Collider other)
    {
        if (isActive && IHandInteractableVR.handsSet && currentCollider == null && (HandTrackerVR.leftHand.colliders.ContainsValue(other) || HandTrackerVR.rightHand.colliders.ContainsValue(other)))
        {
            currentCollider = other;

            isTouched = true;

            elapsedTime = 0;
        }
    }

    /// <summary>
    /// Called when overlapping a 3D trigger collision
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerStay(Collider other)
    {
        if (isActive && IHandInteractableVR.handsSet && currentCollider == other)
        {
            transform.localPosition = new Vector3(transform.localPosition.x, Mathf.Clamp(transform.parent.InverseTransformPoint(other.transform.position).y - transform.localScale.y / startingWorldScaleY, pressedHeight, startHeight), transform.localPosition.z);

            if (transform.localPosition.y <= clickedHeight)
            {
                if (elapsedTime >= heldDelay && elapsedTime != 0)
                {
                    // HELD

                    state = ButtonState.HeldDown;

                    onHold.Invoke();
                }
                else
                {
                    // CLICKED

                    if (elapsedTime == 0)
                    {
                        if (isSticky)
                        {
                            isClicked = !isClicked;

                            if (isClicked)
                            {
                                state = ButtonState.ClickedDown;

                                GetComponent<Renderer>().material = clickedMaterial == null ? GetComponent<Renderer>().material : clickedMaterial;

                                if (clickedSound != null)
                                {
                                    AudioSource.PlayClipAtPoint(clickedSound, transform.position);
                                }

                                onClick.Invoke();
                            }
                            else
                            {
                                state = ButtonState.Unclicked;

                                GetComponent<Renderer>().material = unclickedMaterial == null ? GetComponent<Renderer>().material : unclickedMaterial;

                                if (unclickedSound != null)
                                {
                                    AudioSource.PlayClipAtPoint(unclickedSound, transform.position);
                                }

                                onUnclick.Invoke();
                            }
                        }
                        else
                        {
                            isClicked = true;

                            state = ButtonState.ClickedDown;

                            GetComponent<Renderer>().material = clickedMaterial == null ? GetComponent<Renderer>().material : clickedMaterial;

                            if (clickedSound != null)
                            {
                                AudioSource.PlayClipAtPoint(clickedSound, transform.position);
                            }

                            onClick.Invoke();
                        }
                    }
                }

                elapsedTime += Time.deltaTime;
            }
            else
            {
                // RELEASED

                if (elapsedTime != 0)
                {
                    if (isSticky)
                    {
                        if (isClicked)
                        {
                            isClicked = true;

                            state = ButtonState.ClickedDown;

                            GetComponent<Renderer>().material = clickedMaterial == null ? GetComponent<Renderer>().material : clickedMaterial;
                        }
                        else
                        {
                            isClicked = false;

                            state = ButtonState.Unclicked;

                            GetComponent<Renderer>().material = unclickedMaterial == null ? GetComponent<Renderer>().material : unclickedMaterial;
                        }
                    }
                    else
                    {
                        isClicked = false;

                        state = ButtonState.Unclicked;

                        GetComponent<Renderer>().material = unclickedMaterial == null ? GetComponent<Renderer>().material : unclickedMaterial;

                        if (clickedSound != null)
                        {
                            AudioSource.PlayClipAtPoint(clickedSound, transform.position);
                        }
                    }

                    onRelease.Invoke();
                }

                elapsedTime = 0;
            }

            isTouched = true;
        }
    }

    /// <summary>
    /// Called when leaving a 3D trigger collision
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerExit(Collider other)
    {
        if (isActive && IHandInteractableVR.handsSet && currentCollider == other)
        {
            currentCollider = null;

            isTouched = false;

            if (!isSticky)
            {
                isClicked = false;

                state = ButtonState.Unclicked;

                GetComponent<Renderer>().material = unclickedMaterial == null ? GetComponent<Renderer>().material : unclickedMaterial;

                if (elapsedTime != 0)
                {
                    onRelease.Invoke();
                }

                onUnclick.Invoke();
            }

            elapsedTime = 0;
        }
    }

    /// <summary>
    /// Returns a collection of data representing the button's current state
    /// </summary>
    /// <returns></returns>
    public ButtonStateVR GetButtonState()
    {
        ButtonStateVR buttonState = new ButtonStateVR(isActive, isSticky, isTouched, isClicked, Percentage(transform.localPosition.y, pressedHeight, startHeight), elapsedTime, state);

        return buttonState;
    }

    /// <summary>
    /// Sets whether the button is active
    /// </summary>
    /// <param name="active"></param>
    public void SetActive(bool active)
    {
        isActive = active;
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

/// <summary>
/// Stores the current state of a VR button.
/// </summary>
public readonly struct ButtonStateVR
{
    /// <summary>
    /// Whether the button is currently active and usable
    /// </summary>
    public readonly bool isActive;

    /// <summary>
    /// Whether the button sticks down when pressed
    /// </summary>
    public readonly bool isSticky;

    /// <summary>
    /// Whether the button is currently touched by the player
    /// </summary>
    public readonly bool isTouched;

    /// <summary>
    /// Whether the button is currently clicked down
    /// </summary>
    public readonly bool isClicked;

    /// <summary>
    /// The percentage of the button's pressed height
    /// </summary>
    public readonly float buttonHeight;

    /// <summary>
    /// The elapsed time since the button has been pressed (if the button is currently pressed)
    /// </summary>
    public readonly float elapsedTime;

    /// <summary>
    /// The current state of the button
    /// </summary>
    public readonly ButtonVR.ButtonState state;

    /// <summary>
    /// Button constructor
    /// </summary>
    public ButtonStateVR(bool isActive, bool isSticky, bool isTouched, bool isClicked, float buttonHeight, float elapsedTime, ButtonVR.ButtonState state)
    {
        this.isActive = isActive;
        this.isSticky = isSticky;
        this.isTouched = isTouched;
        this.isClicked = isClicked;
        this.buttonHeight = buttonHeight;
        this.elapsedTime = elapsedTime;
        this.state = state;
    }
}
