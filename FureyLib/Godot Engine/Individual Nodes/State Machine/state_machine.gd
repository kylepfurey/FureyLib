# .gd
# State Machine Node Script
# by Kyle Furey


# STATE MACHINE

extends Node

## A node used to manage a scene's state through switching a single node.
class_name StateMachine


# ENUMS

## How destroying is handled with state nodes.
enum DestroyBehaviour {
	NEVER,
	MY_NODES,
	OTHER_NODES,
	ALWAYS,
}


# VARIABLES

## The state machine's current state node.
@export var _state: Node = null

## The script of the state machine's starting state node.
@export var _starting_state_script: GDScript = null

## Events to call when the current state node is switched.
signal on_switch_state(new_state: Node)

## When nodes are destroyed by this state machine.
@export var destroy_behaviour: DestroyBehaviour = DestroyBehaviour.ALWAYS


# EVENTS

## Initializes the starting state node.
func _ready() -> void:
	if _starting_state_script != null:
		switch_state(_starting_state_script)

## Cleans up the state machine's current state node.
func _exit_tree() -> void:
	if _state != null:
		destroy_state()


# METHODS

## Returns the state machine's current state node.
func get_state() -> Node:
	return _state

## Returns the script of the state machine's current state node.
func get_state_script() -> GDScript:
	return _state.get_script() if _state != null else null

## Returns the script of the state machine's starting state node.
func get_starting_state_script() -> GDScript:
	return _starting_state_script

## Returns whether the state machine's current state node is valid.
func is_state_valid() -> bool:
	return _state != null

## Returns whether the state machine's current state node is an instance of the given script.
func state_is(script: GDScript) -> bool:
	if _state == null:
		return false
	current: GDScript = _state.get_script()
	while current != null:
		if current == script:
			return true
		current = current.get_base_script()
	return false

## Switches the state machine's state node to the given state node.
func switch_state_to(new_state: Node) -> Node:
	if new_state == _state:
		return _state
	if _state != null:
		destroy_state()
	_state = new_state
	if _state != null and "_state_machine" in _state:
		_state["_state_machine"] = self
	on_switch_state.emit(_state)
	return _state

## Switches the state machine's state node to a new instance of the given script.
func switch_state(script: GDScript) -> Node:
	if script != null:
		var new_node = script.new()
		if _state != null:
			_state.add_child(new_node)
		else:
			add_child(new_node)
		return switch_state_to(new_node)
	return switch_state_to(null)

## Destroys this state machine's current state node based on its destroy behaviour.
## Returns whether the node was successfully destroyed.
func destroy_state() -> bool:
	if _state == null:
		return false
	match destroy_behaviour:
		DestroyBehaviour.NEVER:
			return false
		DestroyBehaviour.MY_NODES:
			if _state.owner == owner:
				_state.queue_free()
				_state = null
				return true
			else: return false
		DestroyBehaviour.OTHER_NODES:
			if _state.owner != owner:
				_state.queue_free()
				_state = null
				return true
			else: return false
		DestroyBehaviour.ALWAYS:
			_state.queue_free()
			_state = null
			return true
		_:
			return false
