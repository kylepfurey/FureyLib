
// AI Battle - AI Team Base Class Script
// by Kyle Furey, AI Battle game made by Dave Carrigg

namespace AIBattle
{
    namespace AITeam
    {
        using System.Collections.Generic;
        using UnityEngine;

        // Define the grid nodes
        using Node = UnityEngine.Vector2Int;

        // AI class enum
        public enum AIClass { NULL, Scout, Hunter, Defender, Switcher };

        // Base class for the AI Team.
        public abstract class AIBase : BaseAI
        {
            // DATA

            // The AI's known information
            public AIBrain brain = new AIBrain();


            // FUNCTIONS

            // AI KEY

            // aMoves                =  the chain of movements the AI will take when a CombatantAction.Move is returned
            // aBombTime             =  the number of turns before the placed bomb detonates when a CombatantAction.DropBomb is returned
            // Direction             =  a direction in a series of directions the AI will move when a CombatantAction.Move is returned
            // SensorData            =  the type of space located when UseSensor(Direction) is called for the given Direction (relative to the AI's position)
            // CombatantAction       =  the chosen action the AI will execute for its turn (how it is executed depends on the returned CombatantAction and the set parameters of the function)
            // UseSensor(Direction)  =  returns the type of space of the given direction via the SensorData enum (relative to the AI's position)


            // Base function used to update the AI's map and determine if the game is currently winnable
            public override CombatantAction GetAction(ref List<GameManager.Direction> aMoves, ref int aBombTime)
            {
                // Check that this AI is not a puppet
                if (!brain.puppet)
                {
                    Debug.Log("AI " + AIName + "'s turn!");

                    // Register the AI to the AI team if the AI has not already
                    brain.RegisterAI(this);

                    // Pass the current team index to ensure no AI have died, and if so share that information with the team
                    brain.PassIndex();
                }

                // Clear the list of moves and the bomb time
                aMoves.Clear();
                aBombTime = 0;

                // Store the sensor data
                brain.sensorData = new MapSpace(UseSensor(GameManager.Direction.Current), UseSensor(GameManager.Direction.Up), UseSensor(GameManager.Direction.Down), UseSensor(GameManager.Direction.Left), UseSensor(GameManager.Direction.Right));

                // Generate and store the sensor data
                StoreSensorData();

                // Link the AI team's maps
                brain.LinkMaps();

                // Check if we can grab the key
                GameManager.Direction direction;

                if (!brain.hasKey && (!AIBrain.shareTeamInformation || !AIBrain.teamHasKey) && brain.sensorData.FindData(GameManager.SensorData.Diamond, out direction) && direction != GameManager.Direction.Current && !MapSpace.SpaceContains(brain.sensorData.GetSpace(direction), GameManager.SensorData.Enemy))
                {
                    Debug.Log("AI " + AIName + " found the key!");

                    // Return CombatantAction.Move as we have found the key
                    return CombatantAction.Move;
                }
                // Check if the game is currently winnable
                else if (brain.hasKey && (brain.foundExit || (AIBrain.shareTeamInformation && AIBrain.teamFoundExit && brain.hasLinked)))
                {
                    Debug.Log("AI " + AIName + " is going to the exit!");

                    // Return CombatantAction.DropBomb as the game is currently winnable
                    return CombatantAction.DropBomb;
                }
                // Continue with the AI's default actions
                else
                {
                    // Return CombatantAction.Pass as the game is not currently winnable
                    return CombatantAction.Pass;
                }
            }

