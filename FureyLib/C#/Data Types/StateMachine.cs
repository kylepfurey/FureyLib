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
public interface IState<T>
{
    // INTERFACE

    /// <summary>
    /// The state machine that owns this state instance.
    /// </summary>
    public StateMachine<T> StateMachine { get; }

    /// <summary>
    /// Called when a state machine instantiates this state.
    /// </summary>
    public abstract void OnStateEnter(IState<T>? previousState);

    /// <summary>
    /// Called when a state machine updates this state.
    /// </summary>
    public abstract void OnStateUpdate(double deltaTime);

    /// <summary>
    /// Called when a state machine switches off this state.
    /// </summary>
    public abstract void OnStateExit(IState<T>? nextState);
}


// STATE MACHINE

/// <summary>
/// A class that manages its data within different states of code.
/// </summary>
public sealed class StateMachine<T>
{
    // PROPERTIES

    /// <summary>
    /// The data this state machine is managing.
    /// </summary>
    public T Data { get; set; } = default(T);

    /// <summary>
    /// The current state of this state machine.
    /// </summary>
    public IState<T>? State { get; private set; } = null!;

    /// <summary>
    /// The type of the state machine's current state.
    /// </summary>
    public Type? StateType => State != null ? State.GetType() : null;

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
    public StateMachine(T Data = default(T), IState<T>? State = null!)
    {
        this.Data = Data;
        this.State = State;
        this.State?.OnStateEnter(null!);
        LastUpdate = DateTime.Now;
    }

    /// <summary>
    /// State constructor.
    /// </summary>
    public StateMachine(IState<T>? State, T Data = default(T))
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
    public bool IsState<StateType>() where StateType : IState<T> => State is StateType;

    /// <summary>
    /// Switches the state machine's current state to a new state.
    /// </summary>
    public IState<T>? SwitchState(IState<T>? newState)
    {
        IState<T> currentState = State;
        State?.OnStateExit(newState);
        State = newState;
        State?.OnStateEnter(currentState);
        return State;
    }

    /// <summary>
    /// Updates the state machine's current state and returns the state machine's current or new state.
    /// </summary>
    public IState<T>? Update()
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
