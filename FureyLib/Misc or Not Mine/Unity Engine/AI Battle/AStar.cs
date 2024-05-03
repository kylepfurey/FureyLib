
// AI Battle - A Star Pathfinding Function Script
// by Kyle Furey, AI Battle game made by Dave Carrigg

namespace AIBattle
{
    namespace AITeam
    {
        using System.Collections.Generic;
        using UnityEngine;

        // Define the grid nodes
        using Node = UnityEngine.Vector2Int;

        // A Star Search Algorithm customized for AI Battle.
        public static class AStar
        {
            private const int maxLoops = 300;

            // Starting from the start node, returns a list of nodes representing a route to the ending node using the A Star Algorithm (customized for AI Battle)
            /// Searches every possible node from oldest to newest but queues nodes with less weight first + the heuristic, and recalculates routes if a faster way to a node is found. Guarantees the fastest route in shorter time
            public static List<Node> Search(Node start, Node end, List<Node> availableSpaces, List<Node> occupiedSpaces)
            {
                // Check if the start and end node are identical
                if (start == end)
                {
                    return new List<Node>();
                }

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

                    // Check right
                    connection = current + new Node(1, 0);

                    // Store the new total cost of traveling this node
                    newCost = weights[current];

                    if (availableSpaces.Contains(connection) && (occupiedSpaces == null || !occupiedSpaces.Contains(connection)))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection) || newCost < weights[connection])
                        {
                            // Update the total weight of this connected node
                            weights[connection] = newCost;

                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, newCost + Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check left
                    connection = current + new Node(-1, 0);

                    // Store the new total cost of traveling this node
                    newCost = weights[current];

                    if (availableSpaces.Contains(connection) && (occupiedSpaces == null || !occupiedSpaces.Contains(connection)))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection) || newCost < weights[connection])
                        {
                            // Update the total weight of this connected node
                            weights[connection] = newCost;

                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, newCost + Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check up
                    connection = current + new Node(0, 1);

                    // Store the new total cost of traveling this node
                    newCost = weights[current];

                    if (availableSpaces.Contains(connection) && (occupiedSpaces == null || !occupiedSpaces.Contains(connection)))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection) || newCost < weights[connection])
                        {
                            // Update the total weight of this connected node
                            weights[connection] = newCost;

                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, newCost + Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }

                    // Check down
                    connection = current + new Node(0, -1);

                    // Store the new total cost of traveling this node
                    newCost = weights[current];

                    if (availableSpaces.Contains(connection) && (occupiedSpaces == null || !occupiedSpaces.Contains(connection)))
                    {
                        // Check that our connected node is not currently in our dictionary
                        if (!from.ContainsKey(connection) || newCost < weights[connection])
                        {
                            // Update the total weight of this connected node
                            weights[connection] = newCost;

                            // Enqueue our connected node to the frontier
                            frontier.Enqueue(connection, newCost + Heuristic(connection, end));

                            // Add our connected node as our key and our current node as our value to the dictionary
                            from[connection] = current;
                        }
                    }
                }

                // Check that we made it to our end node
                if (current != end)
                {
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

                // Return our final route
                return route;
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
        }

        // A first in first out list of a specified data type with an associated priority value assigned to each element used for adding and removing data in a specific order.
        public class PriorityQueue<DataType>
        {
            // The list of nodes in queue in order of oldest to newest and lowest priority to highest priority
            public LinkedList<PriorityQueueElement<DataType>> Queue = new LinkedList<PriorityQueueElement<DataType>>();

            // Add a new node to the queue
            public void Enqueue(PriorityQueueElement<DataType> enqueuedNode)
            {
                // Find the first node with a greater priority
                foreach (PriorityQueueElement<DataType> Node in Queue)
                {
                    if (enqueuedNode.priority < Node.priority)
                    {
                        // Add the node to the queue right before the next node
                        Queue.AddBefore(Queue.Find(Node), enqueuedNode);

                        return;
                    }
                }

                // Add the enqueued node to the end of the list
                Queue.AddLast(enqueuedNode);
            }

            // Add a new node to the queue
            public void Enqueue(DataType data, float priority)
            {
                // Make an element from the data and priority
                PriorityQueueElement<DataType> enqueuedNode = new PriorityQueueElement<DataType>();
                enqueuedNode.data = data; enqueuedNode.priority = priority;

                // Enqueue node
                Enqueue(enqueuedNode);
            }

            // Removes the oldest node with the lowest priority and return the removed node
            public DataType Dequeue()
            {
                // Check if the queue is empty
                if (Queue.Count == 0)
                {
                    return default(DataType);
                }

                // Store the oldest node with the lowest priority
                PriorityQueueElement<DataType> dequeuedNode = Queue.First.Value;

                // Remove the oldest node with the lowest priority from the queue
                Queue.Remove(dequeuedNode);

                // Return our removed node
                return dequeuedNode.data;
            }

            // Add a new node to the queue (identical to enqueue)
            public void Push(PriorityQueueElement<DataType> enqueuedNode)
            {
                // Find the first node with a greater priority
                foreach (PriorityQueueElement<DataType> Node in Queue)
                {
                    if (enqueuedNode.priority < Node.priority)
                    {
                        // Add the node to the queue right before the next node
                        Queue.AddBefore(Queue.Find(Node), enqueuedNode);

                        return;
                    }
                }

                // Add the enqueued node to the end of the list
                Queue.AddLast(enqueuedNode);
            }

            // Add a new node to the queue (identical to enqueue)
            public void Push(DataType data, float priority)
            {
                // Make an element from the data and priority
                PriorityQueueElement<DataType> enqueuedNode = new PriorityQueueElement<DataType>();
                enqueuedNode.data = data; enqueuedNode.priority = priority;

                // Enqueue node
                Enqueue(enqueuedNode);
            }

            // Removes the oldest node with the lowest priority and return the removed node (identical to dequeue)
            public DataType Pop()
            {
                // Check if the queue is empty
                if (Queue.Count == 0)
                {
                    return default(DataType);
                }

                // Store the oldest node with the lowest priority
                PriorityQueueElement<DataType> dequeuedNode = Queue.First.Value;

                // Remove the oldest node with the lowest priority from the queue
                Queue.Remove(dequeuedNode);

                // Return our removed node
                return dequeuedNode.data;
            }
        }

        // A member of the priority queue consisting of a data type value and its priority.
        public class PriorityQueueElement<DataType>
        {
            // The node in the queue
            public DataType data;

            // The priority of the corresponding node
            public float priority = 0;
        }
    }
}
