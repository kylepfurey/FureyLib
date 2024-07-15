
# Template State Machine Script
# by Kyle Furey

from enum import Enum

# Include this heading to use the class
from state_machine import StateMachine


class StateType(Enum):
    """State machine states enum"""

    NONE = 0
    """No state selected"""

    STATE = 1
    """Example state"""

    pass


class StateMachine:
    """Base for building a state machine."""

    current_state = None
    """The current state of this state machine"""

    current_state_type = StateType.NONE
    """The current state of this state machine"""

    def __init__(self, new_state):
        """Starting state constructor"""

        self.switch_state(new_state)

        pass

    def switch_state(self, new_state):
        """Properly switches the state machine's current state"""

        # Exit the current state
        if self.current_state is not None:

            self.current_state.on_state_exit()

        # Switch the current state to the new state
        self.current_state = new_state

        # Enter the new state
        if self.current_state is not None:

            self.current_state.on_state_enter()

        pass

    def tick(self):
        """Updates the current state (should be called each tick)"""

        # Call the current state's update function
        if self.current_state is not None:

            self.current_state.on_state_update()

        pass

    pass


class StateBase:
    """The base class for each state. All states should inherit from this class."""

    state_machine = None
    """The inherited state machine from the owner"""

    def on_state_enter(self):
        """Called when this state is set as the state machine's current state"""

        # Note: Logic applies to all inherited states

        pass

    def on_state_update(self):
        """Called every frame while this state is the state machine's current state"""

        # Note: Logic applies to all inherited states

        pass

    def on_state_exit(self):
        """Called when this state machine's current state is no longer this state"""

        # Note: Logic applies to all inherited states

        pass

    pass
