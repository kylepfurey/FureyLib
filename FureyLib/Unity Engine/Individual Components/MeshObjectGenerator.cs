
// Mesh Object Generator Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Generates a triangulated mesh object or a wireframe object of chosen game objects.
/// </summary>
public class MeshObjectGenerator : MonoBehaviour
{
    [Header("Generates a triangulated mesh object or a wireframe object of chosen game objects.")]

    [Header("\nMESH OBJECT SETTINGS")]

    [Header("The selected objects to generate mesh objects for:")]
    [SerializeField] private List<MeshFilter> selectedObjects = new List<MeshFilter>();
    private List<GameObject> generatedObjects = new List<GameObject>();

    [Header("The material to apply to generated meshes:")]
    [SerializeField] private Material material = null;

    [Header("Generates a mesh object for each of the selected game objects:")]
    [SerializeField] private bool GENERATE = false;

    [Header("Generates and explodes a mesh object for each of the selected game objects:")]
    [SerializeField] private bool EXPLODE = false;
    [SerializeField] private float distance = 0.1f;

    [Header("Generates a wireframe object for each of the selected game objects:")]
    [SerializeField] private bool WIREFRAME = false;
    [SerializeField] private float width = 0.01f;

    [Header("Clears all of this object's generated meshes:")]
    [SerializeField] private bool CLEAR = false;


    // EDITOR FUNCTIONS

    /// <summary>
    /// Checks for editor button inputs.
    /// </summary>
    private void OnValidate()
    {
        if (GENERATE)
        {
            GENERATE = false;

            Invoke("GenerateCurrent", 0);
        }

        if (EXPLODE)
        {
            EXPLODE = false;

            Invoke("ExplodeCurrent", 0);
        }

        if (WIREFRAME)
        {
            WIREFRAME = false;

            Invoke("WireframeCurrent", 0);
        }

        if (CLEAR)
        {
            CLEAR = false;

            Invoke("Clear", 0);
        }
    }

    /// <summary>
    /// Generates the current selected meshes.
    /// </summary>
    private void GenerateCurrent()
    {
        GenerateMeshObject(selectedObjects, material);
    }

    /// <summary>
    /// Explodes the current selected meshes.
    /// </summary>
    private void ExplodeCurrent()
    {
        ExplodeMesh(selectedObjects, distance, material);
    }

    /// <summary>
    /// Generates a wireframe of the current selected meshes.
    /// </summary>
    private void WireframeCurrent()
    {
        WireframeMesh(selectedObjects, width, material);
    }

    /// <summary>
    /// Destroys all generated objects in editor.
    /// </summary>
    private void Clear()
    {
        if (Application.isPlaying)
        {
            foreach (GameObject gameObject in generatedObjects)
            {
                Destroy(gameObject);
            }
        }
        else
        {
            foreach (GameObject gameObject in generatedObjects)
            {
                DestroyImmediate(gameObject);
            }
        }

        generatedObjects.Clear();
    }


    // MESH OBJECT

    /// <summary>
    /// Generates and triangulates a mesh object for the given mesh.
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="material"></param>
    /// <returns>The parent game object of the mesh object.</returns>
    public GameObject GenerateMeshObject(MeshFilter mesh, Material material = null)
    {
        return ExplodeMesh(mesh, 0, material);
    }

    /// <summary>
    /// Generates and triangulates a mesh object for each of the given meshes.
    /// </summary>
    /// <param name="meshes"></param>
    /// <param name="material"></param>
    /// <returns>A list of the parent mesh objects.</returns>
    public List<GameObject> GenerateMeshObject(IEnumerable<MeshFilter> meshes, Material material = null)
    {
        List<GameObject> meshObjects = new List<GameObject>();

        foreach (MeshFilter meshFilter in meshes)
        {
            meshObjects.Add(GenerateMeshObject(meshFilter, material));
        }

        return meshObjects;
    }

    /// <summary>
    /// Generates and triangulates a mesh object for each of the given meshes.
    /// </summary>
    /// <param name="meshes"></param>
    /// <returns>A list of the parent mesh objects.</returns>
    public List<GameObject> GenerateMeshObject(params MeshFilter[] meshes)
    {
        List<GameObject> meshObjects = new List<GameObject>(meshes.Length);

        foreach (MeshFilter meshFilter in meshes)
        {
            meshObjects.Add(GenerateMeshObject(meshFilter));
        }

        return meshObjects;
    }

