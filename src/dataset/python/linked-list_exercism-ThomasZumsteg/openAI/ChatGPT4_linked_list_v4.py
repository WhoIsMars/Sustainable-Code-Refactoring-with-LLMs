class Node:
    __slots__ = 'value', 'next', 'previous'

    def __init__(self, value, next=None, previous=None):
        self.value = value
        self.next = next
        self.previous = previous


class LinkedList:
    __slots__ = 'head', '_len'

    def __init__(self):
        self.head = None
        self._len = 0

    def __len__(self):
        return self._len

    def __iter__(self):
        if not self.head:
            return
        p = self.head
        while True:
            yield p.value
            p = p.previous
            if p == self.head:
                break

    def push(self, value):
        node = Node(value)
        if not self.head:
            node.next = node.previous = node
            self.head = node
        else:
            node.next, node.previous = self.head, self.head.previous
            self.head.previous.next = self.head.previous = node
            self.head = node
        self._len += 1

    def pop(self):
        if not self.head:
            return None
        node = self.head
        if self._len == 1:
            self.head = None
        else:
            node.previous.next = node.next
            node.next.previous = node.previous
            self.head = node.next
        self._len -= 1
        return node.value

    def shift(self):
        if not self.head:
            return None
        self.head = self.head.previous
        return self.pop()

    def unshift(self, value):
        self.push(value)
        self.head = self.head.next