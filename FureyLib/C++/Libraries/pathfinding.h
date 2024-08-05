
// Static Node Pathfinding Functions Script
// by Kyle Furey

// REFERENCE: https://www.redblobgames.com/pathfinding/a-star/introduction.html

// REQUIREMENT: graph.h

#pragma once
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <functional>
#include <algorithm>
#include <cmath>
#include <climits>
#include "graph.h"

// Include this heading to use the library
#include "pathfinding.h";

// Define the heuristic value type.
#define HEURISTIC_TYPE float

// A collection of pathfinding algorithms for navigating a graph of connected nodes.
class pathfinding
{
public:

	// PATHFINDING

	// Pathfinding algorithms.
	enum algorithm
	{
		// A Star Search
		a_star,

		// Dijkstra Search
		dijkstra,

		// Uniform Cost Search (Dijkstra)
		uniform_cost = dijkstra,

		// Heuristic Search
		heuristic,

		// Greedy Best First Search (Heuristic)
		greedy_best_first = heuristic,

		// Breadth First Search
		breadth_first,

		// Depth First Search
		depth_first
	};

	// The maximum number of loops before an algorithm terminates.
	static int max_loops;

	// •  Calculates an arbitrary value that represents how close a node is to the goal.
	// •  It is recommended to use Euclidean or Manhattan distance as your Heuristic.
	// •  This function must be defined in order to use the pathfinding functions.
	template<typename data_type> static HEURISTIC_TYPE calculate_heuristic(node<data_type>* current, node<data_type>* end);

	// •  Starting from the start node, returns a list of nodes representing a route to the end node using the given pathfinding algorithm.
	// •  Searches every possible node starting from oldest to newest.
	// •  Time complexity and precision depend on the selected pathfinding algorithm.
	// •  Will calculate the closest location to the goal if the goal is unreachable.
	template<typename data_type> static std::stack<node<data_type>*> pathfind(algorithm algorithm, node<data_type>* start, node<data_type>* end, HEURISTIC_TYPE heuristic_scale = 1)
	{
		switch (algorithm)
		{
		case algorithm::a_star:

			return a_star_search(start, end, heuristic_scale);

		case algorithm::dijkstra:

			return dijkstra_search(start, end);

		case algorithm::heuristic:

			return heuristic_search(start, end);

		case algorithm::breadth_first:

			return breadth_first_search(start, end);

		case algorithm::depth_first:

			return depth_first_search(start, end);
		}

		return std::stack<node<data_type>*>();
	}


	// ALGORITHMS

	// •  Starting from the start node, returns a list of nodes representing a route to the end node using the Depth First Search Algorithm.
	// •  Searches every possible node starting from newest to oldest.
	// •  Guarantees the fastest route but only checks the newest node first. This is best used for search trees.
	// •  Will calculate the closest location to the goal if the goal is unreachable.
	template<typename data_type> static std::stack<node<data_type>*> depth_first_search(node<data_type>* start, node<data_type>* end)
	{
		// Check if the start and end node are identical
		if (start == end)
		{
			return std::stack<node<data_type>*>();
		}

		// Initialize our frontier
		std::stack<node<data_type>*> frontier = std::stack<node<data_type>*>();

		// Enqueue our start node
		frontier.push(start);

		// Make a map to store each node's node before it (which will eventually store the route from the end node to the start)
		// KEY = TO  VALUE = FROM
		// from[current_node] = the node immediately before current_node
		std::map<node<data_type>*, node<data_type>*> from = std::map<node<data_type>*, node<data_type>*>
		{
			// Set our start node's value to an impossible node in our route map
			{ start, nullptr }
		};

		// Store our current value and number of loops
		node<data_type>* current = end;

		int loop_count = -1;

		// Loop until our frontier is empty
		while (frontier.size() > 0)
		{
			// Loop check
			loop_count++;

			if (loop_count >= max_loops)
			{
				break;
			}

			// Pop our current node and increment our number of loops
			current = frontier.top();

			frontier.pop();

			// Check if we made it to our goal
			if (current == end)
			{
				break;
			}

			// Loop through our current node's connections
			for (connection<data_type> connection : current->connections)
			{
				// Check that this connection is a valid connection and a valid node
				if (!connection.active || !connection.to->active)
				{
					continue;
				}

				// Check that our connected node is not currently in our dictionary
				if (!from.count(connection.to))
				{
					// Enqueue our connected node to the frontier
					frontier.push(connection.to);

					// Add our connected node as our key and our current node as our value to the dictionary
					from[connection.to] = current;
				}
			}
		}

		// Clear the frontier
		frontier = std::stack<node<data_type>*>();

		// Check that we made it to our end node
		if (current != end)
		{
			// Store our new goal
			current = start;

			// Store our current heuristic
			HEURISTIC_TYPE current_heuristic = INT_MAX;

			// Calculate the closest node to our goal
			for (auto to : from)
			{
				// Calculate the new heuristic
				HEURISTIC_TYPE new_heuristic = calculate_heuristic(to.second, end);

				// Check if the new heuristic is closer to the goal
				if (new_heuristic < current_heuristic)
				{
					// Mark the new goal
					current = to.second;

					// Update the heuristic
					current_heuristic = new_heuristic;
				}
			}
		}

		// Store our route
		std::stack<node<data_type>*> route = std::stack<node<data_type>*>();

		// Build our final route through our map's connections
		while (from[current] != nullptr)
		{
			// Add our current node to the route
			route.push(current);

			// Set our current node to the previous node
			current = from[current];
		}

		// Return our final route
		return route;
	}

