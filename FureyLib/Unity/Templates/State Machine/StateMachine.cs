
// Template State Machine Script
// by Kyle Furey

using UnityEngine;

// State machine states enum
public enum StateType
{
    NULL = 0,
    State = 1
};

// Base for building a state machine.
public class StateMachine : MonoBehaviour
{
    // The current state of this state machine
    public StateBase currentState = null;

    // The current state of this state machine
    public StateType currentStateType = StateType.NULL;

    // Properly switches the state machine's current state
    public void SwitchState(StateBase newState)
    {
        // Exit the current state
        if (currentState != null)
        {
            currentState.OnStateExit();
        }

        // Switch the current state to the new state
        currentState = newState;

        // Enter the new state
        if (currentState != null)
        {
            currentState.OnStateEnter();
        }
    }

    // Instantiates the starting state (should be changed from template)
    private void Start()
    {
        // Sets the current state as the starting state (should be changed from template state)
        SwitchState(new State(this, gameObject));
    }

    // Calls the update function based on the current state
    private void Update()
    {
        // Call the current state's update function
        if (currentState != null)
        {
            currentState.StateUpdate();
        }
    }
}

// The base class for each state. All states should inherit from this class.
public abstract class StateBase
{
    // The inherited state machine from the owner
    protected StateMachine stateMachine = null;

    // The inherited gameobject from the state machine's owner
    protected GameObject gameObject => stateMachine.gameObject;

    // Called when this state is set as the state machine's current state
    public virtual void OnStateEnter()
    {
        // Note: Logic applies to all inherited states
    }

    // Called when this state machine's current state is no longer this state
    public virtual void OnStateExit()
    {
        // Note: Logic applies to all inherited states
    }

    // Called every frame while this state is the state machine's current state
    public virtual void StateUpdate()
    {
        // Note: Logic applies to all inherited states
    }
}
