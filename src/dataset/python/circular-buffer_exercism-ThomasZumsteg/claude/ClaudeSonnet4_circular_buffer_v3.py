class BufferFullException(Exception):
    pass


class BufferEmptyException(Exception):
    pass


class CircularBuffer(object):
    def __init__(self, capacity):
        self._capacity = capacity
        self._items = [None] * capacity
        self._head = 0
        self._tail = 0
        self._size = 0

    def read(self):
        if self._size == 0:
            raise BufferEmptyException(
                f"Empty buffer: CircularBuffer({self._capacity})")
        
        item = self._items[self._head]
        self._items[self._head] = None
        self._head = (self._head + 1) % self._capacity
        self._size -= 1
        return item

    def write(self, data):
        if self._size >= self._capacity:
            raise BufferFullException(
                f"Buffer is full: CircularBuffer({self._capacity})")
        
        self._items[self._tail] = data
        self._tail = (self._tail + 1) % self._capacity
        self._size += 1

    def overwrite(self, data):
        if self._size >= self._capacity:
            self.read()
        self.write(data)

    def clear(self):
        for i in range(self._capacity):
            self._items[i] = None
        self._head = 0
        self._tail = 0
        self._size = 0

    def _full(self):
        return self._size >= self._capacity