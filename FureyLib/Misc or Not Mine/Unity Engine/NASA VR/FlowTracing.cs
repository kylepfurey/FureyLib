
// Flow Data Beam Tracing Script
// by Kyle Furey for NASA VR Project

// REQUIREMENTS: ParticleVisibility.cs, FlowParticle.cs, IMEF Functions.cs, RaygunVR.cs

using System.Collections.Generic;
using System.Threading.Tasks;
using UnityEngine;
using static UnityEngine.Mathf;
using static UnityEngine.Vector3;
using static IMEF;

/// <summary>
/// Traces a beam following a particle through the attached flow data cube based on a hit point.
/// </summary>
public class FlowTracing : MonoBehaviour, IRaygunShootable
{
    [Header("Traces a beam following a particle through the attached flow data cube based on a hit point.")]

    [Header("\nCONFIGURATION")]

    [Header("Reference to the flow data cube:")]
    [SerializeField] private ParticleVisibility flowData = null;

    [Header("The particle to instantiate at the hit point:")]
    [SerializeField] private GameObject particlePrefab = null;
    [SerializeField] private int particleLayer = 8;

    [Header("Settings for the traced beam:")]
    public float updateTime = 0.01f;
    public float width = 0.01f;
    public int maxNumberOfBeams = 10;

    [Header("The color mode to apply to the beam:")]
    public BeamColorMode colorMode = BeamColorMode.Direction;

    [Header("The color and intensity to trace the beam:")]
    public Color color = Color.red;
    public float intensity = 5;

    [Header("Whether rayguns can only cause particle tracing:")]
    public bool onlyRaygunCollisions = false;

    /// <summary>
    /// Ray color mode enum
    /// </summary>
    public enum BeamColorMode { Color, Direction, Velocity, Density, Magnetic, Coordinate };

    /// <summary>
    /// All of the traced lines in order of each game object
    /// </summary>
    private List<List<GameObject>> tracedLines = new List<List<GameObject>>();


    // PARTICLE COLLISION

    /// <summary>
    /// Checks for entering collisions with new particles
    /// </summary>
    /// <param name="collision"></param>
    private void OnCollisionEnter(Collision collision)
    {
        FlowParticle particle = collision.gameObject.GetComponent<FlowParticle>();

        particle.gameObject.layer = 8;

        if (!onlyRaygunCollisions && particle != null)
        {
            tracedLines.Add(new List<GameObject>());

            if (tracedLines.Count > maxNumberOfBeams)
            {
                for (int i = 0; i < tracedLines[0].Count; i++)
                {
                    Destroy(tracedLines[0][i]);
                }

                tracedLines.RemoveAt(0);
            }

            TraceParticlePath(particle, tracedLines[tracedLines.Count - 1]);
        }
    }

    /// <summary>
    /// IRaygunShootable - Traces a beam through the data based on the raygun's hit point.
    /// </summary>
    /// <param name="hit"></param>
    public void OnRaygunHit(RaycastHit hit)
    {
        if (flowData != null)
        {
            if (particlePrefab != null)
            {
                FlowParticle particle = Instantiate(particlePrefab).GetComponent<FlowParticle>();

                particle.gameObject.layer = 8;

                Vector3 hitPoint = GetRelativeToBounds(hit.point);

                hitPoint.x = Clamp(hitPoint.x, 0, 100);
                hitPoint.y = Clamp(hitPoint.y, 0, 100);
                hitPoint.z = Clamp(hitPoint.z, 0, 100);

                hitPoint = GetBoundsToWorld(hitPoint);

                particle.transform.position = hitPoint;

                tracedLines.Add(new List<GameObject>());

                if (tracedLines.Count > maxNumberOfBeams)
                {
                    for (int i = 0; i < tracedLines[0].Count; i++)
                    {
                        Destroy(tracedLines[0][i]);
                    }

                    tracedLines.RemoveAt(0);
                }

                TraceParticlePath(particle, tracedLines[tracedLines.Count - 1]);
            }
        }
    }


    // TRACING PARTICLE

