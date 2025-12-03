class InputCell(object):
    def __init__(self, initial_value):
        self._value = initial_value
        self._dependents = set()

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, value):
        if self._value != value:
            self._value = value
            self._propagate_update()

    def _propagate_update(self):
        for cell in self._dependents:
            cell._update()

    def _update(self):
        return self._value

    def _add_dependent(self, cell):
        self._dependents.add(cell)


class ComputeCell(object):
    def __init__(self, inputs, compute_function):
        self._inputs = inputs
        self._compute_function = compute_function
        self._callbacks = {}
        self._value = self._compute_function([i.value for i in inputs])
        
        for input_cell in inputs:
            input_cell._add_dependent(self)

    @property
    def value(self):
        return self._value

    def _update(self):
        new_val = self._compute_function([i.value for i in self._inputs])
        if new_val != self._value:
            self._value = new_val
            for callback in self._callbacks.values():
                callback(new_val)
        return new_val

    def add_callback(self, callback):
        self._callbacks[callback] = callback
        return callback

    def remove_callback(self, callback):
        self._callbacks.pop(callback, None)