	// •  Starting from the start node, returns a list of nodes representing a route to the end node using the Breadth First Search Algorithm.
	// •  Searches every possible node starting from oldest to newest.
	// •  Guarantees the fastest route but increases in time exponentially.
	// •  Will calculate the closest location to the goal if the goal is unreachable.
	template<typename data_type> static std::stack<node<data_type>*> breadth_first_search(node<data_type>* start, node<data_type>* end)
	{
		// Check if the start and end node are identical
		if (start == end)
		{
			return std::stack<node<data_type>*>();
		}

		// Initialize our frontier
		std::queue<node<data_type>*> frontier = std::queue<node<data_type>*>();

		// Enqueue our start node
		frontier.push(start);

		// Make a map to store each node's node before it (which will eventually store the route from the end node to the start)
		// KEY = TO  VALUE = FROM
		// from[current_node] = the node immediately before current_node
		std::map<node<data_type>*, node<data_type>*> from = std::map<node<data_type>*, node<data_type>*>
		{
			// Set our start node's value to an impossible node in our route map
			{ start, nullptr }
		};

		// Store our current value and number of loops
		node<data_type>* current = end;

		int loop_count = -1;

		// Loop until our frontier is empty
		while (frontier.size() > 0)
		{
			// Loop check
			loop_count++;

			if (loop_count >= max_loops)
			{
				break;
			}

			// Pop our current node and increment our number of loops
			current = frontier.front();

			frontier.pop();

			// Check if we made it to our goal
			if (current == end)
			{
				break;
			}

			// Loop through our current node's connections
			for (connection<data_type> connection : current->connections)
			{
				// Check that this connection is a valid connection and a valid node
				if (!connection.active || !connection.to->active)
				{
					continue;
				}

				// Check that our connected node is not currently in our dictionary
				if (!from.count(connection.to))
				{
					// Enqueue our connected node to the frontier
					frontier.push(connection.to);

					// Add our connected node as our key and our current node as our value to the dictionary
					from[connection.to] = current;
				}
			}
		}

		// Clear the frontier
		frontier = std::queue<node<data_type>*>();

		// Check that we made it to our end node
		if (current != end)
		{
			// Store our new goal
			current = start;

			// Store our current heuristic
			HEURISTIC_TYPE current_heuristic = INT_MAX;

			// Calculate the closest node to our goal
			for (auto to : from)
			{
				// Calculate the new heuristic
				HEURISTIC_TYPE new_heuristic = calculate_heuristic(to.second, end);

				// Check if the new heuristic is closer to the goal
				if (new_heuristic < current_heuristic)
				{
					// Mark the new goal
					current = to.second;

					// Update the heuristic
					current_heuristic = new_heuristic;
				}
			}
		}

		// Store our route
		std::stack<node<data_type>*> route = std::stack<node<data_type>*>();

		// Build our final route through our map's connections
		while (from[current] != nullptr)
		{
			// Add our current node to the route
			route.push(current);

			// Set our current node to the previous node
			current = from[current];
		}

		// Return our final route
		return route;
	}

