
# Template State Machine Script
# by Kyle Furey


class_name StateMachine extends Node
"""Base for building a state machine."""

enum  StateType { NONE = 0, STATE = 1 }
"""State machine states enum"""
	
var current_state = null
"""The current state of this state machine"""

var current_state_type = StateType.NONE
"""The current state of this state machine"""

func _init(new_state):
	"""Starting state constructor"""

	self.switch_state(new_state)

	pass

func switch_state(new_state):
	"""Properly switches the state machine's current state"""

	# Exit the current state
	if current_state != null:

		current_state.on_state_exit()

	# Switch the current state to the new state
	current_state = new_state

	# Enter the new state
	if current_state != null:

		current_state.on_state_enter()

	pass
	
func _ready():
	"""Instantiates the starting state (should be changed from template)"""
	
	# Sets the current state as the starting state (should be changed from template state)
	switch_state(State.new(self))
	
	pass

func _process(delta):
	"""Updates the current state (should be called each tick)"""

	# Call the current state's update function
	if current_state != null:

		current_state.on_state_update()

	pass

pass
