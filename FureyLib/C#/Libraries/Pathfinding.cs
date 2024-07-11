
// Static Node Pathfinding Functions Script
// by Kyle Furey

// REFERENCE: https://www.redblobgames.com/pathfinding/a-star/introduction.html

// REQUIREMENT: Graph.cs

using System;
using System.Collections.Generic;

// Include this heading to use the library
using static Pathfinding;

// Define the heuristic value type.
using HeuristicType = System.Single;

// Define the weighted space type (must be the same as the node's weight type).
using WeightType = System.Single;

/// <summary>
/// A collection of pathfinding algorithms for navigating a graph of connected nodes.
/// </summary>
public static class Pathfinding
{
    // PATHFINDING

    /// <summary>
    /// Pathfinding algorithms.
    /// </summary>
    public enum Algorithm
    {
        /// <summary>
        /// A Star Search
        /// </summary>
        AStar,

        /// <summary>
        /// Dijkstra Search
        /// </summary>
        Dijkstra,

        /// <summary>
        /// Uniform Cost Search (Dijkstra)
        /// </summary>
        UniformCost = Dijkstra,

        /// <summary>
        /// Heuristic Search
        /// </summary>
        Heuristic,

        /// <summary>
        /// Greedy Best First Search (Heuristic)
        /// </summary>
        GreedyBestFirst = Heuristic,

        /// <summary>
        /// Breadth First Search
        /// </summary>
        BreadthFirst,

        /// <summary>
        /// Depth First Search
        /// </summary>
        DepthFirst
    }

    /// <summary>
    /// The maximum number of loops before a pathfinding algorithm terminates.
    /// </summary>
    public static int maxLoops = 300;

    /// <summary>
    /// •  Calculates an arbitrary value that represents how close a node is to the goal.<br/>
    /// •  It is recommended to use Euclidean or Manhattan distance as your Heuristic.<br/>
    /// •  This function must be defined in order to use the pathfinding functions.
    /// </summary>
    public static extern HeuristicType CalculateHeuristic<DataType>(Node<DataType> current, Node<DataType> end);

    /// <summary>
    /// •  Starting from the start node, returns a list of nodes representing a route to the end node using the given pathfinding algorithm.<br/>
    /// •  Searches every possible node starting from oldest to newest.<br/>
    /// •  Time complexity and precision depend on the selected pathfinding algorithm.<br/>
    /// •  Will calculate the closest location to the goal if the goal is unreachable.
    /// </summary>
    public static Stack<Node<DataType>> Pathfind<DataType>(Algorithm algorithm, Node<DataType> start, Node<DataType> end, HeuristicType heuristicScale = 1)
    {
        switch (algorithm)
        {
            case Algorithm.AStar:

                return AStarSearch(start, end, heuristicScale);

            case Algorithm.Dijkstra:

                return DijkstraSearch(start, end);

            case Algorithm.Heuristic:

                return HeuristicSearch(start, end);

            case Algorithm.BreadthFirst:

                return BreadthFirstSearch(start, end);

            case Algorithm.DepthFirst:

                return DepthFirstSearch(start, end);
        }

        return null;
    }


    // ALGORITHMS

