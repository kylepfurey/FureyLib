
// Template State Machine State Script
// by Kyle Furey

using UnityEngine;

// A template for a new state machine state.
public class State : StateBase
{
    // Constructor (sets state machine and gameobject)
    public State(StateMachine StateMachine, GameObject GameObject)
    {
        stateMachine = StateMachine;

        // Change the state type enum here!
        stateMachine.currentStateType = StateType.State;
    }

    // Called when this state is set as the state machine's current state
    public override void OnStateEnter()
    {
        // Calls the base class's function
        base.OnStateEnter();
    }

    // Called when this state machine's current state is no longer this state
    public override void OnStateExit()
    {
        // Calls the base class's function
        base.OnStateExit();
    }

    // Called every frame while this state is the state machine's current state
    public override void StateUpdate()
    {
        // Calls the base class's function
        base.StateUpdate();
    }
}
