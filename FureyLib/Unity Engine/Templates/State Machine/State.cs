
// Template State Machine State Script
// by Kyle Furey

using UnityEngine;

/// <summary>
/// A template for a new state machine state.
/// </summary>
public class State : StateBase
{
    // STATE VARIABLES

    // New variables here


    // STATE PROPERTIES

    // New properties here


    // STATE CONSTRUCTOR

    /// <summary>
    /// State machine constructor.
    /// </summary>
    /// <param name="stateMachine"></param>
    public State(StateMachine stateMachine = null)
    {
        _stateMachine = stateMachine;

        // Initialize variables here
    }


    // STATE EVENTS

    /// <summary>
    /// Called when this state is set as the state machine's current state.
    /// </summary>
    public override void OnStateStart(StateBase previousState)
    {
        // Calls the base class's function
        base.OnStateStart(previousState);

        // New code here
    }

    /// <summary>
    /// Called every frame while this state is the state machine's current state.
    /// </summary>
    public override void OnStateUpdate(float deltaTime)
    {
        // Calls the base class's function
        base.OnStateUpdate(deltaTime);

        // New code here
    }

    /// <summary>
    /// Called when this state machine's current state is no longer this state.
    /// </summary>
    public override void OnStateExit(StateBase newState)
    {
        // Calls the base class's function
        base.OnStateExit(newState);

        // New code here
    }
}