    /// <summary>
    /// •  Starting from the start node, returns a list of nodes representing a route to the end node using the Depth First Search Algorithm.<br/>
    /// •  Searches every possible node starting from newest to oldest.<br/>
    /// •  Guarantees the fastest route but only checks in one direction. This is best used for search trees.<br/>
    /// •  Will calculate the closest location to the goal if the goal is unreachable.
    /// </summary>
    public static Stack<Node<DataType>> DepthFirstSearch<DataType>(Node<DataType> start, Node<DataType> end)
    {
        // Check if the start and end node are identical
        if (start == end)
        {
            return new Stack<Node<DataType>>();
        }

        // Initialize our frontier
        Stack<Node<DataType>> frontier = new Stack<Node<DataType>>();

        // Enqueue our start node
        frontier.Push(start);

        // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
        // KEY = TO  VALUE = FROM
        // from[currentNode] = the node immediately before currentNode
        Dictionary<Node<DataType>, Node<DataType>> from = new Dictionary<Node<DataType>, Node<DataType>>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, null }
        };

        // Store our current value and number of loops
        Node<DataType> current = end;

        int loopCount = -1;

        // Loop until our frontier is empty
        while (frontier.Count > 0)
        {
            // Loop check
            loopCount++;

            if (loopCount >= maxLoops)
            {
                break;
            }

            // Dequeue our current node and increment our number of loops
            current = frontier.Pop();

            // Check if we made it to our goal
            if (current == end)
            {
                break;
            }

            // Loop through our current node's connections
            foreach (Connection<DataType> connection in current.connections)
            {
                // Check that this connection is a valid connection and a valid node
                if (!connection.active || !connection.to.active)
                {
                    continue;
                }

                // Check that our connected node is not currently in our dictionary
                if (!from.ContainsKey(connection.to))
                {
                    // Enqueue our connected node to the frontier
                    frontier.Push(connection.to);

                    // Add our connected node as our key and our current node as our value to the dictionary
                    from[connection.to] = current;
                }
            }
        }

        // Clear the frontier
        frontier.Clear();

        // Check that we made it to our end node
        if (current != end)
        {
            // Store our new goal
            current = start;

            // Store our current heuristic
            HeuristicType currentHeuristic = HeuristicType.MaxValue;

            // Calculate the closest node to our goal
            foreach (Node<DataType> to in from.Values)
            {
                // Calculate the new heuristic
                HeuristicType newHeuristic = CalculateHeuristic(to, end);

                // Check if the new heuristic is closer to the goal
                if (newHeuristic < currentHeuristic)
                {
                    // Mark the new goal
                    current = to;

                    // Update the heuristic
                    currentHeuristic = newHeuristic;
                }
            }
        }

        // Store our route
        Stack<Node<DataType>> route = new Stack<Node<DataType>>();

        // Build our final route through our dictionary's connections
        while (from[current] != null)
        {
            // Add our current node to the route
            route.Push(current);

            // Set our current node to the previous node
            current = from[current];
        }

        // Return our final route
        return route;
    }

    /// <summary>
    /// •  Starting from the start node, returns a list of nodes representing a route to the end node using the Breadth First Search Algorithm.<br/>
    /// •  Searches every possible node starting from oldest to newest.<br/>
    /// •  Guarantees the fastest route but increases in time exponentially.<br/>
    /// •  Will calculate the closest location to the goal if the goal is unreachable.
    /// </summary>
    public static Stack<Node<DataType>> BreadthFirstSearch<DataType>(Node<DataType> start, Node<DataType> end)
    {
        // Check if the start and end node are identical
        if (start == end)
        {
            return new Stack<Node<DataType>>();
        }

        // Initialize our frontier
        Queue<Node<DataType>> frontier = new Queue<Node<DataType>>();

        // Enqueue our start node
        frontier.Enqueue(start);

        // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
        // KEY = TO  VALUE = FROM
        // from[currentNode] = the node immediately before currentNode
        Dictionary<Node<DataType>, Node<DataType>> from = new Dictionary<Node<DataType>, Node<DataType>>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, null }
        };

        // Store our current value and number of loops
        Node<DataType> current = end;

        int loopCount = -1;

        // Loop until our frontier is empty
        while (frontier.Count > 0)
        {
            // Loop check
            loopCount++;

            if (loopCount >= maxLoops)
            {
                break;
            }

            // Dequeue our current node and increment our number of loops
            current = frontier.Dequeue();

            // Check if we made it to our goal
            if (current == end)
            {
                break;
            }

            // Loop through our current node's connections
            foreach (Connection<DataType> connection in current.connections)
            {
                // Check that this connection is a valid connection and a valid node
                if (!connection.active || !connection.to.active)
                {
                    continue;
                }

                // Check that our connected node is not currently in our dictionary
                if (!from.ContainsKey(connection.to))
                {
                    // Enqueue our connected node to the frontier
                    frontier.Enqueue(connection.to);

                    // Add our connected node as our key and our current node as our value to the dictionary
                    from[connection.to] = current;
                }
            }
        }

        // Clear the frontier
        frontier.Clear();

        // Check that we made it to our end node
        if (current != end)
        {
            // Store our new goal
            current = start;

            // Store our current heuristic
            HeuristicType currentHeuristic = HeuristicType.MaxValue;

            // Calculate the closest node to our goal
            foreach (Node<DataType> to in from.Values)
            {
                // Calculate the new heuristic
                HeuristicType newHeuristic = CalculateHeuristic(to, end);

                // Check if the new heuristic is closer to the goal
                if (newHeuristic < currentHeuristic)
                {
                    // Mark the new goal
                    current = to;

                    // Update the heuristic
                    currentHeuristic = newHeuristic;
                }
            }
        }

        // Store our route
        Stack<Node<DataType>> route = new Stack<Node<DataType>>();

        // Build our final route through our dictionary's connections
        while (from[current] != null)
        {
            // Add our current node to the route
            route.Push(current);

            // Set our current node to the previous node
            current = from[current];
        }

        // Return our final route
        return route;
    }

    /// <summary>
    /// •  Starting from the start node, returns a list of nodes representing a route to the end node using the Heuristic Search Algorithm.<br/>
    /// •  Searches every possible node from oldest to newest but queues nodes considered closer to the goal by the heuristic function first.<br/>
    /// •  Completes quicker but can be a slower route.<br/>
    /// •  Will calculate the closest location to the goal if the goal is unreachable.
    /// </summary>
    public static Stack<Node<DataType>> HeuristicSearch<DataType>(Node<DataType> start, Node<DataType> end)
    {
        // Check if the start and end node are identical
        if (start == end)
        {
            return new Stack<Node<DataType>>();
        }

        // Initialize our frontier
        PriorityQueue<Node<DataType>, HeuristicType> frontier = new PriorityQueue<Node<DataType>, HeuristicType>();

        // Enqueue our start node
        frontier.Enqueue(start, 0);

        // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
        // KEY = TO  VALUE = FROM
        // from[currentNode] = the node immediately before currentNode
        Dictionary<Node<DataType>, Node<DataType>> from = new Dictionary<Node<DataType>, Node<DataType>>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, null }
        };

        // Store our current value and number of loops
        Node<DataType> current = end;

        int loopCount = -1;

        // Loop until our frontier is empty
        while (frontier.Count > 0)
        {
            // Loop check
            loopCount++;

            if (loopCount >= maxLoops)
            {
                break;
            }

            // Dequeue our current node and increment our number of loops
            current = frontier.Dequeue();

            // Check if we made it to our goal
            if (current == end)
            {
                break;
            }

            // Loop through our current node's connections
            foreach (Connection<DataType> connection in current.connections)
            {
                // Check that this connection is a valid connection and a valid node
                if (!connection.active || !connection.to.active)
                {
                    continue;
                }

                // Check that our connected node is not currently in our dictionary
                if (!from.ContainsKey(connection.to))
                {
                    // Enqueue our connected node to the frontier based on the heuristic function
                    frontier.Enqueue(connection.to, CalculateHeuristic(connection.to, end));

                    // Add our connected node as our key and our current node as our value to the dictionary
                    from[connection.to] = current;
                }
            }
        }

        // Clear the frontier
        frontier.Clear();

        // Check that we made it to our end node
        if (current != end)
        {
            // Store our new goal
            current = start;

            // Store our current heuristic
            HeuristicType currentHeuristic = HeuristicType.MaxValue;

            // Calculate the closest node to our goal
            foreach (Node<DataType> to in from.Values)
            {
                // Calculate the new heuristic
                HeuristicType newHeuristic = CalculateHeuristic(to, end);

                // Check if the new heuristic is closer to the goal
                if (newHeuristic < currentHeuristic)
                {
                    // Mark the new goal
                    current = to;

                    // Update the heuristic
                    currentHeuristic = newHeuristic;
                }
            }
        }

        // Store our route
        Stack<Node<DataType>> route = new Stack<Node<DataType>>();

        // Build our final route through our dictionary's connections
        while (from[current] != null)
        {
            // Add our current node to the route
            route.Push(current);

            // Set our current node to the previous node
            current = from[current];
        }

        // Return our final route
        return route;
    }

    /// <summary>
    /// •  Identical to Heuristic Search.<br/>
    /// •  Starting from the start node, returns a list of nodes representing a route to the end node using the Greedy Best First Search Algorithm.<br/>
    /// •  Searches every possible node from oldest to newest but queues nodes considered closer to the goal by the heuristic function first.<br/>
    /// •  Completes quicker but can be a slower route.<br/>
    /// •  Will calculate the closest location to the goal if the goal is unreachable.
    /// </summary>
    public static Stack<Node<DataType>> GreedyBestFirstSearch<DataType>(Node<DataType> start, Node<DataType> end)
    {
        return HeuristicSearch(start, end);
    }

    /// <summary>
    /// •  Starting from the start node, returns a list of nodes representing a route to the end node using Dijkstra's Search Algorithm.<br/>
    /// •  Searches every possible node from oldest to newest but queues nodes with less weight first, and recalculates routes if a faster way to a node is found.<br/>
    /// •  Guarantees the fastest and least resistant route but increases in time exponentially.<br/>
    /// •  Will calculate the closest location to the goal if the goal is unreachable.
    /// </summary>
    public static Stack<Node<DataType>> DijkstraSearch<DataType>(Node<DataType> start, Node<DataType> end)
    {
        // Check if the start and end node are identical
        if (start == end)
        {
            return new Stack<Node<DataType>>();
        }

        // Initialize our frontier
        PriorityQueue<Node<DataType>, HeuristicType> frontier = new PriorityQueue<Node<DataType>, HeuristicType>();

        // Enqueue our start node
        frontier.Enqueue(start, 0);

        // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
        // KEY = TO  VALUE = FROM
        // from[currentNode] = the node immediately before currentNode
        Dictionary<Node<DataType>, Node<DataType>> from = new Dictionary<Node<DataType>, Node<DataType>>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, null }
        };

        // Make a new dictionary that corresponds to the from dictionary's "to" nodes and store the total cost + weight to get to that node
        Dictionary<Node<DataType>, WeightType> weights = new Dictionary<Node<DataType>, WeightType>
        {
            // Set our start node's cost to 0
            { start, 0 }
        };

        // Store our current value and number of loops
        Node<DataType> current = end;

        int loopCount = -1;

        // Loop until our frontier is empty
        while (frontier.Count > 0)
        {
            // Loop check
            loopCount++;

            if (loopCount >= maxLoops)
            {
                break;
            }

            // Dequeue our current node and increment our number of loops
            current = frontier.Dequeue();

            // Check if we made it to our goal
            if (current == end)
            {
                break;
            }

            // Loop through our current node's connections
            foreach (Connection<DataType> connection in current.connections)
            {
                // Check that this connection is a valid connection and a valid node
                if (!connection.active || !connection.to.active)
                {
                    continue;
                }

                // Store the new total cost of traveling this node
                float newCost = weights[current] + connection.weight + connection.to.weight;

                // Check that our connected node is not currently in our dictionary
                if (!from.ContainsKey(connection.to) || newCost < weights[connection.to])
                {
                    // Update the total weight of this connected node
                    weights[connection.to] = newCost;

                    // Enqueue our connected node to the frontier
                    frontier.Enqueue(connection.to, newCost);

                    // Add our connected node as our key and our current node as our value to the dictionary
                    from[connection.to] = current;
                }
            }
        }

        // Clear the frontier
        frontier.Clear();

        // Check that we made it to our end node
        if (current != end)
        {
            // Store our new goal
            current = start;

            // Store our current heuristic
            HeuristicType currentHeuristic = HeuristicType.MaxValue;

            // Calculate the closest node to our goal
            foreach (Node<DataType> to in from.Values)
            {
                // Calculate the new heuristic
                HeuristicType newHeuristic = CalculateHeuristic(to, end);

                // Check if the new heuristic is closer to the goal
                if (newHeuristic < currentHeuristic)
                {
                    // Mark the new goal
                    current = to;

                    // Update the heuristic
                    currentHeuristic = newHeuristic;
                }
            }
        }

        // Store our route
        Stack<Node<DataType>> route = new Stack<Node<DataType>>();

        // Build our final route through our dictionary's connections
        while (from[current] != null)
        {
            // Add our current node to the route
            route.Push(current);

            // Set our current node to the previous node
            current = from[current];
        }

        // Return our final route
        return route;
    }

    /// <summary>
    /// •  Identical to Dijkstra Search.<br/>
    /// •  Starting from the start node, returns a list of nodes representing a route to the end node using Uniform Cost Search Algorithm.<br/>
    /// •  Searches every possible node from oldest to newest but queues nodes with less weight first, and recalculates routes if a faster way to a node is found.<br/>
    /// •  Guarantees the fastest and least resistant route but increases in time exponentially.<br/>
    /// •  Will calculate the closest location to the goal if the goal is unreachable.
    /// </summary>
    public static Stack<Node<DataType>> UniformCostSearch<DataType>(Node<DataType> start, Node<DataType> end)
    {
        return DijkstraSearch(start, end);
    }

    /// <summary>
    /// •  Starting from the start node, returns a list of nodes representing a route to the end node using the A Star Search Algorithm.<br/>
    /// •  Searches every possible node from oldest to newest but queues nodes with less weight first + the heuristic, and recalculates routes if a faster way to a node is found.<br/>
    /// •  Guarantees the fastest and possibly least resistant route in shorter time.<br/>
    /// •  Will calculate the closest location to the goal if the goal is unreachable.
    /// </summary>
    public static Stack<Node<DataType>> AStarSearch<DataType>(Node<DataType> start, Node<DataType> end, HeuristicType heuristicScale = 1)
    {
        // Check if the start and end node are identical
        if (start == end)
        {
            return new Stack<Node<DataType>>();
        }

        // Initialize our frontier
        PriorityQueue<Node<DataType>, HeuristicType> frontier = new PriorityQueue<Node<DataType>, HeuristicType>();

        // Enqueue our start node
        frontier.Enqueue(start, 0);

        // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
        // KEY = TO  VALUE = FROM
        // from[currentNode] = the node immediately before currentNode
        Dictionary<Node<DataType>, Node<DataType>> from = new Dictionary<Node<DataType>, Node<DataType>>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, null }
        };

        // Make a new dictionary that corresponds to the from dictionary's "to" nodes and store the total cost + weight to get to that node
        Dictionary<Node<DataType>, WeightType> weights = new Dictionary<Node<DataType>, WeightType>
        {
            // Set our start node's cost to 0
            { start, 0 }
        };

        // Store our current value and number of loops
        Node<DataType> current = end;

        int loopCount = -1;

        // Loop until our frontier is empty
        while (frontier.Count > 0)
        {
            // Loop check
            loopCount++;

            if (loopCount >= maxLoops)
            {
                break;
            }

            // Dequeue our current node and increment our number of loops
            current = frontier.Dequeue();

            // Check if we made it to our goal
            if (current == end)
            {
                break;
            }

            // Loop through our current node's connections
            foreach (Connection<DataType> connection in current.connections)
            {
                // Check that this connection is a valid connection and a valid node
                if (!connection.active || !connection.to.active)
                {
                    continue;
                }

                // Store the new total cost of traveling this node
                float newCost = weights[current] + connection.weight + connection.to.weight;

                // Check that our connected node is not currently in our dictionary
                if (!from.ContainsKey(connection.to) || newCost < weights[connection.to])
                {
                    // Update the total weight of this connected node
                    weights[connection.to] = newCost;

                    // Enqueue our connected node to the frontier based on the heuristic function
                    frontier.Enqueue(connection.to, newCost + (CalculateHeuristic(connection.to, end) * heuristicScale));

                    // Add our connected node as our key and our current node as our value to the dictionary
                    from[connection.to] = current;
                }
            }
        }

        // Clear the frontier
        frontier.Clear();

        // Check that we made it to our end node
        if (current != end)
        {
            // Store our new goal
            current = start;

            // Store our current heuristic
            HeuristicType currentHeuristic = HeuristicType.MaxValue;

            // Calculate the closest node to our goal
            foreach (Node<DataType> to in from.Values)
            {
                // Calculate the new heuristic
                HeuristicType newHeuristic = CalculateHeuristic(to, end);

                // Check if the new heuristic is closer to the goal
                if (newHeuristic < currentHeuristic)
                {
                    // Mark the new goal
                    current = to;

                    // Update the heuristic
                    currentHeuristic = newHeuristic;
                }
            }
        }

        // Store our route
        Stack<Node<DataType>> route = new Stack<Node<DataType>>();

        // Build our final route through our dictionary's connections
        while (from[current] != null)
        {
            // Add our current node to the route
            route.Push(current);

            // Set our current node to the previous node
            current = from[current];
        }

        // Return our final route
        return route;
    }
}
