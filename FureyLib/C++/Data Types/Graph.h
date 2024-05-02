
// Graph and Node Data Structures Script
// by Kyle Furey

#pragma once
#include <vector>
#include <map>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the classes
#include "Graph.h"

// Forward declaration of node
template <class DataType> class node;

// Stores the connection of two nodes and the weight of the connection.
template<class DataType> class connection
{
public:

	// CONNECTION DATA

	// The node that owns this connection
	node<DataType>* from = nullptr;

	// The node that is being connected to by the from node
	node<DataType>* to = nullptr;

	// The weight of this connection
	float weight = 1;

	// Whether this connection is active
	bool active = true;


	// CONNECTION CONSTRUCTORS

	// Default constructor
	connection()
	{
		from = nullptr;
		to = nullptr;
		weight = 1;
		active = true;
	}

	// Connection constructor
	connection(node<DataType>* from, node<DataType>* to, float weight = 1, bool active = true)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;
	}

	connection(node<DataType>* from, node<DataType>* to, bool active, float weight = 1)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;
	}


	// CONNECTION FUNCTIONS

	// Reconnect a connection's from
	connection<DataType>& reconnect_from(node<DataType>* from)
	{
		this->from = from;

		return *this;
	}

	connection<DataType>& reconnect_from(node<DataType>* from, float weight)
	{
		this->from = from;
		this->weight = weight;

		return *this;
	}

	connection<DataType>& reconnect_from(node<DataType>* from, bool active)
	{
		this->from = from;
		this->active = active;

		return *this;
	}

	connection<DataType>& reconnect_from(node<DataType>* from, float weight, bool active)
	{
		this->from = from;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	connection<DataType>& reconnect_from(node<DataType>* from, bool active, float weight)
	{
		this->from = from;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's to
	connection<DataType>& reconnect_to(node<DataType>* to)
	{
		this->to = to;

		return *this;
	}

	connection<DataType>& reconnect_to(node<DataType>* to, float weight)
	{
		this->to = to;
		this->weight = weight;

		return *this;
	}

	connection<DataType>& reconnect_to(node<DataType>* to, bool active)
	{
		this->to = to;
		this->active = active;

		return *this;
	}

	connection<DataType>& reconnect_to(node<DataType>* to, float weight, bool active)
	{
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	connection<DataType>& reconnect_to(node<DataType>* to, bool active, float weight)
	{
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's from and to
	connection<DataType>& reconnect(node<DataType>* from, node<DataType>* to)
	{
		this->from = from;
		this->to = to;

		return *this;
	}

	connection<DataType>& reconnect(node<DataType>* from, node<DataType>* to, float weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;

		return *this;
	}

	connection<DataType>& reconnect(node<DataType>* from, node<DataType>* to, bool active)
	{
		this->from = from;
		this->to = to;
		this->active = active;

		return *this;
	}

	connection<DataType>& reconnect(node<DataType>* from, node<DataType>* to, float weight, bool active)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	connection<DataType>& reconnect(node<DataType>* from, node<DataType>* to, bool active, float weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}


	// CONNECTION OPERATORS

	// Equals operator
	bool operator==(const connection<DataType> compared)
	{
		return *this == compared;
	}
};

// An individual node with its own connections and weight.
template<class DataType> class node
{
public:

	// NODE DATA

	// The data this node owns
	DataType data = DataType();

	// The other nodes this node is connected to and the weight of that connection
	std::vector<connection<DataType>> connections = std::vector<connection<DataType>>();

	// The weight of this node
	float weight = 1;

	// Whether this node is active
	bool active = true;


	// NODE CONSTRUCTORS

	// Default constructor
	node(float weight = 1, bool active = true)
	{
		data = DataType();
		connections = std::vector<connection<DataType>>();
		this->weight = weight;
		this->active = active;
	}

	node(bool active, float weight = 1)
	{
		data = DataType();
		connections = std::vector<connection<DataType>>();
		this->weight = weight;
		this->active = active;
	}

	// Node constructor
	node(DataType data, std::vector<connection<DataType>> connections, float weight, bool active)
	{
		this->data = data;
		this->connections = connections;
		this->weight = weight;
		this->active = active;
	}

	node(DataType data, std::vector<connection<DataType>> connections, bool active, float weight)
	{
		this->data = data;
		this->connections = connections;
		this->weight = weight;
		this->active = active;
	}

	node(DataType data, connection<DataType> connections[], int number_of_connections, float weight, bool active)
	{
		this->data = data;

		this->connections = std::vector<connection<DataType>>(number_of_connections);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections[i]);
		}

		this->weight = weight;
		this->active = active;
	}

	node(DataType data, connection<DataType> connections[], int number_of_connections, bool active, float weight)
	{
		this->data = data;

		this->connections = std::vector<connection<DataType>>(number_of_connections);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections[i]);
		}

		this->weight = weight;
		this->active = active;
	}

	node(DataType data, float weight, bool active, int number_of_connections)
	{
		this->data = data;

		this->connections = std::vector<connection<DataType>>(number_of_connections);

		this->weight = weight;
		this->active = active;
	}

	node(DataType data, bool active, float weight, int number_of_connections)
	{
		this->data = data;

		this->connections = std::vector<connection<DataType>>(number_of_connections);

		this->weight = weight;
		this->active = active;
	}

	node(DataType data, float weight, bool active, int number_of_connections, connection<DataType> connections...)
	{
		this->data = data;

		this->connections = std::vector<connection<DataType>>(number_of_connections);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(va_arg(list, connection<DataType>));
		}

		this->weight = weight;
		this->active = active;

		va_end(list);
	}

	node(DataType data, bool active, float weight, int number_of_connections, connection<DataType> connections...)
	{
		this->data = data;

		this->connections = std::vector<connection<DataType>>(number_of_connections);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(va_arg(list, connection<DataType>));
		}

		this->weight = weight;
		this->active = active;

		va_end(list);
	}


	// NODE FUNCTIONS

	// Make and add a new connection to the list of connections
	std::vector<connection<DataType>>& add_connection(node<DataType>* connected_node, float weight = 1, bool active = true)
	{
		connection<DataType> new_connection = connection<DataType>(this, connected_node, weight, active);

		connections.push_back(new_connection);

		return connections;
	}

	std::vector<connection<DataType>>& add_connection(node<DataType>* connected_node, bool active, float weight = 1)
	{
		connection<DataType> new_connection = connection<DataType>(this, connected_node, active, weight);

		connections.push_back(new_connection);

		return connections;
	}

	// Make and remove a matching connection from the list of connections
	std::vector<connection<DataType>>& remove_connection(node<DataType>* connected_node, float weight = 1, bool active = true)
	{
		connection<DataType> new_connection = connection<DataType>(this, connected_node, weight, active);

		connections.erase(std::find(connections.begin(), connections.end(), new_connection));

		return connections;
	}

	std::vector<connection<DataType>>& remove_connection(node<DataType>* connected_node, bool active, float weight = 1)
	{
		connection<DataType> new_connection = connection<DataType>(this, connected_node, active, weight);

		connections.erase(std::find(connections.begin(), connections.end(), new_connection));

		return connections;
	}


	// NODE OPERATORS

	// Less than operator
	bool operator<(const node<DataType> compared) const noexcept
	{
		return *this < compared;
	}
};

