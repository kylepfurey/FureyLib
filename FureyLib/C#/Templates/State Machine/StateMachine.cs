
// Template State Machine Script
// by Kyle Furey

// Base for building an state machine.
public class StateMachine
{
    // The current state of this state machine
    public StateBase currentState = null;

    // Starting state constructor
    public StateMachine(StateBase newState = null)
    {
        Start(newState);
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
        Update();
    }

    // Instantiates the starting state
    private void Start(StateBase newState)
    {
        // Sets the current state as the starting state (should be changed from template state)
        SwitchState(newState);
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
