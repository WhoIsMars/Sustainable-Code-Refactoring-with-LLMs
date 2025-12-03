class Node:
    __slots__ = 'val', 'next', 'prev'

    def __init__(self, value, succeeding=None, previous=None):
        self.val = value
        self.next = succeeding
        self.prev = previous


class LinkedList:
    def __init__(self):
        self.front = None
        self.back = None
        self._length = 0  # Use a protected attribute

    def push(self, value):
        new_node = Node(value, None, self.back)

        if self.back:
            self.back.next = new_node
        else:
            self.front = new_node

        self.back = new_node
        self._length += 1

    def pop(self):
        if not self.back:
            raise IndexError("pop from an empty LinkedList")

        value = self.back.val
        self.back = self.back.prev

        if self.back:
            self.back.next = None
        else:
            self.front = None

        self._length -= 1
        return value

    def shift(self):
        if not self.front:
            raise IndexError("shift from an empty LinkedList")

        value = self.front.val
        self.front = self.front.next

        if self.front:
            self.front.prev = None
        else:
            self.back = None

        self._length -= 1
        return value

    def unshift(self, value):
        new_node = Node(value, self.front)

        if self.front:
            self.front.prev = new_node
        else:
            self.back = new_node

        self.front = new_node
        self._length += 1

    def __len__(self):
        return self._length

    def __iter__(self):
        curr = self.front
        while curr:
            yield curr.val
            curr = curr.next