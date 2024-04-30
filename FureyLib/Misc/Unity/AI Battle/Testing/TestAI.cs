using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "TestAI", menuName = "AI/Test AI")]
public class TestAI : BaseAI
{
    // Data here!

    public override CombatantAction GetAction(ref List<GameManager.Direction> aMoves, ref int aBombTime)
    {
        // Check if there is a wall above us
        if ((UseSensor(GameManager.Direction.Up) & GameManager.SensorData.Clear) != 0)
        {
            aMoves.Add(GameManager.Direction.Up);
            return CombatantAction.Move;
        }
        else
        {
            aMoves.Add(GameManager.Direction.Down);
            return CombatantAction.Move;
        }
    }
}