            // Generate and store the sensor data
            public void StoreSensorData()
            {
                // Log the sensor data
                if (AIBrain.shareTeamInformation && brain.hasLinked)
                {
                    // Log the current position
                    AIBrain.teamMap[brain.currentPosition] = brain.sensorData;

                    // Remove the current unexplored position
                    AIBrain.teamUnexplored.Remove(brain.currentPosition);

                    // Log occupied spaces
                    GameManager.SensorData newSensorData;
                    GameManager.SensorData permanentSensorData;
                    Node newPosition;

                    // Log up
                    newSensorData = brain.sensorData.up;
                    permanentSensorData = MapSpace.GetPermanentSpace(newSensorData);
                    newPosition = brain.currentPosition + new Node(0, 1);

                    // Check if the space is occupied
                    if (permanentSensorData != GameManager.SensorData.Clear && permanentSensorData != GameManager.SensorData.Goal)
                    {
                        // Log the space as occupied
                        AIBrain.teamOccupied.Add(newPosition);
                    }
                    else
                    {
                        // Have we visited this space before
                        if (!AIBrain.teamAvailable.Contains(newPosition))
                        {
                            // Log the space as available
                            AIBrain.teamAvailable.Add(newPosition);

                            // Log the space as unexplored
                            AIBrain.teamUnexplored.Add(newPosition);
                        }

                        // Check for bombs
                        if (MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Bomb))
                        {
                            // Mark all bomb positions
                            AIBrain.teamBombs[newPosition + new Node(-1, 0)] = AIBrain.unknownBombTime + 1;

                            AIBrain.teamBombs[newPosition + new Node(0, -1)] = AIBrain.unknownBombTime + 1;
                            AIBrain.teamBombs[newPosition + new Node(0, 0)] = AIBrain.unknownBombTime + 1;
                            AIBrain.teamBombs[newPosition + new Node(0, 1)] = AIBrain.unknownBombTime + 1;

                            AIBrain.teamBombs[newPosition + new Node(1, 0)] = AIBrain.unknownBombTime + 1;
                        }

                        // Check for the goal
                        if (!AIBrain.teamFoundExit && MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Goal))
                        {
                            Debug.Log("AI " + AIName + " found the exit!");

                            // Mark the exit
                            AIBrain.teamFoundExit = true;
                            AIBrain.teamExit = newPosition;
                        }
                    }

                    // Log down
                    newSensorData = brain.sensorData.down;
                    permanentSensorData = MapSpace.GetPermanentSpace(newSensorData);
                    newPosition = brain.currentPosition + new Node(0, -1);

                    // Check if the space is occupied
                    if (permanentSensorData != GameManager.SensorData.Clear && permanentSensorData != GameManager.SensorData.Goal)
                    {
                        // Log the space as occupied
                        AIBrain.teamOccupied.Add(newPosition);
                    }
                    else
                    {
                        // Have we visited this space before
                        if (!AIBrain.teamAvailable.Contains(newPosition))
                        {
                            // Log the space as available
                            AIBrain.teamAvailable.Add(newPosition);

                            // Log the space as unexplored
                            AIBrain.teamUnexplored.Add(newPosition);
                        }

                        // Check for bombs
                        if (MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Bomb))
                        {
                            // Mark all bomb positions
                            AIBrain.teamBombs[newPosition + new Node(-1, 0)] = AIBrain.unknownBombTime + 1;

                            AIBrain.teamBombs[newPosition + new Node(0, -1)] = AIBrain.unknownBombTime + 1;
                            AIBrain.teamBombs[newPosition + new Node(0, 0)] = AIBrain.unknownBombTime + 1;
                            AIBrain.teamBombs[newPosition + new Node(0, 1)] = AIBrain.unknownBombTime + 1;

                            AIBrain.teamBombs[newPosition + new Node(1, 0)] = AIBrain.unknownBombTime + 1;
                        }

                        // Check for the goal
                        if (!AIBrain.teamFoundExit && MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Goal))
                        {
                            Debug.Log("AI " + AIName + " found the exit!");

                            // Mark the exit
                            AIBrain.teamFoundExit = true;
                            AIBrain.teamExit = newPosition;
                        }
                    }

                    // Log left
                    newSensorData = brain.sensorData.left;
                    permanentSensorData = MapSpace.GetPermanentSpace(newSensorData);
                    newPosition = brain.currentPosition + new Node(-1, 0);

