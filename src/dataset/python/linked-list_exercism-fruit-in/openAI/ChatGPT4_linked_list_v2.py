class Node:
    __slots__ = 'val', 'next', 'prev'

    def __init__(self, value, succeeding=None, previous=None):
        self.val = value
        self.next = succeeding
        self.prev = previous


class LinkedList:
    __slots__ = 'front', 'back', 'length'

    def __init__(self):
        self.front = None
        self.back = None
        self.length = 0

    def push(self, value):
        node = Node(value, None, self.back)
        if self.back:
            self.back.next = node
        else:
            self.front = node
        self.back = node
        self.length += 1

    def pop(self):
        if not self.back:
            return None
        value = self.back.val
        self.back = self.back.prev
        if self.back:
            self.back.next = None
        else:
            self.front = None
        self.length -= 1
        return value

    def shift(self):
        if not self.front:
            return None
        value = self.front.val
        self.front = self.front.next
        if self.front:
            self.front.prev = None
        else:
            self.back = None
        self.length -= 1
        return value

    def unshift(self, value):
        node = Node(value, self.front)
        if self.front:
            self.front.prev = node
        else:
            self.back = node
        self.front = node
        self.length += 1

    def __len__(self):
        return self.length

    def __iter__(self):
        curr = self.front
        while curr:
            yield curr.val
            curr = curr.next