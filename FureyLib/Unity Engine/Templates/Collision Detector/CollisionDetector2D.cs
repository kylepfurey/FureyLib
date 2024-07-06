
// Template 2D Collision Detection Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Component used to send 2D collision information to a another component script when referenced.
/// </summary>
public class CollisionDetector2D : MonoBehaviour
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
    // NOTE FROM DEVELOPER: Change CollisionReceiver2D to your class! The collision functions must also be public!
    public List<CollisionReceiver2D> receivers = new List<CollisionReceiver2D>();

    /// <summary>
    /// Called when entering a 2D physical collision
    /// </summary>
    /// <param name="collision"></param>
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (active && sendPhysical)
        {
            for (int i = 0; i < receivers.Count; i++)
            {
                receivers[i].OnCollisionEnter2D(collision);
            }
        }
    }

    /// <summary>
    /// Called when overlapping a 2D physical collision
    /// </summary>
    /// <param name="collision"></param>
    private void OnCollisionStay2D(Collision2D collision)
    {
        if (active && sendPhysical)
        {
            for (int i = 0; i < receivers.Count; i++)
            {
                receivers[i].OnCollisionStay2D(collision);
            }
        }
    }

    /// <summary>
    /// Called when leaving a 2D physical collision
    /// </summary>
    /// <param name="collision"></param>
    private void OnCollisionExit2D(Collision2D collision)
    {
        if (active && sendPhysical)
        {
            for (int i = 0; i < receivers.Count; i++)
            {
                receivers[i].OnCollisionExit2D(collision);
            }
        }
    }

    /// <summary>
    /// Called when entering a 2D trigger collision
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerEnter2D(Collider2D other)
    {
        if (active && sendTrigger)
        {
            for (int i = 0; i < receivers.Count; i++)
            {
                receivers[i].OnTriggerEnter2D(other);
            }
        }
    }

    /// <summary>
    /// Called when overlapping a 2D trigger collision
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerStay2D(Collider2D other)
    {
        if (active && sendTrigger)
        {
            for (int i = 0; i < receivers.Count; i++)
            {
                receivers[i].OnTriggerStay2D(other);
            }
        }
    }

    /// <summary>
    /// Called when leaving a 2D trigger collision
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerExit2D(Collider2D other)
    {
        if (active && sendTrigger)
        {
            for (int i = 0; i < receivers.Count; i++)
            {
                receivers[i].OnTriggerExit2D(other);
            }
        }
    }
}

/// <summary>
/// Example class used to receive 2D collision information.
/// </summary>
public class CollisionReceiver2D : MonoBehaviour
{
    /// <summary>
    /// Called when entering a 2D physical collision
    /// </summary>
    /// <param name="collision"></param>
    public void OnCollisionEnter2D(Collision2D collision)
    {

    }

    /// <summary>
    /// Called when overlapping a 2D physical collision
    /// </summary>
    /// <param name="collision"></param>
    public void OnCollisionStay2D(Collision2D collision)
    {

    }

    /// <summary>
    /// Called when leaving a 2D physical collision
    /// </summary>
    /// <param name="collision"></param>
    public void OnCollisionExit2D(Collision2D collision)
    {

    }

    /// <summary>
    /// Called when entering a 2D trigger collision
    /// </summary>
    /// <param name="other"></param>
    public void OnTriggerEnter2D(Collider2D other)
    {

    }

    /// <summary>
    /// Called when overlapping a 2D trigger collision
    /// </summary>
    /// <param name="other"></param>
    public void OnTriggerStay2D(Collider2D other)
    {

    }

    /// <summary>
    /// Called when leaving a 2D trigger collision
    /// </summary>
    /// <param name="other"></param>
    public void OnTriggerExit2D(Collider2D other)
    {

    }
}
