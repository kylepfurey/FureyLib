
// Navigation Manager Script
// by Kyle Furey

namespace Navigation
{
    using System.Collections.Generic;
    using UnityEngine;

    using static MeshClipper;
    using static NavigationManager;
    using static Pathfinding;

    // Generates navigation meshes for Navigators to traverse.
    public class NavigationManager : MonoBehaviour
    {
        [Header("Generates navigation meshes for Navigators to traverse.")]

        // Instance (to prevent duplicate components)
        private static NavigationManager instance = null;

        [Header("\nBAKE NAVIGATION MESHES:")]
        [SerializeField] private bool BAKE = false;

        [Header("\nCLEAR BAKED NAVIGATION MESHES:")]
        [SerializeField] private bool CLEAR = false;
        public static List<GameObject> bakedMeshes = new List<GameObject>();
        public static List<Node> generatedNodes = new List<Node>();

        [Header("\nMESHES TO BAKE:")]
        [SerializeField] private List<MeshObjectCollection> meshes = new List<MeshObjectCollection>();
        public static List<MeshObjectCollection> meshesToBake = new List<MeshObjectCollection>();

        [Header("\nBAKING SETTINGS:")]
        [SerializeField] private float maxSlopeAngle = 60;
        public static float slopeAngle = 60;

        [Header("\nNAVIGATION SETTINGS:")]
        [SerializeField] private float maxNavigationDistance = 15;
        public static float navigationDistance = 15;

        // MENU BUTTONS

        // Updating static variables and deleting duplicates
        private void OnValidate()
        {
            // Set instance
            if (instance == null)
            {
                instance = this;
            }
            else if (instance != this)
            {
                Debug.LogError("You cannot have more than one instance of a Navigation Manager! Deleting the previous Navigation Manager now . . .");

                instance.Invoke("Destroy", 0);

                instance = this;
            }

            // Bake navigation meshes
            if (BAKE)
            {
                BAKE = false;

                Invoke("BakeMeshes", 0);
            }

            // Clearing baked navigation meshes
            if (CLEAR)
            {
                CLEAR = false;

                Invoke("ClearMeshes", 0);
            }

            // Update the list of objects to bake
            meshesToBake = meshes;

            // Update the maximum slope of generated meshes
            slopeAngle = maxSlopeAngle;

            // Update the maximum distance between a position and the nodes
            navigationDistance = maxNavigationDistance;
        }

        // Destroy this component
        private void Destroy()
        {
            DestroyImmediate(this);
        }

        // Clear baked meshes from the editor
        private void ClearMeshes()
        {
            Clear();
        }

        // Bake meshes from the editor
        private void BakeMeshes()
        {
            Bake();
        }


        // NAVIGATION BAKING

        // Hide the navigation meshes on the game start
        private void Awake()
        {
            // Update the list of objects to bake
            meshesToBake = meshes;

            // Update the maximum slope of generated meshes
            slopeAngle = maxSlopeAngle;

            // Update the maximum distance between a position and the nodes
            navigationDistance = maxNavigationDistance;

            // Bake the meshes
            if (bakedMeshes.Count == 0)
            {
                Bake();
            }

            // Set the navigation meshes as invisible
            for (int i = 0; i < bakedMeshes.Count; i++)
            {
                bakedMeshes[i].active = false;
            }
        }

        // Clear baked meshes
        public static void Clear()
        {
            for (int i = 0; i < bakedMeshes.Count; i++)
            {
                DestroyImmediate(bakedMeshes[i]);
            }

            bakedMeshes.Clear();

            generatedNodes.Clear();
        }

        // Bake navigation meshes
        public static void Bake()
        {
            // Clear the baked objects
            Clear();

            // Bake and generate nodes for each mesh
            for (int i = 0; i < meshesToBake.Count; i++)
            {
                // Generate a navigation mesh
                GameObject navigationMesh = meshesToBake[i].Bake();

                // Store the navigation mesh
                bakedMeshes.Add(navigationMesh);

                // Generate nodes for that navigation mesh
                List<Node> newNodes = GenerateNodes(navigationMesh);

                // Store the generated nodes
                for (int j = 0; j < newNodes.Count; j++)
                {
                    generatedNodes.Add(newNodes[j]);
                }
            }

            Debug.Log("Successfully generated " + bakedMeshes.Count + (bakedMeshes.Count == 1 ? " Navigation Mesh with a total of " : " Navigation Meshes with a total of ") + generatedNodes.Count + (generatedNodes.Count == 1 ? " generate Navigation Nodes." : " generated Navigation Nodes."));
        }

