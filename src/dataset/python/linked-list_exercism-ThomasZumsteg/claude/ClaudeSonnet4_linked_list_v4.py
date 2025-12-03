class Node:
    __slots__ = ('value', 'next', 'previous')
    
    def __init__(self, value, next=None, previous=None):
        self.value = value
        self.next = next
        self.previous = previous


class LinkedList:
    __slots__ = ('head', '_len')
    
    def __init__(self):
        self.head = None
        self._len = 0

    def __len__(self):
        return self._len

    def __iter__(self):
        if self.head is None:
            return
        p = self.head
        while True:
            yield p.value
            p = p.next
            if p == self.head:
                return

    def push(self, value):
        self._len += 1
        node = Node(value)
        if self.head is None:
            self.head = node
            node.next = node.previous = node
        else:
            tail = self.head.previous
            node.next = self.head
            node.previous = tail
            tail.next = node
            self.head.previous = node
            self.head = node

    def pop(self):
        if self.head is None:
            raise IndexError("pop from empty list")
        
        self._len -= 1
        node = self.head
        
        if self.head.next == self.head:
            self.head = None
        else:
            tail = node.previous
            new_head = node.next
            tail.next = new_head
            new_head.previous = tail
            self.head = new_head
        
        return node.value

    def shift(self):
        if self.head is None:
            raise IndexError("shift from empty list")
        
        self._len -= 1
        tail = self.head.previous
        
        if self.head.next == self.head:
            value = self.head.value
            self.head = None
        else:
            value = tail.value
            new_tail = tail.previous
            new_tail.next = self.head
            self.head.previous = new_tail
        
        return value

    def unshift(self, value):
        self._len += 1
        node = Node(value)
        
        if self.head is None:
            self.head = node
            node.next = node.previous = node
        else:
            tail = self.head.previous
            node.next = self.head
            node.previous = tail
            tail.next = node
            self.head.previous = node