    /// <summary>
    /// Generates and triangulates a mesh object for each of the given meshes.
    /// </summary>
    /// <param name="material"></param>
    /// <param name="meshes"></param>
    /// <returns>A list of the parent mesh objects.</returns>
    public List<GameObject> GenerateMeshObject(Material material, params MeshFilter[] meshes)
    {
        List<GameObject> meshObjects = new List<GameObject>(meshes.Length);

        foreach (MeshFilter meshFilter in meshes)
        {
            meshObjects.Add(GenerateMeshObject(meshFilter, material));
        }

        return meshObjects;
    }


    // EXPLODING MESHES

    /// <summary>
    /// Generates, triangulates, and explodes a mesh object for the given mesh.
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="distance"></param>
    /// <returns>The parent game object of the mesh object.</returns>
    public GameObject ExplodeMesh(MeshFilter mesh, float distance = 0.01f, Material material = null)
    {
        if (mesh == null)
        {
            return null;
        }

        GameObject parent = new GameObject(mesh.gameObject.name + " Mesh Object");

        parent.transform.position = mesh.transform.position;

        parent.transform.eulerAngles = mesh.transform.eulerAngles;

        parent.transform.localScale = mesh.transform.localScale;

        parent.AddComponent<MeshFilter>().sharedMesh = mesh.sharedMesh;

        parent.AddComponent<MeshCollider>().enabled = false;

        for (int i = 0; i < mesh.sharedMesh.triangles.Length; i += 3)
        {
            MeshFilter triangle = GameObject.CreatePrimitive(PrimitiveType.Plane).GetComponent<MeshFilter>();

            triangle.name = mesh.gameObject.name + " Triangle " + ((i + 3) / 3);

            triangle.transform.parent = parent.transform;

            triangle.transform.localPosition = Vector3.zero;

            triangle.transform.localEulerAngles = Vector3.zero;

            triangle.transform.localScale = Vector3.one;

            if (material != null)
            {
                triangle.GetComponent<MeshRenderer>().sharedMaterial = material;
            }

            triangle.GetComponent<MeshCollider>().enabled = false;

            Mesh newMesh = new Mesh();

            newMesh.name = mesh.gameObject.name + " Triangle " + ((i + 3) / 3);

            newMesh.vertices = new Vector3[3]
            {
                mesh.sharedMesh.vertices[mesh.sharedMesh.triangles[i]],
                mesh.sharedMesh.vertices[mesh.sharedMesh.triangles[i + 1]],
                mesh.sharedMesh.vertices[mesh.sharedMesh.triangles[i + 2]]
            };

            newMesh.normals = new Vector3[3]
            {
                mesh.sharedMesh.normals[mesh.sharedMesh.triangles[i]],
                mesh.sharedMesh.normals[mesh.sharedMesh.triangles[i + 1]],
                mesh.sharedMesh.normals[mesh.sharedMesh.triangles[i + 2]]
            };

            newMesh.triangles = new int[3]
            {
                0,
                1,
                2
            };

            triangle.sharedMesh = newMesh;

            triangle.transform.Translate(new Plane(newMesh.vertices[0], newMesh.vertices[1], newMesh.vertices[2]).normal * distance, Space.Self);
        }

        generatedObjects.Add(parent);

        return parent;
    }

    /// <summary>
    /// Generates, triangulates, and explodes a mesh object for each of the given meshes.
    /// </summary>
    /// <param name="meshes"></param>
    /// <param name="distance"></param>
    /// <returns>A list of the parent mesh objects.</returns>
    public List<GameObject> ExplodeMesh(IEnumerable<MeshFilter> meshes, float distance = 0.1f, Material material = null)
    {
        List<GameObject> meshObjects = new List<GameObject>();

        foreach (MeshFilter meshFilter in meshes)
        {
            meshObjects.Add(ExplodeMesh(meshFilter, distance, material));
        }

        return meshObjects;
    }

    /// <summary>
    /// Generates, triangulates, and explodes a mesh object for each of the given meshes.
    /// </summary>
    /// <param name="distance"></param>
    /// <param name="meshes"></param>
    /// <returns>A list of the parent mesh objects.</returns>
    public List<GameObject> ExplodeMesh(float distance, params MeshFilter[] meshes)
    {
        List<GameObject> meshObjects = new List<GameObject>(meshes.Length);

        foreach (MeshFilter meshFilter in meshes)
        {
            meshObjects.Add(ExplodeMesh(meshFilter, distance));
        }

        return meshObjects;
    }

