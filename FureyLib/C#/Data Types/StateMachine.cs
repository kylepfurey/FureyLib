// .cs
// Functional State Machine Type
// by Kyle Furey

using System;

/// <summary>
/// A system that manages data via states that can transition into a finite number of other states.s
/// </summary>
public sealed class StateMachine<Type>
{
    // STATE

    /// <summary>
    /// Represents single function that acts as the state machine's current state.<br/>
    /// This function takes a state machine as its only parameter.<br/>
    /// This function returns the next state for the state machine to execute.
    /// </summary>
    public delegate STATE STATE(StateMachine<Type> SM);


    // DATA

    /// <summary>
    /// The current state of this state machine.
    /// </summary>
    public STATE State { get; private set; }

    /// <summary>
    /// The managed data by this state machine.
    /// </summary>
    public Type Data { get; set; }


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor.
    /// </summary>
    public StateMachine(Type Data = default(Type), STATE StartingState = null)
    {
        this.State = StartingState;
        this.Data = Data;
    }

    /// <summary>
    /// Default constructor.
    /// </summary>
    public StateMachine(STATE StartingState, Type Data = default(Type))
    {
        this.State = StartingState;
        this.Data = Data;
    }


    // GETTERS

    /// <summary>
    /// Returns the state machine's managed data.
    /// </summary>
    public Type Get()
    {
        return Data;
    }

    /// <summary>
    /// Returns whether the state machine's current state is valid.
    /// </summary>
    public bool IsValidState()
    {
        return State != null;
    }


    // SETTERS

    /// <summary>
    /// Forcefully switches the state machine's current state to the given state.<br/>
    /// NOTE: This does not execute the new state.
    /// </summary>
    public void Switch(STATE NewState)
    {
        State = NewState;
    }

    /// <summary>
    /// Sets the state machine's managed data to the given data.
    /// </summary>
    public void Set(Type NewData)
    {
        Data = NewData;
    }


    // EXECUTION

    /// <summary>
    /// Executes the state machine's current state.<br/>
    /// The current state's returned state will be the state machine's new state.<br/>
    /// Returns the state machine's new state.
    /// </summary>
    public STATE Execute()
    {
        if (State != null)
        {
            State = State(this);
        }

        return State;
    }
}
