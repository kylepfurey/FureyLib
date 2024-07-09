
// Template State Machine Script
// by Kyle Furey

/// <summary>
/// State machine states enum
/// </summary>
public enum StateType
{
    None = 0,
    State = 1
};

/// <summary>
/// Base for building an state machine.
/// </summary>
public class StateMachine
{
    /// <summary>
    /// The current state of this state machine
    /// </summary>
    public StateBase currentState = null;

    /// <summary>
    /// The current state of this state machine
    /// </summary>
    public States currentStateType = StateType.None;

    /// <summary>
    /// Starting state constructor
    /// </summary>
    /// <param name="newState"></param>
    public StateMachine(StateBase newState)
    {
        SwitchState(newState);
    }

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
    /// Updates the current state (should be called each tick)
    /// </summary>
    public void Tick()
    {
        // Call the current state's update function
        if (currentState != null)
        {
            currentState.OnStateUpdate();
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
    /// Called when this state is set as the state machine's current state
    /// </summary>
    public virtual void OnStateEnter()
    {
        // Note: Logic applies to all inherited states
    }

    /// <summary>
    /// Called every frame while this state is the state machine's current state
    /// </summary>
    public virtual void OnStateUpdate()
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
}
