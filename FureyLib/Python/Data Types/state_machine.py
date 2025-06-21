# .py
# State Machine Interface and Class
# by Kyle Furey

from abc import ABC, abstractmethod
from typing import Any, Type
from time import time


# STATE


class IState(ABC):
    """An interface defining a class that can be used as a state within a state machine."""

    # INTERFACE

    _state_machine: "StateMachine" = None
    """The state machine that owns this state instance."""

    @abstractmethod
    def on_state_enter(self, previous_state: "IState") -> None:
        """Called when a state machine instantiates this state."""
        pass

    @abstractmethod
    def on_state_update(self, delta_time: float) -> None:
        """Called when a state machine updates this state."""
        pass

    @abstractmethod
    def on_state_exit(self, next_state: "IState") -> None:
        """Called when a state machine switches off this state."""
        pass


# STATE MACHINE


class StateMachine:
    """A class that manages its data within different states of code."""

    # VARIABLES

    _data: Any = None
    """The data this state machine is managing."""

    _state: IState = None
    """The current state of this state machine."""

    _last_update: float = time()
    """The time of this state machine's last update."""

    _delta_time: float = 0.0
    """The time in seconds since the state machine's last update."""

    # CONSTRUCTORS

    def __init__(self, data: Any = None, state: IState = None) -> None:
        """Default constructor."""
        self._data = data
        self._state = state
        if self._state is not None:
            self._state._state_machine = self
            self._state.on_state_enter(None)

    # GETTERS

    def get_data(self) -> Any:
        """Returns the data this state machine is managing."""
        return self._data

    def get_state(self) -> IState:
        """Returns the current state of this state machine."""
        return self._state

    def get_state_type(self) -> Type[IState]:
        """Returns the type of the state machine's current state."""
        return type(self._state) if self._state is not None else None

    def is_state_valid(self) -> bool:
        """Returns whether the state machine's current state is not None."""
        return self._state is not None

    def state_is(self, state_type: Type[IState]) -> bool:
        """Returns whether the state machine's current state is the given type."""
        return isinstance(self._state, state_type)

    def get_last_update(self) -> float:
        """Returns the time of this state machine's last update."""
        return self._last_update

    def get_delta_time(self) -> float:
        """Returns the time in seconds since the state machine's last update."""
        return self._delta_time

    # SETTERS

    def set_data(self, data: Any) -> None:
        """Sets the data this state machine is managing."""
        self._data = data

    def switch_state(self, new_state: IState):
        """Switches the state machine's current state to a new state."""
        current_state: IState = self._state
        if self._state is not None:
            self._state.on_state_exit(new_state)
        self._state = new_state
        if self._state is not None:
            self._state._state_machine = self
            self._state.on_state_enter(current_state)
        del current_state
        return self._state

    def update(self) -> IState:
        """Updates the state machine's current state and returns the state machine's current or new state."""
        now: float = time()
        self._delta_time = max(now - self._last_update, 0.000001)
        self._last_update = now
        if self._state is not None:
            self._state.on_state_update(self._delta_time)
        return self._state

    def unwrap(self) -> None:
        """Updates the state machine until its current state is null."""
        while self.update() is not None:
            pass
