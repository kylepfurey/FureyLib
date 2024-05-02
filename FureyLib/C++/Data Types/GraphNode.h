
// Graph and Node Data Structures Script
// by Kyle Furey

#pragma once
#include <vector>
#include <map>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the classes
#include "GraphNode.h"


// GENERIC DATA TYPE NODE, CONNECTION, AND GRAPH CLASSES

// Forward declaration of node
template <class DataType> class t_node;

// Stores the connection of two nodes and the weight of the connection.
template<class DataType> class t_connection
{
public:

	// CONNECTION DATA

	// The node that owns this connection
	t_node<DataType>* from = nullptr;

	// The node that is being connected to by the from node
	t_node<DataType>* to = nullptr;

	// The weight of this connection
	float weight = 1;

	// Whether this connection is active
	bool active = true;


	// CONNECTION CONSTRUCTORS

	// Default constructor
	t_connection()
	{
		from = nullptr;
		to = nullptr;
		weight = 1;
		active = true;
	}

	// Connection constructor
	t_connection(t_node<DataType>* from, t_node<DataType>* to, float weight = 1, bool active = true)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;
	}

	t_connection(t_node<DataType>* from, t_node<DataType>* to, bool active, float weight = 1)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;
	}


	// CONNECTION FUNCTIONS

	// Reconnect a connection's from
	t_connection<DataType>& reconnect_from(t_node<DataType>* from)
	{
		this->from = from;

		return *this;
	}

	t_connection<DataType>& reconnect_from(t_node<DataType>* from, float weight)
	{
		this->from = from;
		this->weight = weight;

		return *this;
	}

	t_connection<DataType>& reconnect_from(t_node<DataType>* from, bool active)
	{
		this->from = from;
		this->active = active;

		return *this;
	}

	t_connection<DataType>& reconnect_from(t_node<DataType>* from, float weight, bool active)
	{
		this->from = from;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	t_connection<DataType>& reconnect_from(t_node<DataType>* from, bool active, float weight)
	{
		this->from = from;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's to
	t_connection<DataType>& reconnect_to(t_node<DataType>* to)
	{
		this->to = to;

		return *this;
	}

	t_connection<DataType>& reconnect_to(t_node<DataType>* to, float weight)
	{
		this->to = to;
		this->weight = weight;

		return *this;
	}

	t_connection<DataType>& reconnect_to(t_node<DataType>* to, bool active)
	{
		this->to = to;
		this->active = active;

		return *this;
	}

	t_connection<DataType>& reconnect_to(t_node<DataType>* to, float weight, bool active)
	{
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	t_connection<DataType>& reconnect_to(t_node<DataType>* to, bool active, float weight)
	{
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's from and to
	t_connection<DataType>& reconnect(t_node<DataType>* from, t_node<DataType>* to)
	{
		this->from = from;
		this->to = to;

		return *this;
	}

	t_connection<DataType>& reconnect(t_node<DataType>* from, t_node<DataType>* to, float weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;

		return *this;
	}

	t_connection<DataType>& reconnect(t_node<DataType>* from, t_node<DataType>* to, bool active)
	{
		this->from = from;
		this->to = to;
		this->active = active;

		return *this;
	}

	t_connection<DataType>& reconnect(t_node<DataType>* from, t_node<DataType>* to, float weight, bool active)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	t_connection<DataType>& reconnect(t_node<DataType>* from, t_node<DataType>* to, bool active, float weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}


	// CONNECTION OPERATORS

	// Equals operator
	bool operator==(const t_connection<DataType> compared)
	{
		return *this == compared;
	}
};

// An individual node with its own connections and weight.
template<class DataType> class t_node
{
public:

	// NODE DATA

	// The data this node owns
	DataType data = DataType();

	// The other nodes this node is connected to and the weight of that connection
	std::vector<t_connection<DataType>> connections = std::vector<t_connection<DataType>>();

	// The weight of this node
	float weight = 1;

	// Whether this node is active
	bool active = true;


	// NODE CONSTRUCTORS

	// Default constructor
	t_node(float weight = 1, bool active = true)
	{
		data = DataType();
		connections = std::vector<t_connection<DataType>>();
		this->weight = weight;
		this->active = active;
	}

	t_node(bool active, float weight = 1)
	{
		data = DataType();
		connections = std::vector<t_connection<DataType>>();
		this->weight = weight;
		this->active = active;
	}

	// Node constructor
	t_node(DataType data, std::vector<t_connection<DataType>> connections, float weight, bool active)
	{
		this->data = data;
		this->connections = connections;
		this->weight = weight;
		this->active = active;
	}

	t_node(DataType data, std::vector<t_connection<DataType>> connections, bool active, float weight)
	{
		this->data = data;
		this->connections = connections;
		this->weight = weight;
		this->active = active;
	}

	t_node(DataType data, t_connection<DataType> connections[], int number_of_connections, float weight, bool active)
	{
		this->data = data;

		this->connections = std::vector<t_connection<DataType>>(number_of_connections);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections[i]);
		}

		this->weight = weight;
		this->active = active;
	}

	t_node(DataType data, t_connection<DataType> connections[], int number_of_connections, bool active, float weight)
	{
		this->data = data;

		this->connections = std::vector<t_connection<DataType>>(number_of_connections);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections[i]);
		}

		this->weight = weight;
		this->active = active;
	}

	t_node(DataType data, float weight, bool active, int number_of_connections)
	{
		this->data = data;

		this->connections = std::vector<t_connection<DataType>>(number_of_connections);

		this->weight = weight;
		this->active = active;
	}

	t_node(DataType data, bool active, float weight, int number_of_connections)
	{
		this->data = data;

		this->connections = std::vector<t_connection<DataType>>(number_of_connections);

		this->weight = weight;
		this->active = active;
	}

	t_node(DataType data, float weight, bool active, int number_of_connections, t_connection<DataType> connections...)
	{
		this->data = data;

		this->connections = std::vector<t_connection<DataType>>(number_of_connections);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(va_arg(list, t_connection<DataType>));
		}

		this->weight = weight;
		this->active = active;

		va_end(list);
	}

	t_node(DataType data, bool active, float weight, int number_of_connections, t_connection<DataType> connections...)
	{
		this->data = data;

		this->connections = std::vector<t_connection<DataType>>(number_of_connections);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(va_arg(list, t_connection<DataType>));
		}

		this->weight = weight;
		this->active = active;

		va_end(list);
	}


	// NODE FUNCTIONS

	// Make and add a new connection to the list of connections
	std::vector<t_connection<DataType>>& add_connection(t_node<DataType>* connected_node, float weight = 1, bool active = true)
	{
		t_connection<DataType> new_connection = t_connection<DataType>(this, connected_node, weight, active);

		connections.push_back(new_connection);

		return connections;
	}

	std::vector<t_connection<DataType>>& add_connection(t_node<DataType>* connected_node, bool active, float weight = 1)
	{
		t_connection<DataType> new_connection = t_connection<DataType>(this, connected_node, active, weight);

		connections.push_back(new_connection);

		return connections;
	}

	// Make and remove a matching connection from the list of connections
	std::vector<t_connection<DataType>>& remove_connection(t_node<DataType>* connected_node, float weight = 1, bool active = true)
	{
		t_connection<DataType> new_connection = t_connection<DataType>(this, connected_node, weight, active);

		connections.erase(std::find(connections.begin(), connections.end(), new_connection));

		return connections;
	}

	std::vector<t_connection<DataType>>& remove_connection(t_node<DataType>* connected_node, bool active, float weight = 1)
	{
		t_connection<DataType> new_connection = t_connection<DataType>(this, connected_node, active, weight);

		connections.erase(std::find(connections.begin(), connections.end(), new_connection));

		return connections;
	}


	// NODE OPERATORS

	// Less than operator
	bool operator<(const t_node<DataType> compared) const noexcept
	{
		return *this < compared;
	}
};