	// •  Starting from the start node, returns a list of nodes representing a route to the end node using the Heuristic Search Algorithm.
	// •  Searches every possible node from oldest to newest but queues nodes considered closer to the goal by the heuristic function first.
	// •  Completes quicker but can be a slower route.
	// •  Will calculate the closest location to the goal if the goal is unreachable.
	template<typename data_type> static std::stack<node<data_type>*> heuristic_search(node<data_type>* start, node<data_type>* end)
	{
		// Check if the start and end node are identical
		if (start == end)
		{
			return std::stack<node<data_type>*>();
		}

		// Initialize our frontier
		std::multimap<HEURISTIC_TYPE, node<data_type>*> frontier = std::multimap<HEURISTIC_TYPE, node<data_type>*>();

		// Enqueue our start node
		frontier.insert({ 0, start });

		// Make a map to store each node's node before it (which will eventually store the route from the end node to the start)
		// KEY = TO  VALUE = FROM
		// from[current_node<data_type>*] = the node immediately before current_node<data_type>*
		std::map<node<data_type>*, node<data_type>*> from = std::map<node<data_type>*, node<data_type>*>
		{
			// Set our start node's value to an impossible node in our route map
			{ start, nullptr }
		};

		// Store our current value and number of loops
		node<data_type>* current = end;

		int loop_count = -1;

		// Loop until our frontier is empty
		while (frontier.size() > 0)
		{
			// Loop check
			loop_count++;

			if (loop_count >= max_loops)
			{
				break;
			}

			// Pop our current node and increment our number of loops
			current = frontier.begin()->second;

			frontier.erase(frontier.begin()->first);

			// Check if we made it to our goal
			if (current == end)
			{
				break;
			}

			// Loop through our current node's connections
			for (connection<data_type> connection : current->connections)
			{
				// Check that this connection is a valid connection and a valid node
				if (!connection.active || !connection.to->active)
				{
					continue;
				}

				// Check that our connected node is not currently in our dictionary
				if (!from.count(connection.to))
				{
					// Enqueue our connected node to the frontier based on the heuristic function
					frontier.push(connection.to, calculate_heuristic(connection.to, end));

					// Add our connected node as our key and our current node as our value to the dictionary
					from[connection.to] = current;
				}
			}
		}

		// Clear the frontier
		frontier = std::multimap<HEURISTIC_TYPE, node<data_type>*>();

		// Check that we made it to our end node
		if (current != end)
		{
			// Store our new goal
			current = start;

			// Store our current heuristic
			HEURISTIC_TYPE current_heuristic = INT_MAX;

			// Calculate the closest node to our goal
			for (auto to : from)
			{
				// Calculate the new heuristic
				HEURISTIC_TYPE new_heuristic = calculate_heuristic(to.second, end);

				// Check if the new heuristic is closer to the goal
				if (new_heuristic < current_heuristic)
				{
					// Mark the new goal
					current = to.second;

					// Update the heuristic
					current_heuristic = new_heuristic;
				}
			}
		}

		// Store our route
		std::stack<node<data_type>*> route = std::stack<node<data_type>*>();

		// Build our final route through our map's connections
		while (from[current] != nullptr)
		{
			// Add our current node to the route
			route.push(current);

			// Set our current node to the previous node
			current = from[current];
		}

		// Return our final route
		return route;
	}

	// •  Identical to Heuristic Search.
	// •  Starting from the start node, returns a list of nodes representing a route to the end node using the Greedy Best First Search Algorithm.
	// •  Searches every possible node from oldest to newest but queues nodes considered closer to the goal by the heuristic function first.
	// •  Completes quicker but can be a slower route.
	// •  Will calculate the closest location to the goal if the goal is unreachable.
	template<typename data_type> static std::stack<node<data_type>*> greedy_best_first_search(node<data_type>* start, node<data_type>* end)
	{
		return heuristic_search(start, end);
	}

