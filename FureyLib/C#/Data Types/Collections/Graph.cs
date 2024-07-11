
// Graph and Node Data Structures Script
// by Kyle Furey

using System.Collections;
using System.Collections.Generic;

// Define the weighted node type
using WeightType = System.Single;

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
    public HashSet<Connection<DataType>> connections = new HashSet<Connection<DataType>>();

    /// <summary>
    /// The weight of this node
    /// </summary>
    public WeightType weight = 1;

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
    public Node(DataType data = default(DataType), WeightType weight = 1, bool active = true)
    {
        this.data = data;

        connections = new HashSet<Connection<DataType>>();

        this.weight = weight;

        this.active = active;
    }

    /// <summary>
    /// Default constructor
    /// </summary>
    /// <param name="active"></param>
    /// <param name="weight"></param>
    public Node(DataType data, bool active, WeightType weight = 1)
    {
        this.data = data;

        connections = new HashSet<Connection<DataType>>();

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
    public Node(DataType data, HashSet<Connection<DataType>> connections, WeightType weight, bool active)
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
    public Node(DataType data, HashSet<Connection<DataType>> connections, bool active, WeightType weight)
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
    public Node(DataType data, Connection<DataType>[] connections, WeightType weight, bool active)
    {
        this.data = data;

        this.connections = new HashSet<Connection<DataType>>(connections.Length);

        foreach (Connection<DataType> connection in connections)
        {
            this.connections.Add(connection);
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
    public Node(DataType data, Connection<DataType>[] connections, bool active, WeightType weight)
    {
        this.data = data;

        this.connections = new HashSet<Connection<DataType>>(connections.Length);

        foreach (Connection<DataType> connection in connections)
        {
            this.connections.Add(connection);
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
    public Node(DataType data, WeightType weight, bool active, params Connection<DataType>[] connections)
    {
        this.data = data;

        this.connections = new HashSet<Connection<DataType>>(connections.Length);

        foreach (Connection<DataType> connection in connections)
        {
            this.connections.Add(connection);
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
    public Node(DataType data, bool active, WeightType weight, params Connection<DataType>[] connections)
    {
        this.data = data;

        this.connections = new HashSet<Connection<DataType>>(connections.Length);

        foreach (Connection<DataType> connection in connections)
        {
            this.connections.Add(connection);
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
    public HashSet<Connection<DataType>> AddConnection(Node<DataType> connectedNode, WeightType weight = 1, bool active = true)
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
    public HashSet<Connection<DataType>> AddConnection(Node<DataType> connectedNode, bool active, WeightType weight = 1)
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
    public HashSet<Connection<DataType>> RemoveConnection(Node<DataType> connectedNode, WeightType weight = 1, bool active = true)
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
    public HashSet<Connection<DataType>> RemoveConnection(Node<DataType> connectedNode, bool active, WeightType weight = 1)
    {
        Connection<DataType> newConnection = new Connection<DataType>(this, connectedNode, active, weight);

        connections.Remove(newConnection);

        return connections;
    }

    /// <summary>
    /// Checks whether this node is connected to the given node
    /// </summary>
    /// <param name="connectedNode"></param>
    /// <returns></returns>
    public bool ConnectedTo(Node<DataType> connectedNode)
    {
        foreach (Connection<DataType> connection in connections)
        {
            if (connection.to == connectedNode)
            {
                return true;
            }
        }

        return false;
    }

    /// <summary>
    /// Checks whether the given node is connected to this node
    /// </summary>
    /// <param name="connectingNode"></param>
    /// <returns></returns>
    public bool ConnectedToMe(Node<DataType> connectingNode)
    {
        foreach (Connection<DataType> connection in connectingNode.connections)
        {
            if (connection.to == this)
            {
                return true;
            }
        }

        return false;
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
    public WeightType weight = 1;

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
    public Connection(Node<DataType> from, Node<DataType> to, WeightType weight = 1, bool active = true)
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
    public Connection(Node<DataType> from, Node<DataType> to, bool active, WeightType weight = 1)
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
    public Connection<DataType> ReconnectFrom(Node<DataType> from, WeightType weight)
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
    public Connection<DataType> ReconnectFrom(Node<DataType> from, WeightType weight, bool active)
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
    public Connection<DataType> ReconnectFrom(Node<DataType> from, bool active, WeightType weight)
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
    public Connection<DataType> ReconnectTo(Node<DataType> to, WeightType weight)
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
    public Connection<DataType> ReconnectTo(Node<DataType> to, WeightType weight, bool active)
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
    public Connection<DataType> ReconnectTo(Node<DataType> to, bool active, WeightType weight)
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
    public Connection<DataType> Reconnect(Node<DataType> from, Node<DataType> to, WeightType weight)
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
    public Connection<DataType> Reconnect(Node<DataType> from, Node<DataType> to, WeightType weight, bool active)
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
    public Connection<DataType> Reconnect(Node<DataType> from, Node<DataType> to, bool active, WeightType weight)
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
    public HashSet<Node<DataType>> nodes;


    // GRAPH CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Graph()
    {
        nodes = new HashSet<Node<DataType>>();
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="nodes"></param>
    public Graph(HashSet<Node<DataType>> nodes)
    {
        this.nodes = nodes;
    }

    /// <summary>
    /// Node constructor
    /// </summary>
    /// <param name="nodes"></param>
    public Graph(params Node<DataType>[] nodes)
    {
        this.nodes = new HashSet<Node<DataType>>(nodes.Length);

        foreach (Node<DataType> newNode in nodes)
        {
            this.nodes.Add(newNode);
        }
    }


    // GRAPH FUNCTIONS

    /// <summary>
    /// Get all of the given node's connections
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public HashSet<Connection<DataType>> NodeConnections(Node<DataType> node)
    {
        return new HashSet<Connection<DataType>>(node.connections);
    }

    /// <summary>
    /// Get all of the connections that are connected to the given node
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    public HashSet<Connection<DataType>> ConnectedNodes(Node<DataType> node)
    {
        HashSet<Connection<DataType>> connections = new HashSet<Connection<DataType>>();

        foreach (Node<DataType> newNode in nodes)
        {
            if (newNode.Equals(node))
            {
                continue;
            }

            foreach (Connection<DataType> connection in newNode.connections)
            {
                if (connection.to.Equals(node))
                {
                    connections.Add(connection);
                }
            }
        }

        return connections;
    }

    /// <summary>
    /// Get all of the connections of each node in a list
    /// </summary>
    /// <returns></returns>
    public HashSet<Connection<DataType>> AllConnections()
    {
        HashSet<Connection<DataType>> allConnections = new HashSet<Connection<DataType>>();

        foreach (Node<DataType> newNode in nodes)
        {
            foreach (Connection<DataType> connection in newNode.connections)
            {
                allConnections.Add(connection);
            }
        }

        return allConnections;
    }

    /// <summary>
    /// Get all of the connections of each node in a dictionary
    /// </summary>
    /// <returns></returns>
    public Dictionary<Node<DataType>, HashSet<Connection<DataType>>> AllConnectionsDictionary()
    {
        Dictionary<Node<DataType>, HashSet<Connection<DataType>>> allConnections = new Dictionary<Node<DataType>, HashSet<Connection<DataType>>>();

        foreach (Node<DataType> newNode in nodes)
        {
            allConnections[newNode] = newNode.connections;
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

        foreach (Node<DataType> newNode in nodes)
        {
            totalConnections += newNode.connections.Count;
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
