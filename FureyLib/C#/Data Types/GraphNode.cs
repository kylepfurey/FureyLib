
// Graph and Node Data Structures Script
// by Kyle Furey

using System.Collections;
using System.Collections.Generic;


// GENERIC DATA TYPE NODE, CONNECTION, AND GRAPH CLASSES

// An individual node with its own data, connections, and weight.
[System.Serializable]
public class Node<DataType>
{
    // NODE DATA

    // The data this node owns
    public DataType data = default(DataType);

    // The other nodes this node is connected to and the weight of that connection
    public List<Connection<DataType>> connections = new List<Connection<DataType>>();

    // The weight of this node
    public float weight = 1;

    // Whether this node is active
    public bool active = true;


    // NODE CONSTRUCTORS

    // Default constructor
    public Node(float weight = 1, bool active = true)
    {
        data = default(DataType);
        connections = new List<Connection<DataType>>();
        this.weight = weight;
        this.active = active;
    }

    public Node(bool active, float weight = 1)
    {
        data = default(DataType);
        connections = new List<Connection<DataType>>();
        this.weight = weight;
        this.active = active;
    }


    // Node constructor
    public Node(DataType data, List<Connection<DataType>> connections, float weight, bool active)
    {
        this.data = data;
        this.connections = connections;
        this.weight = weight;
        this.active = active;
    }

    public Node(DataType data, List<Connection<DataType>> connections, bool active, float weight)
    {
        this.data = data;
        this.connections = connections;
        this.weight = weight;
        this.active = active;
    }

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

    // Make and add a new connection to the list of connections
    public List<Connection<DataType>> AddConnection(Node<DataType> connectedNode, float weight = 1, bool active = true)
    {
        Connection<DataType> newConnection = new Connection<DataType>(this, connectedNode, weight, active);

        connections.Add(newConnection);

        return connections;
    }

    public List<Connection<DataType>> AddConnection(Node<DataType> connectedNode, bool active, float weight = 1)
    {
        Connection<DataType> newConnection = new Connection<DataType>(this, connectedNode, active, weight);

        connections.Add(newConnection);

        return connections;
    }

    // Make and remove a matching connection from the list of connections
    public List<Connection<DataType>> RemoveConnection(Node<DataType> connectedNode, float weight = 1, bool active = true)
    {
        Connection<DataType> newConnection = new Connection<DataType>(this, connectedNode, weight, active);

        connections.Remove(newConnection);

        return connections;
    }

    public List<Connection<DataType>> RemoveConnection(Node<DataType> connectedNode, bool active, float weight = 1)
    {
        Connection<DataType> newConnection = new Connection<DataType>(this, connectedNode, active, weight);

        connections.Remove(newConnection);

        return connections;
    }
}

// Stores the connection of two nodes and the weight of the connection.
[System.Serializable]
public class Connection<DataType>
{
    // CONNECTION DATA

    // The node that owns this connection
    public Node<DataType> from = null;

    // The node that is being connected to by the from node
    public Node<DataType> to = null;

    // The weight of this connection
    public float weight = 1;

    // Whether this connection is active
    public bool active = true;


    // CONNECTION CONSTRUCTORS

    // Default constructor
    public Connection()
    {
        from = null;
        to = null;
        weight = 1;
        active = true;
    }

    // Connection constructor
    public Connection(Node<DataType> from, Node<DataType> to, float weight = 1, bool active = true)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;
        this.active = active;
    }

    public Connection(Node<DataType> from, Node<DataType> to, bool active, float weight = 1)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;
        this.active = active;
    }


    // CONNECTION FUNCTIONS

    // Reconnect a connection's from
    public Connection<DataType> ReconnectFrom(Node<DataType> from)
    {
        this.from = from;

        return this;
    }

    public Connection<DataType> ReconnectFrom(Node<DataType> from, float weight)
    {
        this.from = from;
        this.weight = weight;

        return this;
    }

    public Connection<DataType> ReconnectFrom(Node<DataType> from, bool active)
    {
        this.from = from;
        this.active = active;

        return this;
    }

    public Connection<DataType> ReconnectFrom(Node<DataType> from, float weight, bool active)
    {
        this.from = from;
        this.weight = weight;
        this.active = active;

        return this;
    }

    public Connection<DataType> ReconnectFrom(Node<DataType> from, bool active, float weight)
    {
        this.from = from;
        this.weight = weight;
        this.active = active;

        return this;
    }

    // Reconnect a connection's to
    public Connection<DataType> ReconnectTo(Node<DataType> to)
    {
        this.to = to;

        return this;
    }

    public Connection<DataType> ReconnectTo(Node<DataType> to, float weight)
    {
        this.to = to;
        this.weight = weight;

        return this;
    }

    public Connection<DataType> ReconnectTo(Node<DataType> to, bool active)
    {
        this.to = to;
        this.active = active;

        return this;
    }

    public Connection<DataType> ReconnectTo(Node<DataType> to, float weight, bool active)
    {
        this.to = to;
        this.weight = weight;
        this.active = active;

        return this;
    }

    public Connection<DataType> ReconnectTo(Node<DataType> to, bool active, float weight)
    {
        this.to = to;
        this.weight = weight;
        this.active = active;

        return this;
    }

    // Reconnect a connection's from and to
    public Connection<DataType> Reconnect(Node<DataType> from, Node<DataType> to)
    {
        this.from = from;
        this.to = to;

        return this;
    }

    public Connection<DataType> Reconnect(Node<DataType> from, Node<DataType> to, float weight)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;

        return this;
    }

    public Connection<DataType> Reconnect(Node<DataType> from, Node<DataType> to, bool active)
    {
        this.from = from;
        this.to = to;
        this.active = active;

        return this;
    }

    public Connection<DataType> Reconnect(Node<DataType> from, Node<DataType> to, float weight, bool active)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;
        this.active = active;

        return this;
    }

    public Connection<DataType> Reconnect(Node<DataType> from, Node<DataType> to, bool active, float weight)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;
        this.active = active;

        return this;
    }
}