    /// <summary>
    /// Follows and traces a particle over time
    /// </summary>
    /// <returns></returns>
    private async Task TraceParticlePath(FlowParticle particle, List<GameObject> list)
    {
        Vector3 start = particle.transform.position;

        await Task.Delay((int)(updateTime * 1000));

        if (!Application.isPlaying || !particle.InBounds())
        {
            particle.gameObject.layer = 0;
        }

        Vector3 end = particle.transform.position;

        Renderer beam = GameObject.CreatePrimitive(PrimitiveType.Cube).GetComponent<Renderer>();

        beam.name = "Particle Tracer Ray";

        beam.GetComponent<Collider>().enabled = false;

        beam.transform.position = start;

        beam.transform.LookAt(end);

        float distance = Distance(start, end);

        beam.transform.position += beam.transform.forward * (distance / 2);

        beam.transform.localScale = new Vector3(width, width, distance);

        Color color = this.color;

        Vector3 vector;

        switch (colorMode)
        {
            case BeamColorMode.Direction:

                vector = beam.transform.forward;

                if (vector.x <= 0)
                {
                    vector.x = Abs(vector.x);
                }

                if (vector.y <= 0)
                {
                    vector.y = Abs(vector.y);
                }

                if (vector.z <= 0)
                {
                    vector.z = Abs(vector.z);
                }

                color = new Color(vector.x, vector.y, vector.z, color.a);

                break;

            case BeamColorMode.Velocity:

                vector = flowData.flowFile.Sample(GetRelativeToBounds(particle.transform.position)).normalized;

                if (vector.x <= 0)
                {
                    vector.x = Abs(vector.x);
                }

                if (vector.y <= 0)
                {
                    vector.y = Abs(vector.y);
                }

                if (vector.z <= 0)
                {
                    vector.z = Abs(vector.z);
                }

                color = new Color(vector.x, vector.y, vector.z, color.a);

                break;

            case BeamColorMode.Density:

                vector = GetDensity(particle.transform.position).normalized;

                if (vector.x <= 0)
                {
                    vector.x = Abs(vector.x);
                }

                if (vector.y <= 0)
                {
                    vector.y = Abs(vector.y);
                }

                if (vector.z <= 0)
                {
                    vector.z = Abs(vector.z);
                }

                color = new Color(vector.x, vector.y, vector.z, color.a);

                break;

            case BeamColorMode.Magnetic:

                vector = BDipole(GetRelativeToBounds(particle.transform.position)).normalized;

                if (vector.x <= 0)
                {
                    vector.x = Abs(vector.x);
                }

                if (vector.y <= 0)
                {
                    vector.y = Abs(vector.y);
                }

                if (vector.z <= 0)
                {
                    vector.z = Abs(vector.z);
                }

                color = new Color(vector.x, vector.y, vector.z, color.a);

                break;

            case BeamColorMode.Coordinate:

                vector = GetRelativeToBounds(particle.transform.position).normalized;

                if (vector.x <= 0)
                {
                    vector.x = Abs(vector.x);
                }

                if (vector.y <= 0)
                {
                    vector.y = Abs(vector.y);
                }

                if (vector.z <= 0)
                {
                    vector.z = Abs(vector.z);
                }

                color = new Color(vector.x, vector.y, vector.z, color.a);

                break;
        }

        beam.sharedMaterial = new Material(beam.sharedMaterial);

        beam.sharedMaterial.SetColor("_BaseColor", color);

        beam.sharedMaterial.SetColor("_EmissionColor", color * intensity);

        beam.sharedMaterial.EnableKeyword("_EMISSION");

        list.Add(beam.gameObject);

        if (particle != null && particle.InBounds())
        {
            TraceParticlePath(particle, list);
        }
    }


    // HELPER FUNCTIONS

    /// <summary>
    /// Converts a world position to a local position (0 - 100) of the particle bounds
    /// </summary>
    /// <param name="position"></param>
    /// <returns></returns>
    public Vector3 GetRelativeToBounds(Vector3 position)
    {
        GameObject flowDataScaleParent = flowData.transform.parent.transform.parent.gameObject;

        position = position - flowDataScaleParent.transform.position;

        position.x += flowData.particleOrigin.x * flowDataScaleParent.transform.localScale.x;
        position.z += flowData.particleOrigin.z * flowDataScaleParent.transform.localScale.z;

        position.x /= flowDataScaleParent.transform.localScale.x;
        position.y /= flowDataScaleParent.transform.localScale.y;
        position.z /= flowDataScaleParent.transform.localScale.z;

        position *= ParticleVisibility.particleScale;

        position.x = Round(position.x);
        position.y = Round(position.y);
        position.z = Round(position.z);

        return position;
    }

    /// <summary>
    /// Converts a local position (0 - 100) of the particle bounds to a world position
    /// </summary>
    /// <param name="position"></param>
    /// <returns></returns>
    public Vector3 GetBoundsToWorld(Vector3 position)
    {
        GameObject flowDataScaleParent = flowData.transform.parent.transform.parent.gameObject;

        position /= ParticleVisibility.particleScale;

        position.z *= flowDataScaleParent.transform.localScale.z;
        position.y *= flowDataScaleParent.transform.localScale.y;
        position.x *= flowDataScaleParent.transform.localScale.x;

        position.z -= flowData.particleOrigin.z * flowDataScaleParent.transform.localScale.z;
        position.x -= flowData.particleOrigin.x * flowDataScaleParent.transform.localScale.x;

        position += flowDataScaleParent.transform.position;

        return position;
    }

    /// <summary>
    /// mu0 mathematical constant
    /// </summary>
    public const double mu0 = 1.25663706 * 10e-6;

    /// <summary>
    /// Calculates the magnetic density
    /// </summary>
    /// <param name="position"></param>
    /// <returns></returns>
    public Vector3 GetDensity(Vector3 position)
    {
        FlowFile flowFile = flowData.flowFile;

        Vector3 J;

        float x = position.x;
        float y = position.y;
        float z = position.z;

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
}