// A graph that manages all the nodes and connections inside it.
template<class DataType> class graph
{
public:

	// GRAPH DATA

	// The list of nodes included in this graph
	std::vector<node<DataType>*> nodes = std::vector<node<DataType>*>();


	// GRAPH CONSTRUCTORS

	// Default constructor
	graph()
	{
		nodes = std::vector<node<DataType>*>();
	}

	// Node constructor
	graph(std::vector<node<DataType>*> nodes)
	{
		this->nodes = nodes;
	}

	graph(node<DataType>* nodes[], int number_of_nodes)
	{
		this->nodes = std::vector<node<DataType>*>(number_of_nodes);

		for (int i = 0; i < number_of_nodes; i++)
		{
			this->nodes.push_back(nodes[i]);
		}
	}

	graph(int number_of_nodes, node<DataType>* nodes...)
	{
		this->nodes = std::vector<node<DataType>*>(number_of_nodes);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_nodes; i++)
		{
			this->nodes.push_back(va_arg(list, node<DataType>*));
		}

		va_end(list);
	}

	graph(const std::initializer_list<node<DataType>*> nodes)
	{
		this->nodes = std::vector<node<DataType>*>(nodes.size());

		for (int i = 0; i < nodes.size(); i++)
		{
			this->nodes.push_back(*(nodes.begin() + i));
		}
	}


	// GRAPH FUNCTIONS

	// Get all of the given node's connections
	std::vector<connection<DataType>> node_connections(node<DataType>* node)
	{
		std::vector<connection<DataType>> connections = std::vector<connection<DataType>>();

		for (int i = 0; i < node->connections.size(); i++)
		{
			connections.push_back(node->connections[i]);
		}

		return connections;
	}

	// Get all of the connections that are connected to the given node
	std::vector<connection<DataType>> connected_nodes(node<DataType>* node)
	{
		std::vector<connection<DataType>> connections = std::vector<connection<DataType>>();

		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i] == node)
			{
				continue;
			}

			for (int j = 0; j < nodes[i]->connections.size(); j++)
			{
				if (nodes[i]->connections[j]->to == node)
				{
					connections.push_back(nodes[i]->connections[j]);
				}
			}
		}

		return connections;
	}

	// Get all of the connections of each node in a list
	std::vector<connection<DataType>> all_connections()
	{
		std::vector<connection<DataType>> all_connections = std::vector<connection<DataType>>();

		for (int i = 0; i < nodes.size(); i++)
		{
			for (int j = 0; j < nodes[i]->connections.size(); j++)
			{
				all_connections.push_back(nodes[i]->connections[j]);
			}
		}

		return all_connections;
	}

	// Get all of the connections of each node in a dictionary
	std::map<node<DataType>, std::vector<connection<DataType>>> all_connections_map()
	{
		std::map<node<DataType>, std::vector<connection<DataType>>> all_connections = std::map<node<DataType>, std::vector<connection<DataType>>>();

		for (int i = 0; i < nodes.size(); i++)
		{
			all_connections[*nodes[i]] = nodes[i]->connections;
		}

		return all_connections;
	}

	// Get the total number of connections of this graph
	int total_connections()
	{
		int total_connections = 0;

		for (int i = 0; i < nodes.size(); i++)
		{
			for (int j = 0; j < nodes[i]->connections.size(); j++)
			{
				total_connections++;
			}
		}

		return total_connections;
	}
};

