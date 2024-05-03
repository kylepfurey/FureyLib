
// AI Battle - Defender AI Class Script
// by Kyle Furey, AI Battle game made by Dave Carrigg

namespace AIBattle
{
    namespace AITeam
    {
        using System.Collections.Generic;
        using UnityEngine;

        // Define the grid nodes
        using Node = UnityEngine.Vector2Int;


        // AI TRAITS

        // AI entity that explores in one direction, if that direction is still available to explore, until the exit is found.
        // Goes to the exit, places a bomb there, explores a new position, and then places a bomb there. Repeats this forever unless it finds the key or wins.
        // Grabs the key if it is found, exits if the key is held and the exit is located.
        // Avoids bombs at all costs unless the bomb is their own and is not about to detonate.


        // Defender AI class.
        [CreateAssetMenu(fileName = "DefenderAI", menuName = "AI/AI Team/Defender AI", order = 2)]
        public class DefenderAI : AIBase
        {
            // SETTINGS

            // The time to drop bombs for when enemies are being followed
            private const int exitBombDropTime = 1;
            private const int farBombDropTime = 1;


            // DATA

            // Track how many times we have explored each direction
            private int upExplorations = 0;
            private int downExplorations = 0;
            private int leftExplorations = 0;
            private int rightExplorations = 0;

            // The current state of this defender
            private DefenderState state = DefenderState.NoExitFound;

            // The attempted offset to go to with the exit
            private GameManager.Direction exitOffset = GameManager.Direction.Right;

            // Defender state enum for Defender behaviour
            private enum DefenderState { NoExitFound, BombExit, GoFar, BombFar, GoExit };


            // CONSTRUCTORS

            // Default constructor
            public DefenderAI()
            {
                brain = new AIBrain();

                brain.classType = AIClass.Defender;
            }

            // AI brain constructor
            public DefenderAI(AIBrain brain)
            {
                this.brain = brain;

                this.brain.classType = AIClass.Defender;
            }


            // FUNCTIONS

