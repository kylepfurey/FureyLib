
// Flow Data Particles Script
// by Kyle Furey for NASA VR Project

using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Creates particles and controls their visibility to accurately represent the flow data.
/// </summary>
[RequireComponent(typeof(ParticleSystem))]
public class ParticleVisibility : MonoBehaviour
{
    [Header("Creates particles and controls their visibility to accurately represent the flow data.")]

    [Header("\nDATA SETTINGS")]

    [Header("The list of files containing flow data:")]
    public List<FlowFile> flowFiles = null;

    [Header("The current file containing the data for the particles to represent:")]
    public FlowFile flowFile = null;

    /// <summary>
    /// The index of the current flow file
    /// </summary>
    private int index
    {
        get
        {
            return flowFiles.IndexOf(flowFile);
        }

        set
        {
            if (index >= 0 && index < flowFiles.Count && flowFiles[value] != null)
            {
                index = value;

                flowFile = flowFiles[index];
            }
            else
            {
                index = index;
            }
        }
    }

    [Header("Whether the bounds and origin for the particle system are static and do not change:")]
    public bool boundsAreStatic = true;

    [Header("The scale of the bounds for where particles may go:")]
    public Vector3 particleBounds = Vector3.one;

    [Header("The relative origin of the particle system:")]
    public Vector3 particleOrigin = new Vector3(0.5f, 0.5f, 0.5f);

    [Header("\nGRID SETTINGS")]

    [Header("The flow data cube's X plane:")]
    public GridGenerator xPlane = null;

    [Header("The flow data cube's Y plane:")]
    public GridGenerator yPlane = null;

    [Header("The flow data cube's Z plane:")]
    public GridGenerator zPlane = null;

    /// <summary>
    /// The scale of a particle's position
    /// </summary>
    public const float particleScale = 100;

    /// <summary>
    /// Particle system variables
    /// </summary>
    private ParticleSystem particleSystem;

    /// <summary>
    /// Particle variables
    /// </summary>
    private ParticleSystem.Particle[] particles;

    /// <summary>
    /// The flow data cube's collider
    /// </summary>
    private BoxCollider collider = null;

    /// <summary>
    /// Storage of the plane counts to check if they need to be updated
    /// </summary>
    private Vector2Int[] planeCounts = new Vector2Int[3];

    /// <summary>
    /// Axis enum
    /// </summary>
    public enum Axis { X, Y, Z };


    // FUNCTIONS

    /// <summary>
    /// Sets particle system variables
    /// </summary>
    private void Awake()
    {
        // Set the current flow file
        if (flowFile == null)
        {
            flowFile = flowFiles[0];

            if (flowFiles == null || flowFiles.Count == 0)
            {
                Debug.LogError("ERROR: No flow files have been assigned!");
            }
        }

        // Clamp the bounds
        particleBounds.x = Mathf.Clamp(particleBounds.x, 0, 1);
        particleBounds.y = Mathf.Clamp(particleBounds.y, 0, 1);
        particleBounds.z = Mathf.Clamp(particleBounds.z, 0, 1);

        // Clamp the origin
        particleOrigin.x = Mathf.Clamp(particleOrigin.x, 0, 1);
        particleOrigin.y = Mathf.Clamp(particleOrigin.y, 0, 1);
        particleOrigin.z = Mathf.Clamp(particleOrigin.z, 0, 1);

        // Gets the particle system
        particleSystem = GetComponent<ParticleSystem>();

        particles = new ParticleSystem.Particle[particleSystem.main.maxParticles];

        // Check for a collider
        if (collider == null)
        {
            collider = gameObject.AddComponent<BoxCollider>();
        }

        // Update the collider's trigger
        collider.isTrigger = true;

        // Update the collider's size
        collider.size = particleBounds;

        // Update the plane counts
        xPlane.includeZero = false;
        yPlane.includeZero = false;
        zPlane.includeZero = false;

        xPlane.count.x = (int)(particleBounds.x * 101);
        xPlane.count.y = (int)(particleBounds.z * 101);
        planeCounts[0].x = xPlane.count.x;
        planeCounts[0].y = xPlane.count.y;

        yPlane.count.x = (int)(particleBounds.x * 101);
        yPlane.count.y = (int)(particleBounds.y * 101);
        planeCounts[1].x = yPlane.count.x;
        planeCounts[1].y = yPlane.count.y;

        zPlane.count.x = (int)(particleBounds.z * 101);
        zPlane.count.y = (int)(particleBounds.y * 101);
        planeCounts[2].x = zPlane.count.x;
        planeCounts[2].y = zPlane.count.y;

        // Update the plane positions
        xPlane.transform.localPosition = new Vector3(Mathf.Clamp(particleOrigin.x, particleBounds.x / 2, 1 - particleBounds.x / 2), particleOrigin.y, Mathf.Clamp(particleOrigin.z, particleBounds.z / 2, 1 - particleBounds.z / 2)) * particleScale;
        yPlane.transform.localPosition = new Vector3(Mathf.Clamp(particleOrigin.x, particleBounds.x / 2, 1 - particleBounds.x / 2), Mathf.Clamp(particleOrigin.y, particleBounds.y / 2, 1 - particleBounds.y / 2), particleOrigin.z) * particleScale;
        zPlane.transform.localPosition = new Vector3(particleOrigin.x, Mathf.Clamp(particleOrigin.y, particleBounds.y / 2, 1 - particleBounds.y / 2), Mathf.Clamp(particleOrigin.z, particleBounds.z / 2, 1 - particleBounds.z / 2)) * particleScale;
    }