        // Generate nodes for a navigation mesh's triangles
        private static List<Node> GenerateNodes(GameObject meshObject)
        {
            // Get each mesh object
            List<GameObject> meshObjects = GetObjects(meshObject);

            // Store the positions of each potential node
            List<Vector3> allNodePositions = new List<Vector3>();

            // Initialize dictionaries to store each position, its node, its connected nodes, and which triangle its inside
            Dictionary<Vector3, List<Vector3>> positionToConnections = new Dictionary<Vector3, List<Vector3>>();
            Dictionary<Vector3, Node> positionToNode = new Dictionary<Vector3, Node>();
            Dictionary<Vector3, List<Vector3>> verticesToPositions = new Dictionary<Vector3, List<Vector3>>();

            // Loop through each mesh object
            foreach (GameObject mesh in meshObjects)
            {
                // Store each node position
                List<Vector3> nodePositions = new List<Vector3>();

                // Store the mesh data
                Mesh meshData = GetMesh(mesh);

                // Add the center of that mesh
                nodePositions.Add(GetCenter(meshData.vertices));

                /*
                // Loop through each of the mesh vertices
                for (int i = 0; i < meshData.vertices.Length; i++)
                {
                    // Add each of the vertices
                    nodePositions.Add(meshData.vertices[i]);

                    // Add the middle points of the mesh vertices
                    for (int j = 0; j < meshData.vertices.Length; j++)
                    {
                        // Ignore the same vertices
                        if (i == j)
                        {
                            continue;
                        }

                        // Calculate and add the points in between each vertice
                        nodePositions.Add(meshData.vertices[i] + ((meshData.vertices[j] - meshData.vertices[i]) / 2));
                    }
                }
                */

                // Loop through each of the stored positions of this mesh
                foreach (Vector3 position in nodePositions)
                {
                    // Add each position to the node position list
                    allNodePositions.Add(position);

                    // Store each of the connected positions in a temporary list
                    List<Vector3> connections = new List<Vector3>(nodePositions.Count - 1);

                    // Loop through each of the other stored positions of this mesh
                    foreach (Vector3 connection in nodePositions)
                    {
                        // Ignore the same position
                        if (connection == position)
                        {
                            continue;
                        }

                        // Add a connection between the start and other positions to the temporary list
                        connections.Add(connection);
                    }

                    // Store the new connections
                    if (positionToConnections.ContainsKey(position))
                    {
                        for (int i = 0; i < connections.Count; i++)
                        {
                            if (!positionToConnections[position].Contains(connections[i]))
                            {
                                positionToConnections[position].Add(connections[i]);
                            }
                        }
                    }
                    else
                    {
                        positionToConnections[position] = connections;
                    }
                }

                // Add to the vertices to node positions dictionary
                verticesToPositions[meshData.vertices[0]] = nodePositions;
            }

            // Remove duplicate node positions
            for (int i = 0; i < allNodePositions.Count; i++)
            {
                // Loop through each other position
                for (int j = 0; j < allNodePositions.Count; j++)
                {
                    // Ignore the same position
                    if (i == j)
                    {
                        continue;
                    }

                    // Check if the position is the same
                    if (allNodePositions[i] == allNodePositions[j])
                    {
                        // Remove that position
                        allNodePositions.RemoveAt(j);

                        // Move the count back
                        i -= i > j ? 1 : 0;
                        j--;
                    }
                }
            }

            // Store all the vertices of each mesh in a list
            List<List<Vector3>> vertices = new List<List<Vector3>>(meshObjects.Count);

            // Get each mesh's vertices
            foreach (GameObject mesh in meshObjects)
            {
                // Store each mesh data
                Mesh meshData = GetMesh(mesh);

                // Store the vertices in a temporary list
                List<Vector3> verts = new List<Vector3>();

                // Get the verticies from the mesh
                for (int i = 0; i < meshData.vertices.Length; i++)
                {
                    verts.Add(meshData.vertices[i]);
                }

                // Add the vertices to the list of all the vertices
                vertices.Add(verts);
            }

            // Loop through each set of vertices
            for (int i = 0; i < vertices.Count; i++)
            {
                // Loop through each other set of vertices
                for (int j = 0; j < vertices.Count; j++)
                {
                    // Skip the same group of vertices
                    if (i == j)
                    {
                        continue;
                    }

                    // Store the number of matching vertices
                    int matches = 0;

                    // Loop through each individual vertice
                    for (int k = 0; k < vertices[i].Count; k++)
                    {
                        if (vertices[j].Contains(vertices[i][k]))
                        {
                            matches++;
                        }

                        // Check if the given vertice is inside the current other set of vertices
                        if (matches == 2 || IsInside(vertices[i][k], vertices[j].ToArray()))
                        {
                            // Now that we have found a vertice is overlapping another polygon, we need to add a connection between the center nodes of both polygons.
                            positionToConnections[GetCenter(vertices[i].ToArray())].Add(GetCenter(vertices[j].ToArray()));

                            // Break out of the loop
                            break;
                        }
                    }
                }
            }

            // Make a parent object for the nodes
            GameObject nodesParent = new GameObject("Navigation Nodes");

            // Store all of the nodes we make
            List<Node> allNodes = new List<Node>();

            // Generate nodes in each of the unique positions
            for (int i = 0; i < allNodePositions.Count; i++)
            {
                // Generate an object to store the node
                GameObject newNodeObject = new GameObject("Generated Node");

                // Reparent the node to the parent node object
                newNodeObject.transform.parent = nodesParent.transform;

                // Adjust the position of the new node object
                newNodeObject.transform.position = allNodePositions[i];

                // Make a new node for this object
                Node newNode = newNodeObject.AddComponent<Node>();

                // Add the new node to the final list
                allNodes.Add(newNode);

                // Store the node in the dictionary
                positionToNode[allNodePositions[i]] = newNode;
            }

            // Generate the connections for each of the connected nodes
            foreach (Vector3 currentNode in allNodePositions)
            {
                // Get the list of connected nodes for each node
                List<Vector3> connectedNodes = positionToConnections[currentNode];

                // Store each node position that has been assigned a connection
                List<Vector3> storedConnections = new List<Vector3>();

                // Loop through each of the connected positions
                foreach (Vector3 connectedNode in connectedNodes)
                {
                    // Check that the current node position has not been connected to already
                    if (!storedConnections.Contains(connectedNode) && positionToNode.ContainsKey(connectedNode))
                    {
                        // Make a new connection with each node
                        Connection newConnection = new Connection();

                        // Name the connection
                        newConnection.name = "Automatic Navigation Mesh Connection";

                        // Store the connected node
                        newConnection.connectedNode = positionToNode[connectedNode];

                        // Add the connection to the current node
                        positionToNode[currentNode].AddConnection(newConnection);

                        // Mark this node position as connected
                        storedConnections.Add(connectedNode);
                    }
                }
            }

            // Remove unused nodes
            for (int i = 0; i < allNodes.Count; i++)
            {
                if (allNodes[i].connections.Count == 0)
                {
                    DestroyImmediate(allNodes[i].gameObject);

                    allNodes.RemoveAt(i);

                    i--;
                }
            }

            // Parent the parent node object to the mesh object
            nodesParent.transform.parent = meshObject.transform;

            // Adjust the transform of the parent node object
            nodesParent.transform.localPosition = Vector3.zero;

            // Double the scale of the parent node object
            nodesParent.transform.localScale *= 2;

            // Return the new list of nodes
            return allNodes;
        }


