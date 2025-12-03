from json import dumps

class Tree:
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
        return self.label == other.label and sorted(self.children) == sorted(other.children)

    def from_pov(self, from_node):
        steps = self.find(from_node)
        for step in steps[1:]:
            self.children = [c for c in self.children if c != step]
            step.label, self.label = self.label, step.label
            step.children, self.children = self.children, step.children
            self.children.append(step)
        return self

    def path_to(self, from_node, to_node):
        to_path, from_path = self.find(to_node), self.find(from_node)
        return [n.label for n in reversed(from_path[:-1])] + [n.label for n in to_path]

    def find(self, to_node):
        stack = [(self, [])]
        while stack:
            node, path = stack.pop()
            if node.label == to_node:
                return path + [node]
            stack.extend((c, path + [node]) for c in node.children)
        raise ValueError(f"No node {to_node}")