    /// <summary>
    /// Generates, triangulates, and explodes a mesh object for each of the given meshes.
    /// </summary>
    /// <param name="distance"></param>
    /// <param name="meshes"></param>
    /// <returns>A list of the parent mesh objects.</returns>
    public List<GameObject> ExplodeMesh(float distance, Material material, params MeshFilter[] meshes)
    {
        List<GameObject> meshObjects = new List<GameObject>(meshes.Length);

        foreach (MeshFilter meshFilter in meshes)
        {
            meshObjects.Add(ExplodeMesh(meshFilter, distance, material));
        }

        return meshObjects;
    }


    // MESH WIREFRAMES

    /// <summary>
    /// Generates a wireframe object for the given mesh.
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="width"></param>
    /// <returns>The parent game object of the mesh object.</returns>
    public GameObject WireframeMesh(MeshFilter mesh, float width = 0.01f, Material material = null)
    {
        if (mesh == null)
        {
            return null;
        }

        GameObject parent = new GameObject(mesh.gameObject.name + " Wireframe Object");

        parent.transform.position = mesh.transform.position;

        parent.transform.eulerAngles = mesh.transform.eulerAngles;

        parent.AddComponent<MeshFilter>().sharedMesh = mesh.sharedMesh;

        parent.AddComponent<MeshCollider>().enabled = false;

        HashSet<Vector3> positions = new HashSet<Vector3>();

        for (int i = 0; i < mesh.sharedMesh.triangles.Length; i += 3)
        {
            for (int j = 0; j < 3; j++)
            {
                Vector3 start = TranslateRelative(parent.transform, mesh.sharedMesh.vertices[mesh.sharedMesh.triangles[i + j]]);

                Vector3 end = TranslateRelative(parent.transform, mesh.sharedMesh.vertices[mesh.sharedMesh.triangles[j == 2 ? i : i + j + 1]]);

                GameObject wire = GameObject.CreatePrimitive(PrimitiveType.Cube);

                wire.name = mesh.gameObject.name + " Triangle " + ((i + 3) / 3) + " Wire " + (j + 1);

                wire.transform.parent = parent.transform;

                wire.transform.position = start;

                wire.transform.LookAt(end);

                wire.transform.localScale = new Vector3(width, width, Vector3.Distance(start, end));

                wire.transform.position += wire.transform.forward * wire.transform.localScale.z / 2;

                if (positions.Contains(wire.transform.position))
                {
                    if (Application.isPlaying)
                    {
                        Destroy(wire);
                    }
                    else
                    {
                        DestroyImmediate(wire);
                    }

                    continue;
                }
                else
                {
                    positions.Add(wire.transform.position);
                }

                if (material != null)
                {
                    wire.GetComponent<MeshRenderer>().sharedMaterial = material;
                }

                wire.GetComponent<BoxCollider>().enabled = false;
            }
        }

        parent.transform.localScale = mesh.transform.localScale;

        generatedObjects.Add(parent);

        return parent;
    }

    /// <summary>
    /// Generates a wireframe object for each of the given meshes.
    /// </summary>
    /// <param name="meshes"></param>
    /// <param name="width"></param>
    /// <returns>A list of the parent mesh objects.</returns>
    public List<GameObject> WireframeMesh(IEnumerable<MeshFilter> meshes, float width = 0.01f, Material material = null)
    {
        List<GameObject> meshObjects = new List<GameObject>();

        foreach (MeshFilter meshFilter in meshes)
        {
            meshObjects.Add(WireframeMesh(meshFilter, width, material));
        }

        return meshObjects;
    }

    /// <summary>
    /// Generates a wireframe object for each of the given meshes.
    /// </summary>
    /// <param name="width"></param>
    /// <param name="meshes"></param>
    /// <returns>A list of the parent mesh objects.</returns>
    public List<GameObject> WireframeMesh(float width, params MeshFilter[] meshes)
    {
        List<GameObject> meshObjects = new List<GameObject>(meshes.Length);

        foreach (MeshFilter meshFilter in meshes)
        {
            meshObjects.Add(WireframeMesh(meshFilter, width));
        }

        return meshObjects;
    }

    /// <summary>
    /// Generates a wireframe object for each of the given meshes.
    /// </summary>
    /// <param name="width"></param>
    /// <param name="meshes"></param>
    /// <returns>A list of the parent mesh objects.</returns>
    public List<GameObject> WireframeMesh(float width, Material material, params MeshFilter[] meshes)
    {
        List<GameObject> meshObjects = new List<GameObject>(meshes.Length);

        foreach (MeshFilter meshFilter in meshes)
        {
            meshObjects.Add(WireframeMesh(meshFilter, width, material));
        }

        return meshObjects;
    }


    // HELPER FUNCTIONS

    /// <summary>
    /// Returns an offset vector based on the relative transform and given offset vector
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