        // NAVIGATION FUNCTIONS

        // Get nearest node
        public static Node GetNearestNode(Vector3 worldPosition, float maxDistance = Mathf.Infinity)
        {
            // Check the number of nodes
            if (generatedNodes.Count == 0)
            {
                Debug.LogError("Could not get a node! No nodes have been generated!");

                return null;
            }

            // Store the first node and its distance
            Node closestNode = generatedNodes[0];

            float shortestDistance = DistanceSquared(worldPosition, closestNode.transform.position);

            // Loop through the remaining nodes
            for (int i = 1; i < generatedNodes.Count; i++)
            {
                // Store the distance to the current node
                float newDistance = DistanceSquared(worldPosition, generatedNodes[i].transform.position);

                // Compare the new distance with the closest node
                if (newDistance < shortestDistance)
                {
                    // Update the closest node and the shortest distance
                    closestNode = generatedNodes[i];

                    shortestDistance = newDistance;
                }
            }

            // Check shortest distance
            if (shortestDistance > maxDistance * maxDistance)
            {
                closestNode = null;
            }

            return closestNode;
        }

        // Pathfind to a node using two positions
        public static List<Vector3> Navigate(Vector3 startPosition, Vector3 endPosition, Algorithm searchAlgorithm = Algorithm.AStar, float heuristicScale = 1)
        {
            // Calculate a path from the start node to the end node
            List<Vector3> finalRoute = new List<Vector3>();

            // Get the start and end nodes
            Node startNode = GetNearestNode(startPosition, navigationDistance);
            Node endNode = GetNearestNode(endPosition, navigationDistance);

            // Check the start and end nodes
            if (startNode == null || endNode == null)
            {
                Debug.LogWarning("Could not navigate to the given location! The " + (startNode == null ? "start" : "end") + " position is out of range of the nodes!");
                return new List<Vector3>();
            }

            // Calculate a path from the start node to the end node
            List<Node> path = Pathfind(searchAlgorithm, startNode, endNode, heuristicScale);

            // Check the path
            if (path == null)
            {
                Debug.LogWarning("Could not navigate to the given location! There is no valid route!");
                return null;
            }
            else if (path.Count > 0)
            {
                // Build the final route from the positions of the nodes
                for (int i = 0; i < path.Count; i++)
                {
                    finalRoute.Add(path[i].transform.position);
                }
            }

            // Add the end position
            finalRoute.Add(endPosition);

            // Return the final route
            return finalRoute;
        }


