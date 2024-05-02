
// Template State Machine Script
// by Kyle Furey

using UnityEngine;

/// <summary>
/// State machine states enum
/// </summary>
public enum StateType
{
    NULL = 0,
    State = 1
};

/// <summary>
/// Base for building a state machine.
/// </summary>
public class StateMachine : MonoBehaviour
{
    /// <summary>
    /// The current state of this state machine
    /// </summary>
    public StateBase currentState = null;

    /// <summary>
    /// The current state of this state machine
    /// </summary>
    public StateType currentStateType = StateType.NULL;

    /// <summary>
    /// Properly switches the state machine's current state
    /// </summary>
    /// <param name="newState"></param>
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

    /// <summary>
    /// Instantiates the starting state (should be changed from template)
    /// </summary>
    private void Start()
    {
        // Sets the current state as the starting state (should be changed from template state)
        SwitchState(new State(this, gameObject));
    }

    /// <summary>
    /// Calls the update function based on the current state
    /// </summary>
    private void Update()
    {
        // Call the current state's update function
        if (currentState != null)
        {
            currentState.StateUpdate();
        }
    }
}

/// <summary>
/// The base class for each state. All states should inherit from this class.
/// </summary>
public abstract class StateBase
{
    /// <summary>
    /// The inherited state machine from the owner
    /// </summary>
    protected StateMachine stateMachine = null;

    /// <summary>
    /// The inherited gameobject from the state machine's owner
    /// </summary>
    protected GameObject gameObject => stateMachine.gameObject;

    /// <summary>
    /// Called when this state is set as the state machine's current state
    /// </summary>
    public virtual void OnStateEnter()
    {
        // Note: Logic applies to all inherited states
    }

    /// <summary>
    /// Called when this state machine's current state is no longer this state
    /// </summary>
    public virtual void OnStateExit()
    {
        // Note: Logic applies to all inherited states
    }

    /// <summary>
    /// Called every frame while this state is the state machine's current state
    /// </summary>
    public virtual void StateUpdate()
    {
        // Note: Logic applies to all inherited states
    }
}
