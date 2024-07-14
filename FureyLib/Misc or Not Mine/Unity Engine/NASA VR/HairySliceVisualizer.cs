
// Hairy Slice Visualizer Script
// by Kyle Furey for NASA VR Project

// REQUIREMENTS: Flow Files, HairySlice.cs, ClippingPlane.cs, RaygunVR.cs

using UnityEngine;

/// <summary>
/// Allows easy visualization of hairy slice hairs based on input from a clipping plane.
/// </summary>
public class HairySliceVisualizer : MonoBehaviour, IRaygunShootable
{
    [Header("Allows easy visualization of hairy slice hairs based on input from a clipping plane.")]

    [Header("\nCONFIGURATION")]

    [Header("Reference to the hairy slice:")]
    [SerializeField] private HairySlice slice = null;

    [Header("Reference to the clipping plane:")]
    [SerializeField] private ClippingPlane plane = null;

    /// <summary>
    /// The current active hair
    /// </summary>
    private GameObject currentHair = null;

    /// <summary>
    /// IRaygunShootable - Shows the hairy slice based on the current hit point. Hit point is calculated based on a plane primitive.
    /// </summary>
    /// <param name="hit"></param>
    public void OnRaygunHit(RaycastHit hit)
    {
        if (currentHair != null)
        {
            currentHair.active = false;
        }

        GameObject gameObject = new GameObject();

        gameObject.transform.position = hit.point;

        gameObject.transform.parent = hit.transform;

        Vector2 coordinate = new Vector2
        (
            plane.axis != ParticleVisibility.Axis.Z ? 1 - (gameObject.transform.localPosition.x + 0.5f) : gameObject.transform.localPosition.x + 0.5f,
            plane.axis == ParticleVisibility.Axis.X ? 1 - (gameObject.transform.localPosition.z + 0.5f) : (gameObject.transform.localPosition.z + 0.5f
        ));

        Destroy(gameObject);

        Vector3Int vector = plane.GetNearestCoordinate(coordinate, slice.hairCount);

        int index = slice.GetIndex(vector.x, vector.y, vector.z);

        slice.hairs[index].active = true;

        currentHair = slice.hairs[index];
    }
}
