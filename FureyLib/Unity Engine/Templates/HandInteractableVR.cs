
// VR Hand Interactable Object Template Script
// by Kyle Furey

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
    /// IHandInteractableVR Interface - Adds the object as an implementation to the interface.
    /// </summary>
    public HandInteractableVR()
    {
        IHandInteractableVR.implementations.Add(this);
    }

    /// <summary>
    /// IHandInteractableVR Interface - Removes the object's implementation to the interface.
    /// </summary>
    ~HandInteractableVR()
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
    /// Awake() is called when the script is loaded
    /// </summary>
    private void Awake()
    {

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
