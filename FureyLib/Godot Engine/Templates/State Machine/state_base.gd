
# Template State Machine Base State Script
# by Kyle Furey


class_name StateBase extends Object
"""The base class for each state. All states should inherit from this class."""

var state_machine = null
"""The inherited state machine from the owner"""

func on_state_enter():
	"""Called when this state is set as the state machine's current state"""

	# Note: Logic applies to all inherited states

	pass

func on_state_update():
	"""Called every frame while this state is the state machine's current state"""

	# Note: Logic applies to all inherited states

	pass

func on_state_exit():
	"""Called when this state machine's current state is no longer this state"""

	# Note: Logic applies to all inherited states

	pass

pass
