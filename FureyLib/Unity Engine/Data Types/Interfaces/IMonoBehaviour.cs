// .cs
// Unity MonoBehaviour Interface
// by Kyle Furey

using UnityEngine;

/// <summary>
/// Base interface for component interfaces.
/// </summary>
public interface IMonoBehaviour
{
    /// <summary>
    /// Unity name property.
    /// </summary>
    public string name { get; set; }

    /// <summary>
    /// Unity transform property.
    /// </summary>
    public Transform transform { get; }

    /// <summary>
    /// Unity game object property.
    /// </summary>
    public GameObject gameObject { get; }

    /// <summary>
    /// Unity tag property.
    /// </summary>
    public string tag { get; set; }

    /// <summary>
    /// Unity enabled property.
    /// </summary>
    public bool enabled { get; set; }
}
