class InputCell:
    def __init__(self, initial_value):
        self._value = initial_value
        self._dependents = []

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, value):
        if self._value != value:
            self._value = value
            for dependent in self._dependents:
                dependent._update()

    def _add_dependent(self, cell):
        self._dependents.append(cell)


class ComputeCell:
    def __init__(self, inputs, compute_function):
        self._inputs = inputs
        self._function = compute_function
        self._callbacks = {}
        self._value = self._compute_value()
        for input_cell in inputs:
            input_cell._add_dependent(self)

    @property
    def value(self):
        return self._value

    def _compute_value(self):
        return self._function([i.value for i in self._inputs])

    def _update(self):
        new_val = self._compute_value()
        if new_val != self._value:
            self._value = new_val
            for callback in self._callbacks.values():
                callback(new_val)

    def add_callback(self, callback):
        self._callbacks[callback] = callback

    def remove_callback(self, callback):
        self._callbacks.pop(callback, None)