// Forward declaration of node
template <class DataType> class Node;

// Stores the connection of two nodes and the weight of the connection.
template<class DataType> class Connection
{
public:

	// CONNECTION DATA

	// The node that owns this connection
	Node<DataType>* from = nullptr;

	// The node that is being connected to by the from node
	Node<DataType>* to = nullptr;

	// The weight of this connection
	float weight = 1;

	// Whether this connection is active
	bool active = true;


	// CONNECTION CONSTRUCTORS

	// Default constructor
	Connection()
	{
		from = nullptr;
		to = nullptr;
		weight = 1;
		active = true;
	}

	// Connection constructor
	Connection(Node<DataType>* from, Node<DataType>* to, float weight = 1, bool active = true)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;
	}

	Connection(Node<DataType>* from, Node<DataType>* to, bool active, float weight = 1)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;
	}


	// CONNECTION FUNCTIONS

	// Reconnect a connection's from
	Connection<DataType>& ReconnectFrom(Node<DataType>* from)
	{
		this->from = from;

		return *this;
	}

	Connection<DataType>& ReconnectFrom(Node<DataType>* from, float weight)
	{
		this->from = from;
		this->weight = weight;

		return *this;
	}

	Connection<DataType>& ReconnectFrom(Node<DataType>* from, bool active)
	{
		this->from = from;
		this->active = active;

		return *this;
	}

	Connection<DataType>& ReconnectFrom(Node<DataType>* from, float weight, bool active)
	{
		this->from = from;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	Connection<DataType>& ReconnectFrom(Node<DataType>* from, bool active, float weight)
	{
		this->from = from;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's to
	Connection<DataType>& ReconnectTo(Node<DataType>* to)
	{
		this->to = to;

		return *this;
	}

	Connection<DataType>& ReconnectTo(Node<DataType>* to, float weight)
	{
		this->to = to;
		this->weight = weight;

		return *this;
	}

	Connection<DataType>& ReconnectTo(Node<DataType>* to, bool active)
	{
		this->to = to;
		this->active = active;

		return *this;
	}

	Connection<DataType>& ReconnectTo(Node<DataType>* to, float weight, bool active)
	{
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	Connection<DataType>& ReconnectTo(Node<DataType>* to, bool active, float weight)
	{
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's from and to
	Connection<DataType>& Reconnect(Node<DataType>* from, Node<DataType>* to)
	{
		this->from = from;
		this->to = to;

		return *this;
	}

	Connection<DataType>& Reconnect(Node<DataType>* from, Node<DataType>* to, float weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;

		return *this;
	}

	Connection<DataType>& Reconnect(Node<DataType>* from, Node<DataType>* to, bool active)
	{
		this->from = from;
		this->to = to;
		this->active = active;

		return *this;
	}

	Connection<DataType>& Reconnect(Node<DataType>* from, Node<DataType>* to, float weight, bool active)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	Connection<DataType>& Reconnect(Node<DataType>* from, Node<DataType>* to, bool active, float weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}


	// CONNECTION OPERATORS

	// Equals operator
	bool operator==(const Connection<DataType> compared)
	{
		return *this == compared;
	}
};

// An individual node with its own connections and weight.
template<class DataType> class Node
{
public:

	// NODE DATA

	// The data this node owns
	DataType data = DataType();

	// The other nodes this node is connected to and the weight of that connection
	std::vector<Connection<DataType>> connections = std::vector<Connection<DataType>>();

	// The weight of this node
	float weight = 1;

	// Whether this node is active
	bool active = true;


	// NODE CONSTRUCTORS

	// Default constructor
	Node(float weight = 1, bool active = true)
	{
		data = DataType();
		connections = std::vector<Connection<DataType>>();
		this->weight = weight;
		this->active = active;
	}

	Node(bool active, float weight = 1)
	{
		data = DataType();
		connections = std::vector<Connection<DataType>>();
		this->weight = weight;
		this->active = active;
	}

	// Node constructor
	Node(DataType data, std::vector<Connection<DataType>> connections, float weight, bool active)
	{
		this->data = data;
		this->connections = connections;
		this->weight = weight;
		this->active = active;
	}

	Node(DataType data, std::vector<Connection<DataType>> connections, bool active, float weight)
	{
		this->data = data;
		this->connections = connections;
		this->weight = weight;
		this->active = active;
	}

	Node(DataType data, Connection<DataType> connections[], int number_of_connections, float weight, bool active)
	{
		this->data = data;

		this->connections = std::vector<Connection<DataType>>(number_of_connections);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections[i]);
		}

		this->weight = weight;
		this->active = active;
	}

	Node(DataType data, Connection<DataType> connections[], int number_of_connections, bool active, float weight)
	{
		this->data = data;

		this->connections = std::vector<Connection<DataType>>(number_of_connections);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections[i]);
		}

		this->weight = weight;
		this->active = active;
	}

	Node(DataType data, float weight, bool active, int number_of_connections)
	{
		this->data = data;

		this->connections = std::vector<Connection<DataType>>(number_of_connections);

		this->weight = weight;
		this->active = active;
	}

	Node(DataType data, bool active, float weight, int number_of_connections)
	{
		this->data = data;

		this->connections = std::vector<Connection<DataType>>(number_of_connections);

		this->weight = weight;
		this->active = active;
	}

	Node(DataType data, float weight, bool active, int number_of_connections, Connection<DataType> connections...)
	{
		this->data = data;

		this->connections = std::vector<Connection<DataType>>(number_of_connections);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(va_arg(list, Connection<DataType>));
		}

		this->weight = weight;
		this->active = active;

		va_end(list);
	}

	Node(DataType data, bool active, float weight, int number_of_connections, Connection<DataType> connections...)
	{
		this->data = data;

		this->connections = std::vector<Connection<DataType>>(number_of_connections);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(va_arg(list, Connection<DataType>));
		}

		this->weight = weight;
		this->active = active;

		va_end(list);
	}


	// NODE FUNCTIONS

	// Make and add a new connection to the list of connections
	std::vector<Connection<DataType>>& AddConnection(Node<DataType>* connected_node, float weight = 1, bool active = true)
	{
		Connection<DataType> new_connection = Connection<DataType>(this, connected_node, weight, active);

		connections.push_back(new_connection);

		return connections;
	}

	std::vector<Connection<DataType>>& AddConnection(Node<DataType>* connected_node, bool active, float weight = 1)
	{
		Connection<DataType> new_connection = Connection<DataType>(this, connected_node, active, weight);

		connections.push_back(new_connection);

		return connections;
	}

	// Make and remove a matching connection from the list of connections
	std::vector<Connection<DataType>>& RemoveConnection(Node<DataType>* connected_node, float weight = 1, bool active = true)
	{
		Connection<DataType> new_connection = Connection<DataType>(this, connected_node, weight, active);

		connections.erase(std::find(connections.begin(), connections.end(), new_connection));

		return connections;
	}

	std::vector<Connection<DataType>>& RemoveConnection(Node<DataType>* connected_node, bool active, float weight = 1)
	{
		Connection<DataType> new_connection = Connection<DataType>(this, connected_node, active, weight);

		connections.erase(std::find(connections.begin(), connections.end(), new_connection));

		return connections;
	}


	// NODE OPERATORS

	// Less than operator
	bool operator<(const Node<DataType> compared) const noexcept
	{
		return *this < compared;
	}
};

