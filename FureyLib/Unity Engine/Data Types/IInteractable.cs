
// IInteractable Interface Script
// by Kyle Furey

using UnityEngine;

// Inherit from this interface to implement it

/// <summary>
/// Contracts a function that allows an object to be interacted with.
/// </summary>
public interface IInteractable
{
    /// <summary>
    /// When this object is interacted with.
    /// </summary>
    /// <param name="interactor">The object that is interacting with this object.</param>
    /// <returns>Whether the interaction was successful.</returns>
    public abstract bool OnInteract(GameObject interactor);
}
