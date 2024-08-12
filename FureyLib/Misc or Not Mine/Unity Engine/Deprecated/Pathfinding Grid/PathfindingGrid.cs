
// Static Grid Pathfinding Functions Script
// by Kyle Furey

namespace Navigation
{
    using System.Collections.Generic;
    using UnityEngine;

    // Define the grid nodes
    using Node = UnityEngine.Vector2Int;

    // A collection of pathfinding algorithms relying on connected grid spaces.
    public static class PathfindingGrid
    {
        // List of algorithm types
        public enum Algorithm
        {
            AStar,
            Dijkstra,
            Heuristic,
            BreadthFirst
        }

        // Settings that define a graph in grid space.
        public class Graph
        {
            // Constructor
            public Graph(bool canMoveAdjacent = true, bool canMoveDiagonal = true, bool ignoreOccupiedSpaces = false, List<Node> occupiedSpaces = null, bool ignoreWeightedSpaces = false, Dictionary<Node, float> weightedSpaces = null)
            {
                this.canMoveAdjacent = canMoveAdjacent;
                this.canMoveDiagonal = canMoveDiagonal;
                this.ignoreOccupiedSpaces = ignoreOccupiedSpaces;
                this.occupiedSpaces = occupiedSpaces;
                this.ignoreWeightedSpaces = ignoreWeightedSpaces;
                this.weightedSpaces = weightedSpaces;
            }

            // Whether this graph enables moving adjacent or diagonally
            public bool canMoveAdjacent = true;
            public bool canMoveDiagonal = true;

            // The occupied spaces of this graph
            public bool ignoreOccupiedSpaces = false;
            public List<Node> occupiedSpaces = new List<Node>();

            // The weighted spaces of this graph and their weights
            public bool ignoreWeightedSpaces = false;
            public Dictionary<Node, float> weightedSpaces = new Dictionary<Node, float>();
        }

        private const int maxLoops = 300;

        // Selects the proper function based on the given enum and returns a route from that function
        public static List<Node> Pathfind(Algorithm algorithm, Node start, Node end, bool canMoveAdjacent = true, bool canMoveDiagonal = true, bool ignoreOccupiedSpaces = false, List<Node> occupiedSpaces = null, bool ignoreWeightedSpaces = false, Dictionary<Node, float> weightedSpaces = null, float heuristicScale = 1)
        {
            // Select a pathfinding function based on the selected algorithm
            switch (algorithm)
            {
                case Algorithm.AStar:
                    return AStarSearch(start, end, canMoveAdjacent, canMoveDiagonal, ignoreOccupiedSpaces, occupiedSpaces, ignoreWeightedSpaces, weightedSpaces, heuristicScale);

                case Algorithm.Dijkstra:
                    return DijkstraSearch(start, end, canMoveAdjacent, canMoveDiagonal, ignoreOccupiedSpaces, occupiedSpaces, ignoreWeightedSpaces, weightedSpaces);

                case Algorithm.Heuristic:
                    return HeuristicSearch(start, end, canMoveAdjacent, canMoveDiagonal, ignoreOccupiedSpaces, occupiedSpaces);

                case Algorithm.BreadthFirst:
                    return BreadthFirstSearch(start, end, canMoveAdjacent, canMoveDiagonal, ignoreOccupiedSpaces, occupiedSpaces);

                default:
                    Debug.LogError("Could not calculate a route! No algorithm was selected!");
                    return new List<Node>();
            }
        }

        // Selects the proper function based on the given enum and returns a route from that function
        public static List<Node> Pathfind(Algorithm algorithm, Node start, Node end, ref Graph graph, float heuristicScale = 1)
        {
            return Pathfind(algorithm, start, end, graph.canMoveAdjacent, graph.canMoveDiagonal, graph.ignoreOccupiedSpaces, graph.occupiedSpaces, graph.ignoreWeightedSpaces, graph.weightedSpaces, heuristicScale);
        }