// A graph that manages all the nodes and connections inside it.
template<class DataType> class t_graph
{
public:

	// GRAPH DATA

	// The list of nodes included in this graph
	std::vector<t_node<DataType>*> nodes = std::vector<t_node<DataType>*>();


	// GRAPH CONSTRUCTORS

	// Default constructor
	t_graph()
	{
		nodes = std::vector<t_node<DataType>*>();
	}

	// Node constructor
	t_graph(std::vector<t_node<DataType>*> nodes)
	{
		this->nodes = nodes;
	}

	t_graph(t_node<DataType>* nodes[], int number_of_nodes)
	{
		this->nodes = std::vector<t_node<DataType>*>(number_of_nodes);

		for (int i = 0; i < number_of_nodes; i++)
		{
			this->nodes.push_back(nodes[i]);
		}
	}

	t_graph(int number_of_nodes, t_node<DataType>* nodes...)
	{
		this->nodes = std::vector<t_node<DataType>*>(number_of_nodes);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_nodes; i++)
		{
			this->nodes.push_back(va_arg(list, t_node<DataType>*));
		}

		va_end(list);
	}

	t_graph(const std::initializer_list<t_node<DataType>*> nodes)
	{
		this->nodes = std::vector<t_node<DataType>*>(nodes.size());

		for (int i = 0; i < nodes.size(); i++)
		{
			this->nodes.push_back(*(nodes.begin() + i));
		}
	}


	// GRAPH FUNCTIONS

	// Get all of the given node's connections
	std::vector<t_connection<DataType>> node_connections(t_node<DataType>* node)
	{
		std::vector<t_connection<DataType>> connections = std::vector<t_connection<DataType>>();

		for (int i = 0; i < node->connections.size(); i++)
		{
			connections.push_back(node->connections[i]);
		}

		return connections;
	}

	// Get all of the connections that are connected to the given node
	std::vector<t_connection<DataType>> connected_nodes(t_node<DataType>* node)
	{
		std::vector<t_connection<DataType>> connections = std::vector<t_connection<DataType>>();

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
	std::vector<t_connection<DataType>> all_connections()
	{
		std::vector<t_connection<DataType>> all_connections = std::vector<t_connection<DataType>>();

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
	std::map<t_node<DataType>, std::vector<t_connection<DataType>>> all_connections_map()
	{
		std::map<t_node<DataType>, std::vector<t_connection<DataType>>> all_connections = std::map<t_node<DataType>, std::vector<t_connection<DataType>>>();

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


// DATA TYPELESS NODE, CONNECTION, AND GRAPH CLASSES

// Forward declaration of connection
class node;

// Stores the connection of two nodes and the weight of the connection.
class connection
{
public:

	// CONNECTION DATA

	// The node that owns this connection
	node* from = nullptr;

	// The node that is being connected to by the from node
	node* to = nullptr;

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
	connection(node* from, node* to, float weight = 1, bool active = true)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;
	}

	connection(node* from, node* to, bool active, float weight = 1)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;
	}


	// CONNECTION FUNCTIONS

	// Reconnect a connection's from
	connection& reconnect_from(node* from)
	{
		this->from = from;

		return *this;
	}

	connection& reconnect_from(node* from, float weight)
	{
		this->from = from;
		this->weight = weight;

		return *this;
	}

	connection& reconnect_from(node* from, bool active)
	{
		this->from = from;
		this->active = active;

		return *this;
	}

	connection& reconnect_from(node* from, float weight, bool active)
	{
		this->from = from;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	connection& reconnect_from(node* from, bool active, float weight)
	{
		this->from = from;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's to
	connection& reconnect_to(node* to)
	{
		this->to = to;

		return *this;
	}

	connection& reconnect_to(node* to, float weight)
	{
		this->to = to;
		this->weight = weight;

		return *this;
	}

	connection& reconnect_to(node* to, bool active)
	{
		this->to = to;
		this->active = active;

		return *this;
	}

	connection& reconnect_to(node* to, float weight, bool active)
	{
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	connection& reconnect_to(node* to, bool active, float weight)
	{
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's from and to
	connection& reconnect(node* from, node* to)
	{
		this->from = from;
		this->to = to;

		return *this;
	}

	connection& reconnect(node* from, node* to, float weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;

		return *this;
	}

	connection& reconnect(node* from, node* to, bool active)
	{
		this->from = from;
		this->to = to;
		this->active = active;

		return *this;
	}

	connection& reconnect(node* from, node* to, float weight, bool active)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	connection& reconnect(node* from, node* to, bool active, float weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}


	// CONNECTION OPERATORS

	// Equals operator
	bool operator==(const connection compared)
	{
		return *this == compared;
	}
};

// An individual node with its own connections and weight.
class node
{
public:

	// NODE DATA

	// The other nodes this node is connected to and the weight of that connection
	std::vector<connection> connections = std::vector<connection>();

	// The weight of this node
	float weight = 1;

	// Whether this node is active
	bool active = true;


	// NODE CONSTRUCTORS

	// Default constructor
	node(float weight = 1, bool active = true)
	{
		connections = std::vector<connection>();
		this->weight = weight;
		this->active = active;
	}

	node(bool active, float weight = 1)
	{
		connections = std::vector<connection>();
		this->weight = weight;
		this->active = active;
	}

	// Node constructor
	node(std::vector<connection> connections, float weight, bool active)
	{
		this->connections = connections;
		this->weight = weight;
		this->active = active;
	}

	node(std::vector<connection> connections, bool active, float weight)
	{
		this->connections = connections;
		this->weight = weight;
		this->active = active;
	}

	node(connection connections[], int number_of_connections, float weight, bool active)
	{
		this->connections = std::vector<connection>(number_of_connections);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections[i]);
		}

		this->weight = weight;
		this->active = active;
	}

	node(connection connections[], int number_of_connections, bool active, float weight)
	{
		this->connections = std::vector<connection>(number_of_connections);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections[i]);
		}

		this->weight = weight;
		this->active = active;
	}

	node(float weight, bool active, int number_of_connections)
	{
		this->connections = std::vector<connection>(number_of_connections);

		this->weight = weight;
		this->active = active;
	}

	node(bool active, float weight, int number_of_connections)
	{
		this->connections = std::vector<connection>(number_of_connections);

		this->weight = weight;
		this->active = active;
	}

	node(float weight, bool active, int number_of_connections, connection connections...)
	{
		this->connections = std::vector<connection>(number_of_connections);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(va_arg(list, connection));
		}

		this->weight = weight;
		this->active = active;

		va_end(list);
	}

	node(bool active, float weight, int number_of_connections, connection connections...)
	{
		this->connections = std::vector<connection>(number_of_connections);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(va_arg(list, connection));
		}

		this->weight = weight;
		this->active = active;

		va_end(list);
	}


	// NODE FUNCTIONS

	// Make and add a new connection to the list of connections
	std::vector<connection>& add_connection(node* connected_node, float weight = 1, bool active = true)
	{
		connection new_connection = connection(this, connected_node, weight, active);

		connections.push_back(new_connection);

		return connections;
	}

	std::vector<connection>& add_connection(node* connected_node, bool active, float weight = 1)
	{
		connection new_connection = connection(this, connected_node, active, weight);

		connections.push_back(new_connection);

		return connections;
	}

	// Make and remove a matching connection from the list of connections
	std::vector<connection>& remove_connection(node* connected_node, float weight = 1, bool active = true)
	{
		connection new_connection = connection(this, connected_node, weight, active);

		connections.erase(std::find(connections.begin(), connections.end(), new_connection));

		return connections;
	}

	std::vector<connection>& remove_connection(node* connected_node, bool active, float weight = 1)
	{
		connection new_connection = connection(this, connected_node, active, weight);

		connections.erase(std::find(connections.begin(), connections.end(), new_connection));

		return connections;
	}


	// NODE OPERATORS

	// Less than operator
	bool operator<(node compared) const noexcept
	{
		return *this < compared;
	}
};

