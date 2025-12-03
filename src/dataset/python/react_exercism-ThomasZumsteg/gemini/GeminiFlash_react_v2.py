class InputCell:
    def __init__(self, initial_value):
        self._value = initial_value
        self._observers = []

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, value):
        if self._value != value:
            self._value = value
            for observer in self._observers:
                observer._update()

    def add_observer(self, observer):
        self._observers.append(observer)

    def remove_observer(self, observer):
        try:
            self._observers.remove(observer)
        except ValueError:
            pass

    def _update(self):
        return self._value


class ComputeCell:
    def __init__(self, inputs, compute_function):
        self._inputs = inputs
        self._compute_function = compute_function
        self._callbacks = {}
        self._value = self._compute_value()
        for i in inputs:
            i.add_observer(self)

    def _compute_value(self):
        return self._compute_function([i.value for i in self._inputs])

    @property
    def value(self):
        return self._value

    def _update(self):
        new_val = self._compute_value()
        if new_val != self._value:
            self._value = new_val
            for c in self._callbacks.values():
                c(new_val)
        return new_val

    def add_callback(self, callback):
        self._callbacks[callback] = callback
        return callback

    def remove_callback(self, callback):
        self._callbacks.pop(callback, None)