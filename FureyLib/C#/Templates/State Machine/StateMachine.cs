
// Template State Machine Script
// by Kyle Furey

// State machine states enum
public enum StateType
{
    NULL = 0,
    State = 1
};

// Base for building an state machine.
public class StateMachine
{
    // The current state of this state machine
    public StateBase currentState = null;

    // The current state of this state machine
    public States currentStateType = StateType.NULL;

    // Starting state constructor
    public StateMachine(StateBase newState)
    {
        SwitchState(newState);
    }

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

    // Updates the current state (should be called each tick)
    public void Tick()
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
