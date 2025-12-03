from json import dumps

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
        if self.label != other.label:
            return False
        return self.__dict__() == other.__dict__()

    def from_pov(self, from_node):
        steps = self.find(from_node)
        original_label = self.label
        original_children = self.children
        for step in steps[1:]:
            self.children = [c for c in self.children if c.label != step.label]
            step_label = step.label
            step_children = step.children
            step.label = original_label
            step.children = original_children
            original_label = step_label
            original_children = step_children
            self.children.append(step)
        self.label = original_label
        self.children = original_children
        return self

    def path_to(self, from_node, to_node):
        from_path = self.find(from_node)
        to_path = self.find(to_node)

        from_path_labels = [node.label for node in reversed(from_path)]
        to_path_labels = [node.label for node in to_path[1:]]

        return from_path_labels + to_path_labels

    def find(self, to_node):
        queue = [(self, [self])]
        while queue:
            node, path = queue.pop(0)
            if node.label == to_node:
                return path
            for child in node.children:
                queue.append((child, path + [child]))
        raise ValueError("No node {}".format(to_node))