
// Flow Particle Object Script
// by Kyle Furey for NASA VR Project

using System.Collections.Generic;
using UnityEngine;
using static UnityEngine.Mathf;
using static UnityEngine.Vector3;
using static IMEF;

/// <summary>
/// Movable rigidbody that is affected by particle field data.
/// </summary>
public class FlowParticle : MonoBehaviour
{
    [Header("Movable rigidbody that is affected by particle field data.")]

    [Header("\nVelocity Settings")]
    [SerializeField] private float velocitySpeed = 1;
    [SerializeField] private float velocityLerp = 0.25f;

    [Header("Particle Settings")]
    public float q = 1;
    public float gs = 1;
    public float kp = 1;
    public bool flowLikeOceanCurrent = false;

    [Header("Optimization")]
    [SerializeField] private float maxDistance = 50;
    [SerializeField] private float maxParticles = 5;

    /// <summary>
    /// The flow data file
    /// </summary>
    [HideInInspector] public FlowFile flowFile = null;

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


    // STATIC VARIABLES

    /// <summary>
    /// The unmodified velocity of the boris function
    /// </summary>
    public static Vector3 borisVelocity = zero;

    /// <summary>
    /// Position of particle in the flow data
    /// </summary>
    public static Vector3 position = zero;

    /// <summary>
    /// Velocity of particle in the flow data
    /// </summary>
    public static Vector3 velocity = zero;

    /// <summary>
    /// Density of particle in the flow data
    /// </summary>
    public static Vector3 density = zero;

    /// <summary>
    /// Direction of particle in the flow data
    /// </summary>
    public static Vector3 direction = zero;

    /// <summary>
    /// Magnetic field of particle in the flow data
    /// </summary>
    public static Vector3 magnetic = zero;


    // FUNCTIONS

