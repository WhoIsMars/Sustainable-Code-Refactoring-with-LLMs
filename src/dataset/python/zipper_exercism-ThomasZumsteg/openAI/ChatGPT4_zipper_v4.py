class Zipper:
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
        return Zipper({'left': self.tree['left'], 'right': self.tree['right'], 'value': value}, self.crumbs)

    def left(self):
        if self.tree['left']:
            return Zipper(self.tree['left'], self.crumbs + (('left', self.tree['value'], self.tree['right']),))

    def set_left(self, left):
        return Zipper({'left': left, 'right': self.tree['right'], 'value': self.tree['value']}, self.crumbs)

    def right(self):
        if self.tree['right']:
            return Zipper(self.tree['right'], self.crumbs + (('right', self.tree['value'], self.tree['left']),))

    def set_right(self, right):
        return Zipper({'left': self.tree['left'], 'right': right, 'value': self.tree['value']}, self.crumbs)

    def up(self):
        if not self.crumbs:
            return None
        direction, value, sibling = self.crumbs[-1]
        return Zipper({'value': value, direction: self.tree, 'left' if direction == 'right' else 'right': sibling}, self.crumbs[:-1])

    def to_tree(self):
        current = self
        while current.crumbs:
            current = current.up()
        return current.tree