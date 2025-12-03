class Zipper(object):
    __slots__ = ('tree', 'crumbs')
    
    @staticmethod
    def from_tree(tree):
        return Zipper(tree, ())

    def __init__(self, tree, crumbs):
        self.tree = tree
        self.crumbs = crumbs

    def value(self):
        return self.tree['value']

    def set_value(self, value):
        root = self.tree.copy()
        root['value'] = value
        return Zipper(root, self.crumbs)

    def left(self):
        left_tree = self.tree['left']
        if left_tree:
            crumb = ('left', self.tree['value'], self.tree['right'])
            return Zipper(left_tree, self.crumbs + (crumb,))

    def set_left(self, left):
        root = self.tree.copy()
        root['left'] = left
        return Zipper(root, self.crumbs)

    def right(self):
        right_tree = self.tree['right']
        if right_tree:
            crumb = ('right', self.tree['value'], self.tree['left'])
            return Zipper(right_tree, self.crumbs + (crumb,))

    def set_right(self, right):
        root = self.tree.copy()
        root['right'] = right
        return Zipper(root, self.crumbs)

    def up(self):
        if not self.crumbs:
            return None
        direction, value, tree = self.crumbs[-1]
        root = {
            'value': value,
            direction: self.tree,
            'left' if direction == 'right' else 'right': tree
        }
        return Zipper(root, self.crumbs[:-1])

    def to_tree(self):
        current = self
        while current.crumbs:
            current = current.up()
        return current.tree