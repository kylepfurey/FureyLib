
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

    [Header("\nSETTINGS")]

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
    /// Called before start
    /// </summary>
    private void Awake()
    {

    }

    /// <summary>
    /// Called on start
    /// </summary>
    private void Start()
    {

    }

    /// <summary>
    /// Called every frame
    /// </summary>
    private void Update()
    {
        // Check the player's hands
        if (IHandInteractableVR.handsSet)
        {
            // New code here
        }
    }

    // New functions here
}