        // Selects the proper function based on the given enum and returns a route from that function
        public static List<Node> Pathfind(Algorithm algorithm, Node start, Node end, int heuristicScale = 1, bool canMoveAdjacent = true, bool canMoveDiagonal = true, bool ignoreOccupiedSpaces = false, List<Node> occupiedSpaces = null, bool ignoreWeightedSpaces = false, Dictionary<Node, float> weightedSpaces = null)
        {
            return Pathfind(algorithm, start, end, canMoveAdjacent, canMoveDiagonal, ignoreOccupiedSpaces, occupiedSpaces, ignoreWeightedSpaces, weightedSpaces, heuristicScale);
        }

        // Selects the proper function based on the given enum and returns a route from that function
        public static List<Node> Pathfind(Algorithm algorithm, Node start, Node end, float heuristicScale, ref Graph graph)
        {
            return Pathfind(algorithm, start, end, graph.canMoveAdjacent, graph.canMoveDiagonal, graph.ignoreOccupiedSpaces, graph.occupiedSpaces, graph.ignoreWeightedSpaces, graph.weightedSpaces, heuristicScale);
        }


        // SEARCHING ALGORITHMS

        // Starting from the start node, returns a list of nodes representing a route to the ending node using the Breadth First Search Algorithm
        /// Searches every possible node starting from oldest to newest. Guarantees the fastest route but increases in time exponentially
        public static List<Node> BreadthFirstSearch(Node start, Node end, bool canMoveAdjacent = true, bool canMoveDiagonal = true, bool ignoreOccupiedSpaces = false, List<Node> occupiedSpaces = null)
        {
            // Check that we can actually move
            if (!canMoveAdjacent && !canMoveDiagonal)
            {
                Debug.LogWarning("Could not calculate a route! We cannot move adjacent or diagonally!");
                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start + " to " + end + " with the Breadth First Search Algorithm.");

            // Initalize our frontier
            Queue<Node> frontier = new Queue<Node>();

            // Enqueue our start node
            frontier.Enqueue(start);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, new Node(int.MaxValue, int.MaxValue) }
        };

            // Store our current value and number of loops
            Node current = end;
            int loopCount = -1;

