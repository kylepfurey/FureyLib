
// Graph and Node Data Structures Script
// by Kyle Furey

using System.Collections;
using System.Collections.Generic;

/// <summary>
/// An individual node with its own data, connections, and weight.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public class Node<DataType>
{
    // NODE DATA

    /// <summary>
    /// The data this node owns
    /// </summary>
    public DataType data = default(DataType);

    /// <summary>
    /// The other nodes this node is connected to and the weight of that connection
    /// </summary>
    public List<Connection<DataType>> connections = new List<Connection<DataType>>();

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
    public Node(DataType data = default(DataType), float weight = 1, bool active = true)
    {
        this.data = data;
        connections = new List<Connection<DataType>>();
        this.weight = weight;
        this.active = active;
    }

    /// <summary>
    /// Default constructor
    /// </summary>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    public Node(DataType data, bool active, float weight = 1)
    {
        this.data = data;
        connections = new List<Connection<DataType>>();
        this.weight = weight;
        this.active = active;
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="connections"></param>
    /// <param name="weight"></param>
    /// <param name="active"></param>
    public Node(DataType data, List<Connection<DataType>> connections, float weight, bool active)
    {
        this.data = data;
        this.connections = connections;
        this.weight = weight;
        this.active = active;
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="connections"></param>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    public Node(DataType data, List<Connection<DataType>> connections, bool active, float weight)
    {
        this.data = data;
        this.connections = connections;
        this.weight = weight;
        this.active = active;
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="data"></param>
    /// <param name="connections"></param>
    /// <param name="weight"></param>
    /// <param name="active"></param>
    public Node(DataType data, Connection<DataType>[] connections, float weight, bool active)
    {
        this.data = data;

        this.connections = new List<Connection<DataType>>(connections.Length);

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
    /// <param name="data"></param>
    /// <param name="connections"></param>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    public Node(DataType data, Connection<DataType>[] connections, bool active, float weight)
    {
        this.data = data;

        this.connections = new List<Connection<DataType>>(connections.Length);

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
    /// <param name="data"></param>
    /// <param name="weight"></param>
    /// <param name="active"></param>
    /// <param name="connections"></param>
    public Node(DataType data, float weight, bool active, params Connection<DataType>[] connections)
    {
        this.data = data;

        this.connections = new List<Connection<DataType>>(connections.Length);

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
    /// <param name="data"></param>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    /// <param name="connections"></param>
    public Node(DataType data, bool active, float weight, params Connection<DataType>[] connections)
    {
        this.data = data;

        this.connections = new List<Connection<DataType>>(connections.Length);

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
    public List<Connection<DataType>> AddConnection(Node<DataType> connectedNode, float weight = 1, bool active = true)
    {
        Connection<DataType> newConnection = new Connection<DataType>(this, connectedNode, weight, active);

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
    public List<Connection<DataType>> AddConnection(Node<DataType> connectedNode, bool active, float weight = 1)
    {
        Connection<DataType> newConnection = new Connection<DataType>(this, connectedNode, active, weight);

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
    public List<Connection<DataType>> RemoveConnection(Node<DataType> connectedNode, float weight = 1, bool active = true)
    {
        Connection<DataType> newConnection = new Connection<DataType>(this, connectedNode, weight, active);

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
    public List<Connection<DataType>> RemoveConnection(Node<DataType> connectedNode, bool active, float weight = 1)
    {
        Connection<DataType> newConnection = new Connection<DataType>(this, connectedNode, active, weight);

        connections.Remove(newConnection);

        return connections;
    }
}

/// <summary>
/// Stores the connection of two nodes and the weight of the connection.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public struct Connection<DataType>
{
    // CONNECTION DATA

    /// <summary>
    /// The node that owns this connection
    /// </summary>
    public Node<DataType> from = null;

    /// <summary>
    /// The node that is being connected to by the from node
    /// </summary>
    public Node<DataType> to = null;

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
    public Connection(Node<DataType> from, Node<DataType> to, float weight = 1, bool active = true)
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
    public Connection(Node<DataType> from, Node<DataType> to, bool active, float weight = 1)
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
    public Connection<DataType> ReconnectFrom(Node<DataType> from)
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
    public Connection<DataType> ReconnectFrom(Node<DataType> from, float weight)
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
    public Connection<DataType> ReconnectFrom(Node<DataType> from, bool active)
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
    public Connection<DataType> ReconnectFrom(Node<DataType> from, float weight, bool active)
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
    public Connection<DataType> ReconnectFrom(Node<DataType> from, bool active, float weight)
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
    public Connection<DataType> ReconnectTo(Node<DataType> to)
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
    public Connection<DataType> ReconnectTo(Node<DataType> to, float weight)
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
    public Connection<DataType> ReconnectTo(Node<DataType> to, bool active)
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
    public Connection<DataType> ReconnectTo(Node<DataType> to, float weight, bool active)
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
    public Connection<DataType> ReconnectTo(Node<DataType> to, bool active, float weight)
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
    public Connection<DataType> Reconnect(Node<DataType> from, Node<DataType> to)
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
    public Connection<DataType> Reconnect(Node<DataType> from, Node<DataType> to, float weight)
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
    public Connection<DataType> Reconnect(Node<DataType> from, Node<DataType> to, bool active)
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
    public Connection<DataType> Reconnect(Node<DataType> from, Node<DataType> to, float weight, bool active)
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
    public Connection<DataType> Reconnect(Node<DataType> from, Node<DataType> to, bool active, float weight)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;
        this.active = active;

        return this;
    }
}

/// <summary>
/// A graph that manages all the nodes and connections inside it.
/// </summary>
/// <typeparam name="DataType"></typeparam>
public struct Graph<DataType> : IEnumerable
{
    // GRAPH DATA

    /// <summary>
    /// The list of nodes included in this graph
    /// </summary>
    public List<Node<DataType>> nodes;


    // GRAPH CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Graph()
    {
        nodes = new List<Node<DataType>>();
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="nodes"></param>
    public Graph(List<Node<DataType>> nodes)
    {
        this.nodes = nodes;
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="nodes"></param>
    public Graph(params Node<DataType>[] nodes)
    {
        this.nodes = new List<Node<DataType>>(nodes.Length);

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
    public List<Connection<DataType>> NodeConnections(Node<DataType> node)
    {
        return node.connections;
    }

    /// <summary>
    /// Get all of the connections that are connected to the given node
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public List<Connection<DataType>> ConnectedNodes(Node<DataType> node)
    {
        List<Connection<DataType>> connections = new List<Connection<DataType>>();

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
    public List<Connection<DataType>> AllConnections()
    {
        List<Connection<DataType>> allConnections = new List<Connection<DataType>>();

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
    public Dictionary<Node<DataType>, List<Connection<DataType>>> AllConnectionsDictionary()
    {
        Dictionary<Node<DataType>, List<Connection<DataType>>> allConnections = new Dictionary<Node<DataType>, List<Connection<DataType>>>();

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
            totalConnections += nodes[i].connections.Count;
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
