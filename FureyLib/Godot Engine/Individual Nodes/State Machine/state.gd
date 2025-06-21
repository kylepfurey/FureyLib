# .gd
# State Machine Interface Script
# by Kyle Furey


# STATE

extends Node

## An optional interface used to help define a state machine node's events.
class_name State


# VARIABLES

## The StateMachine node that owns this state.
var _state_machine: StateMachine = null


# EVENTS

## _ready() is called once before _process() by Godot.
func _ready() -> void:
	pass

## _process() is called each frame by Godot.
func _process(_delta: float) -> void:
	pass

## _exit_tree() is called by Godot right before this node is destroyed.
func _exit_tree() -> void:
	pass


# GETTERS

## Returns the StateMachine node that owns this state.
func get_state_machine() -> StateMachine:
	return _state_machine