// A graph that manages all the nodes and connections inside it.
class graph
{
public:

	// GRAPH DATA

	// The list of nodes included in this graph
	std::vector<node*> nodes = std::vector<node*>();


	// GRAPH CONSTRUCTORS

	// Default constructor
	graph()
	{
		nodes = std::vector<node*>();
	}

	// Node constructor
	graph(std::vector<node*> nodes)
	{
		this->nodes = nodes;
	}

	graph(node* nodes[], int number_of_nodes)
	{
		this->nodes = std::vector<node*>(number_of_nodes);

		for (int i = 0; i < number_of_nodes; i++)
		{
			this->nodes.push_back(nodes[i]);
		}
	}

	graph(int number_of_nodes, node* nodes...)
	{
		this->nodes = std::vector<node*>(number_of_nodes);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_nodes; i++)
		{
			this->nodes.push_back(va_arg(list, node*));
		}

		va_end(list);
	}

	graph(const std::initializer_list<node*> nodes)
	{
		this->nodes = std::vector<node*>(nodes.size());

		for (int i = 0; i < nodes.size(); i++)
		{
			this->nodes.push_back(*(nodes.begin() + i));
		}
	}


	// GRAPH FUNCTIONS

	// Get all of the given node's connections
	std::vector<connection> node_connections(node* node)
	{
		std::vector<connection> connections = std::vector<connection>();

		for (int i = 0; i < node->connections.size(); i++)
		{
			connections.push_back(node->connections[i]);
		}

		return connections;
	}

	// Get all of the connections that are connected to the given node
	std::vector<connection> connected_nodes(node* node)
	{
		std::vector<connection> connections = std::vector<connection>();

		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i] == node)
			{
				continue;
			}

			for (int j = 0; j < nodes[i]->connections.size(); j++)
			{
				if (nodes[i]->connections[j].to == node)
				{
					connections.push_back(nodes[i]->connections[j]);
				}
			}
		}

		return connections;
	}

	// Get all of the connections of each node in a list
	std::vector<connection> all_connections()
	{
		std::vector<connection> all_connections = std::vector<connection>();

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
	std::map<node, std::vector<connection>> all_connections_map()
	{
		std::map<node, std::vector<connection>> all_connections = std::map<node, std::vector<connection>>();

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


// GENERIC DATA TYPE NODE, CONNECTION, AND GRAPH CLASSES

// Forward declaration of node
template <class DataType> class TNode;

// Stores the connection of two nodes and the weight of the connection.
template<class DataType> class TConnection
{
public:

	// CONNECTION DATA

	// The node that owns this connection
	TNode<DataType>* from = nullptr;

	// The node that is being connected to by the from node
	TNode<DataType>* to = nullptr;

	// The weight of this connection
	float weight = 1;

	// Whether this connection is active
	bool active = true;


	// CONNECTION CONSTRUCTORS

	// Default constructor
	TConnection()
	{
		from = nullptr;
		to = nullptr;
		weight = 1;
		active = true;
	}

	// Connection constructor
	TConnection(TNode<DataType>* from, TNode<DataType>* to, float weight = 1, bool active = true)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;
	}

	TConnection(TNode<DataType>* from, TNode<DataType>* to, bool active, float weight = 1)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;
	}


	// CONNECTION FUNCTIONS

	// Reconnect a connection's from
	TConnection<DataType>& ReconnectFrom(TNode<DataType>* from)
	{
		this->from = from;

		return *this;
	}

	TConnection<DataType>& ReconnectFrom(TNode<DataType>* from, float weight)
	{
		this->from = from;
		this->weight = weight;

		return *this;
	}

	TConnection<DataType>& ReconnectFrom(TNode<DataType>* from, bool active)
	{
		this->from = from;
		this->active = active;

		return *this;
	}

	TConnection<DataType>& ReconnectFrom(TNode<DataType>* from, float weight, bool active)
	{
		this->from = from;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	TConnection<DataType>& ReconnectFrom(TNode<DataType>* from, bool active, float weight)
	{
		this->from = from;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's to
	TConnection<DataType>& ReconnectTo(TNode<DataType>* to)
	{
		this->to = to;

		return *this;
	}

	TConnection<DataType>& ReconnectTo(TNode<DataType>* to, float weight)
	{
		this->to = to;
		this->weight = weight;

		return *this;
	}

	TConnection<DataType>& ReconnectTo(TNode<DataType>* to, bool active)
	{
		this->to = to;
		this->active = active;

		return *this;
	}

	TConnection<DataType>& ReconnectTo(TNode<DataType>* to, float weight, bool active)
	{
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	TConnection<DataType>& ReconnectTo(TNode<DataType>* to, bool active, float weight)
	{
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's from and to
	TConnection<DataType>& Reconnect(TNode<DataType>* from, TNode<DataType>* to)
	{
		this->from = from;
		this->to = to;

		return *this;
	}

	TConnection<DataType>& Reconnect(TNode<DataType>* from, TNode<DataType>* to, float weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;

		return *this;
	}

	TConnection<DataType>& Reconnect(TNode<DataType>* from, TNode<DataType>* to, bool active)
	{
		this->from = from;
		this->to = to;
		this->active = active;

		return *this;
	}

	TConnection<DataType>& Reconnect(TNode<DataType>* from, TNode<DataType>* to, float weight, bool active)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	TConnection<DataType>& Reconnect(TNode<DataType>* from, TNode<DataType>* to, bool active, float weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}


	// CONNECTION OPERATORS

	// Equals operator
	bool operator==(const TConnection<DataType> compared)
	{
		return *this == compared;
	}
};

// An individual node with its own connections and weight.
template<class DataType> class TNode
{
public:

	// NODE DATA

	// The data this node owns
	DataType data = DataType();

	// The other nodes this node is connected to and the weight of that connection
	std::vector<TConnection<DataType>> connections = std::vector<TConnection<DataType>>();

	// The weight of this node
	float weight = 1;

	// Whether this node is active
	bool active = true;


	// NODE CONSTRUCTORS

	// Default constructor
	TNode(float weight = 1, bool active = true)
	{
		data = DataType();
		connections = std::vector<TConnection<DataType>>();
		this->weight = weight;
		this->active = active;
	}

	TNode(bool active, float weight = 1)
	{
		data = DataType();
		connections = std::vector<TConnection<DataType>>();
		this->weight = weight;
		this->active = active;
	}

	// Node constructor
	TNode(DataType data, std::vector<TConnection<DataType>> connections, float weight, bool active)
	{
		this->data = data;
		this->connections = connections;
		this->weight = weight;
		this->active = active;
	}

	TNode(DataType data, std::vector<TConnection<DataType>> connections, bool active, float weight)
	{
		this->data = data;
		this->connections = connections;
		this->weight = weight;
		this->active = active;
	}

	TNode(DataType data, TConnection<DataType> connections[], int number_of_connections, float weight, bool active)
	{
		this->data = data;

		this->connections = std::vector<TConnection<DataType>>(number_of_connections);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections[i]);
		}

		this->weight = weight;
		this->active = active;
	}

	TNode(DataType data, TConnection<DataType> connections[], int number_of_connections, bool active, float weight)
	{
		this->data = data;

		this->connections = std::vector<TConnection<DataType>>(number_of_connections);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections[i]);
		}

		this->weight = weight;
		this->active = active;
	}

	TNode(DataType data, float weight, bool active, int number_of_connections)
	{
		this->data = data;

		this->connections = std::vector<TConnection<DataType>>(number_of_connections);

		this->weight = weight;
		this->active = active;
	}

	TNode(DataType data, bool active, float weight, int number_of_connections)
	{
		this->data = data;

		this->connections = std::vector<TConnection<DataType>>(number_of_connections);

		this->weight = weight;
		this->active = active;
	}

	TNode(DataType data, float weight, bool active, int number_of_connections, TConnection<DataType> connections...)
	{
		this->data = data;

		this->connections = std::vector<TConnection<DataType>>(number_of_connections);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(va_arg(list, TConnection<DataType>));
		}

		this->weight = weight;
		this->active = active;

		va_end(list);
	}

	TNode(DataType data, bool active, float weight, int number_of_connections, TConnection<DataType> connections...)
	{
		this->data = data;

		this->connections = std::vector<TConnection<DataType>>(number_of_connections);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(va_arg(list, TConnection<DataType>));
		}

		this->weight = weight;
		this->active = active;

		va_end(list);
	}


	// NODE FUNCTIONS

	// Make and add a new connection to the list of connections
	std::vector<TConnection<DataType>>& AddConnection(TNode<DataType>* connected_node, float weight = 1, bool active = true)
	{
		TConnection<DataType> new_connection = TConnection<DataType>(this, connected_node, weight, active);

		connections.push_back(new_connection);

		return connections;
	}

	std::vector<TConnection<DataType>>& AddConnection(TNode<DataType>* connected_node, bool active, float weight = 1)
	{
		TConnection<DataType> new_connection = TConnection<DataType>(this, connected_node, active, weight);

		connections.push_back(new_connection);

		return connections;
	}

	// Make and remove a matching connection from the list of connections
	std::vector<TConnection<DataType>>& RemoveConnection(TNode<DataType>* connected_node, float weight = 1, bool active = true)
	{
		TConnection<DataType> new_connection = TConnection<DataType>(this, connected_node, weight, active);

		connections.erase(std::find(connections.begin(), connections.end(), new_connection));

		return connections;
	}

	std::vector<TConnection<DataType>>& RemoveConnection(TNode<DataType>* connected_node, bool active, float weight = 1)
	{
		TConnection<DataType> new_connection = TConnection<DataType>(this, connected_node, active, weight);

		connections.erase(std::find(connections.begin(), connections.end(), new_connection));

		return connections;
	}


	// NODE OPERATORS

	// Less than operator
	bool operator<(const TNode<DataType> compared) const noexcept
	{
		return *this < compared;
	}
};