                    // Check if the space is occupied
                    if (permanentSensorData != GameManager.SensorData.Clear && permanentSensorData != GameManager.SensorData.Goal)
                    {
                        // Log the space as occupied
                        AIBrain.teamOccupied.Add(newPosition);
                    }
                    else
                    {
                        // Have we visited this space before
                        if (!AIBrain.teamAvailable.Contains(newPosition))
                        {
                            // Log the space as available
                            AIBrain.teamAvailable.Add(newPosition);

                            // Log the space as unexplored
                            AIBrain.teamUnexplored.Add(newPosition);
                        }

                        // Check for bombs
                        if (MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Bomb))
                        {
                            // Mark all bomb positions
                            AIBrain.teamBombs[newPosition + new Node(-1, 0)] = AIBrain.unknownBombTime + 1;

                            AIBrain.teamBombs[newPosition + new Node(0, -1)] = AIBrain.unknownBombTime + 1;
                            AIBrain.teamBombs[newPosition + new Node(0, 0)] = AIBrain.unknownBombTime + 1;
                            AIBrain.teamBombs[newPosition + new Node(0, 1)] = AIBrain.unknownBombTime + 1;

                            AIBrain.teamBombs[newPosition + new Node(1, 0)] = AIBrain.unknownBombTime + 1;
                        }

