class BufferFullException(Exception):
    pass


class BufferEmptyException(Exception):
    pass


class CircularBuffer(object):
    def __init__(self, capacity):
        self._capacity = capacity
        self._items = [None] * capacity  # Pre-allocate memory
        self._head = 0
        self._tail = 0
        self._size = 0

    def read(self):
        if self._size == 0:
            raise BufferEmptyException(
                "Empty buffer: CircularBuffer({})".format(self._capacity)
            )
        item = self._items[self._head]
        self._items[self._head] = None  # Optional: Help with garbage collection
        self._head = (self._head + 1) % self._capacity
        self._size -= 1
        return item

    def write(self, data):
        if self._size == self._capacity:
            raise BufferFullException(
                "Buffer is full: CircularBuffer({})".format(self._capacity)
            )
        self._items[self._tail] = data
        self._tail = (self._tail + 1) % self._capacity
        self._size += 1

    def overwrite(self, data):
        if self._size == self._capacity:
            self._items[self._head] = data
            self._head = (self._head + 1) % self._capacity
        else:
            self.write(data)
            return  # Early return to avoid unnecessary increment
        if self._size < self._capacity:
            self._size += 1

    def clear(self):
        self._items = [None] * self._capacity  # Reset to initial state
        self._head = 0
        self._tail = 0
        self._size = 0

    def _full(self):
        return self._size == self._capacity