// A graph that manages all the nodes and connections inside it.
template<class DataType> class TGraph
{
public:

	// GRAPH DATA

	// The list of nodes included in this graph
	std::vector<TNode<DataType>*> nodes = std::vector<TNode<DataType>*>();


	// GRAPH CONSTRUCTORS

	// Default constructor
	TGraph()
	{
		nodes = std::vector<TNode<DataType>*>();
	}

	// Node constructor
	TGraph(std::vector<TNode<DataType>*> nodes)
	{
		this->nodes = nodes;
	}

	TGraph(TNode<DataType>* nodes[], int number_of_nodes)
	{
		this->nodes = std::vector<TNode<DataType>*>(number_of_nodes);

		for (int i = 0; i < number_of_nodes; i++)
		{
			this->nodes.push_back(nodes[i]);
		}
	}

	TGraph(int number_of_nodes, TNode<DataType>* nodes...)
	{
		this->nodes = std::vector<TNode<DataType>*>(number_of_nodes);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_nodes; i++)
		{
			this->nodes.push_back(va_arg(list, TNode<DataType>*));
		}

		va_end(list);
	}

	TGraph(const std::initializer_list<TNode<DataType>*> nodes)
	{
		this->nodes = std::vector<TNode<DataType>*>(nodes.size());

		for (int i = 0; i < nodes.size(); i++)
		{
			this->nodes.push_back(*(nodes.begin() + i));
		}
	}


	// GRAPH FUNCTIONS

	// Get all of the given node's connections
	std::vector<TConnection<DataType>> NodeConnections(TNode<DataType>* node)
	{
		std::vector<TConnection<DataType>> connections = std::vector<TConnection<DataType>>();

		for (int i = 0; i < node->connections.size(); i++)
		{
			connections.push_back(node->connections[i]);
		}

		return connections;
	}

	// Get all of the connections that are connected to the given node
	std::vector<TConnection<DataType>> ConnectedNodes(TNode<DataType>* node)
	{
		std::vector<TConnection<DataType>> connections = std::vector<TConnection<DataType>>();

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
	std::vector<TConnection<DataType>> AllConnections()
	{
		std::vector<TConnection<DataType>> all_connections = std::vector<TConnection<DataType>>();

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
	std::map<TNode<DataType>, std::vector<TConnection<DataType>>> AllConnectionsMap()
	{
		std::map<TNode<DataType>, std::vector<TConnection<DataType>>> all_connections = std::map<TNode<DataType>, std::vector<TConnection<DataType>>>();

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


// DATA TYPELESS NODE, CONNECTION, AND GRAPH CLASSES

// Forward declaration of connection
class Node;

// Stores the connection of two nodes and the weight of the connection.
class Connection
{
public:

	// CONNECTION DATA

	// The node that owns this connection
	Node* from = nullptr;

	// The node that is being connected to by the from node
	Node* to = nullptr;

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
	Connection(Node* from, Node* to, float weight = 1, bool active = true)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;
	}

	Connection(Node* from, Node* to, bool active, float weight = 1)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;
	}


	// CONNECTION FUNCTIONS

	// Reconnect a connection's from
	Connection& ReconnectFrom(Node* from)
	{
		this->from = from;

		return *this;
	}

	Connection& ReconnectFrom(Node* from, float weight)
	{
		this->from = from;
		this->weight = weight;

		return *this;
	}

	Connection& ReconnectFrom(Node* from, bool active)
	{
		this->from = from;
		this->active = active;

		return *this;
	}

	Connection& ReconnectFrom(Node* from, float weight, bool active)
	{
		this->from = from;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	Connection& ReconnectFrom(Node* from, bool active, float weight)
	{
		this->from = from;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's to
	Connection& ReconnectTo(Node* to)
	{
		this->to = to;

		return *this;
	}

	Connection& ReconnectTo(Node* to, float weight)
	{
		this->to = to;
		this->weight = weight;

		return *this;
	}

	Connection& ReconnectTo(Node* to, bool active)
	{
		this->to = to;
		this->active = active;

		return *this;
	}

	Connection& ReconnectTo(Node* to, float weight, bool active)
	{
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	Connection& ReconnectTo(Node* to, bool active, float weight)
	{
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's from and to
	Connection& Reconnect(Node* from, Node* to)
	{
		this->from = from;
		this->to = to;

		return *this;
	}

	Connection& Reconnect(Node* from, Node* to, float weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;

		return *this;
	}

	Connection& Reconnect(Node* from, Node* to, bool active)
	{
		this->from = from;
		this->to = to;
		this->active = active;

		return *this;
	}

	Connection& Reconnect(Node* from, Node* to, float weight, bool active)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	Connection& Reconnect(Node* from, Node* to, bool active, float weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}


	// CONNECTION OPERATORS

	// Equals operator
	bool operator==(const Connection compared)
	{
		return *this == compared;
	}
};

// An individual node with its own connections and weight.
class Node
{
public:

	// NODE DATA

	// The other nodes this node is connected to and the weight of that connection
	std::vector<Connection> connections = std::vector<Connection>();

	// The weight of this node
	float weight = 1;

	// Whether this node is active
	bool active = true;


	// NODE CONSTRUCTORS

	// Default constructor
	Node(float weight = 1, bool active = true)
	{
		connections = std::vector<Connection>();
		this->weight = weight;
		this->active = active;
	}

	Node(bool active, float weight = 1)
	{
		connections = std::vector<Connection>();
		this->weight = weight;
		this->active = active;
	}

	// Node constructor
	Node(std::vector<Connection> connections, float weight, bool active)
	{
		this->connections = connections;
		this->weight = weight;
		this->active = active;
	}

	Node(std::vector<Connection> connections, bool active, float weight)
	{
		this->connections = connections;
		this->weight = weight;
		this->active = active;
	}

	Node(Connection connections[], int number_of_connections, float weight, bool active)
	{
		this->connections = std::vector<Connection>(number_of_connections);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections[i]);
		}

		this->weight = weight;
		this->active = active;
	}

	Node(Connection connections[], int number_of_connections, bool active, float weight)
	{
		this->connections = std::vector<Connection>(number_of_connections);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections[i]);
		}

		this->weight = weight;
		this->active = active;
	}

	Node(float weight, bool active, int number_of_connections)
	{
		this->connections = std::vector<Connection>(number_of_connections);

		this->weight = weight;
		this->active = active;
	}

	Node(bool active, float weight, int number_of_connections)
	{
		this->connections = std::vector<Connection>(number_of_connections);

		this->weight = weight;
		this->active = active;
	}

	Node(float weight, bool active, int number_of_connections, Connection connections...)
	{
		this->connections = std::vector<Connection>(number_of_connections);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(va_arg(list, Connection));
		}

		this->weight = weight;
		this->active = active;

		va_end(list);
	}

	Node(bool active, float weight, int number_of_connections, Connection connections...)
	{
		this->connections = std::vector<Connection>(number_of_connections);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(va_arg(list, Connection));
		}

		this->weight = weight;
		this->active = active;

		va_end(list);
	}


	// NODE FUNCTIONS

	// Make and add a new connection to the list of connections
	std::vector<Connection>& AddConnection(Node* connected_node, float weight = 1, bool active = true)
	{
		Connection new_connection = Connection(this, connected_node, weight, active);

		connections.push_back(new_connection);

		return connections;
	}

	std::vector<Connection>& AddConnection(Node* connected_node, bool active, float weight = 1)
	{
		Connection new_connection = Connection(this, connected_node, active, weight);

		connections.push_back(new_connection);

		return connections;
	}

	// Make and remove a matching connection from the list of connections
	std::vector<Connection>& RemoveConnection(Node* connected_node, float weight = 1, bool active = true)
	{
		Connection new_connection = Connection(this, connected_node, weight, active);

		connections.erase(std::find(connections.begin(), connections.end(), new_connection));

		return connections;
	}

	std::vector<Connection>& RemoveConnection(Node* connected_node, bool active, float weight = 1)
	{
		Connection new_connection = Connection(this, connected_node, active, weight);

		connections.erase(std::find(connections.begin(), connections.end(), new_connection));

		return connections;
	}


	// NODE OPERATORS

	// Less than operator
	bool operator<(Node compared) const noexcept
	{
		return *this < compared;
	}
};

