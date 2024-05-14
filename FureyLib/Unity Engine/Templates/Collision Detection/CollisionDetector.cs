
// Template 3D Collision Detection Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Component used to send 3D collision information to a another component script when referenced.
/// </summary>
public class CollisionDetector : MonoBehaviour
{
    [Header("Component used to send collision information to a another component script when referenced.")]

    [Header("\nDETECTION SETTINGS")]

    [Header("Whether this collision detector component is active:")]
    public bool active = true;

    [Header("Whether this collision detector component is active for physical collisions:")]
    public bool sendPhysical = true;

    [Header("Whether this collision detector component is active for trigger collisions:")]
    public bool sendTrigger = true;

    [Header("The components receiving the collision data:")]
    // NOTE FROM DEVELOPER: Change CollisionReceiver to your class! The collision functions must also be public!
    public List<CollisionReceiver> receivers = new List<CollisionReceiver>();

    /// <summary>
    /// Called when entering a 3D physical collision
    /// </summary>
    /// <param name="collision"></param>
    private void OnCollisionEnter(Collision collision)
    {
        if (active && sendPhysical)
        {
            for (int i = 0; i < receivers.Count; i++)
            {
                receivers[i].OnCollisionEnter(collision);
            }
        }
    }

    /// <summary>
    /// Called when overlapping a 3D physical collision
    /// </summary>
    /// <param name="collision"></param>
    private void OnCollisionStay(Collision collision)
    {
        if (active && sendPhysical)
        {
            for (int i = 0; i < receivers.Count; i++)
            {
                receivers[i].OnCollisionStay(collision);
            }
        }
    }

    /// <summary>
    /// Called when leaving a 3D physical collision
    /// </summary>
    /// <param name="collision"></param>
    private void OnCollisionExit(Collision collision)
    {
        if (active && sendPhysical)
        {
            for (int i = 0; i < receivers.Count; i++)
            {
                receivers[i].OnCollisionExit(collision);
            }
        }
    }

    /// <summary>
    /// Called when entering a 3D trigger collision
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerEnter(Collider other)
    {
        if (active && sendTrigger)
        {
            for (int i = 0; i < receivers.Count; i++)
            {
                receivers[i].OnTriggerEnter(other);
            }
        }
    }

    /// <summary>
    /// Called when overlapping a 3D trigger collision
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerStay(Collider other)
    {
        if (active && sendTrigger)
        {
            for (int i = 0; i < receivers.Count; i++)
            {
                receivers[i].OnTriggerStay(other);
            }
        }
    }

    /// <summary>
    /// Called when leaving a 3D trigger collision
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerExit(Collider other)
    {
        if (active && sendTrigger)
        {
            for (int i = 0; i < receivers.Count; i++)
            {
                receivers[i].OnTriggerExit(other);
            }
        }
    }
}

/// <summary>
/// Example class used to receive 3D collision information.
/// </summary>
public class CollisionReceiver : MonoBehaviour
{
    /// <summary>
    /// Called when entering a 3D physical collision
    /// </summary>
    /// <param name="collision"></param>
    public void OnCollisionEnter(Collision collision)
    {

    }

    /// <summary>
    /// Called when overlapping a 3D physical collision
    /// </summary>
    /// <param name="collision"></param>
    public void OnCollisionStay(Collision collision)
    {

    }

    /// <summary>
    /// Called when leaving a 3D physical collision
    /// </summary>
    /// <param name="collision"></param>
    public void OnCollisionExit(Collision collision)
    {

    }

    /// <summary>
    /// Called when entering a 3D trigger collision
    /// </summary>
    /// <param name="other"></param>
    public void OnTriggerEnter(Collider other)
    {

    }

    /// <summary>
    /// Called when overlapping a 3D trigger collision
    /// </summary>
    /// <param name="other"></param>
    public void OnTriggerStay(Collider other)
    {

    }

    /// <summary>
    /// Called when leaving a 3D trigger collision
    /// </summary>
    /// <param name="other"></param>
    public void OnTriggerExit(Collider other)
    {

    }
}
