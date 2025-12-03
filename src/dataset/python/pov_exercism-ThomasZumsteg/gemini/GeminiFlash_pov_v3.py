from json import dumps
from collections import deque

class Tree(object):
    def __init__(self, label, children=None):
        self.label = label
        self.children = children or []

    def __dict__(self):
        return {self.label: [c.__dict__() for c in sorted(self.children, key=lambda x: x.label)]}

    def __str__(self, indent=None):
        return dumps(self.__dict__(), indent=indent)

    def __lt__(self, other):
        return self.label < other.label

    def __eq__(self, other):
        return self.__dict__() == other.__dict__()

    def from_pov(self, from_node):
        steps = self.find(from_node)
        current_node = self
        for step in steps[1:]:
            current_node.children = [c for c in current_node.children if c.label != step.label]
            step.label, current_node.label = current_node.label, step.label
            step.children, current_node.children = current_node.children, current_node.children
            current_node.children.append(step)
            current_node = step
        return self

    def path_to(self, from_node, to_node):
        to_path, from_path = self.find(to_node), self.find(from_node)
        from_path_labels = [node.label for node in reversed(from_path)]
        to_path_labels = [node.label for node in to_path[1:]]
        return from_path_labels + to_path_labels

    def find(self, to_node):
        queue = deque([(self, (self,))])
        while queue:
            node, path = queue.popleft()
            if node.label == to_node:
                return path
            queue.extend((child, path + (child,)) for child in node.children)
        raise ValueError("No node {}".format(to_node))