            // The function automatically called to select the AI's next action(s)
            public override CombatantAction GetAction(ref List<GameManager.Direction> aMoves, ref int aBombTime)
            {
                // Update the AI's map knowledge and choose a set action if possible
                CombatantAction setAction = base.GetAction(ref aMoves, ref aBombTime);

                // Recover the key if possible
                if (AIBrain.shareTeamInformation && AIBrain.lostKey && brain.hasLinked)
                {
                    Debug.Log("AI " + AIName + " recovered the key!");

                    // Store the key
                    brain.hasKey = true;

                    if (AIBrain.shareTeamInformation)
                    {
                        AIBrain.teamHasKey = true;
                    }

                    AIBrain.lostKey = false;

                    // Move to the key
                    aMoves = brain.GetMovements(AStar.Search(brain.currentPosition, AIBrain.keyPosition, AIBrain.teamAvailable, AIBrain.teamOccupied));

                    // Update our current position
                    GetNewPosition(aMoves);

                    // Update bomb times
                    brain.UpdateBombTimes();

                    // Check for failure to move
                    if (AIBrain.explodeOnFailure && aMoves == null && AIBrain.shareTeamInformation && brain.hasLinked)
                    {
                        if (MapSpace.SpaceContains(UseSensor(GameManager.Direction.Current), GameManager.SensorData.Goal))
                        {
                            aMoves = new List<GameManager.Direction>
                                {
                                    GameManager.Direction.Up
                                };

                            return CombatantAction.Move;
                        }
                        else
                        {
                            Debug.Log("AI " + AIName + " did not successfully link! EXPLODING!");

                            aMoves = new List<GameManager.Direction>();

                            aBombTime = 1;

                            AIBrain.teamBombs[brain.currentPosition + new Node(-1, 0)] = 1;

                            AIBrain.teamBombs[brain.currentPosition + new Node(0, -1)] = 1;
                            AIBrain.teamBombs[brain.currentPosition + new Node(0, 0)] = 1;
                            AIBrain.teamBombs[brain.currentPosition + new Node(0, 1)] = 1;

                            AIBrain.teamBombs[brain.currentPosition + new Node(1, 0)] = 1;

                            return CombatantAction.DropBomb;
                        }
                    }
                    else if (aMoves == null)
                    {
                        aMoves = new List<GameManager.Direction>();
                    }

                    // Win the game
                    return CombatantAction.Move;
                }

                // Grab the key if possible
                if (setAction == CombatantAction.Move)
                {
                    // Store the key
                    brain.hasKey = true;

                    if (AIBrain.shareTeamInformation)
                    {
                        AIBrain.teamHasKey = true;
                    }

                    // Store the direction of the key
                    GameManager.Direction keyDirection;

                    brain.sensorData.FindData(GameManager.SensorData.Diamond, out keyDirection);

                    // Check that the key is not on us
                    if (keyDirection != GameManager.Direction.Current)
                    {
                        // Go to the direction of the key
                        aMoves.Add(keyDirection);

                        // Update our current position
                        GetNewPosition(aMoves);

                        // Update bomb times
                        brain.UpdateBombTimes();

                        // Check for failure to move
                        if (AIBrain.explodeOnFailure && aMoves == null && AIBrain.shareTeamInformation && brain.hasLinked)
                        {
                            if (MapSpace.SpaceContains(UseSensor(GameManager.Direction.Current), GameManager.SensorData.Goal))
                            {
                                aMoves = new List<GameManager.Direction>
                                {
                                    GameManager.Direction.Up
                                };

                                return CombatantAction.Move;
                            }
                            else
                            {
                                Debug.Log("AI " + AIName + " did not successfully link! EXPLODING!");

                                aMoves = new List<GameManager.Direction>();

                                aBombTime = 1;

                                AIBrain.teamBombs[brain.currentPosition + new Node(-1, 0)] = 1;

                                AIBrain.teamBombs[brain.currentPosition + new Node(0, -1)] = 1;
                                AIBrain.teamBombs[brain.currentPosition + new Node(0, 0)] = 1;
                                AIBrain.teamBombs[brain.currentPosition + new Node(0, 1)] = 1;

                                AIBrain.teamBombs[brain.currentPosition + new Node(1, 0)] = 1;

                                return CombatantAction.DropBomb;
                            }
                        }
                        else if (aMoves == null)
                        {
                            aMoves = new List<GameManager.Direction>();
                        }

                        // Grab the key
                        return CombatantAction.Move;
                    }
                }
                // Win if possible
                else if (setAction == CombatantAction.DropBomb)
                {
                    // Store the direction of the exit
                    GameManager.Direction exitDirection;

                    brain.sensorData.FindData(GameManager.SensorData.Diamond, out exitDirection);

                    // Check if the exit is adjacent of us
                    if (exitDirection != GameManager.Direction.Current)
                    {
                        // Go to the direction of the key
                        aMoves.Add(exitDirection);
                    }
                    // Move to the exit
                    else if (AIBrain.shareTeamInformation && brain.hasLinked)
                    {
                        aMoves = brain.GetMovements(AStar.Search(brain.currentPosition, AIBrain.teamExit, AIBrain.teamAvailable, AIBrain.teamOccupied));
                    }
                    else
                    {
                        aMoves = brain.GetMovements(AStar.Search(brain.currentPosition, brain.exit, brain.available, brain.occupied));
                    }

                    // Update our current position
                    GetNewPosition(aMoves);

                    // Update bomb times
                    brain.UpdateBombTimes();

                    // Check for failure to move
                    if (AIBrain.explodeOnFailure && aMoves == null && AIBrain.shareTeamInformation && brain.hasLinked)
                    {
                        if (MapSpace.SpaceContains(UseSensor(GameManager.Direction.Current), GameManager.SensorData.Goal))
                        {
                            aMoves = new List<GameManager.Direction>
                                {
                                    GameManager.Direction.Up
                                };

                            return CombatantAction.Move;
                        }
                        else
                        {
                            Debug.Log("AI " + AIName + " did not successfully link! EXPLODING!");

                            aMoves = new List<GameManager.Direction>();

                            aBombTime = 1;

                            AIBrain.teamBombs[brain.currentPosition + new Node(-1, 0)] = 1;

                            AIBrain.teamBombs[brain.currentPosition + new Node(0, -1)] = 1;
                            AIBrain.teamBombs[brain.currentPosition + new Node(0, 0)] = 1;
                            AIBrain.teamBombs[brain.currentPosition + new Node(0, 1)] = 1;

                            AIBrain.teamBombs[brain.currentPosition + new Node(1, 0)] = 1;

                            return CombatantAction.DropBomb;
                        }
                    }
                    else if (aMoves == null)
                    {
                        aMoves = new List<GameManager.Direction>();
                    }

                    // Win the game
                    return CombatantAction.Move;
                }


                // Complete movement logic

                // Check if we found the exit
                if (state == DefenderState.NoExitFound && ((AIBrain.shareTeamInformation && AIBrain.teamFoundExit && brain.hasLinked) || brain.foundExit))
                {
                    state = DefenderState.BombExit;

                    // Move to the exit
                    if (AIBrain.shareTeamInformation && brain.hasLinked)
                    {
                        aMoves = brain.GetMovements(AStar.Search(brain.currentPosition, AIBrain.teamExit, AIBrain.teamAvailable, AIBrain.teamOccupied));
                    }
                    else
                    {
                        aMoves = brain.GetMovements(AStar.Search(brain.currentPosition, brain.exit, brain.available, brain.occupied));
                    }

                    // Update our current position
                    GetNewPosition(aMoves);

                    // Update bomb times
                    brain.UpdateBombTimes();

                    // Check for failure to move
                    if (AIBrain.explodeOnFailure && aMoves == null && AIBrain.shareTeamInformation && brain.hasLinked)
                    {
                        if (MapSpace.SpaceContains(UseSensor(GameManager.Direction.Current), GameManager.SensorData.Goal))
                        {
                            aMoves = new List<GameManager.Direction>
                                {
                                    GameManager.Direction.Up
                                };

                            return CombatantAction.Move;
                        }
                        else
                        {
                            Debug.Log("AI " + AIName + " did not successfully link! EXPLODING!");

                            aMoves = new List<GameManager.Direction>();

                            aBombTime = 1;

                            AIBrain.teamBombs[brain.currentPosition + new Node(-1, 0)] = 1;

                            AIBrain.teamBombs[brain.currentPosition + new Node(0, -1)] = 1;
                            AIBrain.teamBombs[brain.currentPosition + new Node(0, 0)] = 1;
                            AIBrain.teamBombs[brain.currentPosition + new Node(0, 1)] = 1;

                            AIBrain.teamBombs[brain.currentPosition + new Node(1, 0)] = 1;

                            return CombatantAction.DropBomb;
                        }
                    }
                    else if (aMoves == null)
                    {
                        aMoves = new List<GameManager.Direction>();
                    }

                    // Win the game
                    return CombatantAction.Move;
                }

                // Check for enemy players
                if (brain.sensorData.FindData(GameManager.SensorData.Enemy))
                {
                    // Check that the enemy player is not an ally and there are no nearby bombs
                    if (!brain.CheckForAllies() && !brain.sensorData.FindData(GameManager.SensorData.Bomb) && !brain.firstTurn)
                    {
                        Debug.Log("AI " + AIName + " found an enemy!");

                        // Drop a bomb
                        aBombTime = AIBrain.enemyBombDropTime + 1;

                        // Mark all bomb positions
                        if (AIBrain.shareTeamInformation && brain.hasLinked)
                        {
                            AIBrain.teamBombs[brain.currentPosition + new Node(-1, 0)] = AIBrain.enemyBombDropTime + 1;

                            AIBrain.teamBombs[brain.currentPosition + new Node(0, -1)] = AIBrain.enemyBombDropTime + 1;
                            AIBrain.teamBombs[brain.currentPosition + new Node(0, 0)] = AIBrain.enemyBombDropTime + 1;
                            AIBrain.teamBombs[brain.currentPosition + new Node(0, 1)] = AIBrain.enemyBombDropTime + 1;

                            AIBrain.teamBombs[brain.currentPosition + new Node(1, 0)] = AIBrain.enemyBombDropTime + 1;
                        }
                        else
                        {
                            brain.bombs[brain.currentPosition + new Node(-1, 0)] = AIBrain.enemyBombDropTime + 1;

                            brain.bombs[brain.currentPosition + new Node(0, -1)] = AIBrain.enemyBombDropTime + 1;
                            brain.bombs[brain.currentPosition + new Node(0, 0)] = AIBrain.enemyBombDropTime + 1;
                            brain.bombs[brain.currentPosition + new Node(0, 1)] = AIBrain.enemyBombDropTime + 1;

                            brain.bombs[brain.currentPosition + new Node(1, 0)] = AIBrain.enemyBombDropTime + 1;
                        }

                        // Update our current position
                        GetNewPosition(aMoves);

                        // Update bomb times
                        brain.UpdateBombTimes();

                        // Move to the next position
                        return CombatantAction.DropBomb;
                    }
                }

                // Decide which action to complete
                switch (state)
                {
                    // Place a bomb at the exit
                    case DefenderState.BombExit:

                        // Check that we are not near an ally and there are no nearby bombs
                        if (!brain.CheckForAllies() && !brain.sensorData.FindData(GameManager.SensorData.Bomb) && !brain.firstTurn)
                        {
                            // Update the next state
                            state = DefenderState.GoFar;

                            // Drop a bomb
                            aBombTime = exitBombDropTime + 1;

                            // Mark all bomb positions
                            if (AIBrain.shareTeamInformation && brain.hasLinked)
                            {
                                AIBrain.teamBombs[brain.currentPosition + new Node(-1, 0)] = exitBombDropTime + 1;

                                AIBrain.teamBombs[brain.currentPosition + new Node(0, -1)] = exitBombDropTime + 1;
                                AIBrain.teamBombs[brain.currentPosition + new Node(0, 0)] = exitBombDropTime + 1;
                                AIBrain.teamBombs[brain.currentPosition + new Node(0, 1)] = exitBombDropTime + 1;

                                AIBrain.teamBombs[brain.currentPosition + new Node(1, 0)] = exitBombDropTime + 1;
                            }
                            else
                            {
                                brain.bombs[brain.currentPosition + new Node(-1, 0)] = exitBombDropTime + 1;

                                brain.bombs[brain.currentPosition + new Node(0, -1)] = exitBombDropTime + 1;
                                brain.bombs[brain.currentPosition + new Node(0, 0)] = exitBombDropTime + 1;
                                brain.bombs[brain.currentPosition + new Node(0, 1)] = exitBombDropTime + 1;

                                brain.bombs[brain.currentPosition + new Node(1, 0)] = exitBombDropTime + 1;
                            }

                            // Update our current position
                            GetNewPosition(aMoves);

                            // Update bomb times
                            brain.UpdateBombTimes();

                            // Move to the next position
                            return CombatantAction.DropBomb;
                        }

                        break;


                    // Go to the furthest explored area
                    case DefenderState.GoFar:

                        // Update the next state
                        state = DefenderState.BombFar;

                        // Move to the next position
                        if (AIBrain.shareTeamInformation && brain.hasLinked)
                        {
                            aMoves = brain.GetMovements(AStar.Search(brain.currentPosition, GetNextPosition(), AIBrain.teamAvailable, AIBrain.teamOccupied));
                        }
                        else
                        {
                            aMoves = brain.GetMovements(AStar.Search(brain.currentPosition, GetNextPosition(), brain.available, brain.occupied));
                        }

                        // Update our current position
                        GetNewPosition(aMoves);

                        // Update bomb times
                        brain.UpdateBombTimes();

                        // Check for failure to move
                        if (AIBrain.explodeOnFailure && aMoves == null && AIBrain.shareTeamInformation && brain.hasLinked)
                        {
                            if (MapSpace.SpaceContains(UseSensor(GameManager.Direction.Current), GameManager.SensorData.Goal))
                            {
                                aMoves = new List<GameManager.Direction>
                                {
                                    GameManager.Direction.Up
                                };

                                return CombatantAction.Move;
                            }
                            else
                            {
                                Debug.Log("AI " + AIName + " did not successfully link! EXPLODING!");

                                aMoves = new List<GameManager.Direction>();

                                aBombTime = 1;

                                AIBrain.teamBombs[brain.currentPosition + new Node(-1, 0)] = 1;

                                AIBrain.teamBombs[brain.currentPosition + new Node(0, -1)] = 1;
                                AIBrain.teamBombs[brain.currentPosition + new Node(0, 0)] = 1;
                                AIBrain.teamBombs[brain.currentPosition + new Node(0, 1)] = 1;

                                AIBrain.teamBombs[brain.currentPosition + new Node(1, 0)] = 1;

                                return CombatantAction.DropBomb;
                            }
                        }
                        else if (aMoves == null)
                        {
                            aMoves = new List<GameManager.Direction>();
                        }

                        // Move to the next position
                        return CombatantAction.Move;


                    // Place a bomb at the new location
                    case DefenderState.BombFar:

                        // Check that we are not near an ally and there are no nearby bombs
                        if (!brain.CheckForAllies() && !brain.sensorData.FindData(GameManager.SensorData.Bomb) && !brain.firstTurn)
                        {
                            // Update the next state
                            state = DefenderState.GoExit;

                            // Drop a bomb
                            aBombTime = farBombDropTime + 1;

                            // Mark all bomb positions
                            if (AIBrain.shareTeamInformation && brain.hasLinked)
                            {
                                AIBrain.teamBombs[brain.currentPosition + new Node(-1, 0)] = farBombDropTime + 1;

                                AIBrain.teamBombs[brain.currentPosition + new Node(0, -1)] = farBombDropTime + 1;
                                AIBrain.teamBombs[brain.currentPosition + new Node(0, 0)] = farBombDropTime + 1;
                                AIBrain.teamBombs[brain.currentPosition + new Node(0, 1)] = farBombDropTime + 1;

                                AIBrain.teamBombs[brain.currentPosition + new Node(1, 0)] = farBombDropTime + 1;
                            }
                            else
                            {
                                brain.bombs[brain.currentPosition + new Node(-1, 0)] = farBombDropTime + 1;

                                brain.bombs[brain.currentPosition + new Node(0, -1)] = farBombDropTime + 1;
                                brain.bombs[brain.currentPosition + new Node(0, 0)] = farBombDropTime + 1;
                                brain.bombs[brain.currentPosition + new Node(0, 1)] = farBombDropTime + 1;

                                brain.bombs[brain.currentPosition + new Node(1, 0)] = farBombDropTime + 1;
                            }

                            // Update our current position
                            GetNewPosition(aMoves);

                            // Update bomb times
                            brain.UpdateBombTimes();

                            // Move to the next position
                            return CombatantAction.DropBomb;
                        }

                        break;


                    // Return to the exit
                    case DefenderState.GoExit:

                        // Update the next state
                        state = DefenderState.BombExit;

                        // Move to the next position
                        if (AIBrain.shareTeamInformation && brain.hasLinked)
                        {
                            aMoves = brain.GetMovements(AStar.Search(brain.currentPosition, GetExitOffset(), AIBrain.teamAvailable, AIBrain.teamOccupied));
                        }
                        else
                        {
                            aMoves = brain.GetMovements(AStar.Search(brain.currentPosition, GetExitOffset(), brain.available, brain.occupied));
                        }

                        // Update our current position
                        GetNewPosition(aMoves);

                        // Update bomb times
                        brain.UpdateBombTimes();

                        // Check for failure to move
                        if (AIBrain.explodeOnFailure && aMoves == null && AIBrain.shareTeamInformation && brain.hasLinked)
                        {
                            if (MapSpace.SpaceContains(UseSensor(GameManager.Direction.Current), GameManager.SensorData.Goal))
                            {
                                aMoves = new List<GameManager.Direction>
                                {
                                    GameManager.Direction.Up
                                };

                                return CombatantAction.Move;
                            }
                            else
                            {
                                Debug.Log("AI " + AIName + " did not successfully link! EXPLODING!");

                                aMoves = new List<GameManager.Direction>();

                                aBombTime = 1;

                                AIBrain.teamBombs[brain.currentPosition + new Node(-1, 0)] = 1;

                                AIBrain.teamBombs[brain.currentPosition + new Node(0, -1)] = 1;
                                AIBrain.teamBombs[brain.currentPosition + new Node(0, 0)] = 1;
                                AIBrain.teamBombs[brain.currentPosition + new Node(0, 1)] = 1;

                                AIBrain.teamBombs[brain.currentPosition + new Node(1, 0)] = 1;

                                return CombatantAction.DropBomb;
                            }
                        }
                        else if (aMoves == null)
                        {
                            aMoves = new List<GameManager.Direction>();
                        }

                        // Move to the next position
                        return CombatantAction.Move;
                }


                // No exit found, continue searching

                // Move to the next position
                if (AIBrain.shareTeamInformation && brain.hasLinked)
                {
                    aMoves = brain.GetMovements(AStar.Search(brain.currentPosition, GetNextPosition(), AIBrain.teamAvailable, AIBrain.teamOccupied));
                }
                else
                {
                    aMoves = brain.GetMovements(AStar.Search(brain.currentPosition, GetNextPosition(), brain.available, brain.occupied));
                }

                // Update our current position
                GetNewPosition(aMoves);

                // Update bomb times
                brain.UpdateBombTimes();

                // Check for failure to move
                if (AIBrain.explodeOnFailure && aMoves == null && AIBrain.shareTeamInformation && brain.hasLinked)
                {
                    if (MapSpace.SpaceContains(UseSensor(GameManager.Direction.Current), GameManager.SensorData.Goal))
                    {
                        aMoves = new List<GameManager.Direction>
                                {
                                    GameManager.Direction.Up
                                };

                        return CombatantAction.Move;
                    }
                    else
                    {
                        Debug.Log("AI " + AIName + " did not successfully link! EXPLODING!");

                        aMoves = new List<GameManager.Direction>();

                        aBombTime = 1;

                        AIBrain.teamBombs[brain.currentPosition + new Node(-1, 0)] = 1;

                        AIBrain.teamBombs[brain.currentPosition + new Node(0, -1)] = 1;
                        AIBrain.teamBombs[brain.currentPosition + new Node(0, 0)] = 1;
                        AIBrain.teamBombs[brain.currentPosition + new Node(0, 1)] = 1;

                        AIBrain.teamBombs[brain.currentPosition + new Node(1, 0)] = 1;

                        return CombatantAction.DropBomb;
                    }
                }
                else if (aMoves == null)
                {
                    aMoves = new List<GameManager.Direction>();
                }

                // Move to the next position
                return CombatantAction.Move;
            }

