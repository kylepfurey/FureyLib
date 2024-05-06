
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
    /// <param name="StateMachine"></param>
    public State(StateMachine StateMachine)
    {
        stateMachine = StateMachine;

        // Change the state type enum here!
        stateMachine.currentStateType = StateType.State;
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
    /// Called when this state machine's current state is no longer this state
    /// </summary>
    public override void OnStateExit()
    {
        // Calls the base class's function
        base.OnStateExit();
    }

    /// <summary>
    /// Called every frame while this state is the state machine's current state
    /// </summary>
    public override void StateUpdate()
    {
        // Calls the base class's function
        base.StateUpdate();
    }
}
