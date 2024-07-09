
// Graph and Node Data Structures Script
// by Kyle Furey

#pragma once
#include <vector>
#include <map>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the classes
#include "graph.h"

// Forward declaration of node
template <typename data_type> class node;

// Stores the connection of two nodes and the weight of the connection.
template <typename data_type> struct connection
{
public:

	// CONNECTION DATA

	// The node that owns this connection
	node<data_type>* from = nullptr;

	// The node that is being connected to by the from node
	node<data_type>* to = nullptr;

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
	connection(node<data_type>* from, node<data_type>* to, float weight = 1, bool active = true)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;
	}

	// Connection constructor
	connection(node<data_type>* from, node<data_type>* to, bool active, float weight = 1)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;
	}


	// CONNECTION FUNCTIONS

	// Reconnect a connection's from
	connection<data_type>& reconnect_from(node<data_type>* from)
	{
		this->from = from;

		return *this;
	}

	// Reconnect a connection's from
	connection<data_type>& reconnect_from(node<data_type>* from, float weight)
	{
		this->from = from;
		this->weight = weight;

		return *this;
	}

	// Reconnect a connection's from
	connection<data_type>& reconnect_from(node<data_type>* from, bool active)
	{
		this->from = from;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's from
	connection<data_type>& reconnect_from(node<data_type>* from, float weight, bool active)
	{
		this->from = from;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's from
	connection<data_type>& reconnect_from(node<data_type>* from, bool active, float weight)
	{
		this->from = from;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's to
	connection<data_type>& reconnect_to(node<data_type>* to)
	{
		this->to = to;

		return *this;
	}

	// Reconnect a connection's to
	connection<data_type>& reconnect_to(node<data_type>* to, float weight)
	{
		this->to = to;
		this->weight = weight;

		return *this;
	}

	// Reconnect a connection's to
	connection<data_type>& reconnect_to(node<data_type>* to, bool active)
	{
		this->to = to;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's to
	connection<data_type>& reconnect_to(node<data_type>* to, float weight, bool active)
	{
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's to
	connection<data_type>& reconnect_to(node<data_type>* to, bool active, float weight)
	{
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's from and to
	connection<data_type>& reconnect(node<data_type>* from, node<data_type>* to)
	{
		this->from = from;
		this->to = to;

		return *this;
	}

	// Reconnect a connection's from and to
	connection<data_type>& reconnect(node<data_type>* from, node<data_type>* to, float weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;

		return *this;
	}

	// Reconnect a connection's from and to
	connection<data_type>& reconnect(node<data_type>* from, node<data_type>* to, bool active)
	{
		this->from = from;
		this->to = to;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's from and to
	connection<data_type>& reconnect(node<data_type>* from, node<data_type>* to, float weight, bool active)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}

	// Reconnect a connection's from and to
	connection<data_type>& reconnect(node<data_type>* from, node<data_type>* to, bool active, float weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->active = active;

		return *this;
	}


	// CONNECTION OPERATORS

	// Equals operator
	bool operator==(const connection<data_type> compared)
	{
		return *this == compared;
	}
};

// An individual node with its own connections and weight.
template <typename data_type> class node
{
public:

	// NODE DATA

	// The data this node owns
	data_type data = data_type();

	// The other nodes this node is connected to and the weight of that connection
	std::vector<connection<data_type>> connections = std::vector<connection<data_type>>();

	// The weight of this node
	float weight = 1;

	// Whether this node is active
	bool active = true;


	// NODE CONSTRUCTORS

	// Default constructor
	node(data_type data = data_type(), float weight = 1, bool active = true)
	{
		this->data = data;
		connections = std::vector<connection<data_type>>();
		this->weight = weight;
		this->active = active;
	}

	// Default constructor
	node(data_type data, bool active, float weight = 1)
	{
		this->data = data;
		connections = std::vector<connection<data_type>>();
		this->weight = weight;
		this->active = active;
	}

	// Node constructor
	node(data_type data, std::vector<connection<data_type>> connections, float weight, bool active)
	{
		this->data = data;
		this->connections = connections;
		this->weight = weight;
		this->active = active;
	}

	// Node constructor
	node(data_type data, std::vector<connection<data_type>> connections, bool active, float weight)
	{
		this->data = data;
		this->connections = connections;
		this->weight = weight;
		this->active = active;
	}

	// Node constructor
	node(data_type data, int number_of_connections, connection<data_type> connections[], float weight, bool active)
	{
		this->data = data;

		this->connections = std::vector<connection<data_type>>();

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections[i]);
		}

		this->weight = weight;
		this->active = active;
	}

	// Node constructor
	node(data_type data, int number_of_connections, connection<data_type> connections[], bool active, float weight)
	{
		this->data = data;

		this->connections = std::vector<connection<data_type>>();

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections[i]);
		}

		this->weight = weight;
		this->active = active;
	}

	// Node constructor
	node(data_type data, float weight, bool active, int number_of_connections, connection<data_type> connections...)
	{
		this->data = data;

		this->connections = std::vector<connection<data_type>>();

		va_list list;

		va_start(list, number_of_connections);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections);

			connections = va_arg(list, connection<data_type>);
		}

		this->weight = weight;
		this->active = active;

		va_end(list);
	}

	// Node constructor
	node(data_type data, bool active, float weight, int number_of_connections, connection<data_type> connections...)
	{
		this->data = data;

		this->connections = std::vector<connection<data_type>>();

		va_list list;

		va_start(list, number_of_connections);

		for (int i = 0; i < number_of_connections; i++)
		{
			this->connections.push_back(connections);

			connections = va_arg(list, connection<data_type>);
		}

		this->weight = weight;
		this->active = active;

		va_end(list);
	}


	// NODE FUNCTIONS

	// Make and add a new connection to the list of connections
	std::vector<connection<data_type>>& add_connection(node<data_type>* connected_node, float weight = 1, bool active = true)
	{
		connection<data_type> new_connection = connection<data_type>(this, connected_node, weight, active);

		connections.push_back(new_connection);

		return connections;
	}

	// Make and add a new connection to the list of connections
	std::vector<connection<data_type>>& add_connection(node<data_type>* connected_node, bool active, float weight = 1)
	{
		connection<data_type> new_connection = connection<data_type>(this, connected_node, active, weight);

		connections.push_back(new_connection);

		return connections;
	}

	// Make and remove a matching connection from the list of connections
	std::vector<connection<data_type>>& remove_connection(node<data_type>* connected_node, float weight = 1, bool active = true)
	{
		connection<data_type> new_connection = connection<data_type>(this, connected_node, weight, active);

		connections.erase(std::find(connections.begin(), connections.end(), new_connection));

		return connections;
	}

	// Make and remove a matching connection from the list of connections
	std::vector<connection<data_type>>& remove_connection(node<data_type>* connected_node, bool active, float weight = 1)
	{
		connection<data_type> new_connection = connection<data_type>(this, connected_node, active, weight);

		connections.erase(std::find(connections.begin(), connections.end(), new_connection));

		return connections;
	}


	// NODE OPERATORS

	// Less than operator
	bool operator<(const node<data_type> compared) const noexcept
	{
		return *this < compared;
	}
};

