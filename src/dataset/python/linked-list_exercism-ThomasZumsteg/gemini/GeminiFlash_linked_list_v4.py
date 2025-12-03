class Node(object):
    __slots__ = ('value', 'next', 'previous')

    def __init__(self, value, next=None, previous=None):
        self.value = value
        self.next = next
        self.previous = previous


class LinkedList(object):
    def __init__(self):
        self.head = None
        self._len = 0

    def __len__(self):
        return self._len

    def __iter__(self):
        if self.head is None:
            return

        current = self.head
        yield current.value
        current = current.previous

        while current is not self.head:
            yield current.value
            current = current.previous

    def push(self, value):
        self._len += 1
        new_node = Node(value)

        if self.head is None:
            self.head = new_node
            new_node.next = new_node
            new_node.previous = new_node
        else:
            tail = self.head.previous
            new_node.next = self.head
            new_node.previous = tail
            self.head.previous = new_node
            tail.next = new_node
            self.head = new_node

    def pop(self):
        if self.head is None:
            raise IndexError("pop from an empty LinkedList")

        self._len -= 1
        node = self.head
        value = node.value

        if self.head.next == self.head:
            self.head = None
        else:
            tail = self.head.previous
            self.head = node.next
            self.head.previous = tail
            tail.next = self.head

        return value

    def shift(self):
        if self.head is None:
            raise IndexError("shift from an empty LinkedList")

        self.head = self.head.previous
        return self.pop()

    def unshift(self, value):
        self.push(value)
        self.head = self.head.next