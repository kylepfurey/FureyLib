
// VR Hand Pointing and Teleporter Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine.Events;
using UnityEngine.UI;
using UnityEngine;

/// <summary>
/// Used to detect when the player is pointing using hand tracking in VR, as well as specific interactions through pointing.
/// </summary>
public class HandPointerVR : MonoBehaviour
{
    [Header("Used to detect when the player is pointing using hand tracking in VR, as well as specific interactions through pointing.")]

    [Header("POINTING SETTINGS")]

    [Header("The player's body GameObject:")]
    [SerializeField] private GameObject player = null;

    // The hand game objects
    [HideInInspector] public GameObject leftHand = null;
    [HideInInspector] public GameObject rightHand = null;
    private GameObject leftHandTip = null;
    private GameObject rightHandTip = null;

    [Header("A cube \"beam\" indicating where the player is pointing:")]
    [SerializeField] private GameObject pointer = null;

    // Whether the player's hands are currently in a pointing state
    private bool isPointingLeft = false;
    private bool isPointingRight = false;

    // What the player is pointing at
    private RaycastHit hit;

    [Header("TELEPORTATION SETTINGS")]

    // Whether the player is in the middle of teleporting
    private bool isTeleporting = false;

    [Header("Whether the player can teleport with their right hand or left hand:")]
    [SerializeField] private bool canTeleportLeft = true;
    [SerializeField] private bool canTeleportRight = true;

    [Header("The time required to teleport via pointing at a teleporter and the delay after a successful teleport (should be synced with the fade):")]
    [SerializeField] private float teleportTimer = 0;
    [SerializeField] private float teleportTime = 1.5f;
    [SerializeField] private float teleportDelay = 0.9f;

    [Header("The offset rotation to add to the pointer's rotation:")]
    [SerializeField] private Vector3 pointerOffset = new Vector3(0, 0, 0);

    [Header("The tag a trigger must have to be a teleporter:")]
    [SerializeField] private string teleportTag = "Anchor";

    [Header("Events triggered by teleporting (fading the screen should be one):")]
    [SerializeField] private UnityEvent OnTeleport = null;

    [Header("TELEPORTATION UI")]

    [Header("The slider and its components indicating when the player is currently teleporting:")]
    [SerializeField] private Slider slider = null;
    [SerializeField] private List<Image> sliderImages = new List<Image>();
    [SerializeField] private float sliderFadeSpeed = 300;

    // Set this object's hands
    public void SetHands()
    {
        leftHand = HandTrackerVR.leftHand.index;

        leftHandTip = HandTrackerVR.leftHand.indexTip;

        rightHand = HandTrackerVR.rightHand.index;

        rightHandTip = HandTrackerVR.rightHand.indexTip;
    }

    private void Start()
    {
        leftHand = null;

        rightHand = null;

        // Hide the slider
        for (int i = 0; i < sliderImages.Count; i++)
        {
            sliderImages[i].color = new Vector4(sliderImages[i].color.r, sliderImages[i].color.g, sliderImages[i].color.b, 0);
        }
    }

    private void Update()
    {
        // Check the player's hands
        if (leftHand != null && rightHand != null)
        {
            // POINTING INPUT

            isPointingLeft = HandTrackerVR.GetGesture(HandVR.Gesture.Point, false);

            isPointingRight = HandTrackerVR.GetGesture(HandVR.Gesture.Point, true);


            // TELEPORTATION

            // Teleportation with right hand
            if (canTeleportRight && isPointingRight)
            {
                CheckTeleport(isPointingRight, rightHand.transform.position, rightHand.transform.rotation, rightHandTip.transform.position);
            }
            // Teleportation with left hand
            else if (canTeleportLeft)
            {
                CheckTeleport(isPointingLeft, leftHand.transform.position, leftHand.transform.rotation, leftHandTip.transform.position);
            }
        }
    }

