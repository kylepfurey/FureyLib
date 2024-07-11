
// Static Grid Pathfinding Functions Script
// by Kyle Furey

// REFERENCE: https://www.redblobgames.com/pathfinding/a-star/introduction.html

#pragma once
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <functional>
#include <algorithm>
#include <cmath>
#include <climits>

// Include this heading to use the library
#include "pathfinding_grid.h";

// Define the heuristic value type.
#define HEURISTIC_TYPE float

// Define the weighted space type.
#define WEIGHT_TYPE float

// A single space in a grid.
struct grid_space
{
public:

	// X Cartesian coordinate.
	int x;

	// Y Cartesian coordinate.
	int y;

	// Default constructor.
	grid_space(int x = 0, int y = 0)
	{
		this->x = x;

		this->y = y;
	}

	// Checks if the given grid spaces are equal.
	bool operator ==(const grid_space& compared) const noexcept
	{
		return x == compared.x && y == compared.y;
	}

	// Checks if the given grid spaces are not equal.
	bool operator !=(const grid_space& compared) const noexcept
	{
		return x != compared.x || y != compared.y;
	}

	// Compares two grid spaces.
	bool operator <(const grid_space& compared) const noexcept
	{
		if (x < compared.x)
		{
			return true;
		}

		if (x > compared.x)
		{
			return false;
		}

		return y < compared.y;
	}

	// Adds two grid spaces together.
	grid_space operator +(grid_space added)
	{
		return grid_space(x + added.x, y + added.y);
	}

	// Subtracts two grid spaces together.
	grid_space operator -(grid_space subtracted)
	{
		return grid_space(x - subtracted.x, y - subtracted.y);
	}

	// Returns a string representation of the grid space.
	std::string to_string()
	{
		return "{ " + std::to_string(x) + ", " + std::to_string(y) + " }";
	}
};

// Settings that define a graph in grid space.
struct grid_graph
{
public:

	// Whether this graph enables moving adjacent.
	bool adjacent_navigation;

	// Whether this graph enables moving diagonally.
	bool diagonal_navigation;

	// Whether this graph ignores occupied spaces.
	bool ignore_occupied;

	// The current occupied spaces of this graph.
	std::set<grid_space> occupied;

	// Whether to assume all spaces are occupied except the ones in the occupied set.
	bool invert_occupied;

	// Whether this graph ignores weighted spaces.
	bool ignore_weights;

	// The weighted spaces of this graph and their corresponding weights (must be positive or zero).
	std::map<grid_space, WEIGHT_TYPE> weights;

	// The default weight value of this graph (must be positive or zero).
	WEIGHT_TYPE default_weight;

	// Default constructor.
	grid_graph()
	{
		this->adjacent_navigation = true;

		this->diagonal_navigation = true;

		this->ignore_occupied = true;

		this->occupied = std::set<grid_space>();

		this->invert_occupied = false;

		this->ignore_weights = true;

		this->weights = std::map<grid_space, WEIGHT_TYPE>();

		this->default_weight = 1;
	}

	// Graph constructor.
	grid_graph(bool adjacent_navigation, bool diagonal_navigation = true, bool ignore_occupied = false, std::set<grid_space> occupied = std::set<grid_space>(), bool invert_occupied = false, bool ignore_weights = false, std::map<grid_space, WEIGHT_TYPE> weights = std::map<grid_space, WEIGHT_TYPE>(), WEIGHT_TYPE default_weight = 1)
	{
		this->adjacent_navigation = adjacent_navigation;

		this->diagonal_navigation = diagonal_navigation;

		this->ignore_occupied = ignore_occupied;

		this->occupied = occupied;

		this->invert_occupied = invert_occupied;

		this->ignore_weights = ignore_weights;

		this->weights = weights;

		this->default_weight = default_weight;
	}
};

