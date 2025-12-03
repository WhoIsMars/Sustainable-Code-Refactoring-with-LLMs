from json import dumps
from itertools import chain
from collections import deque

class Tree(object):
    def __init__(self, label, children=None):
        self.label = label
        self.children = children or []

    def __dict__(self):
        return {self.label: [c.__dict__() for c in sorted(self.children)]}

    def __str__(self, indent=None):
        return dumps(self.__dict__(), indent=indent)

    def __lt__(self, other):
        return self.label < other.label

    def __eq__(self, other):
        return self.__dict__() == other.__dict__()

    def from_pov(self, from_node):
        steps = self.find(from_node)
        children_set = {c.label for c in self.children}
        
        for step in steps[1:]:
            if step.label in children_set:
                self.children = [c for c in self.children if c.label != step.label]
                children_set.discard(step.label)
            
            step.label, self.label = self.label, step.label
            step.children, self.children = self.children, step.children
            self.children.append(step)
            children_set = {c.label for c in self.children}
        return self

    def path_to(self, from_node, to_node):
        to_path = self.find(to_node)
        from_path = self.find(from_node)
        
        result = []
        for node in reversed(from_path):
            result.append(node.label)
        for node in to_path[1:]:
            result.append(node.label)
        return result

    def find(self, to_node):
        queue = deque([(self, ())])
        while queue:
            node, path = queue.popleft()
            new_path = path + (node,)
            if node.label == to_node:
                return new_path
            queue.extend((c, new_path) for c in node.children)
        raise ValueError("No node {}".format(to_node))