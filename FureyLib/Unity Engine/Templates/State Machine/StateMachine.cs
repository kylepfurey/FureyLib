
// Template State Machine Script
// by Kyle Furey

using UnityEngine;

/// <summary>
/// Base for building a state machine.
/// </summary>
public class StateMachine : MonoBehaviour
{
    // STATE MACHINE VARIABLES

    /// <summary>
    /// The current state of this state machine.
    /// </summary>
    private StateBase _currentState = null;

    /// <summary>
    /// The state to start this state machine in.
    /// </summary>
    private StateBase _startingState = null;


    // STATE MACHINE PROPERTIES

    /// <summary>
    /// Returns this state machine's current state.
    /// </summary>
    public StateBase currentState { get { return _currentState; } }

    /// <summary>
    /// Gets or sets the state this state machine starts in.
    /// </summary>
    public StateBase startingState { get { return _startingState; } set { if (_startingState == null) { _startingState = value; } } }

    /// <summary>
    /// Returns whether this state machine's current state is null.
    /// </summary>
    public bool nullState { get { return _currentState == null; } }


    // UNITY FUNCTIONS

    /// <summary>
    /// Instantiates the starting state.
    /// </summary>
    private void Start()
    {
        // Sets the current state as the starting state
        SwitchState(_startingState);
    }

    /// <summary>
    /// Properly destroys the current state.
    /// </summary>
    private void OnDestroy()
    {
        SwitchState(null);
    }

    /// <summary>
    /// Calls the update function based on the current state.
    /// </summary>
    private void Update()
    {
        // Call the current state's update function
        if (_currentState != null)
        {
            _currentState.OnStateUpdate(Time.deltaTime);
        }
    }


    // STATE MACHINE GETTERS

    /// <summary>
    /// Returns this state machine's current state.
    /// </summary>
    /// <returns></returns>
    public StateBase GetCurrentState()
    {
        return _currentState;
    }

    /// <summary>
    /// Returns the state this state machine started in.
    /// </summary>
    /// <returns></returns>
    public StateBase GetStartingState()
    {
        return _startingState;
    }

    /// <summary>
    /// Returns whether this state machine's current state is null.
    /// </summary>
    /// <returns></returns>
    public bool IsStateNull()
    {
        return _currentState == null;
    }


    // STATE MACHINE FUNCTIONS

    /// <summary>
    /// Properly switches the state machine's current state.<br/>
    /// Returns whether the switch was successful.
    /// </summary>
    /// <param name="newState"></param>
    public void SwitchState(StateBase newState)
    {
        StateBase previousState;

        if (_currentState != null)
        {
            previousState = _currentState;

            _currentState.OnStateExit(newState);
        }
        else
        {
            previousState = null;
        }

        if (newState != null)
        {
            _currentState = newState;

            _currentState.OnStateStart(previousState);
        }
        else
        {
            _currentState = null;
        }
    }
}

/// <summary>
/// The base class for each state. All states should inherit from this class.
/// </summary>
public abstract class StateBase
{
    // STATE BASE VARIABLES

    /// <summary>
    /// The inherited state machine from the owner.
    /// </summary>
    protected StateMachine _stateMachine = null;


    // STATE BASE PROPERTIES

    /// <summary>
    /// Returns this state's state machine.
    /// </summary>
    public virtual StateMachine stateMachine { get { return _stateMachine; } }

    /// <summary>
    /// Returns this state's owning game object.
    /// </summary>
    public virtual GameObject gameObject { get { return _stateMachine != null ? _stateMachine.gameObject : null; } }


    // STATE BASE CONSTRUCTOR

    /// <summary>
    /// State machine constructor.
    /// </summary>
    /// <param name="stateMachine"></param>
    public StateBase(StateMachine stateMachine = null)
    {
        _stateMachine = stateMachine;
    }


    // STATE BASE FUNCTIONS

    /// <summary>
    /// Returns this state's state machine.
    /// </summary>
    /// <returns></returns>
    public virtual StateMachine GetStateMachine()
    {
        return _stateMachine;
    }

    /// <summary>
    /// Returns this state's owning game object.
    /// </summary>
    /// <returns></returns>
    public virtual GameObject GetGameObject()
    {
        return _stateMachine != null ? _stateMachine.gameObject : null;
    }


    // STATE BASE EVENTS

    /// <summary>
    /// Called when this state is set as the state machine's current state.
    /// </summary>
    public virtual void OnStateStart(StateBase previousState)
    {
        // Note: Logic applies to all inherited states

        // New code here
    }

    /// <summary>
    /// Called every frame while this state is the state machine's current state.
    /// </summary>
    public virtual void OnStateUpdate(float deltaTime)
    {
        // Note: Logic applies to all inherited states

        // New code here
    }

    /// <summary>
    /// Called when this state machine's current state is no longer this state.
    /// </summary>
    public virtual void OnStateExit(StateBase newState)
    {
        // Note: Logic applies to all inherited states

        // New code here
    }
}
