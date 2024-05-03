
// AI Battle - AI Map Information Script
// by Kyle Furey, AI Battle game made by Dave Carrigg

namespace AIBattle
{
    namespace AITeam
    {
        using System;
        using System.Collections.Generic;
        using UnityEngine;

        // Define the grid nodes
        using Node = UnityEngine.Vector2Int;

        // Stores the map information of what an AI has discovered to decide what to do next.
        public class AIBrain
        {
            // SETTINGS

            // Whether the AI team shares the same information
            public const bool shareTeamInformation = true;

            // Whether the AI team attempts to link their maps
            public const bool linkMaps = true;

            // Whether to link an AI based on similar spaces
            public const bool heuristicLink = false;

            // The minimum number of matching adjacent spaces for two locations to be considered linked
            public const int minimumSimilarities = 4;

            // The maximum number of matching adjacent walls before two locations are not considered linked
            public const int maximumWalls = 1;

            // Whether to explode the AI on a linking failure
            public const bool explodeOnFailure = false;

            // The time to drop bombs with for enemies
            public const int enemyBombDropTime = 1;

            // The remaining time assumed for bombs that have not been discovered
            public const int unknownBombTime = 3;


            // INDEPENDENT DATA

            // This AI's class
            public AIClass classType = AIClass.NULL;

            // The current coordinates of this AI (relative to the AI's starting point)
            public Node currentPosition = Node.zero;

            // The previous coordinates of this AI (relative to the AI's starting point)
            public Node previousPosition = Node.zero;

            // Whether it is this AI's first turn
            public bool firstTurn = true;

            // The current sensor data
            public MapSpace sensorData = null;

            // The list of this AI's available spaces
            public List<Node> available = new List<Node>();

            // The list of this AI's unexplored positions
            public List<Node> unexplored = new List<Node>();

            // The discovered map spaces and what position they are located (relative to the AI's starting point)
            public Dictionary<Node, MapSpace> map = new Dictionary<Node, MapSpace>();

            // The list of occupied map spaces (relative to the AI's starting point)
            public List<Node> occupied = new List<Node>();

            // The list of bomb spaces (relative to the AI's starting point)
            public Dictionary<Node, int> bombs = new Dictionary<Node, int>();

            // Whether this AI is currently holding the key
            public bool hasKey = false;

            // The position of the exit if it has been found
            public Node exit = Node.zero;
            public bool foundExit = false;


            // TEAM DATA

            // The index of this AI as part of its team
            public int index = -1;
            public bool hasRegistered = false;
            public bool puppet = false;

            // Whether this AI has already linked its map to the team map
            public bool hasLinked = false;

            // Whether unlinked AI should compare with the team map (as comparing with other AI can be less accurate than the now updated team map)
            public static bool linkWithTeam = false;

            // The list of all AIs apart of this team
            public static List<AIBase> team = new List<AIBase>();
            public static List<AIClass> classes = new List<AIClass>();

            // The current team index that must be passed in order to track which AI have died
            public static int passIndex = 0;
            public static bool canPass = false;

            // The list of this AI's available spaces
            public static List<Node> teamAvailable = new List<Node>();

            // The list of all unexplored positions
            public static List<Node> teamUnexplored = new List<Node>();

            // All discovered map spaces and what position they are located at (relative to the first linked AI's starting point)
            public static Dictionary<Node, MapSpace> teamMap = new Dictionary<Node, MapSpace>();

            // The list of all occupied map spaces (relative to the first linked AI's starting point)
            public static List<Node> teamOccupied = new List<Node>();

            // The list of all bomb spaces (relative to the first AI's linked starting point)
            public static Dictionary<Node, int> teamBombs = new Dictionary<Node, int>();

            // Whether an AI on this team is currently holding the key
            public static bool teamHasKey = false;

            // Data used to recover a key when a key is lost
            public static Node keyPosition = Node.zero;
            public static bool lostKey = false;

            // The position of the exit if it has been found by the team
            public static Node teamExit = Node.zero;
            public static bool teamFoundExit = false;

            // Whether AI will attempt to attack each other (automatically turns on when all spaces are discovered)
            public static bool friendlyFire = false;


            // INDEPENDENT FUNCTIONS

            // Registers this AI in the team if it has not been registered yet
            public void RegisterAI(AIBase AI)
            {
                // Check if the AI has not been registered
                if (!hasRegistered)
                {
                    if (AI == null)
                    {
                        Debug.LogError("The RegisterAI function's AI parameter must be set to the AI that owns the brain! Put the 'this' keyword as the parameter!");

                        return;
                    }

                    if (shareTeamInformation)
                    {
                        index = team.Count;

                        team.Add(AI);

                        classes.Add(classType);
                    }

                    hasRegistered = true;
                }
                else if (!canPass)
                {
                    Debug.Log("Found " + team.Count + " members of AI Team! FIGHT!");

                    canPass = true;
                }
            }

