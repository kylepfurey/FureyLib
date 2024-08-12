
// Graph Data Structure Node Script
// by Kyle Furey

namespace Navigation
{
    using System.Collections.Generic;
    using UnityEngine;

    // An individual node with its own connections in a graph.
    public class Node : MonoBehaviour
    {
        [Header("An individual node with its own connections in a graph.")]

        [Header("NODE OPTIONS")]

        [Header("All nodes that this node leads to and the weight of that connection:")]
        public List<Connection> connections = new List<Connection>();

        [Header("The weight of this node. This must be positive unless a graph is auto connecting this node:")]
        public float weight = 1;

        // Adds a new connection to another node
        public void AddConnection(Connection newConnection)
        {
            // Set the owner of the connection to this node
            newConnection.owningNode = this;

            // Add the new connection to the list
            connections.Add(newConnection);

            print("Node from " + gameObject.name + " now has a connection to " + newConnection.connectedNode.gameObject.name + "'s node.");
        }

        // Loops through the given nodes and determines whether to connect the nodes or not
        public void FindConnections(List<Node> Nodes, float maxDistance)
        {
            print("Locating connections for " + gameObject.name + "'s node.");

            // Check if the node is within the distance threshold and not itself
            foreach (Node Node in Nodes)
            {
                if (Node == this)
                {
                    Debug.LogWarning("Nodes cannot be connected to themselves.");
                    continue;
                }

                // Check if the node is within range of the graph
                if (Vector3.Distance(transform.position, Node.transform.position) <= maxDistance * maxDistance)
                {
                    // Add the node to this node's connections
                    Connection newConnection = new Connection();
                    newConnection.name = gameObject.name + "'s node auto connected to " + Node.gameObject.name + "'s node.";
                    newConnection.connectedNode = Node;
                    newConnection.weight = Node.weight;

                    AddConnection(newConnection);
                }
                else
                {
                    print("Node from " + gameObject.name + " was farther than " + maxDistance + " Unity units to " + Node.gameObject.name + "'s node and could not connect.");
                }
            }

            print("All connections were located for " + gameObject.name + "'s node.");
        }
    }

    // A connection that leads to another node, with a weight value of that direct connection.
    [System.Serializable]
    public class Connection
    {
        [Header("The name of this connection:")]
        public string name = "New Connection";

        [Header("The node being connected to:")]
        public Node connectedNode;

        [Header("The weight of this connection. This must be positive unless a graph is auto connecting this node:")]
        public float weight = 1;

        // The node that is storing this connection
        [HideInInspector] public Node owningNode;
    }
}
