
// Template State Machine State Script
// by Kyle Furey

using UnityEngine;

/// <summary>
/// A template for a new state machine state.
/// </summary>
public class State : StateBase
{
    /// <summary>
    /// Constructor (sets state machine)
    /// </summary>
    /// <param name="stateMachine"></param>
    public State(StateMachine stateMachine)
    {
        this.stateMachine = stateMachine;
    }

    /// <summary>
    /// Called when this state is set as the state machine's current state
    /// </summary>
    public override void OnStateEnter()
    {
        // Calls the base class's function
        base.OnStateEnter();
    }

    /// <summary>
    /// Called every frame while this state is the state machine's current state
    /// </summary>
    public override void OnStateUpdate()
    {
        // Calls the base class's function
        base.OnStateUpdate();
    }

    /// <summary>
    /// Called when this state machine's current state is no longer this state
    /// </summary>
    public override void OnStateExit()
    {
        // Calls the base class's function
        base.OnStateExit();
    }
}
