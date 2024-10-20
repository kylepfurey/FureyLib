# Template State Machine State Script
# by Kyle Furey

from state_machine import StateBase, StateMachine


class State(StateBase):
    """A template for a new state machine state."""

    def __init__(self, state_machine: StateMachine):
        """Constructor (sets state machine)"""

        self.state_machine = state_machine

        pass

    def on_state_enter(self):
        """Called when this state is set as the state machine's current state"""

        # Calls the base class's function
        super().on_state_enter()

        pass

    def on_state_update(self):
        """Called every frame while this state is the state machine's current state"""

        # Calls the base class's function
        super().on_state_update()

        pass

    def on_state_exit(self):
        """Called when this state machine's current state is no longer this state"""

        # Calls the base class's function
        super().on_state_exit()

        pass

    pass
