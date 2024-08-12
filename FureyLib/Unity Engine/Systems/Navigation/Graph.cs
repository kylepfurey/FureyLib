
// Graph Data Structure Script
// by Kyle Furey

namespace Navigation
{
    using System.Collections.Generic;
    using UnityEngine;

    // A graph that manages all the nodes and connections inside it.
    public class Graph : MonoBehaviour
    {
        [Header("A graph that manages all the nodes and connections inside it.")]

        [Header("GRAPH OPTIONS")]

        [Header("All of this graph's nodes:")]
        [SerializeField] private List<Node> Nodes = new List<Node>();

        [Header("All of the connections of this graph's nodes:")]
        [SerializeField] private List<Connection> Connections = new List<Connection>();

        [Header("Click the \"calculate\" checkbox to calculate the respective criteria:")]
        [SerializeField] private bool calculateAllNodesInChildren = false;
        [SerializeField] private bool calculateAllNodesInScene = false;
        [SerializeField] private bool calculateCurrentConnections = false;

        [Header("The maximum distance between two nodes for it to automatically connect:")]
        [SerializeField] private float maxConnectionDistance = 2f;

        [Header("DEBUG OPTIONS")]

        [Header("Whether to calculate this graph's node connections live:")]
        [SerializeField] private bool liveTesting = false;

        [Header("Click the \"test route\" checkbox to calculate a route between the start and end node using the set algorithm:")]
        [SerializeField] private Node startNode;
        [SerializeField] private Node endNode;
        [SerializeField] private float heuristicScale = 1;
        [SerializeField] private Pathfinding.Algorithm algorithm = Pathfinding.Algorithm.AStar;
        [SerializeField] private bool calculateRoute = false;

        [Header("Whether to hide the mesh of each nodes when the game starts:")]
        [SerializeField] private bool hideNodeMeshes = true;

        [Header("Whether to render the nodes and connections with spheres and lines:")]
        [SerializeField] private bool renderGizmos = true;

        [Header("This graph's node radius and color:")]
        [SerializeField] private float renderNodeRadius = 0.25f;
        [SerializeField] private Color renderNodeColor = new Vector4(255, 255, 255, 100) / 255;

        [Header("This graph's connection color:")]
        [SerializeField] private Color renderConnectionColor = new Vector4(0, 150, 255, 255) / 255;

        // Adds a new node to the collection of nodes
        public void AddNode(Node newNode)
        {
            // Add the new node to the list
            Nodes.Add(newNode);

            if (newNode.weight < 0)
            {
                OnNegativeWeight(newNode.weight);
            }

            print("Node from " + newNode.gameObject.name + " was added to " + gameObject.name + "'s graph.");
        }

        // Adds a new connection to the graph's list of connections
        public void AddConnection(Connection newConnection)
        {
            // Add the new connection to the list of all connections
            Connections.Add(newConnection);

            if (newConnection.owningNode.weight < 0)
            {
                OnNegativeWeight(newConnection.owningNode.weight);
            }

            if (newConnection.weight < 0)
            {
                OnNegativeWeight(newConnection.weight);
            }

            print("Connection from " + newConnection.owningNode.gameObject.name + " 's node to " + newConnection.connectedNode.gameObject.name + "'s node was added to " + gameObject.name + "'s graph.");
        }

        // Finds and stores all nodes in the scene
        public void FindAllNodes()
        {
            print("Locating all nodes in the current scene for " + gameObject.name + "'s graph.");

            // Clear the nodes and connections array
            Nodes.Clear();
            Connections.Clear();

            // Find all objects in the scene
            GameObject[] Objects;
            Objects = FindObjectsByType<GameObject>(FindObjectsSortMode.None);

            // Check if each object has the node script attached
            foreach (GameObject Object in Objects)
            {
                if (Object.GetComponent<Node>())
                {
                    // Add that node to the array
                    AddNode(Object.GetComponent<Node>());
                }
            }

            print("All possible nodes were located for " + gameObject.name + "'s graph.");
        }

        // Finds and stores all nodes in this graph's children
        public void FindAllNodesInChildren()
        {
            print("Locating all nodes in the current scene for " + gameObject.name + "'s graph.");

            // Clear the nodes and connections list
            Nodes.Clear();
            Connections.Clear();

            // Check if each object has the node script attached
            foreach (Node Node in GetComponentsInChildren<Node>())
            {
                // Add that node to the list
                AddNode(Node);
            }

            print("All possible nodes were located for " + gameObject.name + "'s graph.");
        }

        // Automatically generates all nearest connections to nodes based on a set distance threshold
        public void FindAllConnections()
        {
            print("Locating connections for all nodes in " + gameObject.name + "'s graph.");

            // Clear the connections array
            Connections.Clear();

            // Search and connect all nodes within the distance threshold
            foreach (Node Node in Nodes)
            {
                Node.connections.Clear();
                Node.FindConnections(Nodes, maxConnectionDistance);

                foreach (Connection connectedNode in Node.connections)
                {
                    AddConnection(connectedNode);
                }
            }

            print("All connections for all nodes in " + gameObject.name + "'s graph were located.");
        }

        // Adds the weight value to every node and their connections to ensure no nodes or connections are negative but the relative weight is the same
        public void OnNegativeWeight(float weight)
        {
            for (int i = 0; i < Nodes.Count; i++)
            {
                Nodes[i].weight -= weight;

                for (int j = 0; j < Nodes[i].connections.Count; j++)
                {
                    Nodes[i].connections[j].weight -= weight;
                }
            }
        }