// A graph that manages all the nodes and connections inside it.
[System.Serializable]
public class Graph<DataType> : IEnumerable
{
    // GRAPH DATA

    // The list of nodes included in this graph
    public List<Node<DataType>> nodes;


    // GRAPH CONSTRUCTORS

    // Default constructor
    public Graph()
    {
        nodes = new List<Node<DataType>>();
    }

    // Node constructor
    public Graph(List<Node<DataType>> nodes)
    {
        this.nodes = nodes;
    }

    public Graph(params Node<DataType>[] nodes)
    {
        this.nodes = new List<Node<DataType>>(nodes.Length);

        for (int i = 0; i < nodes.Length; i++)
        {
            this.nodes.Add(nodes[i]);
        }
    }


    // GRAPH FUNCTIONS

    // Get all of the given node's connections
    public List<Connection<DataType>> NodeConnections(Node<DataType> node)
    {
        List<Connection<DataType>> connections = new List<Connection<DataType>>();

        for (int i = 0; i < node.connections.Count; i++)
        {
            connections.Add(node.connections[i]);
        }

        return connections;
    }

    // Get all of the connections that are connected to the given node
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

    // Get all of the connections of each node in a list
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

    // Get all of the connections of each node in a dictionary
    public Dictionary<Node<DataType>, List<Connection<DataType>>> AllConnectionsDictionary()
    {
        Dictionary<Node<DataType>, List<Connection<DataType>>> allConnections = new Dictionary<Node<DataType>, List<Connection<DataType>>>();

        for (int i = 0; i < nodes.Count; i++)
        {
            allConnections[nodes[i]] = nodes[i].connections;
        }

        return allConnections;
    }

    // Get the total number of connections of this graph
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

    // Enumerator implementation
    public IEnumerator GetEnumerator()
    {
        return nodes.GetEnumerator();
    }
}


// DATA TYPELESS NODE, CONNECTION, AND GRAPH CLASSES

// An individual node with its own connections and weight.
[System.Serializable]
public class Node
{
    // NODE DATA

    // The other nodes this node is connected to and the weight of that connection
    public List<Connection> connections = new List<Connection>();

    // The weight of this node
    public float weight = 1;

    // Whether this node is active
    public bool active = true;


    // NODE CONSTRUCTORS

    // Default constructor
    public Node(float weight = 1, bool active = true)
    {
        connections = new List<Connection>();
        this.weight = weight;
        this.active = active;
    }

    public Node(bool active, float weight = 1)
    {
        connections = new List<Connection>();
        this.weight = weight;
        this.active = active;
    }

    // Node constructor
    public Node(List<Connection> connections, float weight, bool active)
    {
        this.connections = connections;
        this.weight = weight;
        this.active = active;
    }

    public Node(List<Connection> connections, bool active, float weight)
    {
        this.connections = connections;
        this.weight = weight;
        this.active = active;
    }

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

    // Make and add a new connection to the list of connections
    public List<Connection> AddConnection(Node connectedNode, float weight = 1, bool active = true)
    {
        Connection newConnection = new Connection(this, connectedNode, weight, active);

        connections.Add(newConnection);

        return connections;
    }

    public List<Connection> AddConnection(Node connectedNode, bool active, float weight = 1)
    {
        Connection newConnection = new Connection(this, connectedNode, active, weight);

        connections.Add(newConnection);

        return connections;
    }

    // Make and remove a matching connection from the list of connections
    public List<Connection> RemoveConnection(Node connectedNode, float weight = 1, bool active = true)
    {
        Connection newConnection = new Connection(this, connectedNode, weight, active);

        connections.Remove(newConnection);

        return connections;
    }

