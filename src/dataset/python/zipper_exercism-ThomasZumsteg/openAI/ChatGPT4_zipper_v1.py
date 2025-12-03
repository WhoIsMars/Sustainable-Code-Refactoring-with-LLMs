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
        return Zipper({**self.tree, 'value': value}, self.crumbs)

    def left(self):
        left_tree = self.tree.get('left')
        if left_tree:
            return Zipper(left_tree, self.crumbs + (('left', self.tree['value'], self.tree['right']),))

    def set_left(self, left):
        return Zipper({**self.tree, 'left': left}, self.crumbs)

    def right(self):
        right_tree = self.tree.get('right')
        if right_tree:
            return Zipper(right_tree, self.crumbs + (('right', self.tree['value'], self.tree['left']),))

    def set_right(self, right):
        return Zipper({**self.tree, 'right': right}, self.crumbs)

    def up(self):
        if not self.crumbs:
            return None
        direction, value, sibling = self.crumbs[-1]
        return Zipper({
            'value': value,
            direction: self.tree,
            'left' if direction == 'right' else 'right': sibling
        }, self.crumbs[:-1])

    def to_tree(self):
        current = self
        while current.crumbs:
            current = current.up()
        return current.tree