// A graph that manages all the nodes and connections inside it.
class Graph
{
public:

	// GRAPH DATA

	// The list of nodes included in this graph
	std::vector<Node*> nodes = std::vector<Node*>();


	// GRAPH CONSTRUCTORS

	// Default constructor
	Graph()
	{
		nodes = std::vector<Node*>();
	}

	// Node constructor
	Graph(std::vector<Node*> nodes)
	{
		this->nodes = nodes;
	}

	Graph(Node* nodes[], int number_of_nodes)
	{
		this->nodes = std::vector<Node*>(number_of_nodes);

		for (int i = 0; i < number_of_nodes; i++)
		{
			this->nodes.push_back(nodes[i]);
		}
	}

	Graph(int number_of_nodes, Node* nodes...)
	{
		this->nodes = std::vector<Node*>(number_of_nodes);

		va_list list;

		va_start(list, 1);

		for (int i = 0; i < number_of_nodes; i++)
		{
			this->nodes.push_back(va_arg(list, Node*));
		}

		va_end(list);
	}

	Graph(const std::initializer_list<Node*> nodes)
	{
		this->nodes = std::vector<Node*>(nodes.size());

		for (int i = 0; i < nodes.size(); i++)
		{
			this->nodes.push_back(*(nodes.begin() + i));
		}
	}


	// GRAPH FUNCTIONS

	// Get all of the given node's connections
	std::vector<Connection> NodeConnections(Node* node)
	{
		std::vector<Connection> connections = std::vector<Connection>();

		for (int i = 0; i < node->connections.size(); i++)
		{
			connections.push_back(node->connections[i]);
		}

		return connections;
	}

	// Get all of the connections that are connected to the given node
	std::vector<Connection> ConnectedNodes(Node* node)
	{
		std::vector<Connection> connections = std::vector<Connection>();

		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i] == node)
			{
				continue;
			}

			for (int j = 0; j < nodes[i]->connections.size(); j++)
			{
				if (nodes[i]->connections[j].to == node)
				{
					connections.push_back(nodes[i]->connections[j]);
				}
			}
		}

		return connections;
	}

	// Get all of the connections of each node in a list
	std::vector<Connection> AllConnections()
	{
		std::vector<Connection> all_connections = std::vector<Connection>();

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
	std::map<Node, std::vector<Connection>> AllConnectionsMap()
	{
		std::map<Node, std::vector<Connection>> all_connections = std::map<Node, std::vector<Connection>>();

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
