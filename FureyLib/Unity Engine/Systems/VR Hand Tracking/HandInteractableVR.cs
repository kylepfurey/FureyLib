
// VR Hand Interactable Object Template Script
// by Kyle Furey

// REQUIREMENTS: HandTrackerVR.cs

using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Events;

/// <summary>
/// Template for a new object interactable by VR hands.
/// </summary>
public class HandInteractableVR : MonoBehaviour, IHandInteractableVR
{
    [Header("Template for a new object interactable by VR hands.")]

    [Header("\nCONFIGURATION")]

    [Header("Example setting:")]
    [SerializeField] private bool setting = false;

    // New variables here

    /// <summary>
    /// IHandInteractableVR Interface - Called when VR hands are successfully set.
    /// </summary>
    public void OnSetHands()
    {
        // New hand tracking code here
    }

    /// <summary>
    /// IHandInteractableVR Interface - Removes the object's implementation to the interface.
    /// </summary>
    private void OnDestroy()
    {
        IHandInteractableVR.implementations.Remove(this);

        // New destructor code here
    }

    /// <summary>
    /// Awake() is called when the script is loaded
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
    /// Start() is called before the first frame update
    /// </summary>
    private void Start()
    {

    }

    /// <summary>
    /// Update() is called once per frame
    /// </summary>
    private void Update()
    {
        if (IHandInteractableVR.handsSet)
        {
            // New code here
        }
    }

    /// <summary>
    /// FixedUpdate() is called once per physics tick
    /// </summary>
    private void FixedUpdate()
    {
        if (IHandInteractableVR.handsSet)
        {
            // New code here
        }
    }

    /// <summary>
    /// LateUpdate() is called once per frame after Update
    /// </summary>
    private void LateUpdate()
    {
        if (IHandInteractableVR.handsSet)
        {
            // New code here
        }
    }

    // New functions here
}
