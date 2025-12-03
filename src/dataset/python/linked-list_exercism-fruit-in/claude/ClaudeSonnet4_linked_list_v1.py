class Node:
    __slots__ = ('val', 'next', 'prev')
    
    def __init__(self, value, succeeding=None, previous=None):
        self.val = value
        self.next = succeeding
        self.prev = previous


class LinkedList:
    __slots__ = ('front', 'back', 'length')
    
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
        back_node = self.back
        value = back_node.val

        if back_node.prev:
            back_node.prev.next = None
            self.back = back_node.prev
        else:
            self.front = None
            self.back = None
        self.length -= 1

        return value

    def shift(self):
        front_node = self.front
        value = front_node.val

        if front_node.next:
            front_node.next.prev = None
            self.front = front_node.next
        else:
            self.front = None
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