            // Converts a list of nodes into a list of movements
            public List<GameManager.Direction> GetMovements(List<Node> nodes)
            {
                // Check if the nodes are empty
                if (nodes == null)
                {
                    return null;
                }

                // Store the list of directions
                List<GameManager.Direction> movements = new List<GameManager.Direction>();

                // Add the current position as the first node in the list
                nodes.Insert(0, currentPosition);

                // Loop through each node
                for (int i = 0; i < nodes.Count; i++)
                {
                    // Skip the last node
                    if (i == nodes.Count - 1)
                    {
                        break;
                    }

                    if (nodes[i] + new Node(0, 1) == nodes[i + 1])
                    {
                        // Up
                        movements.Add(GameManager.Direction.Up);
                    }
                    else if (nodes[i] + new Node(0, -1) == nodes[i + 1])
                    {
                        // Down
                        movements.Add(GameManager.Direction.Down);
                    }
                    else if (nodes[i] + new Node(-1, 0) == nodes[i + 1])
                    {
                        // Left
                        movements.Add(GameManager.Direction.Left);
                    }
                    else if (nodes[i] + new Node(1, 0) == nodes[i + 1])
                    {
                        // Right
                        movements.Add(GameManager.Direction.Right);
                    }
                    else
                    {
                        // The path broke!
                        Debug.LogError("The path generated for the AI did not meet the requirement of only having directly adjacent nodes!");

                        return null;
                    }
                }

                // Return the list of movements
                return movements;
            }

            // Pass the current team index to check if the previous AI died
            public void PassIndex()
            {
                // Check that we are sharing team information
                if (shareTeamInformation && canPass && team.Count >= passIndex + 1)
                {
                    // Check that it is supposed to be our turn
                    if (passIndex != index)
                    {
                        Debug.Log("AI " + team[passIndex].AIName + " has been found dead!");

                        // Remove the previous AI from the team and notify other AI
                        RemoveAI(passIndex);

                        // Reset the pass index
                        passIndex = index;
                    }

                    // Pass the index
                    passIndex++;

                    if (passIndex >= team.Count)
                    {
                        passIndex = 0;
                    }
                }
            }


            // TEAM FUNCTIONS