            // Defender AI logic
            public override Node GetNextPosition()
            {
                // Store the next position
                Node nextposition = Node.zero;

                // Check if we have linked our map
                if (AIBrain.shareTeamInformation && brain.hasLinked)
                {
                    // Check if there are any remaining unexplored positions
                    if (AIBrain.teamUnexplored.Count == 1)
                    {
                        nextposition = AIBrain.teamUnexplored[0];
                    }
                    else if (AIBrain.teamUnexplored.Count == 0)
                    {
                        if (AIBrain.shareTeamInformation)
                        {
                            AIBrain.friendlyFire = true;
                        }

                        Debug.Log("AI " + AIName + " found all unexplored locations!");

                        nextposition = AIBrain.teamAvailable.Count > 0 ? AIBrain.teamAvailable[Random.Range(0, AIBrain.teamAvailable.Count)] : Node.zero;
                    }
                    else
                    {
                        // NOTE FROM DEVELOPER: You can change the order of which direction gets priority here!

                        // Store which direction we are next exploring
                        GameManager.Direction exploredDirection;

                        // Left check
                        if (leftExplorations <= upExplorations && leftExplorations <= downExplorations && leftExplorations <= rightExplorations)
                        {
                            exploredDirection = GameManager.Direction.Left;
                        }
                        // Right check
                        else if (rightExplorations <= upExplorations && rightExplorations <= downExplorations && rightExplorations <= leftExplorations)
                        {
                            exploredDirection = GameManager.Direction.Right;
                        }
                        // Up check
                        else if (upExplorations <= downExplorations && upExplorations <= leftExplorations && upExplorations <= rightExplorations)
                        {
                            exploredDirection = GameManager.Direction.Up;
                        }
                        // Down check
                        else
                        {
                            exploredDirection = GameManager.Direction.Down;
                        }

                        // Pick which explored direction to check
                        switch (exploredDirection)
                        {
                            case GameManager.Direction.Up:

                                // Increment the direction we are going
                                upExplorations++;

                                // Store the next position
                                nextposition = AIBrain.teamUnexplored[0];

                                // Loop through each other position
                                for (int i = 1; i < AIBrain.teamUnexplored.Count; i++)
                                {
                                    // Check if that unexplored position is further in this direction
                                    if (AIBrain.teamUnexplored[i].y > nextposition.y)
                                    {
                                        nextposition = AIBrain.teamUnexplored[i];
                                    }
                                }

                                break;

                            case GameManager.Direction.Down:

                                // Increment the direction we are going
                                downExplorations++;

                                // Store the next position
                                nextposition = AIBrain.teamUnexplored[0];

                                // Loop through each other position
                                for (int i = 1; i < AIBrain.teamUnexplored.Count; i++)
                                {
                                    // Check if that unexplored position is further in this direction
                                    if (AIBrain.teamUnexplored[i].y < nextposition.y)
                                    {
                                        nextposition = AIBrain.teamUnexplored[i];
                                    }
                                }

                                break;

                            case GameManager.Direction.Left:

                                // Increment the direction we are going
                                leftExplorations++;

                                // Store the next position
                                nextposition = AIBrain.teamUnexplored[0];

                                // Loop through each other position
                                for (int i = 1; i < AIBrain.teamUnexplored.Count; i++)
                                {
                                    // Check if that unexplored position is further in this direction
                                    if (AIBrain.teamUnexplored[i].x < nextposition.x)
                                    {
                                        nextposition = AIBrain.teamUnexplored[i];
                                    }
                                }

                                break;

                            case GameManager.Direction.Right:

                                // Increment the direction we are going
                                rightExplorations++;

                                // Store the next position
                                nextposition = AIBrain.teamUnexplored[0];

                                // Loop through each other position
                                for (int i = 1; i < AIBrain.teamUnexplored.Count; i++)
                                {
                                    // Check if that unexplored position is further in this direction
                                    if (AIBrain.teamUnexplored[i].x > nextposition.x)
                                    {
                                        nextposition = AIBrain.teamUnexplored[i];
                                    }
                                }

                                break;
                        }
                    }

                    // Make sure that next position is not a bomb
                    if (AIBrain.teamBombs.ContainsKey(nextposition))
                    {
                        for (int i = 0; i < AIBrain.teamUnexplored.Count; i++)
                        {
                            // Find another position
                            if (!AIBrain.teamBombs.ContainsKey(AIBrain.teamUnexplored[i]))
                            {
                                nextposition = AIBrain.teamUnexplored[i];

                                break;
                            }
                        }
                    }

                    // REALLY make sure that next position is not a bomb
                    if (AIBrain.teamBombs.ContainsKey(nextposition))
                    {
                        for (int i = 0; i < AIBrain.teamAvailable.Count; i++)
                        {
                            // Find another position
                            if (!AIBrain.teamBombs.ContainsKey(AIBrain.teamAvailable[i]))
                            {
                                nextposition = AIBrain.teamAvailable[i];

                                break;
                            }
                        }
                    }

                    // We are dead
                    if (AIBrain.teamBombs.ContainsKey(nextposition))
                    {
                        Debug.Log("UH OH!");
                    }

                    // Remove the next position
                    AIBrain.teamUnexplored.Remove(nextposition);

                    // Return the next position
                    return nextposition;
                }
                else
                {
                    // Check if there are any remaining unexplored positions
                    if (brain.unexplored.Count == 1)
                    {
                        nextposition = brain.unexplored[0];
                    }
                    else if (brain.unexplored.Count == 0)
                    {
                        if (AIBrain.shareTeamInformation)
                        {
                            AIBrain.friendlyFire = true;
                        }

                        Debug.Log("AI " + AIName + " found all unexplored locations!");

                        nextposition = brain.available.Count > 0 ? brain.available[Random.Range(0, brain.available.Count)] : Node.zero;
                    }
                    else
                    {
                        // NOTE FROM DEVELOPER: You can change the order of which direction gets priority here!

                        // Store which direction we are next exploring
                        GameManager.Direction exploredDirection;

                        // Left check
                        if (leftExplorations <= upExplorations && leftExplorations <= downExplorations && leftExplorations <= rightExplorations)
                        {
                            exploredDirection = GameManager.Direction.Left;
                        }
                        // Right check
                        else if (rightExplorations <= upExplorations && rightExplorations <= downExplorations && rightExplorations <= leftExplorations)
                        {
                            exploredDirection = GameManager.Direction.Right;
                        }
                        // Up check
                        else if (upExplorations <= downExplorations && upExplorations <= leftExplorations && upExplorations <= rightExplorations)
                        {
                            exploredDirection = GameManager.Direction.Up;
                        }
                        // Down check
                        else
                        {
                            exploredDirection = GameManager.Direction.Down;
                        }

                        // Pick which explored direction to check
                        switch (exploredDirection)
                        {
                            case GameManager.Direction.Up:

                                // Increment the direction we are going
                                upExplorations++;

                                // Store the next position
                                nextposition = brain.unexplored[0];

                                // Loop through each other position
                                for (int i = 1; i < brain.unexplored.Count; i++)
                                {
                                    // Check if that unexplored position is further in this direction
                                    if (brain.unexplored[i].y > nextposition.y)
                                    {
                                        nextposition = brain.unexplored[i];
                                    }
                                }

                                break;

                            case GameManager.Direction.Down:

                                // Increment the direction we are going
                                downExplorations++;

                                // Store the next position
                                nextposition = brain.unexplored[0];

                                // Loop through each other position
                                for (int i = 1; i < brain.unexplored.Count; i++)
                                {
                                    // Check if that unexplored position is further in this direction
                                    if (brain.unexplored[i].y < nextposition.y)
                                    {
                                        nextposition = brain.unexplored[i];
                                    }
                                }

                                break;

                            case GameManager.Direction.Left:

                                // Increment the direction we are going
                                leftExplorations++;

                                // Store the next position
                                nextposition = brain.unexplored[0];

                                // Loop through each other position
                                for (int i = 1; i < brain.unexplored.Count; i++)
                                {
                                    // Check if that unexplored position is further in this direction
                                    if (brain.unexplored[i].x < nextposition.x)
                                    {
                                        nextposition = brain.unexplored[i];
                                    }
                                }

                                break;

                            case GameManager.Direction.Right:

                                // Increment the direction we are going
                                rightExplorations++;

                                // Store the next position
                                nextposition = brain.unexplored[0];

                                // Loop through each other position
                                for (int i = 1; i < brain.unexplored.Count; i++)
                                {
                                    // Check if that unexplored position is further in this direction
                                    if (brain.unexplored[i].x > nextposition.x)
                                    {
                                        nextposition = brain.unexplored[i];
                                    }
                                }

                                break;
                        }
                    }

                    // Make sure that next position is not a bomb
                    if (brain.bombs.ContainsKey(nextposition))
                    {
                        for (int i = 0; i < brain.unexplored.Count; i++)
                        {
                            // Find another position
                            if (!brain.bombs.ContainsKey(brain.unexplored[i]))
                            {
                                nextposition = brain.unexplored[i];

                                break;
                            }
                        }
                    }

                    // REALLY make sure that next position is not a bomb
                    if (brain.bombs.ContainsKey(nextposition))
                    {
                        for (int i = 0; i < brain.available.Count; i++)
                        {
                            // Find another position
                            if (!brain.bombs.ContainsKey(brain.available[i]))
                            {
                                nextposition = brain.available[i];

                                break;
                            }
                        }
                    }

                    // We are dead
                    if (brain.bombs.ContainsKey(nextposition))
                    {
                        Debug.Log("UH OH!");
                    }

                    // Remove the next position
                    brain.unexplored.Remove(nextposition);

                    // Return the next position
                    return nextposition;
                }
            }

