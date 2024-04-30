using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "RandomAI", menuName = "AI/Random AI")]
public class RandomAI : BaseAI
{
    // Data here!

    public override CombatantAction GetAction(ref List<GameManager.Direction> aMoves, ref int aBombTime)
    {
        int choice = UnityEngine.Random.Range(0, 2);

        switch(choice)
        {
            case 0:
                int numberOfMoves = UnityEngine.Random.Range(1, 9);
                for (int i=0; i<numberOfMoves; i++)
                {
                    aMoves.Add((GameManager.Direction)UnityEngine.Random.Range(0, 4));
                }
                return CombatantAction.Move;
            case 1:
                // Drop bomb
                aBombTime = 5;
                return CombatantAction.DropBomb;
        }

        return CombatantAction.Pass;
    }
}
