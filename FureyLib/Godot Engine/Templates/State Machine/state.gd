
# Template State Machine State Script
# by Kyle Furey


class_name State extends StateBase
"""A template for a new state machine state."""

func _init(state_machine: StateMachine):
	"""Constructor (sets state machine)"""

	self.state_machine = state_machine

	# Change the state type enum here!
	self.state_machine.current_state_type = StateMachine.StateType.STATE

	pass

func on_state_enter():
	"""Called when this state is set as the state machine's current state"""

	# Calls the base class's function
	super()

	pass

func on_state_update():
	"""Called every frame while this state is the state machine's current state"""

	# Calls the base class's function
	super()

	pass

func on_state_exit():
	"""Called when this state machine's current state is no longer this state"""

	# Calls the base class's function
	super()

	pass

pass