// A graph that manages all the nodes and connections inside it.
template <typename data_type> struct graph
{
public:

	// GRAPH DATA

	// The list of nodes included in this graph
	std::vector<node<data_type>*> nodes = std::vector<node<data_type>*>();


	// GRAPH CONSTRUCTORS

	// Default constructor
	graph()
	{
		nodes = std::vector<node<data_type>*>();
	}

	// Node constructor
	graph(std::vector<node<data_type>*> nodes)
	{
		this->nodes = nodes;
	}

	// Node constructor
	graph(int number_of_nodes, node<data_type> nodes[])
	{
		this->nodes = std::vector<node<data_type>*>();

		for (int i = 0; i < number_of_nodes; i++)
		{
			this->nodes.push_back(nodes[i]);
		}
	}

	// Node constructor
	graph(int number_of_nodes, node<data_type>* nodes...)
	{
		this->nodes = std::vector<node<data_type>*>();

		va_list list;

		va_start(list, number_of_nodes);

		for (int i = 0; i < number_of_nodes; i++)
		{
			this->nodes.push_back(nodes);

			nodes = va_arg(list, node<data_type>*);
		}

		va_end(list);
	}

	// Node constructor
	graph(const std::initializer_list<node<data_type>*> nodes)
	{
		this->nodes = std::vector<node<data_type>*>();

		for (int i = 0; i < nodes.size(); i++)
		{
			this->nodes.push_back(*(nodes.begin() + i));
		}
	}


	// GRAPH FUNCTIONS

	// Get all of the given node's connections
	std::vector<connection<data_type>> node_connections(node<data_type>* node)
	{
		return node->connections;
	}

	// Get all of the connections that are connected to the given node
	std::vector<connection<data_type>> connected_nodes(node<data_type>* node)
	{
		std::vector<connection<data_type>> connections = std::vector<connection<data_type>>();

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
	std::vector<connection<data_type>> all_connections()
	{
		std::vector<connection<data_type>> all_connections = std::vector<connection<data_type>>();

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
	std::map<node<data_type>, std::vector<connection<data_type>>> all_connections_map()
	{
		std::map<node<data_type>, std::vector<connection<data_type>>> all_connections = std::map<node<data_type>, std::vector<connection<data_type>>>();

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
			total_connections += nodes[i]->connections.size();
		}

		return total_connections;
	}
};