// A collection of pathfinding algorithms for navigating connected grid spaces.
class pathfinding_grid
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
	// •  Heuristic Value = Euclidean Distance or Manhattan Distance
	static HEURISTIC_TYPE calculate_heuristic(grid_space current, grid_space end, bool manhattan = false)
	{
		if (!manhattan)
		{
			HEURISTIC_TYPE xDistance = end.x - current.x;

			HEURISTIC_TYPE yDistance = end.y - current.y;

			HEURISTIC_TYPE heuristic = xDistance * xDistance + yDistance * yDistance;

			return (HEURISTIC_TYPE)std::sqrt(heuristic);
		}
		else
		{
			HEURISTIC_TYPE xDistance = end.x - current.x;

			HEURISTIC_TYPE yDistance = end.y - current.y;

			HEURISTIC_TYPE heuristic = std::abs(xDistance) + std::abs(yDistance);

			return (HEURISTIC_TYPE)heuristic;
		}
	}

	// •  Starting from the start node, returns a list of nodes representing a route to the end node using the given pathfinding algorithm.
	// •  Searches every possible node starting from oldest to newest.
	// •  Time complexity and precision depend on the selected pathfinding algorithm.
	// •  Will calculate the closest location to the goal if the goal is unreachable.
	static std::stack<grid_space> pathfind(algorithm algorithm, grid_space start, grid_space end, grid_graph graph_settings, HEURISTIC_TYPE heuristic_scale = 1)
	{
		switch (algorithm)
		{
		case algorithm::a_star:

			return a_star_search(start, end, graph_settings, heuristic_scale);

		case algorithm::dijkstra:

			return dijkstra_search(start, end, graph_settings);

		case algorithm::heuristic:

			return heuristic_search(start, end, graph_settings);

		case algorithm::breadth_first:

			return breadth_first_search(start, end, graph_settings);

		case algorithm::depth_first:

			return depth_first_search(start, end, graph_settings);
		}

		return std::stack<grid_space>();
	}


	// ALGORITHMS

	// •  Starting from the start node, returns a list of nodes representing a route to the end node using the Depth First Search Algorithm.
	// •  Searches every possible node starting from newest to oldest.
	// •  Guarantees the fastest route but only checks the newest node first. This is best used for search trees.
	// •  Will calculate the closest location to the goal if the goal is unreachable.
	static std::stack<grid_space> depth_first_search(grid_space start, grid_space end, grid_graph graph_settings)
	{
		// Check that we can actually move
		if (!graph_settings.adjacent_navigation && !graph_settings.diagonal_navigation)
		{
			return std::stack<grid_space>();
		}

		// Check if the start and end node are identical
		if (start == end)
		{
			return std::stack<grid_space>();
		}

		// Initialize our frontier
		std::stack<grid_space> frontier = std::stack<grid_space>();

		// Enqueue our start node
		frontier.push(start);

		// Make a map to store each node's node before it (which will eventually store the route from the end node to the start)
		// KEY = TO  VALUE = FROM
		// from[currentgrid_space] = the node immediately before currentgrid_space
		std::map<grid_space, grid_space> from = std::map<grid_space, grid_space>
		{
			// Set our start node's value to an impossible node in our route map
			{ start, grid_space(INT_MAX, INT_MAX) }
		};

		// Store our current value and number of loops
		grid_space current = end;

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

			// Store the current connection
			grid_space connection;

			// Loop through adjacent connections
			if (graph_settings.adjacent_navigation)
			{
				// Check right
				connection = current + grid_space(1, 0);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check left
				connection = current + grid_space(-1, 0);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check up
				connection = current + grid_space(0, 1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down
				connection = current + grid_space(0, -1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}
			}

			// Loop through diagonal connections
			if (graph_settings.diagonal_navigation)
			{
				// Check up right
				connection = current + grid_space(1, 1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check up left
				connection = current + grid_space(-1, 1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down right
				connection = current + grid_space(1, -1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down left
				connection = current + grid_space(-1, -1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}
			}
		}

		// Clear the frontier
		frontier = std::stack<grid_space>();

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
		std::stack<grid_space> route = std::stack<grid_space>();

		// Build our final route through our map's connections
		while (from[current] != grid_space(INT_MAX, INT_MAX))
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
	static std::stack<grid_space> breadth_first_search(grid_space start, grid_space end, grid_graph graph_settings)
	{
		// Check that we can actually move
		if (!graph_settings.adjacent_navigation && !graph_settings.diagonal_navigation)
		{
			return std::stack<grid_space>();
		}

		// Check if the start and end node are identical
		if (start == end)
		{
			return std::stack<grid_space>();
		}

		// Initialize our frontier
		std::queue<grid_space> frontier = std::queue<grid_space>();

		// Enqueue our start node
		frontier.push(start);

		// Make a map to store each node's node before it (which will eventually store the route from the end node to the start)
		// KEY = TO  VALUE = FROM
		// from[currentgrid_space] = the node immediately before currentgrid_space
		std::map<grid_space, grid_space> from = std::map<grid_space, grid_space>
		{
			// Set our start node's value to an impossible node in our route map
			{ start, grid_space(INT_MAX, INT_MAX) }
		};

		// Store our current value and number of loops
		grid_space current = end;

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

			// Store the current connection
			grid_space connection;

			// Loop through adjacent connections
			if (graph_settings.adjacent_navigation)
			{
				// Check right
				connection = current + grid_space(1, 0);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check left
				connection = current + grid_space(-1, 0);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check up
				connection = current + grid_space(0, 1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down
				connection = current + grid_space(0, -1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}
			}

			// Loop through diagonal connections
			if (graph_settings.diagonal_navigation)
			{
				// Check up right
				connection = current + grid_space(1, 1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check up left
				connection = current + grid_space(-1, 1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down right
				connection = current + grid_space(1, -1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down left
				connection = current + grid_space(-1, -1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.push(connection);

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}
			}
		}

		// Clear the frontier
		frontier = std::queue<grid_space>();

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
		std::stack<grid_space> route = std::stack<grid_space>();

		// Build our final route through our map's connections
		while (from[current] != grid_space(INT_MAX, INT_MAX))
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
	static std::stack<grid_space> heuristic_search(grid_space start, grid_space end, grid_graph graph_settings)
	{
		// Check that we can actually move
		if (!graph_settings.adjacent_navigation && !graph_settings.diagonal_navigation)
		{
			return std::stack<grid_space>();
		}

		// Check if the start and end node are identical
		if (start == end)
		{
			return std::stack<grid_space>();
		}

		// Initialize our frontier
		std::multimap<HEURISTIC_TYPE, grid_space> frontier = std::multimap<HEURISTIC_TYPE, grid_space>();

		// Enqueue our start node
		frontier.insert({ 0, start });

		// Make a map to store each node's node before it (which will eventually store the route from the end node to the start)
		// KEY = TO  VALUE = FROM
		// from[current_grid_space] = the node immediately before current_grid_space
		std::map<grid_space, grid_space> from = std::map<grid_space, grid_space>
		{
			// Set our start node's value to an impossible node in our route map
			{ start, grid_space(INT_MAX, INT_MAX) }
		};

		// Store our current value and number of loops
		grid_space current = end;

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

			// Store the current connection
			grid_space connection;

			// Loop through adjacent connections
			if (graph_settings.adjacent_navigation)
			{
				// Check right
				connection = current + grid_space(1, 0);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.insert({ calculate_heuristic(connection, end), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check left
				connection = current + grid_space(-1, 0);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.insert({ calculate_heuristic(connection, end), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check up
				connection = current + grid_space(0, 1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.insert({ calculate_heuristic(connection, end), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down
				connection = current + grid_space(0, -1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.insert({ calculate_heuristic(connection, end), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}
			}

			// Loop through diagonal connections
			if (graph_settings.diagonal_navigation)
			{
				// Check up right
				connection = current + grid_space(1, 1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.insert({ calculate_heuristic(connection, end), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check up left
				connection = current + grid_space(-1, 1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.insert({ calculate_heuristic(connection, end), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down right
				connection = current + grid_space(1, -1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.insert({ calculate_heuristic(connection, end), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down left
				connection = current + grid_space(-1, -1);

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection))
					{
						// Enqueue our connected node to the frontier
						frontier.insert({ calculate_heuristic(connection, end), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}
			}
		}

		// Clear the frontier
		frontier = std::multimap<HEURISTIC_TYPE, grid_space>();

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
		std::stack<grid_space> route = std::stack<grid_space>();

		// Build our final route through our map's connections
		while (from[current] != grid_space(INT_MAX, INT_MAX))
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
	static std::stack<grid_space> greedy_best_first_search(grid_space start, grid_space end, grid_graph graph_settings)
	{
		return heuristic_search(start, end, graph_settings);
	}

	// •  Starting from the start node, returns a list of nodes representing a route to the end node using Dijkstra's Search Algorithm.
	// •  Searches every possible node from oldest to newest but queues nodes with less weight first, and recalculates routes if a faster way to a node is found.
	// •  Guarantees the fastest and least resistant route but increases in time exponentially.
	// •  Will calculate the closest location to the goal if the goal is unreachable.
	static std::stack<grid_space> dijkstra_search(grid_space start, grid_space end, grid_graph graph_settings)
	{
		// Check that we can actually move
		if (!graph_settings.adjacent_navigation && !graph_settings.diagonal_navigation)
		{
			return std::stack<grid_space>();
		}

		// Check if the start and end node are identical
		if (start == end)
		{
			return std::stack<grid_space>();
		}

		// Initialize our frontier
		std::multimap<HEURISTIC_TYPE, grid_space> frontier = std::multimap<HEURISTIC_TYPE, grid_space>();

		// Enqueue our start node
		frontier.insert({ 0, start });

		// Make a map to store each node's node before it (which will eventually store the route from the end node to the start)
		// KEY = TO  VALUE = FROM
		// from[currentgrid_space] = the node immediately before currentgrid_space
		std::map<grid_space, grid_space> from = std::map<grid_space, grid_space>
		{
			// Set our start node's value to an impossible node in our route map
			{ start, grid_space(INT_MAX, INT_MAX) }
		};

		// Make a map that corresponds to the from map's "to" nodes and store the total cost + weight to get to that node
		std::map<grid_space, WEIGHT_TYPE> weights = std::map<grid_space, WEIGHT_TYPE>
		{
			// Set our start node's cost to 0
			{ start, 0 }
		};

		// Store our current value and number of loops
		grid_space current = end;

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

			// Store the current connection
			grid_space connection;

			// Store the total cost
			WEIGHT_TYPE new_cost;

			// Loop through adjacent connections
			if (graph_settings.adjacent_navigation)
			{
				// Check right
				connection = current + grid_space(1, 0);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost, connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check left
				connection = current + grid_space(-1, 0);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost, connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check up
				connection = current + grid_space(0, 1);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost, connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down
				connection = current + grid_space(0, -1);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost, connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}
			}

			// Loop through diagonal connections
			if (graph_settings.diagonal_navigation)
			{
				// Check up right
				connection = current + grid_space(1, 1);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost, connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check up left
				connection = current + grid_space(-1, 1);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost, connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down right
				connection = current + grid_space(1, -1);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost, connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down left
				connection = current + grid_space(-1, -1);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost, connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}
			}
		}

		// Clear the frontier
		frontier = std::multimap<HEURISTIC_TYPE, grid_space>();

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
		std::stack<grid_space> route = std::stack<grid_space>();

		// Build our final route through our map's connections
		while (from[current] != grid_space(INT_MAX, INT_MAX))
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
	static std::stack<grid_space> uniform_cost_search(grid_space start, grid_space end, grid_graph graph_settings)
	{
		return dijkstra_search(start, end, graph_settings);
	}

	// •  Starting from the start node, returns a list of nodes representing a route to the end node using the A Star Search Algorithm.
	// •  Searches every possible node from oldest to newest but queues nodes with less weight first + the heuristic, and recalculates routes if a faster way to a node is found.
	// •  Guarantees the fastest and possibly least resistant route in shorter time.
	// •  Will calculate the closest location to the goal if the goal is unreachable.
	static std::stack<grid_space> a_star_search(grid_space start, grid_space end, grid_graph graph_settings, HEURISTIC_TYPE heuristic_scale = 1)
	{
		// Check that we can actually move
		if (!graph_settings.adjacent_navigation && !graph_settings.diagonal_navigation)
		{
			return std::stack<grid_space>();
		}

		// Check if the start and end node are identical
		if (start == end)
		{
			return std::stack<grid_space>();
		}

		// Initialize our frontier
		std::multimap<HEURISTIC_TYPE, grid_space> frontier = std::multimap<HEURISTIC_TYPE, grid_space>();

		// Enqueue our start node
		frontier.insert({ 0, start });

		// Make a map to store each node's node before it (which will eventually store the route from the end node to the start)
		// KEY = TO  VALUE = FROM
		// from[currentgrid_space] = the node immediately before currentgrid_space
		std::map<grid_space, grid_space> from = std::map<grid_space, grid_space>
		{
			// Set our start node's value to an impossible node in our route map
			{ start, grid_space(INT_MAX, INT_MAX) }
		};

		// Make a map that corresponds to the from map's "to" nodes and store the total cost + weight to get to that node
		std::map<grid_space, WEIGHT_TYPE> weights = std::map<grid_space, WEIGHT_TYPE>
		{
			// Set our start node's cost to 0
			{ start, 0 }
		};

		// Store our current value and number of loops
		grid_space current = end;

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

			// Store the current connection
			grid_space connection;

			// Store the total cost
			WEIGHT_TYPE new_cost;

			// Loop through adjacent connections
			if (graph_settings.adjacent_navigation)
			{
				// Check right
				connection = current + grid_space(1, 0);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost + (calculate_heuristic(connection, end) * heuristic_scale), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check left
				connection = current + grid_space(-1, 0);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost + (calculate_heuristic(connection, end) * heuristic_scale), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check up
				connection = current + grid_space(0, 1);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost + (calculate_heuristic(connection, end) * heuristic_scale), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down
				connection = current + grid_space(0, -1);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost + (calculate_heuristic(connection, end) * heuristic_scale), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}
			}

			// Loop through diagonal connections
			if (graph_settings.diagonal_navigation)
			{
				// Check up right
				connection = current + grid_space(1, 1);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost + (calculate_heuristic(connection, end) * heuristic_scale), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check up left
				connection = current + grid_space(-1, 1);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost + (calculate_heuristic(connection, end) * heuristic_scale), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down right
				connection = current + grid_space(1, -1);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost + (calculate_heuristic(connection, end) * heuristic_scale), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}

				// Check down left
				connection = current + grid_space(-1, -1);

				// Store the total cost of traveling this node
				if (graph_settings.ignore_weights || !graph_settings.weights.count(connection))
				{
					new_cost = weights[current] + graph_settings.default_weight;
				}
				else
				{
					new_cost = weights[current] + graph_settings.weights[connection];
				}

				if (graph_settings.ignore_occupied || (graph_settings.invert_occupied ? graph_settings.occupied.count(connection) : !graph_settings.occupied.count(connection)))
				{
					// Check that our connected node is not currently in our map
					if (!from.count(connection) || new_cost < weights[connection])
					{
						// Update the total weight of this connected node
						weights[connection] = new_cost;

						// Enqueue our connected node to the frontier
						frontier.insert({ new_cost + (calculate_heuristic(connection, end) * heuristic_scale), connection });

						// Add our connected node as our key and our current node as our value to the map
						from[connection] = current;
					}
				}
			}
		}

		// Clear the frontier
		frontier = std::multimap<HEURISTIC_TYPE, grid_space>();

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
		std::stack<grid_space> route = std::stack<grid_space>();

		// Build our final route through our map's connections
		while (from[current] != grid_space(INT_MAX, INT_MAX))
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
int pathfinding_grid::max_loops = 300;