// A graph that manages all the nodes and connections inside it.
template<class DataType> class Graph
{
public:

	// GRAPH DATA

	// The list of nodes included in this graph
	std::vector<Node<DataType>*> nodes = std::vector<Node<DataType>*>();


	// GRAPH CONSTRUCTORS

	// Default constructor
	Graph()
	{
		nodes = std::vector<Node<DataType>*>();
	}

	// Node constructor
	Graph(std::vector<Node<DataType>*> nodes)
	{
		this->nodes = nodes;
	}

	Graph(Node<DataType>* nodes[], int number_of_nodes)
	{
		this->nodes = std::vector<Node<DataType>*>(number_of_nodes);

		for (int i = 0; i < number_of_nodes; i++)
		{
			this->nodes.push_back(nodes[i]);
		}
	}

	Graph(int number_of_nodes, Node<DataType>* nodes...)
	{
		this->nodes = std::vector<Node<DataType>*>(number_of_nodes);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_nodes; i++)
		{
			this->nodes.push_back(va_arg(list, Node<DataType>*));
		}

		va_end(list);
	}

	Graph(const std::initializer_list<Node<DataType>*> nodes)
	{
		this->nodes = std::vector<Node<DataType>*>(nodes.size());

		for (int i = 0; i < nodes.size(); i++)
		{
			this->nodes.push_back(*(nodes.begin() + i));
		}
	}


	// GRAPH FUNCTIONS

	// Get all of the given node's connections
	std::vector<Connection<DataType>> NodeConnections(Node<DataType>* node)
	{
		std::vector<Connection<DataType>> connections = std::vector<Connection<DataType>>();

		for (int i = 0; i < node->connections.size(); i++)
		{
			connections.push_back(node->connections[i]);
		}

		return connections;
	}

	// Get all of the connections that are connected to the given node
	std::vector<Connection<DataType>> ConnectedNodes(Node<DataType>* node)
	{
		std::vector<Connection<DataType>> connections = std::vector<Connection<DataType>>();

		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i] == node)
			{
				continue;
			}

			for (int j = 0; j < nodes[i]->connections.size(); j++)
			{
				if (nodes[i]->connections[j]->to == node)
				{
					connections.push_back(nodes[i]->connections[j]);
				}
			}
		}

		return connections;
	}

	// Get all of the connections of each node in a list
	std::vector<Connection<DataType>> AllConnections()
	{
		std::vector<Connection<DataType>> all_connections = std::vector<Connection<DataType>>();

		for (int i = 0; i < nodes.size(); i++)
		{
			for (int j = 0; j < nodes[i]->connections.size(); j++)
			{
				all_connections.push_back(nodes[i]->connections[j]);
			}
		}

		return all_connections;
	}

	// Get all of the connections of each node in a dictionary
	std::map<Node<DataType>, std::vector<Connection<DataType>>> AllConnectionsMap()
	{
		std::map<Node<DataType>, std::vector<Connection<DataType>>> all_connections = std::map<Node<DataType>, std::vector<Connection<DataType>>>();

		for (int i = 0; i < nodes.size(); i++)
		{
			all_connections[*nodes[i]] = nodes[i]->connections;
		}

		return all_connections;
	}

	// Get the total number of connections of this graph
	int TotalConnections()
	{
		int total_connections = 0;

		for (int i = 0; i < nodes.size(); i++)
		{
			for (int j = 0; j < nodes[i]->connections.size(); j++)
			{
				total_connections++;
			}
		}

		return total_connections;
	}
};
