// .cs
// State Machine Class
// by Kyle Furey

#nullable enable
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
    public StateMachine<Type> StateMachine { get; init; }

    /// <summary>
    /// Called when a state machine instantiates this state.
    /// </summary>
    public abstract void OnStateEnter(IState<Type>? previousState);

    /// <summary>
    /// Called when a state machine updates this state.
    /// </summary>
    public abstract void OnStateUpdate(double deltaTime);

    /// <summary>
    /// Called when a state machine switches off this state.
    /// </summary>
    public abstract void OnStateExit(IState<Type>? nextState);
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
    public IState<Type>? State { get; private set; } = null!;

    /// <summary>
    /// The type of the state machine's current state.
    /// </summary>
    public System.Type? StateType => State != null ? State.GetType() : null;

    /// <summary>
    /// The time of this state machine's last update.
    /// </summary>
    public DateTime LastUpdate { get; private set; } = DateTime.Now;

    /// <summary>
    /// The time in seconds since the state machine's last update.
    /// </summary>
    public double DeltaTime => (DateTime.Now - LastUpdate).TotalSeconds;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor.
    /// </summary>
    public StateMachine(Type Data = default(Type), IState<Type>? State = null!)
    {
        this.Data = Data;
        this.State = State;
        this.State?.OnStateEnter(null!);
        LastUpdate = DateTime.Now;
    }

    /// <summary>
    /// State constructor.
    /// </summary>
    public StateMachine(IState<Type>? State, Type Data = default(T))
    {
        this.Data = Data;
        this.State = State;
        this.State?.OnStateEnter(null!);
        LastUpdate = DateTime.Now;
    }


    // METHODS

    /// <summary>
    /// Returns whether the state machine's current state is not null.
    /// </summary>
    public bool IsStateValid() => State != null;

    /// <summary>
    /// Returns whether the state machine's current state is the given type.
    /// </summary>
    public bool IsState<StateType>() where StateType : IState<Type> => State is StateType;

    /// <summary>
    /// Switches the state machine's current state to a new state.
    /// </summary>
    public IState<Type>? SwitchState(IState<Type>? newState)
    {
        IState<Type>? currentState = State;
        State?.OnStateExit(newState);
        State = newState;
        State?.OnStateEnter(currentState);
        return State;
    }

    /// <summary>
    /// Updates the state machine's current state and returns the state machine's current or new state.
    /// </summary>
    public IState<Type>? Update()
    {
        State?.OnStateUpdate(DeltaTime);
        LastUpdate = DateTime.Now;
        return State;
    }

    /// <summary>
    /// Updates the state machine until its current state is null.
    /// </summary>
    public void Unwrap()
    {
        while (Update() != null);
    }
}
