class Node:
    def __init__(self, value):
        self.value = value
        self.next = None
        self.prev = None


class LinkedList:
    def __init__(self):
        self.head = None
        self._len = 0

    def __len__(self):
        return self._len

    def __iter__(self):
        if self.head is None:
            return
        node = self.head
        yield node.value
        node = node.next
        while node is not self.head and node is not None:
            yield node.value
            node = node.next

    def push(self, value):
        new_node = Node(value)
        if self.head is None:
            self.head = new_node
            new_node.next = new_node
            new_node.prev = new_node
        else:
            tail = self.head.prev
            new_node.next = self.head
            new_node.prev = tail
            self.head.prev = new_node
            tail.next = new_node
            self.head = new_node
        self._len += 1

    def pop(self):
        if self.head is None:
            raise IndexError("pop from an empty LinkedList")

        value = self.head.value
        if self.head.next == self.head:
            self.head = None
        else:
            tail = self.head.prev
            self.head = self.head.next
            self.head.prev = tail
            tail.next = self.head
        self._len -= 1
        return value

    def shift(self):
        if self.head is None:
            raise IndexError("shift from an empty LinkedList")

        tail = self.head.prev
        value = tail.value

        if self.head.next == self.head:
            self.head = None
        else:
            self.head.prev = tail.prev
            tail.prev.next = self.head
        self._len -= 1
        return value

    def unshift(self, value):
        new_node = Node(value)
        if self.head is None:
            self.head = new_node
            new_node.next = new_node
            new_node.prev = new_node
        else:
            tail = self.head.prev
            new_node.next = self.head
            new_node.prev = tail
            self.head.prev = new_node
            tail.next = new_node
            self.head = new_node

        self._len += 1