                        // Check for the goal
                        if (!AIBrain.teamFoundExit && MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Goal))
                        {
                            Debug.Log("AI " + AIName + " found the exit!");

                            // Mark the exit
                            AIBrain.teamFoundExit = true;
                            AIBrain.teamExit = newPosition;
                        }
                    }

                    // Log right
                    newSensorData = brain.sensorData.right;
                    permanentSensorData = MapSpace.GetPermanentSpace(newSensorData);
                    newPosition = brain.currentPosition + new Node(1, 0);

                    // Check if the space is occupied
                    if (permanentSensorData != GameManager.SensorData.Clear && permanentSensorData != GameManager.SensorData.Goal)
                    {
                        // Log the space as occupied
                        AIBrain.teamOccupied.Add(newPosition);
                    }
                    else
                    {
                        // Have we visited this space before
                        if (!AIBrain.teamAvailable.Contains(newPosition))
                        {
                            // Log the space as available
                            AIBrain.teamAvailable.Add(newPosition);

                            // Log the space as unexplored
                            AIBrain.teamUnexplored.Add(newPosition);
                        }

                        // Check for bombs
                        if (MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Bomb))
                        {
                            // Mark all bomb positions
                            AIBrain.teamBombs[newPosition + new Node(-1, 0)] = AIBrain.unknownBombTime + 1;

                            AIBrain.teamBombs[newPosition + new Node(0, -1)] = AIBrain.unknownBombTime + 1;
                            AIBrain.teamBombs[newPosition + new Node(0, 0)] = AIBrain.unknownBombTime + 1;
                            AIBrain.teamBombs[newPosition + new Node(0, 1)] = AIBrain.unknownBombTime + 1;

                            AIBrain.teamBombs[newPosition + new Node(1, 0)] = AIBrain.unknownBombTime + 1;
                        }

                        // Check for the goal
                        if (!AIBrain.teamFoundExit && MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Goal))
                        {
                            Debug.Log("AI " + AIName + " found the exit!");

                            // Mark the exit
                            AIBrain.teamFoundExit = true;
                            AIBrain.teamExit = newPosition;
                        }
                    }
                }
                else
                {
                    // Log the current position
                    brain.map[brain.currentPosition] = brain.sensorData;

                    // Remove the current unexplored position
                    brain.unexplored.Remove(brain.currentPosition);

                    // Log occupied spaces
                    GameManager.SensorData newSensorData;
                    GameManager.SensorData permanentSensorData;
                    Node newPosition;

                    // Log up
                    newSensorData = brain.sensorData.up;
                    permanentSensorData = MapSpace.GetPermanentSpace(newSensorData);
                    newPosition = brain.currentPosition + new Node(0, 1);

                    // Check if the space is occupied
                    if (permanentSensorData != GameManager.SensorData.Clear && permanentSensorData != GameManager.SensorData.Goal)
                    {
                        // Log the space as occupied
                        brain.occupied.Add(newPosition);
                    }
                    else
                    {
                        // Have we visited this space before
                        if (!brain.available.Contains(newPosition))
                        {
                            // Log the space as available
                            brain.available.Add(newPosition);

                            // Log the space as unexplored
                            brain.unexplored.Add(newPosition);
                        }

                        // Check for bombs
                        if (MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Bomb))
                        {
                            // Mark all bomb positions
                            brain.bombs[newPosition + new Node(-1, 0)] = AIBrain.unknownBombTime + 1;

                            brain.bombs[newPosition + new Node(0, -1)] = AIBrain.unknownBombTime + 1;
                            brain.bombs[newPosition + new Node(0, 0)] = AIBrain.unknownBombTime + 1;
                            brain.bombs[newPosition + new Node(0, 1)] = AIBrain.unknownBombTime + 1;

                            brain.bombs[newPosition + new Node(1, 0)] = AIBrain.unknownBombTime + 1;
                        }

                        // Check for the goal
                        if (!brain.foundExit && MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Goal))
                        {
                            Debug.Log("AI " + AIName + " found the exit!");

                            // Mark the exit
                            brain.foundExit = true;
                            brain.exit = newPosition;
                        }
                    }

                    // Log down
                    newSensorData = brain.sensorData.down;
                    permanentSensorData = MapSpace.GetPermanentSpace(newSensorData);
                    newPosition = brain.currentPosition + new Node(0, -1);

                    // Check if the space is occupied
                    if (permanentSensorData != GameManager.SensorData.Clear && permanentSensorData != GameManager.SensorData.Goal)
                    {
                        // Log the space as occupied
                        brain.occupied.Add(newPosition);
                    }
                    else
                    {
                        // Have we visited this space before
                        if (!brain.available.Contains(newPosition))
                        {
                            // Log the space as available
                            brain.available.Add(newPosition);

                            // Log the space as unexplored
                            brain.unexplored.Add(newPosition);
                        }

                        // Check for bombs
                        if (MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Bomb))
                        {
                            // Mark all bomb positions
                            brain.bombs[newPosition + new Node(-1, 0)] = AIBrain.unknownBombTime + 1;

                            brain.bombs[newPosition + new Node(0, -1)] = AIBrain.unknownBombTime + 1;
                            brain.bombs[newPosition + new Node(0, 0)] = AIBrain.unknownBombTime + 1;
                            brain.bombs[newPosition + new Node(0, 1)] = AIBrain.unknownBombTime + 1;

                            brain.bombs[newPosition + new Node(1, 0)] = AIBrain.unknownBombTime + 1;
                        }

                        // Check for the goal
                        if (!brain.foundExit && MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Goal))
                        {
                            Debug.Log("AI " + AIName + " found the exit!");

                            // Mark the exit
                            brain.foundExit = true;
                            brain.exit = newPosition;
                        }
                    }

                    // Log left
                    newSensorData = brain.sensorData.left;
                    permanentSensorData = MapSpace.GetPermanentSpace(newSensorData);
                    newPosition = brain.currentPosition + new Node(-1, 0);

                    // Check if the space is occupied
                    if (permanentSensorData != GameManager.SensorData.Clear && permanentSensorData != GameManager.SensorData.Goal)
                    {
                        // Log the space as occupied
                        brain.occupied.Add(newPosition);
                    }
                    else
                    {
                        // Have we visited this space before
                        if (!brain.available.Contains(newPosition))
                        {
                            // Log the space as available
                            brain.available.Add(newPosition);

                            // Log the space as unexplored
                            brain.unexplored.Add(newPosition);
                        }

                        // Check for bombs
                        if (MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Bomb))
                        {
                            // Mark all bomb positions
                            brain.bombs[newPosition + new Node(-1, 0)] = AIBrain.unknownBombTime + 1;

                            brain.bombs[newPosition + new Node(0, -1)] = AIBrain.unknownBombTime + 1;
                            brain.bombs[newPosition + new Node(0, 0)] = AIBrain.unknownBombTime + 1;
                            brain.bombs[newPosition + new Node(0, 1)] = AIBrain.unknownBombTime + 1;

                            brain.bombs[newPosition + new Node(1, 0)] = AIBrain.unknownBombTime + 1;
                        }

                        // Check for the goal
                        if (!brain.foundExit && MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Goal))
                        {
                            Debug.Log("AI " + AIName + " found the exit!");

                            // Mark the exit
                            brain.foundExit = true;
                            brain.exit = newPosition;
                        }
                    }

                    // Log right
                    newSensorData = brain.sensorData.right;
                    permanentSensorData = MapSpace.GetPermanentSpace(newSensorData);
                    newPosition = brain.currentPosition + new Node(1, 0);

                    // Check if the space is occupied
                    if (permanentSensorData != GameManager.SensorData.Clear && permanentSensorData != GameManager.SensorData.Goal)
                    {
                        // Log the space as occupied
                        brain.occupied.Add(newPosition);
                    }
                    else
                    {
                        // Have we visited this space before
                        if (!brain.available.Contains(newPosition))
                        {
                            // Log the space as available
                            brain.available.Add(newPosition);

                            // Log the space as unexplored
                            brain.unexplored.Add(newPosition);
                        }

                        // Check for bombs
                        if (MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Bomb))
                        {
                            // Mark all bomb positions
                            brain.bombs[newPosition + new Node(-1, 0)] = AIBrain.unknownBombTime + 1;

                            brain.bombs[newPosition + new Node(0, -1)] = AIBrain.unknownBombTime + 1;
                            brain.bombs[newPosition + new Node(0, 0)] = AIBrain.unknownBombTime + 1;
                            brain.bombs[newPosition + new Node(0, 1)] = AIBrain.unknownBombTime + 1;

                            brain.bombs[newPosition + new Node(1, 0)] = AIBrain.unknownBombTime + 1;
                        }

                        // Check for the goal
                        if (!brain.foundExit && MapSpace.SpaceContains(newSensorData, GameManager.SensorData.Goal))
                        {
                            Debug.Log("AI " + AIName + " found the exit!");

                            // Mark the exit
                            brain.foundExit = true;
                            brain.exit = newPosition;
                        }
                    }
                }
            }

            // Overridable logic used to determine the AI's next position
            public virtual Node GetNextPosition()
            {
                return Node.zero;
            }

            // Overridable logic for when an AI is destroyed
            public virtual void AIDestroyed(AIClass destroyedClass) { }

            // Get our new position from the list of movements
            public void GetNewPosition(List<GameManager.Direction> aMoves)
            {
                // Update our previous position
                brain.previousPosition = brain.currentPosition;

                // Null check
                if (aMoves == null)
                {
                    return;
                }

                // Move each position
                foreach (GameManager.Direction aMove in aMoves)
                {
                    switch (aMove)
                    {
                        case GameManager.Direction.Up:

                            brain.currentPosition += new Node(0, 1);

                            break;

                        case GameManager.Direction.Down:

                            brain.currentPosition += new Node(0, -1);

                            break;

                        case GameManager.Direction.Left:

                            brain.currentPosition += new Node(-1, 0);

                            break;

                        case GameManager.Direction.Right:

                            brain.currentPosition += new Node(1, 0);

                            break;
                    }
                }

                // Store that we have moved
                brain.firstTurn = false;
            }
        }
    }
}
