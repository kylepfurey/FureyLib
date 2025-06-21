# .py
# Multicast Event Class
# by Kyle Furey

from typing import Any, List, Tuple, Callable, Iterator


# EVENT


class Event:
    """A collection of functions that can be bound, unbound, and invoked all at once."""

    # DATA

    _bindings: List[Tuple[Any, Callable[..., Any]]]
    """Each bound function and its key."""

    # CONSTRUCTOR

    def __init__(self) -> None:
        """Default constructor."""
        self._bindings = []

    # OPERATORS

    def __iadd__(self, callback: Callable[..., Any]) -> "Event":
        """Binds a new function to this event."""
        self.bind(callback)
        return self

    def __isub__(self, callback: Callable[..., Any]) -> "Event":
        """Unbinds the first instance of the given function from this event."""
        self.unbind(callback)
        return self

    def __call__(self, *args, **kwargs) -> Any:
        """Invokes each bound function with the given arguments and returns the most recent function's returned value."""
        return self.invoke(*args, **kwargs)

    def __iter__(self) -> Iterator[Tuple[Any, Callable[..., Any]]]:
        """Returns an iterator to the event."""
        return iter(self._bindings)

    # EVENT

    def count(self) -> int:
        """Returns the total number of bound functions."""
        return len(self._bindings)

    def bind(self, key: Any, callback: Callable[..., Any] = None) -> None:
        """Binds a new function and its key to this event."""
        if callback == None:
            if callable(key):
                self._bindings.append((key, key))
        else:
            self._bindings.append((key, callback))

    def unbind(self, key: Any) -> bool:
        """Unbinds the first bound function that matches the given key from this event."""
        for i in range(len(self._bindings)):
            if self._bindings[i][0] == key:
                del self._bindings[i]
                return True
        return False

    def is_bound(self, key: Any) -> bool:
        """Returns whether at least one bound function matches the given key."""
        for i in range(len(self._bindings)):
            if self._bindings[i][0] == key:
                return True
        return False

    def invoke(self, *args, **kwargs) -> Any:
        """Invokes each bound function with the given arguments and returns the most recent function's returned value."""
        result: Any = None
        for i in range(len(self._bindings)):
            result = self._bindings[i][1](*args, **kwargs)
        return result

    def clear(self) -> None:
        """Unbinds all functions from this event."""
        self._bindings.clear()
