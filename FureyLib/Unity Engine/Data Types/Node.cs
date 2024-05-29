
// Node Data Structure Script
// by Kyle Furey

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// An individual node with its own connections and weight.
/// </summary>
public class Node : MonoBehaviour
{
    // NODE DATA

    /// <summary>
    /// The other nodes this node is connected to and the weight of that connection
    /// </summary>
    public List<Connection> connections = new List<Connection>();

    /// <summary>
    /// The weight of this node
    /// </summary>
    public float weight = 1;

    /// <summary>
    /// Whether this node is active
    /// </summary>
    public bool active = true;


    // NODE CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    /// <param name="weight"></param>
    /// <param name="active"></param>
    public Node(float weight = 1, bool active = true)
    {
        connections = new List<Connection>();
        this.weight = weight;
        this.active = active;
    }

    /// <summary>
    /// Default constructor
    /// </summary>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    public Node(bool active, float weight = 1)
    {
        connections = new List<Connection>();
        this.weight = weight;
        this.active = active;
    }


    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="connections"></param>
    /// <param name="weight"></param>
    /// <param name="active"></param>
    public Node(List<Connection> connections, float weight, bool active)
    {
        this.connections = connections;
        this.weight = weight;
        this.active = active;
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="connections"></param>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    public Node(List<Connection> connections, bool active, float weight)
    {
        this.connections = connections;
        this.weight = weight;
        this.active = active;
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="connections"></param>
    /// <param name="weight"></param>
    /// <param name="active"></param>
    public Node(Connection[] connections, float weight, bool active)
    {
        this.connections = new List<Connection>(connections.Length);

        for (int i = 0; i < connections.Length; i++)
        {
            this.connections.Add(connections[i]);
        }

        this.weight = weight;
        this.active = active;
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="connections"></param>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    public Node(Connection[] connections, bool active, float weight)
    {
        this.connections = new List<Connection>(connections.Length);

        for (int i = 0; i < connections.Length; i++)
        {
            this.connections.Add(connections[i]);
        }

        this.weight = weight;
        this.active = active;
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="weight"></param>
    /// <param name="active"></param>
    /// <param name="connections"></param>
    public Node(float weight, bool active, params Connection[] connections)
    {
        this.connections = new List<Connection>(connections.Length);

        for (int i = 0; i < connections.Length; i++)
        {
            this.connections.Add(connections[i]);
        }

        this.weight = weight;
        this.active = active;
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    /// <param name="connections"></param>
    public Node(bool active, float weight, params Connection[] connections)
    {
        this.connections = new List<Connection>(connections.Length);

        for (int i = 0; i < connections.Length; i++)
        {
            this.connections.Add(connections[i]);
        }

        this.weight = weight;
        this.active = active;
    }


    // NODE FUNCTIONS

    /// <summary>
    /// Make and add a new connection to the list of connections
    /// </summary>
    /// <param name="connectedNode"></param>
    /// <param name="weight"></param>
    /// <param name="active"></param>
    /// <returns></returns>
    public List<Connection> AddConnection(Node connectedNode, float weight = 1, bool active = true)
    {
        Connection newConnection = new Connection(this, connectedNode, weight, active);

        connections.Add(newConnection);

        return connections;
    }

    /// <summary>
    /// Make and add a new connection to the list of connections
    /// </summary>
    /// <param name="connectedNode"></param>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    /// <returns></returns>
    public List<Connection> AddConnection(Node connectedNode, bool active, float weight = 1)
    {
        Connection newConnection = new Connection(this, connectedNode, active, weight);

        connections.Add(newConnection);

        return connections;
    }

    /// <summary>
    /// Make and remove a matching connection from the list of connections
    /// </summary>
    /// <param name="connectedNode"></param>
    /// <param name="weight"></param>
    /// <param name="active"></param>
    /// <returns></returns>
    public List<Connection> RemoveConnection(Node connectedNode, float weight = 1, bool active = true)
    {
        Connection newConnection = new Connection(this, connectedNode, weight, active);

        connections.Remove(newConnection);

        return connections;
    }

    /// <summary>
    /// Make and remove a matching connection from the list of connections
    /// </summary>
    /// <param name="connectedNode"></param>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    /// <returns></returns>
    public List<Connection> RemoveConnection(Node connectedNode, bool active, float weight = 1)
    {
        Connection newConnection = new Connection(this, connectedNode, active, weight);

        connections.Remove(newConnection);

        return connections;
    }
}

/// <summary>
/// Stores the connection of two nodes and the weight of the connection.
/// </summary>
[System.Serializable]
public class Connection
{
    // CONNECTION DATA

    /// <summary>
    /// The node that owns this connection
    /// </summary>
    public Node from = null;

    /// <summary>
    /// The node that is being connected to by the from node
    /// </summary>
    public Node to = null;

    /// <summary>
    /// The weight of this connection
    /// </summary>
    public float weight = 1;

    /// <summary>
    /// Whether this connection is active
    /// </summary>
    public bool active = true;


    // CONNECTION CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Connection()
    {
        from = null;
        to = null;
        weight = 1;
        active = true;
    }

    /// <summary>
    /// Connection constructor
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <param name="weight"></param>
    /// <param name="active"></param>
    public Connection(Node from, Node to, float weight = 1, bool active = true)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;
        this.active = active;
    }

    /// <summary>
    /// Connection constructor
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    public Connection(Node from, Node to, bool active, float weight = 1)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;
        this.active = active;
    }


    // CONNECTION FUNCTIONS

    /// <summary>
    /// Reconnect a connection's from
    /// </summary>
    /// <param name="from"></param>
    /// <returns></returns>
    public Connection ReconnectFrom(Node from)
    {
        this.from = from;

        return this;
    }

    /// <summary>
    /// Reconnect a connection's from
    /// </summary>
    /// <param name="from"></param>
    /// <param name="weight"></param>
    /// <returns></returns>
    public Connection ReconnectFrom(Node from, float weight)
    {
        this.from = from;
        this.weight = weight;

        return this;
    }

    /// <summary>
    /// Reconnect a connection's from
    /// </summary>
    /// <param name="from"></param>
    /// <param name="active"></param>
    /// <returns></returns>
    public Connection ReconnectFrom(Node from, bool active)
    {
        this.from = from;
        this.active = active;

        return this;
    }

    /// <summary>
    /// Reconnect a connection's from
    /// </summary>
    /// <param name="from"></param>
    /// <param name="weight"></param>
    /// <param name="active"></param>
    /// <returns></returns>
    public Connection ReconnectFrom(Node from, float weight, bool active)
    {
        this.from = from;
        this.weight = weight;
        this.active = active;

        return this;
    }

    /// <summary>
    /// Reconnect a connection's from
    /// </summary>
    /// <param name="from"></param>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    /// <returns></returns>
    public Connection ReconnectFrom(Node from, bool active, float weight)
    {
        this.from = from;
        this.weight = weight;
        this.active = active;

        return this;
    }

    /// <summary>
    /// Reconnect a connection's to
    /// </summary>
    /// <param name="to"></param>
    /// <returns></returns>
    public Connection ReconnectTo(Node to)
    {
        this.to = to;

        return this;
    }

    /// <summary>
    /// Reconnect a connection's to
    /// </summary>
    /// <param name="to"></param>
    /// <param name="weight"></param>
    /// <returns></returns>
    public Connection ReconnectTo(Node to, float weight)
    {
        this.to = to;
        this.weight = weight;

        return this;
    }

    /// <summary>
    /// Reconnect a connection's to
    /// </summary>
    /// <param name="to"></param>
    /// <param name="active"></param>
    /// <returns></returns>
    public Connection ReconnectTo(Node to, bool active)
    {
        this.to = to;
        this.active = active;

        return this;
    }

    /// <summary>
    /// Reconnect a connection's to
    /// </summary>
    /// <param name="to"></param>
    /// <param name="weight"></param>
    /// <param name="active"></param>
    /// <returns></returns>
    public Connection ReconnectTo(Node to, float weight, bool active)
    {
        this.to = to;
        this.weight = weight;
        this.active = active;

        return this;
    }

    /// <summary>
    /// Reconnect a connection's to
    /// </summary>
    /// <param name="to"></param>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    /// <returns></returns>
    public Connection ReconnectTo(Node to, bool active, float weight)
    {
        this.to = to;
        this.weight = weight;
        this.active = active;

        return this;
    }

    /// <summary>
    /// Reconnect a connection's from and to
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <returns></returns>
    public Connection Reconnect(Node from, Node to)
    {
        this.from = from;
        this.to = to;

        return this;
    }

    /// <summary>
    /// Reconnect a connection's from and to
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <param name="weight"></param>
    /// <returns></returns>
    public Connection Reconnect(Node from, Node to, float weight)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;

        return this;
    }

    /// <summary>
    /// Reconnect a connection's from and to
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <param name="active"></param>
    /// <returns></returns>
    public Connection Reconnect(Node from, Node to, bool active)
    {
        this.from = from;
        this.to = to;
        this.active = active;

        return this;
    }

    /// <summary>
    /// Reconnect a connection's from and to
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <param name="weight"></param>
    /// <param name="active"></param>
    /// <returns></returns>
    public Connection Reconnect(Node from, Node to, float weight, bool active)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;
        this.active = active;

        return this;
    }

    /// <summary>
    /// Reconnect a connection's from and to
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    /// <returns></returns>
    public Connection Reconnect(Node from, Node to, bool active, float weight)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;
        this.active = active;

        return this;
    }
}