    public List<Connection> RemoveConnection(Node connectedNode, bool active, float weight = 1)
    {
        Connection newConnection = new Connection(this, connectedNode, active, weight);

        connections.Remove(newConnection);

        return connections;
    }
}

// Stores the connection of two nodes and the weight of the connection.
[System.Serializable]
public class Connection
{
    // CONNECTION DATA

    // The node that owns this connection
    public Node from = null;

    // The node that is being connected to by the from node
    public Node to = null;

    // The weight of this connection
    public float weight = 1;

    // Whether this connection is active
    public bool active = true;


    // CONNECTION CONSTRUCTORS

    // Default constructor
    public Connection()
    {
        from = null;
        to = null;
        weight = 1;
        active = true;
    }

    // Connection constructor
    public Connection(Node from, Node to, float weight = 1, bool active = true)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;
        this.active = active;
    }

    public Connection(Node from, Node to, bool active, float weight = 1)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;
        this.active = active;
    }


    // CONNECTION FUNCTIONS

    // Reconnect a connection's from
    public Connection ReconnectFrom(Node from)
    {
        this.from = from;

        return this;
    }

    public Connection ReconnectFrom(Node from, float weight)
    {
        this.from = from;
        this.weight = weight;

        return this;
    }

    public Connection ReconnectFrom(Node from, bool active)
    {
        this.from = from;
        this.active = active;

        return this;
    }

    public Connection ReconnectFrom(Node from, float weight, bool active)
    {
        this.from = from;
        this.weight = weight;
        this.active = active;

        return this;
    }

    public Connection ReconnectFrom(Node from, bool active, float weight)
    {
        this.from = from;
        this.weight = weight;
        this.active = active;

        return this;
    }

    // Reconnect a connection's to
    public Connection ReconnectTo(Node to)
    {
        this.to = to;

        return this;
    }

    public Connection ReconnectTo(Node to, float weight)
    {
        this.to = to;
        this.weight = weight;

        return this;
    }

    public Connection ReconnectTo(Node to, bool active)
    {
        this.to = to;
        this.active = active;

        return this;
    }

    public Connection ReconnectTo(Node to, float weight, bool active)
    {
        this.to = to;
        this.weight = weight;
        this.active = active;

        return this;
    }

    public Connection ReconnectTo(Node to, bool active, float weight)
    {
        this.to = to;
        this.weight = weight;
        this.active = active;

        return this;
    }

    // Reconnect a connection's from and to
    public Connection Reconnect(Node from, Node to)
    {
        this.from = from;
        this.to = to;

        return this;
    }

    public Connection Reconnect(Node from, Node to, float weight)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;

        return this;
    }

    public Connection Reconnect(Node from, Node to, bool active)
    {
        this.from = from;
        this.to = to;
        this.active = active;

        return this;
    }

    public Connection Reconnect(Node from, Node to, float weight, bool active)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;
        this.active = active;

        return this;
    }

    public Connection Reconnect(Node from, Node to, bool active, float weight)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;
        this.active = active;

        return this;
    }
}

// A graph that manages all the nodes and connections inside it.
[System.Serializable]
public class Graph : IEnumerable
{
    // GRAPH DATA

    // The list of nodes included in this graph
    public List<Node> nodes;


    // GRAPH CONSTRUCTORS

    // Default constructor
    public Graph()
    {
        nodes = new List<Node>();
    }

    // Node constructor
    public Graph(List<Node> nodes)
    {
        this.nodes = nodes;
    }

    public Graph(params Node[] nodes)
    {
        this.nodes = new List<Node>(nodes.Length);

        for (int i = 0; i < nodes.Length; i++)
        {
            this.nodes.Add(nodes[i]);
        }
    }


    // GRAPH FUNCTIONS

    // Get all of the given node's connections
    public List<Connection> NodeConnections(Node node)
    {
        List<Connection> connections = new List<Connection>();

        for (int i = 0; i < node.connections.Count; i++)
        {
            connections.Add(node.connections[i]);
        }

        return connections;
    }

    // Get all of the connections that are connected to the given node
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

    // Get all of the connections of each node in a list
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

    // Get all of the connections of each node in a dictionary
    public Dictionary<Node, List<Connection>> AllConnectionsDictionary()
    {
        Dictionary<Node, List<Connection>> allConnections = new Dictionary<Node, List<Connection>>();

        for (int i = 0; i < nodes.Count; i++)
        {
            allConnections[nodes[i]] = nodes[i].connections;
        }

        return allConnections;
    }

    // Get the total number of connections of this graph
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

    // Enumerator implementation
    public IEnumerator GetEnumerator()
    {
        return nodes.GetEnumerator();
    }
}
