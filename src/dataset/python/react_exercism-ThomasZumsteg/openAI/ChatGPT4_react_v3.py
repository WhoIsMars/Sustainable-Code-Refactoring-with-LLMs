from weakref import WeakSet

CELLS = WeakSet()

class InputCell:
    def __init__(self, initial_value):
        self._value = initial_value
        CELLS.add(self)

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, value):
        if self._value != value:
            self._value = value
            for cell in list(CELLS):
                cell._update()

    def _update(self):
        return self._value


class ComputeCell:
    def __init__(self, inputs, compute_function):
        self._inputs = inputs
        self._function = compute_function
        self._callbacks = set()
        self._value = self._compute_value()
        CELLS.add(self)

    @property
    def value(self):
        return self._value

    def _compute_value(self):
        return self._function([i.value for i in self._inputs])

    def _update(self):
        new_val = self._compute_value()
        if new_val != self._value:
            self._value = new_val
            for callback in self._callbacks:
                callback(new_val)
        return new_val

    def add_callback(self, callback):
        self._callbacks.add(callback)
        return callback

    def remove_callback(self, callback):
        self._callbacks.discard(callback)