        // Calculates and renders all nodes and connections of this graph
        private void OnDrawGizmos()
        {
            // Test nodes and connections live
            if (liveTesting)
            {
                // Finds all connections of the current graph's nodes
                FindAllConnections();

                print("LIVE TESTING IS ON!");
            }

            // Render node spheres and connection lines
            if (renderGizmos)
            {
                // Render node spheres
                foreach (Node Node in Nodes)
                {
                    // Render node color
                    Gizmos.color = renderNodeColor;

                    Gizmos.DrawSphere(Node.transform.position, renderNodeRadius);

                    // Render node connection radius
                    Gizmos.color = new Vector4(Mathf.Abs(renderNodeColor.r - 1), Mathf.Abs(renderNodeColor.g - 1), Mathf.Abs(renderNodeColor.b - 1), renderNodeColor.a / 4);

                    Gizmos.DrawSphere(Node.transform.position, maxConnectionDistance - renderNodeRadius);
                }

                // Render connection color
                Gizmos.color = renderConnectionColor;

                // Render connection lines
                foreach (Connection Connection in Connections)
                {
                    if (Connection.owningNode != null && Connection.connectedNode != null)
                    {
                        Gizmos.DrawLine(Connection.owningNode.transform.position, Connection.connectedNode.transform.position);
                    }
                }
            }
        }

        // Node connection calculations and pathfinding test buttons
        private void OnValidate()
        {
            // Calculate all nodes in the scene
            if (calculateAllNodesInScene)
            {
                // Disable button
                calculateAllNodesInScene = false;

                FindAllNodes();
            }

            // Calculate all nodes in this graph's children
            if (calculateAllNodesInChildren)
            {
                // Disable button
                calculateAllNodesInChildren = false;

                FindAllNodesInChildren();
            }

            // Calculate all of this graph's connections
            if (calculateCurrentConnections)
            {
                // Disable button
                calculateCurrentConnections = false;

                FindAllConnections();
            }

            // Test route calculation
            if (calculateRoute)
            {
                // Disable button
                calculateRoute = false;

                // Pick a color
                Color color = new Vector4(Mathf.Abs(renderConnectionColor.r - 1), Mathf.Abs(renderConnectionColor.g - 1), Mathf.Abs(renderConnectionColor.b - 1), renderConnectionColor.a);
                float time = 2f;

                // Check if either node is null, and set it randomly if that is true
                if (startNode != null && endNode != null)
                {
                    // Calculate a route based on the given algorithm and nodes
                    List<Node> route = Pathfinding.Pathfind(algorithm, startNode, endNode, heuristicScale);

                    // Draw lines to represent the route (if applicable)
                    if (route.Count > 0)
                    {
                        Debug.DrawLine(startNode.transform.position, route[0].transform.position, color, time);

                        for (int i = 0; i < route.Count - 1; i++)
                        {
                            Debug.DrawLine(route[i].transform.position, route[i + 1].transform.position, color, time);
                        }
                    }
                }
                else if (startNode == null && endNode == null)
                {
                    startNode = Nodes[Random.Range(0, Nodes.Count - 1)];
                    endNode = Nodes[Random.Range(0, Nodes.Count - 1)];

                    // Calculate a route based on the given algorithm and nodes
                    List<Node> route = Pathfinding.Pathfind(algorithm, startNode, endNode, heuristicScale);

                    // Draw lines to represent the route (if applicable)
                    if (route.Count > 0)
                    {
                        Debug.DrawLine(startNode.transform.position, route[0].transform.position, color, time);

                        for (int i = 0; i < route.Count - 1; i++)
                        {
                            Debug.DrawLine(route[i].transform.position, route[i + 1].transform.position, color, time);
                        }
                    }

                    startNode = null;
                    endNode = null;
                }
                else if (startNode == null)
                {
                    startNode = Nodes[Random.Range(0, Nodes.Count - 1)];

                    // Calculate a route based on the given algorithm and nodes
                    List<Node> route = Pathfinding.Pathfind(algorithm, startNode, endNode, heuristicScale);

                    // Draw lines to represent the route (if applicable)
                    if (route.Count > 0)
                    {
                        Debug.DrawLine(startNode.transform.position, route[0].transform.position, color, time);

                        for (int i = 0; i < route.Count - 1; i++)
                        {
                            Debug.DrawLine(route[i].transform.position, route[i + 1].transform.position, color, time);
                        }
                    }

                    startNode = null;
                }
                else
                {
                    endNode = Nodes[Random.Range(0, Nodes.Count - 1)];

                    // Calculate a route based on the given algorithm and nodes
                    List<Node> route = Pathfinding.Pathfind(algorithm, startNode, endNode, heuristicScale);

                    // Draw lines to represent the route (if applicable)
                    if (route.Count > 0)
                    {
                        Debug.DrawLine(startNode.transform.position, route[0].transform.position, color, time);

                        for (int i = 0; i < route.Count - 1; i++)
                        {
                            Debug.DrawLine(route[i].transform.position, route[i + 1].transform.position, color, time);
                        }
                    }

                    endNode = null;
                }
            }
        }

        // Disable debug options and hide the meshes of each node on game start
        private void Awake()
        {
            // Disable debug options
            liveTesting = false;

            // Hide the mesh of each node
            if (hideNodeMeshes)
            {
                foreach (Node Node in Nodes)
                {
                    if (Node.gameObject.GetComponent<Renderer>() != null)
                    {
                        Node.gameObject.GetComponent<Renderer>().enabled = false;
                    }
                }
            }
        }
    }
}