    /// <summary>
    /// Get the flow data and track this particle's number
    /// </summary>
    private void Awake()
    {
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
        if (DistanceSquared(transform.position, VRUser.instance.transform.position) >= maxDistance * maxDistance)
        {
            // Destroy this object
            Destroy(gameObject);
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

                // Set the flow file
                flowFile = other.GetComponentInChildren<FlowFile>();

                // Set the flow data's parent
                flowDataScaleParent = flowData.transform.parent.transform.parent.gameObject;

                // Store and ignore gravity
                gravitySetting = rigidbody.useGravity;

                rigidbody.useGravity = false;

                // Reset boris velocity
                borisVelocity = zero;
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

            // Remove the flow file
            flowFile = null;

            // Remove the flow data's parent
            flowDataScaleParent = null;

            // Reset the gravity setting
            rigidbody.useGravity = gravitySetting;
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
            if (flowLikeOceanCurrent)
            {
                rigidbody.velocity = Lerp(rigidbody.velocity, TranslateRelative(flowDataScaleParent.transform, flowFile.Sample(GetRelativeToBounds(transform.position)) * velocitySpeed / 4) - flowDataScaleParent.transform.position, velocityLerp);
            }
            else
            {
                rigidbody.velocity = Lerp(rigidbody.velocity, TranslateRelative(flowDataScaleParent.transform, BorisStep(GetRelativeToBounds(transform.position), borisVelocity) * velocitySpeed * 100) - flowDataScaleParent.transform.position, velocityLerp);
            }

            // Update the static variables
            position = GetRelativeToBounds(transform.position);
            velocity = flowFile.Sample(position);
            density = GetDensity(position);
            direction = velocity.normalized;
            magnetic = IMEF.BDipole(position).normalized;
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
    /// Calculates the next velocity value using a modified version of the IMEF.Boris() function
    /// </summary>
    public Vector3 BorisStep(Vector3 r0, Vector3 v0)
    {
        var RE = 6371000;
        RE = 1;

        // Calculate stepsize (dt) to be no bigger than half the gyroperiod
        var gyroperiod = (2 * PI) / ((Abs(q) * Mag(BDipole(r0 * RE))) / rigidbody.mass);
        var dt = 0.01f * gyroperiod;

        Vector3 rdat;
        Vector3 vdat;

        // Set initial conditions
        var rnew = r0;
        var vnew = v0;

        // Set current position and velocity (cartesian coords)
        var r = rnew; // rdat[i]
        var v = vnew; // vdat[i]

        // Compute B-field [T]
        var B0 = BDipole(r * RE, false);

        // Compute convection E-field [mV/m]
        var EC = VSEField(r, gs, kp, false);

        // Compute corotation E-field [mV/m]
        var ER = CorotationEField(r, false);

        // Compute total E-field and covert to [V/m]
        var E0 = (EC + ER) * 1e-3f;
        // var E0 = zero;

        // c0, ax, bx - arbitrary; to break down equation
        var c0 = (dt * q * B0) / (2 * rigidbody.mass);

        // Push step 1 - update velocity with half electrostatic contribution
        var v1 = v + ((q * E0 * dt) / (2 * rigidbody.mass));

        // Push step 2 - rotated via the magnetic field contribution
        var ax = v1 + (Cross(v1, c0));
        // var bx = (2 * c0) / (1 + (n * Pow(c0, 2))); POWER OF c0
        var bx = (2 * c0) / (1 + (Dot(c0, c0)));
        var v2 = v1 + (Cross(ax, bx));

        // Push step 3 - updated again with another half of the electrostatic push [m/s]
        vnew = v2 + ((q * E0 * dt) / (2 * rigidbody.mass));

        // Append to data arrays
        vdat = vnew;             // Velcoity [m/s]

        borisVelocity = vdat;

        return vdat;
    }

    /// <summary>
    /// mu0 mathematical constant
    /// </summary>
    public const double mu0 = 1.25663706 * 10e-6;

    /// <summary>
    /// Calculates the magnetic density
    /// </summary>
    /// <param name="coords"></param>
    /// <returns></returns>
    private Vector3 GetDensity(Vector3 coords)
    {
        Vector3 J;

        float x = coords.x;
        float y = coords.y;
        float z = coords.z;

        /*
        DENSITY EQUATION

        The current density, J, can be calculated from the magnetic field, B.

        •	We know Bi = (Bxi, Byi, Bzi) at point xi = (xi, yi, zi), where i is a grid cell.

        •	The current density Ji = (Jxi, Jyi, Jzi) at cell i can be calculated as:

        •	mu0 = 1.25663706 × 10-6

        •	Jxi = 1e-6 * mu0 * { [Bz(i+1) - Bz(i-1)] / [y(i+1) - y(i-1)] - [By(i+1) - By(i-1)] / [z(i+1) - z(i-1)] }

        •	Jyi = 1e-6 * mu0 * { [Bx(i+1) - Bx(i-1)] / [z(i+1) - z(i-1)] - [Bz(i+1) - Bz(i-1)] / [x(i+1) - x(i-1)] }

        •	Jzi = 1e-6 * mu0 * { [By(i+1) - By(i-1)] / [x(i+1) - x(i-1)] - [Bx(i+1) - Bx(i-1)] / [y(i+1) - y(i-1)] }
        */

        J.x = (float)
              (1e-6 / mu0 * (flowFile.Sample(new Vector3(x + 1, y + 1, z + 1)).z - flowFile.Sample(new Vector3(x - 1, y - 1, z - 1)).z)
              /
              ((new Vector3(x + 1, y + 1, z + 1).y - new Vector3(x - 1, y - 1, z - 1).y))
              -
              (flowFile.Sample(new Vector3(x + 1, y + 1, z + 1)).y - flowFile.Sample(new Vector3(x - 1, y - 1, z - 1)).y)
              /
              ((new Vector3(x + 1, y + 1, z + 1).z - new Vector3(x - 1, y - 1, z - 1).z)));

        J.y = (float)
              (1e-6 / mu0 * (flowFile.Sample(new Vector3(x + 1, y + 1, z + 1)).x - flowFile.Sample(new Vector3(x - 1, y - 1, z - 1)).x)
              /
              ((new Vector3(x + 1, y + 1, z + 1).z - new Vector3(x - 1, y - 1, z - 1).z))
              -
              (flowFile.Sample(new Vector3(x + 1, y + 1, z + 1)).z - flowFile.Sample(new Vector3(x - 1, y - 1, z - 1)).z)
              /
              ((new Vector3(x + 1, y + 1, z + 1).x - new Vector3(x - 1, y - 1, z - 1).x)));

        J.z = (float)
              (1e-6 / mu0 * (flowFile.Sample(new Vector3(x + 1, y + 1, z + 1)).y - flowFile.Sample(new Vector3(x - 1, y - 1, z - 1)).y)
              /
              ((new Vector3(x + 1, y + 1, z + 1).x - new Vector3(x - 1, y - 1, z - 1).x))
              -
              (flowFile.Sample(new Vector3(x + 1, y + 1, z + 1)).x - flowFile.Sample(new Vector3(x - 1, y - 1, z - 1)).x)
              /
              ((new Vector3(x + 1, y + 1, z + 1).y - new Vector3(x - 1, y - 1, z - 1).y)));

        return J;
    }

    /// <summary>
    /// Returns the squared distance between two vectors
    /// </summary>
    /// <param name="pointA"></param>
    /// <param name="pointB"></param>
    /// <returns></returns>
    private static float DistanceSquared(Vector3 pointA, Vector3 pointB)
    {
        float xDistance = pointA.x - pointB.x;
        float yDistance = pointA.y - pointB.y;
        float zDistance = pointA.z - pointB.z;

        return xDistance * xDistance + yDistance * yDistance + zDistance * zDistance;
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
