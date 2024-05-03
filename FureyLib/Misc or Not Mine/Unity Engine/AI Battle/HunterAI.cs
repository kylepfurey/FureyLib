
// AI Battle - Hunter AI Class Script
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

        // AI entity that explores in one direction if that direction is still available to explore.
        // Places bombs on sight of another player and attempts to follow their direction.
        // Grabs the key if it is found, exits if the key is held and the exit is located.
        // Avoids bombs at all costs unless the bomb is their own and is not about to detonate.


        // Hunter AI class.
        [CreateAssetMenu(fileName = "HunterAI", menuName = "AI/AI Team/Hunter AI", order = 1)]
        public class HunterAI : AIBase
        {
            // SETTINGS

            // The time to drop bombs for when enemies are being followed
            private const int followBombDropTime = 2;


            // DATA

            // The direction for this hunter to explore (changed based on found enemies)
            private GameManager.Direction exploredDirection = GameManager.Direction.Left;


            // CONSTRUCTORS

            // Default constructor
            public HunterAI()
            {
                brain = new AIBrain();

                brain.classType = AIClass.Hunter;
            }

            // AI brain constructor
            public HunterAI(AIBrain brain)
            {
                this.brain = brain;

                this.brain.classType = AIClass.Hunter;
            }


            // FUNCTIONS

            // The function automatically called to select the AI's next action(s)
            public override CombatantAction GetAction(ref List<GameManager.Direction> aMoves, ref int aBombTime)
            {
                // Set our starting direction
                if (brain.firstTurn)
                {
                    exploredDirection = (GameManager.Direction)Random.Range(0, 4);
                }

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

                // Check for enemy players
                if (brain.sensorData.FindData(GameManager.SensorData.Enemy))
                {
                    // Check that the enemy player is not an ally and there are no nearby bombs
                    if (!brain.CheckForAllies() && !brain.sensorData.FindData(GameManager.SensorData.Bomb) && !brain.firstTurn)
                    {
                        Debug.Log("AI " + AIName + " found an enemy!");

                        // Drop a bomb
                        aBombTime = followBombDropTime + 1;

                        // Mark all bomb positions
                        if (AIBrain.shareTeamInformation && brain.hasLinked)
                        {
                            AIBrain.teamBombs[brain.currentPosition + new Node(-1, 0)] = followBombDropTime + 1;

                            AIBrain.teamBombs[brain.currentPosition + new Node(0, -1)] = followBombDropTime + 1;
                            AIBrain.teamBombs[brain.currentPosition + new Node(0, 0)] = followBombDropTime + 1;
                            AIBrain.teamBombs[brain.currentPosition + new Node(0, 1)] = followBombDropTime + 1;

                            AIBrain.teamBombs[brain.currentPosition + new Node(1, 0)] = followBombDropTime + 1;
                        }
                        else
                        {
                            brain.bombs[brain.currentPosition + new Node(-1, 0)] = followBombDropTime + 1;

                            brain.bombs[brain.currentPosition + new Node(0, -1)] = followBombDropTime + 1;
                            brain.bombs[brain.currentPosition + new Node(0, 0)] = followBombDropTime + 1;
                            brain.bombs[brain.currentPosition + new Node(0, 1)] = followBombDropTime + 1;

                            brain.bombs[brain.currentPosition + new Node(1, 0)] = followBombDropTime + 1;
                        }

                        // Follow that AI's direction
                        brain.sensorData.FindData(GameManager.SensorData.Enemy, out exploredDirection);

                        // Update our current position
                        GetNewPosition(aMoves);

                        // Update bomb times
                        brain.UpdateBombTimes();

                        // Move to the next position
                        return CombatantAction.DropBomb;
                    }
                }

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

            // Hunter AI logic
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

                        // Pick which explored direction to check
                        switch (exploredDirection)
                        {
                            case GameManager.Direction.Up:

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

                        // Pick which explored direction to check
                        switch (exploredDirection)
                        {
                            case GameManager.Direction.Up:

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
        }
    }
}
