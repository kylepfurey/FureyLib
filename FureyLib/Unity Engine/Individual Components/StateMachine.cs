// .cs
// State Machine Component Script
// by Kyle Furey

#nullable enable
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;


// STATE

/// <summary>
/// An optional interface used to help define a state machine component's events.
/// </summary>
public interface IState
{
    // INTERFACE

    /// <summary>
    /// The StateMachine component that owns this state.
    /// </summary>
    StateMachine stateMachine { get; set; }

    /// <summary>
    /// Start() is called once before Update() by Unity.
    /// </summary>
    void Start();

    /// <summary>
    /// Update() is called each frame by Unity.<br/>
    /// The time in seconds since the last update can be accessed by UnityEngine.Time.deltaTime.
    /// </summary>
    void Update();

    /// <summary>
    /// OnDestroy() is called by Unity right before this component is destroyed.
    /// </summary>
    void OnDestroy();
}


// STATE MACHINE

/// <summary>
/// A component used to manage a game object's state through a single switching component.
/// </summary>
public sealed class StateMachine : MonoBehaviour
{
    // ENUM

    /// <summary>
    /// How destroying is handled with state components.
    /// </summary>
    public enum DestroyBehaviour
    {
        Never,
        MyComponents,
        OtherComponents,
        Always
    }


    // VARIABLES

    /// <summary>
    /// The state machine's current state component.
    /// </summary>
    [SerializeField]
    private MonoBehaviour? _state = null;

    /// <summary>
    /// Events to call when the current state component is switched.
    /// </summary>
    public UnityEvent<MonoBehaviour?> onSwitchState = new UnityEvent<MonoBehaviour?>();

    /// <summary>
    /// When components are destroyed by this state machine.
    /// </summary>
    public DestroyBehaviour destroyBehaviour = DestroyBehaviour.Always;


    // PROPERTIES

    /// <summary>
    /// The state machine's current state component.
    /// </summary>
    public MonoBehaviour? state => _state;

    /// <summary>
    /// The type of the state machine's current state component.
    /// </summary>
    public Type? stateType => _state != null ? _state.GetType() : null;

    /// <summary>
    /// The type of the state machine's starting state component.
    /// </summary>
    public Type? startingStateType { get; private set; } = null;


    // EVENTS

    /// <summary>
    /// Initializes the starting state component.
    /// </summary>
    private void Start()
    {
        if (_state != null)
        {
            startingStateType = _state.GetType();
            if (_state is IState state)
                state.stateMachine = this;
            onSwitchState.Invoke(_state);
        }
    }

    /// <summary>
    /// Cleans up the state machine's current state component.
    /// </summary>
    private void OnDestroy()
    {
        if (_state != null)
            DestroyState();
    }


    // METHODS

    /// <summary>
    /// Returns whether the state machine's current state component is valid.
    /// </summary>
    public bool IsStateValid() => _state != null;

    /// <summary>
    /// Returns whether the state machine's current state component is the given component type.
    /// </summary>
    public bool StateIs<StateType>() where StateType : MonoBehaviour => _state is StateType;

    /// <summary>
    /// Returns the state machine's current state component as the given component type.
    /// </summary>
    public StateType? StateAs<StateType>() where StateType : MonoBehaviour => _state as StateType;

    /// <summary>
    /// Switches the state machine's state component to the given state component.
    /// </summary>
    public MonoBehaviour? SwitchState(MonoBehaviour? newState)
    {
        if (newState == _state)
            return _state;
        if (_state != null)
            DestroyState();
        _state = newState;
        if (_state != null && _state is IState state)
            state.stateMachine = this;
        onSwitchState.Invoke(_state);
        return _state;
    }

    /// <summary>
    /// Switches the state machine's state component to a new state component of the given type.
    /// </summary>
    public MonoBehaviour? SwitchState<StateType>() where StateType : MonoBehaviour
    {
        return SwitchState(_state != null ? _state.gameObject.AddComponent<StateType>() : gameObject.AddComponent<StateType>());
    }

    /// <summary>
    /// Destroys this state machine's current state component based on its destroy behaviour.<br/>
    /// Returns whether the component was successfully destroyed.
    /// </summary>
    public bool DestroyState()
    {
        if (_state == null)
            return false;

        switch (destroyBehaviour)
        {
            default:
                return false;
            case DestroyBehaviour.Never:
                return false;
            case DestroyBehaviour.MyComponents:
                if (_state.gameObject == gameObject)
                {
                    Destroy(_state);
                    _state = null;
                    return true;
                }
                else return false;
            case DestroyBehaviour.OtherComponents:
                if (_state.gameObject != gameObject)
                {
                    Destroy(_state);
                    _state = null;
                    return true;
                }
                else return false;
            case DestroyBehaviour.Always:
                Destroy(_state);
                _state = null;
                return true;
        }
    }
}
