// .cs
// State Machine Interface and Class
// by Kyle Furey

using System;
using System.Collections;
using System.Collections.Generic;


// STATE

/// <summary>
/// An interface defining a class that can be used as a state within a state machine.
/// </summary>
public interface IState<Type>
{
    // INTERFACE

    /// <summary>
    /// The state machine that owns this state instance.
    /// </summary>
    StateMachine<Type> StateMachine { get; set; }

    /// <summary>
    /// Called when a state machine instantiates this state.
    /// </summary>
    void OnStateEnter(IState<Type> previousState);

    /// <summary>
    /// Called when a state machine updates this state.
    /// </summary>
    void OnStateUpdate(double deltaTime);

    /// <summary>
    /// Called when a state machine switches off this state.
    /// </summary>
    void OnStateExit(IState<Type> nextState);
}


// STATE MACHINE

/// <summary>
/// A class that manages its data within different states of code.
/// </summary>
public sealed class StateMachine<Type>
{
    // PROPERTIES

    /// <summary>
    /// The data this state machine is managing.
    /// </summary>
    public Type Data { get; set; } = default(Type);

    /// <summary>
    /// The current state of this state machine.
    /// </summary>
    public IState<Type> State { get; private set; } = null;

    /// <summary>
    /// The type of the state machine's current state.
    /// </summary>
    public System.Type StateType => State != null ? State.GetType() : null;

    /// <summary>
    /// The time of this state machine's last update.
    /// </summary>
    public DateTime LastUpdate { get; private set; } = DateTime.Now;

    /// <summary>
    /// The time in seconds since the state machine's last update.
    /// </summary>
    public double DeltaTime { get; private set; } = 0.0;

    /// <summary>
    /// A delegate for a method that handles state switching events.
    /// </summary>
    public delegate void StateSwitchedEventHandler(IState<Type> newState);

    /// <summary>
    /// An event that is called when the state machine switches to a new state.
    /// </summary>
    public event StateSwitchedEventHandler OnStateSwitched;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor.
    /// </summary>
    public StateMachine(Type data = default(Type), IState<Type> state = null)
    {
        Data = data;
        State = state;
        if (State != null)
        {
            State.StateMachine = this;
            State.OnStateEnter(null);
        }
    }

    /// <summary>
    /// State constructor.
    /// </summary>
    public StateMachine(IState<Type> state, Type data = default(Type))
    {
        Data = data;
        State = state;
        if (State != null)
        {
            State.StateMachine = this;
            State.OnStateEnter(null);
        }
    }


    // METHODS

    /// <summary>
    /// Returns whether the state machine's current state is not null.
    /// </summary>
    public bool IsStateValid() => State != null;

    /// <summary>
    /// Returns whether the state machine's current state is the given type.
    /// </summary>
    public bool StateIs<StateType>() where StateType : IState<Type> => State is StateType;

    /// <summary>
    /// Returns the state machine's current state as the given type.
    /// </summary>
    public StateType StateAs<StateType>() where StateType : class, IState<Type> => State as StateType;

    /// <summary>
    /// Switches the state machine's current state to a new state.
    /// </summary>
    public IState<Type> SwitchState(IState<Type> newState)
    {
        IState<Type> currentState = State;
        State?.OnStateExit(newState);
        State = newState;
        if (State != null)
        {
            State.StateMachine = this;
            State.OnStateEnter(currentState);
        }
        OnStateSwitched?.Invoke(State);
        return State;
    }

    /// <summary>
    /// Updates the state machine's current state and returns the state machine's current or new state.
    /// </summary>
    public IState<Type> Update()
    {
        DateTime now = DateTime.Now;
        DeltaTime = Math.Max((now - LastUpdate).TotalSeconds, 0.000001);
        LastUpdate = now;
        State?.OnStateUpdate(DeltaTime);
        return State;
    }

    /// <summary>
    /// Updates the state machine until its current state is null.
    /// </summary>
    public void Unwrap()
    {
        while (Update() != null) ;
    }
}
