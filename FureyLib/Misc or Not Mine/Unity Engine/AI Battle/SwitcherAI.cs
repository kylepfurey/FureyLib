
// AI Battle - Multi-Class AI Class Script
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


        // AI TRAITS

        // AI entity that can change its behaviour dynamically based on its set AI class.


        // Switcher AI class.
        [CreateAssetMenu(fileName = "SwitcherAI", menuName = "AI/AI Team/Switcher AI", order = 3)]
        public class SwitcherAI : AIBase
        {
            // SETTINGS

            // The AI's starting class
            // NOTE FROM DEVELOPER: You can change the SwitcherAI's default class here.
            private const AIClass startingClass = AIClass.Hunter;

            // The AI's class if it grabs the key
            private const AIClass keyClass = AIClass.Scout;
            private const bool swapToKeyClass = true;

            // The AI's class if it finds the exit
            private const AIClass exitClass = AIClass.Defender;
            private const bool swapToExitClass = false;

            // Whether this AI will swap its class at random each turn
            private const bool randomizeClass = false;


            // DATA

            // The AI's current class
            private AIBase currentClass = null;


            // CONSTRUCTORS

            // Default constructor
            public SwitcherAI()
            {
                brain = new AIBrain();

                brain.classType = AIClass.Switcher;
            }

            // AI brain constructor
            public SwitcherAI(AIBrain brain)
            {
                this.brain = brain;

                brain.classType = AIClass.Switcher;
            }


            // FUNCTIONS

            // The function automatically called to select the AI's next action(s) depending on its current AI class
            public override CombatantAction GetAction(ref List<GameManager.Direction> aMoves, ref int aBombTime)
            {
                Debug.Log("AI " + AIName + "'s turn!");

                // Register the AI to the AI team if the AI has not already
                brain.RegisterAI(this);

                // Pass the current team index to ensure no AI have died, and if so share that information with the team
                brain.PassIndex();

                // Set our starting class
                if (brain.firstTurn)
                {
                    SwapClass();

                    brain.firstTurn = false;
                }

                // Check if we have the key
                if (swapToKeyClass && brain.hasKey && currentClass.brain.classType != keyClass)
                {
                    Debug.Log("AI " + AIName + " now has the key and will now become the " + Enum.GetName(typeof(AIClass), keyClass) + " class.");

                    SwapClass(keyClass);
                }
                else if (swapToExitClass && ((AIBrain.shareTeamInformation && AIBrain.teamFoundExit && brain.hasLinked) || brain.foundExit) && currentClass.brain.classType != exitClass)
                {
                    Debug.Log("AI " + AIName + " has found the exit and will now become the " + Enum.GetName(typeof(AIClass), exitClass) + " class.");

                    SwapClass(exitClass);
                }
                else if (randomizeClass)
                {
                    // Randomize the AI's class
                    AIClass randomClass = (AIClass)UnityEngine.Random.Range(1, 4);

                    if (randomClass != currentClass.brain.classType)
                    {
                        SwapClass(randomClass);

                        Debug.Log("AI " + AIName + " is randomizing its class to " + Enum.GetName(typeof(AIClass), randomClass) + ".");
                    }
                }

                // Update our information
                brain.CopyInformation(currentClass.brain);

                // Return our puppet AI's action
                return currentClass.GetAction(ref aMoves, ref aBombTime);
            }

            // Swaps the AI's current class but maintains its map information
            private void SwapClass(AIClass newClass = startingClass)
            {
                switch (newClass)
                {
                    default:

                        Debug.LogWarning("Cannot swap SwitcherAI's class! No valid class type was given!");

                        SwapClass(startingClass);

                        return;

                    case AIClass.Scout:

                        currentClass = CreateInstance<ScoutAI>();

                        break;

                    case AIClass.Hunter:

                        currentClass = CreateInstance<HunterAI>();

                        break;

                    case AIClass.Defender:

                        currentClass = CreateInstance<DefenderAI>();

                        break;
                }

                currentClass.brain = brain;

                currentClass.brain.puppet = true;

                currentClass.AIName = AIName;
            }

            // Assume the role of the destroyed class
            public override void AIDestroyed(AIClass destroyedClass)
            {
                if (!brain.hasKey)
                {
                    Debug.Log("AI " + AIName + " is swapping its class to the deceased AI. It's new class is " + Enum.GetName(typeof(AIClass), destroyedClass) + ".");

                    SwapClass(destroyedClass);
                }
            }
        }
    }
}