            // Links each of the AI's maps together as best as they can to update the team map
            public void LinkMaps()
            {
                // Check if there are differing maps to be linked
                if (shareTeamInformation && linkMaps && !hasLinked && team.Count > 1)
                {
                    // Check whether we should link with the team or another AI
                    if (linkWithTeam)
                    {
                        // Check if both AI have found the exit
                        if (foundExit && teamFoundExit)
                        {
                            Debug.Log("AI " + Enum.GetName(typeof(AIClass), classType) + " LINKED WITH TEAM!");

                            // Offset all of this AI's positions
                            OffsetPositions(teamExit - exit);

                            // Link the AI's positions
                            UpdateTeamData(this);

                            // Complete the AI link
                            CompleteLink(this);

                            // Stop linking
                            return;
                        }

                        // Check for nearby teammates with the key

                        // Check up
                        if (teamHasKey && MapSpace.SpaceContains(sensorData.up, GameManager.SensorData.Diamond) && !lostKey)
                        {
                            for (int i = 0; i < team.Count; i++)
                            {
                                if (i == index)
                                {
                                    continue;
                                }

                                if (team[i].brain.hasKey)
                                {
                                    Debug.Log("AI " + Enum.GetName(typeof(AIClass), classType) + " LINKED WITH TEAM!");

                                    // Offset all of this AI's positions
                                    OffsetPositions((i > index ? team[i].brain.currentPosition : team[i].brain.previousPosition) - currentPosition + new Node(0, -1));

                                    // Link the AI's positions
                                    UpdateTeamData(this);

                                    // Complete the AI link
                                    CompleteLink(this);

                                    // Stop linking
                                    return;
                                }
                            }
                        }

                        // Check down
                        if (teamHasKey && MapSpace.SpaceContains(sensorData.down, GameManager.SensorData.Diamond) && !lostKey)
                        {
                            for (int i = 0; i < team.Count; i++)
                            {
                                if (i == index)
                                {
                                    continue;
                                }

                                if (team[i].brain.hasKey)
                                {
                                    Debug.Log("AI " + Enum.GetName(typeof(AIClass), classType) + " LINKED WITH TEAM!");

                                    // Offset all of this AI's positions
                                    OffsetPositions((i > index ? team[i].brain.currentPosition : team[i].brain.previousPosition) - currentPosition + new Node(0, 1));

                                    // Link the AI's positions
                                    UpdateTeamData(this);

                                    // Complete the AI link
                                    CompleteLink(this);

                                    // Stop linking
                                    return;
                                }
                            }
                        }

                        // Check left
                        if (teamHasKey && MapSpace.SpaceContains(sensorData.left, GameManager.SensorData.Diamond) && !lostKey)
                        {
                            for (int i = 0; i < team.Count; i++)
                            {
                                if (i == index)
                                {
                                    continue;
                                }

                                if (team[i].brain.hasKey)
                                {
                                    Debug.Log("AI " + Enum.GetName(typeof(AIClass), classType) + " LINKED WITH TEAM!");

                                    // Offset all of this AI's positions
                                    OffsetPositions((i > index ? team[i].brain.currentPosition : team[i].brain.previousPosition) - currentPosition + new Node(1, 0));

                                    // Link the AI's positions
                                    UpdateTeamData(this);

                                    // Complete the AI link
                                    CompleteLink(this);

                                    // Stop linking
                                    return;
                                }
                            }
                        }

                        // Check right
                        if (teamHasKey && MapSpace.SpaceContains(sensorData.right, GameManager.SensorData.Diamond) && !lostKey)
                        {
                            for (int i = 0; i < team.Count; i++)
                            {
                                if (i == index)
                                {
                                    continue;
                                }

                                if (team[i].brain.hasKey)
                                {
                                    Debug.Log("AI " + Enum.GetName(typeof(AIClass), classType) + " LINKED WITH TEAM!");

                                    // Offset all of this AI's positions
                                    OffsetPositions((i > index ? team[i].brain.currentPosition : team[i].brain.previousPosition) - currentPosition + new Node(-1, 0));

                                    // Link the AI's positions
                                    UpdateTeamData(this);

                                    // Complete the AI link
                                    CompleteLink(this);

                                    // Stop linking
                                    return;
                                }
                            }
                        }

                        if (heuristicLink)
                        {
                            // Compare the map of this AI with the team's map
                            foreach (Node mapPosition in teamMap.Keys)
                            {
                                // Check if two spaces match up
                                if (map[currentPosition].SpaceEquals(teamMap[mapPosition]))
                                {
                                    int similarities = 0;
                                    int walls = 0;

                                    // Check up
                                    if ((map.ContainsKey(currentPosition + new Node(0, 1)) && teamMap.ContainsKey(mapPosition + new Node(0, 1))) ||
                                    (occupied.Contains(currentPosition + new Node(0, 1)) && teamOccupied.Contains(mapPosition + new Node(0, 1))))
                                    {
                                        // Check for a match
                                        if ((occupied.Contains(currentPosition + new Node(0, 1)) && teamOccupied.Contains(mapPosition + new Node(0, 1))) ||
                                        (map[currentPosition + new Node(0, 1)].SpaceEquals(teamMap[mapPosition + new Node(0, 1)])))
                                        {
                                            // Increment the number of similarities 
                                            similarities++;

                                            // Check if the space is an occupied space
                                            if (occupied.Contains(currentPosition + new Node(0, 1)) && teamOccupied.Contains(mapPosition + new Node(0, 1)))
                                            {
                                                // Increment the number of walls
                                                walls++;

                                                // Check if there are too many walls for an accurate check
                                                if (walls > maximumWalls)
                                                {
                                                    // Two spaces do not match, move on to the next position
                                                    continue;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            // Two spaces do not match, move on to the next position
                                            continue;
                                        }
                                    }

                                    // Check down
                                    if ((map.ContainsKey(currentPosition + new Node(0, -1)) && teamMap.ContainsKey(mapPosition + new Node(0, -1))) ||
                                    (occupied.Contains(currentPosition + new Node(0, -1)) && teamOccupied.Contains(mapPosition + new Node(0, -1))))
                                    {
                                        // Check for a match
                                        if ((occupied.Contains(currentPosition + new Node(0, -1)) && teamOccupied.Contains(mapPosition + new Node(0, -1))) ||
                                        (map[currentPosition + new Node(0, -1)].SpaceEquals(teamMap[mapPosition + new Node(0, -1)])))
                                        {
                                            // Increment the number of similarities 
                                            similarities++;

                                            // Check if the space is an occupied space
                                            if (occupied.Contains(currentPosition + new Node(0, -1)) && teamOccupied.Contains(mapPosition + new Node(0, -1)))
                                            {
                                                // Increment the number of walls
                                                walls++;

                                                // Check if there are too many walls for an accurate check
                                                if (walls > maximumWalls)
                                                {
                                                    // Two spaces do not match, move on to the next position
                                                    continue;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            // Two spaces do not match, move on to the next position
                                            continue;
                                        }
                                    }

                                    // Check left
                                    if ((map.ContainsKey(currentPosition + new Node(-1, 0)) && teamMap.ContainsKey(mapPosition + new Node(-1, 0))) ||
                                    (occupied.Contains(currentPosition + new Node(-1, 0)) && teamOccupied.Contains(mapPosition + new Node(-1, 0))))
                                    {
                                        // Check for a match
                                        if ((occupied.Contains(currentPosition + new Node(-1, 0)) && teamOccupied.Contains(mapPosition + new Node(-1, 0))) ||
                                        (map[currentPosition + new Node(-1, 0)].SpaceEquals(teamMap[mapPosition + new Node(-1, 0)])))
                                        {
                                            // Increment the number of similarities 
                                            similarities++;

                                            // Check if the space is an occupied space
                                            if (occupied.Contains(currentPosition + new Node(-1, 0)) && teamOccupied.Contains(mapPosition + new Node(-1, 0)))
                                            {
                                                // Increment the number of walls
                                                walls++;

                                                // Check if there are too many walls for an accurate check
                                                if (walls > maximumWalls)
                                                {
                                                    // Two spaces do not match, move on to the next position
                                                    continue;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            // Two spaces do not match, move on to the next position
                                            continue;
                                        }
                                    }

                                    // Check right
                                    if ((map.ContainsKey(currentPosition + new Node(1, 0)) && teamMap.ContainsKey(mapPosition + new Node(1, 0))) ||
                                    (occupied.Contains(currentPosition + new Node(1, 0)) && teamOccupied.Contains(mapPosition + new Node(1, 0))))
                                    {
                                        // Check for a match
                                        if ((occupied.Contains(currentPosition + new Node(1, 0)) && teamOccupied.Contains(mapPosition + new Node(1, 0))) ||
                                        (map[currentPosition + new Node(1, 0)].SpaceEquals(teamMap[mapPosition + new Node(1, 0)])))
                                        {
                                            // Increment the number of similarities 
                                            similarities++;

                                            // Check if the space is an occupied space
                                            if (occupied.Contains(currentPosition + new Node(1, 0)) && teamOccupied.Contains(mapPosition + new Node(1, 0)))
                                            {
                                                // Increment the number of walls
                                                walls++;

                                                // Check if there are too many walls for an accurate check
                                                if (walls > maximumWalls)
                                                {
                                                    // Two spaces do not match, move on to the next position
                                                    continue;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            // Two spaces do not match, move on to the next position
                                            continue;
                                        }
                                    }

                                    // Check if the link is viable
                                    if (similarities >= minimumSimilarities)
                                    {
                                        Debug.Log("AI " + Enum.GetName(typeof(AIClass), classType) + " LINKED WITH TEAM!");

                                        // Offset all of this AI's positions
                                        OffsetPositions(mapPosition - currentPosition);

                                        // Link the AI's positions
                                        UpdateTeamData(this);

                                        // Complete the AI link
                                        CompleteLink(this);

                                        // Stop looping
                                        return;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        // Check for nearby teammates with the key

                        // Check up
                        if (teamHasKey && MapSpace.SpaceContains(sensorData.up, GameManager.SensorData.Diamond) && !lostKey)
                        {
                            for (int i = 0; i < team.Count; i++)
                            {
                                if (i == index)
                                {
                                    continue;
                                }

                                if (team[i].brain.hasKey)
                                {
                                    Debug.Log("AI " + team[index].AIName + " LINKED WITH AI " + team[i].AIName + "!");

                                    // Offset all of this AI's positions
                                    OffsetPositions((i > index ? team[i].brain.currentPosition : team[i].brain.previousPosition) - currentPosition + new Node(0, -1));

                                    // Link the AI's positions
                                    UpdateTeamData(this);

                                    // Link the other AI's positions
                                    UpdateTeamData(team[i].brain);

                                    // Complete the AI link
                                    CompleteLink(this);

                                    // Complete the other AI's link
                                    CompleteLink(team[i].brain);

                                    // Stop linking
                                    return;
                                }
                            }
                        }

                        // Check down
                        if (teamHasKey && MapSpace.SpaceContains(sensorData.down, GameManager.SensorData.Diamond) && !lostKey)
                        {
                            for (int i = 0; i < team.Count; i++)
                            {
                                if (i == index)
                                {
                                    continue;
                                }

                                if (team[i].brain.hasKey)
                                {
                                    Debug.Log("AI " + team[index].AIName + " LINKED WITH AI " + team[i].AIName + "!");

                                    // Offset all of this AI's positions
                                    OffsetPositions((i > index ? team[i].brain.currentPosition : team[i].brain.previousPosition) - currentPosition + new Node(0, 1));

                                    // Link the AI's positions
                                    UpdateTeamData(this);

                                    // Link the other AI's positions
                                    UpdateTeamData(team[i].brain);

                                    // Complete the AI link
                                    CompleteLink(this);

                                    // Complete the other AI's link
                                    CompleteLink(team[i].brain);

                                    // Stop linking
                                    return;
                                }
                            }
                        }

                        // Check left
                        if (teamHasKey && MapSpace.SpaceContains(sensorData.left, GameManager.SensorData.Diamond) && !lostKey)
                        {
                            for (int i = 0; i < team.Count; i++)
                            {
                                if (i == index)
                                {
                                    continue;
                                }

                                if (team[i].brain.hasKey)
                                {
                                    Debug.Log("AI " + team[index].AIName + " LINKED WITH AI " + team[i].AIName + "!");

                                    // Offset all of this AI's positions
                                    OffsetPositions((i > index ? team[i].brain.currentPosition : team[i].brain.previousPosition) - currentPosition + new Node(1, 0));

                                    // Link the AI's positions
                                    UpdateTeamData(this);

                                    // Link the other AI's positions
                                    UpdateTeamData(team[i].brain);

                                    // Complete the AI link
                                    CompleteLink(this);

                                    // Complete the other AI's link
                                    CompleteLink(team[i].brain);

                                    // Stop linking
                                    return;
                                }
                            }
                        }

                        // Check right
                        if (teamHasKey && MapSpace.SpaceContains(sensorData.right, GameManager.SensorData.Diamond) && !lostKey)
                        {
                            for (int i = 0; i < team.Count; i++)
                            {
                                if (i == index)
                                {
                                    continue;
                                }

                                if (team[i].brain.hasKey)
                                {
                                    Debug.Log("AI " + team[index].AIName + " LINKED WITH AI " + team[i].AIName + "!");

                                    // Offset all of this AI's positions
                                    OffsetPositions((i > index ? team[i].brain.currentPosition : team[i].brain.previousPosition) - currentPosition + new Node(-1, 0));

                                    // Link the AI's positions
                                    UpdateTeamData(this);

                                    // Link the other AI's positions
                                    UpdateTeamData(team[i].brain);

                                    // Complete the AI link
                                    CompleteLink(this);

                                    // Complete the other AI's link
                                    CompleteLink(team[i].brain);

                                    // Stop linking
                                    return;
                                }
                            }
                        }

                        // Compare the map of this AI with each of the team's map
                        for (int i = 0; i < team.Count; i++)
                        {
                            // Ignore the same AI
                            if (i == index)
                            {
                                continue;
                            }

                            // Check if both AI have found the exit
                            if (foundExit && team[i].brain.foundExit)
                            {
                                Debug.Log("AI " + team[index].AIName + " LINKED WITH AI " + team[i].AIName + "!");

                                // Offset all of this AI's positions
                                OffsetPositions(team[i].brain.exit - exit);

                                // Link the AI's positions
                                UpdateTeamData(this);

                                // Link the other AI's positions
                                UpdateTeamData(team[i].brain);

                                // Complete the AI link
                                CompleteLink(this);

                                // Complete the other AI's link
                                CompleteLink(team[i].brain);

                                // Stop linking
                                return;
                            }

                            if (heuristicLink)
                            {
                                foreach (Node mapPosition in team[i].brain.map.Keys)
                                {
                                    // Check if two spaces match up
                                    if (map[currentPosition].SpaceEquals(team[i].brain.map[mapPosition]))
                                    {
                                        int similarities = 0;
                                        int walls = 0;

                                        // Check up
                                        if ((map.ContainsKey(currentPosition + new Node(0, 1)) && team[i].brain.map.ContainsKey(mapPosition + new Node(0, 1))) ||
                                        (occupied.Contains(currentPosition + new Node(0, 1)) && team[i].brain.occupied.Contains(mapPosition + new Node(0, 1))))
                                        {
                                            // Check for a match
                                            if ((occupied.Contains(currentPosition + new Node(0, 1)) && team[i].brain.occupied.Contains(mapPosition + new Node(0, 1)) ||
                                            (map[currentPosition + new Node(0, 1)].SpaceEquals(team[i].brain.map[mapPosition + new Node(0, 1)]))))
                                            {
                                                // Increment the number of similarities 
                                                similarities++;

                                                // Check if the space is an occupied space
                                                if (occupied.Contains(currentPosition + new Node(0, 1)) && team[i].brain.occupied.Contains(mapPosition + new Node(0, 1)))
                                                {
                                                    // Increment the number of walls
                                                    walls++;

                                                    // Check if there are too many walls for an accurate check
                                                    if (walls > maximumWalls)
                                                    {
                                                        // Two spaces do not match, move on to the next position
                                                        continue;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                // Two spaces do not match, move on to the next position
                                                continue;
                                            }
                                        }

                                        // Check down
                                        if ((map.ContainsKey(currentPosition + new Node(0, -1)) && team[i].brain.map.ContainsKey(mapPosition + new Node(0, -1))) ||
                                        (occupied.Contains(currentPosition + new Node(0, -1)) && team[i].brain.occupied.Contains(mapPosition + new Node(0, -1))))
                                        {
                                            // Check for a match
                                            if ((occupied.Contains(currentPosition + new Node(0, -1)) && team[i].brain.occupied.Contains(mapPosition + new Node(0, -1))) ||
                                            (map[currentPosition + new Node(0, -1)].SpaceEquals(team[i].brain.map[mapPosition + new Node(0, -1)])))
                                            {
                                                // Increment the number of similarities 
                                                similarities++;

                                                // Check if the space is an occupied space
                                                if (occupied.Contains(currentPosition + new Node(0, -1)) && team[i].brain.occupied.Contains(mapPosition + new Node(0, -1)))
                                                {
                                                    // Increment the number of walls
                                                    walls++;

                                                    // Check if there are too many walls for an accurate check
                                                    if (walls > maximumWalls)
                                                    {
                                                        // Two spaces do not match, move on to the next position
                                                        continue;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                // Two spaces do not match, move on to the next position
                                                continue;
                                            }
                                        }

                                        // Check left
                                        if ((map.ContainsKey(currentPosition + new Node(-1, 0)) && team[i].brain.map.ContainsKey(mapPosition + new Node(-1, 0))) ||
                                        (occupied.Contains(currentPosition + new Node(-1, 0)) && team[i].brain.occupied.Contains(mapPosition + new Node(-1, 0))))
                                        {
                                            // Check for a match
                                            if ((occupied.Contains(currentPosition + new Node(-1, 0)) && team[i].brain.occupied.Contains(mapPosition + new Node(-1, 0))) ||
                                            (map[currentPosition + new Node(-1, 0)].SpaceEquals(team[i].brain.map[mapPosition + new Node(-1, 0)])))
                                            {
                                                // Increment the number of similarities 
                                                similarities++;

                                                // Check if the space is an occupied space
                                                if (occupied.Contains(currentPosition + new Node(-1, 0)) && team[i].brain.occupied.Contains(mapPosition + new Node(-1, 0)))
                                                {
                                                    // Increment the number of walls
                                                    walls++;

                                                    // Check if there are too many walls for an accurate check
                                                    if (walls > maximumWalls)
                                                    {
                                                        // Two spaces do not match, move on to the next position
                                                        continue;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                // Two spaces do not match, move on to the next position
                                                continue;
                                            }
                                        }

                                        // Check right
                                        if ((map.ContainsKey(currentPosition + new Node(1, 0)) && team[i].brain.map.ContainsKey(mapPosition + new Node(1, 0))) ||
                                        (occupied.Contains(currentPosition + new Node(1, 0)) && team[i].brain.occupied.Contains(mapPosition + new Node(1, 0))))
                                        {
                                            // Check for a match
                                            if ((occupied.Contains(currentPosition + new Node(1, 0)) && team[i].brain.occupied.Contains(mapPosition + new Node(1, 0))) ||
                                            (map[currentPosition + new Node(1, 0)].SpaceEquals(team[i].brain.map[mapPosition + new Node(1, 0)])))
                                            {
                                                // Increment the number of similarities 
                                                similarities++;

                                                // Check if the space is an occupied space
                                                if (occupied.Contains(currentPosition + new Node(1, 0)) && team[i].brain.occupied.Contains(mapPosition + new Node(1, 0)))
                                                {
                                                    // Increment the number of walls
                                                    walls++;

                                                    // Check if there are too many walls for an accurate check
                                                    if (walls > maximumWalls)
                                                    {
                                                        // Two spaces do not match, move on to the next position
                                                        continue;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                // Two spaces do not match, move on to the next position
                                                continue;
                                            }
                                        }

                                        // Check if the link is viable
                                        if (similarities >= minimumSimilarities)
                                        {
                                            Debug.Log("AI " + team[index].AIName + " LINKED WITH AI " + team[i].AIName + "!");

                                            // Offset all of this AI's positions
                                            OffsetPositions(mapPosition - currentPosition);

                                            // Link the AI's positions
                                            UpdateTeamData(this);

                                            // Link the other AI's positions
                                            UpdateTeamData(team[i].brain);

                                            // Complete the AI link
                                            CompleteLink(this);

                                            // Complete the other AI's link
                                            CompleteLink(team[i].brain);

                                            // Stop looping
                                            return;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Offset each of the known map positions by the given offset (used to properly link map coordinates of linked maps)
            public void OffsetPositions(Node deltaOffset)
            {
                // Update positions
                currentPosition += deltaOffset;

                previousPosition += deltaOffset;

                // Update available positions
                for (int i = 0; i < available.Count; i++)
                {
                    available[i] += deltaOffset;
                }

                // Update unexplored positions
                for (int i = 0; i < unexplored.Count; i++)
                {
                    unexplored[i] += deltaOffset;
                }

                // Update map positions
                Dictionary<Node, MapSpace> newMap = new Dictionary<Node, MapSpace>(map.Count);

                foreach (Node key in map.Keys)
                {
                    newMap[key + deltaOffset] = map[key];
                }

                map = newMap;

                // Update occupied positions
                for (int i = 0; i < occupied.Count; i++)
                {
                    occupied[i] += deltaOffset;
                }

                // Update bomb positions
                Dictionary<Node, int> newBombs = new Dictionary<Node, int>(bombs.Count);

                foreach (Node key in bombs.Keys)
                {
                    newBombs[key + deltaOffset] = bombs[key];
                }

                bombs = newBombs;

                // Update the exit position
                if (foundExit)
                {
                    exit += deltaOffset;
                }
            }

            // Update the team's data
            public static void UpdateTeamData(AIBrain brain)
            {
                // Update unexplored positions
                for (int i = 0; i < brain.unexplored.Count; i++)
                {
                    if (!teamUnexplored.Contains(brain.unexplored[i]))
                    {
                        teamUnexplored.Add(brain.unexplored[i]);
                    }
                }

                // Update the team's map
                foreach (Node key in brain.map.Keys)
                {
                    if (!teamMap.ContainsKey(key))
                    {
                        teamMap[key] = brain.map[key];
                    }
                }

                // Update available positions
                for (int i = 0; i < brain.available.Count; i++)
                {
                    if (!teamAvailable.Contains(brain.available[i]))
                    {
                        teamAvailable.Add(brain.available[i]);
                    }
                }

                // Update occupied positions
                for (int i = 0; i < brain.occupied.Count; i++)
                {
                    if (!teamOccupied.Contains(brain.occupied[i]))
                    {
                        teamOccupied.Add(brain.occupied[i]);
                    }
                }

                // Update bomb positions
                foreach (Node key in brain.bombs.Keys)
                {
                    if (!teamBombs.ContainsKey(key))
                    {
                        teamBombs[key] = brain.bombs[key];
                    }
                    else
                    {
                        teamBombs[key] = teamBombs[key] > brain.bombs[key] ? teamBombs[key] : brain.bombs[key];
                    }
                }
            }

            // Complete the linking of map positions
            public static void CompleteLink(AIBrain brain)
            {
                // Update whether the AI has linked to the map
                brain.hasLinked = true;

                // Update whether the next AI's map should be linked with the team map
                linkWithTeam = true;

                // Update whether the team has the key
                if (brain.hasKey)
                {
                    teamHasKey = true;
                }

                // Update whether the team has found the exit
                if (brain.foundExit)
                {
                    teamFoundExit = true;

                    teamExit = brain.exit;
                }
            }

            // Update bomb times
            public void UpdateBombTimes()
            {
                List<Node> keys = new List<Node>();

                if (shareTeamInformation && hasLinked && index == team.Count - 1)
                {
                    foreach (Node key in teamBombs.Keys)
                    {
                        keys.Add(key);
                    }

                    foreach (Node key in keys)
                    {
                        teamBombs[key]--;

                        if (teamBombs[key] <= 0)
                        {
                            teamBombs.Remove(key);
                        }
                    }
                }
                else
                {
                    foreach (Node key in bombs.Keys)
                    {
                        keys.Add(key);
                    }

                    foreach (Node key in keys)
                    {
                        bombs[key]--;

                        if (bombs[key] <= 0)
                        {
                            bombs.Remove(key);
                        }
                    }
                }
            }

            // Check for ally players
            public bool CheckForAllies()
            {
                // Check that we have linked
                if (!friendlyFire && shareTeamInformation && hasLinked)
                {
                    // Loop through each AI
                    for (int i = 0; i < team.Count; i++)
                    {
                        // Ignore the same AI
                        if (i == index)
                        {
                            continue;
                        }

                        // Mark each direction
                        Node up = currentPosition + new Node(0, 1);
                        Node down = currentPosition + new Node(0, -1);
                        Node left = currentPosition + new Node(-1, 0);
                        Node right = currentPosition + new Node(1, 0);

                        Node otherPosition = i > index ? team[i].brain.currentPosition : team[i].brain.previousPosition;

                        // Check for matching positions as each direction
                        if (otherPosition == currentPosition || otherPosition == up || otherPosition == down || otherPosition == left || otherPosition == right)
                        {
                            // Adjacent to a teammate
                            return true;
                        }
                    }
                }

                // Adjacent to an enemy
                return false;
            }

            // Remove an AI from the team as it has died
            public void RemoveAI(int index)
            {
                // Mark the key as lost if the key was on the killed AI
                if (team[index].brain.hasKey && team[index].brain.hasLinked)
                {
                    Debug.Log("AI Team lost the key!");

                    teamHasKey = false;

                    keyPosition = team[index].brain.currentPosition;

                    lostKey = true;
                }

                // Remove our AI from the AI team
                team.RemoveAt(index);
                AIClass deceasedClass = classes[index];
                classes.RemoveAt(index);

                // Loop through each of the remaining AI
                for (int i = index; i < team.Count; i++)
                {
                    Debug.Log("AI #" + (team[i].brain.index + 1) + " is now AI #" + team[i].brain.index + ".");

                    // Update the index of that AI
                    team[i].brain.index--;
                }

                // Loop through each of the remaining AI
                for (int i = 0; i < team.Count; i++)
                {
                    // Call on destroy 
                    team[i].AIDestroyed(deceasedClass);
                }
            }

            // Reset static variables (15 total)
            public static void ResetTeamInformation()
            {
                linkWithTeam = false;

                team = new List<AIBase>();
                classes = new List<AIClass>();

                passIndex = 0;
                canPass = false;

                teamAvailable = new List<Node>();

                teamUnexplored = new List<Node>();

                teamMap = new Dictionary<Node, MapSpace>();

                teamOccupied = new List<Node>();

                teamBombs = new Dictionary<Node, int>();

                teamHasKey = false;

                teamExit = Node.zero;
                teamFoundExit = false;

                friendlyFire = false;
            }

            // Copy another brain's independent information
            public void CopyInformation(AIBrain otherBrain)
            {
                currentPosition = otherBrain.currentPosition;
                previousPosition = otherBrain.previousPosition;
                sensorData = otherBrain.sensorData;
                available = otherBrain.available;
                unexplored = otherBrain.unexplored;
                map = otherBrain.map;
                occupied = otherBrain.occupied;
                bombs = otherBrain.bombs;
                hasKey = otherBrain.hasKey;
                exit = otherBrain.exit;
                foundExit = otherBrain.foundExit;

                if (shareTeamInformation)
                {
                    hasLinked = otherBrain.hasLinked;
                }
            }
        }

        // One position and its connected spaces as part of the map.
        public class MapSpace
        {
            // The connected map positions that define what a map space looks like
            public GameManager.SensorData current;
            public GameManager.SensorData up;
            public GameManager.SensorData down;
            public GameManager.SensorData left;
            public GameManager.SensorData right;

            // Constructor
            public MapSpace(GameManager.SensorData current, GameManager.SensorData up, GameManager.SensorData down, GameManager.SensorData left, GameManager.SensorData right)
            {
                this.current = current;
                this.up = up;
                this.down = down;
                this.left = left;
                this.right = right;
            }

            // Calculate the unchanging map space from the given sensor data (clear, wall, goal, offgrid)
            public static GameManager.SensorData GetPermanentSpace(GameManager.SensorData space)
            {
                if (SpaceContains(space, GameManager.SensorData.Clear))
                {
                    return GameManager.SensorData.Clear;
                }
                else if (SpaceContains(space, GameManager.SensorData.Wall))
                {
                    return GameManager.SensorData.Wall;
                }
                else if (SpaceContains(space, GameManager.SensorData.Goal))
                {
                    return GameManager.SensorData.Goal;
                }
                else if (SpaceContains(space, GameManager.SensorData.OffGrid))
                {
                    return GameManager.SensorData.OffGrid;
                }
                else
                {
                    return space;
                }
            }

            // Check whether the given 'space' is flagged with the 'contains' enum
            public static bool SpaceContains(GameManager.SensorData space, GameManager.SensorData contains)
            {
                return (space & contains) != 0;
            }

            // Return whether the map space contains the given searched data
            public bool FindData(GameManager.SensorData searchedData)
            {
                if (SpaceContains(current, searchedData) || SpaceContains(up, searchedData) || SpaceContains(down, searchedData) || SpaceContains(left, searchedData) || SpaceContains(right, searchedData))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }

            // Gets the direction of the given sensor data and returns if it is successful
            public bool FindData(GameManager.SensorData searchedData, out GameManager.Direction direction)
            {
                if (SpaceContains(current, searchedData))
                {
                    direction = GameManager.Direction.Current;

                    return true;
                }
                else if (SpaceContains(up, searchedData))
                {
                    direction = GameManager.Direction.Up;

                    return true;
                }
                else if (SpaceContains(down, searchedData))
                {
                    direction = GameManager.Direction.Down;

                    return true;
                }
                else if (SpaceContains(left, searchedData))
                {
                    direction = GameManager.Direction.Left;

                    return true;
                }
                else if (SpaceContains(right, searchedData))
                {
                    direction = GameManager.Direction.Right;

                    return true;
                }

                direction = GameManager.Direction.Current;

                return false;
            }

            // Gets the data from the given direction
            public GameManager.SensorData GetSpace(GameManager.Direction direction)
            {
                switch (direction)
                {
                    case GameManager.Direction.Up:

                        return up;

                    case GameManager.Direction.Down:

                        return down;

                    case GameManager.Direction.Left:

                        return left;

                    case GameManager.Direction.Right:

                        return right;

                    default:

                        return current;
                }
            }

            // Equals function
            public bool SpaceEquals(MapSpace comparison)
            {
                int matches = 0;

                matches += current == comparison.current ? 1 : 0;
                matches += up == comparison.up ? 1 : 0;
                matches += down == comparison.down ? 1 : 0;
                matches += left == comparison.left ? 1 : 0;
                matches += right == comparison.right ? 1 : 0;

                return matches == 5;
            }
        }
    }
}
