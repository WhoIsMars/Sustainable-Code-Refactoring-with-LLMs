class Node(object):
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
        current = current.next

        while current != self.head:
            yield current.value
            current = current.next

    def push(self, value):
        new_node = Node(value)
        if self.head is None:
            new_node.next = new_node.previous = new_node
            self.head = new_node
        else:
            tail = self.head.previous
            new_node.next = self.head
            new_node.previous = tail
            self.head.previous = new_node
            tail.next = new_node
            self.head = new_node
        self._len += 1

    def pop(self):
        if self.head is None:
            raise IndexError("pop from an empty LinkedList")

        node = self.head
        value = node.value

        if self.head.next == self.head:
            self.head = None
        else:
            tail = self.head.previous
            self.head = node.next
            tail.next = self.head
            self.head.previous = tail

        self._len -= 1
        return value

    def shift(self):
        if self.head is None:
            raise IndexError("shift from an empty LinkedList")

        value = self.head.previous.value
        if self.head.next == self.head:
            self.head = None
        else:
            new_tail = self.head.previous.previous
            new_tail.next = self.head
            self.head.previous = new_tail
        self._len -= 1
        return value

    def unshift(self, value):
        new_node = Node(value)
        if self.head is None:
            new_node.next = new_node.previous = new_node
            self.head = new_node
        else:
            tail = self.head.previous
            new_node.next = self.head
            new_node.previous = tail
            self.head.previous = new_node
            tail.next = new_node
            self.head = new_node
        self._len += 1