    /// <summary>
    /// Called every frame
    /// </summary>
    private void Update()
    {
        if (!boundsAreStatic)
        {
            UpdatePlanes();
        }

        // PARTICLE SYSTEM UPDATE -> CAMERA RENDER -> UPDATE PARTICLE

        // Updates the particles every frame (renders after the camera, causes flickering!)
        //UpdateParticle();
    }

    /// <summary>
    /// Called when the particle system itself updates
    /// </summary>
    private void OnParticleUpdateJobScheduled()
    {
        // PARTICLE SYSTEM UPDATE -> UPDATE PARTICLE -> CAMERA RENDER

        // Let the particle system update itself, but manually update the particles immediately after with an invoke call.
        // This ensures the particles are updated before the camera renders them (to prevent flickering).
        Invoke("UpdateParticles", 0);
    }


    // UPDATING PARTICLES

    /// <summary>
    /// Updates the clipping planes
    /// </summary>
    public void UpdatePlanes()
    {
        // Clamp the bounds
        particleBounds.x = Mathf.Clamp(particleBounds.x, 0, 1);
        particleBounds.y = Mathf.Clamp(particleBounds.y, 0, 1);
        particleBounds.z = Mathf.Clamp(particleBounds.z, 0, 1);

        // Clamp the origin
        particleOrigin.x = Mathf.Clamp(particleOrigin.x, 0, 1);
        particleOrigin.y = Mathf.Clamp(particleOrigin.y, 0, 1);
        particleOrigin.z = Mathf.Clamp(particleOrigin.z, 0, 1);

        // Update the collider's size
        collider.size = particleBounds;

        // Update the plane counts
        xPlane.count.x = (int)(particleBounds.x * 101);
        xPlane.count.y = (int)(particleBounds.z * 101);

        yPlane.count.x = (int)(particleBounds.x * 101);
        yPlane.count.y = (int)(particleBounds.y * 101);

        zPlane.count.x = (int)(particleBounds.z * 101);
        zPlane.count.y = (int)(particleBounds.y * 101);

        if (planeCounts[0].x != xPlane.count.x || planeCounts[0].y != xPlane.count.y)
        {
            if (xPlane.enabled)
            {
                xPlane.GenerateGrid();
            }

            planeCounts[0].x = xPlane.count.x;
            planeCounts[0].y = xPlane.count.y;
        }

        if (planeCounts[1].x != yPlane.count.x || planeCounts[1].y != yPlane.count.y)
        {
            if (yPlane.enabled)
            {
                yPlane.GenerateGrid();
            }

            planeCounts[1].x = yPlane.count.x;
            planeCounts[1].y = yPlane.count.y;
        }

        if (planeCounts[2].x != zPlane.count.x || planeCounts[2].y != zPlane.count.y)
        {
            if (zPlane.enabled)
            {
                zPlane.GenerateGrid();
            }

            planeCounts[2].x = zPlane.count.x;
            planeCounts[2].y = zPlane.count.y;
        }

        // Update the plane positions
        xPlane.transform.localPosition = new Vector3(Mathf.Clamp(particleOrigin.x, particleBounds.x / 2, 1 - particleBounds.x / 2), particleOrigin.y, Mathf.Clamp(particleOrigin.z, particleBounds.z / 2, 1 - particleBounds.z / 2)) * particleScale;
        yPlane.transform.localPosition = new Vector3(Mathf.Clamp(particleOrigin.x, particleBounds.x / 2, 1 - particleBounds.x / 2), Mathf.Clamp(particleOrigin.y, particleBounds.y / 2, 1 - particleBounds.y / 2), particleOrigin.z) * particleScale;
        zPlane.transform.localPosition = new Vector3(particleOrigin.x, Mathf.Clamp(particleOrigin.y, particleBounds.y / 2, 1 - particleBounds.y / 2), Mathf.Clamp(particleOrigin.z, particleBounds.z / 2, 1 - particleBounds.z / 2)) * particleScale;
    }