	// •  Starting from the start node, returns a list of nodes representing a route to the end node using Dijkstra's Search Algorithm.
	// •  Searches every possible node from oldest to newest but queues nodes with less weight first, and recalculates routes if a faster way to a node is found.
	// •  Guarantees the fastest and least resistant route but increases in time exponentially.
	// •  Will calculate the closest location to the goal if the goal is unreachable.
	template<typename data_type> static std::stack<node<data_type>*> dijkstra_search(node<data_type>* start, node<data_type>* end)
	{
		// Check if the start and end node are identical
		if (start == end)
		{
			return std::stack<node<data_type>*>();
		}

		// Initialize our frontier
		std::multimap<HEURISTIC_TYPE, node<data_type>*> frontier = std::multimap<HEURISTIC_TYPE, node<data_type>*>();

		// Enqueue our start node
		frontier.insert({ 0, start });

		// Make a map to store each node's node before it (which will eventually store the route from the end node to the start)
		// KEY = TO  VALUE = FROM
		// from[current_node] = the node immediately before current_node
		std::map<node<data_type>*, node<data_type>*> from = std::map<node<data_type>*, node<data_type>*>
		{
			// Set our start node's value to an impossible node in our route map
			{ start, nullptr }
		};

		// Make a map that corresponds to the from map's "to" nodes and store the total cost + weight to get to that node
		std::map<node<data_type>*, WEIGHT_TYPE> weights = std::map<node<data_type>*, WEIGHT_TYPE>
		{
			// Set our start node's cost to 0
			{ start, 0 }
		};

		// Store our current value and number of loops
		node<data_type>* current = end;

		int loop_count = -1;

		// Loop until our frontier is empty
		while (frontier.size() > 0)
		{
			// Loop check
			loop_count++;

			if (loop_count >= max_loops)
			{
				break;
			}

			// Pop our current node and increment our number of loops
			current = frontier.begin()->second;

			frontier.erase(frontier.begin()->first);

			// Check if we made it to our goal
			if (current == end)
			{
				break;
			}

			// Loop through our current node's connections
			for (connection<data_type> connection : current->connections)
			{
				// Check that this connection is a valid connection and a valid node
				if (!connection.active || !connection.to->active)
				{
					continue;
				}

				// Store the new total cost of traveling this node
				float new_cost = weights[current] + connection.weight + connection.to.weight;

				// Check that our connected node is not currently in our dictionary
				if (!from.count(connection.to) || new_cost < weights[connection.to])
				{
					// Update the total weight of this connected node
					weights[connection.to] = new_cost;

					// Enqueue our connected node to the frontier
					frontier.push(connection.to, new_cost);

					// Add our connected node as our key and our current node as our value to the dictionary
					from[connection.to] = current;
				}
			}
		}

		// Clear the frontier
		frontier = std::multimap<HEURISTIC_TYPE, node<data_type>*>();

		// Check that we made it to our end node
		if (current != end)
		{
			// Store our new goal
			current = start;

			// Store our current heuristic
			HEURISTIC_TYPE current_heuristic = INT_MAX;

			// Calculate the closest node to our goal
			for (auto to : from)
			{
				// Calculate the new heuristic
				HEURISTIC_TYPE new_heuristic = calculate_heuristic(to.second, end);

				// Check if the new heuristic is closer to the goal
				if (new_heuristic < current_heuristic)
				{
					// Mark the new goal
					current = to.second;

					// Update the heuristic
					current_heuristic = new_heuristic;
				}
			}
		}

		// Store our route
		std::stack<node<data_type>*> route = std::stack<node<data_type>*>();

		// Build our final route through our map's connections
		while (from[current] != nullptr)
		{
			// Add our current node to the route
			route.push(current);

			// Set our current node to the previous node
			current = from[current];
		}

		// Return our final route
		return route;
	}

	// •  Identical to Dijkstra Search.
	// •  Starting from the start node, returns a list of nodes representing a route to the end node using Uniform Cost Search Algorithm.
	// •  Searches every possible node from oldest to newest but queues nodes with less weight first, and recalculates routes if a faster way to a node is found.
	// •  Guarantees the fastest and least resistant route but increases in time exponentially.
	// •  Will calculate the closest location to the goal if the goal is unreachable.
	template<typename data_type> static std::stack<node<data_type>*> uniform_cost_search(node<data_type>* start, node<data_type>* end)
	{
		return dijkstra_search(start, end);
	}

