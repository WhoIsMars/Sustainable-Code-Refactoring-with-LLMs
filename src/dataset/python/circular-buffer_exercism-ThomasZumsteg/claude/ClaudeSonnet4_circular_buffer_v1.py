class BufferFullException(Exception):
    pass


class BufferEmptyException(Exception):
    pass


class CircularBuffer(object):
    def __init__(self, capacity):
        self._capacity = capacity
        self._items = [None] * capacity
        self._start = 0
        self._size = 0

    def read(self):
        if self._size == 0:
            raise BufferEmptyException(
                f"Empty buffer: CircularBuffer({self._capacity})")
        
        item = self._items[self._start]
        self._start = (self._start + 1) % self._capacity
        self._size -= 1
        return item

    def write(self, data):
        if self._size >= self._capacity:
            raise BufferFullException(
                f"Buffer is full: CircularBuffer({self._capacity})")
        
        end = (self._start + self._size) % self._capacity
        self._items[end] = data
        self._size += 1

    def overwrite(self, data):
        if self._size >= self._capacity:
            self.read()
        self.write(data)

    def clear(self):
        self._start = 0
        self._size = 0

    def _full(self):
        return self._size >= self._capacity