    // Checking if the player is teleporting
    private void CheckTeleport(bool isPointing, Vector3 aimPosition, Quaternion aimRotation, Vector3 tip)
    {
        // Offset the pointer's rotation
        aimRotation.eulerAngles += pointerOffset;

        // Set the slider value
        slider.value = teleportTimer / teleportTime;

        // Is the player pointing
        if (isPointing && !isTeleporting)
        {
            // Does the player hit something
            if (Physics.Raycast(aimPosition, aimRotation * Vector3.forward, out hit, 100, ~(1 << 2), QueryTriggerInteraction.Collide))
            {
                // Update the pointer
                if (pointer != null)
                {
                    pointer.active = true;

                    pointer.transform.parent = null;

                    pointer.transform.position = tip;

                    pointer.transform.LookAt(hit.point);

                    pointer.transform.localScale = new Vector3(pointer.transform.localScale.x, pointer.transform.localScale.y, hit.distance);

                    pointer.transform.position += pointer.transform.localScale.z / 2 * pointer.transform.forward;
                }

                // Is the player hitting a teleport anchor
                if (hit.transform.tag == teleportTag)
                {
                    // Increment timer
                    teleportTimer += Time.deltaTime;

                    // Has the player pointed at the anchor for teleportTime number of seconds
                    if (teleportTimer > teleportTime)
                    {
                        // Teleport the player and reset the teleport timer
                        OnTeleport.Invoke();

                        Invoke("Teleport", teleportDelay);

                        isTeleporting = true;

                        return;
                    }

                    // Fade the slider in
                    for (int i = 0; i < sliderImages.Count; i++)
                    {
                        sliderImages[i].color = new Vector4(sliderImages[i].color.r, sliderImages[i].color.g, sliderImages[i].color.b, Mathf.Max(sliderImages[i].color.a + (sliderFadeSpeed * Time.deltaTime / 255), 0));
                    }
                }

                return;
            }
            else
            {
                // Update the pointer
                if (pointer != null)
                {
                    pointer.active = true;

                    pointer.transform.parent = null;

                    pointer.transform.position = tip;

                    pointer.transform.LookAt(aimRotation * Vector3.forward * 100);

                    pointer.transform.localScale = new Vector3(pointer.transform.localScale.x, pointer.transform.localScale.y, 100);

                    pointer.transform.position += pointer.transform.localScale.z / 2 * pointer.transform.forward;
                }
            }
        }
        else if (isTeleporting)
        {
            teleportTimer = teleportTime;

            // Fade the slider out
            for (int i = 0; i < sliderImages.Count; i++)
            {
                sliderImages[i].color = new Vector4(sliderImages[i].color.r, sliderImages[i].color.g, sliderImages[i].color.b, Mathf.Min(sliderImages[i].color.a - (sliderFadeSpeed * Time.deltaTime / 255), 1));
            }

            // Remove the pointer
            if (pointer != null)
            {
                pointer.active = false;
            }

            return;
        }
        else
        {
            // Remove the pointer
            if (pointer != null)
            {
                pointer.active = false;
            }
        }

        // Reset the teleport timer
        teleportTimer -= Time.deltaTime;
        teleportTimer = Mathf.Max(teleportTimer, 0);

        // Fade the slider out
        for (int i = 0; i < sliderImages.Count; i++)
        {
            sliderImages[i].color = new Vector4(sliderImages[i].color.r, sliderImages[i].color.g, sliderImages[i].color.b, Mathf.Min(sliderImages[i].color.a - (sliderFadeSpeed * Time.deltaTime / 255), 1));
        }
    }

    // Teleport to the current hit object
    private void Teleport()
    {
        player.transform.position = new Vector3(hit.collider.transform.position.x, player.transform.position.y, hit.collider.transform.position.z);

        player.transform.eulerAngles = new Vector3(player.transform.eulerAngles.x, hit.collider.transform.eulerAngles.y, player.transform.eulerAngles.z);

        teleportTimer = 0;

        isTeleporting = false;

        // Hide the slider
        for (int i = 0; i < sliderImages.Count; i++)
        {
            sliderImages[i].color = new Vector4(sliderImages[i].color.r, sliderImages[i].color.g, sliderImages[i].color.b, 0);
        }
    }
}