    /// <summary>
    /// Updates the particles
    /// </summary>
    private void UpdateParticles()
    {
        // Store the number of particles remaining
        int totalParticlesAlive = particleSystem.GetParticles(particles);

        // Loop through each particle
        for (int i = 0; i < totalParticlesAlive; ++i)
        {
            // OLD BOUNDS CHECK
            // if (flowFile.InBounds(particles[i].position))

            // Check if the particles are in the bounds of the set
            if (InBounds(particles[i].position))
            {
                // Update the particle's velocity
                particles[i].velocity = flowFile.Sample(particles[i].position);
            }
            else
            {
                // Remove the particle
                particles[i].remainingLifetime = -1f;
            }
        }

        // Update the number of particles
        particleSystem.SetParticles(particles, totalParticlesAlive);
    }


    // IN BOUNDS

    /// <summary>
    /// Determine if the given position is in bounds of the scaled set
    /// </summary>
    /// <param name="position"></param>
    /// <returns></returns>
    public bool InBounds(Vector3 position)
    {
        return (position.x / particleScale >= particleOrigin.x - particleBounds.x / 2) && (position.x / particleScale <= particleOrigin.x + particleBounds.x / 2) &&
               (position.y / particleScale >= particleOrigin.y - particleBounds.y / 2) && (position.y / particleScale <= particleOrigin.y + particleBounds.y / 2) &&
               (position.z / particleScale >= particleOrigin.z - particleBounds.z / 2) && (position.z / particleScale <= particleOrigin.z + particleBounds.z / 2);
    }


    // SETTERS

    /// <summary>
    /// Sets whether to display the X Y or Z plane
    /// </summary>
    public void ShowPlane(Axis axis, bool show)
    {
        switch (axis)
        {
            case Axis.X:

                xPlane.gameObject.active = show;

                return;

            case Axis.Y:

                yPlane.gameObject.active = show;

                return;

            case Axis.Z:

                zPlane.gameObject.active = show;

                return;
        }
    }

    /// <summary>
    /// Sets whether to display the X Y and Z planes
    /// </summary>
    public void ShowPlanes(bool show)
    {
        xPlane.gameObject.active = show;
        yPlane.gameObject.active = show;
        zPlane.gameObject.active = show;
    }

    /// <summary>
    /// Sets whether the bounds are static
    /// </summary>
    public void SetStaticBounds(bool isStatic)
    {
        boundsAreStatic = isStatic;
    }

    /// <summary>
    /// Updates the particle bounds
    /// </summary>
    public void SetParticleBounds(Vector3 bounds)
    {
        particleBounds = bounds;
    }

    /// <summary>
    /// Updates the particle bounds and origin
    /// </summary>
    public void SetParticleBounds(Vector3 bounds, Vector3 origin)
    {
        particleBounds = bounds;
        particleOrigin = origin;
    }

    /// <summary>
    /// Updates the flow file
    /// </summary>
    public void SetFlowFile(int index)
    {
        this.index = index;
    }

    /// <summary>
    /// Cycles the flow file
    /// </summary>
    public void CycleFlowFiles(int cycles = 1)
    {
        index = (index + cycles) % flowFiles.Count;
    }
}
