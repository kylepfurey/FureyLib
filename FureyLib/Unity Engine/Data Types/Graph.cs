
// Graph Data Structure Script
// by Kyle Furey

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// A graph that manages all the nodes and connections inside it.
/// </summary>
public class Graph : MonoBehaviour, IEnumerable
{
    // GRAPH DATA

    /// <summary>
    /// The list of nodes included in this graph
    /// </summary>
    public List<Node> nodes;


    // GRAPH CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Graph()
    {
        nodes = new List<Node>();
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="nodes"></param>
    public Graph(List<Node> nodes)
    {
        this.nodes = nodes;
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="nodes"></param>
    public Graph(params Node[] nodes)
    {
        this.nodes = new List<Node>(nodes.Length);

        for (int i = 0; i < nodes.Length; i++)
        {
            this.nodes.Add(nodes[i]);
        }
    }


    // GRAPH FUNCTIONS

    /// <summary>
    /// Get all of the given node's connections
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public List<Connection> NodeConnections(Node node)
    {
        List<Connection> connections = new List<Connection>();

        for (int i = 0; i < node.connections.Count; i++)
        {
            connections.Add(node.connections[i]);
        }

        return connections;
    }

    /// <summary>
    /// Get all of the connections that are connected to the given node
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public List<Connection> ConnectedNodes(Node node)
    {
        List<Connection> connections = new List<Connection>();

        for (int i = 0; i < nodes.Count; i++)
        {
            if (nodes[i].Equals(node))
            {
                continue;
            }

            for (int j = 0; j < nodes[i].connections.Count; j++)
            {
                if (nodes[i].connections[j].to.Equals(node))
                {
                    connections.Add(nodes[i].connections[j]);
                }
            }
        }

        return connections;
    }

    /// <summary>
    /// Get all of the connections of each node in a list
    /// </summary>
    /// <returns></returns>
    public List<Connection> AllConnections()
    {
        List<Connection> allConnections = new List<Connection>();

        for (int i = 0; i < nodes.Count; i++)
        {
            for (int j = 0; j < nodes[i].connections.Count; j++)
            {
                allConnections.Add(nodes[i].connections[j]);
            }
        }

        return allConnections;
    }

    /// <summary>
    /// Get all of the connections of each node in a dictionary
    /// </summary>
    /// <returns></returns>
    public Dictionary<Node, List<Connection>> AllConnectionsDictionary()
    {
        Dictionary<Node, List<Connection>> allConnections = new Dictionary<Node, List<Connection>>();

        for (int i = 0; i < nodes.Count; i++)
        {
            allConnections[nodes[i]] = nodes[i].connections;
        }

        return allConnections;
    }

    /// <summary>
    /// Get the total number of connections of this graph
    /// </summary>
    /// <returns></returns>
    public int TotalConnections()
    {
        int totalConnections = 0;

        for (int i = 0; i < nodes.Count; i++)
        {
            for (int j = 0; j < nodes[i].connections.Count; j++)
            {
                totalConnections++;
            }
        }

        return totalConnections;
    }


    // ENUMERATOR FUNCTION

    /// <summary>
    /// Enumerator implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return nodes.GetEnumerator();
    }
}
