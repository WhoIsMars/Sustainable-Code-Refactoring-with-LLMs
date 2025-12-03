from collections import deque

class BufferFullException(Exception):
    pass


class BufferEmptyException(Exception):
    pass


class CircularBuffer:
    def __init__(self, capacity):
        self._capacity = capacity
        self._items = deque(maxlen=capacity)

    def read(self):
        if not self._items:
            raise BufferEmptyException(
                f"Empty buffer: CircularBuffer({self._capacity})"
            )
        return self._items.popleft()

    def write(self, data):
        if len(self._items) >= self._capacity:
            raise BufferFullException(
                f"Buffer is full: CircularBuffer({self._capacity})"
            )
        self._items.append(data)

    def overwrite(self, data):
        if len(self._items) >= self._capacity:
            self._items.popleft()
        self._items.append(data)

    def clear(self):
        self._items.clear()

    def _full(self):
        return len(self._items) >= self._capacity