        // OTHER FUNCTIONS

        // Returns the squared distance between two vector 3s
        private static float DistanceSquared(Vector3 pointA, Vector3 pointB)
        {
            float xDistance = pointA.x - pointB.x;
            float yDistance = pointA.y - pointB.y;
            float zDistance = pointA.z - pointB.z;

            return xDistance * xDistance + yDistance * yDistance + zDistance * zDistance;
        }
    }

    // Collections of game objects to bake together.
    [System.Serializable]
    public class MeshObjectCollection
    {
        [Header("Collections of game objects with meshes to bake together.")]

        [Header("The name of this collection of meshes:")]
        public string name = "New Mesh Collection";

        [Header("The list of objects to bake together as one mesh:")]
        public List<GameObject> bakedObjects = new List<GameObject>();

        [Header("The type of baking for this mesh collection:")]
        public BakeMode bakeMode = BakeMode.Simplify;

        // Bake mode enum
        public enum BakeMode { Simplify, Decimate, Terrain };

        // Bakes the objects into a singular mesh object
        public GameObject Bake()
        {
            // Store all of the meshes
            List<Mesh> meshes = GetMeshes(bakedObjects);

            if (bakeMode == BakeMode.Simplify)
            {
                for (int i = 0; i < meshes.Count; i++)
                {
                    meshes[i] = Simplify(meshes[i]);
                }
            }

            // Store the combined mesh
            Mesh combinedMesh = null;

            // Check the number of meshes that are being baked together
            if (bakedObjects.Count > 1)
            {
                // Store the world positions of each object
                Vector3[] worldPositions = new Vector3[bakedObjects.Count];

                for (int i = 0; i < bakedObjects.Count; i++)
                {
                    worldPositions[i] = bakedObjects[i].transform.position;
                }

                // Combine the meshes
                combinedMesh = Combine(meshes, worldPositions);

                if (bakeMode == BakeMode.Decimate)
                {
                    combinedMesh = Decimate(combinedMesh);
                }
            }
            else if (bakedObjects.Count == 1)
            {
                if (bakeMode == BakeMode.Decimate)
                {
                    combinedMesh = Decimate(GetMesh(bakedObjects[0]));
                }
            }
            else
            {
                Debug.LogError("Could not bake a navigation mesh! No meshes were given!");

                return null;
            }

            // Name the new navigation mesh
            combinedMesh.name = name + " Navigation Mesh";

            // Check if this mesh collection is terrain
            if (bakeMode == BakeMode.Terrain)
            {
                // Cut out steep parts of the terrain mesh
                combinedMesh = Discard(combinedMesh, slopeAngle);

                // Check that the terrain baking was successful
                if (combinedMesh == null || combinedMesh.vertices.Length < 3)
                {
                    Debug.LogError("Could not bake a navigation mesh! An object did not qualify as terrain! Double check the slope angle.");

                    return null;
                }
            }

            // Generate a navigation mesh object
            GameObject meshObject = Generate(Triangulate(combinedMesh));

            // Name the new mesh object
            meshObject.name = name + " Navigation Mesh";

            // Update the transform of the mesh object
            meshObject.transform.position = bakedObjects[0].transform.position + new Vector3(0, 2, 0);
            meshObject.transform.eulerAngles = Vector3.zero;
            meshObject.transform.localScale = bakedObjects[0].transform.localScale;

            // Return the generated mesh object
            return meshObject;
        }
    }
}
