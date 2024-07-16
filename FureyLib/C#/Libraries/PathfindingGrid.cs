
// Static Grid Pathfinding Functions Script
// by Kyle Furey

// REFERENCE: https://www.redblobgames.com/pathfinding/a-star/introduction.html

using System;
using System.Collections.Generic;

// Include this heading to use the library
using static PathfindingGrid;

// Define the heuristic value type.
using HeuristicType = System.Single;

// Define the weighted space type.
using WeightType = System.Single;

/// <summary>
/// A collection of pathfinding algorithms for navigating connected grid spaces.
/// </summary>
public static class PathfindingGrid
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
    /// •  Heuristic Value = Euclidean Distance or Manhattan Distance
    /// </summary>
    public static HeuristicType CalculateHeuristic(GridSpace current, GridSpace end, bool manhattan = false)
    {
        if (!manhattan)
        {
            HeuristicType xDistance = end.x - current.x;

            HeuristicType yDistance = end.y - current.y;

            HeuristicType heuristic = xDistance * xDistance + yDistance * yDistance;

            return (HeuristicType)Math.Sqrt(heuristic);
        }
        else
        {
            HeuristicType xDistance = end.x - current.x;

            HeuristicType yDistance = end.y - current.y;

            HeuristicType heuristic = Math.Abs(xDistance) + Math.Abs(yDistance);

            return (HeuristicType)heuristic;
        }
    }

    /// <summary>
    /// •  Starting from the start node, returns a list of nodes representing a route to the end node using the given pathfinding algorithm.<br/>
    /// •  Searches every possible node starting from oldest to newest.<br/>
    /// •  Time complexity and precision depend on the selected pathfinding algorithm.<br/>
    /// •  Will calculate the closest location to the goal if the goal is unreachable.
    /// </summary>
    public static Stack<GridSpace> Pathfind(Algorithm algorithm, GridSpace start, GridSpace end, GridGraph graphSettings, HeuristicType heuristicScale = 1)
    {
        switch (algorithm)
        {
            case Algorithm.AStar:

                return AStarSearch(start, end, graphSettings, heuristicScale);

            case Algorithm.Dijkstra:

                return DijkstraSearch(start, end, graphSettings);

            case Algorithm.Heuristic:

                return HeuristicSearch(start, end, graphSettings);

            case Algorithm.BreadthFirst:

                return BreadthFirstSearch(start, end, graphSettings);

            case Algorithm.DepthFirst:

                return DepthFirstSearch(start, end, graphSettings);
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
    public static Stack<GridSpace> DepthFirstSearch(GridSpace start, GridSpace end, GridGraph graphSettings)
    {
        // Check that we can actually move
        if (!graphSettings.adjacentNavigation && !graphSettings.diagonalNavigation)
        {
            return new Stack<GridSpace>();
        }

        // Check if the start and end node are identical
        if (start == end)
        {
            return new Stack<GridSpace>();
        }

        // Initialize our frontier
        Stack<GridSpace> frontier = new Stack<GridSpace>();

        // Enqueue our start node
        frontier.Push(start);

        // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
        // KEY = TO  VALUE = FROM
        // from[currentGridSpace] = the node immediately before currentGridSpace
        Dictionary<GridSpace, GridSpace> from = new Dictionary<GridSpace, GridSpace>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, new GridSpace(int.MaxValue, int.MaxValue) }
        };

        // Store our current value and number of loops
        GridSpace current = end;

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

            // Store the current connection
            GridSpace connection;

            // Loop through adjacent connections
            if (graphSettings.adjacentNavigation)
            {
                // Check right
                connection = current + new GridSpace(1, 0);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Push(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check left
                connection = current + new GridSpace(-1, 0);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Push(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check up
                connection = current + new GridSpace(0, 1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Push(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down
                connection = current + new GridSpace(0, -1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Push(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }
            }

            // Loop through diagonal connections
            if (graphSettings.diagonalNavigation)
            {
                // Check up right
                connection = current + new GridSpace(1, 1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Push(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check up left
                connection = current + new GridSpace(-1, 1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Push(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down right
                connection = current + new GridSpace(1, -1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Push(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down left
                connection = current + new GridSpace(-1, -1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Push(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
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
            foreach (GridSpace to in from.Values)
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
        Stack<GridSpace> route = new Stack<GridSpace>();

        // Build our final route through our dictionary's connections
        while (from[current] != new GridSpace(int.MaxValue, int.MaxValue))
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
    public static Stack<GridSpace> BreadthFirstSearch(GridSpace start, GridSpace end, GridGraph graphSettings)
    {
        // Check that we can actually move
        if (!graphSettings.adjacentNavigation && !graphSettings.diagonalNavigation)
        {
            return new Stack<GridSpace>();
        }

        // Check if the start and end node are identical
        if (start == end)
        {
            return new Stack<GridSpace>();
        }

        // Initialize our frontier
        Queue<GridSpace> frontier = new Queue<GridSpace>();

        // Enqueue our start node
        frontier.Enqueue(start);

        // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
        // KEY = TO  VALUE = FROM
        // from[currentGridSpace] = the node immediately before currentGridSpace
        Dictionary<GridSpace, GridSpace> from = new Dictionary<GridSpace, GridSpace>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, new GridSpace(int.MaxValue, int.MaxValue) }
        };

        // Store our current value and number of loops
        GridSpace current = end;

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

            // Store the current connection
            GridSpace connection;

            // Loop through adjacent connections
            if (graphSettings.adjacentNavigation)
            {
                // Check right
                connection = current + new GridSpace(1, 0);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check left
                connection = current + new GridSpace(-1, 0);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check up
                connection = current + new GridSpace(0, 1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down
                connection = current + new GridSpace(0, -1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }
            }

            // Loop through diagonal connections
            if (graphSettings.diagonalNavigation)
            {
                // Check up right
                connection = current + new GridSpace(1, 1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check up left
                connection = current + new GridSpace(-1, 1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down right
                connection = current + new GridSpace(1, -1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down left
                connection = current + new GridSpace(-1, -1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
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
            foreach (GridSpace to in from.Values)
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
        Stack<GridSpace> route = new Stack<GridSpace>();

        // Build our final route through our dictionary's connections
        while (from[current] != new GridSpace(int.MaxValue, int.MaxValue))
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
    public static Stack<GridSpace> HeuristicSearch(GridSpace start, GridSpace end, GridGraph graphSettings)
    {
        // Check that we can actually move
        if (!graphSettings.adjacentNavigation && !graphSettings.diagonalNavigation)
        {
            return new Stack<GridSpace>();
        }

        // Check if the start and end node are identical
        if (start == end)
        {
            return new Stack<GridSpace>();
        }

        // Initialize our frontier
        PriorityQueue<GridSpace, HeuristicType> frontier = new PriorityQueue<GridSpace, HeuristicType>();

        // Enqueue our start node
        frontier.Enqueue(start, 0);

        // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
        // KEY = TO  VALUE = FROM
        // from[currentGridSpace] = the node immediately before currentGridSpace
        Dictionary<GridSpace, GridSpace> from = new Dictionary<GridSpace, GridSpace>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, new GridSpace(int.MaxValue, int.MaxValue) }
        };

        // Store our current value and number of loops
        GridSpace current = end;

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

            // Store the current connection
            GridSpace connection;

            // Loop through adjacent connections
            if (graphSettings.adjacentNavigation)
            {
                // Check right
                connection = current + new GridSpace(1, 0);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, CalculateHeuristic(connection, end));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check left
                connection = current + new GridSpace(-1, 0);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, CalculateHeuristic(connection, end));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check up
                connection = current + new GridSpace(0, 1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, CalculateHeuristic(connection, end));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down
                connection = current + new GridSpace(0, -1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, CalculateHeuristic(connection, end));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }
            }

            // Loop through diagonal connections
            if (graphSettings.diagonalNavigation)
            {
                // Check up right
                connection = current + new GridSpace(1, 1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, CalculateHeuristic(connection, end));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check up left
                connection = current + new GridSpace(-1, 1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, CalculateHeuristic(connection, end));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down right
                connection = current + new GridSpace(1, -1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, CalculateHeuristic(connection, end));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down left
                connection = current + new GridSpace(-1, -1);

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, CalculateHeuristic(connection, end));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
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
            foreach (GridSpace to in from.Values)
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
        Stack<GridSpace> route = new Stack<GridSpace>();

        // Build our final route through our dictionary's connections
        while (from[current] != new GridSpace(int.MaxValue, int.MaxValue))
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
    public static Stack<GridSpace> GreedyBestFirstSearch(GridSpace start, GridSpace end, GridGraph graphSettings)
    {
        return HeuristicSearch(start, end, graphSettings);
    }

    /// <summary>
    /// •  Starting from the start node, returns a list of nodes representing a route to the end node using Dijkstra's Search Algorithm.<br/>
    /// •  Searches every possible node from oldest to newest but queues nodes with less weight first, and recalculates routes if a faster way to a node is found.<br/>
    /// •  Guarantees the fastest and least resistant route but increases in time exponentially.<br/>
    /// •  Will calculate the closest location to the goal if the goal is unreachable.
    /// </summary>
    public static Stack<GridSpace> DijkstraSearch(GridSpace start, GridSpace end, GridGraph graphSettings)
    {
        // Check that we can actually move
        if (!graphSettings.adjacentNavigation && !graphSettings.diagonalNavigation)
        {
            return new Stack<GridSpace>();
        }

        // Check if the start and end node are identical
        if (start == end)
        {
            return new Stack<GridSpace>();
        }

        // Initialize our frontier
        PriorityQueue<GridSpace, HeuristicType> frontier = new PriorityQueue<GridSpace, HeuristicType>();

        // Enqueue our start node
        frontier.Enqueue(start, 0);

        // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
        // KEY = TO  VALUE = FROM
        // from[currentGridSpace] = the node immediately before currentGridSpace
        Dictionary<GridSpace, GridSpace> from = new Dictionary<GridSpace, GridSpace>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, new GridSpace(int.MaxValue, int.MaxValue) }
        };

        // Make a new dictionary that corresponds to the from dictionary's "to" nodes and store the total cost + weight to get to that node
        Dictionary<GridSpace, WeightType> weights = new Dictionary<GridSpace, WeightType>
        {
            // Set our start node's cost to 0
            { start, 0 }
        };

        // Store our current value and number of loops
        GridSpace current = end;

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

            // Store the current connection
            GridSpace connection;

            // Store the new total cost
            WeightType newCost;

            // Loop through adjacent connections
            if (graphSettings.adjacentNavigation)
            {
                // Check right
                connection = current + new GridSpace(1, 0);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check left
                connection = current + new GridSpace(-1, 0);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check up
                connection = current + new GridSpace(0, 1);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down
                connection = current + new GridSpace(0, -1);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }
            }

            // Loop through diagonal connections
            if (graphSettings.diagonalNavigation)
            {
                // Check up right
                connection = current + new GridSpace(1, 1);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check up left
                connection = current + new GridSpace(-1, 1);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down right
                connection = current + new GridSpace(1, -1);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down left
                connection = current + new GridSpace(-1, -1);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
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
            foreach (GridSpace to in from.Values)
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
        Stack<GridSpace> route = new Stack<GridSpace>();

        // Build our final route through our dictionary's connections
        while (from[current] != new GridSpace(int.MaxValue, int.MaxValue))
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
    public static Stack<GridSpace> UniformCostSearch(GridSpace start, GridSpace end, GridGraph graphSettings)
    {
        return DijkstraSearch(start, end, graphSettings);
    }

    /// <summary>
    /// •  Starting from the start node, returns a list of nodes representing a route to the end node using the A Star Search Algorithm.<br/>
    /// •  Searches every possible node from oldest to newest but queues nodes with less weight first + the heuristic, and recalculates routes if a faster way to a node is found.<br/>
    /// •  Guarantees the fastest and possibly least resistant route in shorter time.<br/>
    /// •  Will calculate the closest location to the goal if the goal is unreachable.
    /// </summary>
    public static Stack<GridSpace> AStarSearch(GridSpace start, GridSpace end, GridGraph graphSettings, HeuristicType heuristicScale = 1)
    {
        // Check that we can actually move
        if (!graphSettings.adjacentNavigation && !graphSettings.diagonalNavigation)
        {
            return new Stack<GridSpace>();
        }

        // Check if the start and end node are identical
        if (start == end)
        {
            return new Stack<GridSpace>();
        }

        // Initialize our frontier
        PriorityQueue<GridSpace, HeuristicType> frontier = new PriorityQueue<GridSpace, HeuristicType>();

        // Enqueue our start node
        frontier.Enqueue(start, 0);

        // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
        // KEY = TO  VALUE = FROM
        // from[currentGridSpace] = the node immediately before currentGridSpace
        Dictionary<GridSpace, GridSpace> from = new Dictionary<GridSpace, GridSpace>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, new GridSpace(int.MaxValue, int.MaxValue) }
        };

        // Make a new dictionary that corresponds to the from dictionary's "to" nodes and store the total cost + weight to get to that node
        Dictionary<GridSpace, WeightType> weights = new Dictionary<GridSpace, WeightType>
        {
            // Set our start node's cost to 0
            { start, 0 }
        };

        // Store our current value and number of loops
        GridSpace current = end;

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

            // Store the current connection
            GridSpace connection;

            // Store the new total cost
            WeightType newCost;

            // Loop through adjacent connections
            if (graphSettings.adjacentNavigation)
            {
                // Check right
                connection = current + new GridSpace(1, 0);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost + (CalculateHeuristic(connection, end) * heuristicScale));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check left
                connection = current + new GridSpace(-1, 0);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost + (CalculateHeuristic(connection, end) * heuristicScale));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check up
                connection = current + new GridSpace(0, 1);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost + (CalculateHeuristic(connection, end) * heuristicScale));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down
                connection = current + new GridSpace(0, -1);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost + (CalculateHeuristic(connection, end) * heuristicScale));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }
            }

            // Loop through diagonal connections
            if (graphSettings.diagonalNavigation)
            {
                // Check up right
                connection = current + new GridSpace(1, 1);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost + (CalculateHeuristic(connection, end) * heuristicScale));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check up left
                connection = current + new GridSpace(-1, 1);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost + (CalculateHeuristic(connection, end) * heuristicScale));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down right
                connection = current + new GridSpace(1, -1);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost + (CalculateHeuristic(connection, end) * heuristicScale));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
                }

                // Check down left
                connection = current + new GridSpace(-1, -1);

                // Store the new total cost of traveling this node
                if (graphSettings.ignoreWeights || graphSettings.weights == null || !graphSettings.weights.ContainsKey(connection))
                {
                    newCost = weights[current] + graphSettings.defaultWeight;
                }
                else
                {
                    newCost = weights[current] + graphSettings.weights[connection];
                }

                if (graphSettings.ignoreOccupied || graphSettings.occupied == null || (graphSettings.invertOccupied ? graphSettings.occupied.Contains(connection) : !graphSettings.occupied.Contains(connection)))
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection) || newCost < weights[connection])
                    {
                        // Update the total weight of this connected node
                        weights[connection] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection, newCost + (CalculateHeuristic(connection, end) * heuristicScale));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection] = current;
                    }
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
            foreach (GridSpace to in from.Values)
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
        Stack<GridSpace> route = new Stack<GridSpace>();

        // Build our final route through our dictionary's connections
        while (from[current] != new GridSpace(int.MaxValue, int.MaxValue))
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

/// <summary>
/// A single space in a grid.
/// </summary>
public struct GridSpace
{
    /// <summary>
    /// X Cartesian coordinate.
    /// </summary>
    public int x;

    /// <summary>
    /// Y Cartesian coordinate.
    /// </summary>
    public int y;

    /// <summary>
    /// Default constructor.
    /// </summary>
    public GridSpace(int x = 0, int y = 0)
    {
        this.x = x;

        this.y = y;
    }

    /// <summary>
    /// Checks if the given grid spaces are equal.
    /// </summary>
    public static bool operator ==(GridSpace left, GridSpace right)
    {
        return left.x == right.x && left.y == right.y;
    }

    /// <summary>
    /// Checks if the given grid spaces are not equal.
    /// </summary>
    public static bool operator !=(GridSpace left, GridSpace right)
    {
        return left.x != right.x || left.y != right.y;
    }

    /// <summary>
    /// Adds two grid spaces together.
    /// </summary>
    public static GridSpace operator +(GridSpace left, GridSpace right)
    {
        return new GridSpace(left.x + right.x, left.y + right.y);
    }

    /// <summary>
    /// Subtracts two grid spaces together.
    /// </summary>
    public static GridSpace operator -(GridSpace left, GridSpace right)
    {
        return new GridSpace(left.x - right.x, left.y - right.y);
    }

    /// <summary>
    /// Returns a string representation of the grid space.
    /// </summary>
    /// <returns></returns>
    public string ToString()
    {
        return "{ " + x + ", " + y + " }";
    }
}

/// <summary>
/// Settings that define a graph in grid space.
/// </summary>
public struct GridGraph
{
    /// <summary>
    /// Whether this graph enables moving adjacent.
    /// </summary>
    public bool adjacentNavigation;

    /// <summary>
    /// Whether this graph enables moving diagonally.
    /// </summary>
    public bool diagonalNavigation;

    /// <summary>
    /// Whether this graph ignores occupied spaces.
    /// </summary>
    public bool ignoreOccupied;

    /// <summary>
    /// The current occupied spaces of this graph.
    /// </summary>
    public HashSet<GridSpace> occupied;

    /// <summary>
    /// Whether to assume all spaces are occupied except the ones in the occupied hash set.
    /// </summary>
    public bool invertOccupied;

    /// <summary>
    /// Whether this graph ignores weighted spaces.
    /// </summary>
    public bool ignoreWeights;

    /// <summary>
    /// The weighted spaces of this graph and their corresponding weights (must be positive or zero).
    /// </summary>
    public Dictionary<GridSpace, WeightType> weights;

    /// <summary>
    /// The default weight value of this graph (must be positive or zero).
    /// </summary>
    public WeightType defaultWeight;

    /// <summary>
    /// Graph constructor.
    /// </summary>
    public GridGraph(bool adjacentNavigation = true, bool diagonalNavigation = true, bool ignoreOccupied = false, HashSet<GridSpace> occupied = null, bool invertOccupied = false, bool ignoreWeights = false, Dictionary<GridSpace, WeightType> weights = null, WeightType defaultWeight = 1)
    {
        this.adjacentNavigation = adjacentNavigation;

        this.diagonalNavigation = diagonalNavigation;

        this.ignoreOccupied = ignoreOccupied;

        this.occupied = occupied;

        this.invertOccupied = invertOccupied;

        this.ignoreWeights = ignoreWeights;

        this.weights = weights;

        this.defaultWeight = defaultWeight;
    }
}
