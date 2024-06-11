
// Flow Particle Object Script
// by Kyle Furey for NASA VR Project

using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Movable rigidbody that is affected by particle field data.
/// </summary>
public class FlowParticle : MonoBehaviour
{
    [Header("\nVelocity Settings")]
    [SerializeField] private float velocitySpeed = 0.25f;
    [SerializeField] private float velocityLerp = 0.25f;

    [Header("Optimization")]
    [SerializeField] private float maxDistance = 50;
    [SerializeField] private float maxParticles = 5;

    /// <summary>
    /// The flow data file
    /// </summary>
    public static FlowFile flowFile = null;

    /// <summary>
    /// The flow particle's rigidbody
    /// </summary>
    private Rigidbody rigidbody = null;

    /// <summary>
    /// Reference to the flow data cube
    /// </summary>
    private ParticleVisibility flowData = null;

    /// <summary>
    /// Reference to the flow data cube's parent (used for scaling)
    /// </summary>
    private GameObject flowDataScaleParent = null;

    /// <summary>
    /// The number of particles currently spawned
    /// </summary>
    private static List<GameObject> particles = new List<GameObject>();

    /// <summary>
    /// The stored gravity setting of the rigidbody
    /// </summary>
    private bool gravitySetting = false;

    /// <summary>
    /// The total elapsed time this particle has been active in the data field
    /// </summary>
    private float elapsedTime = 0;

    /// <summary>
    /// Get the flow data and track this particle's number
    /// </summary>
    private void Awake()
    {
        // Find the data
        if (flowFile == null)
        {
            flowFile = FindFirstObjectByType<FlowFile>();
        }

        // Get and check the rigidbody
        rigidbody = GetComponent<Rigidbody>();

        if (rigidbody == null)
        {
            Debug.LogError("Rigidbody is missing for flow particle " + gameObject.name + "!");

            Destroy(gameObject);
        }

        // Add this particle to the list
        particles.Add(gameObject);

        // Remove the oldest particle if the particle count is greater then the allowed number of particles
        if (particles.Count > maxParticles)
        {
            Destroy(particles[0]);
        }
    }

    /// <summary>
    /// Distance check
    /// </summary>
    private void Update()
    {
        // Remove the particle if it is too far from the user
        if (Vector3.Distance(transform.position, VRUser.instance.transform.position) >= maxDistance)
        {
            // Destroy this object
            Destroy(gameObject);
        }

        // Increment elapsed time
        if (flowData != null)
        {
            elapsedTime += Time.deltaTime;
        }
    }

    /// <summary>
    /// Entering the flow data cube
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerEnter(Collider other)
    {
        // Check that we do not have flow data stored already
        if (flowData == null)
        {
            // Check if the collided game object is a flow data cube
            ParticleVisibility dataCube = other.gameObject.GetComponent<ParticleVisibility>();

            if (dataCube != null)
            {
                // Set the flow data
                flowData = dataCube;

                // Set the flow data's parent
                flowDataScaleParent = flowData.transform.parent.transform.parent.gameObject;

                // Store and ignore gravity
                gravitySetting = rigidbody.useGravity;

                rigidbody.useGravity = false;
            }
        }
    }

    /// <summary>
    /// Exiting the flow data cube
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerExit(Collider other)
    {
        // Check if we have flow data stored and if we are leaving the flow data cube
        if (flowData != null && other.gameObject == flowData.gameObject)
        {
            // Remove the flow data
            flowData = null;

            // Remove the flow data's parent
            flowDataScaleParent = null;

            // Reset the gravity setting
            rigidbody.useGravity = gravitySetting;

            // Reset elapsed time
            elapsedTime = 0;
        }
    }

    /// <summary>
    /// Moving the particle along the data field
    /// </summary>
    private void FixedUpdate()
    {
        // Check if the particle is in bounds and move it along the path of the flow data
        if (flowData != null)
        {
            // Update the particle velocity
            rigidbody.velocity = Vector3.Lerp(rigidbody.velocity, TranslateRelative(flowDataScaleParent.transform, flowFile.Sample(GetRelativeToBounds(transform.position)) * velocitySpeed) - flowDataScaleParent.transform.position, velocityLerp);
        }
    }

    /// <summary>
    /// Update the particle count and list of particles
    /// </summary>
    private void OnDestroy()
    {
        // Remove this particle
        particles.Remove(gameObject);
    }

    /// <summary>
    /// Converts a world position to a local position (0 - 100) of the particle bounds
    /// </summary>
    /// <param name="position"></param>
    /// <returns></returns>
    private Vector3 GetRelativeToBounds(Vector3 position)
    {
        position = position - flowDataScaleParent.transform.position;

        position.x += flowData.particleOrigin.x * flowDataScaleParent.transform.localScale.x;
        position.z += flowData.particleOrigin.z * flowDataScaleParent.transform.localScale.z;

        position.x /= flowDataScaleParent.transform.localScale.x;
        position.y /= flowDataScaleParent.transform.localScale.y;
        position.z /= flowDataScaleParent.transform.localScale.z;

        return position * ParticleVisibility.particleScale;
    }

    /// <summary>
    /// Returns an offset vector3 based on the relative transform and given offset vector 3
    /// </summary>
    /// <param name="transform"></param>
    /// <param name="offset"></param>
    /// <returns></returns>
    private static Vector3 TranslateRelative(Transform transform, Vector3 offset)
    {
        Vector3 directionX = transform.right * offset.x;
        Vector3 directionY = transform.up * offset.y;
        Vector3 directionZ = transform.forward * offset.z;

        return transform.position + directionX + directionY + directionZ;
    }
}