            // Returns the offset to the exit to visit once the exit is found
            private Node GetExitOffset()
            {
                exitOffset = (GameManager.Direction)(((int)exitOffset + 1) % 4);

                if (AIBrain.shareTeamInformation && brain.hasLinked)
                {
                    // Check for bombs
                    if (AIBrain.teamBombs.ContainsKey(AIBrain.teamExit + new Node(0, 1)) || AIBrain.teamBombs.ContainsKey(AIBrain.teamExit + new Node(0, -1)) ||
                        AIBrain.teamBombs.ContainsKey(AIBrain.teamExit + new Node(-1, 0)) || AIBrain.teamBombs.ContainsKey(AIBrain.teamExit + new Node(1, 0)) ||
                        AIBrain.teamBombs.ContainsKey(AIBrain.teamExit))
                    {
                        // Find safe position
                        return GetNextPosition();
                    }

                    // Go to a spot by or at the exit
                    switch (exitOffset)
                    {
                        default:

                            return GetExitOffset();

                        case GameManager.Direction.Up:

                            return !AIBrain.teamOccupied.Contains(AIBrain.teamExit + new Node(0, 1)) ? AIBrain.teamExit + new Node(0, 1) : GetExitOffset();

                        case GameManager.Direction.Down:

                            return !AIBrain.teamOccupied.Contains(AIBrain.teamExit + new Node(0, -1)) ? AIBrain.teamExit + new Node(0, -1) : GetExitOffset();

                        case GameManager.Direction.Left:

                            return !AIBrain.teamOccupied.Contains(AIBrain.teamExit + new Node(-1, 0)) ? AIBrain.teamExit + new Node(-1, 0) : GetExitOffset();

                        case GameManager.Direction.Right:

                            return !AIBrain.teamOccupied.Contains(AIBrain.teamExit + new Node(1, 0)) ? AIBrain.teamExit + new Node(1, 0) : GetExitOffset();
                    }
                }
                else
                {
                    // Check for bombs
                    if (brain.bombs.ContainsKey(brain.exit + new Node(0, 1)) || brain.bombs.ContainsKey(brain.exit + new Node(0, -1)) ||
                        brain.bombs.ContainsKey(brain.exit + new Node(-1, 0)) || brain.bombs.ContainsKey(brain.exit + new Node(1, 0)) ||
                        brain.bombs.ContainsKey(brain.exit))
                    {
                        // Find safe position
                        return GetNextPosition();
                    }

                    // Go to a spot by or at the exit
                    switch (exitOffset)
                    {
                        default:

                            return GetExitOffset();

                        case GameManager.Direction.Up:

                            return !brain.occupied.Contains(brain.exit + new Node(0, 1)) ? brain.exit + new Node(0, 1) : GetExitOffset();

                        case GameManager.Direction.Down:

                            return !brain.occupied.Contains(brain.exit + new Node(0, -1)) ? brain.exit + new Node(0, -1) : GetExitOffset();

                        case GameManager.Direction.Left:

                            return !brain.occupied.Contains(brain.exit + new Node(-1, 0)) ? brain.exit + new Node(-1, 0) : GetExitOffset();

                        case GameManager.Direction.Right:

                            return !brain.occupied.Contains(brain.exit + new Node(1, 0)) ? brain.exit + new Node(1, 0) : GetExitOffset();
                    }
                }
            }
        }
    }
}