            // Loop until our frontier is empty
            while (frontier.Count > 0)
            {
                // Loop check
                if (loopCount > maxLoops)
                {
                    break;
                }

                // Dequeue our current node and increment our number of loops
                current = frontier.Dequeue();
                loopCount++;

                // Check if we made it to our goal
                if (current == end)
                {
                    break;
                }

                // Store the current connection
                Node connection;

                // Loop through adjacent connections
                if (canMoveAdjacent)
                {
                    // Check right
                    connection = current + new Node(1, 0);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(-1, 0);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(0, 1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(0, -1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                if (canMoveDiagonal)
                {
                    // Check up right
                    connection = current + new Node(1, 1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(-1, 1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(1, -1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(-1, -1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start + " to " + end + " using Breadth First Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != new Node(int.MaxValue, int.MaxValue))
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start + " to " + end + " using Breadth First Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }

        // Starting from the start node, returns a list of nodes representing a route to the ending node using the Breadth First Search Algorithm
        /// Searches every possible node starting from oldest to newest. Guarantees the fastest route but increases in time exponentially
        public static List<Node> BreadthFirstSearch(Node start, Node end, ref Graph graph)
        {
            return BreadthFirstSearch(start, end, graph.canMoveAdjacent, graph.canMoveDiagonal, graph.ignoreOccupiedSpaces, graph.occupiedSpaces);
        }

        // Starting from the start node, returns a list of nodes representing a route to the ending node using the Heuristic Search Algorithm
        /// Searches every possible node from oldest to newest but queues nodes considered closer to the goal by the heuristic first. Completes quicker but can be wrong
        public static List<Node> HeuristicSearch(Node start, Node end, bool canMoveAdjacent = true, bool canMoveDiagonal = true, bool ignoreOccupiedSpaces = false, List<Node> occupiedSpaces = null)
        {
            // Check that we can actually move
            if (!canMoveAdjacent && !canMoveDiagonal)
            {
                Debug.LogWarning("Could not calculate a route! We cannot move adjacent or diagonally!");
                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start + " to " + end + " with the Heuristic Search Algorithm.");

            // Initalize our frontier
            PriorityQueue<Node> frontier = new PriorityQueue<Node>();

            // Enqueue our start node
            frontier.Enqueue(start, 0);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, new Node(int.MaxValue, int.MaxValue) }
        };

            // Store our current value and number of loops
            Node current = end;
            int loopCount = -1;

            // Loop until our frontier is empty
            while (frontier.Queue.Count > 0)
            {
                // Loop check
                if (loopCount > maxLoops)
                {
                    break;
                }

                // Dequeue our current node and increment our number of loops
                current = frontier.Dequeue();
                loopCount++;

                // Check if we made it to our goal
                if (current == end)
                {
                    break;
                }

                // Store the current connection
                Node connection;

                // Loop through adjacent connections
                if (canMoveAdjacent)
                {
                    // Check right
                    connection = current + new Node(1, 0);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check left
                    connection = current + new Node(-1, 0);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check up
                    connection = current + new Node(0, 1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check down
                    connection = current + new Node(0, -1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }
                }

                // Loop through diagonal connections
                if (canMoveDiagonal)
                {
                    // Check up right
                    connection = current + new Node(1, 1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check up left
                    connection = current + new Node(-1, 1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check down right
                    connection = current + new Node(1, -1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check down left
                    connection = current + new Node(-1, -1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }
                }
            }

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start + " to " + end + " using Heuristic Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != new Node(int.MaxValue, int.MaxValue))
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start + " to " + end + " using Heuristic Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }

        // Starting from the start node, returns a list of nodes representing a route to the ending node using the Heuristic Search Algorithm
        /// Searches every possible node from oldest to newest but queues nodes considered closer to the goal by the heuristic first. Completes quicker but can be wrong
        public static List<Node> HeuristicSearch(Node start, Node end, ref Graph graph)
        {
            return HeuristicSearch(start, end, graph.canMoveAdjacent, graph.canMoveDiagonal, graph.ignoreOccupiedSpaces, graph.occupiedSpaces);
        }

        // Starting from the start node, returns a list of nodes representing a route to the ending node using Dijkstra's Search Algorithm
        /// Searches every possible node from oldest to newest but queues nodes with less weight first, and recalculates routes if a faster way to a node is found. Guarantees the fastest and least resistant route but increases in time exponentially
        public static List<Node> DijkstraSearch(Node start, Node end, bool canMoveAdjacent = true, bool canMoveDiagonal = true, bool ignoreOccupiedSpaces = false, List<Node> occupiedSpaces = null, bool ignoreWeightedSpaces = false, Dictionary<Node, float> weightedSpaces = null)
        {
            // Check that we can actually move
            if (!canMoveAdjacent && !canMoveDiagonal)
            {
                Debug.LogWarning("Could not calculate a route! We cannot move adjacent or diagonally!");
                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start + " to " + end + " with the Dijkstra Search Algorithm.");

            // Initalize our frontier
            PriorityQueue<Node> frontier = new PriorityQueue<Node>();

            // Enqueue our start node
            frontier.Enqueue(start, 0);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, new Node(int.MaxValue, int.MaxValue) }
        };

            // Make a new dictionary that corresponds to the from dictionary's "to" nodes and store the total cost + weight to get to that node
            Dictionary<Node, float> weights = new Dictionary<Node, float>()
        {
            // Set our start node's cost to 0
            { start, 0 }
        };

            // Store our current value and number of loops
            Node current = end;
            int loopCount = -1;

            // Loop until our frontier is empty
            while (frontier.Queue.Count > 0)
            {
                // Loop check
                if (loopCount > maxLoops)
                {
                    break;
                }

                // Dequeue our current node and increment our number of loops
                current = frontier.Dequeue();
                loopCount++;

                // Check if we made it to our goal
                if (current == end)
                {
                    break;
                }

                // Store the current connection
                Node connection;

                // Store the new total cost
                float newCost;

                // Loop through adjacent connections
                if (canMoveAdjacent)
                {
                    // Check right
                    connection = current + new Node(1, 0);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(-1, 0);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(0, 1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(0, -1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                if (canMoveDiagonal)
                {
                    // Check up right
                    connection = current + new Node(1, 1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(-1, 1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(1, -1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(-1, -1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start + " to " + end + " using Dijkstra Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != new Node(int.MaxValue, int.MaxValue))
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start + " to " + end + " using Dijkstra Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }

        // Starting from the start node, returns a list of nodes representing a route to the ending node using Dijkstra's Search Algorithm
        /// Searches every possible node from oldest to newest but queues nodes with less weight first, and recalculates routes if a faster way to a node is found. Guarantees the fastest and least resistant route but increases in time exponentially
        public static List<Node> DijkstraSearch(Node start, Node end, ref Graph graph)
        {
            return DijkstraSearch(start, end, graph.canMoveAdjacent, graph.canMoveDiagonal, graph.ignoreOccupiedSpaces, graph.occupiedSpaces, graph.ignoreWeightedSpaces, graph.weightedSpaces);
        }

        // Starting from the start node, returns a list of nodes representing a route to the ending node using the A Star Algorithm
        /// Searches every possible node from oldest to newest but queues nodes with less weight first + the heuristic, and recalculates routes if a faster way to a node is found. Guarantees the fastest route in shorter time
        public static List<Node> AStarSearch(Node start, Node end, bool canMoveAdjacent = true, bool canMoveDiagonal = true, bool ignoreOccupiedSpaces = false, List<Node> occupiedSpaces = null, bool ignoreWeightedSpaces = false, Dictionary<Node, float> weightedSpaces = null, float heuristicScale = 1)
        {
            // Check that we can actually move
            if (!canMoveAdjacent && !canMoveDiagonal)
            {
                Debug.LogWarning("Could not calculate a route! We cannot move adjacent or diagonally!");
                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start + " to " + end + " with the A Star Search Algorithm.");

            // Initalize our frontier
            PriorityQueue<Node> frontier = new PriorityQueue<Node>();

            // Enqueue our start node
            frontier.Enqueue(start, 0);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, new Node(int.MaxValue, int.MaxValue) }
        };

            // Make a new dictionary that corresponds to the from dictionary's "to" nodes and store the total cost + weight to get to that node
            Dictionary<Node, float> weights = new Dictionary<Node, float>()
        {
            // Set our start node's cost to 0
            { start, 0 }
        };

            // Store our current value and number of loops
            Node current = end;
            int loopCount = -1;

            // Loop until our frontier is empty
            while (frontier.Queue.Count > 0)
            {
                // Loop check
                if (loopCount > maxLoops)
                {
                    break;
                }

                // Dequeue our current node and increment our number of loops
                current = frontier.Dequeue();
                loopCount++;

                // Check if we made it to our goal
                if (current == end)
                {
                    break;
                }

                // Store the current connection
                Node connection;

                // Store the new total cost
                float newCost;

                // Loop through adjacent connections
                if (canMoveAdjacent)
                {
                    // Check right
                    connection = current + new Node(1, 0);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection) || newCost < weights[connection])
                        {
                            // Update the total weight of this connected node
                            weights[connection] = newCost;

                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, newCost + (Heuristic(connection, end) * heuristicScale));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check left
                    connection = current + new Node(-1, 0);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection) || newCost < weights[connection])
                        {
                            // Update the total weight of this connected node
                            weights[connection] = newCost;

                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, newCost + (Heuristic(connection, end) * heuristicScale));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check up
                    connection = current + new Node(0, 1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection) || newCost < weights[connection])
                        {
                            // Update the total weight of this connected node
                            weights[connection] = newCost;

                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, newCost + (Heuristic(connection, end) * heuristicScale));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check down
                    connection = current + new Node(0, -1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection) || newCost < weights[connection])
                        {
                            // Update the total weight of this connected node
                            weights[connection] = newCost;

                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, newCost + (Heuristic(connection, end) * heuristicScale));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }
                }

                // Loop through diagonal connections
                if (canMoveDiagonal)
                {
                    // Check up right
                    connection = current + new Node(1, 1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection) || newCost < weights[connection])
                        {
                            // Update the total weight of this connected node
                            weights[connection] = newCost;

                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, newCost + (Heuristic(connection, end) * heuristicScale));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check up left
                    connection = current + new Node(-1, 1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection) || newCost < weights[connection])
                        {
                            // Update the total weight of this connected node
                            weights[connection] = newCost;

                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, newCost + (Heuristic(connection, end) * heuristicScale));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check down right
                    connection = current + new Node(1, -1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection) || newCost < weights[connection])
                        {
                            // Update the total weight of this connected node
                            weights[connection] = newCost;

                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, newCost + (Heuristic(connection, end) * heuristicScale));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check down left
                    connection = current + new Node(-1, -1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection) || newCost < weights[connection])
                        {
                            // Update the total weight of this connected node
                            weights[connection] = newCost;

                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, newCost + (Heuristic(connection, end) * heuristicScale));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }
                }
            }

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start + " to " + end + " using A Star Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != new Node(int.MaxValue, int.MaxValue))
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start + " to " + end + " using A Star Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }

        public static List<Node> AStarSearch(Node start, Node end, ref Graph graph, float heuristicScale = 1)
        {
            return AStarSearch(start, end, graph.canMoveAdjacent, graph.canMoveDiagonal, graph.ignoreOccupiedSpaces, graph.occupiedSpaces, graph.ignoreWeightedSpaces, graph.weightedSpaces, heuristicScale);
        }

        public static List<Node> AStarSearch(Node start, Node end, float heuristicScale = 1, bool canMoveAdjacent = true, bool canMoveDiagonal = true, bool ignoreOccupiedSpaces = false, List<Node> occupiedSpaces = null, bool ignoreWeightedSpaces = false, Dictionary<Node, float> weightedSpaces = null)
        {
            return AStarSearch(start, end, canMoveAdjacent, canMoveDiagonal, ignoreOccupiedSpaces, occupiedSpaces, ignoreWeightedSpaces, weightedSpaces, heuristicScale);
        }

        public static List<Node> AStarSearch(Node start, Node end, float heuristicScale, ref Graph graph)
        {
            return AStarSearch(start, end, graph.canMoveAdjacent, graph.canMoveDiagonal, graph.ignoreOccupiedSpaces, graph.occupiedSpaces, graph.ignoreWeightedSpaces, graph.weightedSpaces, heuristicScale);
        }

        // Calculates a priority value between two nodes from the given heuristic function
        /// The condition to determine whether an element is closer to the goal or not
        private static float Heuristic(Node current, Node end)
        {
            // HEURISTIC = Manhattan distance between two nodes multiplied by the default weight
            float xDistance = current.x - end.x;
            float yDistance = current.y - end.y;
            float heuristic = Mathf.Abs(xDistance) + Mathf.Abs(yDistance);

            return heuristic;

            /*
            // HEURISTIC = Squared euclidean distance between two nodes
            float xDistance = current.x - end.x;
            float yDistance = current.y - end.y;
            float heuristic = xDistance * xDistance + yDistance * yDistance;

            return heuristic;
            */
        }


        // OTHER SEARCHING ALGORITHMS

        // Identical to Heuristic Search Algorithm
        /// Another name for the algorithm
        public static List<Node> GreedyBestFirstSearch(Node start, Node end, bool canMoveAdjacent = true, bool canMoveDiagonal = true, bool ignoreOccupiedSpaces = false, List<Node> occupiedSpaces = null, bool ignoreWeightedSpaces = false, Dictionary<Node, float> weightedSpaces = null)
        {
            // Check that we can actually move
            if (!canMoveAdjacent && !canMoveDiagonal)
            {
                Debug.LogWarning("Could not calculate a route! We cannot move adjacent or diagonally!");
                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start + " to " + end + " with the Greedy Best First Search Algorithm.");

            // Initalize our frontier
            PriorityQueue<Node> frontier = new PriorityQueue<Node>();

            // Enqueue our start node
            frontier.Enqueue(start, 0);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, new Node(int.MaxValue, int.MaxValue) }
        };

            // Store our current value and number of loops
            Node current = end;
            int loopCount = -1;

            // Loop until our frontier is empty
            while (frontier.Queue.Count > 0)
            {
                // Loop check
                if (loopCount > maxLoops)
                {
                    break;
                }

                // Dequeue our current node and increment our number of loops
                current = frontier.Dequeue();
                loopCount++;

                // Check if we made it to our goal
                if (current == end)
                {
                    break;
                }

                // Store the current connection
                Node connection;

                // Loop through adjacent connections
                if (canMoveAdjacent)
                {
                    // Check right
                    connection = current + new Node(1, 0);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check left
                    connection = current + new Node(-1, 0);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check up
                    connection = current + new Node(0, 1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check down
                    connection = current + new Node(0, -1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }
                }

                // Loop through diagonal connections
                if (canMoveDiagonal)
                {
                    // Check up right
                    connection = current + new Node(1, 1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check up left
                    connection = current + new Node(-1, 1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check down right
                    connection = current + new Node(1, -1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check down left
                    connection = current + new Node(-1, -1);

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection))
                        {
                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }
                }
            }

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start + " to " + end + " using Greedy Best First Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != new Node(int.MaxValue, int.MaxValue))
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start + " to " + end + " using Greedy Best First Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }

        public static List<Node> GreedyBestFirstSearch(Node start, Node end, ref Graph graph)
        {
            return GreedyBestFirstSearch(start, end, graph.canMoveAdjacent, graph.canMoveDiagonal, graph.ignoreOccupiedSpaces, graph.occupiedSpaces, graph.ignoreWeightedSpaces, graph.weightedSpaces);
        }

        // Identical to Dijkstra's Search Algorithm
        /// Another name for the algorithm
        public static List<Node> UniformCostSearch(Node start, Node end, bool canMoveAdjacent = true, bool canMoveDiagonal = true, bool ignoreOccupiedSpaces = false, List<Node> occupiedSpaces = null, bool ignoreWeightedSpaces = false, Dictionary<Node, float> weightedSpaces = null, bool invertOccupication = false)
        {

            // Check that we can actually move
            if (!canMoveAdjacent && !canMoveDiagonal)
            {
                Debug.LogWarning("Could not calculate a route! We cannot move adjacent or diagonally!");
                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start + " to " + end + " with the Uniform Cost Search Algorithm.");

            // Initalize our frontier
            PriorityQueue<Node> frontier = new PriorityQueue<Node>();

            // Enqueue our start node
            frontier.Enqueue(start, 0);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to an impossible node in our route dictionary
            { start, new Node(int.MaxValue, int.MaxValue) }
        };

            // Make a new dictionary that corresponds to the from dictionary's "to" nodes and store the total cost + weight to get to that node
            Dictionary<Node, float> weights = new Dictionary<Node, float>()
        {
            // Set our start node's cost to 0
            { start, 0 }
        };

            // Store our current value and number of loops
            Node current = end;
            int loopCount = -1;

            // Loop until our frontier is empty
            while (frontier.Queue.Count > 0)
            {
                // Loop check
                if (loopCount > maxLoops)
                {
                    break;
                }

                // Dequeue our current node and increment our number of loops
                current = frontier.Dequeue();
                loopCount++;

                // Check if we made it to our goal
                if (current == end)
                {
                    break;
                }

                // Store the current connection
                Node connection;

                // Store the new total cost
                float newCost;

                // Loop through adjacent connections
                if (canMoveAdjacent)
                {
                    // Check right
                    connection = current + new Node(1, 0);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(-1, 0);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(0, 1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(0, -1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                if (canMoveDiagonal)
                {
                    // Check up right
                    connection = current + new Node(1, 1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(-1, 1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(1, -1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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
                    connection = current + new Node(-1, -1);

                    // Store the new total cost of traveling this node
                    if (ignoreWeightedSpaces || weightedSpaces == null || !weightedSpaces.ContainsKey(connection))
                    {
                        newCost = weights[current];
                    }
                    else
                    {
                        newCost = weights[current] + weightedSpaces[connection];
                    }

                    if (ignoreOccupiedSpaces || occupiedSpaces == null || !occupiedSpaces.Contains(connection))
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

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start + " to " + end + " using Uniform Cost Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != new Node(int.MaxValue, int.MaxValue))
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start + " to " + end + " using Uniform Cost Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }

        public static List<Node> UniformCostSearch(Node start, Node end, ref Graph graph)
        {
            return UniformCostSearch(start, end, graph.canMoveAdjacent, graph.canMoveDiagonal, graph.ignoreOccupiedSpaces, graph.occupiedSpaces, graph.ignoreWeightedSpaces, graph.weightedSpaces);
        }
    }
}
