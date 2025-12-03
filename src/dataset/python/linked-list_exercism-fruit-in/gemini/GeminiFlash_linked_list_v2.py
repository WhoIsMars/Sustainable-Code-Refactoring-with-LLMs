class Node:
    def __init__(self, value):
        self.val = value
        self.next = None
        self.prev = None


class LinkedList:
    def __init__(self):
        self.front = None
        self.back = None
        self.length = 0

    def push(self, value):
        new_node = Node(value)
        if self.back is None:
            self.front = new_node
            self.back = new_node
        else:
            new_node.prev = self.back
            self.back.next = new_node
            self.back = new_node
        self.length += 1

    def pop(self):
        if self.back is None:
            raise IndexError("pop from an empty LinkedList")

        value = self.back.val
        self.back = self.back.prev

        if self.back is None:
            self.front = None
        else:
            self.back.next = None

        self.length -= 1
        return value

    def shift(self):
        if self.front is None:
            raise IndexError("shift from an empty LinkedList")

        value = self.front.val
        self.front = self.front.next

        if self.front is None:
            self.back = None
        else:
            self.front.prev = None

        self.length -= 1
        return value

    def unshift(self, value):
        new_node = Node(value)
        if self.front is None:
            self.front = new_node
            self.back = new_node
        else:
            new_node.next = self.front
            self.front.prev = new_node
            self.front = new_node
        self.length += 1

    def __len__(self):
        return self.length

    def __iter__(self):
        curr = self.front
        while curr:
            yield curr.val
            curr = curr.next