	// •  Starting from the start node, returns a list of nodes representing a route to the end node using the A Star Search Algorithm.
	// •  Searches every possible node from oldest to newest but queues nodes with less weight first + the heuristic, and recalculates routes if a faster way to a node is found.
	// •  Guarantees the fastest and possibly least resistant route in shorter time.
	// •  Will calculate the closest location to the goal if the goal is unreachable.
	template<typename data_type> static std::stack<node<data_type>*> a_star_search(node<data_type>* start, node<data_type>* end, HEURISTIC_TYPE heuristic_scale = 1)
	{
		// Check if the start and end node are identical
		if (start == end)
		{
			return std::stack<node<data_type>*>();
		}

		// Initialize our frontier
		std::multimap<HEURISTIC_TYPE, node<data_type>*> frontier = std::multimap<HEURISTIC_TYPE, node<data_type>*>();

		// Enqueue our start node
		frontier.insert({ 0, start });

		// Make a map to store each node's node before it (which will eventually store the route from the end node to the start)
		// KEY = TO  VALUE = FROM
		// from[current_node] = the node immediately before current_node
		std::map<node<data_type>*, node<data_type>*> from = std::map<node<data_type>*, node<data_type>*>
		{
			// Set our start node's value to an impossible node in our route map
			{ start, nullptr }
		};

		// Make a map that corresponds to the from map's "to" nodes and store the total cost + weight to get to that node
		std::map<node<data_type>*, WEIGHT_TYPE> weights = std::map<node<data_type>*, WEIGHT_TYPE>
		{
			// Set our start node's cost to 0
			{ start, 0 }
		};

		// Store our current value and number of loops
		node<data_type>* current = end;

		int loop_count = -1;

		// Loop until our frontier is empty
		while (frontier.size() > 0)
		{
			// Loop check
			loop_count++;

			if (loop_count >= max_loops)
			{
				break;
			}

			// Pop our current node and increment our number of loops
			current = frontier.begin()->second;

			frontier.erase(frontier.begin()->first);

			// Check if we made it to our goal
			if (current == end)
			{
				break;
			}

			// Loop through our current node's connections
			for (connection<data_type> connection : current->connections)
			{
				// Check that this connection is a valid connection and a valid node
				if (!connection.active || !connection.to->active)
				{
					continue;
				}

				// Store the new total cost of traveling this node
				float new_cost = weights[current] + connection.weight + connection.to.weight;

				// Check that our connected node is not currently in our dictionary
				if (!from.count(connection.to) || new_cost < weights[connection.to])
				{
					// Update the total weight of this connected node
					weights[connection.to] = new_cost;

					// Enqueue our connected node to the frontier based on the heuristic function
					frontier.push(connection.to, new_cost + (calculate_heuristic(connection.to, end) * heuristic_scale * 2));

					// Add our connected node as our key and our current node as our value to the dictionary
					from[connection.to] = current;
				}
			}
		}

		// Clear the frontier
		frontier = std::multimap<HEURISTIC_TYPE, node<data_type>*>();

		// Check that we made it to our end node
		if (current != end)
		{
			// Store our new goal
			current = start;

			// Store our current heuristic
			HEURISTIC_TYPE current_heuristic = INT_MAX;

			// Calculate the closest node to our goal
			for (auto to : from)
			{
				// Calculate the new heuristic
				HEURISTIC_TYPE new_heuristic = calculate_heuristic(to.second, end);

				// Check if the new heuristic is closer to the goal
				if (new_heuristic < current_heuristic)
				{
					// Mark the new goal
					current = to.second;

					// Update the heuristic
					current_heuristic = new_heuristic;
				}
			}
		}

		// Store our route
		std::stack<node<data_type>*> route = std::stack<node<data_type>*>();

		// Build our final route through our map's connections
		while (from[current] != nullptr)
		{
			// Add our current node to the route
			route.push(current);

			// Set our current node to the previous node
			current = from[current];
		}

		// Return our final route
		return route;
	}
};

// The maximum number of loops before a pathfinding algorithm terminates.
int pathfinding::max_loops = 300;
