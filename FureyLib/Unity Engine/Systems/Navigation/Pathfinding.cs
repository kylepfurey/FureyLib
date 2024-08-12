
// Static Pathfinding Functions Script
// by Kyle Furey

namespace Navigation
{
    using System.Collections.Generic;
    using UnityEngine;

    // A collection of pathfinding algorithms relying on a graph and its nodes and connections.
    public static class Pathfinding
    {
        // List of algorithm types
        public enum Algorithm
        {
            AStar,
            Dijkstra,
            Heuristic,
            BreadthFirst
        }

        private const int maxLoops = 300;

        // Selects the proper function based on the given enum and returns a route from that function
        public static List<Node> Pathfind(Algorithm algorithm, Node start, Node end, float heuristicScale = 1)
        {
            // Select a pathfinding function based on the selected algorithm
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

                default:
                    Debug.LogError("Could not calculate a route! No algorithm was selected!");
                    return new List<Node>();
            }
        }


        // SEARCHING ALGORITHMS

        // Starting from the start node, returns a list of nodes representing a route to the ending node using the Breadth First Search Algorithm
        /// Searches every possible node starting from oldest to newest. Guarantees the fastest route but increases in time exponentially
        public static List<Node> BreadthFirstSearch(Node start, Node end)
        {
            // Check if we are missing the start node or end node
            if (start == null || end == null)
            {
                if (start == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the start node!");
                }
                else if (end == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the end node!");
                }

                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node with the Breadth First Search Algorithm.");

            // Initalize our frontier
            Queue<Node> frontier = new Queue<Node>();

            // Enqueue our start node
            frontier.Enqueue(start);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to null in our route dictionary
            { start, null }
        };

            // Store our current value and number of loops
            Node current = null;
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

                // Loop through our current node's connections
                foreach (Connection connection in current.connections)
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection.connectedNode))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection.connectedNode);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection.connectedNode] = current;
                    }
                }
            }

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Breadth First Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != null)
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Breadth First Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node.gameObject.name;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }

        // Starting from the start node, returns a list of nodes representing a route to the ending node using the Heuristic Search Algorithm
        /// Searches every possible node from oldest to newest but queues nodes considered closer to the goal by the heuristic first. Completes quicker but can be wrong
        public static List<Node> HeuristicSearch(Node start, Node end)
        {
            // Check if we are missing the start node or end node
            if (start == null || end == null)
            {
                if (start == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the start node!");
                }
                else if (end == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the end node!");
                }

                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node with the Heuristic Search Algorithm.");

            // Initalize our frontier
            PriorityQueue<Node> frontier = new PriorityQueue<Node>();

            // Enqueue our start node
            frontier.Enqueue(start, 0);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to null in our route dictionary
            { start, null }
        };

            // Store our current value and number of loops
            Node current = null;
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

                // Loop through our current node's connections
                foreach (Connection connection in current.connections)
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection.connectedNode))
                    {
                        // Enqueue our connected node to the frontier based on the heuristic function
                        frontier.Enqueue(connection.connectedNode, Heuristic(connection.connectedNode, end));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection.connectedNode] = current;
                    }
                }
            }

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Heuristic Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != null)
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Heuristic Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node.gameObject.name;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }

        // Starting from the start node, returns a list of nodes representing a route to the ending node using Dijkstra's Search Algorithm
        /// Searches every possible node from oldest to newest but queues nodes with less weight first, and recalculates routes if a faster way to a node is found. Guarantees the fastest and least resistant route but increases in time exponentially
        public static List<Node> DijkstraSearch(Node start, Node end)
        {
            // Check if we are missing the start node or end node
            if (start == null || end == null)
            {
                if (start == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the start node!");
                }
                else if (end == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the end node!");
                }

                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node with the Dijkstra Search Algorithm.");

            // Initalize our frontier
            PriorityQueue<Node> frontier = new PriorityQueue<Node>();

            // Enqueue our start node
            frontier.Enqueue(start, 0);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to null in our route dictionary
            { start, null }
        };

            // Make a new dictionary that corresponds to the from dictionary's "to" nodes and store the total cost + weight to get to that node
            Dictionary<Node, float> weights = new Dictionary<Node, float>()
        {
            // Set our start node's cost to 0
            { start, 0 }
        };

            // Store our current value and number of loops
            Node current = null;
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

                // Loop through our current node's connections
                foreach (Connection connection in current.connections)
                {
                    // Store the new total cost of traveling this node
                    float newCost = weights[current] + connection.weight + connection.connectedNode.weight;

                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection.connectedNode) || newCost < weights[connection.connectedNode])
                    {
                        // Update the total weight of this connected node
                        weights[connection.connectedNode] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection.connectedNode, newCost);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection.connectedNode] = current;
                    }
                }
            }

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Dijkstra Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != null)
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Dijkstra Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node.gameObject.name;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }

        // Starting from the start node, returns a list of nodes representing a route to the ending node using the A Star Algorithm
        /// Searches every possible node from oldest to newest but queues nodes with less weight first + the heuristic, and recalculates routes if a faster way to a node is found. Guarantees the fastest route in shorter time
        public static List<Node> AStarSearch(Node start, Node end, float heuristicScale = 1)
        {
            // Check if we are missing the start node or end node
            if (start == null || end == null)
            {
                if (start == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the start node!");
                }
                else if (end == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the end node!");
                }

                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node with the A Star Search Algorithm.");

            // Initalize our frontier
            PriorityQueue<Node> frontier = new PriorityQueue<Node>();

            // Enqueue our start node
            frontier.Enqueue(start, 0);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to null in our route dictionary
            { start, null }
        };

            // Make a new dictionary that corresponds to the from dictionary's "to" nodes and store the total cost + weight to get to that node
            Dictionary<Node, float> weights = new Dictionary<Node, float>()
        {
            // Set our start node's cost to 0
            { start, 0 }
        };

            // Store our current value and number of loops
            Node current = null;
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

                // Loop through our current node's connections
                foreach (Connection connection in current.connections)
                {
                    // Store the new total cost of traveling this node
                    float newCost = weights[current] + connection.weight + connection.connectedNode.weight;

                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection.connectedNode) || newCost < weights[connection.connectedNode])
                    {
                        // Update the total weight of this connected node
                        weights[connection.connectedNode] = newCost;

                        // Enqueue our connected node to the frontier based on the heuristic function
                        frontier.Enqueue(connection.connectedNode, newCost + (Heuristic(connection.connectedNode, end) * heuristicScale * 2));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection.connectedNode] = current;
                    }
                }
            }

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using A Star Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != null)
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using A Star Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node.gameObject.name;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }

        // Calculates a priority value between two nodes from the given heuristic function
        /// The condition to determine whether an element is closer to the goal or not
        private static float Heuristic(Node current, Node end)
        {
            // HEURISTIC = Manhattan distance between two nodes multiplied by the default weight
            float xDistance = current.transform.position.x - end.transform.position.x;
            float yDistance = current.transform.position.y - end.transform.position.y;
            float zDistance = current.transform.position.z - end.transform.position.z;
            float heuristic = Mathf.Abs(xDistance) + Mathf.Abs(yDistance) + Mathf.Abs(zDistance);

            return heuristic;

            /*
            // HEURISTIC = Squared euclidean distance between two nodes
            float xDistance = current.transform.position.x - end.transform.position.x;
            float yDistance = current.transform.position.y - end.transform.position.y;
            float zDistance = current.transform.position.z - end.transform.position.z;
            float heuristic = xDistance * xDistance + yDistance * yDistance + zDistance * zDistance;

            return heuristic;
            */
        }


        // OTHER SEARCHING ALGORITHMS

        // Identical to Heuristic Search Algorithm
        /// Another name for the algorithm
        public static List<Node> GreedyBestFirstSearch(Node start, Node end)
        {
            // Check if we are missing the start node or end node
            if (start == null || end == null)
            {
                if (start == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the start node!");
                }
                else if (end == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the end node!");
                }

                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node with the Greedy Best First Search Algorithm.");

            // Initalize our frontier
            PriorityQueue<Node> frontier = new PriorityQueue<Node>();

            // Enqueue our start node
            frontier.Enqueue(start, 0);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to null in our route dictionary
            { start, null }
        };

            // Store our current value and number of loops
            Node current = null;
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

                // Loop through our current node's connections
                foreach (Connection connection in current.connections)
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection.connectedNode))
                    {
                        // Enqueue our connected node to the frontier based on the heuristic function
                        frontier.Enqueue(connection.connectedNode, Heuristic(connection.connectedNode, end));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection.connectedNode] = current;
                    }
                }
            }

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Greedy Best First Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != null)
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Greedy Best First Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node.gameObject.name;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }

        // Identical to Dijkstra's Search Algorithm
        /// Another name for the algorithm
        public static List<Node> UniformCostSearch(Node start, Node end)
        {
            // Check if we are missing the start node or end node
            if (start == null || end == null)
            {
                if (start == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the start node!");
                }
                else if (end == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the end node!");
                }

                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node with the Uniform Cost Search Algorithm.");

            // Initalize our frontier
            PriorityQueue<Node> frontier = new PriorityQueue<Node>();

            // Enqueue our start node
            frontier.Enqueue(start, 0);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to null in our route dictionary
            { start, null }
        };

            // Make a new dictionary that corresponds to the from dictionary's "to" nodes and store the total cost + weight to get to that node
            Dictionary<Node, float> weights = new Dictionary<Node, float>()
        {
            // Set our start node's cost to 0
            { start, 0 }
        };

            // Store our current value and number of loops
            Node current = null;
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

                // Loop through our current node's connections
                foreach (Connection connection in current.connections)
                {
                    // Store the new total cost of traveling this node
                    float newCost = weights[current] + connection.weight + connection.connectedNode.weight;

                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection.connectedNode) || newCost < weights[connection.connectedNode])
                    {
                        // Update the total weight of this connected node
                        weights[connection.connectedNode] = newCost;

                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection.connectedNode, newCost);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection.connectedNode] = current;
                    }
                }
            }

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Uniform Cost Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != null)
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Uniform Cost Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node.gameObject.name;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }

        // Starting from the start node, returns a list of nodes representing a route to the ending node using the Depth First Search Algorithm
        /// Searches every possible node starting from newest to oldest. Guarantees the fastest route but will search in an unconventional order
        public static List<Node> DepthFirstSearch(Node start, Node end)
        {
            // Check if we are missing the start node or end node
            if (start == null || end == null)
            {
                if (start == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the start node!");
                }
                else if (end == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the end node!");
                }

                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node with the Depth First Search Algorithm.");

            // Initalize our frontier
            LinkedList<Node> frontier = new LinkedList<Node>();

            // Enqueue our start node
            frontier.AddFirst(start);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to null in our route dictionary
            { start, null }
        };

            // Store our current value and number of loops
            Node current = null;
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
                current = frontier.First.Value;
                frontier.RemoveFirst();
                loopCount++;

                // Check if we made it to our goal
                if (current == end)
                {
                    break;
                }

                // Loop through our current node's connections
                foreach (Connection connection in current.connections)
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection.connectedNode))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.AddFirst(connection.connectedNode);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection.connectedNode] = current;
                    }
                }
            }

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Depth First Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != null)
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Depth First Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node.gameObject.name;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }

        // Starting from the start node, returns a list of nodes representing a route to the ending node using the Beam Search Algorithm
        /// Searches a narrow selection by only queueing up to a maximum value to the frontier. Completes quicker but can fail
        public static List<Node> BeamSearch(Node start, Node end, int beamWidth = 3)
        {
            // Check if we are missing the start node or end node
            if (start == null || end == null)
            {
                if (start == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the start node!");
                }
                else if (end == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the end node!");
                }

                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node with the Beam Search Algorithm.");

            // Initalize our frontier
            PriorityQueue<Node> frontier = new PriorityQueue<Node>();

            // Enqueue our start node
            frontier.Enqueue(start, 0);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to null in our route dictionary
            { start, null }
        };

            // Store our current value and number of loops
            Node current = null;
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

                // Loop through our current node's connections
                foreach (Connection connection in current.connections)
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection.connectedNode))
                    {
                        // Enqueue our connected node to the frontier
                        frontier.Enqueue(connection.connectedNode, 0);

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection.connectedNode] = current;
                    }
                }

                // Remove nodes in our frontier until the frontier is less than or equal to the beam width
                if (frontier.Queue.Count > beamWidth)
                {
                    PriorityQueue<Node> heuristicSort = new PriorityQueue<Node>();
                    foreach (PriorityQueueElement<Node> node in frontier.Queue)
                    {
                        heuristicSort.Enqueue(node.data, Heuristic(node.data, end));
                    }

                    while (heuristicSort.Queue.Count > beamWidth)
                    {
                        frontier.Queue.Remove(heuristicSort.Queue.Last.Value);
                        heuristicSort.Queue.RemoveLast();
                    }
                }
            }

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Beam Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != null)
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Beam Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node.gameObject.name;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }

        // Starting from the start node, returns a list of nodes representing a route to the ending node using the Shun Search Algorithm (DO NOT USE)
        /// Deliberately searches other nodes before nodes considered to be closer to the goal by the heuristic. Maximizes the time to complete the search
        public static List<Node> ShunSearch(Node start, Node end)
        {
            Debug.LogWarning("The Shun Search Algorithm applies last in first out with heuristic queueing so that it intentionally ignores the heuristic. This function will try to find every route before finding the goal");

            // Check if we are missing the start node or end node
            if (start == null || end == null)
            {
                if (start == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the start node!");
                }
                else if (end == null)
                {
                    Debug.LogError("Could not calculate a route! Missing the end node!");
                }

                return new List<Node>();
            }

            // Check if the start and end node are identical
            if (start == end)
            {
                Debug.LogWarning("Could not calculate a route! Start and end are identical!");
                return new List<Node>();
            }

            Debug.Log("Calculating a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node with the Shun Search Algorithm.");

            // Initalize our frontier
            PriorityQueue<Node> frontier = new PriorityQueue<Node>();

            // Enqueue our start node
            frontier.Enqueue(start, 0);

            // Make a dictionary to store each node's node before it (which will eventually store the route from the end node to the start)
            // KEY = TO  VALUE = FROM
            // from[currentNode] = the node immediately before currentNode
            Dictionary<Node, Node> from = new Dictionary<Node, Node>
        {
            // Set our start node's value to null in our route dictionary
            { start, null }
        };

            // Store our current value and number of loops
            Node current = null;
            int loopCount = -1;

            // Loop until our frontier is empty
            while (frontier.Queue.Count > 0)
            {
                // Loop check
                if (loopCount > maxLoops)
                {
                    break;
                }

                // Dequeue our latest node and increment our number of loops
                current = frontier.Queue.Last.Value.data;
                frontier.Queue.RemoveLast();
                loopCount++;

                // Check if we made it to our goal
                if (current == end)
                {
                    break;
                }

                // Loop through our current node's connections
                foreach (Connection connection in current.connections)
                {
                    // Check that our connected node is not currently in our dictionary
                    if (!from.ContainsKey(connection.connectedNode))
                    {
                        // Enqueue our connected node to the frontier based on the heuristic function
                        frontier.Enqueue(connection.connectedNode, Heuristic(connection.connectedNode, end));

                        // Add our connected node as our key and our current node as our value to the dictionary
                        from[connection.connectedNode] = current;
                    }
                }
            }

            // Check that we made it to our end node
            if (current != end)
            {
                Debug.LogWarning("Could not calculate a route from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Shun Search!");

                return null;
            }

            // Store our route
            List<Node> route = new List<Node>();

            // Build our final route through our dictionary's connections
            while (from[current] != null)
            {
                // Add our current node to the route
                route.Add(current);

                // Set our current node to the previous node
                current = from[current];
            }

            // Reverse our route so that the end node is last
            route.Reverse();

            string log = "A route was successfully calculated from " + start.gameObject.name + "'s node to " + end.gameObject.name + "'s node using Shun Search! The search lasted a total of " + loopCount + " loops. The route is as follows:";

            // Print our route
            foreach (Node node in route)
            {
                log += " " + node.gameObject.name;
            }

            Debug.Log(log + ". The length of the route is " + route.Count + " nodes long.");

            // Return our final route
            return route;
        }
    }
}
